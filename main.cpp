#include "main.h"
using namespace std;
using namespace election;
#define SIZE 100
#include <vector>


int main(void)
{
	try
	{
		mainMenu();
	}
	catch (std::bad_alloc& ba)
	{
		cout << "bad allocation" << endl;
	}
	catch (std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "Error" << endl;
	}

	
	return 0;
}

void printMenu2()
{
	cout << "Welcome To The Elections Menu, Press 1-3 to procceed" << endl;
	cout << "1.new election round" << endl;
	cout << "2.load previous round" << endl;
	cout << "3.Exit" << endl;
}

void mainMenu()
{
	printMenu2();
	int input;
	cin >> input;
	electionRound* round1 = nullptr;
	if (input == 1)
	{
		int day, month, year, type;
		cout << "please enter date of election : day, month, year" << endl;
		cin >> day >> month >> year;
		if ((day < 0 || day > 30)||(month==2&&day>28))
			throw invalid_argument("invalid date day");
		if (month <0 || day > 30)
			throw invalid_argument("invalid date month");
		if (year < 0)
			throw invalid_argument("invalid date year");
		cout << "enter 0 for regular round of election or 1 for simple round of election" << endl;
		cin >> type;
		if (type == 0)
			round1 = new electionRound(day, month, year, electionR::regular);
		else if (type == 1)
		{
			round1 = new electionRound(day, month, year, electionR::simple);
			cout << "enter number of electors" << endl;
			int electors;
			cin >> electors;
			round1->getdArr()[0]->setElectors(electors);
		}
		else
			throw invalid_argument("invalid input");
		
		menu(round1);
	}
	else if (input == 2)
	{
		char fileName[SIZE];
		cout << "please enter file name" << endl;
		cin >> fileName;
		ifstream inFile(fileName, ios::binary);
		if (!inFile)
			throw invalid_argument("invalid File");
		electionRound round1;
		round1.load(inFile);
		inFile.close();
		menu(&round1);
	}
	else if (input == 3)
	{
		cout << "Bye Bye";
		exit(0);
	}
	delete(round1);
}

void printMenu()
{
	cout << "Welcome To The Elections Menu,Press 1-12 to procceed" << endl;
	cout << "1.Enter new district" << endl;
	cout << "2.Enter new citizen" << endl;
	cout << "3.Enter new party" << endl;
	cout << "4.Enter new representative" << endl;
	cout << "5.show all districts" << endl;
	cout << "6.show all citizens" << endl;
	cout << "7.show all parties" << endl;
	cout << "8.make a citizen's vote" << endl;
	cout << "9.Show Elections!!" << endl;
	cout << "10.Exit Program" << endl;
	cout << "11.save this round of election" << endl;
	cout << "12.load previous round" << endl;
}

void menu(electionRound* s)
{
	printMenu();
	bool flag = true;
	while (flag)
	{
		
		int input;
		cin >> input;
		while ((input > twelve) || (input < zero))
		{
			cout << "invalid input, Enter between 1-12" << endl;
			cin >> input;
		}
		try
		{
			switch (input)
			{
			case zero:
				printMenu();
				break;
			case one:
				optionOne(s);
				break;
			case two:
				optionTwo(s);
				break;
			case three:
				optionThree(s);
				break;
			case four:
				optionFour(s);
				break;
			case five:
				optionFive(s);
				break;
			case six:
				optionSix(s);
				break;
			case seven:
				optionSeven(s);
				break;
			case eight:
				optionEight(s);
				break;
			case nine:
				optionNine(s);
				break;
			case ten:
				flag = false;
				break;
			case eleven:
				optionEleven(s);
				break;
			case twelve:
				optionTwelve(s);
				break;

			}
		}
		catch (std::logic_error& ex)
		{
			system("CLS");
			cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
			printMenu();
		}
	}
}

void optionOne(electionRound* s)
{
	if (s->getType() == electionR::simple)
		throw logic_error("simple election, no districts");

	int dType;
	district* res;
	char tmp[100];
	int tmpElec;
	cout << "Enter district name:" << endl;
	cin >> tmp;
	cout << "Enter number of electors:" << endl;
	cin >> tmpElec;
	cout << "enter 0 for unite district or 1 for divided district " << endl;
	cin >> dType;
	try
	{
		checkValidInputDistrict(s, tmp, tmpElec, dType);
		if (dType == 0)
			res = new uniteDis(tmp, tmpElec);
		else
			res = new dividedDis(tmp, tmpElec);
		s->getdArr().push_back(res);
		for (int i = 0; i < s->getpArr().size(); i++) {  //to all existing parties add one more district to consider
			repArr tmprr;
			s->getpArr()[i]->getRepArr().push_back(tmprr);
		}
		system("CLS");
		cout << "district created!" << endl;
		cout << "--------------------" << endl;
		printMenu();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionTwo(electionRound* s)
{
	if (s->getdArr().size() == 0)
		throw logic_error("Error, can't add citizen without district, please add district first");
	
	string tmpName,tmpId;
	int tmpYear, districtSerial;
	cout << "Enter citizen name:" << endl;
	cin >> tmpName;
	cout << "Enter ID, birth year, district serial number:" << endl;
	cin >> tmpId >> tmpYear >> districtSerial;
	if (s->getType() == electionR::simple)   /// for simple election round there is only one district
		districtSerial = 1;
	districtSerial--;
	try
	{
		checkValidInputCitizen(s, tmpName, tmpId, tmpYear, districtSerial);
		citizen* res = new citizen(tmpName, tmpId, tmpYear, s->getdArr()[districtSerial]);
		s->getcArr().push_back(res);
		s->getdArr()[districtSerial]->addCitizen(res);  //adds citizen to it's district citizens array
		system("CLS");
		cout << "citizen created!" << endl << "--------------------" << endl;
		printMenu();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionThree(electionRound* s)
{
	if (s->getcArr().size() == 0)
		throw logic_error("Error, can't add party without citizens, please add citizen first");

	string tmpName,tmpId;
	cout << "Enter party name:" << endl;
	cin >> tmpName;
	cout << "Enter party leader ID:" << endl;
	cin >> tmpId;
	try
	{
		checkValidInputParty(s, tmpName, tmpId);
		party* res = new party(tmpName, s->findCitizen(tmpId), s->getdArr().size());
		s->getpArr().push_back(res);
		s->findCitizen(tmpId)->setAsRep();
		system("CLS");
		cout << "party created!" << endl << "--------------------" << endl;
		printMenu();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionFour(electionRound* s)
{
	if (s->getpArr().size() == 0)
		throw logic_error("Error, can't add representative without parties, please add party first");
	string tmpId;
	int tmpPar, tmpDis;
	cout << "enter new representative ID, party and district" << endl;
	cin >> tmpId >> tmpPar >> tmpDis;
	if (s->getType() == electionR::simple)   /// for simple election round there is only one district
		tmpDis = 1;
	tmpPar--;
	tmpDis--;
	try
	{
		checkValidInputRep(s, tmpId, tmpPar, tmpDis);
		s->getpArr()[tmpPar]->addRep(s->findCitizen(tmpId), tmpDis);
		s->findCitizen(tmpId)->setAsRep();
		system("CLS");
		cout << "representative added!" << endl << "--------------------" << endl;
		printMenu();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionFive(electionRound* s)
{
	if (s->getdArr().size() == 0)
		throw logic_error("there are no districts");
	else
	{
		cout << "List of all districts:" << endl;
		for (int i = 0; i < s->getdArr().size() ; i++)
			cout << *(s->getdArr()[i]) << endl;
		cout << "--------------------" << endl << "to see menu press 0" << endl;
	}
}

void optionSix(electionRound* s)
{
	if (s->getcArr().size() == 0)
		throw logic_error("there are no citizens");
	else
	{
		cout << "List of all citizens:" << endl;
		for (int i = 0; i < s->getcArr().size() ; i++)
			cout << *(s->getcArr()[i]) << endl;
		cout << "--------------------" << endl << "to see menu press 0" << endl;
	}
}

void optionSeven(electionRound* s)
{
	if (s->getpArr().size() == 0)
		throw logic_error("there are no parties");
	else
	{
		cout << "List of all parties:" << endl << endl;
		for (int i = 0; i < s->getpArr().size() ; i++)
			cout << *(s->getpArr()[i]) << endl;
		cout << "--------------------" << endl << "to see menu press 0" << endl;
	}
}

void optionEight(electionRound* s)
{
	if (s->getcArr().size() == 0)
		throw logic_error("there are no citizens");
	int  tmpPar;
	string tmpId;
	cout << "Enter citizen ID and party number to vote " << endl;;
	cin >> tmpId >> tmpPar;
	tmpPar--;
	try
	{
		checkValidInputVote(s, tmpId, tmpPar);

		s->findCitizen(tmpId)->setVote(tmpPar);
		system("CLS");
		cout << "vote has been assigned." << endl << "--------------------" << endl;
		printMenu();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionNine(electionRound* s)
{
	try
	{
		checkNine(s);
		checkRepp(s);

		int tmpNumOfChosen;
		DynamicArray<int> tmpChosen;
		cout << endl;
		cout << "date of election :";
		s->printDate();
		cout << endl;
		cout << "***** SUMMARY BY DISTRICTS *****" << endl;
		for (int i = 0; i < s->getdArr().size(); i++)
		{
			s->getdArr()[i]->initVotesArr(s->getpArr().size());
			int won = s->getdArr()[i]->districtVote();
			cout << "**** " << i + 1 << ". district: " << s->getdArr()[i]->getName() << " ****" << endl;
			s->calcElectors(s->getdArr()[i], tmpChosen);
			if (s->getdArr()[i]->getDtype() == dTypes::unite)  //district is unite
			{
				cout << s->getdArr()[i]->getElectors() << " Electors goes to: " << s->getpArr()[won]->getLeaderName() << endl;
				s->getpArr()[won]->setElectors(s->getpArr()[won]->getElectors() + s->getdArr()[i]->getElectors());
				for (int j = 0; j < s->getpArr().size() ; j++)
				{
					cout << "chosen representatives from party '" << s->getpArr()[j]->getName() << "':" << endl;
					tmpNumOfChosen = tmpChosen[j];
					s->getpArr()[j]->getRepArr()[i].printLim(tmpNumOfChosen);
				}
			}
			else //districts is divided
			{
				for (int k = 0; k < s->getpArr().size() ; k++)
				{
					int maxIndex = 0;
					int max = 0;
					for (int j = 0; j < s->getpArr().size() ; j++)
					{
						if (tmpChosen[j] > max)
						{
							max = tmpChosen[j];
							maxIndex = j;
						}
					}
					if (tmpChosen[maxIndex] > 0)
					{
						cout << tmpChosen[maxIndex] << " Electors goes to: " << s->getpArr()[maxIndex]->getLeaderName() << endl;
						s->getpArr()[maxIndex]->setElectors(s->getpArr()[maxIndex]->getElectors() + tmpChosen[maxIndex]);
						cout << "chosen representatives from party '" << s->getpArr()[maxIndex]->getName() << "':" << endl;
						tmpNumOfChosen = tmpChosen[maxIndex];
						s->getpArr()[maxIndex]->getRepArr()[i].printLim(tmpNumOfChosen);
						tmpChosen[maxIndex] = 0;
					}
				}
			}
			
			for (int k = 0; k < s->getpArr().size() ; k++)
			{
				float percent = (s->getdArr()[i]->getVotes()[k] / s->getdArr()[i]->getCountVotes()) * 100;
				cout << "'" << s->getpArr()[k]->getName() << "'" << " earned " << s->getdArr()[i]->getVotes()[k] << " votes, which is " << percent << "% of district's votes" << endl;
			}
			cout << s->getdArr()[i]->getVotePercent() << "% of district's citizens have voted" << endl;
		}
		s->setVotesForParty();
		s->sortPArr();
		cout << endl;
		cout << "***** SUMMARY BY PARTIES *****" << endl;
		for (int i = 0; i < s->getpArr().size(); i++)  //for each party
		{
			if (i == 0)
				cout << "the winner is: ";
			cout << "****" << s->getpArr()[i]->getLeaderName() << "****" << endl;  //prints party's leader name
			cout << "head of '" << s->getpArr()[i]->getName() << "'" << endl;
			cout << "number of electors: " << s->getpArr()[i]->getElectors() << ", number of votes: " << s->getpArr()[i]->getVotes() << endl;   //prints number of electors from all districts
		}
		cout << "round of election completed, reseting all data" << endl;
		s->reset();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionEleven(electionRound* s)
{
	char fileName[SIZE];
	cout << "please enter file name" << endl;
	cin >> fileName;
	ofstream outFile(fileName, ios::binary);
	try
	{
		s->save(outFile);
		outFile.close();
		if (!outFile.good())
			throw fileError();
		system("CLS");
		cout << "saving succeed" << endl << "--------------------" << endl;
		printMenu();
	}
	catch (std::exception& ex)
	{
		system("CLS");
		cout << "ERROR: " << ex.what() << endl << "--------------------" << endl;
		printMenu();
	}
}

void optionTwelve(electionRound* s)
{
	char fileName[SIZE];
	cout << "please enter file name" << endl;
	cin >> fileName;
	ifstream inFile(fileName, ios::binary);
	if (!inFile)
		throw invalid_argument("invalid File");
	else
	{
		s->load(inFile);
		inFile.close();
		system("CLS");
		cout << "loading succeed" << endl << "--------------------" << endl;
		printMenu();
	}
}

void checkValidInputCitizen(electionRound* s, string _name, string _id, int _year, int disSerial)
{
	if (_name.size() < 1)
		throw logic_error("Invalid name");

	if ((_id.size() != 9) || s->citizenExist(_id))
		throw logic_error("Invalid ID or citizen already has this ID");

	if (s->getYear() - _year < 18)
		throw logic_error("Invalid birth year");

	if ((disSerial >= s->getdArr().size()) || (disSerial < 0))  //Districts range between 0- districts logical size
		throw logic_error("Invalid district serial");
}

void checkValidInputDistrict(electionRound* s, string _name, int _electors, int dType)
{
	if (_name.size() < 1)
		throw logic_error("Invalid name");

	if (_electors < 1)
		throw logic_error("Invalid amount of electors");

	if (dType != 0 && dType != 1)
		throw logic_error("invalid district type");
}

void checkValidInputParty(electionRound* s, string _name, string _leaderId)
{
	if (_name.size() < 1)
		throw logic_error("Invalid name");

	if ((_leaderId.size()!= 9) || (!(s->citizenExist(_leaderId))))
		throw logic_error("Invalid ID or it belongs to no one");

	if (s->findCitizen(_leaderId)->getIsRep() == true)
		throw logic_error("already representative");
}

void checkValidInputRep(electionRound* s, string _id, int _party, int _district)
{
	if ((_id.size()!= 9) || (!(s->citizenExist(_id))))
		throw logic_error("Invalid ID or it belongs to no one");

	if ((_party < 0) || (_party > s->getpArr().size()))
		throw logic_error("Invalid Party Number");

	if ((_district < 0) || (_district > s->getdArr().size()))
		throw logic_error("Invalid district Number");

	if (s->findCitizen(_id)->getIsRep() == true)
		throw logic_error("already representative");
}

void checkValidInputVote(electionRound* s, string _id, int _party)
{
	if ((_party < 0) || (_party > s->getpArr().size() ))
		throw logic_error("Invalid party number");

	citizen* tmpCit = s->findCitizen(_id);
	if (tmpCit == nullptr)
		throw logic_error("this citizen doesn't exist");

	if (tmpCit->getVote() != -1)
		throw logic_error("this citizen already voted");
}

void checkRepp(electionRound* s)
{
	if (s->getpArr().size()  == 0)
	{
		throw logic_error("there is no parties");

		for (int i = 0; i < s->getpArr().size() ; i++)
		{
			for (int j = 0; j < s->getdArr().size() ; j++)
			{
				if (s->getpArr()[i]->getRepArr()[j].getArr().size() < s->getdArr()[j]->getElectors())
					throw logic_error("there are not enough representatives");

			}
		}
	}
}

void checkNine(electionRound* s)
{
	int i, j = 0;
	bool flag;
	if (s->getdArr().size() == 0)
		throw logic_error("there are no districts");

	for (i = 0; i < s->getdArr().size() ; i++)
	{
		flag = false;
		while (j < s->getdArr()[i]->getCitArr().size() && !flag)
		{
			if (s->getdArr()[i]->getCitArr()[j]->getVote() != -1)
				flag = true;
			j++;
		}
		if (!flag)
		{
			throw logic_error("no citizen has voted in some district");
		}
	}
}
