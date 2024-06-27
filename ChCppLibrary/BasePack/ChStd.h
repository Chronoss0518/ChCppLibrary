#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

#ifdef __cplusplus
#if __cplusplus > 200000L

#ifndef CPP20
#define CPP20
#endif

#endif
#endif 

#ifdef _MSVC_LANG  
#if _MSVC_LANG > 202000L

#ifndef CPP20
#define CPP20
#endif

#endif
#endif

#ifndef TO_CHAR
#define TO_CHAR(Text) Text
#endif

#ifndef TO_WCHAR
#define TO_WCHAR(Text) L##Text
#endif

#ifndef TO_CHAR16
#define TO_CHAR16(Text) u##Text
#endif

#ifndef TO_CHAR32
#define TO_CHAR32(Text) U##Text
#endif

#ifdef CPP20
#ifndef TO_CHAR8
#define TO_CHAR8(Text) u8##Text
#endif
#endif

#ifndef DECIMAL_NUM_TEXT
#define DECIMAL_NUM_TEXT(Text) Text##"01234456789"
#endif

#ifndef HEXA_NUM_TEXT
#define HEXA_NUM_TEXT(Text) Text##"01234456789ABCDE"
#endif

#ifndef OCTAL_NUM_TEXT
#define OCTAL_NUM_TEXT(Text) Text##"012344567"
#endif

#ifndef BINARY_NUM_TEXT
#define BINARY_NUM_TEXT(Text) Text##"01"
#endif

#ifndef BASE_64_NUM_TEXT
#define BASE_64_NUM_TEXT(Text) Text##"ABCDEFGHIJKLMNOPQRSTUVWXYZ" Text##"abcdefghijklmnopqrstuvwxyz" Text##"0123456789+/"
#endif

#ifndef NUMBER_FUNCTION_BASE
#define NUMBER_FUNCTION_BASE(Function,Type)template<typename CharaType>\
static auto Function ()->typename std::enable_if<std::is_same< Type ,CharaType>::value , const CharaType*>::type
#endif

#ifdef CRT
#ifndef CPP20
#ifndef TO_NUMBER_TEXT_FUNCTION
#define TO_NUMBER_TEXT_FUNCTION(FunctionDefine,ToDefine)\
FunctionDefine(char) { return ToDefine(""); }\
FunctionDefine(wchar_t) { return ToDefine(L); }\
FunctionDefine(char16_t) { return ToDefine(u); }\
FunctionDefine(char32_t) { return ToDefine(U); }
#endif //TO_NUMBER_TEXT_FUNCTION//
#else //CPP20//
#ifndef TO_NUMBER_TEXT_FUNCTION
#define TO_NUMBER_TEXT_FUNCTION(FunctionDefine,ToDefine)\
FunctionDefine(char) { return ToDefine(""); }\
FunctionDefine(wchar_t) { return ToDefine(L); }\
FunctionDefine(char16_t) { return ToDefine(u); }\
FunctionDefine(char32_t) { return ToDefine(U); }\
FunctionDefine(char8_t) { return ToDefine(u8); }
#endif //TO_NUMBER_TEXT_FUNCTION//
#endif //CPP20//
#endif //CRT//

#ifdef CRT

#ifndef CPP20
#ifndef TO_NUMBER_FUNCTION
#define TO_NUMBER_FUNCTION(FunctionDefine,Chara)\
FunctionDefine(char) { return TO_CHAR(Chara); }\
FunctionDefine(wchar_t) { return TO_WCHAR(Chara); }\
FunctionDefine(char16_t) { return TO_CHAR16(Chara); }\
FunctionDefine(char32_t) { return TO_CHAR32(Chara); }
#endif

#else
#ifndef TO_NUMBER_FUNCTION
#define TO_NUMBER_FUNCTION(FunctionDefine,Chara)\
FunctionDefine(char) { return TO_CHAR(Chara); }\
FunctionDefine(wchar_t) { return TO_WCHAR(Chara); }\
FunctionDefine(char16_t) { return TO_CHAR16(Chara); }\
FunctionDefine(char32_t) { return TO_CHAR32(Chara); }\
FunctionDefine(char8_t) { return TO_CHAR8(Chara); }
#endif
#endif
#endif

#ifndef DECIMAL_NUMBUR_FUNCTION
#define DECIMAL_NUMBUR_FUNCTION(type) NUMBER_FUNCTION_BASE(DECIMAL_NUMBUR,type)
#endif

#ifndef HEXA_DECIMAL_FUNCTION
#define HEXA_DECIMAL_FUNCTION(type) NUMBER_FUNCTION_BASE(HEXA_DECIMAL,type)
#endif

#ifndef OCTAL_FUNCTION
#define OCTAL_FUNCTION(type) NUMBER_FUNCTION_BASE(OCTAL,type)
#endif

#ifndef BINARY_FUNCTION
#define BINARY_FUNCTION(type) NUMBER_FUNCTION_BASE(BINARY_NUMBER,type)
#endif

#ifndef BASE_64_FUNCTION
#define BASE_64_FUNCTION(type) NUMBER_FUNCTION_BASE(BASE_NUMBER_64,type)
#endif

#ifndef ZERO_CHARA_FUNCTION
#define ZERO_CHARA_FUNCTION(type) NUMBER_FUNCTION_BASE(GetZeroChara,type)
#endif

#ifndef HYPHEN_CHARA_FUNCTION
#define HYPHEN_CHARA_FUNCTION(type) NUMBER_FUNCTION_BASE(GetHyphenChara,type)
#endif




#ifdef CRT
#include<vector>
#include<map>
#include<cmath>
#include<string>
#endif

//ChLibraryのベースとなる関数、変数群のまとまり//
namespace ChStd
{
#ifdef CRT
	//10進数//
	TO_NUMBER_TEXT_FUNCTION(DECIMAL_NUMBUR_FUNCTION, DECIMAL_NUM_TEXT);
#endif

#ifdef CRT
	//16進数//
	TO_NUMBER_TEXT_FUNCTION(HEXA_DECIMAL_FUNCTION, HEXA_NUM_TEXT);
#endif

#ifdef CRT
	//8進数//
	TO_NUMBER_TEXT_FUNCTION(OCTAL_FUNCTION, OCTAL_NUM_TEXT);
#endif

#ifdef CRT
	//2進数//
	TO_NUMBER_TEXT_FUNCTION(BINARY_FUNCTION, BINARY_NUM_TEXT);
#endif

#ifdef CRT
	//64進数//
	TO_NUMBER_TEXT_FUNCTION(BASE_64_FUNCTION, BASE_64_NUM_TEXT);
#endif

#ifdef CRT
	TO_NUMBER_FUNCTION(ZERO_CHARA_FUNCTION, "\0");
#endif

#ifdef CRT
	TO_NUMBER_FUNCTION(HYPHEN_CHARA_FUNCTION, "-");
#endif


#ifdef _WINDOWS_
	//Windowsで使用される相対パス・絶対パスの最大文字数//
	static constexpr unsigned short W_MAX_PATH_LEN
#ifdef WIN32
		= 258;
#else
		= 258;
#endif
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	//StanderdFunction
	///////////////////////////////////////////////////////////////////////////////////////

	constexpr static unsigned char MAX_CHAR_BIT = 1 << 7;
	constexpr static unsigned short MAX_SHORT_BIT = 1 << 15;
	constexpr static unsigned long MAX_LONG_BIT = 1 << 31;
	constexpr static unsigned long long MAX_LLONG_BIT = 1ull << 63;

#ifdef WIN32
	constexpr static unsigned int W_MAX_INT_BIT = MAX_SHORT_BIT;
#else
	constexpr static unsigned int W_MAX_INT_BIT = MAX_LONG_BIT;
#endif

#ifdef CRT
	//EnumClassを基底型へキャストするためのクラス//
	template<typename Enum>
	constexpr static inline auto EnumCast(const Enum _enum) -> typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}
#endif

	//指定したアドレス先を値0で初期化する//
	template<class T>
	static inline void MZero(T* _val)
	{
		void* tmp = static_cast<void*>(_val);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmp) + i) = 0;
		}
	}

	//_baseの情報を_copyへコピーする//
	template<class T>
	static inline void MCopy(T* _copy, const T* _base)
	{
		void* tmpCopy = static_cast<void*>(_copy);
		const void* tmpBase = static_cast<const void*>(_base);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmpCopy) + i) = *(static_cast<const char*>(tmpBase) + i);
		}
	}

	template<typename Type>
	static inline Type BinaryToNumWithLittleEndian(const unsigned char* _binary, unsigned long _pos = 0)
	{
		if (_pos + sizeof(Type) >= _binary.size())return 0;

		Type num = 0;

		void* tmp = &num;

		for (unsigned long i = 0; i < sizeof(Type); i++)
		{
			auto& test = reinterpret_cast<char*>(tmp)[i];

			test = (_binary[i + _pos]);
		}

		return num;

	}

	template<typename Type>
	static inline Type BinaryToNumWithBigEndian(const unsigned char* _binary, unsigned long _pos = 0)
	{

		if (_pos + sizeof(Type) >= _binary.size())return 0;

		Type num = 0;

		void* tmp = &num;

		for (unsigned long i = sizeof(Type) - 1; i >= 0; i--)
		{
			auto& test = reinterpret_cast<unsigned char*>(tmp)[sizeof(Type) - i - 1];

			test = (_binary[i + _pos]);

			if (i == 0)break;
		}



		return num;

	}

#ifdef CRT
	template<typename CharaType>
	//10進数の数値を入れると指定した配列によって生成された進数表記で出力される//
	std::basic_string<CharaType> DecimalNumberToBaseNumber(
		const long _decimal,
		const std::basic_string<CharaType>& _baseNumber = HEXA_DECIMAL<CharaType>())
	{
		long decimal = 0;

		unsigned long size = _baseNumber.size();

		std::basic_string<CharaType> testRes = GetZeroChara<CharaType>();

		if (_decimal < 0)
		{
			decimal = -_decimal;
			testRes += GetHyphenChara<CharaType>();
		}

		unsigned long base = decimal / size;

		testRes += _baseNumber[decimal % size];

		if (base == 0)
		{
			return testRes;
		}

		std::basic_string<CharaType> out = DecimalNumberToBaseNumber(base, _baseNumber);

		out = out + testRes[0];

		return out;
	}
#endif

#ifdef CRT
	//指定した進数の配列を入れると10進数の数値が出力される//
	template<typename CharaType>
	long BaseNumberToDecimalNumber(
		const std::basic_string<CharaType>& _decimal,
		const std::basic_string<CharaType>& _baseNumber = HEXA_DECIMAL<CharaType>())
	{
		long out = 0;

		std::map<CharaType, long>numMap;

		long size = _baseNumber.size();

		numMap[static_cast<CharaType>('-')] = size;

		for (long i = 0; i < size; i++)
		{
			numMap[_baseNumber[i]] = i;
		}

		bool mFlg = numMap[_decimal[0]] == size;

		for (long i = 0; static_cast<unsigned long>(i) < (mFlg ? _decimal.size() - 1 : _decimal.size()); i++)
		{
			long sum = numMap[_decimal[_decimal.size() - i - 1]];

			for (long j = 0; j < (!mFlg ? i : i - 1); j++)
			{
				sum *= size;
			}

			out += sum;
		}

		if (mFlg)out = -out;

		return out;
	}
#endif

#ifdef CRT
	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType>
	std::basic_string<CharaType> ToBaseNumber(
		const std::basic_string<CharaType>& _baseNum,
		const std::basic_string<CharaType>& _beforeBaseNumber = DECIMAL_NUMBUR<CharaType>(),
		const std::basic_string<CharaType>& _afterBaseNumber = HEXA_DECIMAL<CharaType>())
	{
		return DecimalNumberToBaseNumber(ChStd::BaseNumberToDecimalNumber(_baseNum, _beforeBaseNumber), _afterBaseNumber);
	}
#endif

#ifdef CRT
	//指定した新数の配列を入れるとその配列によって数値を置換できるかのテストを行う//
	template<typename CharaType>
	bool IsBaseNumbers(
		const std::basic_string<CharaType>& _baseNum,
		const std::basic_string<CharaType>& _beforeBaseNumber = DECIMAL_NUMBUR<CharaType>())
	{

		bool isSuccessFlg = false;
		bool indexFlg = false;
		bool indexSuccessFlg = false;
		bool pointFlg = false;

		for (unsigned char i = 0; i < _baseNum.size(); i++)
		{
			isSuccessFlg = false;

			for (auto&& numChar : _beforeBaseNumber)
			{
				if (_baseNum[i] != numChar)continue;
				if (indexFlg)indexSuccessFlg = true;
				isSuccessFlg = true;
			}
			if (isSuccessFlg)continue;
			if (_baseNum[i] == static_cast<CharaType>('.'))
			{
				if (!pointFlg)
				{
					pointFlg = true;
					continue;
				}
			}
			if (_baseNum[i] == static_cast<CharaType>('E') || _baseNum[i] == static_cast<CharaType>('e'))
			{
				if (!indexFlg)
				{
					indexFlg = true;
					i++;
					if (_baseNum[i] == static_cast<CharaType>('+') || _baseNum[i] == static_cast<CharaType>('-'))continue;
					i--;
					continue;
				}
			}
			return false;

		}

		if (!indexSuccessFlg && indexFlg)return false;

		return true;
	}
#endif

#ifdef CRT
	template<typename Type>
	static inline std::map<Type, unsigned long> CreateHuffmanTree(const std::vector<Type>& _binary)
	{
		std::map<Type, unsigned long>out;

		return out;
	}
#endif

}

#endif