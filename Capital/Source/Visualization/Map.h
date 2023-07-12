#pragma once

#define GLM_FORCE_DOUBLE_PRECISION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Simulation/Simulation.h"
#include "World.h"
#include "../Header.h"
extern Simulation simulation;
struct Vertex {
    glm::vec2 position;
};
struct Line
{
    Line()
    {

    }
    Line(const glm::vec2& a, const glm::vec2& b)
    {
        start = a;
        end = b;
    }
    glm::vec2 start;
    glm::vec2 end;
    glm::vec2 dir_vector()
    {
        return end - start;
    }

};
class Map;

struct Army_visualization
{
    Army_visualization(Army* r, Map* m)
    {
        map = m;
        reference = r;
        choosen = false;
    }
    bool choosen;
    glm::vec2 position;
    Army* reference;
    Map* map;
    void draw();
    void callback(double x, double y, int button, int action);
};
class Army_visualizator
{
    public:
    Army_visualizator(Map* m)
    {
        map = m;
    }
    Map* map;
    std::vector<Army_visualization> armies;
    void construct_armies()
    {
        Army_visualization t(&simulation.player.army, map);
        armies.push_back(t);
    }
    void callback(double x, double y, int button, int action)
    {
        for (auto& i : armies)
            i.callback(x, y, button, action);
    }
    void draw()
    {
        for (auto& i : armies)
            i.draw();
    }
};
class Map
{
public:
    Map()
    {

    }
    Army_visualizator army_visualizator{this};
    double x_slot;
    double y_slot;
    std::vector<Line> lines;
    GLuint VAO1, VBO1, IBO;
    GLuint shaderProgram, fontShader;
    std::vector<Vertex> vertices;
    std::vector<std::vector<Vertex>> map_features;
    Vertex center_point;
    int vertex_count;
    double size;
    double x, y;
    int centre_translate_x;
    int centre_translate_y;
    int init();
    int draw();
    void mouse_callback(int mx, int my, int button, int action);
    double previous_x, previous_y;
private:
    void draw_map_sizing();
};

