#pragma once
#include "district.h"
using namespace std;

namespace election
{
	class dividedDis :public district
	{
	private:
		dTypes type = dTypes::divided;
	public:
		//*****c'tors*****//
		dividedDis() : district() {}
		dividedDis(const char* name, int electors) : district(name, electors) {}
		dividedDis(const dividedDis& other) { *this = other; }
		//*****d'tor*****//
		~dividedDis() {}

		//*****other*****//
		virtual dTypes getDtype() const { return type; }
		virtual void ToOs(ostream& os) const override { os << "district type: divided" << endl; }
		void operator=(const dividedDis& other);

		//*****Files*****//
		virtual void save(ostream& out) const;
		virtual void load(istream& in);
	};
}
