#pragma once
#include <random>
#include <vector>
#include <iomanip>
#include <math.h>
#include "../Graphics/CAP_graphics.h"
struct src
{
	src(int ax, int ay)
	{
		x = ax;
		y = ay;
	}
	int x, y;
	int dist;
	double distance(int ax, int ay)
	{
		dist = sqrt(pow((ax - x), 2) + pow((ay - y), 2));
		return dist;
	}
};
class playground
{
	struct tile
	{
		tile()
		{
			gr = baseGT;
			fert = 0;
		}
		graphicTiles gr;
		double fert;
	};
	
	std::vector<src> conc;
	public:
		tile soil[50][50];
		void generate()
		{
			srand(time(0));
		
			soil[0][0].gr = baseGT;
			for (int y = 0; y < 50; y++)
			{
				for (int x = 0; x < 50; x++)
				{
					if ((rand() % 250) == 50)
					{
						conc.push_back(src(x,y));
						soil[x][y].fert = 1;
					}
				}
				std::cout<< std::endl;
			}
		}
		void draw();
};