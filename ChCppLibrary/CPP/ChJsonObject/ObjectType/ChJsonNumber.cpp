#include"../../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../../ChTextObject/ChTextObject.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"../../ChCumulative/ChCumulative.h"

using namespace ChCpp;


JsonNumber& JsonNumber::operator = (const JsonNumber& _val)
{
	if (this == &_val)return;
	value = _val.value;
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

JsonNumber JsonNumber::operator *(const JsonNumber& _val)const
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
JsonNumber JsonNumber::operator = (const BaseType& _base)
{
	value = static_cast<const long double>(_base);
}

JsonNumber::operator JsonString()const
{
	JsonString res = value;
	return res;
}

JsonNumber::operator std::string()const
{
	return std::to_string(value);
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