#pragma once
#include <random>
#include <ctime>
#include <vector>
#include <deque>
using namespace std;
struct GDP
{
	GDP()
	{
		history.resize(900);
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


class geography
{
public:
	geography()
	{
		sqKilometres = 10000;
	}
	double sqKilometres;
	double totalArableLand = 400000;

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
		for (int i=0000; i<10000; i++)
		agePyramid[i] = 50;
	}
	double density;
	double birthRate;
	int population;
	double laborPool;
	double dependencyRate;
	double totalFertilityRate;
	double fat;
	double births;
	double infantMortality;

	double foodSupply;

	std::deque<int> agePyramid;
	
	void calc()
	{
		std::mt19937 engine;
		engine.seed(std::time(nullptr));

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
				double probability = 1/(10950/totalFertilityRate * 2);
				int chance = engine() % int(1 / probability);// Шанс родить в этот день одной женщине
				if (chance < agePyramid[i]) // Количество шансов = количество женщин
				{
					agePyramid[0]++;
					births++;
				}
			}

			//Расчет смертности

			if (i > 6000 && i < 90000)
			{
				double chanceToDie = 0.00001 * i/800 + (i/30000 * i/30000 * 0.01) + 0.000000000001 - foodSupply*0.000001;
				if (chanceToDie > 1)
					chanceToDie = 1;
				if (chanceToDie < 0)
					chanceToDie = 0;
				int chance = engine() % int(1/chanceToDie); // Шанс умереть в этот день одному человеку
				if (chance < agePyramid[i]) // Количество шансов = количество людей
				{
					agePyramid[i]--;
					fat++;
				}
			}

			if (i < 3000)
			{
	
				double chanceToDie = 0.00001 + 0.000000000001 - foodSupply * 0.0001;

				if (chanceToDie > 1) chanceToDie = 1;
				if (chanceToDie < 0) chanceToDie = 0;

				int chance = engine() % int(1 / chanceToDie); // Шанс умереть в этот день одному челове
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
	void calc(demography* p)
	{
		aggregateDemand = p->population - ((price - 2) * (p->population) / 100);
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
	geography* geo;
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
			productivity = 1.65;
		}
		void compute(demography* p)
		{
			double usedLand;
			if (workers < geo->totalArableLand)
				usedLand = workers;
			else
				usedLand = geo->totalArableLand;

			wheat.naturalOutput = usedLand * productivity;

			output = wheat.naturalOutput;

			wheat.calc(p);
		}
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
			agriculture.geo = &geo;
			date = 0;
			go = false;
			population.dependencyRate = 0.70;
			mining.productivity = 5;
			preference = 100;
			computeOneDay();
			
		}
		geography geo;
		industry  mining;
		agriculture agriculture;
		forestry forestry;
		hunting hunting;
		fishing fishing;
		demography population;
		
		int date;
		GDP GDP;
		
		double preference;
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

			agriculture.compute(&population);
			mining.compute();

			population.foodSupply = (agriculture.output - population.population * 0.85)/ population.population * 100;

			if (population.foodSupply < 20 && preference < 100 && agriculture.workers < geo.totalArableLand)
				preference += 0.01;
			else if (preference > 0 && population.foodSupply > 0 || agriculture.workers > geo.totalArableLand)
				preference -= 0.01;
			

			
			population.density = population.population / geo.sqKilometres;
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