
#include"../../BaseIncluder/ChBase.h"
#include"ChJsonObjectIfication.h"

using namespace ChCp;

struct JsonObject : public JsonObjectIfication::JsonClassBase
{
	JsonObject()
	{
		Init(JsonType::Object);
	}

	JsonObjectIfication* value = nullptr;

	std::string SerializeFromCharText()
	{
		if (ChPtr::NullCheck(value))return "";
		return value->SerializeFromCharText();
	}

	std::wstring SerializeFromWCharText()
	{
		if (ChPtr::NullCheck(value))return L"";
		return value->SerializeFromWCharText();
	}

	void DeserializeFromCharText(const std::string& _text)
	{
		if (ChPtr::NullCheck(value));
		value->DeserializeFromCharText(_text);
	}

	void DeserializeFromWCharText(const std::wstring& _text)
	{
		if (ChPtr::NullCheck(value));
		value->DeserializeFromWCharText(_text);
	}

};

template<typename BaseType>
struct JsonNumber : public JsonObjectIfication::JsonClassBase
{
	JsonNumber()
	{
		Init(JsonType::Number);
	}

	BaseType* value = nullptr;

	std::string SerializeFromCharText()override
	{
		if (ChPtr::NullCheck(value))return "";
		return std::to_string(*value);
	}

	std::wstring SerializeFromWCharText()override
	{
		if (ChPtr::NullCheck(value))return L"";
		return std::to_wstring(*value);
	}

	void DeserializeFromCharText(const std::string& _text)override
	{
		if (ChPtr::NullCheck(value))return;
		*value = static_cast<BaseType>(ChStr::GetFloatingFromText(_text));
	}

	void DeserializeFromWCharText(const std::wstring& _text)override
	{
		if (ChPtr::NullCheck(value))return;
		*value = static_cast<BaseType>(ChStr::GetFloatingFromText(_text));
	}

};

struct JsonString : public JsonObjectIfication::JsonClassBase
{
	JsonString()
	{
		Init(JsonType::String);
	}

	std::wstring* value = nullptr;

	std::string SerializeFromCharText()override
	{
		if (ChPtr::NullCheck(value))return "";
		return "\"" + ChStr::UTF8ToString(*value) + "\"";
	}

	std::wstring SerializeFromWCharText()override
	{
		if (ChPtr::NullCheck(value))return L"";
		return L"\"" + *value + L"\"";
	}

	void DeserializeFromCharText(const std::string& _text)override
	{
		if (ChPtr::NullCheck(value))return;
		std::string tmp = ChStr::RemoveToChars(_text, '\"');
		*value = ChStr::UTF16ToWString(tmp);
	}

	void DeserializeFromWCharText(const std::wstring& _text)override
	{
		if (ChPtr::NullCheck(value))return;
		*value = ChStr::RemoveToChars(_text, L'\"');
	}


};

struct JsonBoolean : public JsonObjectIfication::JsonClassBase
{
	JsonBoolean()
	{
		Init(JsonType::Boolean);
	}

	bool* value = nullptr;

	std::string SerializeFromCharText()override
	{
		if (ChPtr::NullCheck(value))return "";
		return (*value) ? "TRUE" : "FALSE";
	}

	std::wstring SerializeFromWCharText()override
	{
		if (ChPtr::NullCheck(value))return L"";
		return (*value) ? L"TRUE" : L"FALSE";
	}

	void DeserializeFromCharText(const std::string& _text)override
	{
		if (ChPtr::NullCheck(value))return;
		*value = _text == "TRUE";
	}

	void DeserializeFromWCharText(const std::wstring& _text)override
	{
		if (ChPtr::NullCheck(value))return;
		*value = _text == L"TRUE";
	}


};

template<typename BaseType>
struct JsonArray : public JsonObjectIfication::JsonClassBase
{
	JsonArray()
	{
		Init(JsonType::Array);
	}

	std::vector<BaseType>* value;

	std::string SerializeFromCharText()override;
	std::wstring SerializeFromWCharText()override;

	void DeserializeFromCharText(const std::string& _text)override;
	void DeserializeFromWCharText(const std::wstring& _text)override;
};

template class JsonNumber<char>;
template class JsonNumber<short>;
template class JsonNumber<int>;
template class JsonNumber<long>;
template class JsonNumber<long long>;
template class JsonNumber<unsigned char>;
template class JsonNumber<unsigned short>;
template class JsonNumber<unsigned int>;
template class JsonNumber<unsigned long>;
template class JsonNumber<unsigned long long>;
template class JsonNumber<float>;
template class JsonNumber<double>;
template class JsonNumber<long double>;

template class JsonArray<char>;
template class JsonArray<short>;
template class JsonArray<int>;
template class JsonArray<long>;
template class JsonArray<long long>;
template class JsonArray<unsigned char>;
template class JsonArray<unsigned short>;
template class JsonArray<unsigned int>;
template class JsonArray<unsigned long>;
template class JsonArray<unsigned long long>;
template class JsonArray<float>;
template class JsonArray<double>;
template class JsonArray<long double>;
template class JsonArray<bool>;
template class JsonArray<ChPtr::Shared<JsonObjectIfication>>;

template void JsonObjectIfication::AddValue(char* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(short* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(int* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(long* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(long long* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(unsigned char* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(unsigned short* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(unsigned int* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(unsigned long* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(unsigned long long* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(float* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(double* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(long double* _value, const std::string& _parameterName);

template void JsonObjectIfication::AddValue(std::vector<char>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<short>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<int>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<long>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<long long>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<unsigned char>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<unsigned short>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<unsigned int>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<unsigned long>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<unsigned long long>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<float>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<double>* _value, const std::string& _parameterName);
template void JsonObjectIfication::AddValue(std::vector<long double>* _value, const std::string& _parameterName);


template<typename BaseType>
void JsonObjectIfication::AddValue(BaseType* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonNumber<BaseType>>();
	value->value = _value;
	findObject->second = value;
}

void JsonObjectIfication::AddValue(bool* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonBoolean>();
	value->value = _value;
	findObject->second = value;
}

void JsonObjectIfication::AddValue(std::wstring* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonString>();
	value->value = _value;
	findObject->second = value;
}

void JsonObjectIfication::AddValue(JsonObjectIfication* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonObject>();
	value->value = _value;
	findObject->second = value;
}

template<typename BaseType>
void JsonObjectIfication::AddValue(std::vector<BaseType>* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonArray<std::vector<BaseType>>>();
	value->value = _value;
	findObject->second = value;
}

void JsonObjectIfication::AddValue(std::vector<bool>* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonArray<bool>>();
	value->value = _value;
	findObject->second = value;
}

void JsonObjectIfication::AddValue(std::vector<std::wstring>* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonArray<std::wstring>>();
	value->value = _value;
	findObject->second = value;
}

void JsonObjectIfication::AddValue(std::vector<ChPtr::Shared<JsonObjectIfication>>* _value, const std::string& _parameterName)
{
	if (ChPtr::NullCheck(_value))return;
	auto&& findObject = jsonValues.find(_parameterName);
	if (findObject != jsonValues.end())return;
	auto value = ChPtr::Make_S<JsonArray<ChPtr::Shared<JsonObjectIfication>>>();
	value->value = _value;
	findObject->second = value;
}

std::string SerializeFromCharText()
{

}

std::wstring SerializeFromWCharText()
{

}

void DeserializeFromCharText(const std::string& _text)
{

}

void DeserializeFromWCharText(const std::wstring& _text)
{

}
