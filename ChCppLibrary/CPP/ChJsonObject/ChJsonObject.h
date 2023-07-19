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

		ChPtr::Shared<JsonObject> GetObject(const std::string& _parameterName);

		ChPtr::Shared<JsonArray> GetArray(const std::string& _parameterName);

		ChPtr::Shared<JsonString> GetString(const std::string& _parameterName);

		ChPtr::Shared<JsonBoolean> GetBoolean(const std::string& _parameterName);

		ChPtr::Shared<JsonNumber> GetNumber(const std::string& _parameterName);

		const JsonObject* const GetObject(const std::string& _parameterName)const;
		
		const JsonArray* const GetArray(const std::string& _parameterName)const;
		
		const JsonString* const GetString(const std::string& _parameterName)const;
		
		const JsonBoolean* const GetBoolean(const std::string& _parameterName)const;
		
		const JsonNumber* const GetNumber(const std::string& _parameterName)const;

	private:

		std::map<std::string, ChPtr::Shared<JsonBaseType>> values;

	};


}



#endif
