#pragma once

struct GDP
{
	double farmingGDP;
	double total;
	double calcTotalGdp()
	{
		return farmingGDP;
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
			computeOneDay();
		}
		int date;
		double population;
		GDP GDP;
		double dependencyRate;
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{
			date += 1;

			population += population * 0.0001;

			GDP.total = population * dependencyRate;

		}
		void cycle()
		{
			if (go)
				computeOneDay();
		}
};