#pragma once

#define GLM_FORCE_DOUBLE_PRECISION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "World.h"
#include "../Header.h"
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
struct State_zone
{
    void init(Map* _map, double* _size, glm::vec4 _color)
    {
        color = _color;
        map = _map;
        size = _size;
    }
	std::vector<uint32_t> indices;
    glm::vec4 color;
    std::vector<GLfloat> shape;
    double centre_x=0, centre_y=0;
    double* size;
    Map* map;
    void mouse_callback(int x, int y);
    void draw_zone_of_control();
};
class Map
{
public:
    Map()
    {
        State_zone t;
        t.init(this, &size, glm::vec4(0, 1, 0, 1));
        t.centre_x = 35;
        t.centre_y = -100;
        state_zones.push_back(t);
        State_zone t1;
        t1.init(this, &size, glm::vec4(1, 0, 0, 1));
        t1.centre_x = -15;
        t1.centre_y = -100;
        state_zones.push_back(t1);
    }
    std::vector<State_zone> state_zones;
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
    void mouse_callback(int mx, int my);
    double previous_x, previous_y;
private:
    void draw_map_sizing();
};

