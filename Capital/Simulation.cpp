#include "game/simulation.h"

void agriculture::compute()
{
	double usedLand;
	if (workers < geo->totalArableLand)
		usedLand = workers;
	else
		usedLand = geo->totalArableLand;

	wheat.naturalOutput = usedLand * productivity;

	output = wheat.naturalOutput;
	if (sim->date.current_month == sim->date.Sep)
		kgs += wheat.naturalOutput*12;
	kgs -= sim->population.population * 0.7;
	gdp = output * price;
	wheat.calc(&sim->population);
}