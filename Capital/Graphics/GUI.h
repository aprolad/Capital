#pragma once
#include "CAP_graphics.h"

class button
{
public:
	virtual void draw() {};
	virtual void mouseCallback(double, double) {};
};
class quadButton : virtual public button
{
public:
	quadButton()
	{
		this->x = 0;
		this->y = 0;
		this->size = 0.2;
		poly = base;
	}
	quadButton(double x, double y, double size)
	{
		this->x = x;
		this->y = y;
		this->size = 0.2;
		poly = base;
	}
	void (*func)(void);
	double x, y;
	double size;
	graphicObject poly;
	std::string text;
	void draw();
	void mouseCallback(double mx, double my) 
	{
		if (mx > (x - size) && mx < (x + size) && my >(y - size) && my < (y + size))
			(*func)();
	}
};
class exitButton : public quadButton
{
public:
	exitButton(double x, double y, double size)
	{
		this->x = x;
		this->y = y;
		this->size = size;
	}
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size) && mx < (x + size) && my >(y - size) && my < (y + size))
			exit(1);
	}

};
class startButton : public quadButton
{
public:
	startButton(double x, double y, double size)
	{
		this->x = x;
		this->y = y;
		this->size = size;
		poly = base;
	}
	void mouseCallback(double mx, double my);
};
class returnButton : public quadButton
{
public:
	returnButton(double x, double y, double size)
	{
		this->x = x;
		this->y = y;
		this->size = size;
		poly = base;
	}
};
class map : public graphicObject
{
public:
	void display();

};