
#include"ChJsonBoolean.h"

namespace ChCpp
{
	namespace Json
	{
		CH_TO_NUMBER_FUNCTION(CH_JSON_TRUE_TEXT_FUNCTION, "true");

		CH_TO_NUMBER_FUNCTION(CH_JSON_FALSE_TEXT_FUNCTION, "false");
	}
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonBoolean<CharaType>> ChCpp::JsonBoolean<CharaType>::CreateObject(const bool& _flg)
{
	auto&& res = ChPtr::Make_S<JsonBoolean>();
	*res = _flg;
	return res;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>& ChCpp::JsonBoolean<CharaType>::operator = (const JsonBoolean& _val)
{
	value = _val.value;
	return *this;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>& ChCpp::JsonBoolean<CharaType>::operator = (const bool& _flg)
{
	value = _flg;
	return *this;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>::operator bool()const
{
	return value;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>::operator std::basic_string<CharaType>()const
{
	auto&& res = GetRawData();
	return res;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>::JsonBoolean()
{
	value = false;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>::JsonBoolean(const JsonBoolean& _val)
{
	*this = _val;
}

template<typename CharaType>
ChCpp::JsonBoolean<CharaType>::JsonBoolean(const bool& _val)
{
	*this = _val;
}

template<typename CharaType>
bool ChCpp::JsonBoolean<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	std::basic_string<CharaType> testValue = _jsonText;
	if (testValue.empty())return false;
	if (testValue.size() < 4)return false;
	if (testValue.size() > 5)return false;

	if (testValue == Json::GetTrueText<CharaType>())
	{
		value = true;
		return true;
	}

	if (testValue == Json::GetFalseText<CharaType>())
	{
		value = false;
		return true;
	}

	return false;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBoolean<CharaType>::GetRawData()const
{
	return value ? Json::GetTrueText<CharaType>() : Json::GetFalseText<CharaType>();
}


CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonBoolean);
