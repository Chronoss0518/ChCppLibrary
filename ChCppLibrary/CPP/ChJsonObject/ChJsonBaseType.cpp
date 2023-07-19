#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonBaseType.h"
#include"ChJsonObject.h"
#include"ChJsonArray.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"ChJsonBoolean.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;

constexpr char nullText[] = "NULL";

std::string JsonNull::GetRawData()const
{
	return nullText;
}

ChPtr::Shared<JsonBaseType> JsonBaseType::GetParameter(const std::string& _json)
{
	if (_json == nullText)return ChPtr::Make_S<JsonNull>();

	ChPtr::Shared<JsonBaseType> res = nullptr;

	res = GetParameterToObject(_json);

	if (res != nullptr)return res;

	res = GetParameterToArray(_json);

	if (res != nullptr)return res;

	res = GetParameterToString(_json);

	if (res != nullptr)return res;

	res = GetParameterToBoolean(_json);

	if (res != nullptr)return res;

	res = GetParameterToNumber(_json);

	if (res != nullptr)return res;

	return  ChPtr::Make_S<JsonNull>();
}

ChPtr::Shared<JsonObject> JsonBaseType::GetParameterToObject(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonObject>();
	if(!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonArray> JsonBaseType::GetParameterToArray(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonString> JsonBaseType::GetParameterToString(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonString>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonBoolean> JsonBaseType::GetParameterToBoolean(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonBoolean>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonNumber> JsonBaseType::GetParameterToNumber(const std::string& _json)
{
	if (_json.size() <= 0)return nullptr;
	if (_json.size() <= 1 && (_json[0] > 57 || _json[0] < 48))return nullptr;


	bool floatingPointFlg = false;

	auto&& res = ChPtr::Make_S<JsonNumber>();

	*res = ChStr::GetFloatingFromText<long double>(_json);

	return res;
}


std::string JsonBaseType::GetRawText(unsigned long& _textPosition, const std::string& _parameterObjectText, const TextObject& _parameterObject,bool _jsonObjectFlg)
{
	std::string res = _parameterObjectText;
	if (res[0] == '[')
	{
		do
		{
			_textPosition++;
			if (_parameterObject.LineCount() < _textPosition)return "";
			res += "," + _parameterObject.GetTextLine(_textPosition);
		} while (_parameterObject.GetTextLine(_textPosition)[_parameterObject.GetTextLine(_textPosition).size() - 1] != ']');
	}
	if (res[0] == '{')
	{
		if (_jsonObjectFlg)
		{
			auto nameAndValue = ChStr::Split(_parameterObject.GetTextLine(_textPosition), ":");
			res += ":" + nameAndValue[2] + ",";
		}
		else
		{
			res += ",";
		}

		do
		{
			_textPosition++;
			if (_parameterObject.LineCount() < _textPosition)return "";
			res += _parameterObject.GetTextLine(_textPosition) + ",";
		} while (_parameterObject.GetTextLine(_textPosition)[_parameterObject.GetTextLine(_textPosition).size() - 1] != '}');
		res.pop_back();
	}

	return res;
}
