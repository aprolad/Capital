#pragma once
#include <random>
#include <ctime>
#include <vector>
#include <deque>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;
class Display_value
{
public:
	Display_value(double value, int type)
	{
		this->value = value;
		this->type = type;
	}
	double value;
	std::string result;
	std::vector<std::string> unit_of_measure{ "","Kg", "Denarius", "Km" };
	std::vector<std::string> exponent_string{ "","Thousands","Millions", "Billions", "Trillions", "Quadrillions"};

	operator double() const
	{
		return value;
	}

	// Unary operators
	Display_value operator+() const
	{
		return *this;
	}

	Display_value operator-() const
	{
		return Display_value(type, -static_cast<const double&>(this->value));
	}
	Display_value& operator=(const Display_value& other)
	{
		value = other.value;
		return *this;
	}
	Display_value& operator=(const double& other)
	{
		int exp = 0;
		double p = other;
		while (int(log10(p)) > 2 and p != 0)
		{
			exp++;
			p /= 1e3;
		}
		std::stringstream stream;
		stream << std::fixed << std::setprecision(3)<<p;
		result = stream.str() + " " + exponent_string[exp] + " " + unit_of_measure[type];
		value = other;
		return *this;
	}
private:
	int type;
	std::string postfix;
};
struct GDP
{
	GDP() : total(Display_value(0,2))
	{
		history.resize(900);
	}

	Display_value total;
	double private_consumption;
	vector<double> history;
	double calcTotalGdp()
	{	
		total = private_consumption;
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
class Profession
{
public:

};
class Socium
{
public:
};
class Demography
{
public:
	Demography() : money(Display_value(0, 2))
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
	Display_value money;
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
				double chanceToDie = (0.004 + (double(i)/80) * (0.1))/ 365 * (2.3 - foodSupply/200);
				if (i > 90)
					chanceToDie *= 2 * log(i-90);
				agePyramid[i]-= chanceToDie * agePyramid[i] * (0.2+engine()%200/100);

			}

		}
		births = fertilePop * totalFertilityRate / 25/ 365 / 2 * double(0.98 + double(rand() % 40) / 1000) * (0.6 + foodSupply/200);
		agePyramid[0] += int(births);
		fat = prevPop + births - population;
		
	}
};
class Product
{
public:
	Product()
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
class Order
{
public:
	Order(double q, double p, double* ra) : quantity{ q }, price{ p }, recepient_account{ ra }
	{
		ttm = 30;
	}
	void execute(double* sender_account)
	{
		*sender_account -= quantity * price;
		*recepient_account += quantity * price;
	}
	void execute(double* sender_account, double quantity_bought)
	{
		*sender_account -= quantity_bought * price;
		*recepient_account += quantity_bought * price;
		quantity -= quantity_bought;
	}
	double ttm;
	double quantity, price;
	double* recepient_account;
	static bool compareByPrice(const Order& a, const Order& b) {
		return a.price < b.price;
	}
	void process(double cp)
	{
		if (ttm == 0)
		{
			ttm = 150;
			price = cp;
		}
			ttm -= 1;
	}
};
struct Purchase_check
{

};
class Exchange
{
public:
	Exchange()
	{
		current_price = 100;
	}
	std::deque<Order> order_book;
	double current_price;
	double total_demand;
	double total_supply;
	double quantity_backlog;
	double calculate_excess()
	{
		quantity_backlog = 0;
		for (auto a : order_book)
			quantity_backlog += a.quantity;
		return quantity_backlog;
	}
	void process()
	{
		if (calculate_excess() > total_demand * 14)
			current_price /= 1.01;
		if (total_demand > total_supply)
			current_price *= 1.001;
		else
			current_price /= 1.001;
		for (auto a : order_book)
			a.process(current_price);

		total_demand = 0;
		total_supply = 0;
	}
	void put_sell_order(double quantity, double price, double* recepient_account)
	{
		total_supply += quantity;
		auto a = Order(quantity, price, recepient_account);
		std::sort(order_book.begin(), order_book.end(), Order::compareByPrice);

		auto insertPosition = std::lower_bound(order_book.begin(), order_book.end(), a, Order::compareByPrice);

		// Insert the new element at the appropriate position
		order_book.insert(insertPosition, a);

	}
	double buy_amount(double buy_amount, double* account)
	{
		total_demand += buy_amount;
		// Cannot buy if there are no offers
		if (order_book.empty())
			return buy_amount;

		for (int i = 0; buy_amount > 0; i++)
		{
			if (buy_amount >= order_book[0].quantity)
			{
				order_book[0].execute(account);
				buy_amount -= order_book[0].quantity;
				order_book.erase(order_book.begin());
				if (order_book.empty())
				{
					return buy_amount;
				}
			}
			else
			{
				order_book[0].execute(account, buy_amount);
				buy_amount = 0;
			}
			 //Small negative numbers represent operational debts 
			if (*account < 0)
				return buy_amount;
		}
		return 0;
	}
	double get_current_price()
	{
		//if (!order_book.empty())
		//	current_price = order_book.front().price;
		return current_price;
	}
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
		double income;
		double money;
		Product* wheat;
		double price;
		double kgs;
		double t;
		double last_day_balance;
		double workplace_count;
		double workforce;
		Display_value outputT;
		Agriculture() : outputT(0, 1)
		{
			wheat = new Product();
			price = 0.1;
		}
		void compute();
};
class Gathering : public Agriculture
{
public:
	void compute();
	Product foraged_food;
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

			population.money = 1e15;

		}
		static int game_speed;
		Simulation_date date;
		Geography geo;
		Agriculture* agriculture;
		Gathering gathering;
		Demography population;
		Goverment goverment;
		GDP GDP;
		Exchange exc;
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
			GDP.private_consumption = 0;
			date.calculate_date();
			population.calc(date.days_from_start);

			calculate_jobs();
			exc.process();
			gathering.compute();
			agriculture->compute();
			//mining.compute();


			population.foodSupply = agriculture->wheat->consumerCoverage * 100;
			
			population.density = population.population / geo.sqKilometres;

			double before = population.money;
			double beforeA = agriculture->money;
			double beforeB = gathering.money;
			double realistic_demand = population.population * 2 * (std::tanh(-(exc.current_price - 100)/100) * 0.5 + 1);
			//std::cout << "Current demand: " << realistic_demand << std::endl;
			//std::cout << "Possible demand: " << (population.population * 2) << std::endl;
			//std::cout << "Supply: " << exc.total_supply << std::endl;
			agriculture->wheat->consumerCoverage = realistic_demand / (population.population * 2);
			double malnutrition = exc.buy_amount(realistic_demand, &population.money.value);


			double specific_malnutrition = malnutrition/population.population;
			//std::cout << "FAMINE: " << exc.order_book.size() << std::endl;
			GDP.private_consumption += abs(population.money - before);
			agriculture->income = agriculture->money - beforeA;
			gathering.income = gathering.money - beforeB;



			GDP.calcTotalGdp();
		}
		void cycle()
		{
			if (go)
				for (int i=0; i<game_speed;i++)
					computeOneDay();
		}
};
