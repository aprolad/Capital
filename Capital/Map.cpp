#include "Map.h"
#include"Header.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>
#include "gdal_priv.h"
#include "ogrsf_frmts.h"
#include "Visualization.h"
#include "misc/earcut.hpp"
#include <array>
#include <math.h>
extern Visualization visualization;
extern World world;

Vertex transformCoordinates(double longitude, double latitude)
{
    Vertex t;
    t.position.x = (longitude + 180.0) * (1000.0 / 360.0) - 500;
    t.position.y = (1 - log(tan(latitude * M_PI / 180.0) + 1 / cos(latitude * M_PI / 180.0)) / M_PI) * 500.0 - 500;
    return t;
}
int Map::init()
{
    x_slot = visualization.window_resolution.x / 50;
    y_slot = visualization.window_resolution.y / 50;
    x = -2500;
    y = -1500;
    centre_translate_x = visualization.window_resolution.x/2;
	centre_translate_y = visualization.window_resolution.y/2;
    size = 1;
    world.init();
    return 0;
}
void Map::draw_map_sizing()
{
    glUseProgram(shaderProgram);
    glm::mat4 trans = glm::mat4(1);
    GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
    draw_rectangle(x_slot * 45, 890, 75, 25);
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 1, 0, 0, 1);
    draw_line(x_slot * 44, 890, x_slot * 46, 890);
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
    // Calculate sizing of the map based on lattitude 45 degrees
    RenderText(fontShader, std::to_string(size) + " Km", x_slot * 44, 890, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
}
int Map::draw()
{

        glUseProgram(shaderProgram);
        GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glm::mat4 trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(centre_translate_x, centre_translate_y, 0.0f));
        trans = glm::scale(trans, glm::vec3(size, size, size));
        trans = glm::translate(trans, glm::vec3(x, y, 0.0f));


       
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        for (int i = 0; i < world.map.size(); i++)
        {
            for (int c = 0; c < world.map.size(); c++)
            {
                glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), world.map[i][c].color.x, world.map[i][c].color.y, world.map[i][c].color.z, 1);
                world.map[i][c].draw();

            }
        }
        if (world.choosen_tile != nullptr)
        {
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0,0, 1);
            world.choosen_tile->choosen_draw();
        }
        draw_map_sizing();
        previous_x = x;
        previous_y = y;
        return 0;
}

void Map::mouse_callback(int mx, int my)
{
	double t_x = (mx - centre_translate_x) / size - x + 25;
    double t_y = (my - centre_translate_y) / size - y + 25;
    int x_tile = int(t_x) / 50;
	int y_tile = int(t_y) / 50;
    if (x_tile >= 0 && x_tile < 100 && y_tile >= 0 && y_tile < 100)
    {
        world.choosen_tile = &world.map[y_tile][x_tile];
    }
    std::cout << t_x << " " << t_y << std::endl;

}
void State_zone::mouse_callback(int mx, int my)
{


}


