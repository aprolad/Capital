#include "Simulation.h"
int Simulation::game_speed = 1;
void Farming::compute()
{
	output = workforce[0].quantity * 250 * double(250)/100;


		state->exchanges[food_exc]->put_sell_order(output / (365)/2, state->exchanges[food_exc]->get_current_price()*0.9, &money);
		state->exchanges[food_exc]->put_sell_order(output / (365)/2, state->exchanges[food_exc]->get_current_price()*1.1, &money);

}

void Goverment::compute()
{

}

void Gathering::compute()
{
	double exhaust = sqrt(workforce[0].quantity / state->geography.square_kilometres / 15);
//	std::cout << workforce[0].quantity << std::endl;
	if (workforce[0].quantity != 0)
		output = workforce[0].quantity * 0.7 / exhaust;


		state->exchanges[food_exc]->put_sell_order(output/2, state->exchanges[food_exc]->get_current_price()*0.9, &money);
		state->exchanges[food_exc]->put_sell_order(output / 2, state->exchanges[food_exc]->get_current_price() * 1.1, &money);



}

void Pottery::compute()
{

	output = workforce[0].quantity * 10;

	state->exchanges[pottery_exc]->put_sell_order(output, state->exchanges[pottery_exc]->get_current_price(), &money);

	prev_wage = workforce[0].wage;

}

void Husbandry::compute()
{
	
	double wool_output = workforce[0].quantity * 0.1;

	double meat_output = workforce[0].quantity*0.3;
	
	output = workforce[0].quantity * 0.1;


	state->exchanges[wool_exc]->put_sell_order(wool_output, state->exchanges[wool_exc]->get_current_price(), &money);
	state->exchanges[food_exc]->put_sell_order(meat_output, state->exchanges[food_exc]->get_current_price(), &money);


}

void Textile::compute()
{

	output = workforce[0].quantity * 0.1;
	auto t = state->exchanges[wool_exc]->buy_amount(output * 0.5, &money);
	double material_coverage = t.amount_bought / (output * 0.5);
	if (material_coverage < 0.1)
		material_coverage = 0.1;
	//std::cout << "1 "<<material_coverage << std::endl;
	expenditure += t.money_spent;

	//std::cout << revenue << std::endl;
	state->exchanges[cloth_exc]->put_sell_order(output * material_coverage, state->exchanges[cloth_exc]->get_current_price(), &money);


}

void Forestry::compute()
{
	output = workforce[0].quantity * 0.5;

	state->exchanges[wood_exc]->put_sell_order(output, state->exchanges[wood_exc]->get_current_price(), &money);

}

void Construction::compute()
{
	output = workforce[0].quantity * 0.2;
	auto t = state->exchanges[wood_exc]->buy_amount(output * 0.5, &money);
	output.value += 0.1;
	double material_coverage = t.amount_bought / (output * 0.5);
	if (material_coverage < 0.1)
		material_coverage = 0.1;
	expenditure += t.money_spent;

	state->exchanges[constr_exc]->put_sell_order(output * material_coverage, state->exchanges[constr_exc]->get_current_price(), &money);


}

void Industry::process()
{
	revenue = money - last_day_money;
	gross_profit = revenue - expenditure;
	operating_profit = gross_profit - payroll;
	expenditure = 0;
	auto t = state->exchanges[constr_exc]->buy_amount(workforce[0].quantity * 0.001, &money);
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
	double inc = workforce[0].quantity / 50;
	if (workforce[0].vacancies < workplace_count/10 && investment_account > inc*state->exchanges[constr_exc]->current_price/10)
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

	workforce_d = workforce[0].quantity;
	workforce[0].vacancies = workplace_count - workforce[0].quantity;
	if (workforce[0].quantity < 1)
		workforce[0].quantity = 1;
	// arbitary vacancies creation
	if (workforce[0].vacancies < 1000)
		workplace_count += 10;
	invest();


	workforce[0].wage = (profit_after_investment * 0.95) / workforce[0].quantity;
	(workforce[0].wage < 0) ? workforce[0].wage = 0 : workforce[0].wage;
	payroll = workforce[0].wage * workforce[0].quantity + money/50;
	if (payroll > money)
	{	
		workforce[0].wage * 0.9;
		payroll = money;
	}
	workforce[0].wage = workforce[0].wage;
	double taxes = payroll * 0.03;
	double netto_salary = payroll - taxes;
	state->industries[goverment]->money += taxes;

	wages = workforce[0].wage;

	state->demography.money = state->demography.money + netto_salary;

	money -= payroll;


}


Socium::Socium()
{
	
}

