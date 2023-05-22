#pragma once

#include "../State.h"




class Technology_tree
{
public:
	
};

class Simulation
{
	bool go;
	public:
		Simulation()
		{
			date = *new Simulation_date(-4000);
			go = false;
			player.demography.dependencyRate = 0.70;
			
			computeOneDay();
			game_speed = 1;

			player.demography.money = 1e7;
			cheat = 1e15;
		}

		State player;
		static int game_speed;
		Simulation_date date;
		Geography geo;
		
		double g, cheat;
		
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{
			player.GDP.private_consumption = 0;
			date.calculate_date();
			
			player.simulate(date.days_from_start);


			
			player.demography.density = player.demography.population / geo.square_kilometres;

			double before = player.demography.money;

			double realistic_demand = player.demography.population * 1.0 * (std::tanh(-(player.foodExc.current_price - 100)/100) * 0.5 + 1);

			auto t = player.foodExc.buy_money(player.demography.money.value * 0.8, &player.demography.money.value);

			player.foodExc.total_demand = player.demography.population;

			player.demography.foodSupply = t.amount_bought / player.demography.population * 100;
		
			if (player.demography.money.value > 0)
				t = player.potteryExc.buy_money(player.demography.money.value*0.5, &player.demography.money.value);
		//	potteryExc.total_demand = population.population / 5;

			player.clothExc.buy_money(player.demography.money.value, &player.demography.money.value);

		//	std::cout << "Remains  " << socium.by_name("Weavers")->percent_of_workforce << std::endl;
			player.GDP.private_consumption += abs(player.demography.money - before);

			player.GDP.calcTotalGdp();
		}
		void cycle()
		{
			if (go)
				for (int i=0; i<game_speed;i++)
					computeOneDay();
		}
};
