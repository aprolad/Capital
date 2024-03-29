#include "Map.h"
#include "../Header.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>
#include "Visualization.h"
#include <array>
#include <math.h>
extern Visualization visualization;
extern Simulation simulation;

Vertex transformCoordinates(double longitude, double latitude)
{
    Vertex t;
    t.position.x = (longitude + 180.0) * (1000.0 / 360.0) - 500;
    t.position.y = (1 - log(tan(latitude * M_PI / 180.0) + 1 / cos(latitude * M_PI / 180.0)) / M_PI) * 500.0 - 500;
    return t;
}
int Map::init()
{
    army_visualizator.construct_armies();

    x_slot = visualization.window_resolution.x / 50;
    y_slot = visualization.window_resolution.y / 50;
    x = -2500;
    y = -1500;
    centre_translate_x = visualization.window_resolution.x/2;
	centre_translate_y = visualization.window_resolution.y/2;
    size = 1;
	
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



        for (int i = 0; i < simulation.world.map.size(); i++)
        {
            for (int c = 0; c < simulation.world.map.size(); c++)
            {
                glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), simulation.world.map[i][c].color.x, simulation.world.map[i][c].color.y, simulation.world.map[i][c].color.z, 1);
                simulation.world.map[i][c].draw();

            }
        }
        if (simulation.world.choosen_tile != nullptr)
        {
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0,0, 1);
            simulation.world.choosen_tile->choosen_draw();
        }
        

        army_visualizator.draw();

        draw_map_sizing();
        previous_x = x;
        previous_y = y;
        return 0;
}

void Map::mouse_callback(int mx, int my, int button, int action)
{
	double t_x = (mx - centre_translate_x) / size - x + 25;
    double t_y = (my - centre_translate_y) / size - y + 25;


    army_visualizator.callback(t_x - 10, t_y - 10, button, action);


    int x_tile = int(t_x) / 50;
	int y_tile = int(t_y) / 50;
    if (x_tile >= 0 && x_tile < 100 && y_tile >= 0 && y_tile < 100 && button == GLFW_MOUSE_BUTTON_LEFT)
    {
        simulation.world.choosen_tile = &simulation.world.map[y_tile][x_tile];
        if (simulation.world.map[y_tile][x_tile].owner == 2)
            visualization.scene[1]->enemy = true;
        else
            visualization.scene[1]->enemy = false;
    }

}

void Army_visualization::draw()
{
	glUniform4f(glGetUniformLocation(map->shaderProgram, "ourColor"), 1, 0, 0, 1);
    draw_quad(reference->x, reference->y, 15);
	glUniform4f(glGetUniformLocation(map->shaderProgram, "ourColor"), 0, 0, 0, 1);
	draw_line(reference->x-reference->size, reference->y-reference->size, reference->x+reference->size, reference->y+reference->size);
	draw_line(reference->x+reference->size, reference->y-reference->size, reference->x-reference->size, reference->y+reference->size);
    if (choosen)
    {
		glUniform4f(glGetUniformLocation(map->shaderProgram, "ourColor"), 1, 1, 1, 1);
		draw_border(reference->x-15, reference->y-15, reference->x+15, reference->y+15, 1);
    }
}

void Army_visualization::callback(double x, double y, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (is_click_in_square(x, y, reference->x, reference->y, 15))
        {
            choosen = true;
        }
        else
            choosen = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
		if (choosen)
		    reference->set_move_target(x-15, y-15);
    }
}