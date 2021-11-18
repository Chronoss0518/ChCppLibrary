
#include"..././../BaseIncluder/ChBase.h"
#include"../../ChBitBool/ChBitBool.h"

#include"../ChBaseCompressor.h"
#include"ChCharactorRunglessCompressor.h"

using namespace ChCpp;
using namespace Cmp;


///////////////////////////////////////////////////////////////////////////////////
//RunglessCompressorÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorRungless::Press(const std::vector<unsigned char>& _pressBase)
{

	if (_pressBase.size() <= 0)return _pressBase;

	ChPtr::Shared<Memo> memo = nullptr;

	std::vector<ChPtr::Shared<Memo>>memos;

	for (unsigned long i = 0; i < _pressBase.size(); i++)
	{
		if (i <= 0)
		{
			memo = nullptr;
			memo = ChPtr::Make_S<Memo>();
			memo->datas = _pressBase[i];
		}
		else if (memo->datas != _pressBase[i])
		{
			memos.push_back(memo);
			memo = nullptr;
			memo = ChPtr::Make_S<Memo>();
			memo->datas = _pressBase[i];
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

	return out.size() < _pressBase.size() ? out : _pressBase;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorRungless::Thaw(const std::vector<unsigned char>& _thawBase)
{
	if (_thawBase.size() < 3)return _thawBase;

	std::vector<unsigned char> out;

	for (unsigned long i = 0; i < _thawBase.size(); i++)
	{
		if (_thawBase[i] < 128 || _thawBase[i] > 131)
		{
			out.push_back(_thawBase[i]);
			continue;
		}

		unsigned char byteSize = (_thawBase[i] & (3)) + 1;

		i++;

		unsigned long count = 0;

		void* tmp = &count;
		for (char j = 0; j < byteSize; j++)
		{
			*(static_cast<unsigned char*>(tmp) + (byteSize - j - 1)) = _thawBase[i + j];
		}

		i += byteSize;
		unsigned char datas = _thawBase[i];

		for (unsigned long j = 0; j < count; j++)
		{
			out.push_back(datas);
		}
	}


	return out;
}
