#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonObject.h"
#include"ChJsonArray.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"ChJsonBoolean.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;


bool JsonObject::SetRawData(const std::string& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != '{' || _jsonText[_jsonText.size() - 1] != '}')return false;

	std::string parameter = _jsonText.substr(1, _jsonText.length() - 2);
	parameter = ChStr::RemoveToWhiteSpaceChars(parameter);

	TextObject parameterObject;

	parameterObject.SetCutChar(',');

	parameterObject.SetText(parameter);

	for (unsigned long i = 0; i < parameterObject.LineCount(); i++)
	{

		auto nameAndValue = ChStr::Split(parameterObject.GetTextLine(i), ":");
		if (nameAndValue.size() < 2)continue;
#if false
		if (nameAndValue[1][0] == '[')
		{
			do
			{
				i++;
				nameAndValue[1] += "," + parameterObject.GetTextLine(i);
			} while (parameterObject.GetTextLine(i)[parameterObject.GetTextLine(i).size() - 1] != ']');
		}
		if (nameAndValue[1][0] == '{')
		{
			nameAndValue[1] += ":" + nameAndValue[2] + ",";
			do
			{
				i++;
				nameAndValue[1] += parameterObject.GetTextLine(i) + ",";
			} while (parameterObject.GetTextLine(i)[parameterObject.GetTextLine(i).size() - 1] != '}');
			nameAndValue[1].pop_back();
		}
#endif
		nameAndValue[1] = GetRawText(i, nameAndValue[1], parameterObject, true);
		auto obj = JsonBaseType::GetParameter(nameAndValue[1]);
		if (obj == nullptr)continue;
		values[nameAndValue[0]] = obj;
	}

	return true;

}

void JsonObject::SetObject(const std::string& _parameterName, const ChPtr::Shared<JsonBaseType> _value)
{
	if (_value == nullptr)
	{
		values[_parameterName] = ChPtr::Make_S<JsonNull>();
		return;
	}

	values[_parameterName] = _value;
}

std::string JsonObject::GetRawData()const
{
	std::string res = "{";

	bool initFlg = false;

	for (auto&& val : values)
	{
		if (initFlg)res += ",\n";
		res += val.first + ":" + val.second->GetRawData();
		initFlg = true;
	}

	res += "}";

	return res;
}

ChPtr::Shared<JsonObject> JsonObject::GetObject(const std::string& _parameterName)
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SharedSafeCast<JsonObject>(findObject->second);
}

ChPtr::Shared<JsonArray> JsonObject::GetArray(const std::string& _parameterName)
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SharedSafeCast<JsonArray>(findObject->second);
}

ChPtr::Shared<JsonNumber> JsonObject::GetNumber(const std::string& _parameterName)
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SharedSafeCast<JsonNumber>(findObject->second);
}

ChPtr::Shared<JsonString> JsonObject::GetString(const std::string& _parameterName)
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SharedSafeCast<JsonString>(findObject->second);
}

ChPtr::Shared<JsonBoolean> JsonObject::GetBoolean(const std::string& _parameterName)
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SharedSafeCast<JsonBoolean>(findObject->second);
}

const JsonObject* const JsonObject::GetObject(const std::string& _parameterName)const
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SafeCast<JsonObject>(findObject->second.get());
}

const JsonArray* const JsonObject::GetArray(const std::string& _parameterName)const
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SafeCast<JsonArray>(findObject->second.get());
}

const JsonString* const JsonObject::GetString(const std::string& _parameterName)const
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SafeCast<JsonString>(findObject->second.get());
}

const JsonBoolean* const JsonObject::GetBoolean(const std::string& _parameterName)const
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SafeCast<JsonBoolean>(findObject->second.get());
}

const JsonNumber* const JsonObject::GetNumber(const std::string& _parameterName)const
{
	auto findObject = values.find(_parameterName);
	if (findObject == values.end())return nullptr;
	return ChPtr::SafeCast<JsonNumber>(findObject->second.get());
}
