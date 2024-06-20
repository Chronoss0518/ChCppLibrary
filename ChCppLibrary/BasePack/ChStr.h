#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 4996
#endif

#include"ChStd.h"

#ifdef CRT
#include<string>
#include<cstdlib>
#include<cstring>
#include<wchar.h>

#ifndef CPP20
#include <codecvt>
#include <cassert>
#include <locale>
#endif

#endif

namespace ChStr
{

	///////////////////////////////////////////////////////////////////////////////////

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T>
	static inline T StrBinaryToNum(
		const unsigned char* const _str
		, const size_t& _sPos = 0)
	{
		T _setData = static_cast<T>(0);
		for (unsigned char i = 0; i < sizeof(T); i++)
		{
			if (_str[_sPos + i] == 0)break;

			unsigned char test = _str[_sPos + i];
			if (test <= 0)continue;
			_setData += static_cast<T>(test << 8 * ((sizeof(T) - 1) - i));
		}
		return _setData;
	}

	///////////////////////////////////////////////////////////////////////////////////

#ifdef CRT
	//クラス名を取得する関数//
	template<typename CharaType,class T = int>
	static inline std::basic_string<CharaType> GetTypeName()
	{
		std::basic_string<CharaType> tmpStr = typeid(T).name();


		size_t tmp = tmpStr.find(static_cast<CharaType>(' '));
		if (tmp == std::basic_string<CharaType>::npos)tmp = 0;
		else tmp += 1;

		return &tmpStr[tmp];
	}
#endif

#ifdef CRT
	//文字の置き換え//
	template<typename CharaType>
	std::basic_string<CharaType> StrReplase(
		const std::basic_string<CharaType>& _base,
		const std::basic_string<CharaType>& _before,
		const std::basic_string<CharaType>& _after = ChStd::GetZeroChara())
	{
		if (_base.find(_before) == _base.npos)return _base;

		std::basic_string<CharaType> out = ChStd::GetZeroChara();

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
#endif

#ifdef CRT
	//空文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToWhiteSpaceChars(const std::basic_string<CharaType>& _str)
	{

		std::basic_string<CharaType> out = ChStd::GetZeroChara();

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
#endif

#ifdef CRT
	//指定した文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToChars(
		const std::basic_string<CharaType>& _str,
		const std::basic_string<CharaType>& _removeChars)
	{

		std::basic_string<CharaType> out = ChStd::GetZeroChara();

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] == _removeChars)continue;

			out = out + _str[i];

		}

		return out;
	}
#endif

#ifdef CRT
	//数値に変換可能な文字以外の文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToUnNums(const std::basic_string<CharaType>& _str)
	{

		std::string out = ChStd::GetZeroChara();

		const CharaType startNum = static_cast<CharaType>('0');
		const CharaType endNum = static_cast<CharaType>('9');

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			bool conFlg = false;

			if (_str[i] < startNum)conFlg = true;
			if (_str[i] > endNum)conFlg = true;

			if (_str[i] == static_cast<CharaType>('.'))conFlg = false;
			if (_str[i] == static_cast<CharaType>('-'))conFlg = false;

			if (conFlg)continue;

			out = out + _str[i];

		}

		return out;
	}
#endif

#ifdef CRT
	//対象の文字で区切り配列にする//
	template<typename CharaType>
	std::vector<std::basic_string<CharaType>> Split(
		const std::basic_string<CharaType>& _str,
		const std::basic_string<CharaType>& _splitChar)
	{
		std::vector<std::basic_string<CharaType>> out;

		unsigned long nowPos = 0;
		unsigned long testPos = _str.find(_splitChar, nowPos);

		if (testPos == std::string::npos)
		{
			out.push_back(_str);
			return out;
	}

		while (testPos != std::basic_string<CharaType>::npos)
		{
			unsigned long tmp = testPos - nowPos;
			out.push_back(tmp != 0 ? _str.substr(nowPos, testPos - nowPos) : ChStd::GetZeroChara());
			nowPos = testPos + _splitChar.size();
			testPos = _str.find(_splitChar, nowPos);
		}

		out.push_back(_str.substr(nowPos));

		return out;
	}
#endif

#ifdef CRT
	//指定されたコード値の範囲の文字のみを返す//
	template<typename CharaType>
	std::basic_string<CharaType> GetCharsToRangeCode(
		const std::basic_string<CharaType>& _str,
		const CharaType _min,
		const CharaType _max)
	{

		std::basic_string<CharaType> out = ChStd::GetZeroChara();

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] > _max || _str[i] < _min)continue;

			out = out + _str[i];

		}

		return out;
	}
#endif

#ifdef CRT
	template<typename CharaType,typename BaseType>
	inline auto GetIntegialFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::basic_string<CharaType> useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		if (useText.empty())return static_cast<BaseType>(0);

		long long tmp = std::stoll(useText.c_str());

		return static_cast<BaseType>(tmp);

	}
#endif

#ifdef CRT
	template<typename CharaType,typename BaseType>
	inline auto GetFloatingFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::basic_string<CharaType> useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		if (useText.empty())return static_cast<BaseType>(0.0);

		double tmp = std::stof(useText.c_str());

		return static_cast<BaseType>(tmp);
	}
#endif

#ifdef CRT
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
	std::wstring UTF8ToWString(const std::string& _str)
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
#endif

}


#endif