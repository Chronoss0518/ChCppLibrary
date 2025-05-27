
#include"ChMath3D.h"

#ifndef CH_MATH3D_METHOD_VECTOR2_FROM
#define CH_MATH3D_METHOD_VECTOR2_FROM(_FunctionName,_X,_Y)\
ChVector2 ChVector2::_FunctionName(const float _##_X, const float _##_Y){\
	ChVector2 res;\
	res._X = _##_X;\
	res._Y = _##_Y;\
	return res;\
}
#endif

#ifndef CH_MATH3D_METHOD_VECTOR3_FROM
#define CH_MATH3D_METHOD_VECTOR3_FROM(_FunctionName,_X,_Y,_Z)\
ChVector3 ChVector3::_FunctionName(const float _##_X, const float _##_Y, const float _##_Z){\
	ChVector3 res;\
	res._X = _##_X;\
	res._Y = _##_Y;\
	res._Z = _##_Z;\
	return res;\
}
#endif

#ifndef CH_MATH3D_METHOD_VECTOR4_FROM
#define CH_MATH3D_METHOD_VECTOR4_FROM(_FunctionName,_X,_Y,_Z,_W)\
ChVector4 ChVector4::_FunctionName(const float _##_X, const float _##_Y, const float _##_Z, const float _##_W){\
	ChVector4 res;\
	res._X = _##_X;\
	res._Y = _##_Y;\
	res._Z = _##_Z;\
	res._W = _##_W;\
	return res;\
}
#endif

#ifndef CH_MATH3D_METHOD_VECTOR_CAST
#define CH_MATH3D_METHOD_VECTOR_CAST(_BaseClass,_OutClass)\
_BaseClass::operator const _OutClass() const {\
	_OutClass res;\
	res.val.Set(val);\
	return res;\
}
#endif

#ifndef CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION
#define CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(_MatrixType,_AxisOrder,_ZeroTestAxis,_ZeroTestAxisFunction,_Axiz1,_ZeroAxiz1Function,_NotZeroAxiz1Function,_Axiz2,_ZeroAxiz2Function,_NotZeroAxiz2Function)\
ChMath::ChEular##_AxisOrder<float> _MatrixType::GetEulerRotation##_AxisOrder(const unsigned long _digit)const{\
	ChMath::ChEular##_AxisOrder<float> res; \
	ChMath::BaseMatrix3x3<float> outM;\
	outM.m.Set(m);\
	outM.m[0].Normalize(_digit);\
	outM.m[1].Normalize(_digit);\
	outM.m[2].Normalize(_digit);\
	res._ZeroTestAxis = _ZeroTestAxisFunction;\
	if(CH_FLOAT_TEST(res._ZeroTestAxis,Ch_FLOAT_TEST_VALUE)){\
	res._Axiz1 = _ZeroAxiz1Function; \
	res._Axiz2 = _ZeroAxiz2Function; \
	}else{\
		res._Axiz1 = _NotZeroAxiz1Function;\
		res._Axiz2 = _NotZeroAxiz2Function;\
	}\
	return res;}
#endif



CH_MATH3D_METHOD_VECTOR2_FROM(FromPosition, x, y);

CH_MATH3D_METHOD_VECTOR2_FROM(FromSize, w, h);

CH_MATH3D_METHOD_VECTOR2_FROM(FromTime, start, end);

CH_MATH3D_METHOD_VECTOR2_FROM(FromHighLow, high, low);

CH_MATH3D_METHOD_VECTOR3_FROM(FromPosition, x, y, z);

CH_MATH3D_METHOD_VECTOR3_FROM(FromColor, r, g, b);

CH_MATH3D_METHOD_VECTOR4_FROM(FromPosition, x, y, z, w);

CH_MATH3D_METHOD_VECTOR4_FROM(FromColor, r, g, b, a);

CH_MATH3D_METHOD_VECTOR4_FROM(FromRect, left, top, right, bottom);


CH_MATH3D_METHOD_VECTOR_CAST(ChVector2, ChVector4);
CH_MATH3D_METHOD_VECTOR_CAST(ChVector2, ChVector3);

CH_MATH3D_METHOD_VECTOR_CAST(ChVector3, ChVector4);
CH_MATH3D_METHOD_VECTOR_CAST(ChVector3, ChVector2);

CH_MATH3D_METHOD_VECTOR_CAST(ChVector4, ChVector3);
CH_MATH3D_METHOD_VECTOR_CAST(ChVector4, ChVector2);

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion Method//
///////////////////////////////////////////////////////////////////////////////////

//à»â∫ÇÃURLÇéQè∆//
//https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf#%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%8B%E3%82%89%E5%9B%9E%E8%BB%A2%E8%A1%8C%E5%88%97
//
void ChQuaternion::SetRotationLMatrix(const ChLMatrix& _mat)
{
	w = ChMath::SqrtEx(_mat.l_11 + _mat.l_22 + _mat.l_33 + 1.0f) / 2.0f;
	if (w != 0)
	{
		x = (_mat.l_32 - _mat.l_23) / (w * 4.0f);
		y = (_mat.l_13 - _mat.l_31) / (w * 4.0f);
		z = (_mat.l_21 - _mat.l_12) / (w * 4.0f);
		return;
	}

	z = ChMath::SqrtEx(-_mat.l_11 - _mat.l_22 + _mat.l_33 + 1.0f) / 2.0f;
	if (z != 0)
	{
		x = (_mat.l_13 + _mat.l_31) / (z * 4.0f);
		y = (_mat.l_32 + _mat.l_23) / (z * 4.0f);
		return;
	}

	y = ChMath::SqrtEx(-_mat.l_11 + _mat.l_22 - _mat.l_33 + 1.0f) / 2.0f;
	if (y != 0)
	{
		x = (_mat.l_13 + _mat.l_31) / (z * 4.0f);
		return;
	}

	x = ChMath::SqrtEx(_mat.l_11 - _mat.l_22 - _mat.l_33 + 1.0f) / 2.0f;

	return;

}

//à»â∫ÇÃURLÇéQè∆//
//https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf#%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%8B%E3%82%89%E5%9B%9E%E8%BB%A2%E8%A1%8C%E5%88%97
//
void ChQuaternion::SetRotationRMatrix(const ChRMatrix& _mat)
{

	w = ChMath::SqrtEx(_mat.r_11 + _mat.r_22 + _mat.r_33 + 1.0f) / 2.0f;
	if (w != 0)
	{
		x = (_mat.r_32 - _mat.r_23) / (w * 4.0f);
		y = (_mat.r_13 - _mat.r_31) / (w * 4.0f);
		z = (_mat.r_21 - _mat.r_12) / (w * 4.0f);
		return;
	}

	z = ChMath::SqrtEx(-_mat.r_11 - _mat.r_22 + _mat.r_33 + 1.0f) / 2.0f;
	if (z != 0)
	{
		x = (_mat.r_13 + _mat.r_31) / (z * 4.0f);
		y = (_mat.r_32 + _mat.r_23) / (z * 4.0f);
		return;
	}

	y = ChMath::SqrtEx(-_mat.r_11 + _mat.r_22 - _mat.r_33 + 1.0f) / 2.0f;
	if (y != 0)
	{
		x = (_mat.r_13 + _mat.r_31) / (z * 4.0f);
		return;
	}

	x = ChMath::SqrtEx(_mat.r_11 - _mat.r_22 - _mat.r_33 + 1.0f) / 2.0f;

	return;
}

void ChQuaternion::SetRotationXAxis(const float _x)
{
	SetRotation(ChVector3(1.0f, 0.0f, 0.0f), _x);
}

void ChQuaternion::SetRotationYAxis(const float _y)
{
	SetRotation(ChVector3(0.0f, 1.0f, 0.0f), _y);
}

void ChQuaternion::SetRotationZAxis(const float _z)
{
	SetRotation(ChVector3(0.0f, 0.0f, 1.0f), _z);
}

void ChQuaternion::SetRotation(const ChVector3& _axis, const float _angle)
{
	ChVector3 tmp = _axis;

	tmp.Normalize();

	float tmpAngle = ChMath::GetFMod(_angle * 0.5f, ChMath::PI * 2.0f);

	w = ChMath::GetCos(tmpAngle);

	x = CH_FLOAT_TEST(tmp.x, Ch_FLOAT_TEST_VALUE) ? 0.0f : tmp.x * ChMath::GetSin(tmpAngle);
	y = CH_FLOAT_TEST(tmp.y, Ch_FLOAT_TEST_VALUE) ? 0.0f : tmp.y * ChMath::GetSin(tmpAngle);
	z = CH_FLOAT_TEST(tmp.z, Ch_FLOAT_TEST_VALUE) ? 0.0f : tmp.z * ChMath::GetSin(tmpAngle);
}

void ChQuaternion::SetRotation(const ChVector3& _from, const ChVector3& _to)
{
	ChVector3 from = _from, to = _to;
	from.Normalize();
	to.Normalize();

	auto&& axis = ChVector3::GetCross(from, to);

	if (!axis.Normalize())
	{
		Identity();
		return;
	}

	auto&& cos = ChVector3::GetRadian(from, to);

	SetRotation(axis, cos);
}
ChLMatrix ChQuaternion::GetRotationLMatrix(const unsigned long _digit)const
{
	ChLMat mat;
	mat.SetRotation(*this, _digit);
	return mat;
}

ChRMatrix ChQuaternion::GetRotationRMatrix(const unsigned long _digit)const
{
	ChRMat mat;
	mat.SetRotation(*this, _digit);
	return mat;
}

ChVector3 ChQuaternion::GetAxis()const
{
	ChVector3 res = ChVector3(x, y, z);

	if (res.GetLen() <= 0.00001f)return ChVector3(0.0f, 1.0f, 0.0f);

	float sin = ChMath::GetSin(GetRadian() / 2.0f);

	if (sin <= 0.00001f)return ChVector3(0.0f, 1.0f, 0.0f);

	return res / sin;

}

float ChQuaternion::GetRadian()const
{
	return ChMath::GetACos(w) * 2.0f;
}

float ChQuaternion::GetCos()const
{
	return ChMath::GetCos(GetRadian());
}

float ChQuaternion::GetSin()const
{
	return ChMath::GetSin(GetRadian());
}

void ChQuaternion::AddRotationXAxis(float _x)
{
	ChQuaternion qua;
	qua.SetRotationXAxis(_x);

	*this = qua * *this;
}

void ChQuaternion::AddRotationYAxis(float _y)
{
	ChQuaternion qua;
	qua.SetRotationYAxis(_y);

	*this = qua * *this;
}

void ChQuaternion::AddRotationZAxis(float _z)
{
	ChQuaternion qua;
	qua.SetRotationZAxis(_z);
	*this = qua * *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChLMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetPosition(const ChVector3& _vec)
{
	SetPosition(_vec.x, _vec.y, _vec.z);
}

void ChLMatrix::SetPosition(const float _x, const float _y, const float _z)
{
	l_41 = _x;
	l_42 = _y;
	l_43 = _z;
}

//à»â∫ÇÃURLÇéQè∆//
//https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf#%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%8B%E3%82%89%E5%9B%9E%E8%BB%A2%E8%A1%8C%E5%88%97
//
void ChLMatrix::SetRotation(const ChQuaternion& _qua, const unsigned long _digit)
{
	float squaredW = 2.0f * _qua.w * _qua.w;

	ChVector3 scl = GetScalling(_digit);

	for (unsigned char i = 0; i < 3; i++)
	{
		m[i][i] = (squaredW + (2.0f * _qua.val[i] * _qua.val[i]) - 1.0f) * scl.val[i];
	}

	m[0][1] = 2.0f * ((_qua.x * _qua.y) + (_qua.z * _qua.w)) * scl.x;
	m[0][2] = 2.0f * ((_qua.x * _qua.z) - (_qua.y * _qua.w)) * scl.x;

	m[1][0] = 2.0f * ((_qua.y * _qua.x) - (_qua.z * _qua.w)) * scl.y;
	m[1][2] = 2.0f * ((_qua.y * _qua.z) + (_qua.x * _qua.w)) * scl.y;

	m[2][0] = 2.0f * ((_qua.z * _qua.x) + (_qua.y * _qua.w)) * scl.z;
	m[2][1] = 2.0f * ((_qua.z * _qua.y) - (_qua.x * _qua.w)) * scl.z;
}

void ChLMatrix::SetRotationYPR(const float _x, const float _y, const float _z, const unsigned long _digit)
{
	ChVector3 scale = GetScalling();
	ChVector3 pos = GetPosition();

	SetRotationYAxis(_y);

	ChLMat tmp;

	tmp.SetRotationXAxis(_x);

	*this = tmp * *this;

	tmp.SetRotationZAxis(_z);

	*this = tmp * *this;

	SetPosition(pos);
	SetScalling(scale);
}

void ChLMatrix::SetRotationYPR(const ChVector3& _vec, const unsigned long _digit)
{
	SetRotationYPR(_vec.x, _vec.y, _vec.z, _digit);
}

void ChLMatrix::SetRotationXAxis(const float _x)
{
	Identity();

	float x = -ChMath::GetFMod(_x, ChMath::PI * 2.0f);

	l_22 = ChMath::GetCos(x);
	l_23 = ChMath::GetSin(x);

	l_32 = -ChMath::GetSin(x);
	l_33 = ChMath::GetCos(x);
}

void ChLMatrix::SetRotationYAxis(const float _y)
{
	Identity();

	float  y = -ChMath::GetFMod(_y, ChMath::PI * 2.0f);

	l_11 = ChMath::GetCos(y);
	l_13 = -ChMath::GetSin(y);

	l_31 = ChMath::GetSin(y);
	l_33 = ChMath::GetCos(y);
}

void ChLMatrix::SetRotationZAxis(const float _z)
{
	Identity();

	float z = -ChMath::GetFMod(_z, ChMath::PI * 2.0f);

	l_11 = ChMath::GetCos(z);
	l_12 = ChMath::GetSin(z);

	l_21 = -ChMath::GetSin(z);
	l_22 = ChMath::GetCos(z);
}

void ChLMatrix::SetScalling(
	const ChVector3& _vec,
	const unsigned long _digit)
{
	SetScalling(_vec.x, _vec.y, _vec.z, _digit);
}

void ChLMatrix::SetScalling(
	const float _x,
	const float _y,
	const float _z,
	const unsigned long _digit)
{
	m[0].Normalize(_digit);
	m[0].Mul(_x);

	m[1].Normalize(_digit);
	m[1].Mul(_y);

	m[2].Normalize(_digit);
	m[2].Mul(_z);
}

ChVector3 ChLMatrix::GetPosition()const
{
	return ChVector3(l_41, l_42, l_43);
}

ChQuaternion ChLMatrix::GetRotation(const unsigned long _digit)const
{
	ChQuaternion res;
	res.SetRotationLMatrix(*this);
	return res;
}

CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(
	ChLMatrix,
	XYZ,
	y,
	ChMath::GetSin(-outM.m[0][2]),
	x,
	ChMath::GetATan(-outM.m[2][1] / outM.m[1][1]),
	ChMath::GetATan(outM.m[1][2] / outM.m[2][2]),
	z,
	0.0f,
	ChMath::GetATan(outM.m[0][1] / outM.m[0][0]));

CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(
	ChLMatrix,
	XZY,
	z,
	ChMath::GetSin(outM.m[0][1]),
	x,
	ChMath::GetATan(outM.m[1][2] / outM.m[2][2]),
	ChMath::GetATan(-outM.m[0][2] / outM.m[2][2]),
	y,
	0.0f,
	ChMath::GetATan(-outM.m[0][2] / outM.m[0][0]));

CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(
	ChLMatrix,
	YXZ,
	x,
	ChMath::GetSin(outM.m[1][2]),
	y,
	ChMath::GetATan(outM.m[2][0] / outM.m[0][0]),
	ChMath::GetATan(-outM.m[0][2] / outM.m[2][2]),
	z,
	0.0f,
	ChMath::GetATan(-outM.m[1][0] / outM.m[1][1]));

CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(
	ChLMatrix,
	YZX,
	z,
	ChMath::GetSin(-outM.m[1][0]),
	x,
	0.0f,
	ChMath::GetATan(outM.m[1][2] / outM.m[1][1]),
	y,
	ChMath::GetATan(-outM.m[0][2] / outM.m[2][2]),
	ChMath::GetATan(outM.m[2][0] / outM.m[0][0]));

CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(
	ChLMatrix,
	ZXY,
	x,
	ChMath::GetSin(-outM.m[2][1]),
	y,
	0.0f,
	ChMath::GetATan(outM.m[2][0] / outM.m[2][2]),
	z,
	ChMath::GetATan(-outM.m[1][0] / outM.m[0][0]),
	ChMath::GetATan(outM.m[0][1] / outM.m[1][1]));

CH_MATH_METHOD_MATRIX_GET_EULER_ROTATION(
	ChLMatrix,
	ZYX,
	y,
	ChMath::GetSin(outM.m[2][0]),
	x,
	0.0f,
	ChMath::GetATan(outM.m[2][1] / outM.m[2][2]),
	z,
	ChMath::GetATan(-outM.m[1][0] / outM.m[0][0]),
	ChMath::GetATan(outM.m[0][1] / outM.m[1][1]));

ChVector3 ChLMatrix::GetScalling(const unsigned long _digit)const
{
	return ChVector3(m[0].GetLen(_digit), m[1].GetLen(_digit), m[2].GetLen(_digit));
}

ChVector4 ChLMatrix::Transform(const ChVector4& _base)const
{
	ChVector4 res;

	res = _base;
	res.w = 1.0f;
	res.val = m.HorizontalMul(res.val);

	return res;
}

ChVector4 ChLMatrix::TransformCoord(const ChVector4& _base)const
{
	ChLMatrix tmp = *this;

	tmp.l_41 = 0.0f;
	tmp.l_42 = 0.0f;
	tmp.l_43 = 0.0f;

	return tmp.Transform(_base);
}

///////////////////////////////////////////////////////////////////////////////////
//ChRMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetPosition(const ChVector3& _vec)
{
	SetPosition(_vec.x, _vec.y, _vec.z);
}

void ChRMatrix::SetPosition(const float _x, const float _y, const float _z)
{
	r_41 = _x;
	r_42 = _y;
	r_43 = _z;
}

void ChRMatrix::SetRotation(const ChQuaternion& _qua, const unsigned long _digit)
{

}

void ChRMatrix::SetRotationXAxis(const float _x)
{
	float x = -ChMath::GetFMod(_x, ChMath::PI * 2.0f);

	r_22 = ChMath::GetCos(x);
	r_23 = ChMath::GetSin(x);

	r_32 = -ChMath::GetSin(x);
	r_33 = ChMath::GetCos(x);
}

void ChRMatrix::SetRotationYAxis(const float _y)
{
	float  y = -ChMath::GetFMod(_y, ChMath::PI * 2.0f);

	r_11 = ChMath::GetCos(y);
	r_13 = -ChMath::GetSin(y);

	r_31 = ChMath::GetSin(y);
	r_33 = ChMath::GetCos(y);
}

void ChRMatrix::SetRotationZAxis(const float _z)
{
	float z = -ChMath::GetFMod(_z, ChMath::PI * 2.0f);

	r_11 = ChMath::GetCos(z);
	r_12 = ChMath::GetSin(z);

	r_21 = -ChMath::GetSin(z);
	r_22 = ChMath::GetCos(z);
}

void ChRMatrix::SetScalling(
	const ChVector3& _vec,
	const unsigned long _digit)
{
	SetScalling(_vec.x, _vec.y, _vec.z, _digit);
}

void ChRMatrix::SetScalling(
	const float _x,
	const float _y,
	const float _z,
	const unsigned long _digit)
{
	ChVector4 vec[3];

	for (unsigned long i = 0; i < m.GetRow() - 1; i++)
	{
		for (unsigned long j = 0; j < m.GetColumn() - 1; j++)
		{
			vec[i].val[j] = m[j][i];
		}
	}

	vec[0].Normalize(_digit);
	vec[0].val.Mul(_x);

	vec[1].Normalize(_digit);
	vec[1].val.Mul(_y);

	vec[2].Normalize(_digit);
	vec[2].val.Mul(_z);

	for (unsigned long i = 0; i < m.GetRow() - 1; i++)
	{
		for (unsigned long j = 0; j < m.GetColumn() - 1; j++)
		{
			m[j][i] = vec[i].val[j];
		}
	}
}

ChVector3 ChRMatrix::GetPosition()const
{
	return ChVector3(r_41, r_42, r_43);
}

ChVector3 ChRMatrix::GetScalling(const unsigned long _digit)const
{
	ChVector4 vec[3];

	for (unsigned long i = 0; i < m.GetRow() - 1; i++)
	{
		for (unsigned long j = 0; j < m.GetColumn() - 1; j++)
		{
			vec[i].val[j] = m[j][i];
		}
	}

	return ChVector3(vec[0].val.GetLen(_digit), vec[1].val.GetLen(_digit), vec[2].val.GetLen(_digit));
}

ChVector4 ChRMatrix::Transform(const ChVector4& _Base)const
{
	ChVector4 out;

	out = _Base;
	out.w = 1.0f;
	out.val = m.VerticalMul(out.val);

	return out;
}

ChVector4 ChRMatrix::TransformCoord(const ChVector4& _Base)const
{
	ChRMatrix tmp = *this;

	tmp.r_41 = 0.0f;
	tmp.r_42 = 0.0f;
	tmp.r_43 = 0.0f;

	return tmp.Transform(_Base);
}

///////////////////////////////////////////////////////////////////////////////////
//Math Function//
///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChMath::GetFaceNormal(
	const ChVector3& _Pos1
	, const ChVector3& _Pos2
	, const ChVector3& _Pos3,
	const unsigned long _digit)
{

	ChVector3 tmpVec, tmpVec2;

	tmpVec = _Pos1 - _Pos2;
	tmpVec2 = _Pos2 - _Pos3;

	tmpVec.SetCross(tmpVec, tmpVec2, _digit);

	tmpVec.Normalize(_digit);

	return tmpVec;
}
