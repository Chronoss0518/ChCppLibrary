
#include"../../../BaseIncluder/ChBase.h"
#include"../../ChBitBool/ChBitBool.h"

#include"../ChBaseCompressor.h"
#include"../../../External/zlib/zlib.h"
#include"ChDeflateCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//DeflateCompressorÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> Deflate::Compress(const std::vector<unsigned char>& _compressBase)
{
	if (_compressBase.size() <= 0)return _compressBase;

	std::map<unsigned char, ChPtr::Shared<BitBool>> tree;

	std::vector<unsigned char> out;

	for (unsigned long i = 0; i < _compressBase.size(); i++)
	{

	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> Deflate::Decompress(const std::vector<unsigned char>& _decompressBase)
{
	if (_decompressBase.size() <= 0)return _decompressBase;

	std::vector<unsigned char> out;

	for (unsigned long i = 0; i < _decompressBase.size(); i++)
	{

	}

	return out;
}

