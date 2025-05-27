
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 4996
#endif

#include<locale.h>

#include"../BaseIncluder/ChBase.h"
#include"ChStr.h"

#include"../CPP/ChCumulative/ChCumulative.h"

#define LOCALE_TYPE_COUNT 6

using namespace ChStr;

//文字の置き換え//
template<typename CharaType>
std::basic_string<CharaType> ChStr::StrReplase(
	const std::basic_string<CharaType>& _base,
	const std::basic_string<CharaType>& _before,
	const std::basic_string<CharaType>& _after)
{
	if (_base.find(_before) == std::basic_string<CharaType>::npos)return _base;

	std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();

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

//空文字を取り除く//
template<typename CharaType>
std::basic_string<CharaType> ChStr::RemoveToWhiteSpaceChars(const std::basic_string<CharaType>& _str)
{
	std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();

	const char whiteSpaceInterfaceChar = 32;
	const char delCharNum = 127;

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] <= whiteSpaceInterfaceChar)continue;
		if (_str[i] == delCharNum)continue;

		out = out + _str[i];
	}

	return out;
}

//指定した文字を取り除く//
template<typename CharaType>
std::basic_string<CharaType> ChStr::RemoveToChars(
	const std::basic_string<CharaType>& _str,
	const std::basic_string<CharaType>& _removeChars)
{
	if (_removeChars.size() <= 0)return _str;

	std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();


	size_t endPos = _str.find(_removeChars);
	size_t startPos = 0;

	while(endPos < _str.length())
	{
		out += _str.substr(startPos,endPos - startPos - 1);


		startPos = endPos + _removeChars.size();
		startPos = _str.find(_removeChars, endPos);
	}

	out += _str.substr(startPos);

	return out;
}

//数値に変換可能な文字以外の文字を取り除く//
template<typename CharaType>
std::basic_string<CharaType> ChStr::RemoveToUnNumCharas(const std::basic_string<CharaType>& _str)
{
	if (_str.length() <= 0)return  _str;

	std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();

	const CharaType mChara = static_cast<CharaType>('-');

	const CharaType startNum = static_cast<CharaType>('0');
	const CharaType endNum = static_cast<CharaType>('9');

	bool conFlg = false;
	for (unsigned long i = 0; i < _str.length(); i++)
	{
		conFlg = false;
		if (_str[i] < startNum)conFlg = true;
		if (_str[i] > endNum)conFlg = true;
		if (out.size() == 0 && _str[i] == mChara)conFlg = false;

		if (!conFlg)out = out + _str[i];
	}
	return out;
}

//数値に変換可能な文字以外の文字を取り除く//
template<typename CharaType>
std::basic_string<CharaType> ChStr::RemoveToUnFloatingNumCharas(
	const std::basic_string<CharaType>& _str,
	unsigned long* _ePosition,
	unsigned long* _colonPoint)
{
	if (ChPtr::NotNullCheck(_ePosition))*_ePosition = -1;
	if (ChPtr::NotNullCheck(_colonPoint))*_colonPoint = -1;
	if (_str.length() <= 0)return  _str;

	std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();

	const CharaType startNum = static_cast<CharaType>('0');
	const CharaType endNum = static_cast<CharaType>('9');

	bool colonFlg = false;
	CharaType colonChara = static_cast<CharaType>('.');

	CharaType mChara = static_cast<CharaType>('-');
	CharaType pChara = static_cast<CharaType>('+');
	CharaType eChara = static_cast<CharaType>('e');
	CharaType EChara = static_cast<CharaType>('E');
	unsigned long ePosition = -1;
	bool conFlg = false;
	for (unsigned long i = 0; i < _str.length(); i++)
	{
		conFlg = false;

		if (_str[i] < startNum)conFlg = true;
		if (_str[i] > endNum)conFlg = true;
		if (out.size() == 0 && _str[i] == mChara)conFlg = false;

		if (!colonFlg && _str[i] == colonChara)
		{
			conFlg = false;
			colonFlg = true;
			if (ChPtr::NotNullCheck(_colonPoint))*_colonPoint = i;
		}

		if ((_str[i] == eChara && _str[i + 1] == mChara) || (_str[i] == EChara && _str[i + 1] == mChara))
		{
			ePosition = i + 2;
			out = out + _str[i] + _str[i + 1];
			break;
		}

		if ((_str[i] == eChara && _str[i + 1] == pChara) || (_str[i] == EChara && _str[i + 1] == pChara))
		{
			ePosition = i + 2;
			out = out + _str[i] + _str[i + 1];
			break;
		}

		if (conFlg)continue;

		out = out + _str[i];
	}

	if (ePosition < _str.length())
	{
		if (ChPtr::NotNullCheck(_ePosition))*_ePosition = ePosition;
		out += ChStr::RemoveToUnNumCharas<CharaType>(&_str[ePosition]);
	}

	return out;
}

//対象の文字で区切り配列にする//
template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChStr::Split(
	const std::basic_string<CharaType>& _str,
	const std::basic_string<CharaType>& _splitChar)
{
	std::vector<std::basic_string<CharaType>> out;

	size_t nowPos = 0;
	size_t testPos = _str.find(_splitChar, nowPos);

	while (testPos != std::basic_string<CharaType>::npos)
	{
		size_t tmp = testPos - nowPos;
		out.push_back(tmp != 0 ? _str.substr(nowPos, testPos - nowPos) : ChStd::GetZeroChara<CharaType>());
		nowPos = testPos + _splitChar.size();
		testPos = _str.find(_splitChar, nowPos);
	}

	out.push_back(_str.substr(nowPos));

	return out;
}

//指定されたコード値の範囲の文字のみを返す//
template<typename CharaType>
std::basic_string<CharaType> ChStr::GetCharsToRangeCode(
	const std::basic_string<CharaType>& _str,
	const CharaType _min,
	const CharaType _max)
{
	std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		if (_str[i] <= _max && _str[i] >= _min)out = out + _str[i];
	}
	return out;
}

#define EXPLICIT_DECLARATION(_CharaType)\
template std::basic_string<_CharaType> ChStr::StrReplase(\
	const std::basic_string<_CharaType>& _base,\
	const std::basic_string<_CharaType>& _before,\
	const std::basic_string<_CharaType>& _after);\
template std::basic_string<_CharaType> ChStr::RemoveToWhiteSpaceChars(const std::basic_string<_CharaType>& _str);\
template std::basic_string<_CharaType> ChStr::RemoveToChars(\
	const std::basic_string<_CharaType>& _str,\
	const std::basic_string<_CharaType>& _removeChars);\
template std::basic_string<_CharaType> ChStr::RemoveToUnNumCharas(const std::basic_string<_CharaType>& _str);\
template std::basic_string<_CharaType> ChStr::RemoveToUnFloatingNumCharas(\
	const std::basic_string<_CharaType>& _str,\
	unsigned long* _ePosition,\
	unsigned long* _colonPoint);\
template std::vector<std::basic_string<_CharaType>> ChStr::Split(\
	const std::basic_string<_CharaType>& _str,\
	const std::basic_string<_CharaType>& _splitChar);\
template std::basic_string<_CharaType> ChStr::GetCharsToRangeCode(\
	const std::basic_string<_CharaType>& _str,\
	const _CharaType _min,\
	const _CharaType _max)

std::wstring GetMBSFormWCS(const std::string& _str, const std::string& _locale)
{
	if (_str == "")return L"";
	std::wstring res = L"";
	res.resize(_str.capacity() + 1);
	std::string localeName = setlocale(LC_ALL, "");
	std::string tmpLocale = localeName;
	size_t tmpPos = tmpLocale.rfind(".");
	tmpLocale = tmpLocale.substr(0, tmpPos);
	setlocale(LC_ALL, (tmpLocale + "." + _locale).c_str());
	size_t createSize = mbstowcs(&res[0], _str.c_str(), _str.capacity() + 1);
	setlocale(LC_ALL, (localeName).c_str());
	if (createSize > _str.capacity() + 1)return L"";
	res = res.substr(0, createSize).c_str();
	return res;
}

std::string GetWCSFormMBS(const std::wstring& _str, const std::string& _locale)
{
	if (_str == L"")return "";
	std::string res = "";
	res.resize(_str.capacity() * 3 + 1);
	std::string localeName = setlocale(LC_ALL, "");
	std::string tmpLocale = localeName;
	size_t tmpPos = tmpLocale.rfind(".");
	tmpLocale = tmpLocale.substr(0, tmpPos);
	setlocale(LC_ALL, (tmpLocale + "." + _locale).c_str());
	size_t createSize = wcstombs(&res[0], &_str.c_str()[0], _str.capacity() * 3 + 1);
	setlocale(LC_ALL, (localeName).c_str());
	if (createSize > _str.capacity() * 3)return "";
	res = res.substr(0, createSize).c_str();
	return res;
}


std::string ChStr::GetShiftJisFromUTF16(const std::wstring& _str)
{
	return GetWCSFormMBS(_str, "932");
}

std::wstring ChStr::GetUTF16FromShiftJis(const std::string& _str)
{
	return GetMBSFormWCS(_str, "932");
}

std::string ChStr::GetUTF8FromUTF16(const std::wstring& _str)
{
	return GetWCSFormMBS(_str, "UTF8");
}

std::wstring ChStr::GetUTF16FromUTF8(const std::string& _str)
{
	return GetMBSFormWCS(_str, "UTF8");
}

EXPLICIT_DECLARATION(char);
EXPLICIT_DECLARATION(wchar_t);
EXPLICIT_DECLARATION(char8_t);
EXPLICIT_DECLARATION(char16_t);
EXPLICIT_DECLARATION(char32_t);
