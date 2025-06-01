#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

#include<vector>
#include<string>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 4996
#endif

#include<cstdlib>
#include<wchar.h>
#include<stddef.h>

#ifndef CPP26
#include <codecvt>
#include <cassert>
#endif

#include <locale>

#include"ChStd.h"
#include"ChPtr.h"

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
	template<typename T>
	struct Bytes
	{
		Bytes(){}

		union
		{
			unsigned char byte[sizeof(T)];
			T val;
		};
	};

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T,typename CharaType>
	inline T StrBinaryToNum(
		const CharaType* const _str,
		const unsigned long _strLen,
		const size_t& _sPos = 0,
		const bool _reverseFlg = false)
	{
		Bytes<T> res;
		unsigned long readCharaCount = sizeof(T) / sizeof(CharaType);

		if (_strLen < readCharaCount - _sPos)return res.val;

		for (unsigned long i = 0; i < readCharaCount; i++)
		{
			void* tmp = const_cast<CharaType*>(&_str[_sPos + i]);

			for (unsigned char j = 0; j < sizeof(CharaType); j++)
			{
				unsigned long tmpLen = j + (i * sizeof(CharaType));
				res.byte[tmpLen] = *(reinterpret_cast<unsigned char*>(tmp) + j);
			}
		}
		return res.val;
	}

	//クラス名を取得する関数//
	template<typename CharaType, class T = int>
	inline std::basic_string<CharaType> GetTypeName()
	{
		std::basic_string<CharaType> tmpStr = typeid(T).name();

		size_t tmp = tmpStr.GetFindPosition(static_cast<CharaType>(' '));
		if (tmp == std::basic_string<CharaType>::NPos())tmp = 0;
		else tmp += 1;

		return &tmpStr[tmp];
	}

	//文字の置き換え//
	template<typename CharaType>
	std::basic_string<CharaType> StrReplase(
		const std::basic_string<CharaType>& _base,
		const std::basic_string<CharaType>& _before,
		const std::basic_string<CharaType>& _after = ChStd::GetZeroChara<CharaType>());

	//空文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToWhiteSpaceChars(const std::basic_string<CharaType>& _str);

	//指定した文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToChars(
		const std::basic_string<CharaType>& _str,
		const std::basic_string<CharaType>& _removeChars);

	//数値に変換可能な文字以外の文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToUnNumCharas(const std::basic_string<CharaType>& _str);

	//数値に変換可能な文字以外の文字を取り除く//
	template<typename CharaType>
	std::basic_string<CharaType> RemoveToUnFloatingNumCharas(
		const std::basic_string<CharaType>& _str,
		unsigned long* _ePosition = nullptr,
		unsigned long* _colonPoint = nullptr);

	//対象の文字で区切り配列にする//
	template<typename CharaType>
	std::vector<std::basic_string<CharaType>> Split(
		const std::basic_string<CharaType>& _str,
		const std::basic_string<CharaType>& _splitChar);

	//指定されたコード値の範囲の文字のみを返す//
	template<typename CharaType>
	std::basic_string<CharaType> GetCharsToRangeCode(
		const std::basic_string<CharaType>& _str,
		const CharaType _min,
		const CharaType _max);

	namespace BaseFunctions
	{
		template<typename CharaType>
		static long double GetExponentialFromTextBase(const std::basic_string<CharaType>& _text)
		{
			if (_text.size() <= 0)return 0.0f;

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
	}

#if true

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_integral<BaseType>::value, BaseType>::type GetNumFromText(
		const std::basic_string<char>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<char>::npos)
	{
		std::basic_string<char> text = RemoveToUnFloatingNumCharas<char>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(atoll(text.c_str()));
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_integral<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<wchar_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<wchar_t>::npos)
	{
		std::basic_string<wchar_t> text = RemoveToUnFloatingNumCharas<wchar_t>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(wcstoll(text.c_str(),nullptr,10));
	}

#ifdef CPP20

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_integral<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<char8_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<char8_t>::npos)
	{
		return 0;
	}

#endif

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_integral<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<char16_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<char16_t>::npos)
	{
		return 0;
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_integral<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<char32_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<char32_t>::npos)
	{
		return 0;
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_floating_point<BaseType>::value, BaseType>::type GetNumFromText(
		const std::basic_string<char>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<char>::npos)
	{
		std::basic_string<char> text = RemoveToUnFloatingNumCharas<char>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(atof(text.c_str()));
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	static inline typename std::enable_if<std::is_floating_point<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<wchar_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<wchar_t>::npos)
	{
		std::basic_string<wchar_t> text = RemoveToUnFloatingNumCharas<wchar_t>(_text.substr(_startPos, _endPos - _startPos));
		return static_cast<BaseType>(wcstold(text.c_str(),nullptr));
	}

#ifdef CPP20

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	inline typename std::enable_if<std::is_floating_point<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<char8_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<char8_t>::npos)
	{
		return 0.0f;
	}

#endif

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	inline typename std::enable_if<std::is_floating_point<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<char16_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<char16_t>::npos)
	{
		return 0.0f;
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename BaseType>
	inline typename std::enable_if<std::is_floating_point<BaseType>::value, BaseType>::type
		GetNumFromText(
			const std::basic_string<char32_t>& _text,
			const size_t& _startPos = 0,
			const size_t& _endPos = std::basic_string<char32_t>::npos)
	{
		return 0.0f;
	}

#else

	template<typename BaseType, typename CharaType>
	inline BaseType GetNumFromText(
		const std::basic_string<CharaType>& _text,
		const size_t& _startPos = 0,
		const size_t& _endPos = std::basic_string<CharaType>::npos)
	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
			endPos = _text.size();

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

			res = useText[ePosition - 1] == static_cast<CharaType>('-') ? res / exponential : res * exponential;
		}

		return  static_cast<BaseType>(res);
	}

#endif


#if true

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	inline typename std::enable_if<std::is_same<char, CharaType>::value, std::basic_string<CharaType>>::type GetTextFromNum(const InType& _baseNum)
	{
		return std::to_string(_baseNum);
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	inline typename std::enable_if<std::is_same<wchar_t, CharaType>::value, std::basic_string<CharaType>>::type GetTextFromNum(const InType& _baseNum)
	{
		return std::to_wstring(_baseNum);
	}


#ifdef CPP20

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	static inline typename std::enable_if<std::is_same<char8_t, CharaType>::value, std::basic_string<CharaType>>::type GetTextFromNum(const InType& _baseNum)
	{
		return u8"";
	}

#endif

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	inline typename std::enable_if<std::is_same<char16_t, CharaType>::value, std::basic_string<CharaType>>::type GetTextFromNum(const InType& _baseNum)
	{
		return u"";
	}

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	inline typename std::enable_if<std::is_same<char32_t, CharaType>::value, std::basic_string<CharaType>>::type GetTextFromNum(const InType& _baseNum)
	{
		return U"";
	}

#else

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType, typename InType>
	inline std::basic_string<CharaType> GetTextFromNum(const InType& _baseNum)
	{
		return BaseFunctions::GetTextFromNumBase<CharaType, InType>(_baseNum);
	}

#endif

	std::string GetShiftJisFromUTF16(const std::wstring& _str);

	std::wstring GetUTF16FromShiftJis(const std::string& _str);

	std::string GetUTF8FromUTF16(const std::wstring& _str);

	std::wstring GetUTF16FromUTF8(const std::string& _str);

#ifndef CPP26

	using ConvertUTF8 = std::codecvt_utf8<wchar_t>;
	using ConvertUTF16 = std::codecvt_utf16<wchar_t>;

	static inline std::wstring_convert<ConvertUTF8, wchar_t>& GetU8Converter()
	{
		static std::wstring_convert<ConvertUTF8, wchar_t> strconverter;

		return strconverter;
	}

	static inline std::wstring_convert<ConvertUTF16, wchar_t>& GetU16Converter()
	{
		static std::wstring_convert<ConvertUTF16, wchar_t> strconverter;

		return strconverter;
	}


	//文字列からUTF8のワイド文字列へ変換する//
	static inline std::wstring UTF8ToWString(const std::string& _str)
	{

		return GetU8Converter().from_bytes(_str.c_str());
	}

	//ワイド文字列から文字列へ変換する//
	static inline std::string UTF8ToString(const std::wstring& _str)
	{
		return GetU8Converter().to_bytes(_str.c_str());
	}

	//文字列からUTF16のワイド文字列へ変換する//
	static inline std::wstring UTF16ToWString(const std::string& _str)
	{

		return GetU16Converter().from_bytes(_str.c_str());
	}

	//ワイド文字列から文字列へ変換する//
	static inline std::string UTF16ToString(const std::wstring& _str)
	{
		return GetU16Converter().to_bytes(_str.c_str());
	}
#endif

	template<typename CharaType>
	std::basic_string<CharaType> FormatDocument(
		const std::basic_string<CharaType>& _str,
		const std::vector<CharaType>& _addCRLF,
		const std::vector<CharaType>& _addTab,
		const std::vector<CharaType>& _subTab);

}


#endif