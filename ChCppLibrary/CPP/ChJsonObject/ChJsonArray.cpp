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

ChPtr::Shared<JsonBaseType> JsonArray::GetValue(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return values[_num];
}

ChPtr::Shared<JsonArray> JsonArray::GetArray(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonArray>(values[_num]);
}

ChPtr::Shared<JsonNumber> JsonArray::GetNumber(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonNumber>(values[_num]);
}

ChPtr::Shared<JsonString> JsonArray::GetString(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonString>(values[_num]);
}

ChPtr::Shared<JsonBoolean> JsonArray::GetBoolean(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonBoolean>(values[_num]);
}

ChPtr::Shared<JsonObject> JsonArray::GetObject(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<JsonObject>(values[_num]);
}

void JsonArray::AddObject(ChPtr::Shared<JsonBaseType> _value)
{
	if (_value == nullptr)return;
	values.push_back(_value);
}
