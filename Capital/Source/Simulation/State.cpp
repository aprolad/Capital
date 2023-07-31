#include "State.h"
#include "Simulation.h"

State::State(Simulation* sim, double start_pos)
	{
				
		simulation = sim;

		if (start_pos == 0)
		{
			army.x = 2000;
			army.y = 2000;
			for (int y = 0; y < 100; y++)
				for (int x = 0; x < 100; x++)
				{

					if (pow(x - 30, 2) + pow(y - 40, 2) < 49)
					{
						simulation->world.map[y][x].owner = 1;
						simulation->world.map[y][x].color = glm::vec4(1, 0.5, 0.0, 1);
					}
				}
		}
		else
			for (int y = 0; y<100; y++)
				for (int x = 0; x<100;x++)
				{
					if (pow(x - 70, 2) + pow(y - 60, 2) < 49)
					{
						simulation->world.map[y][x].owner = 2;
						simulation->world.map[y][x].color = glm::vec4(0.5, 0.1, 0.0, 1);
					}
				}




		socium = Socium();

		industries["Farming"] = new Farming(this);

		industries["Gathering"] =(new Gathering(this));

		industries["Pottery"] =(new Pottery(this));

		industries["Husbandry"] =(new Husbandry(this));

		industries["Textile"] =(new Textile(this));


		industries["Forestry"] =(new Forestry(this));

		industries["Construction"] =(new Construction(this));


		industries["Goverment"] =(new Goverment(this));


		industries["Unemployed"] =(new Unemployed(this));





		demography.money = 1e9;

		demography.calc(0);


		for (auto& t : industries)
		{
			t.second->workforce[0].quantity = 1.0/industries.size() * demography.laborPool;
			t.second->number_of_facilities = t.second->workforce[0].quantity/4;
		}
		for (int i = 0; i < 6 ; i++)
			exchanges.push_back(new Exchange());
	}