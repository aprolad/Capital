#pragma once

extern int choosenTab;
#include "../Interface/tab.h"

class geographyTab : virtual public tab
{
public:
	geographyTab()
	{
		x = 1760;
		y = 100;
	}
	void draw();
};