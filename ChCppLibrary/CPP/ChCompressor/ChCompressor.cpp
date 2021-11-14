
#include"../../BaseIncluder/ChBase.h"
#include"../ChBitBool/ChBitBool.h"

#include"ChBaseCompressor.h"
#include"ChCharactorHuffmanTreeCompressor.h"
#include"ChDeflateCompressor.h"
#include"ChCharactorRunglessCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//HuffmanTreeCompressorメソッド
///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorHuffmanTree::Press(const std::vector<unsigned char>& _pressBase)
{
	if (_pressBase.size() <= 0)return _pressBase;

	std::map<unsigned char, unsigned long>trees;

	unsigned long counter = 0;

	for (unsigned long i = 0; i < _pressBase.size(); i++)
	{
		trees[_pressBase[i]]++;
		counter++;
	}

	unsigned long maxBitSize = trees.size();

	std::map<unsigned char,unsigned long>bitData;
	std::vector<unsigned char>line;

	{
		unsigned char charas = 0;
		unsigned long max = 0;

		for (unsigned long i = 0; i < trees.size(); i++)
		{
			charas = 0;
			max = 0;

			for (auto&& obj : trees)
			{
				if (max > obj.second)continue;
				charas = obj.first;
				max = obj.second;
			}

			bitData[charas] = i + 1;
			line.push_back(charas);

			trees[charas] = 0;

		}
	}

	std::vector<unsigned char> out;

	{
		unsigned char createObj = 0;
		unsigned char pos = 0;
		unsigned long size = 0;
		for (unsigned long i = 0; i < _pressBase.size(); i++)
		{
			size = bitData[_pressBase[i]];
			unsigned char now = _pressBase[i];

			if (pos > 7)
			{
				out.push_back(createObj);
				createObj = 0;
				pos = 0;
			}

			unsigned char tmp = (8 - pos);

			if (tmp >= size)
			{
				createObj <<= size;
				createObj |= 1;
				pos += size;
				continue;
			}

			createObj <<= tmp;

			out.push_back(createObj);

			size -= (tmp);

			for (unsigned long j = 0; j < static_cast<unsigned long>((size - 1) / 8); j++)
			{
				out.push_back(0);
			}
			
			pos = size % 8 == 0 ? 8 : ((size) % 8);

			createObj = 1;

		}

		createObj <<= (8 - pos);
		
		out.push_back(createObj);

	}

	out.push_back(0);

	for (unsigned char i = 0;i< line.size();i++)
	{
		out.push_back(line[i]);
	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorHuffmanTree::Thaw(const std::vector<unsigned char>& _thawBase)
{
	if (_thawBase.size() <= 0)return _thawBase;

	unsigned long cutPos = 0;

	for (unsigned long i = 0; i < _thawBase.size(); i++)
	{
		unsigned long tmp = _thawBase.size() - i - 1;
		if (_thawBase[tmp] > 0)continue;
		cutPos = tmp;
		break;
	}

	std::vector<unsigned char>maps;

	for (unsigned long i = cutPos + 1; i < _thawBase.size(); i++)
	{
		maps.push_back(_thawBase[i]);
	}
	
	std::vector<unsigned char> out;

	ChCpp::BitBool flgs;

	unsigned long zeroCount = 0;
	for (unsigned long i = 0; i < cutPos; i++)
	{
		unsigned char val = _thawBase[i];
		flgs.SetValue(_thawBase[i]);
		for (char j = 7; j >= 0; j--)
		{
			if (flgs.GetBitFlg(j))
			{
				out.push_back(maps[zeroCount]);

				zeroCount = 0;

			}
			else
			{
				zeroCount++;
			}
		}
	}


	return out;
}

///////////////////////////////////////////////////////////////////////////////////
//DeflateCompressorメソッド
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


///////////////////////////////////////////////////////////////////////////////////
//RunglessCompressorメソッド
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
