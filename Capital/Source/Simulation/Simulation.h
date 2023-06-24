#pragma once

#include "State.h"


class Technology_tree
{
public:
	
};

class Simulation
{
	bool go;
	public:
		Simulation() : player(this, 0), enemy(this, 1)
		{

			std::cout << "Sim constr" << std::endl;
			date = *new Simulation_date(-4000);
			go = false;
			computeOneDay();
			game_speed = 1;
			
		}
		World world;
		State player;
		State enemy;
		static int game_speed;
		Simulation_date date;
		
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{

			date.calculate_date();
			player.simulate(date.days_from_start);
			//enemy.simulate(date.days_from_start);
		}
		void cycle()
		{

			if (go)
				for (int i=0; i<game_speed;i++)
					computeOneDay();
		}
};
