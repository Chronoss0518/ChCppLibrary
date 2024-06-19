#pragma once
#include "ChMathCRT.h"
#include"ChMath3D.h"

#define FLOAT_ZERO_TEST(val, testSize) val >= -testSize && val <= testSize

#include <float.h>
#include <cmath>


inline const char* ChVector2::Serialize(
	const char* _cutChar,
	const char* _endChar)const
{
	return val.Serialize(_cutChar, _endChar);
}


inline const wchar_t* ChVector2::Serialize(
	const wchar_t* _cutChar,
	const wchar_t* _endChar)const
{
	return val.Serialize(_cutChar, _endChar);
}


inline void ChVector2::Deserialize(
	const char* _str,
	const size_t _fPos,
	const char* _cutChar,
	const char* _endChar,
	const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
}

inline void ChVector2::Deserialize(
	const wchar_t* _str,
	const size_t _fPos,
	const wchar_t* _cutChar,
	const wchar_t* _endChar,
	const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
}

ChVector2 ChVec2::GetCross(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	ChVector2 tmpVec;
	tmpVec.val.Cross(_vec1.val, _vec2.val, _digit);
	return tmpVec;
}

float ChVec2::GetCos(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetCos(_vec2.val, _digit);
}

float ChVec2::GetRadian(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetRadian(_vec2.val, _digit);
}

float ChVec2::GetDot(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetDot(_vec2.val, _digit);
}

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
ChVector2 ChVec2::GetCorrection(
	const ChVector2& _start
	, const ChVector2& _end
	, const float _Now)
{
	ChVector2 tmpVec;
	tmpVec.val.Correction(_start.val, _end.val, _Now);
	return tmpVec;
}

float ChVec2::GetLen(
	const ChVector2& _vec1
	, const ChVector2& _vec2,
	const unsigned long _digit)
{
	ChVec2 tmpVec = _vec1 - _vec2;
	return  tmpVec.val.GetLen(_digit);
}

float ChVec2::GetElementsLen(
	const ChVector2& _vec1
	, const ChVector2& _vec2)
{
	ChVec2 tmpVec = _vec1 - _vec2;
	return  tmpVec.val.GetElementsLen();
}

ChVector2 ChVector2::Lerp(
	const ChVector2& _start,
	const ChVector2& _end,
	const float _pow)
{
	ChVector2 out;
	out.val.Set(ChMath::VectorBase<float, 2>::Lerp(_start.val, _end.val, _pow));
	return out;
}



ChVector3 ChVec3::GetCross(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	ChVector3 tmpVec;
	tmpVec.val.Cross(_vec1.val, _vec2.val, _digit);
	return tmpVec;
}

float ChVec3::GetCos(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetCos(_vec2.val, _digit);
}

float ChVec3::GetRadian(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetRadian(_vec2.val, _digit);
}

float ChVec3::GetDot(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetDot(_vec2.val, _digit);
}

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
ChVector3 ChVec3::GetCorrection(
	const ChVector3& _start,
	const ChVector3& _end,
	const float _Now)
{
	ChVector3 tmpVec;
	tmpVec.val.Correction(_start.val, _end.val, _Now);
	return tmpVec;
}

float ChVec3::GetLen(
	const ChVector3& _vec1
	, const ChVector3& _vec2,
	const unsigned long _digit)
{
	ChVec3 tmpVec = _vec1 - _vec2;
	return  tmpVec.val.GetLen(_digit);
}

float ChVec3::GetElementsLen(
	const ChVector3& _vec1,
	const ChVector3& _vec2)
{
	ChVec3 tmpVec = _vec1 - _vec2;
	return  tmpVec.val.GetElementsLen();
}




const char* ChVec4::SerializeARGB(
	const char* _cutChar,
	const char* _endChar)const
{
	ChVec4 tmpVec;

	for (unsigned char i = 0; i < 4; i++)
	{
		tmpVec.val[(i + 1) % 4] = val[i];
	}

	return tmpVec.Serialize(_cutChar, _endChar);
}

const wchar_t* ChVec4::SerializeARGB(
	const wchar_t* _cutChar,
	const wchar_t* _endChar)const
{
	ChVec4 tmpVec;

	for (unsigned char i = 0; i < 4; i++)
	{
		tmpVec.val[(i + 1) % 4] = val[i];
	}

	return tmpVec.Serialize(_cutChar, _endChar);
}

void ChVec4::DeserializeARGB(
	const char* _str,
	const size_t _fPos,
	const char* _cutChar,
	const char* _endChar,
	const unsigned int _digit)
{
	ChVec4 tmpVec;
	tmpVec.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);

	for (unsigned char i = 0; i < 4; i++)
	{
		val[i] = tmpVec.val[(i + 1) % 4];
	}
}

void ChVec4::DeserializeARGB(
	const wchar_t* _str,
	const size_t _fPos,
	const wchar_t* _cutChar,
	const wchar_t* _endChar,
	const unsigned int _digit)
{
	ChVec4 tmpVec;
	tmpVec.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);

	for (unsigned char i = 0; i < 4; i++)
	{
		val[i] = tmpVec.val[(i + 1) % 4];
	}
}



//à»â∫ÇÃURLÇéQè∆//
//https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf#%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%8B%E3%82%89%E5%9B%9E%E8%BB%A2%E8%A1%8C%E5%88%97
//
void ChQua::SetRotationLMatrix(const ChLMatrix& _mat)
{

	w = std::sqrtf(_mat.l_11 + _mat.l_22 + _mat.l_33 + 1.0f) / 2.0f;

	if (w != 0)
	{
		x = (_mat.l_32 - _mat.l_23) / (w * 4.0f);
		y = (_mat.l_13 - _mat.l_31) / (w * 4.0f);
		z = (_mat.l_21 - _mat.l_12) / (w * 4.0f);
		return;
	}

	z = std::sqrtf(-_mat.l_11 - _mat.l_22 + _mat.l_33 + 1.0f) / 2.0f;

	if (z != 0)
	{
		x = (_mat.l_13 + _mat.l_31) / (z * 4.0f);
		y = (_mat.l_32 + _mat.l_23) / (z * 4.0f);
		return;
	}

	y = std::sqrtf(-_mat.l_11 + _mat.l_22 - _mat.l_33 + 1.0f) / 2.0f;

	if (y != 0)
	{
		x = (_mat.l_13 + _mat.l_31) / (z * 4.0f);
		return;
	}

	x = std::sqrtf(_mat.l_11 - _mat.l_22 - _mat.l_33 + 1.0f) / 2.0f;

	return;

}

//à»â∫ÇÃURLÇéQè∆//
//https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf#%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%8B%E3%82%89%E5%9B%9E%E8%BB%A2%E8%A1%8C%E5%88%97
//
void ChQua::SetRotationRMatrix(const ChRMatrix& _mat)
{

	w = std::sqrtf(_mat.r_11 + _mat.r_22 + _mat.r_33 + 1.0f) / 2.0f;

	if (w != 0)
	{
		x = (_mat.r_32 - _mat.r_23) / (w * 4.0f);
		y = (_mat.r_13 - _mat.r_31) / (w * 4.0f);
		z = (_mat.r_21 - _mat.r_12) / (w * 4.0f);
		return;
	}

	z = std::sqrtf(-_mat.r_11 - _mat.r_22 + _mat.r_33 + 1.0f) / 2.0f;

	if (z != 0)
	{
		x = (_mat.r_13 + _mat.r_31) / (z * 4.0f);
		y = (_mat.r_32 + _mat.r_23) / (z * 4.0f);
		return;
	}

	y = std::sqrtf(-_mat.r_11 + _mat.r_22 - _mat.r_33 + 1.0f) / 2.0f;

	if (y != 0)
	{
		x = (_mat.r_13 + _mat.r_31) / (z * 4.0f);
		return;
	}

	x = std::sqrtf(_mat.r_11 - _mat.r_22 - _mat.r_33 + 1.0f) / 2.0f;

	return;
}

void ChQua::SetRotation(const ChVec3& _axis, const float _angle)
{
	ChVec3 tmp = _axis;

	tmp.Normalize();

	float tmpAngle = std::fmod(_angle * 0.5f, ChMath::PI * 2.0f);

	w = std::cosf(tmpAngle);

	x = FLOAT_ZERO_TEST(tmp.x, 0.00001f) ? 0.0f : tmp.x * std::sinf(tmpAngle);
	y = FLOAT_ZERO_TEST(tmp.y, 0.00001f) ? 0.0f : tmp.y * std::sinf(tmpAngle);
	z = FLOAT_ZERO_TEST(tmp.z, 0.00001f) ? 0.0f : tmp.z * std::sinf(tmpAngle);
}

ChVec3 ChQua::GetAxis()const
{
	ChVec3 res = ChVec3(x, y, z);

	if (res.Len() <= 0.00001f)return ChVec3(0.0f, 1.0f, 0.0f);

	float sin = std::sinf(GetRadian() / 2.0f);

	if (sin <= 0.00001f)return ChVec3(0.0f, 1.0f, 0.0f);

	return res / sin;

}

ChEularXYZ ChQua::GetEulerRotationXYZ(const unsigned long _digit)const
{
	ChEularXYZ res;

	res.y = std::asinf((2.0f * x * z + 2.0f * y * w));

	float yz = 2.0f * y * z;
	float xw = 2.0f * x * w;

	float ww = 2.0f * w * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.y), 0.000001f))
	{
		res.x = std::atanf((yz + xw) / (ww + 2.0f * y * y - 1.0f));
		res.z = 0.0f;
	}
	else
	{
		res.x = std::atanf(-(yz - xw) / (ww + 2.0f * z * z - 1.0f));
		res.z = std::atanf(-(2.0f * x * y - 2.0f * z * w) / (ww + 2.0f * x * x - 1.0f));
	}

	return res;
}

ChEularXZY ChQua::GetEulerRotationXZY(const unsigned long _digit)const
{
	ChEularXZY res;

	res.z = std::asinf(-(2.0f * x * y - 2.0f * z * w));

	float ww = 2.0f * w * w;

	float xw = 2.0f * x * w;
	float yz = 2.0f * y * z;

	if (FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f))
	{
		res.x = std::atanf(-(yz - xw) / (ww + 2.0f * z * z - 1.0f));
		res.y = 0.0f;
	}
	else
	{
		res.x = std::atanf((yz + xw) / (ww + 2.0f * y * y - 1.0f));
		res.y = std::atanf((2.0f * x * z + 2.0f * y * w) / (ww + 2.0f * x * x - 1.0f));
	}

	return res;
}

ChEularYXZ ChQua::GetEulerRotationYXZ(const unsigned long _digit)const
{
	ChEularYXZ res;

	res.x = std::asinf(-(2.0f * y * z - 2.0f * x * w));

	float ww = 2.0f * w * w;

	float xz = 2.0f * x * z;
	float yw = 2.0f * y * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f))
	{
		res.y = std::atanf(-(xz - yw) / (ww + 2.0f * x * x - 1.0f));
		res.z = 0.0f;
	}
	else
	{
		res.y = std::atanf((xz + yw) / (ww + 2.0f * z * z - 1.0f));
		res.z = std::atanf((2.0f * x * y + 2.0f * z * w) / (ww + 2.0f * y * y - 1.0f));
	}

	return res;
}

ChEularYZX ChQua::GetEulerRotationYZX(const unsigned long _digit)const
{
	ChEularYZX res;

	res.z = std::asinf((2.0f * x * y + 2.0f * z * w));

	float ww = 2.0f * w * w;

	float xz = 2.0f * x * z;
	float yw = 2.0f * y * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f))
	{
		res.x = 0.0f;
		res.y = std::atanf((xz + yw) / (ww + 2.0f * z * z - 1.0f));
	}
	else
	{
		res.x = std::atanf(-(2.0f * y * z - 2.0f * x * w) / (ww + 2.0f * y * y - 1.0f));
		res.y = std::atanf(-(xz - yw) / (ww + 2.0f * x * x - 1.0f));
	}

	return res;
}

ChEularZXY ChQua::GetEulerRotationZXY(const unsigned long _digit)const
{
	ChEularZXY res;

	res.x = std::asinf((2.0f * y * z + 2.0f * x * w));

	float ww = 2.0f * w * w;

	float xz = 2.0f * x * z;
	float yw = 2.0f * y * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f))
	{
		res.y = 0.0f;
		res.z = std::atanf((xz + yw) / (ww + 2.0f * x * x - 1.0f));
	}
	else
	{
		res.y = std::atanf(-(2.0f * x * y - 2.0f * z * w) / (ww + 2.0f * y * y - 1.0f));
		res.z = std::atanf(-(xz - yw) / (ww + 2.0f * z * z - 1.0f));
	}

	return res;
}

ChEularZYX ChQua::GetEulerRotationZYX(const unsigned long _digit)const
{
	ChEularZYX res;

	res.y = std::asinf(-(2.0f * x * z - 2.0f * y * w));

	float ww = 2.0f * w * w;

	float xy = 2.0f * x * y;
	float zw = 2.0f * z * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.y), 0.000001f))
	{
		res.x = 0.0f;
		res.z = std::atanf(-(xy - zw) / (ww + 2.0f * y * y - 1.0f));
	}
	else
	{
		res.x = std::atanf((2.0f * y * z + 2.0f * x * w) / (ww + 2.0f * z * z - 1.0f));
		res.z = std::atanf((xy + zw) / (ww + 2.0f * x * x - 1.0f));
	}

	return res;
}

float ChQua::GetRadian()const
{
	return std::acosf(w) * 2.0f;
}

float ChQua::GetCos()const
{
	return std::cosf(GetRadian());
}

float ChQua::GetSin()const
{
	return std::sinf(GetRadian());
}



void ChLMatrix::SetRotationXAxis(const float _x)
{
	Identity();

	float x = -std::fmod(_x, ChMath::PI * 2.0f);

	l_22 = std::cos(x);
	l_23 = std::sin(x);

	l_32 = -std::sin(x);
	l_33 = std::cos(x);
}

void ChLMatrix::SetRotationYAxis(const float _y)
{
	Identity();

	float  y = -std::fmod(_y, ChMath::PI * 2.0f);

	l_11 = std::cos(y);
	l_13 = -std::sin(y);

	l_31 = std::sin(y);
	l_33 = std::cos(y);
}

void ChLMatrix::SetRotationZAxis(const float _z)
{
	Identity();

	float z = -std::fmod(_z, ChMath::PI * 2.0f);

	l_11 = std::cos(z);
	l_12 = std::sin(z);

	l_21 = -std::sin(z);
	l_22 = std::cos(z);
}

ChEularXYZ ChLMatrix::GetEulerRotationXYZ(const unsigned long _digit)const
{
	ChEularXYZ res;
	ChMath::BaseMatrix3x3<float> outM;

	outM.m.Set(m);
	outM.m[0].Normalize(_digit);
	outM.m[1].Normalize(_digit);
	outM.m[2].Normalize(_digit);

	res.y = std::asinf(-outM.m[0][2]);

	bool zeroFlg = FLOAT_ZERO_TEST(std::cosf(res.y), 0.000001f);

	res.x = std::atanf(zeroFlg ? -outM.m[2][1] / outM.m[1][1] : outM.m[1][2] / outM.m[2][2]);
	res.z = zeroFlg ? 0.0f : (std::atanf(outM.m[0][1] / outM.m[0][0]));

	return res;
}

ChEularXZY ChLMatrix::GetEulerRotationXZY(const unsigned long _digit)const
{
	ChEularXZY res;
	ChMath::BaseMatrix3x3<float> outM;

	outM.m.Set(m);
	outM.m[0].Normalize(_digit);
	outM.m[1].Normalize(_digit);
	outM.m[2].Normalize(_digit);

	res.z = std::asinf(outM.m[0][1]);

	bool zeroFlg = FLOAT_ZERO_TEST(std::cosf(res.z), 0.000001f);

	res.x = std::atanf(zeroFlg ? outM.m[1][2] / outM.m[2][2] : -outM.m[0][2] / outM.m[2][2]);
	res.y = zeroFlg ? 0.0f : (std::atanf(-outM.m[0][2] / outM.m[0][0]));

	return res;
}

ChEularYXZ ChLMatrix::GetEulerRotationYXZ(const unsigned long _digit)const
{
	ChEularYXZ res;

	ChMath::BaseMatrix3x3<float> outM;

	outM.m.Set(m);
	outM.m[0].Normalize(_digit);
	outM.m[1].Normalize(_digit);
	outM.m[2].Normalize(_digit);

	res.x = std::asinf(outM.m[1][2]);

	bool zeroFlg = FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f);

	res.y = std::atanf(zeroFlg ? outM.m[2][0] / outM.m[0][0] : -outM.m[0][2] / outM.m[2][2]);
	res.z = zeroFlg ? 0.0f : (std::atanf(-outM.m[1][0] / outM.m[1][1]));

	return res;
}

ChEularYZX ChLMatrix::GetEulerRotationYZX(const unsigned long _digit)const
{
	ChEularYZX res;

	ChMath::BaseMatrix3x3<float> outM;

	outM.m.Set(m);
	outM.m[0].Normalize(_digit);
	outM.m[1].Normalize(_digit);
	outM.m[2].Normalize(_digit);

	res.z = std::asinf(-outM.m[1][0]);

	bool zeroFlg = FLOAT_ZERO_TEST(std::cosf(res.z), 0.000001f);

	res.x = zeroFlg ? 0.0f : (std::atanf(outM.m[1][2] / outM.m[1][1]));
	res.y = std::atanf(zeroFlg ? -outM.m[0][2] / outM.m[2][2] : outM.m[2][0] / outM.m[0][0]);

	return res;
}

ChEularZXY ChLMatrix::GetEulerRotationZXY(const unsigned long _digit)const
{
	ChEularZXY res;
	ChMath::BaseMatrix3x3<float> outM;

	outM.m.Set(m);
	outM.m[0].Normalize(_digit);
	outM.m[1].Normalize(_digit);
	outM.m[2].Normalize(_digit);

	res.x = std::asinf(-outM.m[2][1]);

	bool zeroFlg = FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f);

	res.y = zeroFlg ? 0.0f : (std::atanf(outM.m[2][0] / outM.m[2][2]));
	res.z = std::atanf(zeroFlg ? -outM.m[1][0] / outM.m[0][0] : outM.m[0][1] / outM.m[1][1]);

	return res;
}

ChEularZYX ChLMatrix::GetEulerRotationZYX(const unsigned long _digit)const
{
	ChEularZYX res;
	ChMath::BaseMatrix3x3<float> outM;

	outM.m.Set(m);
	outM.m[0].Normalize(_digit);
	outM.m[1].Normalize(_digit);
	outM.m[2].Normalize(_digit);

	res.y = std::asinf(outM.m[2][0]);

	bool zeroFlg = FLOAT_ZERO_TEST(std::cosf(res.y), 0.000001f);

	res.x = zeroFlg ? 0.0f : (std::atanf(outM.m[2][1] / outM.m[2][2]));
	res.z = std::atanf(zeroFlg ? -outM.m[1][0] / outM.m[0][0] : outM.m[0][1] / outM.m[1][1]);

	return res;
}



void ChRMatrix::SetRotationXAxis(const float _x)
{
	float x = -std::fmod(_x, ChMath::PI * 2.0f);

	r_22 = std::cos(x);
	r_23 = std::sin(x);

	r_32 = -std::sin(x);
	r_33 = std::cos(x);
}

void ChRMatrix::SetRotationYAxis(const float _y)
{
	float  y = -std::fmod(_y, ChMath::PI * 2.0f);

	r_11 = std::cos(y);
	r_13 = -std::sin(y);

	r_31 = std::sin(y);
	r_33 = std::cos(y);
}

void ChRMatrix::SetRotationZAxis(const float _z)
{
	float z = -std::fmod(_z, ChMath::PI * 2.0f);

	r_11 = std::cos(z);
	r_12 = std::sin(z);

	r_21 = -std::sin(z);
	r_22 = std::cos(z);
}
