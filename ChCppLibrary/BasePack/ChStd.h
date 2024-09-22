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

#ifndef CH_NUMBER_FUNCTION_BASE
#define CH_NUMBER_FUNCTION_BASE(Function)template<typename CharaType>\
static const CharaType* Function()
#endif

#ifndef CH_NUMBER_FUNCTION
#define CH_NUMBER_FUNCTION(Function,Type)\
template<> constexpr static inline const Type* Function()
#endif

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


#include"../CRTPack/ChVectorPack/ChVectorPack.h"
#include"../CRTPack/ChMapPack/ChMapPack.h"
#include"../CRTPack/ChStringPack/ChStringPack.h"

//ChLibraryのベースとなる関数、変数群のまとまり//
namespace ChStd
{
	//10進数//
	CH_NUMBER_FUNCTION_BASE(DECIMAL_NUMBUR);
	//16進数//
	CH_NUMBER_FUNCTION_BASE(HEXA_DECIMAL);
	//8進数//
	CH_NUMBER_FUNCTION_BASE(OCTAL);
	//2進数//
	CH_NUMBER_FUNCTION_BASE(BINARY_NUMBER);
	//64進数//
	CH_NUMBER_FUNCTION_BASE(BASE_NUMBER_64);
	//"\0"//
	CH_NUMBER_FUNCTION_BASE(GetZeroChara);
	//"0"//
	CH_NUMBER_FUNCTION_BASE(Get0Chara);
	//"-"//
	CH_NUMBER_FUNCTION_BASE(GetHyphenChara);
	//"\r\n"//
	CH_NUMBER_FUNCTION_BASE(GetCRLFChara);
	//"\r//
	CH_NUMBER_FUNCTION_BASE(GetCRChara);
	//"\n"//
	CH_NUMBER_FUNCTION_BASE(GetLFChara);
	//"\b"//
	CH_NUMBER_FUNCTION_BASE(GetBackChara);
	//"\f"//
	CH_NUMBER_FUNCTION_BASE(GetNextPageChara);
	//"\t"//
	CH_NUMBER_FUNCTION_BASE(GetTabChara);
	//","//
	CH_NUMBER_FUNCTION_BASE(GetCommaChara);
	//"."//
	CH_NUMBER_FUNCTION_BASE(GetDotChara);
	//";"//
	CH_NUMBER_FUNCTION_BASE(GetSemiColonChara);
	//":"//
	CH_NUMBER_FUNCTION_BASE(GetDoubleColonChara);
	//" "//
	CH_NUMBER_FUNCTION_BASE(GetSpaceChara);
	//"/"//
	CH_NUMBER_FUNCTION_BASE(GetSlashChara);
	//"\\"//
	CH_NUMBER_FUNCTION_BASE(GetYenChara);
	//"("//
	CH_NUMBER_FUNCTION_BASE(GetStartParenthesesChara);
	//")"//
	CH_NUMBER_FUNCTION_BASE(GetEndParenthesesChara);
	//"{"//
	CH_NUMBER_FUNCTION_BASE(GetStartBraceChara);
	//"}"//
	CH_NUMBER_FUNCTION_BASE(GetEndBraceChara);
	//"["//
	CH_NUMBER_FUNCTION_BASE(GetStartBracketChara);
	//"]"//
	CH_NUMBER_FUNCTION_BASE(GetEndBracketChara);
	//"\'"//
	CH_NUMBER_FUNCTION_BASE(GetSGQuotation);
	//"\""//
	CH_NUMBER_FUNCTION_BASE(GetDBQuotation);
	//"*"//
	CH_NUMBER_FUNCTION_BASE(GetAsterisk);

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
	constexpr static inline typename std::underlying_type<Enum>::type EnumCast(const Enum _enum)
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
	static inline Type BinaryToNumWithLittleEndian(const ChCRT::VectorPack<unsigned char>& _binary, unsigned long _pos = 0)
	{
		if (_pos + sizeof(Type) >= _binary.GetSize())return 0;

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
	static inline Type BinaryToNumWithBigEndian(const ChCRT::VectorPack<unsigned char>& _binary, unsigned long _pos = 0)
	{
		if (_pos + sizeof(Type) >= _binary.GetSize())return 0;

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

	template<typename CharaType>
	//10進数の数値を入れると指定した配列によって生成された進数表記で出力される//
	static inline ChCRT::StringPack<CharaType> DecimalNumberToBaseNumber(
		const long _decimal,
		const ChCRT::StringPack<CharaType>& _baseNumber = HEXA_DECIMAL<CharaType>())
	{
		long decimal = 0;

		unsigned long size = _baseNumber.GetSize();

		ChCRT::StringPack<CharaType> testRes = GetZeroChara<CharaType>();

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

		ChCRT::StringPack<CharaType> out = DecimalNumberToBaseNumber(base, _baseNumber);

		out = out + testRes[0];

		return out;
	}

	//指定した進数の配列を入れると10進数の数値が出力される//
	template<typename CharaType>
	static inline long BaseNumberToDecimalNumber(
		const ChCRT::StringPack<CharaType>& _decimal,
		const ChCRT::StringPack<CharaType>& _baseNumber = HEXA_DECIMAL<CharaType>())
	{
		long out = 0;

		ChCRT::MapPack<CharaType, long>numMap;

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

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	template<typename CharaType>
	static inline ChCRT::StringPack<CharaType> ToBaseNumber(
		const ChCRT::StringPack<CharaType>& _baseNum,
		const ChCRT::StringPack<CharaType>& _beforeBaseNumber = DECIMAL_NUMBUR<CharaType>(),
		const ChCRT::StringPack<CharaType>& _afterBaseNumber = HEXA_DECIMAL<CharaType>())
	{
		return DecimalNumberToBaseNumber(ChStd::BaseNumberToDecimalNumber(_baseNum, _beforeBaseNumber), _afterBaseNumber);
	}

	//指定した新数の配列を入れるとその配列によって数値を置換できるかのテストを行う//
	template<typename CharaType>
	static inline bool IsBaseNumbers(
		const ChCRT::StringPack<CharaType>& _baseNum,
		const ChCRT::StringPack<CharaType>& _beforeBaseNumber = DECIMAL_NUMBUR<CharaType>())
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