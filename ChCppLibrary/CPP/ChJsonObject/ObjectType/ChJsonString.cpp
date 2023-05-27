#include"../../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../../ChTextObject/ChTextObject.h"
#include"ChJsonNumber.h"
#include"ChJsonString.h"
#include"../../ChCumulative/ChCumulative.h"

using namespace ChCpp;

JsonString& JsonString::operator =(const JsonString& _value)
{
	if (this == &_value)return *this;
	value = _value.value;
	return *this;
}

JsonString& JsonString::operator +=(const JsonString& _value)
{
	value += _value.value;
	return *this;
}

JsonString& JsonString::operator +(const JsonString& _value)const
{
	JsonString res = value;
	res += _value;
	return res;
}

JsonString& JsonString::operator =(const std::string& _value)
{
	if (&value == &_value)return *this;
	value = _value;
	return *this;
}

JsonString& JsonString::operator +=(const std::string& _value)
{
	value += _value;
	return *this;
}

JsonString& JsonString::operator +(const std::string& _value)const
{
	JsonString res = value;
	res += _value;
	return res;
}


JsonString::JsonString()
{
	value = "";
}

JsonString::JsonString(const JsonString& _str)
{
	*this = _str;
}

JsonString::JsonString(const std::string& _str)
{
	*this = _str;
}

JsonString::JsonString(const JsonNumber& _number)
{

	*this = _number;
}

template<typename BaseType>
JsonString::JsonString(const BaseType& _num)
{
	*this = std::to_string(_num);
}
