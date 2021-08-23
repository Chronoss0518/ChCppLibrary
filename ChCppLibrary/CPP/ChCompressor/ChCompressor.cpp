
#include"../../BaseIncluder/ChBase.h"
#include"../ChBitBool/ChBitBool.h"

#include"ChBaseCompressor.h"
#include"ChHuffmanTreeCompressor.h"
#include"ChDeflateCompressor.h"
#include"ChRunglessCompressor.h"

using namespace ChCpp;
using namespace Cmp;

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

std::vector<unsigned char> Rungless::Press(const std::vector<unsigned char>& _pressBase)
{

	if (_pressBase.size() <= 0)return _pressBase;

	char targetChar = 0;
	unsigned long targetCharCount = 0;

	unsigned long maxSize = 0;

	for (unsigned long i = 0; i < _pressBase.size(); i++)
	{
		if (i <= 0)
		{
			targetChar = _pressBase[i];
		}
		else if (targetChar != _pressBase[i])
		{
			maxSize = targetCharCount > maxSize ? targetCharCount : maxSize;

			targetChar = _pressBase[i];
			targetCharCount = 0;
		}
		targetCharCount++;
	}

	char byteSize = maxSize < 0xff ? 1 : maxSize < 0xffff ? 2 : maxSize < 0xffffffff ? 4 : 8;

	std::vector<unsigned char> out;

	out.push_back(byteSize);
	out.push_back('\0');


	targetChar = 0;
	targetCharCount = 0;


	for (unsigned long i = 0; i < _pressBase.size(); i++)
	{
		if (i <= 0)
		{
			targetChar = _pressBase[i];
		}
		else if (targetChar != _pressBase[i])
		{
			out.push_back(targetChar);

			void* tmp = &targetCharCount;

			for (unsigned char j = 0; j < byteSize; j++)
			{
				out.push_back(static_cast<unsigned char*>(tmp)[byteSize - j - 1]);
			}

			targetChar = _pressBase[i];
			targetCharCount = 0;
		}
		targetCharCount++;
	}

	out.push_back(targetChar);

	void* tmp = &targetCharCount;

	for (unsigned char j = 0; j < byteSize; j++)
	{
		out.push_back(static_cast<char*>(tmp)[byteSize - j - 1]);
	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned char> Rungless::Thaw(const std::vector<unsigned char>& _thawBase)
{
	if (_thawBase.size() <= 1 || (_thawBase.size() % 2) != 0)return _thawBase;



	std::vector<unsigned char> out;

	char byteSize = _thawBase[0];

	if (byteSize <= 0 || byteSize > 4)return _thawBase;

	for (unsigned long i = 2; i < _thawBase.size(); i += byteSize + 1)
	{
		unsigned long dataLen = 0;
		unsigned char chara = _thawBase[i];


		for (unsigned char j = 0; j < byteSize; j++)
		{
			dataLen |= _thawBase[i + j + 1] << j;
		}

		for (unsigned long j = 0; j < dataLen; j++)
		{
			out.push_back(chara);
		}
		
	}

	return out;
}
