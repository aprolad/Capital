#include "game/simulation.h"

void agriculture::compute()
{
	double usedLand;
	if (workers/1000 < geo->totalArableLand)
		usedLand = workers/1000;
	else
		usedLand = geo->totalArableLand;

	wheat.naturalOutput = usedLand * 200 * 250;

	output = wheat.naturalOutput;
	outputT = output/1000;
	if (sim->date.current_month == sim->date.Sep)
		kgs += wheat.naturalOutput*0.7;
	kgs -= sim->population.population * 0.8;
	double capacity = sim->population.population * 2000;
	if (kgs > capacity)
		kgs = capacity;
	if (kgs < 0)
		kgs = 0;
	t = kgs / 1000;
	gdp = output * price;
	wheat.calc(&sim->population);
}