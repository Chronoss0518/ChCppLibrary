#ifndef Ch_CPP_JsonArray_h
#define Ch_CPP_JsonArray_h

#include"ChJsonBaseType.h"

namespace ChCpp
{

	class JsonArray :public JsonBaseType
	{
	public:

		bool SetRawData(const std::string& _jsonText)override;

		void SetValue(unsigned long _num, const JsonBaseType& _value);

		void SetObject(unsigned long _num, const JsonObject& _value);

		void SetArray(unsigned long _num, const JsonArray& _value);

		void SetString(unsigned long _num, const JsonString& _value);

		void SetBoolean(unsigned long _num, const JsonBoolean& _value);

		void SetNumber(unsigned long _num, const JsonNumber& _value);

	public:

		std::string GetRawData()const override;

		JsonBaseType GetValue(unsigned long _num)const;

		JsonBaseType GetObject(unsigned long _num)const;

		JsonBaseType GetArray(unsigned long _num)const;

		JsonBaseType GetString(unsigned long _num)const;

		JsonBaseType GetBoolean(unsigned long _num)const;

		JsonBaseType GetNumber(unsigned long _num)const;

	public:

		void AddObject(ChPtr::Shared<JsonBaseType> _value);

	private:

		std::vector<ChPtr::Shared<JsonBaseType>>values;

	};

}

#endif