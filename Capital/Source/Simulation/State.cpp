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

		industries.push_back(new Farming(this));
		socium.worker_types.push_back(Profession("Farmers", 0.12, std::vector<float>{76, 175, 80, 1}));
		industries.push_back(new Gathering(this));
		socium.worker_types.push_back(Profession("Gatherers",0.75, std::vector<float>{255, 152, 0, 1}));
		industries.push_back(new Pottery(this));
		socium.worker_types.push_back(Profession("Potters", 0.03, std::vector<float>{121, 85, 72, 1} ));
		industries.push_back(new Husbandry(this));
		socium.worker_types.push_back(Profession("Shepards", 0.01, std::vector<float>{155, 52, 0, 1}));
		industries.push_back(new Textile(this));
		socium.worker_types.push_back(Profession("Weavers", 0.02, std::vector<float>{055, 52, 0, 1}));

		industries.push_back(new Forestry(this));
		socium.worker_types.push_back(Profession("Foresters", 0.01, std::vector<float>{0, 255, 0, 1}));
		industries.push_back(new Construction(this));
		socium.worker_types.push_back(Profession("Construction", 0.01, std::vector<float>{0, 0, 0, 1}));

		industries.push_back(new Goverment(this));
		socium.worker_types.push_back(Profession("Leaders", 0.05, std::vector<float>{255, 0, 0, 1}));
		industries.push_back(new Unemployed(this));
		socium.worker_types.push_back(Profession("Unemployed", 0.00, std::vector<float>{0, 0, 255, 1}));



		demography.money = 1e9;

		demography.calc(0);


		for (int i = 0; i < industries.size(); i++)
		{
			industries[i]->workforce[0].quantity = socium.worker_types[i].percent_of_workforce * demography.laborPool;
			industries[i]->number_of_facilities = industries[i]->workforce[0].quantity/4;
		}
		for (int i = 0; i < 6 ; i++)
			exchanges.push_back(new Exchange());
	}