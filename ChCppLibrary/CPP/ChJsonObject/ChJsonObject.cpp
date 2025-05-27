
#include"ChJsonObject.h"

#include"ChJsonBoolean.h"
#include"ChJsonArray.h"
#include"ChJsonNumber.h"
#include"ChJsonString.h"

#ifndef CH_JSON_OBJECT_GET_SHARED_METHOD
#define CH_JSON_OBJECT_GET_SHARED_METHOD(_CastClass)\
template<typename CharaType>\
ChPtr::Shared<ChCpp::_CastClass<CharaType>> ChCpp::JsonObject<CharaType>::Get##_CastClass(const std::basic_string<CharaType>& _parameterName){\
	auto findObject = values.find(_parameterName);\
	if (findObject == values.end())return nullptr;\
	return ChPtr::SharedSafeCast<_CastClass<CharaType>>(findObject->second);}
#endif

#ifndef CH_JSON_OBJECT_GET_RAW_METHOD
#define CH_JSON_OBJECT_GET_RAW_METHOD(_CastClass)\
template<typename CharaType>\
const ChCpp::_CastClass<CharaType>* const ChCpp::JsonObject<CharaType>::Get##_CastClass(const std::basic_string<CharaType>& _parameterName)const{\
	auto findObject = values.find(_parameterName);\
	if (findObject == values.end())return nullptr;\
	return ChPtr::SafeCast<_CastClass<CharaType>>(findObject->second.get());}
#endif

template<typename CharaType>
bool ChCpp::JsonObject<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != ChStd::GetStartBraceChara<CharaType>()[0] ||
		_jsonText[_jsonText.size() - 1] != ChStd::GetEndBraceChara<CharaType>()[0])return false;

	std::basic_string<CharaType> parameter = _jsonText.substr(1, _jsonText.length() - 2);
	parameter = JsonBaseType<CharaType>::GetExtractString(parameter);

	TextObject<CharaType> parameterObject;

	parameterObject.SetCutChar(ChStd::GetCommaChara<CharaType>());

	parameterObject.SetText(parameter.c_str());

	for (unsigned long i = 0; i < parameterObject.LineCount(); i++)
	{
		auto&& nameAndValue = ChStr::Split<CharaType>(parameterObject.GetTextLine(i), ChStd::GetDoubleColonChara<CharaType>());
		if (nameAndValue.size() < 2)continue;

		if (nameAndValue[0][0] != ChStd::GetDBQuotation<CharaType>()[0] ||
			nameAndValue[0][nameAndValue[0].size() - 1] != ChStd::GetDBQuotation<CharaType>()[0])return false;

		nameAndValue[0] = nameAndValue[0].substr(1, nameAndValue[0].size() - 2);

		if (IsCutCharInParameterName(nameAndValue[0]))return false;

		nameAndValue[1] = JsonBaseType<CharaType>::GetRawText(i, nameAndValue[1], parameterObject, true);
		if (nameAndValue[1].empty())return false;
		auto obj = JsonBaseType<CharaType>::GetParameter(nameAndValue[1]);
		if (obj == nullptr)continue;
		values[nameAndValue[0]] = obj;
	}

	return true;

}


template<typename CharaType>
void ChCpp::JsonObject<CharaType>::Set(const std::basic_string<CharaType>& _parameterName, const ChPtr::Shared<JsonBaseType<CharaType>> _value)
{
	if (IsCutCharInParameterName(_parameterName))return;

	if (_value == nullptr)
	{
		values[_parameterName] = ChPtr::Make_S<JsonNull<CharaType>>();
		return;
	}

	values[_parameterName] = _value;
}


template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonObject<CharaType>::GetRawData()const
{
	std::basic_string<CharaType> res = ChStd::GetStartBraceChara<CharaType>();

	bool initFlg = false;

	for (auto&& val : values)
	{
		if (initFlg)res += ChStd::GetCommaChara<CharaType>();
		res += ChStd::GetDBQuotation<CharaType>() + val.first + ChStd::GetDBQuotation<CharaType>() + ChStd::GetDoubleColonChara<CharaType>() + val.second->GetRawData();
		initFlg = true;
	}

	res += ChStd::GetEndBraceChara<CharaType>();

	return res;
}

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::JsonObject<CharaType>::GetParameterNames()const
{
	std::vector<std::basic_string<CharaType>> res;

	for (auto&& value : values)
	{
		res.push_back(value.first);
	}

	return res;
}

CH_JSON_OBJECT_GET_SHARED_METHOD(JsonObject);
CH_JSON_OBJECT_GET_SHARED_METHOD(JsonArray);
CH_JSON_OBJECT_GET_SHARED_METHOD(JsonNumber);
CH_JSON_OBJECT_GET_SHARED_METHOD(JsonString);
CH_JSON_OBJECT_GET_SHARED_METHOD(JsonBoolean);


CH_JSON_OBJECT_GET_RAW_METHOD(JsonObject);
CH_JSON_OBJECT_GET_RAW_METHOD(JsonArray);
CH_JSON_OBJECT_GET_RAW_METHOD(JsonNumber);
CH_JSON_OBJECT_GET_RAW_METHOD(JsonString);
CH_JSON_OBJECT_GET_RAW_METHOD(JsonBoolean);

template<typename CharaType>
void ChCpp::JsonObject<CharaType>::Remove(const std::basic_string<CharaType>& _parameterName)
{
	auto&& obj = values.find(_parameterName);
	if (obj == values.end())return;

	(*obj).second = ChPtr::Make_S<JsonNull<CharaType>>();
}

template<typename CharaType>
void ChCpp::JsonObject<CharaType>::RemoveHard(const std::basic_string<CharaType>& _parameterName)
{
	auto&& obj = values.find(_parameterName);
	if (obj == values.end())return;
	values.erase(obj);
}

template<typename CharaType>
void ChCpp::JsonObject<CharaType>::Clear()
{
	if (values.empty())return;
	values.clear();
}

template<typename CharaType>
bool ChCpp::JsonObject<CharaType>::IsCutCharInParameterName(const std::basic_string<CharaType>& _parameterName)
{
	for (unsigned long i = 0; i < _parameterName.size(); i++)
	{
		if (_parameterName[i] == ChStd::GetDBQuotation<CharaType>()[0])return true;
	}

	return false;
}

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::JsonObject<CharaType>::GetKeys()const
{
	std::vector<std::basic_string<CharaType>> res;
	for (auto&& obj : values)
	{
		res.push_back(obj.first);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonObject<CharaType>::GetKeysToArray()const
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& obj : values)
	{
		res->Add(obj.first);
	}
	return res;
}

template<typename CharaType>
std::vector<ChPtr::Shared<ChCpp::JsonBaseType<CharaType>>> ChCpp::JsonObject<CharaType>::GetValues()const
{
	std::vector<ChPtr::Shared<ChCpp::JsonBaseType<CharaType>>> res;
	for (auto&& obj : values)
	{
		res.push_back(obj.second);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonObject<CharaType>::GetValuesToArray()const
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& obj : values)
	{
		res->Add(obj.second);
	}
	return res;
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonObject);
