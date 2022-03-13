#pragma once
#include <vector>
#include <deque>
using namespace std;
class chart
{
public:
	chart(int len)
	{
		data.resize(len);
		maxHistory.resize(1000);
		sizing = len;
	}
	vector<double> data;
	deque <double> maxHistory;
	int sizing;
	void draw();

};
class ageChart 
{
public:
	ageChart()
	{
		data.resize(1600);
		maxHistory.resize(1000);
	}
	vector<double> data;
	double sizing;
	deque <double> maxHistory;
	void draw();
};