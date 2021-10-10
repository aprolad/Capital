#pragma once
#include "Header.h"
class scene
{
public:
	std::vector<button*> bn;
	void draw()
	{
		for (int i = 0; i < bn.size(); i++)
			bn[i]->draw();
	}
};
