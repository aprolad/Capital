#include "../game/Simulation.h"

void Farming::compute()
{
	expenditure = 0;
	output = workforce * 500 * double(250)/100;

	if (state->foodExc.calculate_excess() < state->foodExc.total_demand * 250)
		state->foodExc.put_sell_order(output / (365), state->foodExc.get_current_price(), &money);
	else
		state->foodExc.put_sell_order(output / (365), state->foodExc.get_current_price()/2, &money);
	pay_wage();
}

void Gathering::compute()
{
	expenditure = 0;
	double exhaust = sqrt(workforce / state->geography.square_kilometres / 15);
	if (workforce != 0)
		output = workforce * 1.4 / exhaust;

	if (state->foodExc.calculate_excess() < state->foodExc.total_demand * 250)
		state->foodExc.put_sell_order(output, state->foodExc.get_current_price(), &money);
	else 
		state->foodExc.put_sell_order(output, state->foodExc.get_current_price()/2, &money);

	pay_wage();
}

void Pottery::compute()
{
	expenditure = 0;
	output = workforce * 10;

	state->potteryExc.put_sell_order(output, state->potteryExc.get_current_price(), &money);

	prev_wage = wages;
	pay_wage();
}

void Husbandry::compute()
{
	expenditure = 0;
	double wool_output = workforce * 0.1;

	double meat_output = workforce;
	
	output = workforce * 0.1;


	state->woolExc.put_sell_order(wool_output, state->woolExc.get_current_price(), &money);
	state->foodExc.put_sell_order(meat_output, state->foodExc.get_current_price(), &money);

	pay_wage();
}

void Textile::compute()
{
	output = workforce * 0.1;
	auto t = state->woolExc.buy_amount(output * 0.5, &money);
	double material_coverage = t.amount_bought / (output * 0.5);
	expenditure = t.money_spent;

	state->clothExc.put_sell_order(output * material_coverage, state->clothExc.get_current_price(), &money);

	pay_wage();
}


void Industry::pay_wage()
{
	income = money - last_day_money;
	double avg = 0;
	for (auto a : historic_wages)
		avg += a;
	avg /= 30;

	if (workforce == 0)
		workforce = 1;
	wages = avg / workforce;
	if (wages < 0.01)
		wages = 0.01;
	double salary = income - expenditure;
	if (salary < 0)
		salary = 0;
	if (money > income * 3)
		salary += money / 10;

	double taxes = salary * 0.01;
	double netto_salary = salary - taxes;

	state->goverment.money += taxes;


	state->demography.money = state->demography.money + netto_salary;
	historic_wages.push_front(netto_salary);
	historic_wages.pop_back();
	money -= salary;

	last_day_money = money;
}


Socium::Socium()
{

	worker_types.push_back(Profession("Potters", 0.03, std::vector<float>{121, 85, 72, 1} ));

	worker_types.push_back(Profession("Leaders", 0.05, std::vector<float>{255, 0, 0, 1}));

	worker_types.push_back(Profession("Farmers", 0.12, std::vector<float>{76, 175, 80, 1}));
	
	worker_types.push_back(Profession("Gatherers",0.77, std::vector<float>{255, 152, 0, 1}));

	worker_types.push_back(Profession("Shepards", 0.01, std::vector<float>{155, 52, 0, 1}));

	worker_types.push_back(Profession("Weavers", 0.02, std::vector<float>{055, 52, 0, 1}));
	
}

void Goverment::pay_wages()
{
	double payment = money / 2;
	wages = payment / workforce;
	money -= payment;
	state->demography.money.value += payment;
}