#include"../../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../../ChTextObject/ChTextObject.h"
#include"ChJsonBaseType.h"
#include"../ChJsonObject.h"
#include"ChJsonArray.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"../../ChCumulative/ChCumulative.h"

using namespace ChCpp;

ChPtr::Shared<JsonBaseType> JsonBaseType::GetParameter(const std::string& _json)
{
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

	return res;
}

ChPtr::Shared<JsonObject> JsonBaseType::GetParameterToObject(const std::string& _json)
{
	if (_json.size() < 2)return nullptr;
	if (_json[0] != '{' || _json[_json.size() - 1] != '{')return nullptr;

	auto&& res = ChPtr::Make_S<JsonObject>();

	std::string parameter = _json.substr(1, _json.length() - 2);

	Cumulative<char> cumulativeObjectChecker = Cumulative<char>('{', '}');

	cumulativeObjectChecker.Update(_json[0]);

	TextObject parameterObject;

	parameterObject.SetCutChar(',');

	parameterObject.SetText(parameter);

	for (unsigned long i = 0; i < parameterObject.Count() - 1; i++)
	{
		auto nameAndValue = ChStr::Split(parameterObject.GetTextLine(i), ":");
		if (nameAndValue.size() < 2)continue;
	}

	return res;
}

ChPtr::Shared<JsonArray> JsonBaseType::GetParameterToArray(const std::string& _json)
{
	if (_json.size() < 2)return nullptr;
	if (_json[0] != '[' || _json[_json.size() - 1] != ']')return nullptr;

	auto&& res = ChPtr::Make_S<JsonArray>();



	return res;
}

ChPtr::Shared<JsonString> JsonBaseType::GetParameterToString(const std::string& _json)
{

}

ChPtr::Shared<JsonBoolean> JsonBaseType::GetParameterToBoolean(const std::string& _json)
{

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
