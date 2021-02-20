#pragma once
#include "citizen.h"
#include <iostream>
using namespace std;

namespace election
{
	class repArr
	{
	private:
		DynamicArray<citizen*> arr;
		DynamicArray<string> idArr;
	public:
		repArr() {}
		repArr(const repArr& other) { *this = other; }
		~repArr() {}
		//*****getters*****//
		DynamicArray<citizen*>& getArr() { return arr; }
		DynamicArray<string>& getIdArr() { return idArr; }
		string getId(int indx) const { return (idArr[indx]); }
		int getSize() const { return arr.size(); }

		//*****setters*****//
		void setRep(int i, citizen* rep) { arr[i] = rep; }

		//*****others*****//
		void enlargeArr();
		void addRep(citizen* cit) { arr.push_back(cit); }
		void printLim(int lim);
		void printAll();
		void operator=(const repArr& other);
		
		//*****files*****//
		void save(ostream& out) const;
		void load(istream& in);
	};
}