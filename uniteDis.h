#pragma once
#include "district.h"
using namespace std;

namespace election
{
	class uniteDis :public district
	{
	private:
		dTypes type = dTypes::unite;
	public:
		uniteDis() : district() {}
		uniteDis(const char* name, int electors) : district(name, electors) {}
		uniteDis(const uniteDis& other) { *this = other; }
		~uniteDis() {}
		virtual dTypes getDtype() const { return type; }
		virtual void ToOs(ostream& os) const override { os << "district type: unite" << endl; }
		void operator=(const uniteDis& other);
		virtual void save(ostream& out) const;
		virtual void load(istream& in);
	};
}
