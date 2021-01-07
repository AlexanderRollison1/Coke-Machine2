//Alexander Rollison 1001681800 @Alexander.rollison@mavs.uta.edu
#include <iostream> //cin,cout,etc.
#include <vector> //vectors
#include <string> //strings
#include <sstream> //ostringstream
#include <stdexcept> //errors
#include <fstream> //files

#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

int main(int argc, char *argv[])
{
	//CokeMachine MyCokeMachine{"\n\nCSE 1325 Coke Machine", 50, 500, 100};
    int choice;
    int payment;
    int action;
    std::string change = {};
    bool buycheck;
	std::string newName;
	int newCokePrice;
	ostringstream output;
	std::string output1;

    int addproduct;
    bool inventorycheck;
    bool changecheck;
    int addchange;
	
	std::string inputFilename;
	std::string outputFilename;
	
	int pick;
	
	try
	{
		get_command_line_params(argc, argv, inputFilename, outputFilename);	
	}
	catch(invalid_argument& ex)
	{
		cerr<<ex.what()<<endl;
		exit(0);
	}
	
	vector<CokeMachine>SetOfCokeMachines;
	ifstream fpi;
	fpi.open(inputFilename, ios::in);

	if(fpi.is_open())
	{
		std::string CokeMachineLine;
		vector<std::string>ConstructorValues(4);
		
		while(getline(fpi,CokeMachineLine))
		{
			if(ParseCokeLine(CokeMachineLine, ConstructorValues)==1)
			{
				CokeMachine addMachine(ConstructorValues.at(0),stoi(ConstructorValues.at(1)),stoi(ConstructorValues.at(2)),stoi(ConstructorValues.at(3)));
				SetOfCokeMachines.push_back(addMachine);
			}
			else
			{
				cout<<"Unable to open file"<<endl;
				exit(0);
			}
		}
	}
	fpi.close();
	
	do
	{
		int i = 1;
		cout<<"\nPick a Coke Machine"<<endl;
		cout<<"0. Exit"<<endl;
		
		for(auto &it: SetOfCokeMachines)
		{
			cout<<i++<<". "<<it.getMachineName()<<endl;
		}
		
		cout<<i<<". "<<"Add a new machine"<<endl;
		cout<<"\nEnter Choice ";
		cin>>pick;
        getchar();
		
		if(pick == 0)
		{
			ofstream fpo{outputFilename, ios::out};
			if(fpo.is_open())
			{
				for(auto &it: SetOfCokeMachines)
				{
					output1 = CreateCokeOutputLine(it);
					fpo<<output1;
				}
			}
			fpo.close();
		}
		else if(pick == i)
		{
			CokeMachine newMachine;
			SetOfCokeMachines.push_back(newMachine);
		}
		else if(pick > i || pick < 0)
		{
			pick = 0;
		}
		else if(pick < i)
		{
            pick--;
			//CokeMachine MyCokeMachine(SetOfCokeMachines.at(pick));
			
			do
			{
				cout<<(SetOfCokeMachines.at(pick)).getMachineName()<<endl;
				cout<<"\n0. Walk away\n1. Buy a Coke\n2. Restock Machine\n3. Add change\n4. Display Machine Info\n5. Update Machine Name\n6. Update Coke Price"<<endl;
				cin>>choice;
                getchar();
				output<<(SetOfCokeMachines.at(pick));
				switch(choice)
				{
					case 0: //Walk away
						cout<<"Are you sure you aren't really THIRSTY and need a Coke?"<<endl;
						//break out of loop
						break;
					case 1: //Buy a Coke
						cout<<"\ninsert payment ";
						cin>>payment;
						buycheck = (SetOfCokeMachines.at(pick)).buyACoke(payment,change, action);

						if(buycheck == 1)
						{
							if(action == OK)    
							{
								cout<<"Here's your Coke and your change of $"<<change<<endl;
							}

							if(action == EXACTCHANGE)
							{
								cout<<"\nThank you for exact change"<<endl;
								cout<<"Here's your Coke"<<endl;
							}
						}
						else
						{
							switch(action) //OK,NOINVENTORY,NOCHANGE,INSUFFICIENTFUNDS,EXACTCHANGE
							{
								case NOINVENTORY:
									cout<<"\nMachine Empty...\nreturning your payment"<<endl;
									break;
								case NOCHANGE:
									cout<<"\nUnable to give change at this time...\nreturning your payment"<<endl;
									break;
								case INSUFFICIENTFUNDS:
									cout<<"\nInsufficent payment...\nreturning your payment"<<endl;
									break;
								case TOOMUCHCHANGE:
									cout<<"\nChange box is full - call 1800IMFULL to get change removed...\nreturning your payment"<<endl;
									break;
							}
						}
						break;
					case 2: //Restock Machine
						cout<<"\nHow much product are you adding to the machine? ";
						cin>>addproduct;
						inventorycheck = (SetOfCokeMachines.at(pick)).incrementInventory(addproduct);
						if(inventorycheck == 0)
						{
							cout<<"You have exceeded your machine's max capacity"<<endl;
						}
						else
						{
							cout<<"Your machine has been restocked"<<endl;
						}
						cout<<"Your inventory level is now "<<(SetOfCokeMachines.at(pick)).getInventoryLevel()<<endl;
						break;
					case 3: //Add Change
						cout<<"\nHow much change are you adding to the machine? ";
						cin>>addchange;
						changecheck = (SetOfCokeMachines.at(pick)).incrementChangeLevel(addchange);
						if(changecheck == 0)
						{
							cout<<"You have exceeded your machine's max capacity"<<endl;
						}
						else
						{
							cout<<"Your machine has been restocked"<<endl;
						}
						cout<<"Your change level is now "<<(SetOfCokeMachines.at(pick)).getChangeLevel()<<endl;
						break;
					case 4: //Display Machine Info
						cout<<output.str();
						break;
					case 5:
						cout<<"Enter a new machine name ";
						getline(cin,newName);
						(SetOfCokeMachines.at(pick)).setMachineName(newName);
						
						cout<<"Machine name has been updated\n"<<endl;
                        break;
					case 6:
						cout<<"Enter a new Coke price ";
						cin>>newCokePrice;
                        getchar();
						(SetOfCokeMachines.at(pick)).setCokePrice(newCokePrice);
						
						cout<<"Coke price has been updated\n"<<endl;
                        break;
				}
			}
			while(choice != 0);
		}
	}
	while(pick != 0);
}
