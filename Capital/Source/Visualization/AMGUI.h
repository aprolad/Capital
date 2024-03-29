#pragma once
#pragma once
#include "../Header.h"
#include"../Simulation/Simulation.h"
class Graphic_element
{
protected:
	GLuint VBO, VAO;

	GLuint shaderProgram, fontShader;

	int x, y;
public:
	double size_x, size_y;
	bool hovered_on;
	bool active;
	void (*action) ();
	virtual void mouseCallback(double, double) {};
	virtual void mouse_move_callback(double mx, double my)
	{
			if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
			{
				hovered_on = true;
			}
			else
			{
				hovered_on = false;
			}
	}
	virtual void init()
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
	virtual void draw() {};
	virtual void prepare_shaders()
	{

		glUseProgram(shaderProgram);
		glm::mat4 trans = glm::mat4(1);
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));

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
	std::string text;
	glm::vec3 text_color;
	glm::vec3 button_color;
	double text_size;

	Quad_button* set_properties(GLuint shader, GLuint font, int ax, int ay, int sx, int sy, std::string atext, double text_size = 1)
	{
		this->text_size = text_size;
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		this->size_x = sx;
		this->size_y = sy;
		text = atext;
		text_color = { 1.0, 0.0f, 0.0f };
		button_color = { 0.0f, 0.0f, 0.0f };
		init();
		return this;
	}
	void mouseCallback(double mx, double my)
	{
		if (action != nullptr)
			if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
				action();
	}
	void mouse_move_callback(double mx, double my)
	{
			if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
			{
				hovered_on = true;
			}
			else
			{
				hovered_on = false;
			}
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		if (active)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"),0.5, 0.5, 1, 1);
		else if (hovered_on == true)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"),0.5, 0.5, 0.5, 1);
		else
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), button_color.x, button_color.y, button_color.z, 1);
		prepare_shaders();
		RenderText(fontShader, text, x - size_x * 0.9, y - 20, text_size, text_color);

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
template <typename T>
class Dynamic_text_element : virtual public Text_element
{
public:
	std::string num_to_string(double input)
	{
		std::vector<std::string> unit_of_measure{ "","Kg", "Denarius", "Km", "Square km" };
		std::vector<std::string> exponent_string{ "","Thousands","Millions", "Billions", "Trillions", "Quadrillions" };
		int exp = 0;
		double p = input;
		while (int(log10(p)) > 2 and p != 0)
		{
			exp++;
			p /= 1e3;
		}
		std::stringstream stream;
		stream << std::fixed << std::setprecision(3) << p;
		return stream.str() + " " + exponent_string[exp] + " " + unit_of_measure[0];
	}
	T binded_value;
	std::string postfix;
	std::string* ready_text;
	double text_size;
	Dynamic_text_element* set_properties(T bind, GLuint shader, GLuint font, int ax, int ay, std::string atext, std::string post, double text_size = 0.5)
	{
		this->text_size = text_size;
		postfix = post;
		binded_value = bind;
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		ready_text = nullptr;
		text = atext;
		return this;
	}

	Dynamic_text_element* set_properties(std::string* text, GLuint shader, GLuint font, int ax, int ay, std::string atext, double text_size = 0.5)
	{
		this->text_size = text_size;
		ready_text = text;
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		this->text = atext;
		return this;
	}

	void draw()
	{
		prepare_shaders();
		if (ready_text != nullptr)
		{
			RenderText(fontShader, text + *ready_text, x - 100 * 0.85, y, text_size, glm::vec3(1.0, 0.0f, 0.0f));
		}
		else
		{

			std::string result;
			std::vector<std::string> unit_of_measure{ "","Kg", "Denarius", "Km", "Square km" };
			std::vector<std::string> exponent_string{ "","Thousands","Millions", "Billions", "Trillions", "Quadrillions", "", ""};

			int exp = 0;
			double p = *binded_value;
			while (int(log10(p)) > 2 and p != 0)
			{
				exp++;
				p /= 1e3;
			}
			std::stringstream stream;
			stream << std::fixed << std::setprecision(3) << p;
			result = text + stream.str() + " " + exponent_string[exp] + " " + unit_of_measure[0];


			RenderText(fontShader, result, x - 100 * 0.85, y, text_size, glm::vec3(1.0, 0.0f, 0.0f));
		}
	}


};


class Information_panel : virtual public Graphic_element
{
public:
	std::string text;
	std::vector<Text_element*> text_elements;
	void add_text_element(std::string atext, int x, int y)
	{
		Text_element* t = (new Text_element())->set_properties(shaderProgram, fontShader, x, y, atext);
		t->init();
		text_elements.push_back(t);

	}
	template <typename T>
	void add_dynamic_text_element(std::string atext, std::string postfix, int x, int y, T bind)
	{
		Dynamic_text_element<T>* t = (new Dynamic_text_element<T>())->set_properties(bind, shaderProgram, fontShader, x, y, atext, postfix);
		t->init();
		text_elements.push_back(t);

	}
	void add_dynamic_text_element(std::string atext, std::string* text, int x, int y)
	{
		Dynamic_text_element<double*>* t = (new Dynamic_text_element<double*>())->set_properties(text, shaderProgram, fontShader, x, y, atext);
		t->init();
		text_elements.push_back(t);

	}
	Information_panel* set_properties(GLuint shader, GLuint font, int ax, int ay, int sx = 220, int sy = 350)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = sx;
		size_y = sy;
		init();
		return this;
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

class Chart : virtual public Graphic_element
{
public:
	void draw(std::vector<double> _data);
	void set_properties(GLuint shader, GLuint font);
	GLuint VAO, VBO;
	double x, y;
};


class Linear_chart : virtual public Chart
{
public:
	Linear_chart(int len, int siz)
	{
		data.resize(len);
		maxHistory.resize(1000);
		sizing = siz;
		length = 1200;
	}

	std::vector<double> data;
	int sizing;
	double length;
	std::deque <double> maxHistory;
	void set_properties(GLuint shader, GLuint font)
	{
		shaderProgram = shader;
		fontShader = font;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}

	void draw(std::vector<double> _data)
	{
		data = _data;
		auto min = std::min_element(std::begin(data), std::end(data));
		auto max = std::max_element(std::begin(data), std::end(data));

		maxHistory.push_front(*max);
		maxHistory.pop_back();
		double maxHistoryT = 0;
		for (int i = 0; i < 100; i++)
			maxHistoryT += maxHistory[i];
		double range = (*max - 0) + 1;

		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(600, 350, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		int dtr = 0;
		GLfloat* vertices = new GLfloat[sizing * 3 + 3];
		for (int i = 0; i < sizing * 3; i += 3)
		{
			vertices[i] = dtr * (length / sizing);
			vertices[i + 1] = (data[dtr] / (maxHistoryT / 100)) * 400;
			vertices[i + 2] = 0;
			dtr++;
		};

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sizing * 3, vertices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, sizing);
		glBindVertexArray(0);
		delete[] vertices;
		glUseProgram(shaderProgram);
		trans = glm::mat4(1);
		trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		draw_line(600, 350, 1900, 350);
		draw_line(600, 350, 600, 780);
		std::string str = "";
		str = str + std::to_string(int(*std::max_element(std::begin(data), std::end(data))));
		RenderText(fontShader, str, 540, 750, 0.3, glm::vec3(1.0, 0.0f, 0.0f));

		draw_scale();
	}

	virtual void draw_scale() {}
};
class GDP_chart : virtual public Linear_chart
{
public:
	GDP_chart(int len, int siz) : Linear_chart(len, siz) {}

	void draw_scale()
	{
		std::string str = "";
		str = std::to_string(int(sizing));
		RenderText(fontShader, str, 1500, 280, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
	}
};

class Age_chart : virtual public  Linear_chart
{
public:
	Age_chart(int len, int siz) : Linear_chart(len, siz) {}

	void draw_scale()
	{
		std::string str = "";
		for (int i = 0; i < 11; i++)
		{
			str = "";
			str = str + std::to_string(i * 10);
			RenderText(fontShader, str, 600 + i * 120, 330, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
		}
	}
};

class Pie_chart : virtual public Chart
{
public:
	Pie_chart(GLuint shader, GLuint font, double _x, double _y)
	{
		x = _x;
		y = _y;
		shaderProgram = shader;
		fontShader = font;
		glGenVertexArrays(1, &VBO);
		glGenBuffers(1, &VAO);
	}
	void set_properties(GLuint shader, GLuint font)
	{
		//shaderProgram = shader;
		//fontShader = font;
		//glGenVertexArrays(1, &VAO1);
		//glGenBuffers(1, &VBO1);
	}
	std::vector<GLfloat> shape;

	void draw_slice(GLfloat x, GLfloat y, double radius, double start_angle, double end_angle, glm::vec4 color) {
		std::vector <GLfloat> shp;
		int num_segments = 4000;
		double theta = (end_angle - start_angle) / double(num_segments - 1);
		double tangetial_factor = tanf(theta);
		double radial_factor = cosf(theta);

		double x1 = radius * cosf(start_angle);
		double y1 = radius * sinf(start_angle);

		shp.push_back(x); // center of the circle
		shp.push_back(y); // center of the circle
		shp.push_back(0); // center of the circle

		for (int i = 0; i <= num_segments; i++) {
			shp.push_back(x + x1); // center of the circle
			shp.push_back(y + y1); // center of the circle
			shp.push_back(0);
			GLfloat tx = -y1;
			GLfloat ty = x1;
			x1 += tx * tangetial_factor;
			y1 += ty * tangetial_factor;
			x1 *= radial_factor;
			y1 *= radial_factor;
		}
		

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, shp.size() * sizeof(GLfloat), shp.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), color[0]/255, color[1]/255, color[2]/255, color[3]/255);
		glDrawArrays(GL_TRIANGLE_FAN, 0, shp.size() / 3);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);

	}

	void draw(std::vector<Profession> data)
	{
		double current_angle = 0;
		double radius = 260;
	

		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		double start_angle = 0.0f, end_angle = 0.0f;
		for (int i = 0; i < data.size(); i++) {
			end_angle = start_angle + data[i].percent_of_workforce * 2.0f * glm::pi<float>();
			draw_slice(0, 0, radius, start_angle, end_angle, data[i].color);
			start_angle = end_angle;
		}

		glUseProgram(shaderProgram);
		trans = glm::mat4(1);
		trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		for (int i = 0; i < data.size(); i++)
		{
			RenderText(fontShader, data[i].name, x, i * 25 + y - 500, 0.6, glm::vec3(0.0, 0.0f, 0.0f));
			
			glUseProgram(shaderProgram);
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), data[i].color[0] / 255, data[i].color[1] / 255, data[i].color[2] / 255, data[i].color[3] / 255);
			draw_quad(x - 10, i* 25 + y - 490, 10);
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"),0, 0, 0,1);
		}

		

		//draw_line(600, 350, 1900, 350);
		//draw_line(600, 350, 600, 780);
		std::string str = "";
		//str = str + std::to_string(int(*std::max_element(std::begin(data), std::end(data))));
		RenderText(fontShader, str, 540, 750, 0.3, glm::vec3(1.0, 0.0f, 0.0f));

		//draw_scale();
	}

	//virtual void draw_scale() {}
};



class Multiple_choice_panel : virtual public Quad_button
{
public:
	std::vector<Multiple_choice_panel*>* top_menus;
	std::vector<Multiple_choice_panel*> root_menus;
	Multiple_choice_panel* set_properties(std::vector<Multiple_choice_panel*>* atop_menus, GLuint shader, GLuint font, int ax, int ay, int sx, int sy, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = sx;
		size_y = sy;
		text = atext;
		top_menus = atop_menus;
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
		return this;
	}
	Quad_button* base;

	Information_panel* panel;
	void draw_button()
	{
		glUseProgram(shaderProgram);
		if (active)
			base->active = true;
		else
			base->active = false;
		base->draw();
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
	}
	void mouseCallback(double mx, double my)
	{
		for (auto a : root_menus)
		{
			a->mouseCallback(mx, my);
		}
		if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
		{
			bool t = active;
			for (int i = 0; i < top_menus->size(); i++)
			{
				(top_menus->at(i))->active = false;
			}
			active = !t;
		}
	}
	void mouse_move_callback(double mx, double my)
	{
		for (auto& a : root_menus)
		{
			a->mouse_move_callback(mx, my);
		}
		base->mouse_move_callback(mx, my);
		if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
		{
			
		}
	}
	void init()
	{

	}
	void draw()
	{

		if (active)
		{
			panel->draw();
		}
		base->draw();

	}
};