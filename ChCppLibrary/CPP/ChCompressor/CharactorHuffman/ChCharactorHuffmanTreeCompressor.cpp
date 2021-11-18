
#include"../../../BaseIncluder/ChBase.h"
#include"../../ChBitBool/ChBitBool.h"

#include"../ChBaseCompressor.h"
#include"ChCharactorHuffmanTreeCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//HuffmanTreeCompressorÉÅÉ\ÉbÉh
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

	std::map<unsigned char, unsigned long>bitData;
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

	out.push_back(dictionaryFirstFlg ? 128 : 0);

	if (dictionaryFirstFlg)
	{

		for (unsigned char i = 0; i < line.size(); i++)
		{
			out.push_back(line[i]);
		}

		out.push_back(dictionaryAnnotation);

	}

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

	if (!dictionaryFirstFlg)
	{

		out.push_back(dictionaryAnnotation);

		for (unsigned char i = 0; i < line.size(); i++)
		{
			out.push_back(line[i]);
		}

	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorHuffmanTree::Thaw(const std::vector<unsigned char>& _thawBase)
{
	if (_thawBase.size() <= 0)return _thawBase;

	unsigned long cutPos = 0;

	unsigned char firstFlg = _thawBase[0];

	firstFlg &= 128;

	std::vector<unsigned char>maps;

	{
		unsigned long sizeCount = 0;
		for (unsigned long i = 1; i < _thawBase.size(); i++)
		{
			unsigned long tmp = firstFlg ? i : _thawBase.size() - i;
			sizeCount++;
			if (_thawBase[tmp] != dictionaryAnnotation)continue;
			cutPos = tmp;
			sizeCount - 1;
			break;
		}

		for (unsigned long i = 1; i < sizeCount; i++)
		{
			maps.push_back(_thawBase[i + (firstFlg ? 0 : cutPos)]);
		}

	}

	std::vector<unsigned char> out;

	ChCpp::BitBool flgs;

	unsigned long zeroCount = 0;
	for (unsigned long i = 1; firstFlg ? (i + cutPos) < _thawBase.size() : i < cutPos; i++)
	{
		unsigned long useNum = (firstFlg ? i + cutPos : i);
		unsigned char val = _thawBase[useNum];
		flgs.SetValue(_thawBase[useNum]);
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
