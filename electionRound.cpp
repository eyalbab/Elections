#include "electionRound.h"
using namespace std;
namespace election
{
	electionRound::electionRound(int day, int month, int year, electionR type) : day(day), month(month), year(year), type(type)
	{
		if (type == electionR::simple)
			dArr.push_back(new dividedDis("state", 1));
	}
	
	bool electionRound::citizenExist(string _id)
	{
		for (int i = 0; i < cArr.size() ; i++)
		{
			if (cArr[i]->getId().compare(_id)==0)
				return true;
		}
		return false;
	}
	citizen* electionRound::findCitizen(string _id)
	{
		_id.resize(idSize);
		for (int i = 0; i < cArr.size(); i++)
		{
			if (cArr[i]->getId().compare(_id) == 0)
				return cArr[i];
		}
		return nullptr;
	}
	void electionRound::calcElectors(district* dis, DynamicArray<int>& res)
	{
		int tmpLs = dis->getVotes().size();
		int tmpElector = dis->getElectors();
		int maxModulu = 0;
		float electorPer = dis->getCountVotes() / dis->getElectors();
		int electorPerInt = static_cast<int>(electorPer);
		DynamicArray<int> tmpVotes(tmpLs);
		tmpVotes = dis->getVotes();
		for (int i = 0; i < tmpLs; i++)
		{
			res[i] = static_cast<int>(tmpVotes[i] / electorPer);
			tmpElector = tmpElector - res[i];
		}
		while (tmpElector > 0)
		{
			for (int j = 1; j < tmpLs; j++)
			{
				if ((tmpVotes[j] % (electorPerInt+1)) > (tmpVotes[maxModulu] % (electorPerInt+1)))
					maxModulu = j;
			}
			res[maxModulu]++;
			tmpVotes[maxModulu] = 0;
			tmpElector--;
			maxModulu = 0;
		}
		
	}
	void electionRound::sortPArr()
	{
		for (int i = 0; i < pArr.size() - 1 ; i++)
		{
			for (int j = 0; j < pArr.size() - i - 1; j++)
			{
				if (pArr[j]->getElectors() < pArr[j + 1]->getElectors())
				{
					party* tmp = pArr[j];
					pArr[j] = pArr[j + 1];
					pArr[j + 1] = tmp;
				}
			}
		}
	}
	void electionRound::reset()
	{
		dArr[0]->zeroCounter();
		pArr[0]->zeroCounter();
		for (int i = 0; i < cArr.size(); i++)
		{
			delete cArr[i];
		}
		for (int i = 0; i < dArr.size() ; i++)
		{
			delete dArr[i];
		}
		for (int i = 0; i < pArr.size(); i++)
		{
			delete pArr[i];
		}
		cArr.clear();
		dArr.clear();
		pArr.clear();
	}
	void electionRound::save(ostream& out) const
	{
		out.write(rcastcc(&type), sizeof(type));
		out.write(rcastcc(&day), sizeof(day));
		out.write(rcastcc(&month), sizeof(month));
		out.write(rcastcc(&year), sizeof(year));
		int tmpcLs = cArr.size();
		out.write(rcastcc(&tmpcLs), sizeof(tmpcLs));
		int tmpdLs = dArr.size();
		out.write(rcastcc(&tmpdLs), sizeof(tmpdLs));
		int tmppLs = pArr.size();
		out.write(rcastcc(&tmppLs), sizeof(tmppLs));
		for (int i = 0; i < tmpdLs; i++)
			dArr[i]->save(out);
		for (int i = 0; i < tmppLs; i++)
			pArr[i]->save(out);
		if (!out.good())
			throw fileError();
	}
	void electionRound::load(istream& in)
	{
		int cLs, dLs, pLs;
		in.read(rcastc(&type), sizeof(type));
		in.read(rcastc(&day), sizeof(day));
		in.read(rcastc(&month), sizeof(month));
		in.read(rcastc(&year), sizeof(year));
		in.read(rcastc(&cLs), sizeof(cLs));
		in.read(rcastc(&dLs), sizeof(dLs));
		in.read(rcastc(&pLs), sizeof(pLs));
		int tmpLs,citCounter=0;
	
		for (int i = 0; i < dLs ; i++)
		{
			dTypes tmpType;
			in.read(rcastc(&tmpType), sizeof(tmpType));
			if (tmpType == dTypes::divided)
			{
				district* tmpDis = new dividedDis();
				tmpDis->load(in);
				dArr.push_back(tmpDis);
			}
			else   // unite district
			{
				district* tmpDis = new uniteDis();
				tmpDis->load(in);
				dArr.push_back(tmpDis);
			}
			tmpLs = dArr[i]->getCitArr().size();
			for (int j = 0; j < tmpLs; j++)                                  
				cArr.push_back(dArr[i]->getCitArr()[j]);
		}

		for (int i = 0; i < pLs; i++)
		{
			party* tmpPar = new party();
			tmpPar->load(in);
			pArr.push_back(tmpPar);
		}
		setRepAfterLoad();
	}
	void electionRound::setVotesForParty()
	{
		for (int i = 0; i < dArr.size(); i++)
		{
			for (int j = 0; j < dArr[i]->getVotes().size(); j++)
				pArr[j]->setVotes(dArr[i]->getVotes()[j]);
			
		}
	}
	void electionRound::setRepAfterLoad()   ///after loading a file this method will match pointer to citizen
	{
		for (int i = 0; i < pArr.size(); i++)
		{
			pArr[i]->setLeader(findCitizen(pArr[i]->getLeadersId()));
			for (int j = 0; j < dArr.size(); j++)
			{
				int tmpsize = pArr[i]->getRepArr()[j].getIdArr().size();
				for (int k = 0; k < tmpsize; k++)
				{
					citizen* tmpRep = findCitizen(pArr[i]->getRepArr()[j].getId(k));
					pArr[i]->getRepArr()[j].getArr().push_back(tmpRep);
				}
			}
		}
	}
	void electionRound::operator=(const electionRound& other)
	{
		day = other.day;
		month = other.month;
		year = other.year;
		cArr = other.cArr;
		dArr = other.dArr;
		pArr = other.pArr;
	}
}