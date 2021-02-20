#include "dividedDis.h"

namespace election 
{
	void dividedDis::save(ostream& out) const
	{
		out.write(rcastcc(&type), sizeof(type));
		district::save(out);
		if (!out.good())
			throw fileError();
	}
	void dividedDis::load(istream& in)
	{
		district::load(in);
	}

	void dividedDis::operator=(const dividedDis& other)
	{
		district::operator=(other);
		type = other.type;
	}
}