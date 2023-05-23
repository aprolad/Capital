#pragma once
#define GLM_FORCE_DOUBLE_PRECISION
#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_geometry.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ogrsf_frmts.h>
#include "Header.h"
struct Vertex {
    glm::vec2 position;
};
struct Line
{
    glm::vec2 start;
    glm::vec2 end;

};
class Map;
struct State_zone
{
    void init(Map* _map, double* _size)
    {
        map = _map;
        size = _size;
    }
    std::vector<GLfloat> shape;
    double centre_x=0, centre_y=0;
    double* size;
    Map* map;
    void calculate_zone_of_control();
    void draw_zone_of_control();
};
class Map
{
public:
    Map()
    {
        State_zone t;
        t.init(this, &size);
        state_zones.push_back(t);
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
    std::vector<uint32_t> indices;
    int init();
    int draw();

    double previous_x, previous_y;
private:
    void draw_map_sizing();
};

