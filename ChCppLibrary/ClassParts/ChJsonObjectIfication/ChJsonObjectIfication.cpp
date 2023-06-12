
#include"../../BaseIncluder/ChBase.h"
#include"ChJsonObjectIfication.h"

namespace ChCp
{
	struct JsonClassBase :protected ChCp::Initializer
	{
	public:

		void Init(JsonType _type)
		{
			if (*this)return;
			type = type;
			SetInitFlg(true);
		}
		virtual std::string SerializeFromCharText() = 0;

		virtual std::wstring SerializeFromWCharText() = 0;

		virtual void DeserializeFromCharText(const std::string& _text) = 0;

		virtual void DeserializeFromWCharText(const std::wstring& _text) = 0;

	private:

		JsonType type;

	};

}

using namespace ChCp;


struct JsonObject : public JsonClassBase
{
	JsonObject()
	{
		Init(JsonType::Object);
	}

	JsonObjectIfication* value = nullptr;

	std::string SerializeFromCharText()override
	{
		if (ChPtr::NullCheck(value))return "";
		return value->SerializeFromCharText();
	}

	std::wstring SerializeFromWCharText()override
	{
		if (ChPtr::NullCheck(value))return L"";
		return value->SerializeFromWCharText();
	}

	void DeserializeFromCharText(const std::string& _text)override
	{
		if (ChPtr::NullCheck(value));
		value->DeserializeFromCharText(_text);
	}

	void DeserializeFromWCharText(const std::wstring& _text)override
	{
		if (ChPtr::NullCheck(value));
		value->DeserializeFromWCharText(_text);
	}

};

template<typename BaseType>
struct JsonNumber : public JsonClassBase
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

struct JsonString : public JsonClassBase
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

struct JsonBoolean : public JsonClassBase
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
