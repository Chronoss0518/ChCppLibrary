
#include"../../BaseIncluder/ChBase.h"
#include"../ChCumulative/ChCumulative.h"

#include"ChScript.h"

using namespace ChCpp;

void Script::SetTmpValue(void* _value)
{
	tmpValue = _value;
}

void* Script::GetTmpValue()
{
	return tmpValue;
}