#ifndef Ch_CPP_JsonArray_h
#define Ch_CPP_JsonArray_h

#include"ChJsonBaseType.h"

namespace ChCpp
{

	class JsonArray :public JsonBaseType
	{
	public:

		bool SetRawData(const std::string& _jsonText)override;

		void SetValue(unsigned long _num, const ChPtr::Shared<JsonBaseType> _value);

	public:

		std::string GetRawData()const override;

		unsigned long GetCount()const;

		ChPtr::Shared<JsonBaseType> GetValue(unsigned long _num)const;

		ChPtr::Shared<JsonObject> GetObject(unsigned long _num)const;

		ChPtr::Shared<JsonArray> GetArray(unsigned long _num)const;

		ChPtr::Shared<JsonString> GetString(unsigned long _num)const;

		ChPtr::Shared<JsonBoolean> GetBoolean(unsigned long _num)const;

		ChPtr::Shared<JsonNumber> GetNumber(unsigned long _num)const;

	public:

		void AddObject(ChPtr::Shared<JsonBaseType> _value);

	private:

		std::vector<ChPtr::Shared<JsonBaseType>>values;

	};

}

#endif