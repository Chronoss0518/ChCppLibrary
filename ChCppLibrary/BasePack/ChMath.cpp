#include"ChMath.h"

float ChMath::Round(const float& _val, const unsigned long _digit)
{
	return static_cast<float>(Round(static_cast<double>(_val), _digit));
}

double ChMath::SqrtEx(const double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	double out = _base;

	unsigned long maxCount = _digit > 307 ? 307 : _digit;

	out = static_cast<double>(SqrtEx(static_cast<long double>(out), maxCount));

	return out;
}

float ChMath::SqrtEx(const float& _base, const unsigned long _digit)
{
	if (_base == 0.0f)return 0.0f;

	float out = _base;

	unsigned long maxCount = _digit > 37 ? 37 : _digit;

	out = static_cast<float>(SqrtEx(static_cast<long double>(out), maxCount));

	return out;
}
