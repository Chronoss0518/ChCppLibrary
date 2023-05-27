#ifndef Ch_CPP_JsonBaseType_h
#define Ch_CPP_JsonBaseType_h

namespace ChCpp
{

	class JsonArray;
	class JsonNumber;
	class JsonString;
	class JsonBoolean;
	class JsonObject;

	class JsonBaseType
	{
	public:

		static ChPtr::Shared<JsonBaseType> GetParameter(const std::string& _json);

	private:

		static ChPtr::Shared<JsonObject> GetParameterToObject(const std::string& _json);

		static ChPtr::Shared<JsonArray> GetParameterToArray(const std::string& _json);

		static ChPtr::Shared<JsonString> GetParameterToString(const std::string& _json);

		static ChPtr::Shared<JsonBoolean> GetParameterToBoolean(const std::string& _json);

		static ChPtr::Shared<JsonNumber> GetParameterToNumber(const std::string& _json);

	public://Set Function//

		virtual bool SetRawData(const std::string& _jsonText) = 0;

	public://Get Function//

		virtual std::string GetRawData()const = 0;

	};

}

#endif