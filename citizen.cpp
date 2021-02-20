#pragma warning (disable: 4996)
#include "district.h"
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace election
{
	citizen::citizen(string _name, string _id, int _birthYear, district* _district) :birthYear(_birthYear)
	{
	
		setId(_id);
		setName(_name);
		this->dis = _district;
	}
	void citizen::setName(string _name)
	{
		name.assign(_name);
	}

	void citizen::save(ostream& out) const
	{
		int len = name.size(),len2=id.size();
		out.write(rcastcc(&len), sizeof(len));  //length of name
		out.write(&name[0], len);
		out.write(rcastcc(&len2), sizeof(len2));//length of id string
		out.write(rcastcc(&id[0]), len2);
		out.write(rcastcc(&birthYear), sizeof(birthYear));
		out.write(rcastcc(&voted), sizeof(voted));
		out.write(rcastcc(&isRep), sizeof(isRep));
		if (!out.good())
			throw fileError();
	}

	void citizen::load(istream& in)
	{
		int len1,len2;
		in.read(rcastc(&len1), sizeof(len1));  //length of name
		name.resize(len1);
		in.read(&name[0], len1);
		in.read(rcastc(&len2), sizeof(len2));  //length of ID
		id.resize(len2);
		in.read(rcastc(&id[0]), len2);
		in.read(rcastc(&birthYear), sizeof(birthYear));
		in.read(rcastc(&voted), sizeof(voted));
		in.read(rcastc(&isRep), sizeof(isRep));
	}

	ostream& operator<<(ostream& os, const citizen& cit)
	{
		os << "name:" << cit.getName() << endl << "ID num:" << cit.getId() << endl
			<< "Birth year:" << cit.getBirthYear() <<endl<< "District:" << cit.dis->getName() << endl;

		return os;
	}
	void citizen::operator=(const citizen& other)
	{
		setName(other.getName());
		setId(other.getId());
		setBirthId(other.getBirthYear());
		setDistrict(other.getDistrict());
		setVote(other.getVote());
		setIsRep(other.getIsRep());
	}
}