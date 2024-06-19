#ifndef Ch_CPP_BStr_CRT_h
#define Ch_CPP_BStr_CRT_h

#include"ChStr.h"

#include<cstringt.h>
#include<cstdlib>
#include<cstring>
#include<wchar.h>
#include<string>

#include"ChStdCRT.h"
#include"ChPtrCRT.h"
#include"ChListArray.h"

#ifndef CPP20

#include <codecvt>
#include <cassert>
#include <locale>

#endif

template<typename CharaType>
void ChStr::BaseString<CharaType>::Release()
{
	ChPtr::Release(str);
}

template<typename CharaType>
void ChStr::BaseString<CharaType>::Set(const CharaType* _str)
{
	if (ChPtr::NullCheck(_str))return;
	if (str == _str)return;
	std::basic_string<CharaType>tmpStr = _str;
	Release();
	str = ChPtr::InstantiateArray<CharaType>(tmpStr.length() + 1);
	for (unsigned long i = 0; i < tmpStr.length(); i++)
	{
		str[i] = tmpStr[i];
	}
	str[tmpStr.length()] = 0;
}

template<typename CharaType>
void ChStr::BaseString<CharaType>::Add(const BaseString& _str)
{
	if (ChPtr::NullCheck(str))
	{
		Set(_str);
		return;
	}
	if (_str.GetLength() <= 0)return;

	CharaType* createStr = ChPtr::InstantiateArray<CharaType>(_str.GetLength() + GetLength() + 1);
	for (unsigned long i = 0; i < GetLength(); i++)
	{
		createStr[i] = str[i];
	}

	for (unsigned long i = 0; i < _str.GetLength(); i++)
	{
		createStr[GetLength() + i] = _str.str[i];
	}

	createStr[GetLength() + _str.GetLength()] = 0;

	Release();

	str = createStr;
}

template<typename CharaType>
unsigned long ChStr::BaseString<CharaType>::GetLength()const
{
	if (ChPtr::NullCheck(str))return 0;
	std::basic_string<CharaType> tmpStr = str;
	return tmpStr.length();
}

template<typename CharaType>
ChArray::AllocArray<ChStr::BaseString<CharaType>> ChStr::BaseString<CharaType>::Split(const BaseString _str)
{
	ChArray::ListArray<unsigned long>memo;

	unsigned long pos = 0;
	unsigned long findFirstEndCount = 0;
	while (pos < GetLength())
	{
		pos = Find(_str, pos);
		if (pos < GetLength())
		{
			findFirstEndCount = pos == 0 || pos == (GetLength() - 1) ? findFirstEndCount + 1 : findFirstEndCount;
			memo.Push(pos);
			
			pos += 1;
		}
	}

	ChArray::AllocArray<ChStr::BaseString<CharaType>> result;

	if (memo.GetCount() <= 0)return result;

	result.ReSize(memo.GetCount() + 1 - findFirstEndCount);
	bool zeroFlg = memo[0] == 0;
	pos = zeroFlg ? _str.GetLength() : 0;
	unsigned long memoPosition = 0;
	for (unsigned long i = 0; i < result.GetCount(); i++)
	{
		memoPosition = zeroFlg ? i + 1 : i;
		result[i] = SubStr(pos, memo[memoPosition] - pos);
		pos = memo[memoPosition] + _str.GetLength();
	}

	return result;
}


template<typename CharaType>
void ChStr::BaseString<CharaType>::Replace(
	const BaseString _before,
	const BaseString _after,
	unsigned long _start)
{
	if (GetLength() <= 0)return;
	if (GetLength() < _before.GetLength())return;
	if(_before == _after)return;

	BaseString newText = "";

	unsigned long beforePosition = _start;
	bool findFlg = false;
	for (unsigned long i = _start; i < GetLength(); i++)
	{
		findFlg = true;
		for (unsigned long j = 0; j < _before.GetLength(); j++)
		{
			if (_before.str[j] == str[i + j])continue;
			findFlg = false;
			break;
		}

		if (!findFlg)continue;

		newText.Add(SubStr(beforePosition, i - beforePosition));
		i += _before.GetLength();
		newText.Add(_after);
		beforePosition = i;
	}

	if (beforePosition <= GetLength())
	{
		newText.Add(SubStr(beforePosition, GetLength() - beforePosition));
	}


	Set(newText);

}


template<typename CharaType>
void ChStr::BaseString<CharaType>::ReSize(unsigned long _value)
{
	CharaType* tmp = ChPtr::InstantiateArray<CharaType>(_value + 1);
	unsigned long loopCount = (_value > GetLength() ? GetLength() : _value);
	for (unsigned long i = 0; i < loopCount; i++)
	{
		tmp[i] = str[i];
	}
	tmp[loopCount] = 0;
	Release();
	str = tmp;
}

//クラス名を取得する関数//
template<typename CharaType,class T>
static inline ChStr::BaseString<CharaType> ChStr::GetTypeName()
{
	BaseString<CharaType> tmpStr = typeid(T).name();

	size_t tmp = tmpStr.Find(" ");
	if (tmp == std::string::npos)tmp = 0;
	else tmp += 1;

	return &tmpStr[tmp];
}

//文字の置き換え//
template<typename CharaType>
ChStr::BaseString<CharaType> ChStr::StrReplase(
	const ChStr::BaseString<CharaType>& _base,
	const ChStr::BaseString<CharaType>& _before,
	const ChStr::BaseString<CharaType>& _after)
{

	if (_base.find(_before) == _base.npos)return _base;

	ChStr::BaseString<CharaType> out;

	size_t tmpPos = 0;
	size_t testPos = 0;

	while (true)
	{
		testPos = _base.find(_before, tmpPos);

		if (testPos == _base.npos)break;

		out += _base.substr(tmpPos, testPos - tmpPos);

		out += _after;

		tmpPos = testPos + _before.length();

	}

	return out;
}

template<typename CharaType>
ChStr::BaseString<CharaType> ChStr::RemoveToWhiteSpaceChars(const ChStr::BaseString<CharaType>& _str)
{

	ChStr::BaseString<CharaType> out;

	const char WhiteSpaceInterfaceChar = 32;
	const char DelCharNum = 127;

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] <= WhiteSpaceInterfaceChar)continue;
		if (_str[i] == DelCharNum)continue;

		out = out + _str[i];

	}

	return out;
}

static inline std::wstring RemoveToWhiteSpaceChars(const std::wstring& _str)
{

	std::wstring out = L"";

	const char WhiteSpaceInterfaceChar = 32;
	const char DelCharNum = 127;

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] < WhiteSpaceInterfaceChar)continue;
		if (_str[i] == DelCharNum)continue;

		out = out + _str[i];

	}

	return out;
}

std::string RemoveToChars(const std::string& _str, const char _rempveChars)
{

	std::string out = "";

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] == _rempveChars)continue;

		out = out + _str[i];

	}

	return out;
}

std::wstring RemoveToChars(const std::wstring& _str, const wchar_t _rempveChars)
{

	std::wstring out = L"";

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] == _rempveChars)continue;

		out = out + _str[i];

	}

	return out;
}

std::string RemoveToUnNums(const std::string& _str)
{

	std::string out = "";

	const char StartNum = '0';
	const char EndNum = '9';

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		bool ConFlg = false;

		if (_str[i] < StartNum)ConFlg = true;
		if (_str[i] > EndNum)ConFlg = true;

		if (_str[i] == '.')ConFlg = false;
		if (_str[i] == '-')ConFlg = false;

		if (ConFlg)continue;

		out = out + _str[i];

	}

	return out;
}

std::wstring RemoveToUnNums(const std::wstring& _str)
{

	std::wstring out = L"";

	const wchar_t StartNum = L'0';
	const wchar_t EndNum = L'9';

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		bool conFlg = false;

		if (_str[i] < StartNum)conFlg = true;
		if (_str[i] > EndNum)conFlg = true;

		if (_str[i] == L'.')conFlg = false;
		if (_str[i] == L'-')conFlg = false;

		if (conFlg)continue;
		out = out + _str[i];

	}
	return out;
}

std::vector<std::string> Split(const std::string& _str, const std::string& _split)
{
	std::vector<std::string> out;

	unsigned long nowPos = 0;
	unsigned long testPos = _str.find(_split, nowPos);

	if (testPos == std::string::npos)
	{
		out.push_back(_str);
		return out;
	}

	while (testPos != std::string::npos)
	{
		unsigned long tmp = testPos - nowPos;
		out.push_back(tmp != 0 ? _str.substr(nowPos, testPos - nowPos) : "\0");
		nowPos = testPos + _split.size();
		testPos = _str.find(_split, nowPos);
	}

	out.push_back(_str.substr(nowPos));

	return out;
}

std::vector<std::wstring> Split(const std::wstring& _str, const std::wstring& _split)
{
	std::vector<std::wstring> out;

	unsigned long nowPos = 0;
	unsigned long testPos = _str.find(_split, nowPos);

	if (testPos == std::wstring::npos)
	{
		out.push_back(_str);
		return out;
	}

	while (testPos != std::wstring::npos)
	{
		out.push_back(_str.substr(nowPos, testPos - nowPos));
		nowPos = testPos + _split.size();
		testPos = _str.find(_split, nowPos);
	}

	out.push_back(_str.substr(nowPos));

	return out;
}

std::string GetCharsToRangeCode(
	const std::string& _str
	, const char _min
	, const char _max)
{

	std::string out = "";

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] > _max || _str[i] < _min)continue;

		out = out + _str[i];

	}

	return out;
}

static inline std::wstring GetCharsToRangeCode(
	const std::wstring& _str
	, const wchar_t _min
	, const wchar_t _max)
{

	std::wstring out = L"";

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] > _max || _str[i] < _min)continue;

		out = out + _str[i];

	}
	return out;
}

namespace ChStr
{
#ifndef CPP20


	using ConvertUTF8 = std::codecvt_utf8<wchar_t>;
	using ConvertUTF16 = std::codecvt_utf16<wchar_t>;


	std::wstring_convert<ConvertUTF8, wchar_t>& GetU8Converter()
	{

		static std::wstring_convert<ConvertUTF8, wchar_t> strconverter;

		return strconverter;
	}

	std::wstring_convert<ConvertUTF16, wchar_t>& GetU16Converter()
	{

		static std::wstring_convert<ConvertUTF16, wchar_t> strconverter;

		return strconverter;
	}


	//文字列からUTF8のワイド文字列へ変換する//
	std::wstring ChStrUTF8ToWString(const std::string& _str)
	{

		return GetU8Converter().from_bytes(_str.c_str());
	}

	//ワイド文字列から文字列へ変換する//
	std::string UTF8ToString(const std::wstring& _str)
	{
		return GetU8Converter().to_bytes(_str.c_str());
	}

	//文字列からUTF16のワイド文字列へ変換する//
	std::wstring UTF16ToWString(const std::string& _str)
	{

		return GetU16Converter().from_bytes(_str.c_str());
	}

	//ワイド文字列から文字列へ変換する//
	std::string UTF16ToString(const std::wstring& _str)
	{
		return GetU16Converter().to_bytes(_str.c_str());
	}

#endif

}


#endif