#pragma once
#include <vector>

using namespace std;
class chart
{
public:
	chart(int len)
	{
		data.resize(len);
		sizing = len;
	}
	vector<double> data;
	int sizing;
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