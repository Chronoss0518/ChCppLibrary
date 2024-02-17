#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonNumber.h"
#include"ChJsonString.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;


#define ESCAPE_SEQUENCE_COUNT 8

static constexpr unsigned char escapeSequenceBaseCharaList[ESCAPE_SEQUENCE_COUNT] =
{
	'\"',
	'\\',
	'\b',
	'\f',
	'\n',
	'\r',
	'\t'
};

static constexpr unsigned char escapeSequenceTextCharaList[ESCAPE_SEQUENCE_COUNT] =
{
	'\"',
	'\\',
	'b',
	'f',
	'n',
	'r',
	't'
};

ChPtr::Shared<JsonString> JsonString::CreateObject(const std::string& _text)
{
	auto&& res = ChPtr::Make_S<JsonString>();
	*res = _text;
	return res;
}

JsonString& JsonString::operator =(const JsonString& _value)
{
	if (this == &_value)return *this;
	value = _value.value;
	return *this;
}

JsonString& JsonString::operator +=(const JsonString& _value)
{
	value += _value.value;
	return *this;
}

JsonString JsonString::operator +(const JsonString& _value)const
{
	JsonString res = value;
	res += _value;
	return res;
}

JsonString& JsonString::operator =(const std::string& _value)
{
	if (&value == &_value)return *this;
	value = _value;
	return *this;
}

JsonString& JsonString::operator +=(const std::string& _value)
{
	value += _value;
	return *this;
}

JsonString JsonString::operator +(const std::string& _value)const
{
	JsonString res = value;
	res += _value;
	return res;
}

JsonString& JsonString::operator =(const char& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const short& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const int& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const long& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const long long& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const unsigned char& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const unsigned short& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const unsigned int& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const unsigned long& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const unsigned long long& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const float& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const double& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString& JsonString::operator =(const long double& _value)
{
	value = std::to_string(_value);
	return *this;
}

JsonString::operator std::string()const
{
	return GetString();
}

JsonString::JsonString()
{
	value = "";
}

JsonString::JsonString(const JsonString& _str)
{
	value = _str.value;
}

JsonString::JsonString(const std::string& _str)
{
	value = _str;
}

JsonString::JsonString(const JsonNumber& _number)
{
	value = _number.ToString();
}

JsonString::JsonString(const char& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const short& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const int& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const long& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const long long& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const unsigned char& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const unsigned short& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const unsigned int& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const unsigned long& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const unsigned long long& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const float& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const double& _value)
{
	*this = std::to_string(_value);
}

JsonString::JsonString(const long double& _value)
{
	*this = std::to_string(_value);
}

bool JsonString::SetRawData(const std::string& _jsonText)
{
	if (_jsonText.size() < 2)return false;

	auto textStartChar = _jsonText[0];
	if (!IsCutChar(textStartChar))return false;
	if (_jsonText[_jsonText.size() - 1] != textStartChar)return false;

	std::string testText = _jsonText.substr(1, _jsonText.size() - 2);

	std::string setTestText = "";

	bool isEscapeSequence = false;
	for (unsigned long i = 0; i < testText.size(); i++)
	{

		if (testText[i] == '\n')
			return false;


		if (testText[i] == '\\')
		{
			isEscapeSequence = false;
			for (unsigned long j = 0; j < ESCAPE_SEQUENCE_COUNT; j++)
			{
				if (testText[i + 1] != escapeSequenceTextCharaList[j])continue;
				i++;
				setTestText += escapeSequenceBaseCharaList[j];
				break;
				isEscapeSequence = true;
			}
			if (!isEscapeSequence)
			{
				return false;
			}

			continue;
		}

		setTestText += testText[i];
	}

	value = setTestText;

	return true;
}

std::string JsonString::GetRawData()const
{
	std::string outText = "";

	bool isEscapeSequence = false;

	for (unsigned long i = 0; i < value.size(); i++)
	{
		isEscapeSequence = false;

		for (unsigned char j = 0; j < ESCAPE_SEQUENCE_COUNT; j++)
		{
			if (escapeSequenceBaseCharaList[j] != outText[i])continue;
			outText += "\\";
			outText += escapeSequenceTextCharaList[j];
			isEscapeSequence = true;
			break;
		}

		if (isEscapeSequence)continue;

		outText += value[i];
	}

	return "\"" + outText + "\"";
}

void JsonString::SetString(const std::string& _text)
{
	value = _text;
}

std::string JsonString::GetString()const
{
	return value;
}

bool JsonString::IsCutChar(unsigned char _char)const
{
	return _char == '\"' || _char == '\'';
}

bool JsonString::AddDecimal(std::string& _outText, const std::string& _inText, const std::vector<char>& _baseDecimal)
{
	std::vector<char> tmp;

	for (unsigned char i = 0; i < _inText.size(); i++)
	{
		tmp.push_back(_inText[i]);
	}

	if (!ChStd::IsBaseNumbers(tmp, _baseDecimal))return false;

	tmp = ChStd::ToBaseNumber(tmp, _baseDecimal, ChStd::DECIMAL_NUMBUR());

	for (auto&& numChar : tmp)
	{
		_outText += numChar;
	}

	return true;

}