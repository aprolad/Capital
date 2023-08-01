#include "Simulation.h"
int Simulation::game_speed = 1;
void Farming::compute()
{
	output = total_worker_count * 250 * double(250)/100;


		state->exchanges[food_exc]->put_sell_order(output / (365)/2, state->exchanges[food_exc]->get_current_price()*0.9, &money);
		state->exchanges[food_exc]->put_sell_order(output / (365)/2, state->exchanges[food_exc]->get_current_price()*1.1, &money);

}

void Goverment::compute()
{
	number_of_facilities = state->demography.population / 200;
}

void Gathering::compute()
{
	double exhaust = sqrt(total_worker_count / state->geography.square_kilometres / 15);
//	std::cout << total_worker_count << std::endl;
	if (total_worker_count != 0)
		output = total_worker_count * 0.7 / exhaust;


		state->exchanges[food_exc]->put_sell_order(output/2, state->exchanges[food_exc]->get_current_price()*0.9, &money);
		state->exchanges[food_exc]->put_sell_order(output / 2, state->exchanges[food_exc]->get_current_price() * 1.1, &money);



}

void Pottery::compute()
{

	output = total_worker_count * 10;

	state->exchanges[pottery_exc]->put_sell_order(output, state->exchanges[pottery_exc]->get_current_price(), &money);


}

void Husbandry::compute()
{
	
	double wool_output = total_worker_count * 0.1;

	double meat_output = total_worker_count*0.3;
	
	output = total_worker_count * 0.1;


	state->exchanges[wool_exc]->put_sell_order(wool_output, state->exchanges[wool_exc]->get_current_price(), &money);
	state->exchanges[food_exc]->put_sell_order(meat_output, state->exchanges[food_exc]->get_current_price(), &money);


}

void Textile::compute()
{

	output = total_worker_count * 0.1;
	double material_consumption = output * 0.5;
	double stockpile_fill = stockpile / (material_consumption * 100);
	double miss = 1 - stockpile_fill;
	if (stockpile < material_consumption * 200)
	{
		auto t = state->exchanges[wool_exc]->buy_amount(material_consumption, &money);
		stockpile += t.amount_bought;
		expenditure += t.money_spent;
	}
	if (stockpile < material_consumption * 100)
	{
		auto t = state->exchanges[wool_exc]->buy_amount(material_consumption * miss, &money);
		stockpile += t.amount_bought;
		expenditure += t.money_spent;
	}
	if (stockpile > (material_consumption))
		material_coverage = 1;
	else
		material_coverage = stockpile / (material_consumption);

	stockpile -= material_consumption * material_coverage;
	if (material_coverage < 0.001)
		material_coverage = 0.001;




	state->exchanges[cloth_exc]->put_sell_order(output * material_coverage, state->exchanges[cloth_exc]->get_current_price(), &money);


}

void Forestry::compute()
{
	output = total_worker_count * 0.5;

	state->exchanges[wood_exc]->put_sell_order(output, state->exchanges[wood_exc]->get_current_price(), &money);

}

void Construction::compute()
{
	output = total_worker_count * 0.2;
	double material_consumption = output * 0.5;
	double stockpile_fill = stockpile / (material_consumption * 300);
	double miss = 1 - stockpile_fill;
	if (stockpile < material_consumption * 500)
	{
		auto t = state->exchanges[wool_exc]->buy_amount(material_consumption, &money);
		stockpile += t.amount_bought;
		expenditure += t.money_spent;
	}
	if (stockpile < material_consumption * 300)
	{
		auto t = state->exchanges[wool_exc]->buy_amount(material_consumption * miss, &money);
		stockpile += t.amount_bought;
		expenditure += t.money_spent;
	}
	if (stockpile > (material_consumption))
		material_coverage = 1;
	else
		material_coverage = stockpile / (material_consumption);

	stockpile -= material_consumption * material_coverage;
	if (material_coverage < 0.001)
		material_coverage = 0.001;

	state->exchanges[constr_exc]->put_sell_order(output * material_coverage, state->exchanges[constr_exc]->get_current_price(), &money);


}

void Industry::process()
{
	total_worker_count = 0;
	for (auto& a : workforce)
		total_worker_count += a.quantity;
	revenue = money - last_day_money;
	gross_profit = revenue - expenditure;
	operating_profit = gross_profit - payroll;
	expenditure = 0;
	auto t = state->exchanges[constr_exc]->buy_amount(total_worker_count * 0.001, &money);
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
	double inc = total_worker_count / 250;
	if (workforce[0].vacancies < number_of_facilities/5 && investment_account > inc*state->exchanges[constr_exc]->current_price/10)
	{
		number_of_facilities += inc;
		transfer_money(&investment_account, &state->industries["Construction"]->money, inc * state->exchanges[constr_exc]->current_price / 10);
	}


	double investment = 0;
	if (investment_account < revenue/50)
		investment = revenue/150;
	profit_after_investment = gross_profit - investment;
	transfer_money(&investment_account, investment);
}

void Industry::pay_wage()
{

	workforce_d = total_worker_count;
	for (int i = 0; i < workforce.size(); i++)
		workforce[i].vacancies = number_of_facilities*typical_facility.positions[i] - workforce[i].quantity;

	for (int i = 0; i < workforce.size(); i++)
	{
		if (workforce[i].quantity < 1)
			workforce[i].quantity = 1;
		// arbitary vacancies creation
		//if (workforce[i].vacancies < 1000)
		//	number_of_facilities += 1;
	}

	invest();

	payroll = 0;
	double share = 0;
	for (int i = 0; i < workforce.size(); i++)
	{
		share += workforce[i].quantity * (1 + i * 3);
	}
	share = (profit_after_investment * 0.9) / share;
	for (int i = 0; i < workforce.size(); i++)
	{
		workforce[i].wage = share * (1 + i*3);
		(workforce[i].wage < 0) ? workforce[i].wage = 0 : workforce[i].wage;
		payroll += workforce[i].wage * workforce[i].quantity + money / 50;
	}

	if (payroll > money)
	{
			payroll = money;
	}

	double taxes = payroll * 0.03;
	double netto_salary = payroll - taxes;
	state->industries["Goverment"]->money += taxes;

	wages = workforce[0].wage;

	state->demography.money = state->demography.money + netto_salary;

	money -= payroll;


}


