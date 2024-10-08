#ifndef Ch_CPP_JsonBoolean_h
#define Ch_CPP_JsonBoolean_h

#include"ChJsonBaseType.h"

#ifndef CH_JSON_TRUE_TEXT_FUNCTION
#define CH_JSON_TRUE_TEXT_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetTrueText,type)
#endif

#ifndef CH_JSON_FALSE_TEXT_FUNCTION
#define CH_JSON_FALSE_TEXT_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetFalseText,type)
#endif

namespace ChCpp
{
	namespace Json
	{
#ifdef CRT
		CH_TO_NUMBER_FUNCTION(CH_JSON_TRUE_TEXT_FUNCTION, "true");

		CH_TO_NUMBER_FUNCTION(CH_JSON_FALSE_TEXT_FUNCTION, "false");
#endif
	}

	template<typename CharaType>
	class JsonBoolean :public JsonBaseType<CharaType>
	{
	public://static Create Function//

#ifdef CRT
		static ChPtr::Shared<JsonBoolean> CreateObject(const bool& _flg);
#endif
	public://Operator Functions//

		JsonBoolean& operator = (const JsonBoolean& _val);

		JsonBoolean& operator = (const bool& _flg);

	public://To BaseClass Operator Functions//

		operator bool()const;

	public://To String Operator Functions//

#ifdef CRT
		operator std::basic_string<CharaType>()const;
#endif
	public://Constructor Destructor//

		JsonBoolean();

		JsonBoolean(const JsonBoolean& _val);

		JsonBoolean(const bool& _val);

	public:

#ifdef CRT
		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;
#endif
		inline void SetFlg(bool _flg) { value = _flg; }

	public:

#ifdef CRT
		std::basic_string<CharaType> GetRawData()const override;
#endif
	public:

		bool IsFlg() { return value; }

	private:

		bool value;
	};

}

#ifdef CRT

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonBoolean<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToBoolean(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonBoolean<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
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


#endif

#include"SharedFunctions/ChJsonSharedArrayBooleanNumberString.h"

#endif