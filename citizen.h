#pragma once
#pragma warning (disable: 4996)
#include <string>
#include <iostream>
#include "DynamicArray.h"
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#define idSize 9

class fileError : public exception {
public:
	const char* what() { "saving failed"; }
};

namespace election
{
	class district;
	class citizen
	{
	private:
		string name;
		string id;
		int birthYear = 0;
		district* dis = nullptr;
		mutable int voted = -1;   //citizen's vote:-1=not voted, else voted party with serial number=voted
		mutable bool isRep = false;
	
	public:
		citizen() {}
		citizen(string _name, string _id, int _birthYear, district* _district);
		citizen(const citizen& other) { *this = other; }
		~citizen() {}

		//********Getters**********//
		string getName() const { return name; }
		string getId() const { return id; }
		int getBirthYear() const { return birthYear; }
		int getVote() const { return voted; }
		bool getIsRep() const { return isRep; }
		district* getDistrict()const { return dis; }

		//*********Setters*********//
		void setId(string _id) { id.assign(_id); }
		void setBirthId(int _bYear) { birthYear = _bYear; }
		void setName(string _name);
		void setDistrict(district* _dis) { dis = _dis; }
		void setVote(int vote)  { voted = vote; }
		void setIsRep(int isRep) { isRep = isRep; }

		void setAsRep()  { isRep = true; }
		
		void save(ostream& out) const;
		void load(istream& in);

		void operator=(const citizen& other);
		friend ostream& operator<<(ostream& os, const citizen& cit);
	};
}