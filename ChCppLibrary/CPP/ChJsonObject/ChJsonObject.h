#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

#include"ObjectType/ChJsonBaseType.h"

namespace ChCpp
{
	class JsonObject :public JsonBaseType
	{
	public://Set Function//

		bool SetRawData(const std::string& _jsonText)override;

		void SetObject(const std::string& _parameterName, const JsonObject& _value);

		void SetArray(const std::string& _parameterName,const JsonArray& _value);

		void SetString(const std::string& _parameterName,const JsonString& _value);

		void SetBoolean(const std::string& _parameterName, const JsonBoolean& _value);

		void SetNumber(const std::string& _parameterName, const JsonNumber& _value);

	public: //Get Function//

		std::string GetRawData()const override;

		JsonObject GetObject(const std::string& _parameterName)const;

		JsonArray GetArray(const std::string& _parameterName)const;

		JsonString GetString(const std::string& _parameterName)const;

		JsonBoolean GetBoolean(const std::string& _parameterName)const;

		JsonNumber GetNumber(const std::string& _parameterName)const;

	private:

		std::map<std::string, ChPtr::Shared<JsonBaseType>> value;

	};


}



#endif
