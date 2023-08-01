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


		using glm::vec4;


		industries["Farming"] = new Farming(this, vec4(76, 175, 80, 1), 1);

		industries["Gathering"] =new Gathering(this, vec4(255, 152, 0, 1), 1);

		industries["Pottery"] =(new Pottery(this, vec4(121, 85, 72, 1), 1));

		industries["Husbandry"] =(new Husbandry(this, vec4(155, 52, 0, 1), 1));

		industries["Textile"] =(new Textile(this, vec4(55, 52, 0, 1), 1));


		industries["Forestry"] =(new Forestry(this, vec4(0, 255, 0, 1), 1));

		industries["Construction"] =(new Construction(this, vec4(0, 0, 0, 1), 1));


		industries["Goverment"] =(new Goverment(this, vec4(255, 0, 0, 1), 1));


		industries["Unemployed"] =(new Unemployed(this, vec4(0, 0, 255, 1), 1));





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