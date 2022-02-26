#pragma once
class simulation
{
	bool go;
	public:
		simulation()
		{
			population = 100;
			date = 0;
			go = false;
		}
		int date;
		double population;
		double GDP;
		void pause()
		{
			go = !go;
		}
		void computeOneDay()
		{
			date += 1;

			population += population * 0.0001;
		}
		void cycle()
		{
			if (go)
				computeOneDay();
		}
};