#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 4996
#endif

#include"ChStd.h"
#include"ChPtr.h"

#ifdef CRT
#include<string>
#include<cstdlib>
#include<cstring>
#include<wchar.h>
#include<stddef.h>

#ifndef CPP20
#include <codecvt>
#include <cassert>
#include <locale>
#endif

#endif

#ifndef	CH_IS_INTEGETR_TYPE
#define CH_IS_INTEGETR_TYPE(Type)\
->typename std::enable_if<std::is_integral<Type>::value&& \
!std::is_same<bool, Type>::value, Type>::type
#endif

#ifndef	CH_IS_FLOATING_TYPE
#define CH_IS_FLOATING_TYPE(Type)\
->typename std::enable_if<std::is_floating_point<Type>::value, Type>::type
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
		const std::basic_string<CharaType>& _after = ChStd::GetZeroChara<CharaType>())
	{
		if (_base.find(_before) == _base.npos)return _base;

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
#endif

#ifdef CRT
	//空文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToWhiteSpaceChars(const std::basic_string<CharaType>& _str)
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
	std::basic_string<CharaType> RemoveToUnNumCharas(const std::basic_string<CharaType>& _str)
	{
		if (_str.length() <= 0)return  _str;

		std::basic_string<CharaType> out = ChStd::GetZeroChara<CharaType>();

		const CharaType startNum = static_cast<CharaType>('0');
		const CharaType endNum = static_cast<CharaType>('9');

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] < startNum || _str[i] > endNum)continue;

			out = out + _str[i];
		}

		return out;
	}

	//数値に変換可能な文字以外の文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToUnFloatingNumCharas(
		const std::basic_string<CharaType>& _str,
		unsigned long* _ePosition = nullptr,
		unsigned long* _colonPoint = nullptr)
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
			if (i == 0 && _str[i] > mChara)conFlg = false;

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
			out += RemoveToUnNumCharas<CharaType>(&_str[ePosition]);
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
			out.push_back(tmp != 0 ? _str.substr(nowPos, testPos - nowPos) : ChStd::GetZeroChara<CharaType>());
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

	namespace BaseFunctions
	{
#ifdef CRT

		template<typename CharaType>
		inline long double GetExponentialFromTextBase(const std::basic_string<CharaType>& _text)
		{
			if (_text.empty())return 0.0f;

			unsigned long tmp = 0.0;
			for (unsigned long i = 0; i < _text.size(); i++)
			{
				tmp *= 10;
				tmp += static_cast<unsigned long>(_text[i] - static_cast<CharaType>('0'));
			}

			long double res = 1.0f;

			for (unsigned long i = 0; i < tmp; i++)
			{
				res *= 10.0;
			}

			return res;
		}

#endif
	}

#ifdef CRT

#if true

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType, typename CharaType>
	static inline auto GetNumFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos) -> typename std::enable_if<std::is_same<char, CharaType>::value && std::is_integral<BaseType>::value, BaseType>::type
	{
		std::basic_string<CharaType> text = RemoveToUnFloatingNumCharas<CharaType>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(std::atoll(text.c_str()));
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType, typename CharaType>
	static inline auto GetNumFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos) -> typename std::enable_if<std::is_same<char, CharaType>::value&& std::is_floating_point<BaseType>::value, BaseType>::type
	{
		std::basic_string<CharaType> text = RemoveToUnFloatingNumCharas<CharaType>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(std::atof(text.c_str()));
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType, typename CharaType>
	static inline auto GetNumFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos) -> typename std::enable_if<std::is_same<wchar_t, CharaType>::value&& std::is_integral<BaseType>::value, BaseType>::type
	{
		std::basic_string<CharaType> text = RemoveToUnFloatingNumCharas<CharaType>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(_wtoll(text.c_str()));
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType, typename CharaType>
	static inline auto GetNumFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos) -> typename std::enable_if<std::is_same<wchar_t, CharaType>::value&& std::is_floating_point<BaseType>::value, BaseType>::type
	{
		std::basic_string<CharaType> text = RemoveToUnFloatingNumCharas<CharaType>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(_wtof(text.c_str()));
	}

#else

	template<typename BaseType, typename CharaType>
	inline auto GetNumFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos)
	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::basic_string<CharaType> useText = _text.substr(_startPos, endPos - _startPos);

		if (useText.empty())return static_cast<BaseType>(0.0);
		unsigned long colonPosition = -1;
		unsigned long ePosition = -1;
		useText = RemoveToUnFloatingNumCharas<CharaType>(useText, &ePosition, &colonPosition);
		if (useText.empty())return static_cast<BaseType>(0.0);

		unsigned long loopSize = -1;
		loopSize = loopSize > colonPosition ? colonPosition : loopSize;
		long double res = 0.0l;
		if (useText.size() > loopSize)
		{
			for (unsigned long i = 0; i < loopSize; i++)
			{
				res *= 10.0l;
				res += static_cast<long long>(useText[i] - static_cast<CharaType>('0'));
			}
			loopSize = useText.size();
			loopSize = loopSize > ePosition ? ePosition : loopSize;
			long double tmp = 0.0l;
			for (unsigned long i = 1; i < loopSize; i++)
			{
				tmp /= 10.0l;
				tmp += static_cast<long long>(useText[loopSize - i] - static_cast<CharaType>('0'));
			}
			res += tmp;
		}
		else
		{

			for (unsigned long i = 0; i < useText.size(); i++)
			{
				res *= 10.0l;
				res += static_cast<long long>(useText[i] - static_cast<CharaType>('0'));
			}
		}


		if (ePosition < useText.size())
		{
			std::basic_string<CharaType> test = &useText[ePosition];
			long double exponential = BaseFunctions::GetExponentialFromTextBase<CharaType>(&useText[ePosition]);

			res = useText[ePosition - 1] == static_cast<CharaType>('-') ?
				res / exponential : res * exponential;
		}

		return  static_cast<BaseType>(res);
	}

#endif

#endif

#ifdef CRT

#if true

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	static inline auto GetTextFromNum(const InType& _baseNum)-> typename std::enable_if<std::is_same<char,CharaType>::value, std::basic_string<CharaType>>::type
	{
		return std::to_string(_baseNum);
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	static inline auto GetTextFromNum(const InType& _baseNum) -> typename std::enable_if<std::is_same<wchar_t, CharaType>::value, std::basic_string<CharaType>>::type
	{
		return std::to_wstring(_baseNum);
	}

#else

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	static inline std::basic_string<CharaType> GetTextFromNum(const InType& _baseNum)
	{
		return BaseFunctions::GetTextFromNumBase<CharaType, InType>(_baseNum);
	}

#endif

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