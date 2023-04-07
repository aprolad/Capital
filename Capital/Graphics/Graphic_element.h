#pragma once
#include "../Header.h"
#include "../game/Simulation.h"
#include "Utility_graphic_functions.h"

class Graphic_element
{
protected:
	GLuint VBO, VAO;

	GLuint shaderProgram, fontShader;
	double size_x, size_y;
	int x, y;
public:
	Simulation* simulation;
	void (*action) ();
	virtual void mouseCallback(double, double) {};
	virtual void init() {};
	virtual void draw() {};
	virtual void prepare_shaders() 
	{

		glUseProgram(shaderProgram);
		glm::mat4 trans;
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
	int sx, sy;
	glm::vec3 text_color;
	Quad_button* set_properties(GLuint shader, GLuint font, int ax, int ay, int sx, int sy, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		this->sx = sx;
		this->sy = sy;
		text = atext;
		text_color = { 1.0, 0.0f, 0.0f };
		init();
		return this;
	}
	void mouseCallback(double mx, double my)
	{
		if (action !=nullptr)
			if (mx > (x - sx) && mx < (x + sx) && my >(y - sy) && my < (y + sy))
				action();
	}
	void init()
	{
		GLfloat vertices[] = {
		sx, -sy, 0.0f,
		sx, sy, 0.0f,
		-sx, -sy, 0.0f,
		-sx, sy, 0.0f
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
		double size = 3 / double(text.size()) + 0.4;
		RenderText(fontShader, text, x - sx * 0.9, y-20, 1, text_color);

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
	T binded_value;
	std::string postfix;
	Dynamic_text_element* set_properties(T bind, GLuint shader, GLuint font, int ax, int ay, std::string atext, std::string post)
	{
		postfix = post;
		binded_value = bind;
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
		std::stringstream stream; stream << std::fixed << std::setprecision(0) << *binded_value;
		std::string s = stream.str();
		//string str = text+to_string(double());
		RenderText(fontShader, text + s + postfix, x - 100 * 0.85, y, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
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
	template <typename T>
	void add_dynamic_text_element(std::string atext, std::string postfix, int x, int y, T bind)
	{
		Dynamic_text_element<T>* t = (new Dynamic_text_element<T>())->set_properties(bind, shaderProgram, fontShader, x, y, atext, postfix);
		t->init();
		text_elements.push_back(t);

	}
	Information_panel* set_properties(GLuint shader, GLuint font, int ax, int ay)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = 120;
		size_y = 250;
		init();
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

class abs_chart : virtual public Graphic_element
{
public:
	GLuint VAO1, VBO1;
	vector<double> data;
	int sizing;
	double length;
	deque <double> maxHistory;
	void set_properties(GLuint shader, GLuint font, ::Simulation* s)
	{
		shaderProgram = shader;
		fontShader = font;
		simulation = s;
		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);
	}

	void prp()
	{
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

		glBindVertexArray(VAO1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sizing * 3, vertices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(VAO1);
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
		string str = "";
		str = str + std::to_string(int(*std::max_element(std::begin(data), std::end(data))));
		RenderText(fontShader, str, 540, 750, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class Chart : virtual public abs_chart
{
public:
	Chart(int len)
	{
		data.resize(len);
		maxHistory.resize(1000);
		sizing = len;
		length = 1200;

	}
		void draw()
	{
			
			prp();
		string str = "";

		str = std::to_string(int(sizing));
		RenderText(fontShader, str, 1500, 280, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
	}
};

class ageChart  : virtual public abs_chart
{
public:
	
	ageChart()
	{
		data.resize(2000);
		maxHistory.resize(1000);
		sizing = 120;
		length = 1200;
	}

	void draw()
{
		
		data = std::vector(simulation->population.agePyramid.begin(), simulation->population.agePyramid.end());
		data[0] = data[1];
		prp();

		string str = "";

		for (int i = 0; i < 11; i++)
		{
			str = "";
			str = str + std::to_string(i*10);
			RenderText(fontShader, str, 600 + i*120, 330, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
		}
}
};
class Top_menu : public virtual Quad_button
{

public:
	std::vector<Top_menu*> *top_menus;
	Top_menu* set_properties(std::vector<Top_menu*> *atop_menus, GLuint shader, GLuint font, int ax, int ay, int sx, int sy, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = sx;
		size_y = sy;
		text = atext;
		top_menus = atop_menus;
		return this;
	}
	Quad_button* base;
	bool active;
	Information_panel* panel;
	void draw_button()
	{
		glUseProgram(shaderProgram);
		if (active)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.5, 0.5, 1, 1);
		base->draw();
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
	}
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
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

class Economics_menu : virtual public Top_menu
{
public:

	Chart* chartG;
	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

		panel->add_dynamic_text_element("GDP: "," Denarius", x, y - 400, &simulation->GDP.total);

		panel->add_dynamic_text_element("Wheat: ", " Tonnes", x, y - 450, &simulation->agriculture.t);

		panel->add_dynamic_text_element("Total arable land:  ", " Square km", x, y - 550, &simulation->geo.totalArableLand);

		panel->add_dynamic_text_element("Wheat output: ", " Tonnes", x, y - 650, &simulation->agriculture.outputT);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
		chartG = new Chart(900);
		chartG->init();
		chartG->set_properties(shaderProgram, fontShader, simulation);
	}
	void draw()
	{
		draw_button();

		if (active)
		{
			panel->draw();

			chartG->data = simulation->GDP.history;
			chartG->draw();
		}
		
	}
};
class Demographics_menu : virtual public Top_menu
{
public:
	ageChart chart;
	Chart* chartG;
	void draw()
	{
		draw_button();
		if (active)
		{
			panel->draw();
			chart.draw();
		}
	}
	void init()
	{
		chart.init();
		chart.set_properties(shaderProgram, fontShader, simulation);
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
		panel->add_dynamic_text_element("Population: "," ", 250, y - 400, &simulation->population.population);
		panel->add_dynamic_text_element("Labor pool: ","", 250, y - 450, &simulation->population.laborPool);
		panel->add_dynamic_text_element("Food supply: ","", 250, y - 500, &simulation->population.foodSupply);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
	}
};

class Technology_menu : virtual public Top_menu
{
public:

	Chart* chartG;
	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

		
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
		chartG = new Chart(900);
		chartG->init();
		chartG->set_properties(shaderProgram, fontShader, simulation);
	}
	void draw()
	{
		draw_button();

		if (active)
		{
			panel->draw();

			chartG->data = simulation->GDP.history;
			chartG->draw();
		}

	}
};

class Goverment_menu : virtual public Top_menu
{
public:

	Chart* chartG;
	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

		

		panel->add_dynamic_text_element("Wheat: ", "Kg" , x, y - 650, &simulation->agriculture.output);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
		chartG = new Chart(900);
		chartG->init();
		chartG->set_properties(shaderProgram, fontShader, simulation);
	}
	void draw()
	{
		draw_button();

		if (active)
		{
			panel->draw();

			chartG->data = simulation->GDP.history;
			chartG->draw();
		}

	}
};

class Panel : virtual public Graphic_element
{
public:
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
			for (auto a : buttons)
				a.mouseCallback(mx, my);
	}
	Quad_button buttons[3];
	static int* gs;
	Panel* set_properties(GLuint shader, GLuint font, int ax, int ay, int sx, int sy)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = sx;
		size_y = sy;
		init();
		gs = &simulation->game_speed;
		buttons[0] = *(new Quad_button())->set_properties(shaderProgram, fontShader, 2005, 1250, 20, 20, "1");
		buttons[0].text_color = { 1,0,0 };
		buttons[0].action = []() -> void { *gs = 1; };
		buttons[1] = *(new Quad_button())->set_properties(shaderProgram, fontShader, 2050, 1250, 20, 20, "2");
		buttons[1].text_color = { 1,1,0 };
		buttons[1].action = []() -> void { *gs = 10; };
		buttons[2] = *(new Quad_button())->set_properties(shaderProgram, fontShader, 2095, 1250, 20, 20, "3");
		buttons[2].text_color = { 0,1,0 };
		buttons[2].action = []() -> void { *gs = 100; };
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
		
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.3, 0.3, 0, 1);
		for (auto a : buttons)
			a.draw();
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0, 1);
	}
};

class Multiple_choice_panel
{
public:

};