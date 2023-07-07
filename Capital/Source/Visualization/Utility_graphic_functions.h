#pragma once
#include "../Header.h"
void draw_line(double x1, double y1, double x2, double y2);
void draw_point(double x1, double y1);
void draw_quad(double x, double y, double size);
void draw_rectangle(double x, double y, double size_x, double size_y);
void draw_border(double x1, double y1, double x2, double y2, double);
void reset_matrix(GLuint shader_program);