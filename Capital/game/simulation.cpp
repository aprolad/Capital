#include "../game/Simulation.h"

void Farming::compute()
{
	output = workforce * 500 * double(250)/100;


		state->exchanges[food_exc]->put_sell_order(output / (365)/2, state->exchanges[food_exc]->get_current_price()*0.9, &money);
		state->exchanges[food_exc]->put_sell_order(output / (365)/2, state->exchanges[food_exc]->get_current_price()*1.1, &money);

}

void Goverment::compute()
{

}

void Gathering::compute()
{
	double exhaust = sqrt(workforce / state->geography.square_kilometres / 15);
	if (workforce != 0)
		output = workforce * 1.4 / exhaust;


		state->exchanges[food_exc]->put_sell_order(output/2, state->exchanges[food_exc]->get_current_price()*0.9, &money);
		state->exchanges[food_exc]->put_sell_order(output / 2, state->exchanges[food_exc]->get_current_price() * 1.1, &money);



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
	if (material_coverage < 1)
		material_coverage = 1;
	expenditure += t.money_spent;

	//std::cout << revenue << std::endl;
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
	expenditure = 0;
	auto t = state->exchanges[constr_exc]->buy_amount(workplace_count * 0.001, &money);
	expenditure += t.money_spent;
	compute();

	pay_wage();

	last_day_money = money;

	revenue_d = revenue;
	gross_profit_d = gross_profit;
	profit_after_investment_d = profit_after_investment;
	operating_profit_d = operating_profit;
	investment_account_d = investment_account;
}

void Industry::invest()
{
	double inc = workplace_count / 50;
	if (vacancies < workplace_count/10 && investment_account > inc*state->exchanges[constr_exc]->current_price/10)
	{
		workplace_count += inc;
		transfer_money(&investment_account, &state->industries[construction]->money, inc*state->exchanges[constr_exc]->current_price/10);
	}


	double investment = 0;
	if (investment_account < revenue/50)
		investment = revenue/150;
	profit_after_investment = gross_profit - investment;
	transfer_money(&investment_account, investment);
}

void Industry::pay_wage()
{
	workforce_d = workforce;
	vacancies = workplace_count - workforce;
	if (workforce < 1)
		workforce = 1;
	// arbitary vacancies creation


	invest();


	wages.value = (profit_after_investment * 0.95) / workforce;
	(wages.value < 0) ? wages = 0 : wages;
	payroll = wages * workforce + money/50;
	if (payroll > money)
	{	
		wages * 0.9;
		payroll = money;
	}
	wages = wages.value;
	double taxes = payroll * 0.03;
	double netto_salary = payroll - taxes;
	state->industries[goverment]->money += taxes;


	state->demography.money = state->demography.money + netto_salary;

	money -= payroll;


}


Socium::Socium()
{
	
}

