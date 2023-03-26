#pragma once
#include "Header.h"
#include "game/simulation.h"
class Graphic_element
{
protected:
	GLuint VBO, VAO;

	GLuint shaderProgram, fontShader;
	int x, y;
public:
	simulation* simulation;
	void (*action) ();
	virtual void mouseCallback(double, double) {};
	virtual void init() {};
	virtual void draw() {};
	virtual void prepare_shaders() 
	{

		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		trans = glm::scale(trans, glm::vec3(100 / 50, 100 / 50, 100 / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	};
	virtual void set_properties() {};
};

class Quad_button : virtual public Graphic_element
{
public:
	int size;
	std::string text;
	Quad_button* set_properties(GLuint shader, GLuint font, int ax, int ay, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		text = atext;
		return this;
	}
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size) && mx < (x + size) && my >(y - size) && my < (y + size))
			action();
	}
	void init()
	{
		GLfloat vertices[] = {
		50.0f, -50.0f, 0.0f,
		50.0f, 50.0f, 0.0f,
		-50.0f, -50.0f, 0.0f,
		-50.0f, 50.0f, 0.0f
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
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		trans = glm::scale(trans, glm::vec3(100 / 50, 100 / 50, 100 / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		RenderText(fontShader, text, x - 100 * 0.85, y, 150 / 150, glm::vec3(1.0, 0.0f, 0.0f));

	}

};

class Text_element : virtual public Graphic_element
{
public:
	int size;
	std::string text;
	Text_element* set_properties(GLuint shader, GLuint font, int ax, int ay, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		text = atext;
		return this;
	}
	void draw()
	{
		prepare_shaders();
		RenderText(fontShader, text, x - 100 * 0.85, y, 150 / 150, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class Dynamic_text_element : virtual public Text_element
{
public:
	double* binded_value;
	Dynamic_text_element* set_properties(double* bind, GLuint shader, GLuint font, int ax, int ay, std::string atext)
	{
		binded_value = bind;
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		text = atext;
		std::cout <<"!"<< bind << endl;
		return this;
	}
	void draw()
	{
		prepare_shaders();
		string str = text+to_string(int(*binded_value));
		RenderText(fontShader, str, x - 100 * 0.85, y, 150 / 150, glm::vec3(1.0, 0.0f, 0.0f));
	}

};
class Information_panel : virtual public Graphic_element
{
public:
	int size_x, size_y;
	std::string text;
	std::vector<Text_element*> text_elements;
	void add_text_element(std::string atext, int x, int y)
	{
		Text_element* t = (new Text_element())->set_properties(shaderProgram, fontShader, x, y, atext);
		t->init();
		text_elements.push_back(t);

	}
	void add_dynamic_text_element(std::string atext, int x, int y, double* bind)
	{
		Dynamic_text_element* t = (new Dynamic_text_element())->set_properties(bind, shaderProgram, fontShader, x, y, atext);
		t->init();
		text_elements.push_back(t);

	}
	Information_panel* set_properties(GLuint shader, GLuint font, int ax, int ay)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = 50;
		size_y = 150;
		return this;
	}
	void init()
	{
		GLfloat vertices[] = {
		size_x, -size_y, 0.0f,
		size_x, size_y, 0.0f,
		-size_x, -size_y, 0.0f,
		-size_x, size_y, 0.0f
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
		prepare_shaders();
	
		
		for (auto i : text_elements)
		{
			i->draw();
		}
	}

};
class ageChart : virtual public Graphic_element
{
public:
	void set_properties(GLuint shader, GLuint font)
	{
		shaderProgram = shader;
		fontShader = font;

	}
	ageChart()
	{
		data.resize(1600);
		maxHistory.resize(1000);
	}
	vector<double> data;
	double sizing;
	deque <double> maxHistory;
	void draw()
{
		GLuint VAO1, VBO1;
		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);
	std::vector<double>::iterator min = std::min_element(std::begin(data), std::end(data));
	std::vector<double>::iterator max = std::max_element(std::begin(data), std::end(data));

	double range = (*max - *min) + 1;

	maxHistory.push_front(*max);
	maxHistory.pop_back();
	double maxHistoryT = 0;
	for (int i = 0; i < 100; i++)
		maxHistoryT += maxHistory[i];
	glUseProgram(shaderProgram);
	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(600, 350, 0.0f));
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	int dtr = 0;
	GLfloat vertices[4800];
	for (int i = 0; i < 4800; i += 3)
	{
		vertices[i] = dtr;
		vertices[i + 1] = (data[dtr]/(maxHistoryT/100)) * 400;
		vertices[i + 2] = 0;
		dtr++;
	};

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO1);
	glDrawArrays(GL_LINE_STRIP, 0, 1600);
	glBindVertexArray(0);

	glUseProgram(shaderProgram);
	trans = glm::mat4(1);
	trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
	transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//drawLine(600, 350, 1900, 350);
	//drawLine(600, 350, 600, 780);

	string str = "";
	str = str + std::to_string(int(*max));
	//RenderText(fontShader, str, 540, 750, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
}
};
class Top_menu : public virtual Quad_button
{

public:
	ageChart chart;
	std::vector<Top_menu*> *top_menus;
	Top_menu* set_properties(std::vector<Top_menu*> *atop_menus, GLuint shader, GLuint font, int ax, int ay, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		text = atext;
		top_menus = atop_menus;
		return this;
	}
	Quad_button* base;
	bool active;
	Information_panel* panel;
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size) && mx < (x + size) && my >(y - size) && my < (y + size))
		{
			bool t = active;
			for (int i = 0; i<top_menus->size(); i++)
			{
				(top_menus->at(i))->active = false;
			}
			active = !t;
		}
	}
	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 150, 950);
		panel->init();
		panel->add_text_element("Economics", 150, 1000);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, text);
		base->init();
		chart.init();
		chart.set_properties(shaderProgram, fontShader);
	}
	void draw()
	{
		base->draw();
		double temp;
		for (int i = 0; i < 1600; i++)
		{
			temp = 0;
			for (int c = 0; c < 24; c++)
				temp += simulation->population.agePyramid[i * 25 + c];
			chart.data[i] = temp;
			//std::cout << chart.data[i];
		}
		chart.draw();
		if (active)
			panel->draw();
	}
};

class Demographics_menu : virtual public Top_menu
{
public:

	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 150, 950);
		panel->init();
		panel->add_dynamic_text_element("Population: ", 350, 1000, &simulation->population.population);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, text);
		base->init();
	}
};