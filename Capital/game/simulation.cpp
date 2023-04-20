#include "../game/Simulation.h"
extern Simulation simulation;
void Agriculture::compute()
{
	//income = money - last_day_balance;

	//last_day_balance = money;


	workplace_count = simulation.geo.totalArableLand * 300;

	output = workforce * 800 * 250/300;


	for (int i = 0; i < 5; i++)
		simulation.foodExc.put_sell_order(output / (5 * 365), simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &simulation.agriculture.money);

	simulation.population.money.value += income;
	workforce++;
	wages = income / workforce;
	money -= income;

	
}

void Gathering::compute()
{
	//income = money - last_day_balance;

	//last_day_balance = money;

	double exhaust = sqrt(workforce / simulation.geo.sqKilometres / 15);
	if (workforce!=0)
		output = workforce * 1 / exhaust;



	for (int i = 0; i < 5; i++)
		simulation.foodExc.put_sell_order(output / 5, simulation.foodExc.get_current_price() * 0.8 + i * 0.1, &simulation.gathering.money);


	simulation.population.money = simulation.population.money + income;
	workforce++;
	wages = income / workforce;
	money -= income;

}

void Pottery::compute()
{
	//income = money - last_day_balance;

	//last_day_balance = money;
	double avg = 0;
	for (auto a : historic_wages)
		avg += a;
	avg /= 30;
	output = workforce * 20;

	for (int i = 0; i < 5; i++)
	{
		simulation.potteryExc.put_sell_order(output / 5, simulation.potteryExc.get_current_price() * 0.8 + i * 0.1, &simulation.pottery.money);
	}
	prev_wage = wages;
	simulation.population.money = simulation.population.money + income;
	if (workforce == 0)
		workforce += 1;
	wages = avg / workforce;
	historic_wages.push_front(income);
	historic_wages.pop_back();
	money -= income;

}

Socium::Socium()
{
	double free_workforce = simulation.population.laborPool;

	if (simulation.population.laborPool == 0)
		simulation.population.laborPool = 1;

	worker_types.push_back(Profession("Potters", (simulation.population.population / 300) / simulation.population.laborPool));
	free_workforce -= simulation.pottery.workforce;
	worker_types.push_back(Profession("Leaders", (simulation.population.population / 30) / simulation.population.laborPool));
	free_workforce -= simulation.goverment.workforce;
	if (free_workforce > simulation.agriculture.workplace_count)
	{
		worker_types.push_back(Profession("Farmers", simulation.agriculture.workplace_count / simulation.population.laborPool));
		free_workforce -= simulation.agriculture.workplace_count;
	}
	else
	{
		worker_types.push_back(Profession("Farmers", simulation.agriculture.workplace_count / simulation.population.laborPool));
		free_workforce = 0;
	}

	worker_types.push_back(Profession("Gatherers", free_workforce / simulation.population.laborPool));
	//	for (auto a : worker_types)
		//	std::cout <<a.name<<" " << a.percent_of_workforce << std::endl;
}