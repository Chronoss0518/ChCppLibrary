#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"ChJsonObject.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;

bool JsonObjectBase::IsObject(const std::string& _json)
{

	Cumulative<char> cumulativeObjectChecker = Cumulative<char>('{', '}');
	Cumulative<char> cumulativeArrayChecker = Cumulative<char>('[', ']');
	unsigned long stringDQuotation = 0;
	unsigned long stringSQuotation = 0;

	cumulativeObjectChecker.Update(_json[0]);

	if (cumulativeObjectChecker.GetCount() <= 0)return false;

	for (unsigned long i = 1; i < _json.length(); i++)
	{
		cumulativeObjectChecker.Update(_json[i]);
		cumulativeArrayChecker.Update(_json[i]);

		if (_json[i] == '\'' && stringDQuotation % 2 <= 0)stringSQuotation += 1;
		if (_json[i] == '\"' && stringSQuotation % 2 <= 0)stringDQuotation += 1;

	}

	if (cumulativeObjectChecker.GetCount() > 0)return false;
	if (cumulativeArrayChecker.GetCount() > 0)return false;
	if (stringDQuotation % 2 > 0)return false;
	if (stringSQuotation % 2 > 0)return false;

	return true;
}

bool JsonObjectBase::IsArray(const std::string& _json)
{

}

bool JsonObjectBase::IsString(const std::string& _json)
{

}

bool JsonObjectBase::IsNumber(const std::string& _json)
{

}

bool JsonObjectBase::IsBoolean(const std::string& _json)
{

}

bool JsonObject::SetRawData(const std::string& _jsonText)
{
	Cumulative<char> cumulativeObjectChecker = Cumulative<char>('{', '}');

	cumulativeObjectChecker.Update(_jsonText[0]);

	if (cumulativeObjectChecker.GetCount() <= 0)return false;




	return true;

}

std::string JsonObject::GetRawData()const
{
	std::string res = "{";

	bool initFlg = false;

	for (auto&& val : value)
	{
		if (initFlg)res += ",";
		res += val.first + ":" + val.second->GetRawData();
		initFlg = true;
	}

	res += "}";

	return res;
}