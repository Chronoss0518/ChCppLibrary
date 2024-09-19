#ifndef Ch_CPP_JsonArray_h
#define Ch_CPP_JsonArray_h

#ifdef CRT

#include<vector>

#endif

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
	public:

		struct JsonArrayCRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>values;
#endif
		};

	public:

		JsonArray();
		
		virtual ~JsonArray();

	public://static Create Function//

#ifdef CRT
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
#endif

	public:

#ifdef CRT
		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		void Set(unsigned long _num, const ChPtr::Shared<JsonBaseType<CharaType>> _value)
		{
			if (_value == nullptr)
			{
				Remove(_num);
				return;
			}
			if (_num >= value->values.size())return;
			value->values[_num] = nullptr;
			value->values[_num] = _value;
		}
#endif

	public:

#ifdef CRT
		std::basic_string<CharaType> GetRawData()const override;
#endif

		unsigned long GetCount()const;

#ifdef CRT
		ChPtr::Shared<JsonBaseType<CharaType>> GetJsonValue(unsigned long _num)const
		{
			if (_num >= value->values.size())return  nullptr;
			return value->values[_num];
		}

		ChPtr::Shared<JsonObject<CharaType>> GetJsonObject(unsigned long _num)const
		{
			if (_num >= value->values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonObject<CharaType>>(value->values[_num]);
		}

		ChPtr::Shared<JsonArray> GetJsonArray(unsigned long _num)const
		{
			if (_num >= value->values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonArray>(value->values[_num]);
		}

		ChPtr::Shared<JsonString<CharaType>> GetJsonString(unsigned long _num)const
		{
			if (_num >= value->values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonString>(value->values[_num]);
		}

		ChPtr::Shared<JsonBoolean<CharaType>> GetJsonBoolean(unsigned long _num)const
		{
			if (_num >= value->values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonBoolean>(value->values[_num]);
		}

		ChPtr::Shared<JsonNumber<CharaType>> GetJsonNumber(unsigned long _num)const
		{
			if (_num >= value->values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonNumber>(value->values[_num]);
		}
#endif

	public:

#ifdef CRT
		void Add(ChPtr::Shared<JsonBaseType<CharaType>> _value)
		{
			if (_value == nullptr)return;
			value->values.push_back(_value);
		}

		Ch_Json_BaseTypeMethods(CH_Json_Array_Add_FunctionsDeclaration);

		void Add(const bool _value);

		void Add(const std::basic_string<CharaType>& _value);
#endif

		void Remove(unsigned long _num);

		void Clear();

	public:

#ifdef CRT
		typename std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>::iterator begin() { return value->values.begin(); }

		typename std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>::iterator end() { return value->values.end(); }
#endif

	private:

		JsonArrayCRT* value = nullptr;

	};
}

#ifdef CRT

template<typename CharaType>
ChCpp::JsonArray<CharaType>::JsonArray()
{
	value = new JsonArrayCRT();
}

template<typename CharaType>
ChCpp::JsonArray<CharaType>::~JsonArray()
{
	delete value;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToArray(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

template<typename CharaType>
bool ChCpp::JsonArray<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != ChStd::GetStartBracketChara<CharaType>()[0] ||
		_jsonText[_jsonText.size() - 1] != ChStd::GetEndBracketChara<CharaType>()[0])return false;

	std::basic_string<CharaType> parameter = _jsonText.substr(1, _jsonText.length() - 2);

	parameter = JsonBaseType<CharaType>::GetExtractString(parameter);

	TextObject<CharaType> parameterObject;

	parameterObject.SetCutChar(ChStd::GetCommaChara<CharaType>());

	parameterObject.SetText(parameter.c_str());

	for (unsigned long i = 0; i < parameterObject.LineCount(); i++)
	{
		std::basic_string<CharaType> val = parameterObject.GetTextLine(i);
		val = JsonBaseType<CharaType>::GetRawText(i, val, parameterObject, false);
		if (val.empty())continue;
		auto&& obj = JsonBaseType<CharaType>::GetParameter(val);
		if (obj == nullptr)continue;
		value->values.push_back(obj);
	}

	return true;

}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonArray<CharaType>::GetRawData()const
{
	std::basic_string<CharaType> res = ChStd::GetStartBracketChara<CharaType>();

	bool initFlg = false;

	for (auto&& val : value->values)
	{
		if (initFlg)res += ChStd::GetCommaChara<CharaType>();
		res += val->GetRawData();
		initFlg = true;
	}

	res += ChStd::GetEndBracketChara<CharaType>();

	return res;
}


template<typename CharaType>
unsigned long ChCpp::JsonArray<CharaType>::GetCount()const
{
	return value->values.size();
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Remove(unsigned long _num)
{
	if (value->values.empty())return;
	if (value->values.size() <= _num)return;

	value->values.erase(value->values.begin() + _num);
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Clear()
{
	if (value->values.empty())return;
	value->values.clear();
}


Ch_Json_BaseTypeMethods(CH_Json_Array_Create_Functions);

template<typename CharaType>
static ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::CreateObject(const std::vector<std::basic_string<CharaType>>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& val : _array)
	{
		res->Add(val);
	}
	return res;
}

template<typename CharaType>
static ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::CreateObject(const std::vector<bool>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& val : _array)
	{
		res->Add(val);
	}
	return res;
}



#endif

#include"SharedFunctions/ChJsonSharedArrayBooleanNumberString.h"

#include"SharedFunctions/ChJsonSharedArrayObject.h"

#endif