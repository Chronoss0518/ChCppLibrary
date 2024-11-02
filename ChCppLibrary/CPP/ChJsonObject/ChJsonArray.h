#ifndef Ch_CPP_JsonArray_h
#define Ch_CPP_JsonArray_h

#include<vector>

#include"ChJsonBaseType.h"

#include"../ChTextObject/ChTextObject.h"

#ifndef	CH_Json_Array_Create_FunctionsDeclaration
#define	CH_Json_Array_Create_FunctionsDeclaration(_type) static ChPtr::Shared<JsonArray> CreateObject(const std::vector<_type>& _array);
#endif

#ifndef	CH_Json_Array_Create_Functions
#define	CH_Json_Array_Create_Functions(_type)\
template<typename CharaType>\
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::CreateObject(const std::vector<_type>& _array){\
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();\
	for (auto&& val : _array)\
		res->Add(val);\
	return res;}
#endif

#ifndef	CH_Json_Array_Add_FunctionsDeclaration
#define	CH_Json_Array_Add_FunctionsDeclaration(_type) void Add(const _type _value);
#endif

namespace ChCpp
{
	template<typename CharaType>
	class JsonArray :public JsonBaseType<CharaType>
	{
	public://static Create Function//

		Ch_Json_BaseTypeMethods(CH_Json_Array_Create_FunctionsDeclaration);

		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<bool>& _array);

		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<std::basic_string<CharaType>>& _array);

		template<typename BaseType>
		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<std::vector<BaseType>>& _array)
		{
			auto&& res = ChPtr::Make_S<JsonArray>();
			for (auto&& val : _array)
			{
				res->Add(JsonArray::CreateObject(val));
			}
			return res;
		}

	public:

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		void Set(unsigned long _num, const ChPtr::Shared<JsonBaseType<CharaType>> _value)
		{
			if (_value == nullptr)
			{
				Remove(_num);
				return;
			}
			if (_num >= values.size())return;
			values[_num] = nullptr;
			values[_num] = _value;
		}

	public:

		std::basic_string<CharaType> GetRawData()const override;

		unsigned long GetCount()const;

		ChPtr::Shared<JsonBaseType<CharaType>> GetJsonValue(unsigned long _num)const
		{
			if (_num >= values.size())return  nullptr;
			return values[_num];
		}

		ChPtr::Shared<JsonObject<CharaType>> GetJsonObject(unsigned long _num)const;

		ChPtr::Shared<JsonArray> GetJsonArray(unsigned long _num)const;

		ChPtr::Shared<JsonString<CharaType>> GetJsonString(unsigned long _num)const;

		ChPtr::Shared<JsonBoolean<CharaType>> GetJsonBoolean(unsigned long _num)const;

		ChPtr::Shared<JsonNumber<CharaType>> GetJsonNumber(unsigned long _num)const;

	public:

		void Add(ChPtr::Shared<JsonBaseType<CharaType>> _value)
		{
			if (_value == nullptr)return;
			values.push_back(_value);
		}

		Ch_Json_BaseTypeMethods(CH_Json_Array_Add_FunctionsDeclaration);

		void Add(const bool _value);

		void Add(const std::basic_string<CharaType>& _value);

		void Remove(unsigned long _num);

		void Clear();

	public:

		typename std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>::iterator begin() { return values.begin(); }

		typename std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>::iterator end() { return values.end(); }

	private:

		std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>values;

	};
}

#endif