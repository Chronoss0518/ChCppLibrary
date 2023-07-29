#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

#include"ChJsonBaseType.h"

namespace ChCpp
{
	class JsonObject :public JsonBaseType
	{
	public://Set Function//

		bool SetRawData(const std::string& _jsonText)override;

		void SetObject(const std::string& _parameterName,const ChPtr::Shared<JsonBaseType> _value);

	public: //Get Function//

		std::string GetRawData()const override;

		//パラメーター名を取得する機能を追加//
		std::vector<std::string> GetParameterNames()const;

		ChPtr::Shared<JsonObject> GetJsonObject(const std::string& _parameterName);

		ChPtr::Shared<JsonArray> GetJsonArray(const std::string& _parameterName);

		ChPtr::Shared<JsonString> GetJsonString(const std::string& _parameterName);

		ChPtr::Shared<JsonBoolean> GetJsonBoolean(const std::string& _parameterName);

		ChPtr::Shared<JsonNumber> GetJsonNumber(const std::string& _parameterName);

		const JsonObject* const GetJsonObject(const std::string& _parameterName)const;
		
		const JsonArray* const GetJsonArray(const std::string& _parameterName)const;
		
		const JsonString* const GetJsonString(const std::string& _parameterName)const;
		
		const JsonBoolean* const GetJsonBoolean(const std::string& _parameterName)const;
		
		const JsonNumber* const GetJsonNumber(const std::string& _parameterName)const;

	private:

		bool IsCutCharInParameterName(const std::string& _parameterName);

	private:

		std::map<std::string, ChPtr::Shared<JsonBaseType>> values;

	};


}



#endif
