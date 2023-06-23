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
#include "World.h"

#define CAP_UNIT_OF_MEASURE_NO 0 
#define CAP_UNIT_OF_MESURE_KG 1
#define CAP_UNIT_OF_MESURE_MONEY 2
#define CAP_UNIT_OF_MESURE_KM 3
#define CAP_UNIT_OF_MEASURE_SQ_KM 4
class Simulation;
enum industry_index {
    farming,
    gathering,
    pottery,
    husbandry,
	textile,
	forestry,
	construction,
	goverment,
	unemployed
};


enum exchange_index {
	food_exc,
	wool_exc,
	pottery_exc,
	cloth_exc,
	wood_exc,
	constr_exc
  
};
class State;

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
	double wage;
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
		consumption_level = 1;
	}
	std::mt19937 engine;
	Display_value money;
	double consumption_level;
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
	double delta_workers;
	double foodSupply;

	std::deque<double> agePyramid;

	void calc(int date)
	{

		double fertilePop = 0;
		fat = 0;
		births = 0;
		double prevPop = population;
		population = 0;
		double prev_workers = laborPool;
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
		delta_workers = laborPool - prev_workers;

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
	double execute_part(double* sender_account, double budget)
	{
		if (price < 0.0001)
			price = 0.0001;
		double quantity_bought = budget / price;
		*sender_account -= quantity_bought * price;
		*recepient_account += quantity_bought * price;
		quantity -= quantity_bought;
		return quantity_bought;
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
	double sold_quantity;
	double total_demand;
	double total_supply;
	Display_value sold_quantity_d{ 0 }, total_demand_d{ 0 }, total_supply_d{ 0 }, quantity_backlog_d{ 0 };
	Display_value current_price_d{2};
	double quantity_backlog;
	double money_spent;
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

		sold_quantity_d = sold_quantity;
		total_demand_d = total_demand;
		total_supply_d = total_supply;
		quantity_backlog_d = quantity_backlog;
		current_price_d = current_price;

		if (calculate_excess() > total_demand * 155)
			current_price /= 1.0005;

		//std::cout <<"sold " << sold_quantity <<"ratio "<<sold_quantity/total_supply<< std::endl;
		if (total_demand > total_supply && ((sold_quantity / total_supply) > 0.8))
		{
		//	std::cout <<"price up "<< std::endl;
			current_price *= 1 + (0.003 * (total_demand - total_supply) / total_demand);
		}
		else if (total_demand < total_supply)
			current_price /= 1 + (0.003 * (total_supply - total_demand) / total_supply);



		//if (order_book.size() > 0)
		//	consolidate();
	//	for (auto &a : order_book)
		//	a.process(current_price);


		if (current_price < 0.00001)
			current_price = 0.00001;
		sold_quantity = 0;
		total_demand = 0;
		total_supply = 0;
	}
	void put_sell_order(double quantity, double price, double* recepient_account)
	{
		total_supply += quantity;
		auto a = Order(quantity, price, recepient_account);
		if (order_book.size() > 150)
			order_book.erase(order_book.end()-1);

		std::sort(order_book.begin(), order_book.end(), Order::compareByPrice);

		auto insertPosition = std::lower_bound(order_book.begin(), order_book.end(), a, Order::compareByPrice);

		// Insert the new element at the appropriate position
		order_book.insert(insertPosition, a);

	}
	Purchase_check buy_amount(double buy_amount, double* account)
	{
		// Cannot buy if there are no offers or no money

		money_spent = 0;
		double want_amount = buy_amount;
		total_demand += buy_amount;
		if (order_book.empty() || *account < 1)
			return Purchase_check(0, 0);


		for (int i = 0; buy_amount > 0; i++)
		{
			if (buy_amount >= order_book[0].quantity)
			{
				if (order_book[0].quantity * order_book[0].price > *account)
				{
					double account_left = *account;
					
					buy_amount -= order_book[0].execute_part(account, *account);
					money_spent += account_left;
					sold_quantity += want_amount - buy_amount;
					return Purchase_check(want_amount - buy_amount, money_spent);
				}
				else
				{
					order_book[0].execute(account);
					buy_amount -= order_book[0].quantity;
					money_spent += order_book[0].quantity * order_book[0].price;
					order_book.erase(order_book.begin());
					if (order_book.empty())
					{
						sold_quantity += want_amount - buy_amount;
						return Purchase_check(want_amount - buy_amount, money_spent);
					}
				}
				
			}
			else
			{
				if (buy_amount * order_book[0].price < *account)
				{
					order_book[0].execute(account, buy_amount);
					money_spent += buy_amount * order_book[0].price;
					buy_amount = 0;
				}
				else
				{
					double account_left = *account;
					buy_amount -= order_book[0].execute_part(account, *account);
					money_spent += account_left;
					sold_quantity += want_amount - buy_amount;
					return Purchase_check(want_amount - buy_amount, money_spent);
				}
			}
			
		}
		sold_quantity += want_amount - buy_amount;
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
					sold_quantity += bought;
					return Purchase_check(bought, buy_money_ - buy_money);
				}
			}
			else
			{
				bought += order_book[0].execute_part(account, buy_money);
				buy_money = 0;
				sold_quantity += bought;
				return Purchase_check(bought, buy_money_ - buy_money);
			}
	
		}

	}

	double get_current_price()
	{
		return current_price;
	}
};
class Industry
{
public:
	Industry(State* _state) :  wages(CAP_UNIT_OF_MESURE_MONEY), income(CAP_UNIT_OF_MESURE_MONEY), workforce_d(0)
	{ 
		state = _state;
		wages = 10;
		money = 100000;
		investment_account = 0;
	}
	double productivity;
	Display_value output{ CAP_UNIT_OF_MESURE_KG };
	double vacancies;
	double gdp;
	Display_value income;
	double money, last_day_money;
	double last_day_balance;
	double workplace_count;
	double workforce;
	Display_value workforce_d;
	Display_value wages;
	double prev_wage;
	double expenditure;
	double revenue, gross_profit, profit_after_investment, operating_profit;
	Display_value revenue_d{ 2 }, gross_profit_d{ 2 }, profit_after_investment_d{ 2 }, operating_profit_d{2};
	Display_value investment_account_d{ 2 };
	double payroll;
	double investment_account;
	double consumer_coverage;
	State* state;
	void pay_wage();
	void invest();
	void process();
	virtual void compute() = 0;
	void transfer_money(double* destination, double amount)
	{
		money -= amount;
		(*destination) += amount;
	}
	void transfer_money(double* source, double* destination, double amount)
	{
		(*source) -= amount;
		(*destination) += amount;
	}
	static bool compare_by_wage_descending(const Industry* a, const Industry* b) {
		return a->wages.value > b->wages.value;
	}
};

class Unemployed : public Industry
{
public:
	using Industry::Industry;
	void compute()
	{
	
	}
};

class Goverment : public Industry
{
public:
	using Industry::Industry;
	void compute();
};

class Farming : public Industry
{
public:
	using Industry::Industry;
	void compute();
};
class Husbandry : public Industry
{
public:
	using Industry::Industry;
	void compute();
};
class Textile : public Industry
{
public:
	using Industry::Industry;
	void compute();
};
class Construction : public Industry
{
public:
	using Industry::Industry;
	void compute();
};
class Forestry : public Industry
{
public:
	using Industry::Industry;
	void compute();
};
class Gathering : public Industry
{
public:
	using Industry::Industry;
	void compute();
};
class Pottery : public Industry
{
public:
	using Industry::Industry;
	void compute();
};

class State
{
public:
	State(Simulation* sim, double);
	Simulation* simulation;
	Geography geography;
	Socium socium;
	std::vector<tile*> controlled_tiles;
	GDP GDP;

	std::vector<Industry*> industries;
	std::vector<Exchange*> exchanges;
	Demography demography;

	void distrubute_worker_loss()
	{
		for (int c = 0; c < industries.size(); c++)
			industries[c]->workforce += socium.worker_types[c].percent_of_workforce * demography.delta_workers;
	}
	void calculate_jobs()
	{
		// Worker delta distribution
		if (demography.delta_workers < 0)
			distrubute_worker_loss();
		else
			industries[unemployed]->workforce += abs(demography.delta_workers);
		// Staff turnover
		for (int c = 0; c < industries.size()-2; c++)
		{
			double change = industries[c]->workforce * 0.0001;
			industries[unemployed]->workforce += change;
			industries[c]->workforce -= change;
		}

		// Separate industries with changing employment in separate vecrot to avoid breaking enum order 
		std::vector<Industry*> i_sort;
		i_sort.assign(industries.begin(), industries.end() - 2);
		std::sort(i_sort.begin(), i_sort.end(), Industry::compare_by_wage_descending);

		// Hiring workers
		for (int c = 0; c < i_sort.size(); c++)
		{
			if (i_sort[c]->vacancies > 0)
				if (i_sort[c]->vacancies > industries[unemployed]->workforce)
				{
					i_sort[c]->vacancies -= industries[unemployed]->workforce;
					i_sort[c]->workforce += industries[unemployed]->workforce;
					industries[unemployed]->workforce = 0;
					break;
				}
				else
				{
					industries[unemployed]->workforce -= i_sort[c]->vacancies;
					i_sort[c]->workforce += i_sort[c]->vacancies;
					i_sort[c]->vacancies = 0;
				}
		}
		// Calc percentages
		for (int c = 0; c < industries.size(); c++)
			socium.worker_types[c].percent_of_workforce = industries[c]->workforce / demography.laborPool;


	}
	void populus_consumption()
	{
		GDP.private_consumption = 0;

		double before = demography.money;

		double realistic_demand = demography.population * 1.0;

	
		// Necessary buy
		auto t = exchanges[food_exc]->buy_amount(realistic_demand * demography.consumption_level, &demography.money.value);

		demography.foodSupply = (t.amount_bought / demography.population)/(demography.population/(geography.square_kilometres*100)) * 100;

		exchanges[pottery_exc]->buy_amount(demography.population*0.1 * demography.consumption_level, &demography.money.value);
		exchanges[cloth_exc]->buy_amount(demography.population*0.01 * demography.consumption_level, &demography.money.value);
		exchanges[wood_exc]->buy_amount(demography.population*0.01 * demography.consumption_level, &demography.money.value);
		// Populus leasure buy
		//exchanges[food_exc]->buy_money(demography.money.value*0.1, &demography.money.value);
	//	exchanges[pottery_exc]->buy_money(demography.money.value*0.1, &demography.money.value);
		//exchanges[cloth_exc]->buy_money(demography.money.value*0.1, &demography.money.value);
		if (demography.money > 5e8)
			demography.consumption_level += 0.01;
		else if (demography.consumption_level > 0)
			demography.consumption_level -= 0.01;
		// Goverment buy
		exchanges[food_exc]->buy_money(industries[goverment]->money*0.1, &industries[goverment]->money);
		exchanges[pottery_exc]->buy_money(industries[goverment]->money*0.1, &industries[goverment]->money);
		exchanges[cloth_exc]->buy_money(industries[goverment]->money*0.1, &industries[goverment]->money);

		GDP.private_consumption += abs(demography.money - before);
	}
	int date1;
	void simulate(int date)
	{
		date1 = date;

		demography.calc(date);

		calculate_jobs();

		for (int i = 0; i < exchanges.size(); i++)
			exchanges[i]->process();

		for (int i = 0; i<industries.size(); i++)
			industries[i]->process();


		demography.density = demography.population / geography.square_kilometres;

		populus_consumption();

		GDP.calcTotalGdp();


	}
};