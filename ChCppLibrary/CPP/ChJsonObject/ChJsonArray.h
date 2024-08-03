#ifndef Ch_CPP_JsonArray_h
#define Ch_CPP_JsonArray_h

#ifdef CRT

#include<vector>

#endif

#include"ChJsonBaseType.h"

#include"../ChTextObject/ChTextObject.h"

namespace ChCpp
{
	template<typename CharaType>
	class JsonArray :public JsonBaseType<CharaType>
	{
	public://static Create Function//

#ifdef CRT
		template<typename BaseType>
		static ChPtr::Shared<JsonArray> CreateObject(const std::vector<BaseType>& _array);

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
			if (_num >= values.size())return;
			values[_num] = nullptr;
			values[_num] = _value;
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
			if (_num >= values.size())return  nullptr;
			return values[_num];
		}

		ChPtr::Shared<JsonObject<CharaType>> GetJsonObject(unsigned long _num)const
		{
			if (_num >= values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonObject<CharaType>>(values[_num]);
		}

		ChPtr::Shared<JsonArray> GetJsonArray(unsigned long _num)const
		{
			if (_num >= values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonArray>(values[_num]);
		}

		ChPtr::Shared<JsonString<CharaType>> GetJsonString(unsigned long _num)const
		{
			if (_num >= values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonString>(values[_num]);
		}

		ChPtr::Shared<JsonBoolean<CharaType>> GetJsonBoolean(unsigned long _num)const
		{
			if (_num >= values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonBoolean>(values[_num]);
		}

		ChPtr::Shared<JsonNumber<CharaType>> GetJsonNumber(unsigned long _num)const
		{
			if (_num >= values.size())return  nullptr;
			return ChPtr::SharedSafeCast<JsonNumber>(values[_num]);
		}
#endif

	public:

#ifdef CRT
		void Add(ChPtr::Shared<JsonBaseType<CharaType>> _value)
		{
			if (_value == nullptr)return;
			values.push_back(_value);
		}

		template<typename BaseType>
		void Add(const BaseType _value);

		void Add(const bool _value);

		void Add(const std::basic_string<CharaType>& _value);
#endif

		void Remove(unsigned long _num);

		void Clear();

	public:

#ifdef CRT
		typename std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>::iterator begin() { return values.begin(); }

		typename std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>::iterator end() { return values.end(); }
#endif

	private:

#ifdef CRT
		std::vector<ChPtr::Shared<JsonBaseType<CharaType>>>values;
#endif

	};
}

#ifdef CRT

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
		std::basic_string<CharaType> value = parameterObject.GetTextLine(i);
		value = JsonBaseType<CharaType>::GetRawText(i, value, parameterObject, false);
		if (value.empty())continue;
		auto&& obj = JsonBaseType<CharaType>::GetParameter(value);
		if (obj == nullptr)continue;
		values.push_back(obj);
	}

	return true;

}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonArray<CharaType>::GetRawData()const
{
	std::basic_string<CharaType> res = ChStd::GetStartBracketChara<CharaType>();

	bool initFlg = false;

	for (auto&& val : values)
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
	return values.size();
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Remove(unsigned long _num)
{
	if (values.empty())return;
	if (values.size() <= _num)return;

	values.erase(values.begin() + _num);
}

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Clear()
{
	if (values.empty())return;
	values.clear();
}


template<typename CharaType>
template<typename BaseType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonArray<CharaType>::CreateObject(const std::vector<BaseType>& _array)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& val : _array)
	{
		res->Add(val);
	}
	return res;
}

#ifdef Ch_CPP_JsonNumber_h

template<typename CharaType>
template<typename BaseType>
void ChCpp::JsonArray<CharaType>::Add(const BaseType _value)
{
	if (_value == nullptr)return;
	values.push_back(JsonNumber<CharaType>::CreateObject(_value));
}

#endif


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

#ifdef Ch_CPP_JsonString_h

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Add(const std::basic_string<CharaType>& _value)
{
	values.push_back(JsonString<CharaType>::CreateObject(_value));
}

#endif

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


#ifdef Ch_CPP_JsonBoolean_h

template<typename CharaType>
void ChCpp::JsonArray<CharaType>::Add(const bool _value)
{
	if (_value == nullptr)return;
	values.push_back(_value);
}

#endif



#ifdef Ch_CPP_JsonObject_h

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::JsonObject<CharaType>::GetKeys()const
{
	std::vector<std::basic_string<CharaType>> res;
	for (auto&& obj : values)
	{
		res.push_back(obj.first);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonObject<CharaType>::GetKeysToArray()const
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	for (auto&& obj : values)
	{
		res->Add(obj.first);
	}
	return res;
}

template<typename CharaType>
std::vector<ChPtr::Shared<ChCpp::JsonBaseType<CharaType>>> ChCpp::JsonObject<CharaType>::GetValues()const
{
	std::vector<ChPtr::Shared<ChCpp::JsonBaseType<CharaType>>> res;
	for (auto&& obj : values)
	{
		res.push_back(obj.second);
	}
	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonObject<CharaType>::GetValuesToArray()const
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	for (auto&& obj : values)
	{
		res->Add(obj.second);
	}
	return res;
}

#endif

#endif

#endif