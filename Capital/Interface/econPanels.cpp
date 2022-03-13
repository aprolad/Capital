#include "../game/EconPanels.h"

void econSubPanel::mouseInvoke(int mx, int my)
{
	int x = 100;
	int x2 = 500;
	int y = 185;
	int y2 = 235;
	if (mx > x && mx < x2 && my > y && my < y2)
	{
		active = !active;
	}
}