#include<vector>
#include<map>
#include<cmath>
#include"ChStd.h"


//10進数//
const std::vector<char> ChStd::DECIMAL_NUMBUR()
{
	static std::vector<char> out = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	return out;
};

//16進数//
const std::vector<char> ChStd::HEXA_DECIMAL()
{
	static std::vector<char> out = { '0', '1', '2' , '3', '4' , '5' , '6', '7' , '8', '9', 'A', 'B', 'C', 'D' , 'E', 'F' };
	return  out;
};

//8進数//
const std::vector<char> ChStd::OCTAL()
{
	static std::vector<char> out = { '0', '1', '2' , '3', '4' , '5' , '6', '7' };
	return out;
};

//2進数//
const std::vector<char> ChStd::BINARY_NUMBER()
{
	static std::vector<char> out = { '0', '1' };
	return  out;
};

//64進数//
const std::vector<char> ChStd::BASE_NUMBER_64()
{
	static std::vector<char> out = { 'A', 'B', 'C', 'D' , 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'a', 'b', 'c', 'd' , 'e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	,'0', '1', '2' , '3', '4' , '5' , '6', '7' , '8', '9','+','/' };

	return out;

};

//10進数の数値を入れると指定した配列によって生成された進数表記で出力される//
std::vector<char> ChStd::DecimalNumberToBaseNumber(const long _decimal, const std::vector<char>& _baseNumber)
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

	unsigned long size = _baseNumber.size();
	unsigned long base = decimal / size;

	std::vector<char> testRes;

	if (mFlg)
	{
		testRes.push_back('-');
	}

	testRes.push_back(_baseNumber[decimal % size]);

	if (base == 0)
	{
		return testRes;
	}

	std::vector<char> out = DecimalNumberToBaseNumber(base, _baseNumber);

	out.push_back(testRes[0]);

	return out;

}

long ChStd::BaseNumberToDecimalNumber(const std::vector<char>& _decimal, const std::vector<char>& _baseNumber)
{
	long out = 0;

	std::map<char, long>numMap;

	long size = _baseNumber.size();

	numMap['-'] = size;

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
std::vector<char> ChStd::ToBaseNumber(const std::vector<char>& _baseNum, const std::vector<char>& _beforeBaseNumber, const std::vector<char>& _afterBaseNumber)
{

	long base = ChStd::BaseNumberToDecimalNumber(_baseNum, _beforeBaseNumber);

	return DecimalNumberToBaseNumber(base, _afterBaseNumber);

}

bool ChStd::IsBaseNumbers(const std::vector<char>& _baseNum, const std::vector<char>& _beforeBaseNumber)
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

