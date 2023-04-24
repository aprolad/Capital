#include "../game/Simulation.h"
extern Simulation simulation;
void Agriculture::compute()
{
	expenditure = 0;
	output = workforce * 800 * double(250)/100;

	//if (simulation.foodExc.quantity_backlog < 1e8)
		for (int i = 0; i < 5; i++)
			simulation.foodExc.put_sell_order(output / (5 * 365), simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &money);

	pay_wage();
}

void Gathering::compute()
{
	expenditure = 0;
	double exhaust = sqrt(workforce / simulation.geo.square_kilometres / 15);
	//std::cout << "Exhaust "<<exhaust << std::endl;
	if (workforce!=0)
		output = workforce * 2 / exhaust;
	//if (simulation.foodExc.quantity_backlog < 1e8)
		for (int i = 0; i < 5; i++)
			simulation.foodExc.put_sell_order(output / 5, simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &money);


	pay_wage();
}

void Pottery::compute()
{
	expenditure = 0;
	output = workforce * 20;

	for (int i = 0; i < 5; i++)
	{
		simulation.potteryExc.put_sell_order(output / 5, simulation.potteryExc.get_current_price() * 0.8 + i * 0.1, &money);
	}
	prev_wage = wages;
	pay_wage();
}

void Husbandry::compute()
{
	expenditure = 0;
	double wool_output = workforce * 0.1;

	double meat_output = workforce;
	
	output = workforce * 0.1;

	for (int i = 0; i < 5; i++)
	{
		simulation.woolExc.put_sell_order(wool_output / 5, simulation.woolExc.get_current_price() * 0.8 + i * 0.1, &money);
		simulation.foodExc.put_sell_order(meat_output / 5, simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &money);
	}
	//std::cout << "Income " <<income << std::endl;
	//std::cout << "Quantity " << wool_output << std::endl;
	pay_wage();
}

void Textile::compute()
{
	output = workforce * 0.1;
	//std::cout << "M to buy  " << money << std::endl;
	auto t = simulation.woolExc.buy_amount(output * 0.5, &money);
	//std::cout << "Money spent " << t.money_spent << std::endl;
	//std::cout << "WOOL BOUGHT  " << t.amount_bought << std::endl;
	double needed_material = t.amount_bought / (output * 0.5);
	//std::cout << "PRice " << simulation.woolExc.current_price << std::endl;
	expenditure = t.money_spent;
	for (int i = 0; i < 5; i++)
	{
		simulation.clothExc.put_sell_order(output / 5 * needed_material, simulation.clothExc.get_current_price() * 0.8 + i * 0.1, &money);
	}

	pay_wage();
}


void Industry::pay_wage()
{
	double avg = 0;
	for (auto a : historic_wages)
		avg += a;
	avg /= 30;


	//simulation.population.income += income;
	if (workforce == 0)
		workforce += 1;
	wages = avg / workforce;
	if (wages < 0.01)
		wages = 0.01;
	double salary = income - expenditure;
	if (money > income * 10)
		salary += money / 30;
	simulation.population.money = simulation.population.money + salary;
	historic_wages.push_front(income - expenditure);
	historic_wages.pop_back();
	money -= salary;
}


Socium::Socium()
{

	worker_types.push_back(Profession("Potters", 0.03, std::vector<float>{121, 85, 72, 1} ));

	worker_types.push_back(Profession("Leaders", 0.05, std::vector<float>{255, 0, 0, 1}));

	worker_types.push_back(Profession("Farmers", 0.12, std::vector<float>{76, 175, 80, 1}));
	
	worker_types.push_back(Profession("Gatherers",0.77, std::vector<float>{255, 152, 0, 1}));

	worker_types.push_back(Profession("Shepards", 0.01, std::vector<float>{155, 52, 0, 1}));

	worker_types.push_back(Profession("Weavers", 0.02, std::vector<float>{055, 52, 0, 1}));
		for (auto a : worker_types)
			std::cout <<a.name<<" " << a.percent_of_workforce << std::endl;
}