#ifdef CRT

#ifdef Ch_CPP_JsonArray_h


#ifdef Ch_CPP_JsonNumber_h

#ifndef Ch_CPP_Shared_Json_Array_Number
#define Ch_CPP_Shared_Json_Array_Number

template<typename CharaType>
template<typename BaseType>
void ChCpp::JsonArray<CharaType>::Add(const BaseType _value)
{
	if (_value == nullptr)return;
	values.push_back(JsonNumber<CharaType>::CreateObject(_value));
}
#endif

#endif


#ifdef Ch_CPP_JsonString_h

#ifndef Ch_CPP_Shared_Json_Array_String
#define Ch_CPP_Shared_Json_Array_String

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Add(const std::basic_string<CharaType>& _value)
{
	values.push_back(JsonString<CharaType>::CreateObject(_value));
}
#endif

#endif


#ifdef Ch_CPP_JsonBoolean_h

#ifndef Ch_CPP_Shared_Json_Array_Boolean
#define Ch_CPP_Shared_Json_Array_Boolean

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Add(const bool _value)
{
	auto&& val = ChPtr::Make_S<ChCpp::JsonBoolean<CharaType>>();
	val->SetFlg(_value);
	values.push_back(val);
}

#endif

#endif


#endif
#endif