#include"ChMath.h"

#include <float.h>
#include <cmath>

#ifndef CH_MATH_FUNCTION
#define CH_MATH_FUNCTION(_Type,_FunctionName,_FunctionArg,_UseFunctionName,_UseFunctionArg)\
 _Type ChMath::_FunctionName ( _FunctionArg ) { return std::_UseFunctionName ( _UseFunctionArg ); }
#endif

#ifndef CH_FMOD_ARGUMENT
#define CH_FMOD_ARGUMENT(_Type) _Type _valx, _Type _valy 
#endif

#ifndef CH_FMOD_USE_ARGUMENT
#define CH_FMOD_USE_ARGUMENT  _valx, _valy 
#endif

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

double ChMath::Round(const double& _val, const unsigned long _digit)
{
	if (_val == 0.0)return 0.0;

	double out = _val * std::pow(10, static_cast<double>(_digit - 1));
	out = std::round(out);
	out = out * std::pow(0.1, static_cast<double>(_digit - 1));

	return out;
}

long double ChMath::SqrtEx(const long double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	long double out = std::sqrt(_base);
	//微分積分自分で使えるようになってから再度考える//
	return out;

	unsigned long maxCount = _digit > 4931 ? 4931 : _digit;

	//以下を参照//
	//https://qiita.com/rytaryu/items/e5d760a80f9ce5db860f
	//

	for (unsigned long i = 0; i < maxCount; i++)
	{
		out = ((out * out) + _base) / (2 * out);
	}

	return out;
}

CH_MATH_FUNCTION(float, GetSin, float _val, sin, _val);
CH_MATH_FUNCTION(double, GetSin, double _val, sin, _val);
CH_MATH_FUNCTION(long double, GetSin, long double _val, sin, _val);

CH_MATH_FUNCTION(float, GetASin, float _val, asin, _val);
CH_MATH_FUNCTION(double, GetASin, double _val, asin, _val);
CH_MATH_FUNCTION(long double, GetASin, long double _val, asin, _val);

CH_MATH_FUNCTION(float, GetCos, float _val, cos, _val);
CH_MATH_FUNCTION(double, GetCos, double _val, cos, _val);
CH_MATH_FUNCTION(long double, GetCos, long double _val, cos, _val);

CH_MATH_FUNCTION(float, GetACos, float _val, acos, _val);
CH_MATH_FUNCTION(double, GetACos, double _val, acos, _val);
CH_MATH_FUNCTION(long double, GetACos, long double _val, acos, _val);

CH_MATH_FUNCTION(float, GetATan, float _val, atan, _val);
CH_MATH_FUNCTION(double, GetATan, double _val, atan, _val);
CH_MATH_FUNCTION(long double, GetATan, long double _val, atan, _val);

CH_MATH_FUNCTION(float, GetFMod, CH_FMOD_ARGUMENT(float), fmod, CH_FMOD_USE_ARGUMENT);
CH_MATH_FUNCTION(double, GetFMod, CH_FMOD_ARGUMENT(double), fmod, CH_FMOD_USE_ARGUMENT);
CH_MATH_FUNCTION(long double, GetFMod, CH_FMOD_ARGUMENT(long double), fmod, CH_FMOD_USE_ARGUMENT);


float ChMath::GetMaxFloat()
{
	return FLT_MAX;
}
