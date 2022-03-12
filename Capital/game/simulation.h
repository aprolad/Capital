#pragma once
#include <random>
#include <vector>
#include <deque>
using namespace std;
struct GDP
{
	GDP()
	{
		history.resize(100);
	}
	double farmingGDP;
	double miningGDP;
	double total;
	vector<double> history;
	double calcTotalGdp()
	{
		
		total = farmingGDP + miningGDP;

		history.insert(history.begin(), total);
		history.pop_back();
		return total;
	}
};



class demography
{
public:
	demography()
	{
		agePyramid.resize(100000);
		population = 1000;
		totalFertilityRate = 8;
		for (int i = 0; i < 100000; i++)
		{
			agePyramid[i] = 0;
		}
		for (int i=0; i<3000; i++)
		agePyramid[6000 + i] = 10;
	}
	double birthRate;
	int population;
	double laborPool;
	double dependencyRate;
	double totalFertilityRate;
	double fat;
	double births;
	double infantMortality;
	std::deque<int> agePyramid;
	
	void calc()
	{
		srand(time(0));
		fat = 0;
		births = 0;
		population = 0;
		laborPool = 0;
		agePyramid.push_front(0);
		agePyramid.pop_back();
		for (int i = 0; i < 100000; i++)
		{
			population += agePyramid[i];

			//Расчет работоспособного населения
			if (i > 5110 && i < 23725)
				laborPool += agePyramid[i];

			dependencyRate = 1 - laborPool / (population + 1);

			// Расчет рождаемости
			if (i > 5475 && i < 16425)
			{
				int chance = rand() % int(10950 / 8 * 2);// Шанс родить в этот день одной женщине
				if (chance < agePyramid[i]) // Количество шансов = количество женщин
				{
					agePyramid[0]++;
					births++;
				}
			}

			//Расчет смертности

			if (i > 6000 && i <30000)
			{
				int chance = rand() % int(6000 - i/10000 * 5999); // Шанс умереть в этот день одному человеку
				if (chance < agePyramid[i]) // Количество шансов = количество людей
				{
					agePyramid[i]--;
					fat++;
				}
			}

		}
		
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
	void calc(demography p)
	{
		aggregateDemand = p.population - ((price - 2) * (p.population) / 100);
		//price = price + (aggregateDemand - naturalOutput) * 0.000001;

		
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
			totalArableLand = 100000;
		}
		void compute(demography p)
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
class forestry : public industry
{
public:

};
class fishing : public industry
{

};
class hunting : public industry
{

};
class simulation
{
	bool go;
	public:
		simulation()
		{
			date = 0;
			go = false;
			population.dependencyRate = 0.70;
			agriculture.productivity = 2;
			mining.productivity = 5;
			preference = 100;
			computeOneDay();
			
		}
		industry  mining;
		agriculture agriculture;
		forestry forestry;
		hunting hunting;
		fishing fishing;
		demography population;
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
			population.calc();

			agriculture.workers = int(population.laborPool * (preference / 100));
			mining.workers = int(population.laborPool * (1 - preference / 100));

			agriculture.compute(population);
			mining.compute();

			foodSupply = (agriculture.output - population.population)/ population.population * 100;

			if (foodSupply < 20 && preference < 100 && agriculture.workers < agriculture.totalArableLand)
				preference += 0.01;
			else if (preference > 0 && foodSupply > 0)
				preference -= 0.01;
			

			

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