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
