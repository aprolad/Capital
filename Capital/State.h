#pragma once

#include <random>
#include <ctime>
#include <vector>
#include <deque>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

#define CAP_UNIT_OF_MEASURE_NO 0 
#define CAP_UNIT_OF_MESURE_KG 1
#define CAP_UNIT_OF_MESURE_MONEY 2
#define CAP_UNIT_OF_MESURE_KM 3
#define CAP_UNIT_OF_MEASURE_SQ_KM 4

class Display_value
{
public:
	Display_value(int type, double value = 0)
	{

		this->type = type;
	}
	double value;
	std::string result;
	std::vector<std::string> unit_of_measure{ "","Kg", "Denarius", "Km", "Square km" };
	std::vector<std::string> exponent_string{ "","Thousands","Millions", "Billions", "Trillions", "Quadrillions" };

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
		stream << std::fixed << std::setprecision(3) << p;
		result = stream.str() + " " + exponent_string[exp] + " " + unit_of_measure[type];
		value = other;
		return *this;
	}
private:
	int type;
	std::string postfix;
};

class Goverment
{
public:
	Goverment() : d_money(CAP_UNIT_OF_MESURE_MONEY), wages(CAP_UNIT_OF_MESURE_MONEY)
	{}
	double workforce;
	double money;
	Display_value wages;
	Display_value d_money;
	void process()
	{
		d_money = money;
		pay_wages();
	}
	void pay_wages();
};

class Simulation_date
{
public:
	Simulation_date() {}
	Simulation_date(int sy)
	{
		starting_year = sy;
		days_from_start = 0;
	}
	int starting_year;
	int days_from_start;
	int years_from_start;
	int days_from_year_start;
	int calendar_years;
	enum months { Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
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
		current_month = days_from_year_start / 31;
	}
private:

};

struct GDP
{
	GDP() : total(Display_value(CAP_UNIT_OF_MESURE_MONEY))
	{
		history.resize(900);
	}

	Display_value total;
	double private_consumption;
	std::vector<double> history;
	double calcTotalGdp()
	{
		total = private_consumption;
		history.insert(history.begin(), total);
		history.pop_back();
		return total;
	}
};

class Geography
{
public:
	Geography() : square_kilometres(CAP_UNIT_OF_MESURE_KM), totalArableLand(CAP_UNIT_OF_MESURE_KM), pastoral_land(CAP_UNIT_OF_MEASURE_SQ_KM)
	{
		square_kilometres = 10000;
		pastoral_land = 2000;
		totalArableLand = square_kilometres * 0.05;
	}
	Display_value pastoral_land;
	Display_value square_kilometres;
	Display_value totalArableLand;

};
class Profession
{
public:
	Profession(std::string n, double percent_of_workforce, std::vector<float> c)
	{
		color = c;
		name = n;
		this->percent_of_workforce = percent_of_workforce;
	}

	std::string name;
	std::vector<float> color;
	double percent_of_workforce;
};
class Socium
{
public:
	Socium();
	Profession* by_name(std::string target)
	{
		auto it = std::find_if(worker_types.begin(), worker_types.end(),
			[=](const Profession& obj) { return obj.name == target; });
		if (it != worker_types.end())
			return &(*it);
		else
			return nullptr;
	}
	operator std::vector<double>() const
	{
		std::vector<double> t;
		for (auto a : worker_types)
			t.push_back(a.percent_of_workforce);
		return t;
	}
	std::vector<Profession> worker_types;
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
		for (int i = 0; i < 120; i++)
			agePyramid[i] = (10 + engine() % 1 - double(i) / 10) * 365;
	}
	std::mt19937 engine;
	Display_value money;
	double income;
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
		if (date % 365 == 0)
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
			if (i == 12)
				laborPool += agePyramid[12] * (double(date % 365) / 365);


			dependencyRate = 1 - laborPool / (population + 1);

			// Расчет рождаемости
			if (i > 16 && i < 45)
			{
				fertilePop += agePyramid[i];
			}
			//Расчет смертности

			if (i > 1 && i < 120)
			{
				double chanceToDie = (0.004 + (double(i) / 80) * (0.1)) / 365 * (2.3 - foodSupply / 200);
				if (i > 90)
					chanceToDie *= 2 * log(i - 90);
				agePyramid[i] -= chanceToDie * agePyramid[i] * (0.2 + engine() % 200 / 100);

			}

		}
		births = fertilePop * totalFertilityRate / 25 / 365 / 2 * double(0.98 + double(rand() % 40) / 1000) * (0.6 + foodSupply / 200);
		agePyramid[0] += int(births);
		fat = prevPop + births - population;

	}
};
class Product
{
public:
	Product()
	{}
	double aggregateDemand;
	double aggregateSupply;
	double reserves;
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
	void execute_part(double* sender_account, double budget)
	{
		if (price < 0.0001)
			price = 0.0001;
		double quantity_bought = budget / price;
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
		quantity *= 0.99;
		if (ttm == 0)
		{
			ttm = 20;
			price = cp * 1;
		}
		ttm -= 1;
	}
};
struct Purchase_check
{
	Purchase_check(double a, double m)
	{
		amount_bought = a;
		money_spent = m;
	}
	double amount_bought;
	double money_spent;
};

class Exchange
{
public:
	Exchange()
	{
		current_price = 10;
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
		{
			quantity_backlog += a.quantity;
		}

		return quantity_backlog;
	}
	void process()
	{
		if (total_supply < 1) total_supply = 1;
		if (total_demand < 1) total_demand = 1;


		if (calculate_excess() > total_demand * 155)
			current_price /= 1.0005;


		if (total_demand > total_supply)
			current_price *= 1 + (0.003 * (total_demand - total_supply) / total_demand);
		else
			current_price /= 1 + (0.003 * (total_supply - total_demand) / total_supply);



		for (auto a : order_book)
			a.process(current_price);


		if (current_price < 0.0001)
			current_price = 0.0001;

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
	Purchase_check buy_amount(double buy_amount, double* account)
	{
		// Cannot buy if there are no offers or no money
		if (order_book.empty() || *account < 1)
			return Purchase_check(0, 0);
		double money_spent = 0;
		double want_amount = buy_amount;
		total_demand += buy_amount;



		for (int i = 0; buy_amount > 0; i++)
		{
			if (buy_amount >= order_book[0].quantity)
			{
				if (order_book[0].quantity * order_book[0].price > *account)
				{
					double account_left = *account;
					order_book[0].execute_part(account, *account);
					buy_amount -= order_book[0].quantity;
					money_spent += account_left;
					return Purchase_check(want_amount - buy_amount, money_spent);
				}
				order_book[0].execute(account);
				buy_amount -= order_book[0].quantity;
				money_spent += order_book[0].quantity * order_book[0].price;
				order_book.erase(order_book.begin());
				if (order_book.empty())
				{
					return Purchase_check(want_amount - buy_amount, money_spent);
				}
			}
			else
			{
				order_book[0].execute(account, buy_amount);
				money_spent += buy_amount * order_book[0].price;
				buy_amount = 0;
			}
			//Small negative numbers represent operational debts 
			if (*account < 0)
				return Purchase_check(want_amount - buy_amount, money_spent);
		}
		return Purchase_check(want_amount - buy_amount, money_spent);
	}

	Purchase_check buy_money(double buy_money_, double* account)
	{
		if (order_book.empty() || *account < 1)
			return Purchase_check(0, 0);

		double buy_money = buy_money_;
		if (current_price < 0.001)
			current_price = 0.001;
		total_demand += buy_money_ / current_price;
		// Cannot buy if there are no offers

		double bought = 0;
		for (int i = 0; buy_money > 0; i++)
		{
			if (buy_money >= order_book[0].quantity * order_book[0].price)
			{

				order_book[0].execute(account);
				buy_money -= order_book[0].quantity * order_book[0].price;
				bought += order_book[0].quantity;

				order_book.erase(order_book.begin());
				if (order_book.empty())
				{
					return Purchase_check(bought, buy_money_ - buy_money);
				}
			}
			else
			{
				order_book[0].execute_part(account, buy_money);
				//total_demand += 
				bought += order_book[0].quantity;
				buy_money = 0;
			}
			//Small negative numbers represent operational debts 
			if (*account < 0)
				return Purchase_check(bought, buy_money_ - buy_money);
		}
		return Purchase_check(bought, buy_money_ - buy_money);
	}

	double get_current_price()
	{
		return current_price;
	}
};
class Industry
{
public:
	Industry() : output(CAP_UNIT_OF_MESURE_KG), wages(CAP_UNIT_OF_MESURE_MONEY), income(CAP_UNIT_OF_MESURE_MONEY), workforce(0) { historic_wages.resize(30); money = 100000; }
	double productivity;
	Display_value output;
	double workers;
	double gdp;
	Display_value income;
	double money, last_day_money;
	double last_day_balance;
	double workplace_count;
	Display_value workforce;
	Display_value wages;
	double prev_wage;
	double expenditure;
	std::deque<double> historic_wages;
	double consumer_coverage;
	void pay_wage();

	void compute()
	{
	}
};
class Agriculture : public Industry
{
public:

	Agriculture() {}
	void compute();
};
class Husbandry : public Industry
{
public:
	void compute();
};
class Textile : public Industry
{
public:
	void compute();
};
class Gathering : public Agriculture
{
public:
	void compute();
};
class Pottery : public Industry
{
public:
	void compute();
};

class State
{
public:
	State()
	{
		agriculture = Agriculture();
		pottery.wages = 10;
		demography.money = 1e7;
		socium = Socium();
	}
	Geography geography;
	Agriculture agriculture;
	Gathering gathering;
	Socium socium;
	Goverment goverment;
	Pottery pottery;
	Husbandry husbandry;
	Textile textile;
	GDP GDP;
	Exchange foodExc, woolExc;
	Exchange potteryExc, clothExc;
	Demography demography;
	void calculate_job_changes()
	{
		if (gathering.workforce < 1000)
			return;
		if (pottery.wages > gathering.wages * 1.8)
		{

			socium.by_name("Gatherers")->percent_of_workforce -= 0.0001 * (pottery.wages / gathering.wages);
			socium.by_name("Potters")->percent_of_workforce += 0.0001 * (pottery.wages / gathering.wages);
		}
		else if (socium.by_name("Potters")->percent_of_workforce > 0.0002)
		{
			socium.by_name("Gatherers")->percent_of_workforce += 0.0001;
			socium.by_name("Potters")->percent_of_workforce -= 0.0001;
		}

		if (textile.wages > gathering.wages * 1.8)
		{

			socium.by_name("Gatherers")->percent_of_workforce -= 0.0001 * (pottery.wages / gathering.wages);
			socium.by_name("Weavers")->percent_of_workforce += 0.0001 * (pottery.wages / gathering.wages);
		}
		else if (socium.by_name("Weavers")->percent_of_workforce > 0.0002)
		{
			socium.by_name("Gatherers")->percent_of_workforce += 0.0001;
			socium.by_name("Weavers")->percent_of_workforce -= 0.0001;
		}
		if (husbandry.wages > gathering.wages * 1.8)
		{

			socium.by_name("Gatherers")->percent_of_workforce -= 0.0001 * (pottery.wages / gathering.wages);
			socium.by_name("Shepards")->percent_of_workforce += 0.0001 * (pottery.wages / gathering.wages);
		}
		else if (socium.by_name("Shepards")->percent_of_workforce > 0.0001 && woolExc.total_demand < woolExc.total_supply)
		{
			socium.by_name("Gatherers")->percent_of_workforce += 0.0001;
			socium.by_name("Shepards")->percent_of_workforce -= 0.0001;
		}

	}
	void calculate_jobs()
	{
		pottery.workforce = socium.by_name("Potters")->percent_of_workforce * demography.laborPool;
		goverment.workforce = socium.by_name("Leaders")->percent_of_workforce * demography.laborPool;
		agriculture.workforce = socium.by_name("Farmers")->percent_of_workforce * demography.laborPool;
		gathering.workforce = socium.by_name("Gatherers")->percent_of_workforce * demography.laborPool;
		textile.workforce = socium.by_name("Weavers")->percent_of_workforce * demography.laborPool;
		husbandry.workforce = socium.by_name("Shepards")->percent_of_workforce * demography.laborPool;

		
	}
	void simulate(int date)
	{
		GDP.private_consumption = 0;

		demography.calc(date);

		calculate_jobs();

		foodExc.process();
		potteryExc.process();
		woolExc.process();
		clothExc.process();
		gathering.compute();
		agriculture.compute();
		pottery.compute();
		husbandry.compute();
		textile.compute();
		goverment.process();

		demography.density = demography.population / geography.square_kilometres;

		double before = demography.money;

		double realistic_demand = demography.population * 1.0 * (std::tanh(-(foodExc.current_price - 100) / 100) * 0.5 + 1);

		auto t = foodExc.buy_money(demography.money.value * 0.8, &demography.money.value);

		foodExc.total_demand = demography.population;

		demography.foodSupply = t.amount_bought / demography.population * 100;

		if (demography.money.value > 0)
			t = potteryExc.buy_money(demography.money.value * 0.5, &demography.money.value);
		//	potteryExc.total_demand = population.population / 5;

		clothExc.buy_money(demography.money.value, &demography.money.value);

		//	std::cout << "Remains  " << socium.by_name("Weavers")->percent_of_workforce << std::endl;
		GDP.private_consumption += abs(demography.money - before);

		GDP.calcTotalGdp();


		calculate_job_changes();
	}
};