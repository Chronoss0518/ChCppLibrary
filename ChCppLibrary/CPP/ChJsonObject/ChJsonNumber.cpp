#include"ChJsonNumber.h"

using namespace ChCpp;

template<typename CharaType>
bool JsonNumber<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	if (!ChStd::IsBaseNumbers<CharaType>(_jsonText, ChStd::DECIMAL_NUMBUR<CharaType>()))return false;

	value = ChStr::GetNumFromText<long double>(_jsonText);
	return true;
}

template<typename CharaType>
std::basic_string<CharaType> JsonNumber<CharaType>::ToString()const
{
	std::basic_string<CharaType> tmpStr = ChStr::GetTextFromNum<CharaType>(value);
	unsigned long endPoint = tmpStr.find(ChStd::GetDotChara<CharaType>());
	for (unsigned long i = endPoint + 1; i < tmpStr.size(); i++)
	{
		if (tmpStr[i] == ChStd::GetZeroChara<CharaType>()[0])continue;
		endPoint = i + 1;
	}

	if (endPoint >= tmpStr.size())
	{
		return tmpStr;
	}

	return tmpStr.substr(0, endPoint);
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonNumber);
