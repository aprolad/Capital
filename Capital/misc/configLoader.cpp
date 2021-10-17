#include <fstream>
#include <iostream>
#include "configLoader.h"
void loadConfig(int &x, int &y)
{
	std::ifstream input("config.txt");
	if (!input.is_open())
	{
		std::cout << "Failed to open config";
		exit(1);
	}
	input >> x >> y;
}