#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

#ifdef CRT

#include<vector>
#include<map>

#endif

#include"ChJsonBaseType.h"

#ifndef CH_JSON_OBJECT_GET_SHARED_METHOD
#define CH_JSON_OBJECT_GET_SHARED_METHOD(_CastClass)\
template<typename CharaType>\
ChPtr::Shared<ChCpp::##_CastClass##<CharaType>> ChCpp::JsonObject<CharaType>::Get##_CastClass##(const std::basic_string<CharaType>& _parameterName){\
	auto findObject = values.find(_parameterName);\
	if (findObject == values.end())return nullptr;\
	return ChPtr::SharedSafeCast<##_CastClass##<CharaType>>(findObject->second);}
#endif

#ifndef CH_JSON_OBJECT_GET_RAW_METHOD
#define CH_JSON_OBJECT_GET_RAW_METHOD(_CastClass)\
template<typename CharaType>\
const ChCpp::##_CastClass##<CharaType>* const ChCpp::JsonObject<CharaType>::Get##_CastClass##(const std::basic_string<CharaType>& _parameterName)const{\
	auto findObject = values.find(_parameterName);\
	if (findObject == values.end())return nullptr;\
	return ChPtr::SafeCast<##_CastClass##<CharaType>>(findObject->second.get());}
#endif

namespace ChCpp
{
	template<typename CharaType>
	class JsonObject :public JsonBaseType<CharaType>
	{
	public://Set Function//

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		void Set(const std::basic_string<CharaType>& _parameterName,const ChPtr::Shared<JsonBaseType<CharaType>> _value);

	public: //Get Function//

		std::basic_string<CharaType> GetRawData()const override;

		//パラメーター名を取得する機能を追加//
		std::vector<std::basic_string<CharaType>> GetParameterNames()const;

		ChPtr::Shared<JsonObject<CharaType>> GetJsonObject(const std::basic_string<CharaType>& _parameterName);

		ChPtr::Shared<JsonArray<CharaType>> GetJsonArray(const std::basic_string<CharaType>& _parameterName);

		ChPtr::Shared<JsonString<CharaType>> GetJsonString(const std::basic_string<CharaType>& _parameterName);

		ChPtr::Shared<JsonBoolean<CharaType>> GetJsonBoolean(const std::basic_string<CharaType>& _parameterName);

		ChPtr::Shared<JsonNumber<CharaType>> GetJsonNumber(const std::basic_string<CharaType>& _parameterName);

		const JsonObject<CharaType>* const GetJsonObject(const std::basic_string<CharaType>& _parameterName)const;
		
		const JsonArray<CharaType>* const GetJsonArray(const std::basic_string<CharaType>& _parameterName)const;
		
		const JsonString<CharaType>* const GetJsonString(const std::basic_string<CharaType>& _parameterName)const;
		
		const JsonBoolean<CharaType>* const GetJsonBoolean(const std::basic_string<CharaType>& _parameterName)const;
		
		const JsonNumber<CharaType>* const GetJsonNumber(const std::basic_string<CharaType>& _parameterName)const;

		std::vector<std::basic_string<CharaType>>GetKeys()const;

		ChPtr::Shared<JsonArray<CharaType>> GetKeysToArray()const;

		std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>GetValues()const;

		ChPtr::Shared<JsonArray<CharaType>> GetValuesToArray()const;

	public:

		void Remove(const std::basic_string<CharaType>& _parameterName);

		void RemoveHard(const std::basic_string<CharaType>& _parameterName);

		void Clear();

	public:

		typename std::map<std::basic_string<CharaType>, ChPtr::Shared<JsonBaseType<CharaType>>>::iterator begin() { return values.begin(); }

		typename std::map<std::basic_string<CharaType>, ChPtr::Shared<JsonBaseType<CharaType>>>::iterator end() { return values.end(); }

	private:

		bool IsCutCharInParameterName(const std::basic_string<CharaType>& _parameterName);

	private:

		std::map<std::basic_string<CharaType>, ChPtr::Shared<JsonBaseType<CharaType>>> values;

	};


}

#ifdef CRT

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
	std::vector<std::string> res;

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

#endif

#include"SharedFunctions/ChJsonSharedArrayObject.h"

#endif
