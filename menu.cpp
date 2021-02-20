#pragma warning (disable: 4996)
#include <iostream>
#include "party.h"
#include "district.h"
#include "voters_notebook.h"

using namespace std;
using namespace election;

bool createCitizen(citizen* cit)
{
	char name[200];
	int id, year, district;
	cout << "Enter new citizen name,id,birth year and district serial num";
	cin>>name >> id >> year >> district;
	if (strlen(name) < 1) 
	{
		cout << "Invalid Name";
		return false;
	}
	if (id < 1)
	{
		cout << "Invalid ID";
		return false;
	}
	if ((year< 1900)||(year>2030))
	{
		cout << "Invalid year";
		return false;
	}
	if((district<0)||(district>)

}
bool isValidId(int id)
{
	if (id > 0)
		return true;
	cout << "Wrong Input,Enter valid one" << endl;
	return false;
}
bool isValidName(char* name)
{
	if (strlen(name) > 0)
		return true;
	cout << "Wrong Input,Enter valid one" << endl;
	return false;
}
void mainMenu(void)
{
	district** allDistricts
	voters_notebook state;
	int input;
	cin >> input;
	while (input != 10)
	{
		if (input == 2)
		{
			state.addCitizen();
		}
	}
}