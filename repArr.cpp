#include "repArr.h"

namespace election
{
	void repArr::printLim(int lim)
	{
		for (int i = 0; i < lim; i++)
			cout << arr[i]->getName() << endl;
	}
	void repArr::printAll()
	{
		for (int i = 0; i < arr.size() ; i++)
			cout << arr[i]->getName() << endl;
	}
	void repArr::save(ostream& out) const
	{
		int size = arr.size();
		out.write(rcastcc(&size), sizeof(size));
		for (int i = 0; i < size ; i++)
		{
			string id;
			id.assign(arr[i]->getId());
			out.write(&id[0], id.size());
		}
		if (!out.good())
			throw fileError();
	}
	void repArr::load(istream& in)
	{
		string tmp;
		int size;
		in.read(rcastc(&size), sizeof(size));
		for (int i = 0; i < size; i++)
		{
			in.read(&tmp[0], idSize);
			getIdArr().push_back(&tmp[0]);
		}
	}
	void repArr::operator=(const repArr& other)
	{
		arr = other.arr;
		idArr = other.idArr;
	}
}