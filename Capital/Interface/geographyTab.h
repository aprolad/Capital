#pragma once

extern int choosenTab;

class geographyTab
{
public:
	bool active;
	void (*reset)();
	void mouseInvoke(int mx, int my);
	void draw();
};