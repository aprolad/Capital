#include "../game/economicsTab.h"

void econSubPanel::mouseInvoke(int mx, int my)
{
	int x = 100;
	int x2 = 500;
	
	if (mx > x && mx < x2 && my > y-25 && my < y+25)
	{
		*choosen = id;
		active = !active;
	}
}