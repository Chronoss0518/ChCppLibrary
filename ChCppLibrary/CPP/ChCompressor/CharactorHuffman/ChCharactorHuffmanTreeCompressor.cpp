
#include"../../../BaseIncluder/ChBase.h"
#include"../../ChBitBool/ChBitBool.h"

#include"../ChBaseCompressor.h"
#include"ChCharactorHuffmanTreeCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//HuffmanTreeCompressorÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorHuffmanTree::Compress(const std::vector<unsigned char>& _compressBase)
{
	if (_compressBase.size() <= 0)return _compressBase;

	std::map<unsigned char, FlgObject> dictionary;

	CreateMaps(dictionary, _compressBase);

	std::vector<unsigned char> out;
	std::vector<unsigned char>pressData;

	unsigned char maxByteSize = 0;

	{
		unsigned char maxCodeSize = 0;

		for (auto&& chara : dictionary)
		{
			maxCodeSize = chara.first > maxCodeSize ? chara.first : maxCodeSize;
		}

		for (unsigned char i = 0; i < 8; i++)
		{
			if(!(maxCodeSize & (1 << i)))continue;
			maxByteSize = i + 1;
		}

	}
	
	FirstFlgment firstFlgment;

	{
		firstFlgment.dictionaryFirstFlg = dictionaryFirstFlg ? 1 : 0;

		firstFlgment.charaMaxByte = maxByteSize;

	}

	{
		BitBool createByte = BitBool(1);

		unsigned char nowCount = 0;



		if (dictionaryFirstFlg)
		{

			CreateDictionary(pressData, createByte, nowCount, dictionary, maxByteSize);

			pressData.push_back(dictionaryAnnotation);

			nowCount = 0;

		}

		for (auto&& pressChara : _compressBase)
		{
			for (unsigned long i = 0; i < dictionary[pressChara].bitSize; i++)
			{
				createByte.SetBitFlg((7 - nowCount), dictionary[pressChara].value & (1 << (dictionary[pressChara].bitSize - 1 - i)));
				nowCount++;

				if (nowCount < 7)continue;

				pressData.push_back(createByte.GetValue());

				nowCount = 0;
				createByte.SetAllDownFlg();
			}
		}

		pressData.push_back(createByte.GetValue());

		firstFlgment.unUsedLastByte = (7 - nowCount);

		if (!dictionaryFirstFlg)
		{
			pressData.push_back(dictionaryAnnotation);

			nowCount = 0;

			CreateDictionary(pressData, createByte, nowCount, dictionary, maxByteSize);

		}

		out.push_back(firstFlgment.value);
		out.push_back(dictionaryAnnotation);

		for (auto&& byte : pressData)
		{
			out.push_back(byte);
		}

	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> CharactorHuffmanTree::Decompress(const std::vector<unsigned char>& _decompressBase)
{
	if (_decompressBase.size() <= 0)return _decompressBase;
	
	FirstFlgment firstFlgment;

	firstFlgment.value = _decompressBase[0];
	unsigned char dAnnotation = _decompressBase[1];
	std::map<unsigned char, FlgObject>dictionary;


	unsigned long startPos = 2;
	unsigned long endPos = _decompressBase.size();

	{

		std::vector<unsigned char>dictionaryByte;

		if (firstFlgment.dictionaryFirstFlg)
		{
			for (long long i = 2; i < _decompressBase.size(); i++)
			{
				dictionaryByte.push_back(_decompressBase[i]);
				if (_decompressBase[i] != dAnnotation) continue;
				startPos = i;
				dictionaryByte.pop_back();
				break;
			}

		}
		else
		{
			for (long long i = _decompressBase.size(); i >= 0; i--)
			{
				dictionaryByte.push_back(_decompressBase[i]);
				if (_decompressBase[i] != dAnnotation) continue;
				endPos = i;
				dictionaryByte.pop_back();
				break;
			}
		}

		BitBool nowByte;
		unsigned char readByteCount = 0;
		unsigned long readBytePos = 0;



		nowByte.SetValue(firstFlgment.dictionaryFirstFlg ? dictionaryByte[readBytePos] : dictionaryByte[(dictionaryByte.size() - readBytePos - 1)]);

		{

			bool endFlg = false;

			while (!endFlg)
			{
				unsigned char chara = 0;

				FlgObject charaSize;

				for (unsigned char i = 0; i < firstFlgment.charaMaxByte; i++)
				{
					if (endFlg)break;
					chara |= (nowByte.GetBitFlg(firstFlgment.charaMaxByte - i - 1) ? 1 : 0) << (firstFlgment.charaMaxByte - i - 1);

					endFlg = ChangeByteTest(nowByte, readByteCount, readBytePos, dictionaryByte, firstFlgment.dictionaryFirstFlg);
				}

				for (unsigned char i = 0; i < 8; i++)
				{
					if (endFlg)break;
					charaSize.bitSize |= (nowByte.GetBitFlg(8 - i - 1) ? 1 : 0) << (8 - i - 1);

					endFlg = ChangeByteTest(nowByte, readByteCount, readBytePos, dictionaryByte, firstFlgment.dictionaryFirstFlg);
				}
				for (unsigned char i = 0; i < charaSize.bitSize; i++)
				{
					if (readBytePos >= dictionaryByte.size())break;
					charaSize.value |= (nowByte.GetBitFlg(charaSize.bitSize - i - 1) ? 1 : 0) << (charaSize.bitSize - i - 1);

					endFlg = ChangeByteTest(nowByte, readByteCount, readBytePos, dictionaryByte, firstFlgment.dictionaryFirstFlg);
				}

				if (endFlg)break;
				dictionary[chara] = charaSize;
			}
		}
		int test = 0;
		test = 1;

	}


	std::vector<unsigned char>out;



	return out;
}

///////////////////////////////////////////////////////////////////////////////////

void CharactorHuffmanTree::CreateMaps(std::map<unsigned char, FlgObject>& _maps, const std::vector<unsigned char>&_compressBase)
{
	RootObject objects;

	unsigned long pressSize = 0;
	{

		std::map<unsigned char, unsigned long>tmpCounter;
		for (unsigned long i = 0; i < _compressBase.size(); i++)
		{
			tmpCounter[_compressBase[i]]++;
			pressSize++;
		}
		
		for (unsigned long i = 0; i < tmpCounter.size(); i++)
		{
			unsigned long maxs = 0;
			unsigned char maxValue = 0;

			for (auto&& obj : tmpCounter)
			{
				if (maxs >= obj.second)continue;
				maxValue = obj.first;
				maxs = obj.second;
			}

			auto obj = ChPtr::Make_S<TreeObject>();
			obj->value = maxValue;
			obj->frequency = maxs;
			objects.objects.push_back(obj);
			tmpCounter[maxValue] = 0;

		}

		objects.frequency = pressSize + 1;
	}

	CreateRootObject(_maps, objects);
}

///////////////////////////////////////////////////////////////////////////////////

void CharactorHuffmanTree::CreateRootObject(std::map<unsigned char, FlgObject>& _maps, const RootObject& _object, const FlgObject& _nowFlg)
{
	RootObject high, low;

	for (auto&& _obj : _object.objects)
	{
		RootObject* tmp = (high.frequency <= low.frequency ? &high : &low);

		tmp->frequency += _obj->frequency;
		tmp->objects.push_back(_obj);
	}

	//low
	{
		FlgObject tmp = _nowFlg;
		tmp.bitSize++;
		tmp.value <<= 1;
		tmp.value |= highToZeroFlg ? 1 : 0;
		SetTreeBranchs(_maps,high,tmp);
	}

	//high
	{
		FlgObject tmp = _nowFlg;
		tmp.bitSize++;
		tmp.value <<= 1;
		tmp.value |= highToZeroFlg ? 0 : 1;
		SetTreeBranchs(_maps,low,tmp);
	}


}

///////////////////////////////////////////////////////////////////////////////////

void CharactorHuffmanTree::SetTreeBranchs(std::map<unsigned char, FlgObject>& _maps, RootObject& _obj, const FlgObject& _nowFlg)
{

	if (_obj.objects.size() <= 1)
	{
		_maps[_obj.objects[0]->value] = _nowFlg;

		return;
	}

	CreateRootObject(_maps , _obj,_nowFlg);

	return;

}


void CharactorHuffmanTree::CreateDictionary(
	std::vector<unsigned char>& _out,
	BitBool& _nowByte,
	unsigned char& _nowCount,
	const std::map<unsigned char, FlgObject>& _fObject,
	const unsigned char _maxByteSize)
{

	for (auto&& dictionary : _fObject)
	{


		for (unsigned long i = 0; i < _maxByteSize - 1; i++)
		{
			_nowByte.SetBitFlg((7 - _nowCount), (dictionary.first & (1 << (_maxByteSize - i - 1))));
			_nowCount++;

			if (_nowCount < 7)continue;

			_out.push_back(_nowByte.GetValue());

			_nowCount = 0;
			_nowByte.SetAllDownFlg();
		}

		for (unsigned long i = 0; i < 8; i++)
		{
			_nowByte.SetBitFlg((7 - _nowCount), (dictionary.first & (1 << (8 - i - 1))));
			_nowCount++;

			if (_nowCount < 7)continue;

			_out.push_back(_nowByte.GetValue());

			_nowCount = 0;
			_nowByte.SetAllDownFlg();
		}

		for (unsigned long i = 0; i < dictionary.second.bitSize; i++)
		{
			_nowByte.SetBitFlg((7 - _nowCount), (dictionary.second.value & (1 << (dictionary.second.bitSize - i - 1))));
			_nowCount++;

			if (_nowCount < 7)continue;

			_out.push_back(_nowByte.GetValue());

			_nowCount = 0;
			_nowByte.SetAllDownFlg();
		}
	}

	if(_nowCount > 0)_out.push_back(_nowByte.GetValue());
}


bool CharactorHuffmanTree::ChangeByteTest(
	BitBool& _nowByte,
	unsigned char& _readByteCount
	, unsigned long& _readBytePos
	, std::vector<unsigned char>& _dictionaryByte, 
	const bool _dictionaryFirstFlg)
{

	_readByteCount++;
	if (_readByteCount < 7)return false;

	_readByteCount = 0;
	_readBytePos++;

	if ((_readBytePos >= _dictionaryByte.size()))return true;
	_nowByte.SetValue(_dictionaryFirstFlg ? _dictionaryByte[_readBytePos] : _dictionaryByte[(_dictionaryByte.size() - _readBytePos - 1)]);

	return false;
}