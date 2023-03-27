#pragma once
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
class Map
{
public:
    GLuint VAO1, VBO1;
    GLuint shaderProgram;
    std::vector<Vertex> vertices;
    int init();
    int draw();
};

