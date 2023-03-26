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

	double total;
	vector<double> history;
	double calcTotalGdp()
	{	

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
		srand(time(0));
		
		engine.seed(std::time(0));
		agePyramid.resize(100000);
		population = 1000;
		totalFertilityRate = 2;
		for (int i = 0; i < 100000; i++)
		{
			agePyramid[i] = 0;
		}
		for (int i=0; i<20000; i++)
		agePyramid[i] = 50 + engine()%10;
	}
	std::mt19937 engine;
	double density;
	double birthRate;
	double population;
	double laborPool;
	double dependencyRate;
	double totalFertilityRate;
	double fat;
	double births;
	double infantMortality;

	double foodSupply;

	std::deque<double> agePyramid;
	
	void calc()
	{

		double fertilePop = 0;
		fat = 0;
		births = 0;
		double prevPop = population;
		population = 0;
		laborPool = 0;
		agePyramid.push_front(0);
		agePyramid.pop_back();
		for (int i = 0; i < 100000; i++)
		{
			if (agePyramid[i] < 0)
				agePyramid[i] = 0;
			population += agePyramid[i];

			//Расчет работоспособного населения
			if (i > 5110 && i < 23725)
				laborPool += agePyramid[i];

			dependencyRate = 1 - laborPool / (population + 1);

			// Расчет рождаемости
			if (i > 5475 && i < 16425)
			{
				fertilePop += agePyramid[i];
			}
			//Расчет смертности

			if (i > 1 && i < 90000)
			{
				double chanceToDie = abs(i * 0.000000004 * (1 - foodSupply / 100) + i/(20000) * 0.0001 + i / (12000) * 0.00005) + i / (30000) * 0.001;
				
				agePyramid[i]-= chanceToDie * agePyramid[i] * (0.2+engine()%200/100);

			}

		}
		births = fertilePop * totalFertilityRate / 25 / 2 / 365 * double(0.8 + double(rand() % 400) / 1000) * (1 + foodSupply/100);
		agePyramid[0] = int(births);
		fat = prevPop + births - population;
		
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
	double gdp;
	void compute()
	{
		output = workers * productivity;
		gdp = output;
	}
};
class agriculture : public industry
{
	public:
		consumerGoods wheat;
		double price;
		agriculture()
		{
			price = 2;
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

			gdp = output * price;
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
			preference = 80;
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
			
			population.density = population.population / geo.sqKilometres;
			
			GDP.calcTotalGdp();
		}
		void cycle()
		{
			if (go)
				computeOneDay();
		}
};