#include"../../BaseIncluder/ChBase.h"
#include<cmath>


#include"../ChTextObject/ChTextObject.h"
#include"ChJsonArray.h"
#include"ChJsonNumber.h"
#include"ChJsonString.h"
#include"ChJsonBoolean.h"
#include"ChJsonObject.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;

template<typename BaseType>
ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<BaseType>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	for (auto&& val : _array)
	{
		res->AddObject(JsonNumber::CreateObject(val));
	}
	return res;
}

ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<bool>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	for (auto&& val : _array)
	{
		res->AddObject(JsonBoolean::CreateObject(val));
	}
	return res;
}

ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<std::string>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	for (auto&& val : _array)
	{
		res->AddObject(JsonString::CreateObject(val));
	}
	return res;
}


bool JsonArray::SetRawData(const std::string& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != '[' || _jsonText[_jsonText.size() - 1] != ']')return false;

	std::string parameter = _jsonText.substr(1, _jsonText.length() - 2);

	parameter = ChStr::RemoveToWhiteSpaceChars(parameter);

	TextObject parameterObject;

	parameterObject.SetCutChar(',');

	parameterObject.SetText(parameter);

	for (unsigned long i = 0; i < parameterObject.LineCount(); i++)
	{
		std::string value = parameterObject.GetTextLine(i);
		value = GetRawText(i, value, parameterObject, false);
		if (value.empty())return false;
		auto&& obj = JsonBaseType::GetParameter(value);
		if (obj == nullptr)continue;
		values.push_back(obj);
	}

	return true;

}

void JsonArray::SetValue(unsigned long _num, const ChPtr::Shared<JsonBaseType> _value)
{
	if (_value == nullptr)return;
	if (_num >= values.size())return;
	values[_num] = nullptr;
	values[_num] = _value;
}


std::string JsonArray::GetRawData()const
{
	std::string res = "[";

	bool initFlg = false;

	for (auto&& val : values)
	{
		if (initFlg)res += ",";
		res += val->GetRawData();
		initFlg = true;
	}

	res += "]";

	return res;
}

unsigned long JsonArray::GetCount()const
{
	return values.size();
}

ChPtr::Shared<JsonBaseType> JsonArray::GetJsonValue(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return values[_num];
}

ChPtr::Shared<JsonArray> JsonArray::GetJsonArray(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonArray>(values[_num]);
}

ChPtr::Shared<JsonNumber> JsonArray::GetJsonNumber(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonNumber>(values[_num]);
}

ChPtr::Shared<JsonString> JsonArray::GetJsonString(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonString>(values[_num]);
}

ChPtr::Shared<JsonBoolean> JsonArray::GetJsonBoolean(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonBoolean>(values[_num]);
}

ChPtr::Shared<JsonObject> JsonArray::GetJsonObject(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonObject>(values[_num]);
}

void JsonArray::AddObject(ChPtr::Shared<JsonBaseType> _value)
{
	if (_value == nullptr)return;
	values.push_back(_value);
}
