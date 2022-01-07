
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
	std::vector<unsigned char> dictionaryByte;

	unsigned char maxByteSize = 0;

	{
		unsigned char maxCodeSize = 0;

		for (auto&& chara : dictionary)
		{
			maxCodeSize = chara.first > maxCodeSize ? chara.first : maxCodeSize;
		}

		BitBool maxByte = BitBool(1);
		maxByte.SetValue(maxCodeSize);
		for (unsigned char i = 0; i < 8; i++)
		{
			if(!(maxByte.GetBitFlg(7 - i)))continue;
			maxByteSize = 8 - i;
			break;
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

		unsigned char AnnotationCount = 0;

		{
			createByte.SetAllDownFlg();

			CreateDictionary(dictionaryByte, AnnotationCount, createByte, nowCount, dictionary, maxByteSize);

			nowCount = 0;
		}

		out.push_back(firstFlgment.value);
		out.push_back(dictionaryAnnotation);
		out.push_back(AnnotationCount);

		if (dictionaryFirstFlg)
		{
			for (auto&& byte : dictionaryByte)
			{
				out.push_back(byte);
			}

			out.push_back(dictionaryAnnotation);

		}

		for (auto&& pressChara : _compressBase)
		{
			for (unsigned long i = 0; i < dictionary[pressChara].bitSize; i++)
			{
				createByte.SetBitFlg((7 - nowCount), dictionary[pressChara].value & (1 << (dictionary[pressChara].bitSize - 1 - i)));
				nowCount++;

				if (nowCount < 7)continue;

				out.push_back(createByte.GetValue());

				nowCount = 0;
				createByte.SetAllDownFlg();
			}
		}

		if(createByte.GetValue() > 0)out.push_back(createByte.GetValue());

		firstFlgment.unUsedLastByte = (7 - nowCount);

		if (!dictionaryFirstFlg)
		{
			out.push_back(dictionaryAnnotation);

			for (auto&& byte : dictionaryByte)
			{
				out.push_back(byte);
			}
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
	unsigned char annotationCountInDictionary = _decompressBase[2];
	std::map<unsigned char, FlgObject>dictionary;


	unsigned long startPos = 3;
	unsigned long endPos = _decompressBase.size();

	LoadDictionary(dictionary, startPos, endPos, _decompressBase, firstFlgment, dAnnotation, annotationCountInDictionary);

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
	unsigned char& _annotationInDictionary,
	BitBool& _nowByte,
	unsigned char& _nowCount,
	const std::map<unsigned char, FlgObject>& _fObject,
	const unsigned char _maxByteSize)
{

	for (auto&& dictionary : _fObject)
	{

		for (unsigned long i = 0; i < _maxByteSize; i++)
		{
			_nowByte.SetBitFlg((7 - _nowCount), (dictionary.first & (1 << (_maxByteSize - i - 1))));
			_nowCount++;

			if (_nowCount < 8)continue;

			if (_nowByte.GetValue() == dictionaryAnnotation)_annotationInDictionary++;

			_out.push_back(_nowByte.GetValue());

			_nowCount = 0;
			_nowByte.SetAllDownFlg();
		}

		for (unsigned long i = 0; i < 8; i++)
		{
			_nowByte.SetBitFlg((7 - _nowCount), (dictionary.second.bitSize & (1 << (8 - i - 1))));
			_nowCount++;

			if (_nowCount < 8)continue;

			if (_nowByte.GetValue() == dictionaryAnnotation)_annotationInDictionary++;

			_out.push_back(_nowByte.GetValue());

			_nowCount = 0;
			_nowByte.SetAllDownFlg();
		}

		for (unsigned long i = 0; i < dictionary.second.bitSize; i++)
		{
			_nowByte.SetBitFlg((7 - _nowCount), (dictionary.second.value & (1 << (dictionary.second.bitSize - i - 1))));
			_nowCount++;

			if (_nowCount < 8)continue;

			if (_nowByte.GetValue() == dictionaryAnnotation)_annotationInDictionary++;

			_out.push_back(_nowByte.GetValue());

			_nowCount = 0;
			_nowByte.SetAllDownFlg();
		}
	}

	if(_nowCount > 0)_out.push_back(_nowByte.GetValue());
}

///////////////////////////////////////////////////////////////////////////////////

bool CharactorHuffmanTree::ChangeByteTest(
	BitBool& _nowByte,
	unsigned char& _readByteCount
	, unsigned long& _readBytePos
	, std::vector<unsigned char>& _dictionaryByte, 
	const bool _dictionaryFirstFlg)
{

	_readByteCount++;
	if (_readByteCount < 8)return false;

	_readByteCount = 0;
	_readBytePos++;

	if ((_readBytePos >= _dictionaryByte.size()))return true;
	_nowByte.SetValue(_dictionaryFirstFlg ? _dictionaryByte[_readBytePos] : _dictionaryByte[(_dictionaryByte.size() - _readBytePos - 1)]);

	return false;
}

///////////////////////////////////////////////////////////////////////////////////

void CharactorHuffmanTree::LoadDictionary(
	std::map<unsigned char, FlgObject>& _dictionary,
	unsigned long& _startPos,
	unsigned long& _endPos,
	const std::vector<unsigned char>& _decompressBase,
	const FirstFlgment _fFlgs,
	const unsigned char _annotatino ,
	const unsigned char _annotationCountInDictionary)
{

	std::vector<unsigned char>dictionaryByte;
	unsigned char annotationCount = 0;
	if (_fFlgs.dictionaryFirstFlg)
	{
		for (unsigned long i = _startPos; i < _endPos; i++)
		{
			dictionaryByte.push_back(_decompressBase[i]);
			if (_decompressBase[i] != _annotatino) continue;
			if (_annotationCountInDictionary > annotationCount++)continue;
			_startPos = i + 1;
			dictionaryByte.pop_back();
			break;
		}

	}
	else
	{
		for (unsigned long i = _endPos; i >= _startPos; i--)
		{
			dictionaryByte.push_back(_decompressBase[i]);
			if (_decompressBase[i] != _annotatino) continue;
			if (_annotationCountInDictionary > annotationCount++)continue;
			_endPos = i - 1;
			dictionaryByte.pop_back();
			break;
		}
	}

	BitBool nowByte;
	unsigned char readByteCount = 0;
	unsigned long readBytePos = 0;

	nowByte.SetValue(_fFlgs.dictionaryFirstFlg ? dictionaryByte[readBytePos] : dictionaryByte[(dictionaryByte.size() - readBytePos - 1)]);

	{

		bool endFlg = false;

		while (!endFlg)
		{
			unsigned char chara = 0;

			FlgObject charaSize;

			for (unsigned char i = 0; i < _fFlgs.charaMaxByte; i++)
			{
				if (endFlg)break;
				chara |= (nowByte.GetBitFlg(7 - readByteCount) ? 1 : 0) << (_fFlgs.charaMaxByte - i - 1);

				endFlg = ChangeByteTest(nowByte, readByteCount, readBytePos, dictionaryByte, _fFlgs.dictionaryFirstFlg);
			}

			for (unsigned char i = 0; i < 8; i++)
			{
				if (endFlg)break;
				charaSize.bitSize |= (nowByte.GetBitFlg(7 - readByteCount) ? 1 : 0) << (7 - i);

				endFlg = ChangeByteTest(nowByte, readByteCount, readBytePos, dictionaryByte, _fFlgs.dictionaryFirstFlg);
			}

			for (unsigned long i = 0; i < charaSize.bitSize; i++)
			{
				if (endFlg)break;
				if (readBytePos >= dictionaryByte.size())break;
				charaSize.value |= (nowByte.GetBitFlg(7 - readByteCount) ? 1 : 0) << (charaSize.bitSize - i - 1);

				endFlg = ChangeByteTest(nowByte, readByteCount, readBytePos, dictionaryByte, _fFlgs.dictionaryFirstFlg);
			}

			if (endFlg)break;
			_dictionary[chara] = charaSize;
		}
	}
}