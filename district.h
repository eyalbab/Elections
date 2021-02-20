#pragma once
#pragma warning (disable: 4996)
using namespace std;
#include "citizen.h"
enum class dTypes { unite, divided };
namespace election
{
	class citizen;
	class district
	{
	protected:
		static int dCounter;    //amount of districts counter
		int serial= ++dCounter;
		string name;
		int electors = 0;	        //amount of electors the district is given
		DynamicArray<citizen*> arr;    //array of district's citizens*
		DynamicArray<int> votes;	    //array of votes arranged by party serial number
		float countVotes = 0.0;           //current overall votes count
		float votePercent = 0.0;
		dTypes type = dTypes::unite;

	public:
		district() {}
		district(string name, int electors);
		district(const district& other) { *this = other; }
		virtual ~district() {}

		//*********Getters***********//
		string getName() const {return name; }
		int getElectors() const { return electors; }
		int getSerial() const { return serial; }
		DynamicArray<int>& getVotes() { return votes; }
		float getCountVotes() const { return countVotes; }
		float getVotePercent() const { return votePercent; }
		DynamicArray<citizen*>& getCitArr() { return arr; }
		virtual dTypes getDtype() const { return type; }

		//**********Setters**********//
		void seSerial(int num) { serial = num; }
		void setName(string _name);
		void setElectors(int x) { electors = x; }
		void setCountVotes(float x) { countVotes = x; }
		void setVotePercent(float x) { votePercent = x; }
		void setType(dTypes type) { type = type; }

		//**********init**********//
		void zeroCounter() { dCounter = 0; }
		void initVotesArr(int size);
		//
		virtual void save(ostream& out) const;
		virtual void load(istream& in);

		//***********Others**********//
		citizen* findCitizen(string id) const;    //if citizen exist in the district return ptr,else return nullptr
		int districtVote();              //updates votes arr, returns serial number of max voted party
		void addCitizen(citizen* newCit);
		friend ostream& operator<<(ostream& os, district& dis);
		void operator=(const district& other);
		virtual void ToOs(ostream& os) const = 0;
	};
}
