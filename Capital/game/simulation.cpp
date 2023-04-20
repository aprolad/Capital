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
	wages = income / simulation.population.population;
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
	money -= income;


}

void Product::calc()
{

}