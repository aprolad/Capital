#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Header.h"
struct tile
{
	tile()
	{

	}
	float x, y;
	float size;
	glm::vec4 color;
	GLuint VAO, VBO;
	short owner;
	void init(double _x, double _y, double _size)
	{
		x = _x;
		y = _y;
		size = _size;
		GLfloat vertices[] {
		x - size, y - size, 0.0f,
		x - size, y + size, 0.0f,
		x + size, y + size, 0.0f,
		x + size, y - size, 0.0f,
		};


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void draw()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
	}
	void choosen_draw()
	{
		draw_line(x + size, y - size, x + size, y + size);
		draw_line(x - size, y - size, x - size, y + size);
		draw_line(x - size, y + size, x + size, y + size);
		draw_line(x - size, y - size, x + size, y - size);
	}
	~tile()
	{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	}
};
class World
{
public:
	World()
	{
	
	}
	void init()
	{
		map.resize(100);
		for (int y = 0; y<100; y++)
		{
			map[y].resize(100);
			for (int x = 0; x<100; x++)
			{
				map[y][x].init(x * 50, y * 50, 25);
				map[y][x].color = glm::vec4(0, 0, 1, 1);

			}
		}
		double angle = 0;
		for (int y = 0; y<100; y++)
			for (int x = 0; x<100;x++)
			{
				if (pow(x-50,2) + pow(y-50,2) < 1200)
					map[y][x].color = glm::vec4(0, 0.5, 0.0, 1);

			}
	}
	std::vector<std::vector<tile>> map;
	tile* choosen_tile;
};
