//Alexander Rollison
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

CokeMachine::CokeMachine(std::string name, int cost, int change, int inventory)
:machineName{name},CokePrice{cost},changeLevel{change},inventoryLevel{inventory}
{
}

CokeMachine::~CokeMachine()
{
	cout<<"CokeMachine Machine "<<CokeMachine::machineName<<" has been destroyed"<<endl;
}

std::ostream& operator<<(std::ostream& output, const CokeMachine& Machine)
{
	output<<"\nCurrent Inventory Level\t"<<Machine.inventoryLevel<<"\nMax Inventory Capacity\t"<<Machine.maxInventoryCapacity<<"\n\nCurrent Change Level\t"<<Machine.displayMoney(Machine.changeLevel)<<"\nMax Change Capacity\t"<<Machine.displayMoney(Machine.maxChangeCapacity)<<"\n\nCurrent Coke Price\t"<<Machine.displayMoney(Machine.CokePrice)<<endl;
	return output;
}

bool CokeMachine::buyACoke(int payment, std::string &change, int &action)
{
	if(payment < CokePrice)
	{
		action = INSUFFICIENTFUNDS;
		return 0;
	}
	else if (changeLevel == 0 || (payment-CokePrice)>changeLevel)
	{
		action = NOCHANGE;
		return 0;
	}
	else if(changeLevel == maxChangeCapacity)
	{
		action = TOOMUCHCHANGE;
		return 0;
	}
	else if(inventoryLevel == 0)
	{
		action = NOINVENTORY;
		return 0;
	}
	else if(payment == CokePrice)
	{
		action = EXACTCHANGE;
		changeLevel = changeLevel + CokePrice;
		inventoryLevel--;
		return 1;
	}
	else
	{
		action = OK;
		payment = payment - CokePrice;
		changeLevel = changeLevel + CokePrice;
		inventoryLevel--;
		change = displayMoney(payment);
		return 1;
	}
	return 0;
}

std::string CokeMachine::getMachineName()
{
	return machineName;
}

void CokeMachine::setMachineName(std::string name)
{
	machineName = name;
}

std::string CokeMachine::getChangeLevel()
{
	return displayMoney(changeLevel);
}

bool CokeMachine::incrementChangeLevel(int amountToAdd)
{
	if((changeLevel+amountToAdd) > maxChangeCapacity)
	{
		changeLevel = maxChangeCapacity;
		return 0;
	}
	else
	{
		changeLevel = changeLevel + amountToAdd;
		return 1;
	}
	return 0;
}

std::string CokeMachine::getMaxChangeCapacity()
{
	return displayMoney(maxChangeCapacity);
}

int CokeMachine::getInventoryLevel()
{
	return inventoryLevel;
}

int CokeMachine::getMaxInventoryCapacity()
{
	return maxInventoryCapacity;
}

bool CokeMachine::incrementInventory(int amountToAdd)
{
	if((inventoryLevel+amountToAdd) > maxInventoryCapacity)
	{
		inventoryLevel = maxInventoryCapacity;
		return 0;
	}
	else
	{
		inventoryLevel = inventoryLevel + amountToAdd;
		return 1;
	}
	return 0;
}

std::string CokeMachine::getCokePrice()
{
	return displayMoney(CokePrice);
}

void CokeMachine::setCokePrice(int newCokePrice)
{
	CokePrice = newCokePrice;
}

std::string CokeMachine::displayMoney(int amount) const
{
	std::string dollars{std::to_string(amount/100)};
	std::string cents{std::to_string(amount%100)};
	std::ostringstream moneyOs;
	moneyOs <<"$"<<dollars << "." << (cents.size() == 1 ? "0" : "") + cents;
	std::string money = moneyOs.str();

	return money;
}

std::string CreateCokeOutputLine(CokeMachine &value)
{
	ostringstream output;
	output<<value.machineName<<"|"<<value.CokePrice<<"|"<<value.changeLevel<<"|"<<value.inventoryLevel<<"\n";
	return output.str();
}
