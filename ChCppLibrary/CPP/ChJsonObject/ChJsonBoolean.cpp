#include"../../BaseIncluder/ChBase.h"

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonString.h"
#include"ChJsonBoolean.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;

JsonBoolean& JsonBoolean::operator = (const JsonBoolean& _val)
{
	value = _val.value;
	return *this;
}

JsonBoolean& JsonBoolean::operator = (const bool& _flg)
{
	value = _flg;
	return *this;
}

JsonBoolean::operator bool()const
{
	return value;
}

JsonBoolean::operator JsonString()const
{
	JsonString res = GetRawData();
	return res;
}

JsonBoolean::JsonBoolean()
{
	value = false;
}

JsonBoolean::JsonBoolean(const JsonBoolean& _val)
{
	*this = _val;
}

JsonBoolean::JsonBoolean(const bool& _val)
{
	*this = _val;
}

bool JsonBoolean::SetRawData(const std::string& _jsonText)
{
	std::string testValue = _jsonText;
	if (testValue.empty())return false;
	if (testValue.size() < 4)return false;
	if (testValue.size() > 5)return false;

	for (unsigned char i = 0; i < testValue.size(); i++)
	{
		testValue[i] = testValue[i] >= 0x60 ? testValue[i] - 0x20 : testValue[i];
	}

	if (testValue == GetTrueText())
	{
		value = true;
		return true;
	}

	if (testValue == GetFalseText())
	{
		value = false;
		return true;
	}

	return false;
}

std::string JsonBoolean::GetRawData()const
{
	return value ? GetTrueText() : GetFalseText();
}

constexpr char* const JsonBoolean::GetTrueText()
{
	return const_cast<char*>("TRUE");
}

constexpr char* const JsonBoolean::GetFalseText()
{
	return const_cast<char*>("FALSE");;
}
