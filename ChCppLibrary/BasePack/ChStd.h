#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

#include<string>
#include<vector>
#include<map>

#ifdef __cplusplus

#if __cplusplus >= 201703L
#ifndef CPP17
#define CPP17
#endif
#endif

#if __cplusplus >= 202002L
#ifndef CPP20
#define CPP20
#endif
#endif

#endif 

#ifdef _MSVC_LANG

#if _MSVC_LANG >= 201703L 
#ifndef CPP17
#define CPP17
#endif
#endif

#if _MSVC_LANG >= 202002L
#ifndef CPP20
#define CPP20
#endif
#endif

#endif

#ifdef CPP17

#include<filesystem>

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

#ifndef CH_TO_CHAR8
#define CH_TO_CHAR8(Text) u8##Text
#endif

#ifndef CH_NUMBER_FUNCTION_BASE
#define CH_NUMBER_FUNCTION_BASE(Function)\
template<typename CharaType>\
const CharaType* Function()
#endif

#ifndef CH_NUMBER_FUNCTION
#define CH_NUMBER_FUNCTION(Function,Type)\
template<> const Type* Function<##Type##>()
#endif

#ifndef CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION
#define CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(_Class)\
template class _Class##<char>;\
template class _Class##<wchar_t>
#endif

#ifdef CPP20
#ifndef CH_TO_NUMBER_TEXT_FUNCTION
#define CH_TO_NUMBER_TEXT_FUNCTION(FunctionDefine,ToDefine)\
FunctionDefine(char) { return ToDefine(""); }\
FunctionDefine(wchar_t) { return ToDefine(L); }\
FunctionDefine(char16_t) { return ToDefine(u); }\
FunctionDefine(char32_t) { return ToDefine(U); }\
FunctionDefine(char8_t) { return ToDefine(u8); }
#endif //TO_NUMBER_TEXT_FUNCTION//

#ifndef CH_TO_NUMBER_FUNCTION
#define CH_TO_NUMBER_FUNCTION(FunctionDefine,Chara)\
FunctionDefine(char) { return CH_TO_CHAR(Chara); }\
FunctionDefine(wchar_t) { return CH_TO_WCHAR(Chara); }\
FunctionDefine(char16_t) { return CH_TO_CHAR16(Chara); }\
FunctionDefine(char32_t) { return CH_TO_CHAR32(Chara); }\
FunctionDefine(char8_t) { return CH_TO_CHAR8(Chara); }
#endif

#ifndef CH_STRING_TYPE_EXPLICIT_DECLARATION
#define CH_STRING_TYPE_EXPLICIT_DECLARATION(_Class)\
template class _Class##<char>;\
template class _Class##<wchar_t>;\
template class _Class##<char8_t>;\
template class _Class##<char16_t>;\
template class _Class##<char32_t>
#endif

#else

#ifndef CH_TO_NUMBER_TEXT_FUNCTION
#define CH_TO_NUMBER_TEXT_FUNCTION(FunctionDefine,ToDefine)\
FunctionDefine(char) { return ToDefine(""); }\
FunctionDefine(wchar_t) { return ToDefine(L); }\
FunctionDefine(char16_t) { return ToDefine(u); }\
FunctionDefine(char32_t) { return ToDefine(U); }
#endif //TO_NUMBER_TEXT_FUNCTION//

#ifndef CH_TO_NUMBER_FUNCTION
#define CH_TO_NUMBER_FUNCTION(FunctionDefine,Chara)\
FunctionDefine(char) { return CH_TO_CHAR(Chara); }\
FunctionDefine(wchar_t) { return CH_TO_WCHAR(Chara); }\
FunctionDefine(char16_t) { return CH_TO_CHAR16(Chara); }\
FunctionDefine(char32_t) { return CH_TO_CHAR32(Chara); }
#endif

#ifndef CH_STRING_TYPE_EXPLICIT_DECLARATION
#define CH_STRING_TYPE_EXPLICIT_DECLARATION(_Class)\
template class _Class##<char>;\
template class _Class##<wchar_t>;\
template class _Class##<char16_t>;\
template class _Class##<char32_t>
#endif

#endif

#ifndef CH_BASE_TYPE_EXPLICIT_DECLARATION
#define CH_BASE_TYPE_EXPLICIT_DECLARATION(_functionDefine)\
_functionDefine(signed char)\
_functionDefine(signed short)\
_functionDefine(signed int)\
_functionDefine(signed long)\
_functionDefine(signed long long)\
_functionDefine(unsigned char)\
_functionDefine(unsigned short)\
_functionDefine(unsigned int)\
_functionDefine(unsigned long)\
_functionDefine(unsigned long long)\
_functionDefine(float)\
_functionDefine(double)\
_functionDefine(long double)
#endif

#ifndef CH_SINGLE_TONE_BASE
#define	CH_SINGLE_TONE_BASE(_ClassNmae)\
private:\
 _ClassName##(){}\
 ~##_ClassName##(){}\
public:\
static inline _ClassName##& GetIns(){ static _ClassName ins; return ins; }
#endif

//ChLibrary�̃x�[�X�ƂȂ�֐��A�ϐ��Q�̂܂Ƃ܂�//
namespace ChStd
{
	//10�i��//
	CH_NUMBER_FUNCTION_BASE(DECIMAL_NUMBUR);
	//16�i��//
	CH_NUMBER_FUNCTION_BASE(HEXA_DECIMAL);
	//8�i��//
	CH_NUMBER_FUNCTION_BASE(OCTAL);
	//2�i��//
	CH_NUMBER_FUNCTION_BASE(BINARY_NUMBER);
	//64�i��//
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


	//EnumClass�����^�փL���X�g���邽�߂̃N���X//
	template<typename Enum>
	constexpr static inline typename std::underlying_type<Enum>::type EnumCast(const Enum _enum)
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}

	//�w�肵���A�h���X���l0�ŏ���������//
	template<class T>
	inline void MZero(T* _val)
	{
		void* tmp = static_cast<void*>(_val);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmp) + i) = 0;
		}
	}

	//_base�̏���_copy�փR�s�[����//
	template<class T>
	inline void MCopy(T* _copy, const T* _base)
	{
		void* tmpCopy = static_cast<void*>(_copy);
		const void* tmpBase = static_cast<const void*>(_base);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmpCopy) + i) = *(static_cast<const char*>(tmpBase) + i);
		}
	}

	template<typename Type>
	inline Type BinaryToNumWithLittleEndian(const std::vector<unsigned char>& _binary, unsigned long _pos = 0)
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
	inline Type BinaryToNumWithBigEndian(const std::vector<unsigned char>& _binary, unsigned long _pos = 0)
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

	//10�i���̐��l������Ǝw�肵���z��ɂ���Đ������ꂽ�i���\�L�ŏo�͂����//
	template<typename CharaType>
	std::basic_string<CharaType> DecimalNumberToBaseNumber(
		const long long _decimal,
		const std::basic_string<CharaType>& _baseNumber = HEXA_DECIMAL<CharaType>());

	//�w�肵���i���̔z��������10�i���̐��l���o�͂����//
	template<typename CharaType>
	long long BaseNumberToDecimalNumber(
		const std::basic_string<CharaType>& _decimal,
		const std::basic_string<CharaType>& _baseNumber = HEXA_DECIMAL<CharaType>());

	//�w�肵���i���̔z�������Ǝw�肵���z��ɂ���Đ������ꂽ�i���\�L�ŏo�͂����//
	template<typename CharaType>
	std::basic_string<CharaType> ToBaseNumber(
		const std::basic_string<CharaType>& _baseNum,
		const std::basic_string<CharaType>& _beforeBaseNumber = DECIMAL_NUMBUR<CharaType>(),
		const std::basic_string<CharaType>& _afterBaseNumber = HEXA_DECIMAL<CharaType>());

	//�w�肵���V���̔z�������Ƃ��̔z��ɂ���Đ��l��u���ł��邩�̃e�X�g���s��//
	template<typename CharaType>
	bool IsBaseNumbers(
		const std::basic_string<CharaType>& _baseNum,
		const std::basic_string<CharaType>& _beforeBaseNumber = DECIMAL_NUMBUR<CharaType>());

	template<typename Type>
	inline std::map<Type, unsigned long> CreateHuffmanTree(const std::vector<Type>& _binary)
	{
		std::map<Type, unsigned long>out;

		return out;
	}
}

#endif