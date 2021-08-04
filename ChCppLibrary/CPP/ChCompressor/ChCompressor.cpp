
#include"../../BaseIncluder/ChBase.h"
#include"../ChBitBool/ChBitBool.h"

#include"ChBaseCompressor.h"
#include"ChDeflateCompressor.h"
#include"ChRunglessCompressor.h"

using namespace ChCpp;
using namespace Cmp;

///////////////////////////////////////////////////////////////////////////////////
//DictionaryCompressorメソッド
///////////////////////////////////////////////////////////////////////////////////

std::vector<char> Deflate::Press(const std::vector<char>& _pressBase)
{
	if (_pressBase.size() <= 0)return _pressBase;

	std::map<char, ChPtr::Shared<BitBool>> tree;

	std::vector<char> out;

	for (unsigned long i = 0; i < _pressBase.size(); i++)
	{

	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<char> Deflate::Thaw(const std::vector<char>& _thawBase)
{
	if (_thawBase.size() <= 0)return _thawBase;

	std::vector<char> out;

	for (unsigned long i = 0; i < _thawBase.size(); i++)
	{

	}

	return out;
}


///////////////////////////////////////////////////////////////////////////////////
//RunglessCompressorメソッド
///////////////////////////////////////////////////////////////////////////////////

std::vector<char> Rungless::Press(const std::vector<char>& _pressBase)
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

	char biteSize = maxSize < 0xff ? 1 : maxSize < 0xffff ? 2 : maxSize < 0xffffffff ? 4 : 8;

	std::vector<char> out;

	out.push_back(biteSize);
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

			for (unsigned char j = 0; j < biteSize; j++)
			{
				out.push_back(static_cast<char*>(tmp)[biteSize - j - 1]);
			}

			targetChar = _pressBase[i];
			targetCharCount = 0;
		}
		targetCharCount++;
	}

	out.push_back(targetChar);

	void* tmp = &targetCharCount;

	for (unsigned char j = 0; j < biteSize; j++)
	{
		out.push_back(static_cast<char*>(tmp)[biteSize - j - 1]);
	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<char> Rungless::Thaw(const std::vector<char>& _thawBase)
{
	if (_thawBase.size() <= 1)return _thawBase;

	std::vector<char> out;

	for (unsigned long i = 0; i < _thawBase.size(); i++)
	{

	}

	return out;
}
