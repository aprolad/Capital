#include "../game/Simulation.h"

void Farming::compute()
{
	output = workforce * 500 * double(250)/100;

	if (state->exchanges[food_exc]->calculate_excess() < state->exchanges[food_exc]->total_demand * 250)
		state->exchanges[food_exc]->put_sell_order(output / (365), state->exchanges[food_exc]->get_current_price(), &money);
	else
		state->exchanges[food_exc]->put_sell_order(output / (365), state->exchanges[food_exc]->get_current_price()/2, &money);

}

void Goverment::compute()
{

}

void Gathering::compute()
{
	double exhaust = sqrt(workforce / state->geography.square_kilometres / 15);
	if (workforce != 0)
		output = workforce * 1.4 / exhaust;

	if (state->exchanges[food_exc]->calculate_excess() < state->exchanges[food_exc]->total_demand * 250)
		state->exchanges[food_exc]->put_sell_order(output, state->exchanges[food_exc]->get_current_price(), &money);
	else 
		state->exchanges[food_exc]->put_sell_order(output, state->exchanges[food_exc]->get_current_price()/2, &money);


}

void Pottery::compute()
{

	output = workforce * 10;

	state->exchanges[pottery_exc]->put_sell_order(output, state->exchanges[pottery_exc]->get_current_price(), &money);

	prev_wage = wages;

}

void Husbandry::compute()
{
	
	double wool_output = workforce * 0.1;

	double meat_output = workforce;
	
	output = workforce * 0.1;


	state->exchanges[wool_exc]->put_sell_order(wool_output, state->exchanges[wool_exc]->get_current_price(), &money);
	state->exchanges[food_exc]->put_sell_order(meat_output, state->exchanges[food_exc]->get_current_price(), &money);


}

void Textile::compute()
{

	output = workforce * 0.1;
	auto t = state->exchanges[wool_exc]->buy_amount(output * 0.5, &money);
	double material_coverage = t.amount_bought / (output * 0.5);
	expenditure += t.money_spent;

	state->exchanges[cloth_exc]->put_sell_order(output * material_coverage, state->exchanges[cloth_exc]->get_current_price(), &money);


}

void Forestry::compute()
{
	output = workforce * 0.1;

	state->exchanges[wood_exc]->put_sell_order(output, state->exchanges[wood_exc]->get_current_price(), &money);

}

void Construction::compute()
{
	output = workforce * 0.1;
	auto t = state->exchanges[wood_exc]->buy_amount(output * 0.5, &money);
	output.value += 0.1;
	double material_coverage = t.amount_bought / (output * 0.5);
	expenditure += t.money_spent;

	state->exchanges[constr_exc]->put_sell_order(output * material_coverage, state->exchanges[constr_exc]->get_current_price(), &money);


}

void Industry::process()
{
	revenue = money - last_day_money;
	gross_profit = revenue - expenditure;
	operating_profit = gross_profit - payroll;

	auto t = state->exchanges[constr_exc]->buy_amount(workplace_count * 0.001, &money);
	expenditure += t.money_spent;
	compute();

	pay_wage();

	last_day_money = money;

	expenditure = 0;
}

void Industry::pay_wage()
{
	workforce_d = workforce;
	vacancies = workplace_count - workforce;
	// arbitary vacancies creation
	if (vacancies < 50 && investment_account > 1000)
	{
		transfer_money(&investment_account, &state->industries[construction]->money, 1000);
		workplace_count += 100;
	}
	else if (vacancies > workplace_count*0.1)
		workplace_count -= 10;


	//	if (operating_profit > 0)
	//		wages = wages * 1.01;
	//	if (operating_profit < 0)
	//		wages = wages * 0.99;
	if (workforce < 1)
		workforce = 1;

	double investment = 50;
	if (vacancies > 50)
		investment = 0;
	double profit_after_investment = gross_profit - investment;
	transfer_money(&investment_account, investment);

	wages = profit_after_investment / workforce;

	payroll = wages * workforce + money/50;
	if (payroll > money)
	{	
		wages * 0.9;
		payroll = money;
	}

	double taxes = payroll * 0.01;
	double netto_salary = payroll - taxes;
	state->industries[goverment]->money += taxes;


	state->demography.money = state->demography.money + netto_salary;

	money -= payroll;


}


Socium::Socium()
{
	
}

