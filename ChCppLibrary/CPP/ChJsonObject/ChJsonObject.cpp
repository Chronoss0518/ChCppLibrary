#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonObject.h"
#include"ObjectType/ChJsonArray.h"
#include"ObjectType/ChJsonString.h"
#include"ObjectType/ChJsonNumber.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;


bool JsonObject::SetRawData(const std::string& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != '{' || _jsonText[_jsonText.size() - 1] != '{')return false;

	std::string parameter = _jsonText.substr(1, _jsonText.length() - 2);

	Cumulative<char> cumulativeObjectChecker = Cumulative<char>('{', '}');

	cumulativeObjectChecker.Update(_jsonText[0]);

	TextObject parameterObject;

	parameterObject.SetCutChar(',');

	parameterObject.SetText(parameter);

	for (unsigned long i = 0; i < parameterObject.Count() - 1; i++)
	{
		auto nameAndValue = ChStr::Split(parameterObject.GetTextLine(i), ":");
		if (nameAndValue.size() < 2)continue;
	}

	return true;

}

void JsonObject::SetArray(const std::string& _parameterName, const JsonArray& _value)
{

}

void JsonObject::SetNumber(const std::string& _parameterName, const JsonNumber& _value)
{

}

void JsonObject::SetString(const std::string& _parameterName, const JsonString& _value)
{

}

void JsonObject::SetBoolean(const std::string& _parameterName, const JsonBoolean& _value)
{

}

void JsonObject::SetObject(const std::string& _parameterName, const JsonObject& _value)
{

}

std::string JsonObject::GetRawData()const
{
	std::string res = "{";

	bool initFlg = false;

	for (auto&& val : value)
	{
		if (initFlg)res += ",";
		res += val.first + ":" + val.second->GetRawData();
		initFlg = true;
	}

	res += "}";

	return res;
}

JsonArray JsonObject::GetArray(const std::string& _parameterName)const
{

}

JsonNumber JsonObject::GetNumber(const std::string& _parameterName)const
{

}

JsonString JsonObject::GetString(const std::string& _parameterName)const
{

}

JsonBoolean JsonObject::GetBoolean(const std::string& _parameterName)const
{

}

JsonObject JsonObject::GetObject(const std::string& _parameterName)const
{

}
