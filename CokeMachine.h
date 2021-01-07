//Alexander Rollison
#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

enum ACTION
{
    OK,NOINVENTORY,NOCHANGE,INSUFFICIENTFUNDS,EXACTCHANGE,TOOMUCHCHANGE
};

class CokeMachine
{
	friend std::ostream& operator<<(std::ostream& output, const CokeMachine& MyMachine);
	friend std::string CreateCokeOutputLine(CokeMachine &value);
	
	public:
		CokeMachine(std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100);
		~CokeMachine();
	
		bool buyACoke(int payment, std::string &change, int &action);
		std::string getMachineName();
		void setMachineName(std::string name);
		std::string getChangeLevel();
		bool incrementChangeLevel(int amountToAdd);
		std::string getMaxChangeCapacity();
		int getInventoryLevel();
		int getMaxInventoryCapacity();
		bool incrementInventory(int amountToAdd);
		std::string getCokePrice();
		void setCokePrice(int newCokePrice);
		std::string displayMoney(int amount) const;
	
	private:
		std::string machineName;
		int changeLevel;
		int maxChangeCapacity{5000};
		int maxInventoryCapacity{100};
		int inventoryLevel;
		int CokePrice;
};

#endif
