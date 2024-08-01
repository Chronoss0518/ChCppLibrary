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

#ifndef CH_TO_CHAR
#define CH_TO_CHAR(Text) Text
#endif

#ifndef CH_TO_WCHAR
#define CH_TO_WCHAR(Text) L##Text
#endif

#ifndef CH_TO_CHAR16
#define CH_TO_CHAR16(Text) u##Text
#endif

#ifndef CH_TO_CHAR32
#define CH_TO_CHAR32(Text) U##Text
#endif

#ifdef CPP20
#ifndef CH_TO_CHAR8
#define CH_TO_CHAR8(Text) u8##Text
#endif
#endif

#ifndef CH_DECIMAL_NUM_TEXT
#define CH_DECIMAL_NUM_TEXT(Text) Text##"01234456789"
#endif

#ifndef CH_HEXA_NUM_TEXT
#define CH_HEXA_NUM_TEXT(Text) Text##"01234456789ABCDE"
#endif

#ifndef CH_OCTAL_NUM_TEXT
#define CH_OCTAL_NUM_TEXT(Text) Text##"012344567"
#endif

#ifndef CH_BINARY_NUM_TEXT
#define CH_BINARY_NUM_TEXT(Text) Text##"01"
#endif

#ifndef CH_BASE_64_NUM_TEXT
#define CH_BASE_64_NUM_TEXT(Text) Text##"ABCDEFGHIJKLMNOPQRSTUVWXYZ" Text##"abcdefghijklmnopqrstuvwxyz" Text##"0123456789+/"
#endif

#ifndef CH_NUMBER_FUNCTION_BASE
#define CH_NUMBER_FUNCTION_BASE(Function,Type)template<typename CharaType>\
constexpr static typename std::enable_if<std::is_same<Type ,CharaType>::value , const CharaType*>::type Function()
#endif

#ifdef CRT
#ifndef CPP20
#ifndef CH_TO_NUMBER_TEXT_FUNCTION
#define CH_TO_NUMBER_TEXT_FUNCTION(FunctionDefine,ToDefine)\
FunctionDefine(char) { return ToDefine(""); }\
FunctionDefine(wchar_t) { return ToDefine(L); }\
FunctionDefine(char16_t) { return ToDefine(u); }\
FunctionDefine(char32_t) { return ToDefine(U); }
#endif //TO_NUMBER_TEXT_FUNCTION//
#else //CPP20//
#ifndef CH_TO_NUMBER_TEXT_FUNCTION
#define CH_TO_NUMBER_TEXT_FUNCTION(FunctionDefine,ToDefine)\
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
#ifndef CH_TO_NUMBER_FUNCTION
#define CH_TO_NUMBER_FUNCTION(FunctionDefine,Chara)\
FunctionDefine(char) { return CH_TO_CHAR(Chara); }\
FunctionDefine(wchar_t) { return CH_TO_WCHAR(Chara); }\
FunctionDefine(char16_t) { return CH_TO_CHAR16(Chara); }\
FunctionDefine(char32_t) { return CH_TO_CHAR32(Chara); }
#endif

#else
#ifndef CH_TO_NUMBER_FUNCTION
#define CH_TO_NUMBER_FUNCTION(FunctionDefine,Chara)\
FunctionDefine(char) { return CH_TO_CHAR(Chara); }\
FunctionDefine(wchar_t) { return CH_TO_WCHAR(Chara); }\
FunctionDefine(char16_t) { return CH_TO_CHAR16(Chara); }\
FunctionDefine(char32_t) { return CH_TO_CHAR32(Chara); }\
FunctionDefine(char8_t) { return CH_TO_CHAR8(Chara); }
#endif
#endif
#endif

#ifndef CH_DECIMAL_NUMBUR_FUNCTION
#define CH_DECIMAL_NUMBUR_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(DECIMAL_NUMBUR,type)
#endif

#ifndef CH_HEXA_DECIMAL_FUNCTION
#define CH_HEXA_DECIMAL_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(HEXA_DECIMAL,type)
#endif

#ifndef CH_OCTAL_FUNCTION
#define CH_OCTAL_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(OCTAL,type)
#endif

#ifndef CH_BINARY_FUNCTION
#define CH_BINARY_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(BINARY_NUMBER,type)
#endif

#ifndef CH_BASE_64_FUNCTION
#define CH_BASE_64_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(BASE_NUMBER_64,type)
#endif

#ifndef CH_ZERO_CHARA_FUNCTION
#define CH_ZERO_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetZeroChara,type)
#endif

#ifndef CH_HYPHEN_CHARA_FUNCTION
#define CH_HYPHEN_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetHyphenChara,type)
#endif

#ifndef CH_CRLF_CHARA_FUNCTION
#define CH_CRLF_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetCRLFChara,type)
#endif

#ifndef CH_LF_CHARA_FUNCTION
#define CH_LF_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetLFChara,type)
#endif

#ifndef CH_COMMA_CHARA_FUNCTION
#define CH_COMMA_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetCommaChara,type)
#endif

#ifndef CH_DOT_CHARA_FUNCTION
#define CH_DOT_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetDotChara,type)
#endif

#ifndef CH_SEMICOLON_CHARA_FUNCTION
#define CH_SEMICOLON_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetSemiColonChara,type)
#endif

#ifndef CH_SPACE_CHARA_FUNCTION
#define CH_SPACE_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetSpaceChara,type)
#endif

#ifndef CH_SLASH_CHARA_FUNCTION
#define CH_SLASH_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetSlashChara,type)
#endif

#ifndef CH_YEN_CHARA_FUNCTION
#define CH_YEN_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetYenChara,type)
#endif

#ifndef CH_START_SQUARE_BRACKETS_CHARA_FUNCTION
#define CH_START_SQUARE_BRACKETS_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetStartSquareBracketsChara,type)
#endif

#ifndef CH_END_SQUARE_BRACKETS_CHARA_FUNCTION
#define CH_END_SQUARE_BRACKETS_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetEndSquareBracketsChara,type)
#endif

#ifndef CH_SINGLE_QUOTATION_CHARA_FUNCTION
#define CH_SINGLE_QUOTATION_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetSGQuotation,type)
#endif

#ifndef CH_DOUBLE_QUOTATION_CHARA_FUNCTION
#define CH_DOUBLE_QUOTATION_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetDBQuotation,type)
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
	CH_TO_NUMBER_TEXT_FUNCTION(CH_DECIMAL_NUMBUR_FUNCTION, CH_DECIMAL_NUM_TEXT);
	//16進数//
	CH_TO_NUMBER_TEXT_FUNCTION(CH_HEXA_DECIMAL_FUNCTION, CH_HEXA_NUM_TEXT);
	//8進数//
	CH_TO_NUMBER_TEXT_FUNCTION(CH_OCTAL_FUNCTION, CH_OCTAL_NUM_TEXT);
	//2進数//
	CH_TO_NUMBER_TEXT_FUNCTION(CH_BINARY_FUNCTION, CH_BINARY_NUM_TEXT);
	//64進数//
	CH_TO_NUMBER_TEXT_FUNCTION(CH_BASE_64_FUNCTION, CH_BASE_64_NUM_TEXT);

	CH_TO_NUMBER_FUNCTION(CH_ZERO_CHARA_FUNCTION, "\0");

	CH_TO_NUMBER_FUNCTION(CH_HYPHEN_CHARA_FUNCTION, "-");

	CH_TO_NUMBER_FUNCTION(CH_CRLF_CHARA_FUNCTION, "\r\n");

	CH_TO_NUMBER_FUNCTION(CH_LF_CHARA_FUNCTION, "\n");

	CH_TO_NUMBER_FUNCTION(CH_COMMA_CHARA_FUNCTION, ",");

	CH_TO_NUMBER_FUNCTION(CH_DOT_CHARA_FUNCTION, ".");

	CH_TO_NUMBER_FUNCTION(CH_SEMICOLON_CHARA_FUNCTION, ";");

	CH_TO_NUMBER_FUNCTION(CH_SPACE_CHARA_FUNCTION, " ");

	CH_TO_NUMBER_FUNCTION(CH_SLASH_CHARA_FUNCTION, "/");

	CH_TO_NUMBER_FUNCTION(CH_YEN_CHARA_FUNCTION, "\\");

	CH_TO_NUMBER_FUNCTION(CH_START_SQUARE_BRACKETS_CHARA_FUNCTION, "{");

	CH_TO_NUMBER_FUNCTION(CH_END_SQUARE_BRACKETS_CHARA_FUNCTION, "}");

	CH_TO_NUMBER_FUNCTION(CH_SINGLE_QUOTATION_CHARA_FUNCTION, "\'");

	CH_TO_NUMBER_FUNCTION(CH_DOUBLE_QUOTATION_CHARA_FUNCTION, "\"");
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