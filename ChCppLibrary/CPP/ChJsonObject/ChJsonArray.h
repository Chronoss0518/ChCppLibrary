#ifndef Ch_CPP_JsonArray_h
#define Ch_CPP_JsonArray_h

#include"ChJsonBaseType.h"

namespace ChCpp
{

	class JsonArray :public JsonBaseType
	{
	public://static Create Function//

		template<typename BaseType>
		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<BaseType>& _array);

		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<bool>& _array);

		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<std::string>& _array);

		template<typename BaseType>
		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<std::vector<BaseType>>& _array);

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


	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<char>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<short>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<int>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<long>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<long long>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<unsigned char>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<unsigned short>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<unsigned int>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<unsigned long>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<unsigned long long>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<float>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<double>& _array);
	template ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<long double>& _array);

	template<typename BaseType>
	ChPtr::Shared<JsonArray> JsonArray::CreateObject(const std::vector<std::vector<BaseType>>& _array)
	{
		auto&& res = ChPtr::Make_S<JsonArray>();
		for (auto&& val : _array)
		{
			res->AddObject(JsonArray::CreateObject(val));
		}
		return res;
	}


}

#endif