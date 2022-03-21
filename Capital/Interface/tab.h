#pragma once
class tab
{
public:
	tab()
	{
		active = false;
	}

	bool active;
	int resx; int resy;
	double x, y;
	void (*reset)();

	virtual void draw() {};
	virtual void mouseInvoke(int mx, int my)
	{
		if (mx > x - 100 && mx < x + 100 && my > y - 100 && my < y + 100)
		{
			bool actTemp = active;
			reset();
			if (actTemp == false)
				active = true;
		}
	}

	void drawBase();
	
};