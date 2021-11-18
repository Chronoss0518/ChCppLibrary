
#include"../../BaseIncluder/ChBase.h"
#include"../ChBitBool/ChBitBool.h"

#include"ChBaseCompressor.h"
#include"ChDeflateCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//DeflateCompressorÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> Deflate::Press(const std::vector<unsigned char>& _pressBase)
{
	if (_pressBase.size() <= 0)return _pressBase;

	std::map<unsigned char, ChPtr::Shared<BitBool>> tree;

	std::vector<unsigned char> out;

	for (unsigned long i = 0; i < _pressBase.size(); i++)
	{

	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> Deflate::Thaw(const std::vector<unsigned char>& _thawBase)
{
	if (_thawBase.size() <= 0)return _thawBase;

	std::vector<unsigned char> out;

	for (unsigned long i = 0; i < _thawBase.size(); i++)
	{

	}

	return out;
}

