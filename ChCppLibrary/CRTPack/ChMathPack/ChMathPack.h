#ifndef Ch_CRT_Math
#define Ch_CRT_Math

#ifndef CH_MATH_LONG_TYPE
#define CH_MATH_LONG_TYPE(_type) long _type
#endif

#ifndef CH_MATH_SIGNED_TYPE
#define CH_MATH_SIGNED_TYPE(_type) signed _type
#endif


#ifndef CH_MATH_METHOD_SIGNED_ABS
#define CH_MATH_METHOD_SIGNED_ABS(_type) inline _type GetAbs(_type _val){return _val < 0 ? -_val : _val;}
#endif

#ifndef CH_MATH_METHOD_UNSIGNED_ABS
#define CH_MATH_METHOD_UNSIGNED_ABS(_type) inline unsigned _type GetAbs(unsigned _type _val){return _val;}
#endif

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

	static constexpr float GetMaxFloat();

	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(char));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(short));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(int));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(long));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(CH_MATH_LONG_TYPE(long)));
	CH_MATH_METHOD_SIGNED_ABS(float);
	CH_MATH_METHOD_SIGNED_ABS(double);
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_LONG_TYPE(double));

	CH_MATH_METHOD_UNSIGNED_ABS(char);
	CH_MATH_METHOD_UNSIGNED_ABS(short);
	CH_MATH_METHOD_UNSIGNED_ABS(int);
	CH_MATH_METHOD_UNSIGNED_ABS(long);
	CH_MATH_METHOD_UNSIGNED_ABS(CH_MATH_LONG_TYPE(long));

}

#endif