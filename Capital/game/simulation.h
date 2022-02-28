#pragma once

struct GDP
{
	double farmingGDP;
	double miningGDP;
	double total;
	double calcTotalGdp()
	{
		total = farmingGDP + miningGDP;
		return total;
	}
};

class industry
{
public:
	double productivity;
	double output;
	double workers;
	void compute()
	{
		output = workers * productivity;
	}
};
class simulation
{
	bool go;
	public:
		simulation()
		{
			population = 1000;
			date = 0;
			go = false;
			dependencyRate = 0.70;
			agriculture.productivity = 2;
			mining.productivity = 3;
			preference = 100;
			computeOneDay();
			
		}
		industry agriculture, mining;
		int date;
		double population;
		double laborPool;
		GDP GDP;
		double dependencyRate;
		double preference;
		double foodSupply;
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{
			date += 1;
			laborPool = int(population * dependencyRate);

			agriculture.workers = laborPool * (preference / 100);
			mining.workers = laborPool * (1 - preference / 100);

			agriculture.compute();
			mining.compute();

			foodSupply = (agriculture.output - population)/population * 100;

			if (foodSupply < 10 && preference < 100)
				preference += 1;
			if (foodSupply > 20 && preference > 0)
				preference -= 1;

			population += population * 0.00002 * foodSupply;

			

			GDP.farmingGDP = agriculture.output * 1;
			GDP.miningGDP = mining.output * 1;
			GDP.calcTotalGdp();
		}
		void cycle()
		{
			if (go)
				computeOneDay();
		}
};