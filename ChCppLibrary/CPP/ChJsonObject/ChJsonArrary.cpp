#include"ChJsonArray.h"

#include"ChJsonObject.h"
#include"ChJsonBoolean.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"

#define	CH_Json_Array_Add_Functions(_type)\
template<typename CharaType>\
void ChCpp::JsonArray<CharaType>::Add(const _type _value){\
	auto&& val = ChPtr::Make_S<JsonNumber<CharaType>>();\
	*val = _value;\
	values.push_back(val);}

CH_BASE_TYPE_EXPLICIT_DECLARATION(CH_Json_Array_Add_Functions);


template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Add(const bool _value)
{
	auto&& val = ChPtr::Make_S<JsonBoolean<CharaType>>();
	*val = _value;
	values.push_back(val);
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Add(const std::basic_string<CharaType>& _value)
{
	auto&& val = ChPtr::Make_S<JsonString<CharaType>>();
	*val = _value;
	values.push_back(val);
}


template<typename CharaType>
bool ChCpp::JsonArray<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != ChStd::GetStartBracketChara<CharaType>()[0] ||
		_jsonText[_jsonText.size() - 1] != ChStd::GetEndBracketChara<CharaType>()[0])return false;

	std::basic_string<CharaType> parameter = _jsonText.substr(1, _jsonText.length() - 2);

	parameter = JsonBaseType<CharaType>::GetExtractString(parameter);

	TextObject<CharaType> parameterObject;

	parameterObject.SetCutChar(ChStd::GetCommaChara<CharaType>());

	parameterObject.SetText(parameter.c_str());

	for (unsigned long i = 0; i < parameterObject.LineCount(); i++)
	{
		std::basic_string<CharaType> val = parameterObject.GetTextLine(i);
		val = JsonBaseType<CharaType>::GetRawText(i, val, parameterObject, false);
		if (val.empty())continue;
		auto&& obj = JsonBaseType<CharaType>::GetParameter(val);
		if (obj == nullptr)continue;
		values.push_back(obj);
	}

	return true;

}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonArray<CharaType>::GetRawData()const
{
	std::basic_string<CharaType> res = ChStd::GetStartBracketChara<CharaType>();

	bool initFlg = false;

	for (auto&& val : values)
	{
		if (initFlg)res += ChStd::GetCommaChara<CharaType>();
		res += val->GetRawData();
		initFlg = true;
	}

	res += ChStd::GetEndBracketChara<CharaType>();

	return res;
}


template<typename CharaType>
unsigned long ChCpp::JsonArray<CharaType>::GetCount()const
{
	return values.size();
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonObject<CharaType>> ChCpp::JsonArray<CharaType>::GetJsonObject(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<ChCpp::JsonObject<CharaType>>(values[_num]);
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::GetJsonArray(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<ChCpp::JsonArray<CharaType>>(values[_num]);
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonString<CharaType>> ChCpp::JsonArray<CharaType>::GetJsonString(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<ChCpp::JsonString<CharaType>>(values[_num]);
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonBoolean<CharaType>> ChCpp::JsonArray<CharaType>::GetJsonBoolean(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<ChCpp::JsonBoolean<CharaType>>(values[_num]);
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonNumber<CharaType>> ChCpp::JsonArray<CharaType>::GetJsonNumber(unsigned long _num)const
{
	if (_num >= values.size())return  nullptr;
	return ChPtr::SharedSafeCast<ChCpp::JsonNumber<CharaType>>(values[_num]);
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Remove(unsigned long _num)
{
	if (values.empty())return;
	if (values.size() <= _num)return;

	values.erase(values.begin() + _num);
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Clear()
{
	if (values.empty())return;
	values.clear();
}


Ch_Json_BaseTypeMethods(CH_Json_Array_Create_Functions);

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::CreateObject(const std::vector<std::basic_string<CharaType>>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& val : _array)
	{
		res->Add(val);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::CreateObject(const std::vector<bool>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& val : _array)
	{
		res->Add(val);
	}
	return res;
}


CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonArray);