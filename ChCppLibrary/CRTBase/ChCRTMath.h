#ifndef Ch_CRT_Math
#define Ch_CRT_Math

namespace ChMath
{

	double Round(const double& _val, const unsigned long _digit = 307);

	float Round(const float& _val, const unsigned long _digit = 37);

	long double SqrtEx(const long double& _base, const unsigned long _digit = 4931);

	double SqrtEx(const double& _base, const unsigned long _digit = 307);

	float SqrtEx(const float& _base, const unsigned long _digit = 37);

	float GetSin(float _val);
	double GetSin(double _val);
	long double GetSin(long double _val);

	float GetASin(float _val);
	double GetASin(double _val);
	long double GetASin(long double _val);

	float GetACos(float _val);
	double GetACos(double _val);
	long double GetACos(long double _val);

	float GetCos(float _val);
	double GetCos(double _val);
	long double GetCos(long double _val);

	float GetATan(float _val);
	double GetATan(double _val);
	long double GetATan(long double _val);

	float GetFMod(float _valx, float _valy);
	double GetFMod(double _valx, double _valy);
	long double GetFMod(long double _valx, long double _valy);

	float GetMaxFloat();

}

#endif