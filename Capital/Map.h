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
    Line* previous;
    Line* next;
};
class Map
{
public:
    double x_slot;
    double y_slot;
    int debug;
    std::vector<Line> lines;
    GLuint VAO1, VBO1;
    GLuint shaderProgram, fontShader;
    std::vector<Vertex> vertices;
    std::vector<std::vector<Vertex>> map_features;
    Vertex center_point;
    int vertex_count;
    double size;
    double x, y;
    int init();
    int draw();
    void draw_zone_of_control();
private:
    double previous_x, previous_y;
    std::vector<GLfloat> shape;
    void calculate_zone_of_control();
    void draw_border();
};

