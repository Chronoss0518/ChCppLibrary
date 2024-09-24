
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 4996
#endif

#include"../BaseIncluder/ChBase.h"
#include"ChStr.h"

#define LOCALE_TYPE_COUNT 6

using namespace ChStr;

//文字の置き換え//
template<typename CharaType>
ChCRT::StringPack<CharaType> ChStr::StrReplaseBase(
	const ChCRT::StringPack<CharaType>& _base,
	const ChCRT::StringPack<CharaType>& _before,
	const ChCRT::StringPack<CharaType>& _after)
{
	if (_base.GetFindPosition(_before) == ChCRT::StringPack<CharaType>::GetNPos())return _base;

	ChCRT::StringPack<CharaType> out = ChStd::GetZeroChara<CharaType>();

	size_t tmpPos = 0;
	size_t testPos = 0;

	while (true)
	{
		testPos = _base.GetFindPosition(_before, tmpPos);

		if (testPos == _base.GetNPos())break;

		out += _base.GetSubStr(tmpPos, testPos - tmpPos);
		out += _after;
		tmpPos = testPos + _before.GetLength();
	}
	return out;
}

//空文字を取り除く//
template<typename CharaType>
ChCRT::StringPack<CharaType> ChStr::RemoveToWhiteSpaceCharsBase(const ChCRT::StringPack<CharaType>& _str)
{
	ChCRT::StringPack<CharaType> out = ChStd::GetZeroChara<CharaType>();

	const char whiteSpaceInterfaceChar = 32;
	const char delCharNum = 127;

	for (unsigned long i = 0; i < _str.GetLength(); i++)
	{
		if (_str[i] <= whiteSpaceInterfaceChar)continue;
		if (_str[i] == delCharNum)continue;

		out = out + _str[i];
	}

	return out;
}

//指定した文字を取り除く//
template<typename CharaType>
ChCRT::StringPack<CharaType> ChStr::RemoveToCharsBase(
	const ChCRT::StringPack<CharaType>& _str,
	const ChCRT::StringPack<CharaType>& _removeChars)
{
	ChCRT::StringPack<CharaType> out = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _str.GetLength(); i++)
	{
		if (_str[i] != _removeChars)out += _str[i];
	}

	return out;
}

//数値に変換可能な文字以外の文字を取り除く//
template<typename CharaType>
ChCRT::StringPack<CharaType> ChStr::RemoveToUnNumCharasBase(const ChCRT::StringPack<CharaType>& _str)
{
	if (_str.GetLength() <= 0)return  _str;

	ChCRT::StringPack<CharaType> out = ChStd::GetZeroChara<CharaType>();

	const CharaType mChara = static_cast<CharaType>('-');

	const CharaType startNum = static_cast<CharaType>('0');
	const CharaType endNum = static_cast<CharaType>('9');

	bool conFlg = false;
	for (unsigned long i = 0; i < _str.GetLength(); i++)
	{
		conFlg = false;
		if (_str[i] < startNum)conFlg = true;
		if (_str[i] > endNum)conFlg = true;
		if (out.GetSize() == 0 && _str[i] == mChara)conFlg = false;

		if (!conFlg)out = out + _str[i];
	}
	return out;
}

//数値に変換可能な文字以外の文字を取り除く//
template<typename CharaType>
ChCRT::StringPack<CharaType> ChStr::RemoveToUnFloatingNumCharasBase(
	const ChCRT::StringPack<CharaType>& _str,
	unsigned long* _ePosition,
	unsigned long* _colonPoint)
{
	if (ChPtr::NotNullCheck(_ePosition))*_ePosition = -1;
	if (ChPtr::NotNullCheck(_colonPoint))*_colonPoint = -1;
	if (_str.GetLength() <= 0)return  _str;

	ChCRT::StringPack<CharaType> out = ChStd::GetZeroChara<CharaType>();

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
	for (unsigned long i = 0; i < _str.GetLength(); i++)
	{
		conFlg = false;

		if (_str[i] < startNum)conFlg = true;
		if (_str[i] > endNum)conFlg = true;
		if (out.GetSize() == 0 && _str[i] == mChara)conFlg = false;

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

	if (ePosition < _str.GetLength())
	{
		if (ChPtr::NotNullCheck(_ePosition))*_ePosition = ePosition;
		out += ChStr::RemoveToUnNumCharasBase<CharaType>(&_str[ePosition]);
	}

	return out;
}

//対象の文字で区切り配列にする//
template<typename CharaType>
ChCRT::VectorPack<ChCRT::StringPack<CharaType>> ChStr::SplitBase(
	const ChCRT::StringPack<CharaType>& _str,
	const ChCRT::StringPack<CharaType>& _splitChar)
{
	ChCRT::VectorPack<ChCRT::StringPack<CharaType>> out;

	size_t nowPos = 0;
	size_t testPos = _str.GetFindPosition(_splitChar, nowPos);

	while (testPos != ChCRT::StringPack<CharaType>::GetNPos())
	{
		size_t tmp = testPos - nowPos;
		out.Push(tmp != 0 ? _str.GetSubStr(nowPos, testPos - nowPos).GetString() : ChStd::GetZeroChara<CharaType>());
		nowPos = testPos + _splitChar.GetSize();
		testPos = _str.GetFindPosition(_splitChar, nowPos);
	}

	out.Push(_str.GetSubStr(nowPos));

	return out;
}

//指定されたコード値の範囲の文字のみを返す//
template<typename CharaType>
ChCRT::StringPack<CharaType> ChStr::GetCharsToRangeCodeBase(
	const ChCRT::StringPack<CharaType>& _str,
	const CharaType _min,
	const CharaType _max)
{
	ChCRT::StringPack<CharaType> out = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _str.GetLength(); i++)
	{
		if (_str[i] <= _max && _str[i] >= _min)out = out + _str[i];
	}
	return out;
}

#define EXPLICIT_DECLARATION(_CharaType)\
template ChCRT::StringPack<##_CharaType##> ChStr::StrReplaseBase(\
	const ChCRT::StringPack<##_CharaType##>& _base,\
	const ChCRT::StringPack<##_CharaType##>& _before,\
	const ChCRT::StringPack<##_CharaType##>& _after);\
template ChCRT::StringPack<##_CharaType##> ChStr::RemoveToWhiteSpaceCharsBase(const ChCRT::StringPack<##_CharaType##>& _str);\
template ChCRT::StringPack<##_CharaType##> ChStr::RemoveToCharsBase(\
	const ChCRT::StringPack<##_CharaType##>& _str,\
	const ChCRT::StringPack<##_CharaType##>& _removeChars);\
template ChCRT::StringPack<##_CharaType##> ChStr::RemoveToUnNumCharasBase(const ChCRT::StringPack<##_CharaType##>& _str);\
template ChCRT::StringPack<##_CharaType##> ChStr::RemoveToUnFloatingNumCharasBase(\
	const ChCRT::StringPack<##_CharaType##>& _str,\
	unsigned long* _ePosition,\
	unsigned long* _colonPoint);\
template ChCRT::VectorPack<ChCRT::StringPack<##_CharaType##>> ChStr::SplitBase(\
	const ChCRT::StringPack<##_CharaType##>& _str,\
	const ChCRT::StringPack<##_CharaType##>& _splitChar);\
template ChCRT::StringPack<##_CharaType##> ChStr::GetCharsToRangeCodeBase(\
	const ChCRT::StringPack<##_CharaType##>& _str,\
	const _CharaType _min,\
	const _CharaType _max);

EXPLICIT_DECLARATION(char);
EXPLICIT_DECLARATION(wchar_t);
EXPLICIT_DECLARATION(char8_t);
EXPLICIT_DECLARATION(char16_t);
EXPLICIT_DECLARATION(char32_t);
