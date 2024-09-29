#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

#include<vector>
#include<map>

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
	public:

		JsonObject(){}

	public://Set Function//

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		void Set(const std::basic_string<CharaType>& _parameterName, const ChPtr::Shared<JsonBaseType<CharaType>> _value);

	public: //Get Function//

		std::basic_string<CharaType> GetRawData()const override;

		//�p�����[�^�[�����擾����@�\��ǉ�//
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

#endif
