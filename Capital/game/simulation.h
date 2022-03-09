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



class population
{
public:
	double population;
	double laborPool;
	double dependencyRate;
	void calc()
	{
		laborPool = int(population * dependencyRate);
	}
};
class consumerGoods
{
public:
	consumerGoods()
	{
		price = 2;
	}
	double aggregateDemand;
	double naturalOutput;
	double price;
	void calc(population p)
	{
		aggregateDemand = p.population;
		price = price + (aggregateDemand - naturalOutput) * 0.000001;

		
	}
};
class exchange
{
public:

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
class agriculture : public industry
{
	public:
		consumerGoods wheat;
		agriculture()
		{
			totalArableLand = 1000;
		}
		void compute(population p)
		{
			double usedLand;
			if (workers < totalArableLand)
				usedLand = workers;
			else
				usedLand = totalArableLand;

			wheat.naturalOutput = usedLand * productivity;

			output = wheat.naturalOutput;

			wheat.calc(p);
		}
		double totalArableLand;
};
class simulation
{
	bool go;
	public:
		simulation()
		{
			population.population = 1000;
			date = 0;
			go = false;
			population.dependencyRate = 0.70;
			agriculture.productivity = 2;
			mining.productivity = 3;
			preference = 100;
			computeOneDay();
			
		}
		industry  mining;
		agriculture agriculture;
		population population;
		int date;
		GDP GDP;
		
		double preference;
		double foodSupply;
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{
			date += 1;
			double wht = agriculture.wheat.price;
			population.calc();

			agriculture.workers = population.laborPool * (preference / 100);
			mining.workers = population.laborPool * (1 - preference / 100);

			agriculture.compute(population);
			mining.compute();

			foodSupply = (agriculture.output - population.population)/ population.population * 100;

			if (foodSupply < 20 && preference < 100)
				preference += 0.1;
			else if (preference > 0 && foodSupply > 0)
				preference -= 0.1;
			population.population += population.population * 0.00002 * foodSupply;

			

			GDP.farmingGDP = agriculture.output * agriculture.wheat.price;
			GDP.miningGDP = mining.output * 1;
			GDP.calcTotalGdp();
		}
		void cycle()
		{
			if (go)
				computeOneDay();
		}
};