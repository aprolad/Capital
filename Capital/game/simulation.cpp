#include "../game/Simulation.h"

void Agriculture::compute()
{
	double usedLand;
	if (workers/300< geo->totalArableLand)
		usedLand = workers/300;
	else
		usedLand = geo->totalArableLand;

	wheat.naturalOutput = usedLand * 800 * 250;

	output = wheat.naturalOutput;
	outputT = output/1000;
	if (300 == sim->date.days_from_year_start)
		kgs += wheat.naturalOutput*0.7;
	kgs -= sim->population.population * 0.5;
	double capacity = sim->population.population * 1000;
	if (kgs > capacity)
		kgs = capacity;
	if (kgs < 0)
		kgs = 0;
	t = kgs / 1000;
	gdp = output * price;
	wheat.calc(&sim->population);
}