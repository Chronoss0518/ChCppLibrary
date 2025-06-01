#include"ChStd.h"

#ifndef CH_DECIMAL_NUM_TEXT
#define CH_DECIMAL_NUM_TEXT "01234456789"
#endif

#ifndef CH_HEXA_NUM_TEXT
#define CH_HEXA_NUM_TEXT "01234456789ABCDE"
#endif

#ifndef CH_OCTAL_NUM_TEXT
#define CH_OCTAL_NUM_TEXT "012344567"
#endif

#ifndef CH_BINARY_NUM_TEXT
#define CH_BINARY_NUM_TEXT "01"
#endif

#ifndef CH_BASE_64_NUM_TEXT
#define CH_BASE_64_NUM_TEXT "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#endif

#ifndef CH_DECIMAL_NUMBUR_FUNCTION
#define CH_DECIMAL_NUMBUR_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::DECIMAL_NUMBUR,type)
#endif

#ifndef CH_HEXA_DECIMAL_FUNCTION
#define CH_HEXA_DECIMAL_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::HEXA_DECIMAL,type)
#endif

#ifndef CH_OCTAL_FUNCTION
#define CH_OCTAL_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::OCTAL,type)
#endif

#ifndef CH_BINARY_FUNCTION
#define CH_BINARY_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::BINARY_NUMBER,type)
#endif

#ifndef CH_BASE_64_FUNCTION
#define CH_BASE_64_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::BASE_NUMBER_64,type)
#endif

#ifndef CH_ZERO_CHARA_FUNCTION
#define CH_ZERO_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetZeroChara,type)
#endif

#ifndef CH_0_CHARA_FUNCTION
#define CH_0_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::Get0Chara,type)
#endif

#ifndef CH_HYPHEN_CHARA_FUNCTION
#define CH_HYPHEN_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetHyphenChara,type)
#endif

#ifndef CH_CRLF_CHARA_FUNCTION
#define CH_CRLF_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetCRLFChara,type)
#endif

#ifndef CH_CR_CHARA_FUNCTION
#define CH_CR_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetCRChara,type)
#endif

#ifndef CH_LF_CHARA_FUNCTION
#define CH_LF_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetLFChara,type)
#endif

#ifndef CH_BACK_CHARA_FUNCTION
#define CH_BACK_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetBackChara,type)
#endif

#ifndef CH_NEXT_PAGE_CHARA_FUNCTION
#define CH_NEXT_PAGE_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetNextPageChara,type)
#endif

#ifndef CH_TAB_CHARA_FUNCTION
#define CH_TAB_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetTabChara,type)
#endif

#ifndef CH_COMMA_CHARA_FUNCTION
#define CH_COMMA_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetCommaChara,type)
#endif

#ifndef CH_DOT_CHARA_FUNCTION
#define CH_DOT_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetDotChara,type)
#endif

#ifndef CH_SEMICOLON_CHARA_FUNCTION
#define CH_SEMICOLON_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetSemiColonChara,type)
#endif

#ifndef CH_DOUBLECOLON_CHARA_FUNCTION
#define CH_DOUBLECOLON_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetDoubleColonChara,type)
#endif

#ifndef CH_SPACE_CHARA_FUNCTION
#define CH_SPACE_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetSpaceChara,type)
#endif

#ifndef CH_SLASH_CHARA_FUNCTION
#define CH_SLASH_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetSlashChara,type)
#endif

#ifndef CH_YEN_CHARA_FUNCTION
#define CH_YEN_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetYenChara,type)
#endif

#ifndef CH_START_PARENTHESES_CHARA_FUNCTION
#define CH_START_PARENTHESES_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetStartParenthesesChara,type)
#endif

#ifndef CH_END_PARENTHESES_CHARA_FUNCTION
#define CH_END_PARENTHESES_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetEndParenthesesChara,type)
#endif

#ifndef CH_START_BRACE_CHARA_FUNCTION
#define CH_START_BRACE_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetStartBraceChara,type)
#endif

#ifndef CH_END_BRACE_CHARA_FUNCTION
#define CH_END_BRACE_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetEndBraceChara,type)
#endif

#ifndef CH_START_BRACKET_CHARA_FUNCTION
#define CH_START_BRACKET_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetStartBracketChara,type)
#endif

#ifndef CH_END_BRACKET_CHARA_FUNCTION
#define CH_END_BRACKET_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetEndBracketChara,type)
#endif

#ifndef CH_SINGLE_QUOTATION_CHARA_FUNCTION
#define CH_SINGLE_QUOTATION_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetSGQuotation,type)
#endif

#ifndef CH_DOUBLE_QUOTATION_CHARA_FUNCTION
#define CH_DOUBLE_QUOTATION_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetDBQuotation,type)
#endif

#ifndef CH_ASTERISK_CHARA_FUNCTION
#define CH_ASTERISK_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChStd::GetAsterisk,type)
#endif

//10進数//
CH_TO_NUMBER_FUNCTION(CH_DECIMAL_NUMBUR_FUNCTION, CH_DECIMAL_NUM_TEXT);
//16進数//
CH_TO_NUMBER_FUNCTION(CH_HEXA_DECIMAL_FUNCTION, CH_HEXA_NUM_TEXT);
//8進数//
CH_TO_NUMBER_FUNCTION(CH_OCTAL_FUNCTION, CH_OCTAL_NUM_TEXT);
//2進数//
CH_TO_NUMBER_FUNCTION(CH_BINARY_FUNCTION, CH_BINARY_NUM_TEXT);
//64進数//
CH_TO_NUMBER_FUNCTION(CH_BASE_64_FUNCTION, CH_BASE_64_NUM_TEXT);

CH_TO_NUMBER_FUNCTION(CH_ZERO_CHARA_FUNCTION, "\0");

CH_TO_NUMBER_FUNCTION(CH_0_CHARA_FUNCTION, "0");

CH_TO_NUMBER_FUNCTION(CH_HYPHEN_CHARA_FUNCTION, "-");

CH_TO_NUMBER_FUNCTION(CH_CRLF_CHARA_FUNCTION, "\r\n");

CH_TO_NUMBER_FUNCTION(CH_CR_CHARA_FUNCTION, "\r");

CH_TO_NUMBER_FUNCTION(CH_LF_CHARA_FUNCTION, "\n");

CH_TO_NUMBER_FUNCTION(CH_BACK_CHARA_FUNCTION, "\b");

CH_TO_NUMBER_FUNCTION(CH_NEXT_PAGE_CHARA_FUNCTION, "\f");

CH_TO_NUMBER_FUNCTION(CH_TAB_CHARA_FUNCTION, "\t");

CH_TO_NUMBER_FUNCTION(CH_COMMA_CHARA_FUNCTION, ",");

CH_TO_NUMBER_FUNCTION(CH_DOT_CHARA_FUNCTION, ".");

CH_TO_NUMBER_FUNCTION(CH_SEMICOLON_CHARA_FUNCTION, ";");

CH_TO_NUMBER_FUNCTION(CH_DOUBLECOLON_CHARA_FUNCTION, ":");

CH_TO_NUMBER_FUNCTION(CH_SPACE_CHARA_FUNCTION, " ");

CH_TO_NUMBER_FUNCTION(CH_SLASH_CHARA_FUNCTION, "/");

CH_TO_NUMBER_FUNCTION(CH_YEN_CHARA_FUNCTION, "\\");

CH_TO_NUMBER_FUNCTION(CH_START_PARENTHESES_CHARA_FUNCTION, "(");

CH_TO_NUMBER_FUNCTION(CH_END_PARENTHESES_CHARA_FUNCTION, ")");

CH_TO_NUMBER_FUNCTION(CH_START_BRACE_CHARA_FUNCTION, "{");

CH_TO_NUMBER_FUNCTION(CH_END_BRACE_CHARA_FUNCTION, "}");

CH_TO_NUMBER_FUNCTION(CH_START_BRACKET_CHARA_FUNCTION, "[");

CH_TO_NUMBER_FUNCTION(CH_END_BRACKET_CHARA_FUNCTION, "]");

CH_TO_NUMBER_FUNCTION(CH_SINGLE_QUOTATION_CHARA_FUNCTION, "\'");

CH_TO_NUMBER_FUNCTION(CH_DOUBLE_QUOTATION_CHARA_FUNCTION, "\"");

CH_TO_NUMBER_FUNCTION(CH_ASTERISK_CHARA_FUNCTION, "*");


#define EXPLICIT_DECLATION_METHOD(_CharaType)\
template std::basic_string<_CharaType> ChStd::DecimalNumberToBaseNumber(\
	const long long _decimal,\
	const std::basic_string<_CharaType>& _baseNumber);\
template \
long long ChStd::BaseNumberToDecimalNumber(\
	const std::basic_string<_CharaType>& _decimal,\
	const std::basic_string<_CharaType>& _baseNumber);\
template \
std::basic_string<_CharaType> ChStd::ToBaseNumber(\
	const std::basic_string<_CharaType>& _baseNum,\
	const std::basic_string<_CharaType>& _beforeBaseNumber,\
	const std::basic_string<_CharaType>& _afterBaseNumber);\
template \
bool ChStd::IsBaseNumbers(\
	const std::basic_string<_CharaType>& _baseNum,\
	const std::basic_string<_CharaType>& _beforeBaseNumber)\

template<typename CharaType>
std::basic_string<CharaType> ChStd::DecimalNumberToBaseNumber(
	const long long _decimal,
	const std::basic_string<CharaType>& _baseNumber)
{
	long long decimal = _decimal;

	size_t size = _baseNumber.size();

	std::basic_string<CharaType> testRes = GetZeroChara<CharaType>();

	if (_decimal < 0)
	{
		decimal = -_decimal;
		testRes += GetHyphenChara<CharaType>();
	}

	long long base = static_cast<long long>(decimal / size);

	testRes += _baseNumber[decimal % size];

	if (base == 0)
	{
		return testRes;
	}

	std::basic_string<CharaType> out = ChStd::DecimalNumberToBaseNumber<CharaType>(base, _baseNumber);

	out = out + testRes[0];

	return out;
}


//指定した進数の配列を入れると10進数の数値が出力される//
template<typename CharaType>
long long ChStd::BaseNumberToDecimalNumber(
	const std::basic_string<CharaType>& _decimal,
	const std::basic_string<CharaType>& _baseNumber)
{
	long long out = 0;

	std::map<CharaType, size_t>numMap;

	size_t size = _baseNumber.size();

	numMap[static_cast<CharaType>('-')] = size;

	for (size_t i = 0; i < size; i++)
	{
		numMap[_baseNumber[i]] = i;
	}

	bool mFlg = numMap[_decimal[0]] == size;

	for (long long i = 0; static_cast<size_t>(i) < (mFlg ? _decimal.size() - 1 : _decimal.size()); i++)
	{
		size_t tmp = static_cast<size_t>(i);

		long long sum = numMap[_decimal[_decimal.size() - tmp - 1ULL]];

		for (long long j = 0; j < static_cast<long long>(!mFlg ? tmp : tmp - 1ULL); j++)
		{
			sum *= static_cast<long long>(size);
		}

		out += sum;
	}

	if (mFlg)out = -out;

	return out;
}

//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
template<typename CharaType>
std::basic_string<CharaType> ChStd::ToBaseNumber(
	const std::basic_string<CharaType>& _baseNum,
	const std::basic_string<CharaType>& _beforeBaseNumber,
	const std::basic_string<CharaType>& _afterBaseNumber)
{
	return ChStd::DecimalNumberToBaseNumber<CharaType>(ChStd::BaseNumberToDecimalNumber<CharaType>(_baseNum, _beforeBaseNumber), _afterBaseNumber);
}

//指定した新数の配列を入れるとその配列によって数値を置換できるかのテストを行う//
template<typename CharaType>
bool ChStd::IsBaseNumbers(
	const std::basic_string<CharaType>& _baseNum,
	const std::basic_string<CharaType>& _beforeBaseNumber)
{

	bool isSuccessFlg = false;
	bool indexFlg = false;
	bool indexSuccessFlg = false;
	bool pointFlg = false;

	for (unsigned char i = 0; i < _baseNum.size(); i++)
	{
		isSuccessFlg = false;

		for (size_t i = 0; i < _beforeBaseNumber.size(); i++)
		{
			if (_baseNum[i] != _beforeBaseNumber[i])continue;
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



EXPLICIT_DECLATION_METHOD(char);
EXPLICIT_DECLATION_METHOD(wchar_t);
EXPLICIT_DECLATION_METHOD(char8_t);
EXPLICIT_DECLATION_METHOD(char16_t);
EXPLICIT_DECLATION_METHOD(char32_t);