#ifndef Ch_CPP_BStd_CRT_h
#define Ch_CPP_BStd_CRT_h

#include"ChStd.h"

#include<string.h>
#include<iostream>
#include<vector>
#include<map>
#include<cmath>

#include"ChStrCRT.h"

#ifdef __cplusplus
#if __cplusplus > 200000L

#ifndef CPP20
#define CPP20
#endif

#endif
#endif 

#ifdef _MSVC_LANG
#if _MSVC_LANG > 200000L

#ifndef CPP20
#define CPP20
#endif

#endif
#endif

//10進数の数値を入れると指定した配列によって生成された進数表記で出力される//
ChStr::BaseString<char> ChStd::DecimalNumberToBaseNumber(const long _decimal, const char* _baseNumber)
{
	bool mFlg = false;
	long decimal = 0;

	if (_decimal > 0)
	{
		decimal = _decimal;
	}
	else
	{
		decimal = -_decimal;
		mFlg = true;
	}

	unsigned long size = strlen(_baseNumber);
	unsigned long base = decimal / size;

	ChStr::BaseString<char> testRes;

	if (mFlg)
	{
		testRes.Add('-');
	}

	testRes.Add(_baseNumber[decimal % size]);

	if (base == 0)
	{
		return testRes;
	}

	ChStr::BaseString<char> returnValue = DecimalNumberToBaseNumber(base, _baseNumber);

	returnValue.Add(testRes);

	return returnValue;
}

long ChStd::BaseNumberToDecimalNumber(const char* _decimal, const char* _baseNumber)
{
	long out = 0;

	std::map<char, long>numMap;

	unsigned long size = strlen(_baseNumber);
	unsigned long decimalSize = strlen(_decimal);

	numMap['-'] = size;

	for (unsigned long i = 0; i < size; i++)
	{
		numMap[_baseNumber[i]] = i;
	}

	bool mFlg = numMap[_decimal[0]] == size;

	for (unsigned long i = 0; static_cast<unsigned long>(i) < (mFlg ? decimalSize - 1 : decimalSize); i++)
	{
		long sum = numMap[_decimal[decimalSize - i - 1]];

		for (unsigned long j = 0; j < (!mFlg ? i : i - 1); j++)
		{
			sum *= size;
		}

		out += sum;
	}

	if (mFlg)out = -out;

	return out;
}

//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
ChStr::BaseString<char> ChStd::ToBaseNumber(const char* _baseNum, const char* _beforeBaseNumber, const char* _afterBaseNumber)
{

	long base = ChStd::BaseNumberToDecimalNumber(_baseNum, _beforeBaseNumber);

	return DecimalNumberToBaseNumber(base, _afterBaseNumber);

}

bool ChStd::IsBaseNumbers(const char* _baseNum, const char* _beforeBaseNumber)
{

	bool isSuccessFlg = false;
	bool indexFlg = false;
	bool indexSuccessFlg = false;
	bool pointFlg = false;

	unsigned long baseNumLen = strlen(_baseNum);
	unsigned long beforeBaseNumLen = strlen(_beforeBaseNumber);

	for (unsigned long i = 0; i < baseNumLen; i++)
	{
		isSuccessFlg = false;

		for (unsigned long j = 0; j < beforeBaseNumLen; j++)
		{
			auto&& numChar = _beforeBaseNumber[j];

			if (_baseNum[i] != numChar)continue;
			if (indexFlg)indexSuccessFlg = true;
			isSuccessFlg = true;
		}

		if (isSuccessFlg)continue;
		if (_baseNum[i] == '.')
		{
			if (!pointFlg)
			{
				pointFlg = true;
				continue;
			}
		}
		if (_baseNum[i] == 'E' || _baseNum[i] == 'e')
		{
			if (!indexFlg)
			{
				indexFlg = true;
				i++;
				if (_baseNum[i] == '+' || _baseNum[i] == '-')continue;
				i--;
				continue;
			}
		}
		return false;

	}

	if (!indexSuccessFlg && indexFlg)return false;

	return true;
}

namespace ChStd
{
	//EnumClassを基底型へキャストするためのクラス//
	template<typename Enum>
	constexpr static inline auto EnumCast(const Enum _enum) -> typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}

}

#endif