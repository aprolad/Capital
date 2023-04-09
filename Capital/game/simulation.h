#pragma once
#include <random>
#include <ctime>
#include <vector>
#include <deque>
#include <iostream>
#include <cmath>
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

class Simulation;

class Geography
{
public:
	Geography()
	{
		sqKilometres = 10000;
		totalArableLand = sqKilometres * 0.01;
	}
	double sqKilometres;
	double totalArableLand;

};

class demography
{
public:
	demography()
	{
		srand(time(0));
		
		engine.seed(std::time(0));
		agePyramid.resize(120);
		population = 1000;
		totalFertilityRate = 5;
		for (int i = 0; i < 120; i++)
		{
			agePyramid[i] = 0;
		}
		for (int i=0; i<120; i++)
		agePyramid[i] = (10 + engine()%1 - double(i)/10) * 365;
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
	
	void calc(int date)
	{

		double fertilePop = 0;
		fat = 0;
		births = 0;
		double prevPop = population;
		population = 0;
		laborPool = 0;
		if (date%365 ==0)
		for (int i = 0; i < 1; i++)
		{
			agePyramid.push_front(0);
			agePyramid.pop_back();
		}
		for (int i = 0; i < 120; i++)
		{
			if (agePyramid[i] < 0)
				agePyramid[i] = 0;
			population += agePyramid[i];

			//Расчет работоспособного населения
			if (i > 12 && i < 65)
				laborPool += agePyramid[i];

			dependencyRate = 1 - laborPool / (population + 1);

			// Расчет рождаемости
			if (i > 16 && i < 45)
			{
				fertilePop += agePyramid[i];
			}
			//Расчет смертности

			if (i > 1 && i < 120)
			{
				double chanceToDie = (0.004 + (double(i)/80) * (0.1))/ 365 * (2.8 - foodSupply/100);
				if (i > 90)
					chanceToDie *= 2 * log(i-90);
				agePyramid[i]-= chanceToDie * agePyramid[i] * (0.2+engine()%200/100);

			}

		}
		births = fertilePop * totalFertilityRate / 25/ 365 / 2 * double(0.98 + double(rand() % 40) / 1000) * (0.1 + foodSupply/100);
		agePyramid[0] += int(births);
		fat = prevPop + births - population;
		
	}
};
class product
{
public:
	product()
	{

		price = 0.1;
	}
	double aggregateDemand;
	double aggregateSupply;
	double reserves;
	double price;
	double consumerCoverage;
	void calc();
};
class Market
{
public:
	std::vector<product> products;

};
class Industry
{
public:
	Geography* geo;
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
class Agriculture : public Industry
{
	public:
		product* wheat;
		double price;
		double kgs;
		double t;
		double outputT;
		double workplace_count;
		double workforce;
		Agriculture()
		{
			wheat = new product();
			price = 0.1;
		}
		void compute();
};
class Gathering : public Agriculture
{
public:
	void compute();
	product foraged_food;
};
class Simulation_date
{
	public:
		Simulation_date(){}
		Simulation_date(int sy)
		{
			starting_year = sy;
			days_from_start =0;
		}
	int starting_year;
	int days_from_start;
	int years_from_start;
	int days_from_year_start;
	int calendar_years;
	enum months {Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec};
	int current_month;
	std::string postfix;
	void calculate_date()
	{
		days_from_start++;
		years_from_start = days_from_start / 365;
		days_from_year_start = days_from_start % 365;
		if (starting_year < 0 && years_from_start < abs(starting_year))
		{
			calendar_years = abs(starting_year + years_from_start);
			postfix = "BC";
		}
		else
		{
			calendar_years = starting_year + years_from_start;
			postfix = "AD";
		}
		current_month = days_from_year_start/31;
	}
private:

};
class Goverment
{
public:
	double workforce;
};
class Simulation
{
	bool go;
	public:
		Simulation()
		{
			date = *new Simulation_date(-4000);
			go = false;
			population.dependencyRate = 0.70;
			
			preference = 80;
			agriculture = new Agriculture();
			computeOneDay();
			game_speed = 1;

		}
		static int game_speed;
		Simulation_date date;
		Geography geo;
		//industry  mining;
		Agriculture* agriculture;
		Gathering gathering;
		demography population;
		Goverment goverment;
		GDP GDP;
		
		double preference;
		void calculate_jobs()
		{
			double free_workforce = population.laborPool;
			goverment.workforce = population.population / 30;
			free_workforce -= goverment.workforce;
			if (free_workforce > agriculture->workplace_count)
			{
				agriculture->workforce = agriculture->workplace_count;
				free_workforce -= agriculture->workplace_count;
			}
			else
			{
				agriculture->workforce = free_workforce;
				free_workforce = 0;
			}

			gathering.workforce = free_workforce;
		}
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{
			date.calculate_date();
			population.calc(date.days_from_start);

			calculate_jobs();

			gathering.compute();
			agriculture->compute();
			//mining.compute();

			population.foodSupply = agriculture->wheat->consumerCoverage * 100;
			
			population.density = population.population / geo.sqKilometres;
			GDP.total = 0;
			//GDP.total += mining.gdp;
			GDP.total += agriculture->gdp;
			GDP.total += gathering.output * 0.1;
			GDP.calcTotalGdp();
		}
		void cycle()
		{
			if (go)
				for (int i=0; i<game_speed;i++)
					computeOneDay();
		}
};
