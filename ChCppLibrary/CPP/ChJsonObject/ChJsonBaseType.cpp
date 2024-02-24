#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonBaseType.h"
#include"ChJsonObject.h"
#include"ChJsonArray.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"ChJsonBoolean.h"
#include"../ChCumulative/ChCumulative.h"

#define USE_COLON_FLG 0

using namespace ChCpp;

constexpr char nullText[] = "null";

std::string JsonNull::GetRawData()const
{
	return nullText;
}

ChPtr::Shared<JsonBaseType> JsonBaseType::GetParameter(const std::string& _json)
{
	if (_json == nullText)return ChPtr::Make_S<JsonNull>();

	ChPtr::Shared<JsonBaseType> res = nullptr;

	res = GetParameterToObject(_json);

	if (res != nullptr)return res;

	res = GetParameterToArray(_json);

	if (res != nullptr)return res;

	res = GetParameterToString(_json);

	if (res != nullptr)return res;

	res = GetParameterToBoolean(_json);

	if (res != nullptr)return res;

	res = GetParameterToNumber(_json);

	if (res != nullptr)return res;

	return  ChPtr::Make_S<JsonNull>();
}

std::string JsonBaseType::FormatDocument(const std::string& _str)
{
	std::vector<char>testCharList = { '[','{' ,',', '}',']'};

	ChCpp::Cumulative<char> objectCount = ChCpp::Cumulative<char>('{' , '}');
	ChCpp::Cumulative<char> arrayCount = ChCpp::Cumulative<char>('[', ']');
	bool beforeCrFlg = false;
	bool afterCrFlg = false;
#if USE_COLON_FLG
	bool colonCrFlg = false;
#endif
	std::string res = "";

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		beforeCrFlg = false;
		afterCrFlg = false;
#if USE_COLON_FLG
		colonCrFlg = false;
#endif
		for (unsigned char j = 0; j <testCharList.size(); j++)
		{
			if (_str[i] != testCharList[j])continue;
			beforeCrFlg = j > 2;

#if USE_COLON_FLG
			afterCrFlg = j < 2;
			//colonCrFlg = j == 2;
#else
			afterCrFlg = j <= 2;
#endif 
			break;
		}

		objectCount.Update(_str[i]);
		arrayCount.Update(_str[i]);

		if ((beforeCrFlg) && i > 0)
		{
			res += '\n' + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}

		res += _str[i];

#if USE_COLON_FLG
		if (afterCrFlg || colonCrFlg)
		{
			res += '\n' + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}
#else

		if (afterCrFlg)
		{
			res += '\n' + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}
#endif

	}

	return res;
}

ChPtr::Shared<JsonObject> JsonBaseType::GetParameterToObject(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonObject>();
	if(!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonArray> JsonBaseType::GetParameterToArray(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonString> JsonBaseType::GetParameterToString(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonString>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonBoolean> JsonBaseType::GetParameterToBoolean(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonBoolean>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonNumber> JsonBaseType::GetParameterToNumber(const std::string& _json)
{
	if (_json.size() <= 0)return nullptr;
	if (_json.size() <= 1 && (_json[0] > 57 || _json[0] < 48))return nullptr;


	bool floatingPointFlg = false;

	auto&& res = ChPtr::Make_S<JsonNumber>();

	*res = ChStr::GetFloatingFromText<long double>(_json);

	return res;
}

std::string JsonBaseType::GetTabText(unsigned long _count)
{
	std::string res = "";

	for (unsigned long i = 0; i < _count; i++)
	{
		res += "\t";
	}

	return res;
}

std::string JsonBaseType::GetExtractString(const std::string& _value)
{
	bool inString = false;

	ChCpp::Cumulative<char>objectCumulative = ChCpp::Cumulative<char>('{', '}');
	ChCpp::Cumulative<char>arrayCumulative = ChCpp::Cumulative<char>('[', ']');

	std::string res = "";

	const char whiteSpaceInterfaceChar = 32;
	const char delCharNum = 127;

	bool isInObjectOrArray = false;

	for (unsigned long i = 0; i < _value.length(); i++)
	{
		if (!inString && !isInObjectOrArray)
		{
			if (_value[i] <= whiteSpaceInterfaceChar)continue;
			if (_value[i] == delCharNum)continue;
		}

		res = res + _value[i];

		objectCumulative.Update(_value[i]);
		arrayCumulative.Update(_value[i]);

		isInObjectOrArray = objectCumulative.GetCount() > 0 || arrayCumulative.GetCount() > 0;

		if (isInObjectOrArray)continue;
		if (_value[i] != '\"')continue;

		inString = !inString;

	}

	return res;


}


std::string JsonBaseType::GetRawText(unsigned long& _textPosition, const std::string& _parameterObjectText, const TextObject& _parameterObject,bool _jsonObjectFlg)
{
	std::string res = _parameterObjectText;
	ChPtr::Shared<ChCpp::Cumulative<char>> testNum = nullptr;


	if (res[0] == '[')
	{
		if (_jsonObjectFlg)
		{
			auto nameAndValue = ChStr::Split(_parameterObject.GetTextLine(_textPosition), ":");

			for (unsigned long i = 2; i < nameAndValue.size(); i++)
			{
				res += ":" + nameAndValue[i];
			}

		}

		testNum = ChPtr::Make_S<ChCpp::Cumulative<char>>('[', ']');
		
		for (unsigned long i = 0; i < res.size(); i++)
		{
			testNum->Update(res[i]);
		}


		while (testNum->GetCount() > 0)
		{
			_textPosition++;
			if (_parameterObject.LineCount() <= _textPosition)return "";
			std::string testText = _parameterObject.GetTextLine(_textPosition);
			res += "," + testText;

			for (unsigned long i = 0; i < testText.size(); i++)
			{
				testNum->Update(testText[i]);
			}

		}
	}
	else if (res[0] == '{')
	{
		if (_jsonObjectFlg)
		{
			auto nameAndValue = ChStr::Split(_parameterObject.GetTextLine(_textPosition), ":");

			for (unsigned long i = 2; i < nameAndValue.size(); i++)
			{
				res += ":" + nameAndValue[i];
			}

		}
		else
		{
			res += ",";
		}

		testNum = ChPtr::Make_S<ChCpp::Cumulative<char>>('{', '}');

		for (unsigned long i = 0; i < res.size(); i++)
		{
			testNum->Update(res[i]);
		}

		while(testNum->GetCount() > 0)
		{
			_textPosition++;
			if (_parameterObject.LineCount() <= _textPosition)return "";

			std::string testText = _parameterObject.GetTextLine(_textPosition);
			res += "," + testText;

			for (unsigned long i = 0; i < testText.size(); i++)
			{
				testNum->Update(testText[i]);
			}


		} 
	}

	return res;
}
