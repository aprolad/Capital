#pragma once
#include <vector>

using namespace std;
class chart
{
public:
	chart()
	{
		data.resize(100);
	}
	vector<double> data;
	double sizing;
	void draw();

};
class ageChart 
{
public:
	ageChart()
	{
		data.resize(100);
	}
	vector<double> data;
	double sizing;
	void draw();
};