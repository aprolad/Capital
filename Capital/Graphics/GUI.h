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
	quadButton(double x, double y)
	{
		this->x = x;
		this->y = y;
		this->size = 0.2;
		poly = base;
	}
	double x, y;
	double size;
	graphicObject poly;
	void draw();
	void mouseCallback(double mx, double my)
	{
		//	if (mx > (x - 0.2) && mx < (x + 0.2) && my >(y - 0.2) && my < (y + 0.2))
		//		exit(1);
	}
};
class exitButton : public quadButton
{
public:
	exitButton(double x, double y)
	{
		this->x = x;
		this->y = y;
		this->size = 0.2;
		poly = base;
	}
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size) && mx < (x + size) && my >(-y - size) && my < (-y + size))
			exit(1);
	}

};
class startButton : public quadButton
{
public:
	startButton(double x, double y)
	{
		this->x = x;
		this->y = y;
		this->size = 0.2;
		poly = base;
	}
	void mouseCallback(double mx, double my);

};
class map : public graphicObject
{
public:
	void display();

};