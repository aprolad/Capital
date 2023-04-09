#include "../game/Simulation.h"
extern Simulation simulation;
void Agriculture::compute()
{
	workplace_count = simulation.geo.totalArableLand * 300;

	output = workforce * 800 * 250/300;

	outputT = output/1000;
	if (300 == simulation.date.days_from_year_start)
		wheat->reserves += output*0.7;
	double capacity = simulation.population.population * 1000;
	if (wheat->reserves > capacity)
		wheat->reserves = capacity;

	wheat->calc();

	t = wheat->reserves / 1000;
	gdp = output * price;
	
}

void Gathering::compute()
{
	
	if (workforce!=0)
		output = workforce * 1 * (10/(workforce/double(simulation.geo.sqKilometres)));

	outputT = output / 1000;

	simulation.agriculture->wheat->reserves += output;

	t = wheat->reserves / 1000;
	gdp = output * price;

}

void product::calc()
{
	aggregateDemand = simulation.population.population * 0.5;
	

	if (reserves > aggregateDemand)
		aggregateSupply = aggregateDemand;
	else
		aggregateSupply = reserves;

	aggregateSupply *= 1 + (reserves / simulation.population.population / 1000 - 1);

	reserves -= aggregateSupply;
	if (aggregateDemand != 0)
		consumerCoverage = aggregateSupply / aggregateDemand;
	else consumerCoverage = 1;
}