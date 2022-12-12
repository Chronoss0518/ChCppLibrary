
#include"../../../BaseIncluder/ChBase.h"
#include"../../ChBitBool/ChBitBool.h"

#include"../ChBaseCompressor.h"
#include"ChCharactorRunglessCompressor.h"

using namespace ChCpp;
using namespace Cmp;


///////////////////////////////////////////////////////////////////////////////////
//RunglessCompressorÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorRungless::Compress(const std::vector<unsigned char>& _compressBase)
{

	if (_compressBase.size() <= 0)return _compressBase;

	ChPtr::Shared<Memo> memo = nullptr;

	std::vector<ChPtr::Shared<Memo>>memos;

	for (unsigned long i = 0; i < _compressBase.size(); i++)
	{
		if (i <= 0)
		{
			memo = nullptr;
			memo = ChPtr::Make_S<Memo>();
			memo->datas = _compressBase[i];
		}
		else if (memo->datas != _compressBase[i])
		{
			memos.push_back(memo);
			memo = nullptr;
			memo = ChPtr::Make_S<Memo>();
			memo->datas = _compressBase[i];
		}
		memo->count++;
	}
	memos.push_back(memo);

	std::vector<unsigned char> out;


	for (auto&& obj : memos)
	{
		if (obj->count <= 1)
		{
			out.push_back(obj->datas);
			continue;
		}

		unsigned char byteSize = obj->count < 0xffU ? 1 : obj->count < 0xffffU ? 2 : 4;

		out.push_back(128 + (byteSize - 1));

		void* tmp = &obj->count;

		for (char i = byteSize - 1; i >= 0; i--)
		{
			out.push_back(*(static_cast<unsigned char*>(tmp) + i));
		}

		out.push_back(obj->datas);
	}

	return out.size() < _compressBase.size() ? out : _compressBase;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorRungless::Decompress(const std::vector<unsigned char>& _decompressBase)
{
	if (_decompressBase.size() < 3)return _decompressBase;

	std::vector<unsigned char> out;

	for (unsigned long i = 0; i < _decompressBase.size(); i++)
	{
		if (_decompressBase[i] < 128 || _decompressBase[i] > 131)
		{
			out.push_back(_decompressBase[i]);
			continue;
		}

		unsigned char byteSize = (_decompressBase[i] & (3)) + 1;

		i++;

		unsigned long count = 0;

		void* tmp = &count;
		for (char j = 0; j < byteSize; j++)
		{
			*(static_cast<unsigned char*>(tmp) + (byteSize - j - 1)) = _decompressBase[i + j];
		}

		i += byteSize;
		unsigned char datas = _decompressBase[i];

		for (unsigned long j = 0; j < count; j++)
		{
			out.push_back(datas);
		}
	}


	return out;
}
