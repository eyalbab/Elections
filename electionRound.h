#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include "uniteDis.h"
#include "dividedDis.h"
#include "citizen.h"
#include "party.h"
#include "repArr.h"

enum class electionR { regular, simple };
using namespace std;
namespace election
{
	class electionRound
	{
	protected:
		int day=1, month=1, year=2021;
		DynamicArray<citizen*> cArr;					//general citizen* array+logical\physical size
		DynamicArray<district*> dArr;					//general district* array+logical\physical size
		DynamicArray<party*> pArr;						//general party* array+logical\physical size
		electionR type = electionR::regular;
	
	public:
		electionRound() {}
		electionRound(int day, int month, int year, electionR type);
		electionRound(const electionRound& other) { *this = other; }
		~electionRound() {}

		//*********Getters**********//
		int getYear() const { return year; }
		DynamicArray<citizen*>& getcArr() { return cArr; }
		DynamicArray<district*>& getdArr() { return dArr; }
		DynamicArray<party*>& getpArr() { return pArr; }
		electionR getType() const { return type; }

		//******Finders******//
		bool citizenExist(string _id);
		citizen* findCitizen(string _id);
		
		//*******Others*******//
		void calcElectors(district* dis, DynamicArray<int>& res);
		void sortPArr();
		void reset();
		void setVotesForParty();
		void setRepAfterLoad();
		void save(ostream& out) const;
		void load(istream& in);
		void printDate() { cout << " " << day << "/" << month << "/" << year; }
		void operator=(const electionRound& other);
	};

}