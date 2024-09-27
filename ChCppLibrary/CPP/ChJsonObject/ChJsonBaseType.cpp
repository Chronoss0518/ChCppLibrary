#include"ChJsonBaseType.h"

#include"ChJsonBoolean.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"ChJsonArray.h"
#include"ChJsonObject.h"


using namespace ChCpp;


#ifndef CH_JSON_NULL_TEXT_FUNCTION
#define CH_JSON_NULL_TEXT_FUNCTION(type) CH_NUMBER_FUNCTION(ChCpp::Json::GetNullText,type)
#endif

namespace ChCpp
{
	namespace Json
	{
		CH_TO_NUMBER_FUNCTION(CH_JSON_NULL_TEXT_FUNCTION, "\"");
	}
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonNull<CharaType>::GetRawData()const
{
	return ChCpp::Json::GetNullText<CharaType>();
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonBaseType<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameter(const std::basic_string<CharaType>& _json)
{
	if (_json == ChCpp::Json::GetNullText<CharaType>())return ChPtr::Make_S<JsonNull<CharaType>>();

	ChPtr::Shared<JsonBaseType<CharaType>> res = nullptr;

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

	return  ChPtr::Make_S<JsonNull<CharaType>>();
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBaseType<CharaType>::FormatDocument(const std::basic_string<CharaType>& _str)
{
	std::vector<CharaType>testCharList = {
		ChStd::GetStartBracketChara<CharaType>()[0],
		ChStd::GetStartBraceChara<CharaType>()[0],
		ChStd::GetCommaChara<CharaType>()[0],
		ChStd::GetEndBraceChara<CharaType>()[0],
		ChStd::GetEndBracketChara<CharaType>()[0] };

	CH_JSON_OBJECT_COUNT;

	CH_JSON_ARRAY_COUNT;

	bool beforeCrFlg = false;
	bool afterCrFlg = false;

	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		beforeCrFlg = false;
		afterCrFlg = false;

		for (unsigned char j = 0; j < testCharList.size(); j++)
		{
			if (_str[i] != testCharList[j])continue;
			beforeCrFlg = j > 2;

			afterCrFlg = j <= 2;
			break;
		}

		objectCount.Update(_str[i]);
		arrayCount.Update(_str[i]);

		if ((beforeCrFlg) && i > 0)
		{
			res += ChStd::GetLFChara<CharaType>()[0] + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}

		res += _str[i];

		if (afterCrFlg)
		{
			res += ChStd::GetLFChara<CharaType>()[0] + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}
	}

	return res;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBaseType<CharaType>::GetTabText(unsigned long _count)
{
	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _count; i++)
		res += ChStd::GetTabChara<CharaType>();

	return res;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBaseType<CharaType>::GetExtractString(const std::basic_string<CharaType>& _value)
{
	bool inString = false;

	CH_JSON_OBJECT_COUNT;

	CH_JSON_ARRAY_COUNT;

	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

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

		objectCount.Update(_value[i]);
		arrayCount.Update(_value[i]);

		isInObjectOrArray = objectCount.GetCount() > 0 || arrayCount.GetCount() > 0;

		if (isInObjectOrArray)continue;
		if (_value[i] != '\"')continue;

		inString = !inString;
	}
	return res;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBaseType<CharaType>::GetRawText(unsigned long& _textPosition, const std::basic_string<CharaType>& _parameterObjectText, const ChCpp::TextObject<CharaType>& _parameterObject, bool _jsonObjectFlg)
{
	std::basic_string<CharaType> res = _parameterObjectText;

	CharaType baseStartText = res[0];
	if (baseStartText != ChStd::GetStartBracketChara<CharaType>()[0] &&
		baseStartText != ChStd::GetStartBraceChara<CharaType>()[0])return res;

	CharaType baseEndText = ChStd::GetEndBracketChara<CharaType>()[0];
	if (baseStartText == ChStd::GetStartBraceChara<CharaType>()[0])
		baseEndText = ChStd::GetEndBraceChara<CharaType>()[0];

	if (_jsonObjectFlg)
	{
		auto nameAndValue = ChStr::Split<CharaType>(_parameterObject.GetTextLine(_textPosition), ChStd::GetDoubleColonChara<CharaType>());

		for (unsigned long i = 2; i < nameAndValue.size(); i++)
			res += ChStd::GetDoubleColonChara<CharaType>() + nameAndValue[i];
	}
	else
	{
		res += ChStd::GetCommaChara<CharaType>();
	}


	ChCpp::Cumulative<CharaType> testNum = ChCpp::Cumulative<CharaType>(baseStartText, baseEndText);

	for (unsigned long i = 0; i < res.size(); i++)
	{
		testNum.Update(res[i]);
	}

	while (testNum.GetCount() > 0)
	{
		_textPosition++;
		if (_parameterObject.LineCount() <= _textPosition)return ChStd::GetZeroChara<CharaType>();
		std::basic_string<CharaType> testText = _parameterObject.GetTextLine(_textPosition);
		res += ChStd::GetCommaChara<CharaType>() + testText;

		for (unsigned long i = 0; i < testText.size(); i++)
		{
			testNum.Update(testText[i]);
		}

	}

	return res;
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonBaseType);
CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonNull);
