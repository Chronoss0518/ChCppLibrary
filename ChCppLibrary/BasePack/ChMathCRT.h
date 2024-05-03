#ifndef Ch_CPP_BMath_CRT_h
#define Ch_CPP_BMath_CRT_h

#include<cmath>

namespace ChMath
{
	double Round(const double& _val, const unsigned int _digit)
	{
		double out = _val * std::powl(10, static_cast<double>(_digit - 1));
		out = std::round(out);
		out = out * std::powl(0.1, static_cast<double>(_digit - 1));

		return out;
	}

	long double SqrtEx(const long double& _base, const unsigned long _digit)
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

}

#endif