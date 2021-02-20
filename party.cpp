#pragma warning (disable: 4996)
#include "party.h"

namespace election
{
	int party::pCounter;
	
	party::party(string _name, citizen* _leader,int numOfDistricts)
	{
		setName(_name);
		setLeader(_leader);
		repArr tmp;
		for (int i = 0; i < numOfDistricts; i++)
			arr.push_back(tmp);
	}

	void party::setName(string _name)
	{
		name.assign(_name);
	}
	void party::setID(string _id)
	{
		leadersId.assign(_id);
	}
	
	ostream& operator<<(ostream& os, party& party)
	{
		os << party.getSerial() << ". Party name:" << party.getName() << endl << "party's leader:" << party.getLeaderName() << endl;
		for (int i = 0; i < party.arr.size() ; i++)
		{
			cout << "Representatives for district " << i + 1 <<":" << endl;
			party.getRepArr()[i].printAll();
		}
		return os;
	}
	void party::save(ostream& out) const
	{
		string tmpId = leader->getId();
		out.write(rcastcc(&parSerial), sizeof(parSerial));
		int len1 = name.size(),len2= tmpId.size();
		out.write(rcastcc(&len1), sizeof(len1));  //length of name
		out.write(&name[0], len1);
		out.write(rcastcc(&len2), sizeof(len2));
		out.write(&tmpId[0], len2);
		int size = arr.size();
		out.write(rcastcc(&size), sizeof(size));
		for (int i = 0; i < size ; i++)
		{
			if (arr[i].getSize() != 0)
				arr[i].save(out);
			else 
			{
				repArr tmpArr;
				tmpArr.save(out);
			}
		}
		if (!out.good())
			throw fileError();
	}
	void party::load(istream& in)
	{
		in.read(rcastc(&parSerial), sizeof(parSerial));
		int len1, len2, size;
		in.read(rcastc(&len1), sizeof(len1));  //length of name
		name.resize(len1);
		in.read(&name[0], len1);
		in.read(rcastc(&len2), sizeof(len2));  //length of ID
		leadersId.resize(len2);
		in.read(&leadersId[0], len2);
		in.read(rcastc(&size), sizeof(size));
		for (int i = 0; i < size; i++)
		{
			repArr* tmpRep = new repArr;
			tmpRep->load(in);
			arr.push_back(*tmpRep);
		}
	}

	void party::operator=(const party& other)
	{
		parSerial = other.parSerial;
		setName(other.name);
		leader = other.leader;
		setID(other.leadersId);
		votes = other.votes;
		arr = other.arr;
		electors = other.electors;
		pCounter--;
	}
}