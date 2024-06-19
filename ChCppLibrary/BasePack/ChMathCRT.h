#ifndef Ch_CPP_BMath_CRT_h
#define Ch_CPP_BMath_CRT_h

#include"ChMath.h"

#include<cmath>
#include<string>
#include<vector>

#include<string>
#include<type_traits>
#include<cstdlib>
#include <codecvt>
#include <string>
#include <cassert>
#include <locale>

#include"ChStrCRT.h"

double ChMath::Round(const double& _val, const unsigned int _digit)
{
	if (_val <= 0.0)return 0.0;

	double out = _val * std::powl(10, static_cast<double>(_digit - 1));
	out = std::round(out);
	out = out * std::powl(0.1, static_cast<double>(_digit - 1));

	return out;
}

long double ChMath::SqrtEx(const long double& _base, const unsigned long _digit)
{
	if (_base <= 0.0)return 0.0;

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

template<typename T, unsigned long Array>
const char* ChMath::VectorBase<T, Array>::Serialize(
	const char* _cutChar,
	const char* _endChar)const
{
	std::string tmp = "";
	for (unsigned char i = 0; i < Array; i++)
	{
		tmp += std::to_string(val[i]);
		if (i == (Array - 1))break;
		tmp += _cutChar;
	}

	tmp += _endChar;

	return tmp.c_str();
}

template<typename T, unsigned long Array>
const wchar_t* ChMath::VectorBase<T, Array>::Serialize(
	const wchar_t* _cutChar,
	const wchar_t* _endChar)const
{
	std::wstring tmp = L"";
	for (unsigned char i = 0; i < Array; i++)
	{
		tmp += std::to_wstring(val[i]);
		if (i == (Array - 1))break;
		tmp += _cutChar;
	}

	tmp += _endChar;

	return tmp.c_str();
}


template<typename T, unsigned long Array>
void ChMath::VectorBase<T, Array>::Deserialize(
	const char* _str,
	const size_t _fPos,
	const char* _cutChar,
	const char* _endChar,
	const unsigned int _digit)
{

	std::string tmpStr = _str;

	size_t tmpFPos = _fPos;

	size_t EPos = tmpStr.find(_endChar, tmpFPos);

	if (EPos == tmpStr.npos)EPos = tmpStr.size();

	tmpStr = tmpStr.substr(tmpFPos, EPos - tmpFPos);

	tmpFPos = 0;

	EPos = tmpStr.length();

	size_t tmp = tmpFPos;

	for (unsigned char i = 0; i < Array; i++)
	{
		size_t Test = tmpStr.find(_cutChar, tmp);
		if (Test > EPos)Test = EPos;
		{
			tmpFPos = Test;

			std::string Num = tmpStr.substr(tmp, tmpFPos - tmp);

			val[i] = static_cast<T>(ChStr::GetFloatingFromText<float>(Num));

			//val[i] = ChMath::Round(val[i], _digit);

			tmp += Num.length();
			tmp += 1;

		}

		if (Test >= EPos)return;
	}

}

template<typename T, unsigned long Array>
void ChMath::VectorBase<T, Array>::Deserialize(
	const wchar_t* _str,
	const size_t _fPos,
	const wchar_t* _cutChar,
	const wchar_t* _endChar,
	const unsigned int _digit)
{

	std::wstring tmpStr = _str;

	size_t tmpFPos = _fPos;

	size_t EPos = tmpStr.find(_endChar, tmpFPos);

	if (EPos == tmpStr.npos)EPos = tmpStr.size();

	tmpStr = tmpStr.substr(tmpFPos, EPos - tmpFPos);

	tmpFPos = 0;

	EPos = tmpStr.length();

	size_t tmp = tmpFPos;

	for (unsigned char i = 0; i < Array; i++)
	{
		size_t Test = tmpStr.find(_cutChar, tmp);
		if (Test > EPos)Test = EPos;
		{
			tmpFPos = Test;

			std::wstring Num = tmpStr.substr(tmp, tmpFPos - tmp);

			val[i] = static_cast<T>(ChStr::GetFloatingFromText<float>(Num));

			//val[i] = ChMath::Round(val[i], _digit);

			tmp += Num.length();
			tmp += 1;

		}

		if (Test >= EPos)return;
	}

}


template<typename T, unsigned long Array>
T ChMath::VectorBase<T, Array>::GetRadian(
	const VectorBase& _vec,
	const unsigned long _digit)const
{
	return static_cast<T>(std::acos(GetCos(_vec, _digit)));
}

template<typename T, unsigned long Array>
static ChMath::VectorBase<T, Array> ChMath::VectorBase<T, Array>::SLerp(
	const VectorBase<T, Array>& _start,
	const VectorBase<T, Array>& _end,
	const float _pow)
{

	if (_pow >= 1.0f)return _end;
	if (_pow <= 0.0f)return _start;

	VectorBase<T, Array> start = _start;
	VectorBase<T, Array> end = _end;

	float rad = start.GetDot(end);
	rad = std::acosf(rad);
	if (rad == 0.0f)return start;

	float baseSin = std::sinf(rad);

	if (baseSin == 0.0f)return start;

	start.Mul(std::sinf((1.0f - _pow) * rad) / baseSin);
	end.Mul(std::sinf(_pow * rad) / baseSin);

	return (start + end);
}



template<typename T, unsigned long Row, unsigned long Column>
const char* ChMath::MatrixBase<T,Row,Column>::Serialize(
	const char* _cutChar,
	const char* _endChar)const
{
	std::string tmp = "";
	for (unsigned char i = 0; i < Column; i++)
	{
		for (unsigned char j = 0; j < Row; j++)
		{
			if (i == 3 && j == 3)break;
			tmp += std::to_string(m[i][j]);
			tmp += _cutChar;
		}
	}

	tmp += std::to_string(m[3][3]);
	tmp += _endChar;

	return tmp.c_str();
}

template<typename T, unsigned long Row, unsigned long Column>
const wchar_t* ChMath::MatrixBase<T, Row, Column>::Serialize(
	const wchar_t* _cutChar,
	const wchar_t* _endChar)const
{
	std::wstring tmp = L"";
	for (unsigned char i = 0; i < Column; i++)
	{
		for (unsigned char j = 0; j < Row; j++)
		{
			if (i == 3 && j == 3)break;
			tmp += std::to_wstring(m[i][j]);
			tmp += _cutChar;
		}
	}

	tmp += std::to_wstring(m[3][3]);
	tmp += _endChar;

	return tmp.c_str();
}

template<typename T, unsigned long Row, unsigned long Column>
const char* ChMath::MatrixBase<T, Row, Column>::SerializeUpper(
	const char* _cutChar,
	const char* _endChar,
	const char* _cutTo4Char)const
{
	std::string tmp = "";
	for (unsigned char i = 0; i < Column; i++)
	{
		for (unsigned char j = 0; j < Row; j++)
		{
			if (i == 3 && j == 3)break;
			tmp += std::to_string(m[i][j]);
			tmp += _cutChar;

			if (j < 3)continue;
			tmp += _cutTo4Char;
		}
	}

	tmp += std::to_string(m[3][3]);
	tmp += _endChar;

	return tmp.c_str();
}

template<typename T, unsigned long Row, unsigned long Column>
const wchar_t* ChMath::MatrixBase<T, Row, Column>::SerializeUpper(
	const wchar_t* _cutChar,
	const wchar_t* _endChar,
	const wchar_t* _cutTo4Char)const
{
	std::wstring tmp = L"";
	for (unsigned char i = 0; i < Column; i++)
	{
		for (unsigned char j = 0; j < Row; j++)
		{
			if (i == 3 && j == 3)break;
			tmp += std::to_wstring(m[i][j]);
			tmp += _cutChar;

			if (j < 3)continue;
			tmp += _cutTo4Char;
		}
	}

	tmp += std::to_wstring(m[3][3]);
	tmp += _endChar;

	return tmp.c_str();
}

template<typename T, unsigned long Row, unsigned long Column>
void ChMath::MatrixBase<T, Row, Column>::Deserialize(
	const char* _str,
	const size_t _fPos,
	const char* _cutChar,
	const char* _endChar,
	const unsigned int _digit)
{

	std::string tmpStr = _str;

	size_t tmpFPos = _fPos;

	size_t EPos = tmpStr.find(_endChar, tmpFPos);

	if (EPos == tmpStr.npos)EPos = tmpStr.size() - 1;

	tmpStr = tmpStr.substr(tmpFPos, EPos - tmpFPos);

	tmpFPos = 0;

	EPos = tmpStr.length();

	size_t tmp = tmpFPos;

	for (unsigned char i = 0; i < Column; i++)
	{
		for (unsigned char j = 0; j < Row; j++)
		{
			size_t Test = tmpStr.find(_cutChar, tmp);

			if (Test > EPos)Test = EPos;

			{
				tmpFPos = Test;

				std::string Num = tmpStr.substr(tmp, tmpFPos - tmp);

				m[i][j] = static_cast<T>(ChStr::GetFloatingFromText<float>(Num));

				tmp = Test + 1;

			}

			if (Test >= EPos)return;
		}

	}

}

template<typename T, unsigned long Row, unsigned long Column>
void ChMath::MatrixBase<T, Row, Column>::Deserialize(
	const wchar_t* _str,
	const size_t _fPos,
	const wchar_t* _cutChar,
	const wchar_t* _endChar,
	const unsigned int _digit)
{

	std::wstring tmpStr = _str;

	size_t tmpFPos = _fPos;

	size_t EPos = tmpStr.find(_endChar, tmpFPos);

	if (EPos == tmpStr.npos)EPos = tmpStr.size() - 1;

	tmpStr = tmpStr.substr(tmpFPos, EPos - tmpFPos);

	tmpFPos = 0;

	EPos = tmpStr.length();

	size_t tmp = tmpFPos;

	for (unsigned char i = 0; i < Column; i++)
	{
		for (unsigned char j = 0; j < Row; j++)
		{
			size_t Test = tmpStr.find(_cutChar, tmp);

			if (Test > EPos)Test = EPos;

			{
				tmpFPos = Test;

				std::wstring Num = tmpStr.substr(tmp, tmpFPos - tmp);

				m[i][j] = static_cast<T>(ChStr::GetFloatingFromText<float>(Num));

				tmp = Test + 1;

			}

			if (Test >= EPos)return;
		}

	}

}

#endif