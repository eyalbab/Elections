#include "uniteDis.h"

namespace election
{
	void uniteDis::save(ostream& out) const
	{
		out.write(rcastcc(&type), sizeof(type));
		district::save(out);
		if (!out.good())
			throw fileError();
	}
	void uniteDis::load(istream& in)
	{
		district::load(in);
	}

	void uniteDis::operator=(const uniteDis& other)
	{
		district::operator=(other);
		type = other.type;
	}
}