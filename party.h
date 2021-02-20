#pragma once
#include "repArr.h"
#pragma warning (disable: 4996)
#include <iostream>
using namespace std;

namespace election 
{
	class party
	{
	private:
		static int pCounter;
		int parSerial = ++pCounter;
		string name ;
		citizen* leader = nullptr;
		string leadersId;
		int votes = 0;
		DynamicArray<repArr> arr;
		int electors = 0;
	public:
		party() {}
		party(string _name, citizen* _leader, int numOfDistricts);
		party(const party& other) { *this = other; }
		~party() {}

		//*********Getters********//
		string getName() const { return name; }
		citizen* getLeader() const { return leader; }
		int getElectors() const { return electors; }
		int getSerial() const { return parSerial; }
		string getLeadersId() const { return leadersId; }
		int getVotes() const { return votes; }
		DynamicArray<repArr>& getRepArr() { return arr; }
		

		//*********Setters********//
		void setName(string _name);
		void setID(string _id);
		void setLeader(citizen* _leader) { leader = _leader; }
		void setElectors(int x) { electors = x; }
		void zeroCounter() { pCounter = 0; }
		void setVotes(int x) { votes += x; }

		//*****General Methods****//
		string getLeaderName() { return getLeader()->getName(); }
		void addRep(citizen* cit, int _district) { arr[_district].addRep(cit); }
		friend ostream& operator<<(ostream& os, party& party);
		void operator=(const party& other);

		void save(ostream& out) const;
		void load(istream& in);
	};

	
}
