#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;


template<typename BaseType>
ChPtr::Shared<JsonNumber> JsonNumber::CreateObject(const BaseType& _value)
{
	auto&& res = ChPtr::Make_S<JsonNumber>();
	*res = _value;
	return res;
}

JsonNumber& JsonNumber::operator = (const JsonNumber& _val)
{
	if (this == &_val)return *this;
	value = _val.value;
	return *this;
}

JsonNumber& JsonNumber::operator += (const JsonNumber& _val)
{
	value += _val.value;
	return *this;
}

JsonNumber JsonNumber::operator + (const JsonNumber& _val)const
{
	JsonNumber res = *this;
	res += _val;
	return res;
}

JsonNumber& JsonNumber::operator -= (const JsonNumber& _val)
{
	value -= _val.value;
	return *this;
}

JsonNumber JsonNumber::operator - (const JsonNumber& _val)const
{
	JsonNumber res = *this;
	res -= _val;
	return res;
}

JsonNumber& JsonNumber::operator *= (const JsonNumber& _val)
{
	value *= _val.value;
	return *this;
}

JsonNumber JsonNumber::operator *(const JsonNumber& _val)const
{
	JsonNumber res = *this;
	res *= _val;
	return res;
}

JsonNumber& JsonNumber::operator /= (const JsonNumber& _val)
{
	value /= _val.value != 0.0l ? _val.value : 1.0l;
	return *this;
}

JsonNumber JsonNumber::operator /(const JsonNumber& _val)const
{
	JsonNumber res = *this;
	res /= _val;
	return res;
}

JsonNumber& JsonNumber::operator %= (const JsonNumber& _val)
{
	value = std::fmodl(value, _val.value);
	return *this;
}

JsonNumber JsonNumber::operator % (const JsonNumber& _val)const
{
	JsonNumber res = *this;
	res %= _val;
	return res;
}

template<typename BaseType>
JsonNumber::operator BaseType()const
{
	return static_cast<BaseType>(value);
}

template<typename BaseType>
JsonNumber& JsonNumber::operator = (const BaseType& _base)
{
	value = static_cast<const long double>(_base);
	return *this;
}

JsonNumber::operator JsonString()const
{
	JsonString res = value;
	return res;
}

JsonNumber::operator std::string()const
{
	return ToString();
}

JsonNumber::JsonNumber()
{
	value = 0.0l;
}

JsonNumber::JsonNumber(const JsonNumber& _val)
{
	*this = _val;
}

template<typename BaseType>
JsonNumber::JsonNumber(const BaseType& _val)
{
	*this = _val;
}

bool JsonNumber::SetRawData(const std::string& _jsonText)
{
	std::vector<char> text;
	for (char value : _jsonText)
	{
		text.push_back(value);
	}

	if (!ChStd::IsBaseNumbers(text, ChStd::DECIMAL_NUMBUR()))return false;

	value = ChStr::GetFloatingFromText<long double>(_jsonText);

	return true;
}

std::string JsonNumber::GetRawData()const
{
	return ToString();
}

std::string JsonNumber::ToString()const
{
	std::string tmpStr = std::to_string(value);
	unsigned long endPoint = tmpStr.find('.');
	for (unsigned long i = endPoint + 1; i < tmpStr.size(); i++)
	{
		if (tmpStr[i] == '0')continue;
		endPoint = i + 1;
	}

	if (endPoint >= tmpStr.size())
	{
		return tmpStr;
	}

	return tmpStr.substr(0,endPoint);
}