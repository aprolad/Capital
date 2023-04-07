#include "../game/Simulation.h"

void Agriculture::compute()
{
	double usedLand;
	if (workers/300 < sim->geo.totalArableLand)
		usedLand = workers/300;
	else
		usedLand = sim->geo.totalArableLand;

	output = usedLand * 800 * 250;

	outputT = output/1000;
	if (300 == sim->date.days_from_year_start)
		wheat->reserves += output*0.7;
	double capacity = sim->population.population * 1000;
	if (wheat->reserves > capacity)
		wheat->reserves = capacity;

	wheat->calc();

	t = wheat->reserves / 1000;
	gdp = output * price;
	
}
void product::calc()
{
	aggregateDemand = sim->population.population * 0.5;
	

	if (reserves > aggregateDemand)
		aggregateSupply = aggregateDemand;
	else
		aggregateSupply = reserves;

	aggregateSupply *= 1 + (reserves / sim->population.population / 1000 - 1);

	reserves -= aggregateSupply;
	if (aggregateDemand != 0)
		consumerCoverage = aggregateSupply / aggregateDemand;
	else consumerCoverage = 1;
}