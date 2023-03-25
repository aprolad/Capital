
#include "../Interface/tab.h"


extern int choosenTab;

class technologyTab : virtual public tab
{
public:
	technologyTab()
	{
		x = 760;
		y = 980;
	}
	void draw();
};