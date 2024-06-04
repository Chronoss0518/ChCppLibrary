#include"../BaseIncluder/ChBase.h"

using namespace ChMath;


float ChMath::Round(const float& _val, const unsigned int _digit)
{
	float out = _val * std::powf(10.0f, static_cast<float>(_digit - 1));
	out = std::round(out);
	out = out * std::powf(0.1f, static_cast<float>(_digit - 1));

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

double ChMath::Round(const double& _val, const unsigned int _digit)
{
	double out = _val * std::powl(10, static_cast<double>(_digit - 1));
	out = std::round(out);
	out = out * std::powl(0.1, static_cast<double>(_digit - 1));

	return out;

}

long double ChMath::SqrtEx(const long double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	long double out = std::sqrt(_base);

	//�����ϕ������Ŏg����悤�ɂȂ��Ă���ēx�l����//
	return out;

	unsigned long maxCount = _digit > 4931 ? 4931 : _digit;

	//�ȉ����Q��//
	//https://qiita.com/rytaryu/items/e5d760a80f9ce5db860f
	//

	for (unsigned long i = 0; i < maxCount; i++)
	{
		out = ((out * out) + _base) / (2 * out);
	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

double ChMath::SqrtEx(const double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	double out = _base;

	unsigned long maxCount = _digit > 307 ? 307 : _digit;

	out = static_cast<double>(SqrtEx(static_cast<long double>(out), maxCount));

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

float ChMath::SqrtEx(const float& _base, const unsigned long _digit)
{
	if (_base == 0.0f)return 0.0f;

	float out = _base;

	unsigned long maxCount = _digit > 37 ? 37 : _digit;

	out = static_cast<float>(SqrtEx(static_cast<long double>(out), maxCount));

	return out;
}
