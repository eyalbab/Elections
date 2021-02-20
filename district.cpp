#pragma warning (disable: 4996)
int minimum(int a, int b)
{
	return (a < b ? a : b);
}
#include "district.h"

namespace election
{
	int district::dCounter;
	district::district(string name, int electors) : countVotes(0) 
	{
		setName(name);
		this->electors = electors;
	}
	void district::setName(string _name)
	{
		name.assign(_name);
	}
	
	void district::addCitizen(citizen* newCit)
	{
		arr.push_back(newCit);
	}
	ostream& operator<<(ostream& os,district& dis)
	{
		os <<dis.getSerial()<<".name: " << dis.getName() << endl << "Number of electors:" << dis.getElectors() << endl; 
		dis.ToOs(os);
		return os;
	}
	citizen* district::findCitizen(string id) const
	{
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i]->getId().compare(id) == 0)
				return arr[i];
		}
		return nullptr;
	}
	void district::initVotesArr(int size)
	{
		for (int i = 0; i < size; i++)
		{
			votes.push_back(0);
		}
	}
	int district::districtVote()
	{
		int maxIndex = 0;
		for (int i = 0; i < arr.size() ; i++)
		{
			int v = arr[i]->getVote();
			if (v != -1)
			{
				votes[v]++;
				setCountVotes(getCountVotes()+1);
				setVotePercent((getCountVotes() / arr.size() )*100);
				if (votes[v] > votes[maxIndex])
					maxIndex = v;
				else if (votes[v] == votes[maxIndex])
					maxIndex = minimum(v, maxIndex);
			}
		}
		return maxIndex;
	}
	void district::save(ostream& out) const
	{
		out.write(rcastcc(&serial), sizeof(serial));
		int len = name.size();
		out.write(rcastcc(&len), sizeof(len));  //length of name
		out.write(&name[0], len);
		out.write(rcastcc(&electors), sizeof(electors));
		int size = arr.size();
		out.write(rcastcc(&size), sizeof(size));
		for (int i = 0; i < size ; i++) 
			arr[i]->save(out);
		if (!out.good())
			throw fileError();
	}

	void district::load(istream& in)
	{
		in.read(rcastc(&serial), sizeof(serial));
		int len = 0;
		in.read(rcastc(&len), sizeof(len));  //length of name
		name.resize(len);
		in.read(&name[0], len);
		in.read(rcastc(&electors), sizeof(electors));
		int size;
		in.read(rcastc(&size), sizeof(size));
		for (int i = 0; i < size ; i++)
		{
			citizen* tmpC = new citizen();
			tmpC->load(in);
			tmpC->setDistrict(this);
			arr.push_back(tmpC);
		}
		
	}
	void district::operator=(const district& other)
	{
		serial = other.serial;
		setName(other.name);
		electors = other.electors;
		arr = other.arr;
		votes = other.votes;
		countVotes = other.countVotes;
		votePercent = other.votePercent;
		type = other.type;
		dCounter--;
	}
}