
#ifdef CRT

#ifdef Ch_CPP_JsonObject_h
#ifdef Ch_CPP_JsonArray_h

#ifndef Ch_CPP_Shared_Json_Object_Array
#define Ch_CPP_Shared_Json_Object_Array

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::JsonObject<CharaType>::GetKeys()const
{
	std::vector<std::basic_string<CharaType>> res;
	for (auto&& obj : value->values)
	{
		res.push_back(obj.first);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonObject<CharaType>::GetKeysToArray()const
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& obj : value->values)
	{
		res->Add(obj.first);
	}
	return res;
}

template<typename CharaType>
std::vector<ChPtr::Shared<ChCpp::JsonBaseType<CharaType>>> ChCpp::JsonObject<CharaType>::GetValues()const
{
	std::vector<ChPtr::Shared<ChCpp::JsonBaseType<CharaType>>> res;
	for (auto&& obj : value->values)
	{
		res.push_back(obj.second);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonObject<CharaType>::GetValuesToArray()const
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	for (auto&& obj : value->values)
	{
		res->Add(obj.second);
	}
	return res;
}

#endif

#endif
#endif

#endif