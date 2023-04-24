#include "../game/Simulation.h"
extern Simulation simulation;
void Agriculture::compute()
{


	workplace_count = simulation.geo.totalArableLand * 300;

	output = workforce * 800 * 250/300;


	for (int i = 0; i < 5; i++)
		simulation.foodExc.put_sell_order(output / (5 * 365), simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &simulation.agriculture.money);

	pay_wage();
}

void Gathering::compute()
{

	double exhaust = sqrt(workforce / simulation.geo.square_kilometres / 15);
	if (workforce!=0)
		output = workforce * 1 / exhaust;

	for (int i = 0; i < 5; i++)
		simulation.foodExc.put_sell_order(output / 5, simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &simulation.gathering.money);

	pay_wage();
}

void Pottery::compute()
{

	output = workforce * 20;

	for (int i = 0; i < 5; i++)
	{
		simulation.potteryExc.put_sell_order(output / 5, simulation.potteryExc.get_current_price() * 0.8 + i * 0.1, &simulation.pottery.money);
	}
	prev_wage = wages;
	pay_wage();
}

void Husbandry::compute()
{

	output = workforce * 20;

	for (int i = 0; i < 5; i++)
	{
		simulation.potteryExc.put_sell_order(output / 5, simulation.potteryExc.get_current_price() * 0.8 + i * 0.1, &simulation.pottery.money);
	}
	prev_wage = wages;
	pay_wage();
}

void Industry::pay_wage()
{
	double avg = 0;
	for (auto a : historic_wages)
		avg += a;
	avg /= 30;

	simulation.population.money = simulation.population.money + income;
	//simulation.population.income += income;
	if (workforce == 0)
		workforce += 1;
	wages = avg / workforce;
	if (wages < 0.01)
		wages = 0.01;
	historic_wages.push_front(income);
	historic_wages.pop_back();
	money -= income;
}


Socium::Socium()
{
	double free_workforce = simulation.population.laborPool;
	std::cout << simulation.population.laborPool << std::endl;
	if (simulation.population.laborPool == 0)
		simulation.population.laborPool = 1;

	worker_types.push_back(Profession("Potters", (simulation.population.population / 300) / simulation.population.laborPool, std::vector<float>{121, 85, 72, 1} ));
	free_workforce -= simulation.population.population / 300;
	worker_types.push_back(Profession("Leaders", (simulation.population.population / 30) / simulation.population.laborPool, std::vector<float>{255, 0, 0, 1}));
	free_workforce -= (simulation.population.population / 30);
	if (free_workforce > simulation.agriculture.workplace_count)
	{
		worker_types.push_back(Profession("Farmers", simulation.agriculture.workplace_count / simulation.population.laborPool, std::vector<float>{76, 175, 80, 1}));
		free_workforce -= simulation.agriculture.workplace_count;
	}
	else
	{
		worker_types.push_back(Profession("Farmers", simulation.agriculture.workplace_count / simulation.population.laborPool, std::vector<float>{76, 175, 80, 1}));
		free_workforce = 0;
	}

	worker_types.push_back(Profession("Gatherers", free_workforce / simulation.population.laborPool, std::vector<float>{255, 152, 0, 1}));
		for (auto a : worker_types)
			std::cout <<a.name<<" " << a.percent_of_workforce << std::endl;
}