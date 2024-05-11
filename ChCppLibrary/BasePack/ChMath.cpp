#include"../BaseIncluder/ChBase.h"

float ChMath::Round(const float& _val, const unsigned int _digit)
{
	double tmp = (double)(_val);

	float out = (float)Round(tmp, _digit);

	return out;
}

double ChMath::SqrtEx(const double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	double out = _base;

	long double tmp = (long double)(out);

	unsigned long maxCount = _digit > 307 ? 307 : _digit;

	out = (double)SqrtEx(tmp, maxCount);

	return out;
}

float ChMath::SqrtEx(const float& _base, const unsigned long _digit)
{
	if (_base == 0.0f)return 0.0f;

	float out = _base;

	long double tmp = (long double)(out);

	unsigned long maxCount = _digit > 37 ? 37 : _digit;

	out = (float)SqrtEx(tmp, maxCount);

	return out;
}

