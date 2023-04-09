
#include"../../BaseIncluder/ChBase.h"
#include"../ChBitBool/ChBitBool.h"

#include"ChBaseCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//CompressorFunction
///////////////////////////////////////////////////////////////////////////////////

unsigned long Cmp::CreateAdler32(const std::vector<unsigned char>& _base)
{
	unsigned short a = 1;
	for (auto&& num : _base)
	{
		unsigned short tmp = a;
		tmp += num;
		tmp %= 0xffff;
		a = tmp;
	}

	unsigned short b = 0;
	for (unsigned long i = 0;i<_base.size();i++)
	{
		unsigned short tmp = b;

		tmp += 1;
		for (unsigned short j = 0; j <= i; j++)
		{
			tmp += _base[j];
		}

		tmp %= 0xffff;
		b = tmp;
	}

	unsigned long out = (b << 16) + a;

	return out;
}