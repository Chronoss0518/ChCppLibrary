#include"../BaseIncluder/ChBase.h"

///////////////////////////////////////////////////////////////////////////////////
//ChVector2 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVector2::operator=(const ChVector2& _vec)
{
	if (this == &_vec)return *this;
	val.Set(_vec.val);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator*= (const float& _num)
{
	val.Mul(_num);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator * (const float& _num)const
{

	ChVector2 tmpVec = *this;

	tmpVec *= _num;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator/= (const float& _num)
{
	val.Div(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator / (const float& _num)const
{

	ChVector2 tmpVec = *this;

	tmpVec /= _num;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator= (const float& _num)
{

	val.Set(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator += (const ChVector2& _vec)
{
	val.Add(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator + (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;

	tmpVec += _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator -= (const ChVector2& _vec)
{
	val.Sub(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator - (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;

	tmpVec -= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator *= (const ChVector2& _vec)
{
	val.Mul(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator * (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;

	tmpVec *= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator /= (const ChVector2& _vec)
{
	val.Div(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator / (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;

	tmpVec /= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const ChVector4() const
{
	ChVec4 out;

	out.val = static_cast<ChMath::VectorBase<float, 4>>(val);

	return out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const ChVector3() const
{

	ChVec3 out;

	out.val = static_cast<ChMath::VectorBase<float, 3>>(val);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec2::Serialize(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	return val.Serialize(_cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Deserialize(
	const std::string& _str
	, const size_t _fPos
	, const std::string& _cutChar
	, const std::string& _endChar
	, const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::GetCross(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	ChVector2 tmpVec;

	tmpVec.val.Cross(_vec1.val, _vec2.val, _digit);

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetCos(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetCos(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetRadian(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetRadian(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetDot(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetDot(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

//???????s??(Now??0?`1)
ChVector2 ChVec2::GetCorrection(
	const ChVector2& _start
	, const ChVector2& _end
	, const float _Now)
{
	ChVector2 tmpVec;

	tmpVec.val.Correction(_start.val, _end.val, _Now);

	return tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetLen(
	const ChVector2& _vec1
	, const ChVector2& _vec2,
	const unsigned long _digit)
{

	ChVec2 tmpVec = _vec1 - _vec2;

	return  tmpVec.val.GetLen(_digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetElementsLen(
	const ChVector2& _vec1
	, const ChVector2& _vec2)
{

	ChVec2 tmpVec = _vec1 - _vec2;

	return  tmpVec.val.GetElementsLen();
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVec2::Normalize(const unsigned long _digit)
{
	return val.Normalize(_digit);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::ElementsNormalize()
{
	val.ElementsNormalize();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Cross(
	const ChVector2& _vec1,
	const ChVector2& _vec2,
	const unsigned long _digit)
{
	*this = GetCross(_vec1, _vec2, _digit);
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator*= (const float& _num)
{

	val.Mul(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator * (const float& _num)const
{

	ChVector3 tmpVec = *this;

	tmpVec *= _num;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator/= (const float& _num)
{
	val.Div(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator / (const float& _num)const
{

	ChVector3 tmpVec = *this;

	tmpVec /= _num;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator= (const float& _num)
{

	val.Set(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVector3::operator=(const ChVector3& _vec)
{
	val.Set(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator *= (const ChVector3& _vec)
{
	val.Mul(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator * (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;

	tmpVec *= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator /= (const ChVector3& _vec)
{
	val.Div(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator / (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;

	tmpVec /= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator -= (const ChVector3& _vec)
{
	val.Sub(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator - (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;

	tmpVec -= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator += (const ChVector3& _vec)
{
	val.Add(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator + (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;

	tmpVec += _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const ChVector4() const
{
	ChVec4 out;

	out.val = static_cast<ChMath::VectorBase<float, 4>>(val);

	return out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const ChVector2() const
{

	ChVec2 out;

	out.val = static_cast<ChMath::VectorBase<float, 2>>(val);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec3::Serialize(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	return val.Serialize(_cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Deserialize(
	const std::string& _str
	, const size_t _fPos
	, const std::string& _cutChar
	, const std::string& _endChar
	, const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::GetCross(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	ChVector3 tmpVec;

	tmpVec.val.Cross(_vec1.val, _vec2.val, _digit);

	return tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetCos(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetCos(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetRadian(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetRadian(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetDot(
	const ChVector3& _vec1,
	const ChVector3& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetDot(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

//???????s??(Now??0?`1)
ChVector3 ChVec3::GetCorrection(const ChVector3& _start, const ChVector3& _end, const float _Now)
{
	ChVector3 tmpVec;

	tmpVec.val.Correction(_start.val, _end.val, _Now);

	return tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetLen(
	const ChVector3& _vec1
	, const ChVector3& _vec2,
	const unsigned long _digit)
{

	ChVec3 tmpVec = _vec1 - _vec2;

	return  tmpVec.val.GetLen(_digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetElementsLen(
	const ChVector3& _vec1
	, const ChVector3& _vec2)
{

	ChVec3 tmpVec = _vec1 - _vec2;

	return  tmpVec.val.GetElementsLen();
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVec3::Normalize(
	const unsigned long _digit)
{
	return val.Normalize(_digit);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::ElementsNormalize()
{
	val.ElementsNormalize();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Cross(
	const ChVector3& _vec1
	, const ChVector3& _vec2,
	const unsigned long _digit)
{
	*this = GetCross(_vec1, _vec2, _digit);
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector4 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator*= (const float& _num)
{

	val.Mul(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator * (const float& _num)const
{

	ChVector4 tmpVec = *this;

	tmpVec *= _num;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator/= (const float& _num)
{
	val.Div(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator / (const float& _num)const
{

	ChVector4 tmpVec = *this;

	tmpVec /= _num;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator= (const float& _num)
{

	val.Set(_num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVector4::operator=(const ChVector4& _vec)
{
	val.Set(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator *= (const ChVector4& _vec)
{
	val.Mul(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator * (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;

	tmpVec *= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator /= (const ChVector4& _vec)
{
	val.Div(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator / (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;

	tmpVec /= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator -= (const ChVector4& _vec)
{

	val.Sub(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator - (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;

	tmpVec -= _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator += (const ChVector4& _vec)
{

	val.Add(_vec.val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator + (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;

	tmpVec += _vec;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const ChVector3() const
{
	ChVec3 out;

	out.val = static_cast<ChMath::VectorBase<float, 3>>(val);

	return out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const ChVector2() const
{

	ChVec2 out;

	out.val = static_cast<ChMath::VectorBase<float, 2>>(val);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec4::Serialize(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	return val.Serialize(_cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec4::SerializeARGB(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	ChVec4 tmpVec;

	for (unsigned char i = 0; i < 4; i++)
	{
		tmpVec.val[(i + 1) % 4] = val[i];
	}

	return tmpVec.Serialize(_cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Deserialize(
	const std::string& _str
	, const size_t _fPos
	, const std::string& _cutChar
	, const std::string& _endChar
	, const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
}


///////////////////////////////////////////////////////////////////////////////////

void ChVec4::DeserializeARGB(
	const std::string& _str
	, const size_t _fPos
	, const std::string& _cutChar
	, const std::string& _endChar
	, const unsigned int _digit)
{

	ChVec4 tmpVec;
	tmpVec.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);

	for (unsigned char i = 0; i < 4; i++)
	{
		val[i] = tmpVec.val[(i + 1) % 4];
	}

}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::GetCross(
	const ChVector4& _vec1, 
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	ChVector4 tmpVec;

	tmpVec.val.Cross(_vec1.val, _vec2.val,_digit);

	return tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetCos(
	const ChVector4& _vec1, 
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetCos(_vec2.val,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetRadian(
	const ChVector4& _vec1, 
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetRadian(_vec2.val,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetDot(
	const ChVector4& _vec1,
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetDot(_vec2.val,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

//???????s??(Now??0?`1)
ChVector4 ChVec4::GetCorrection(
	const ChVector4& _start, 
	const ChVector4& _end,
	const float _Now)
{
	ChVector4 tmpVec;

	tmpVec.val.Correction(_start.val, _end.val, _Now);

	return tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetLen(
	const ChVector4& _vec1
	, const ChVector4& _vec2,
	const unsigned long _digit)
{

	ChVec4 tmpVec = _vec1 - _vec2;

	return  tmpVec.val.GetLen(_digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetElementsLen(
	const ChVector4& _vec1,
	const ChVector4& _vec2)
{

	ChVec4 tmpVec = _vec1 - _vec2;

	return  tmpVec.val.GetElementsLen();
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVec4::Normalize(const unsigned long _digit)
{
	return val.Normalize(_digit);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::ElementsNormalize()
{
	val.ElementsNormalize();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Cross(
	const ChVector4& _vec1
	, const ChVector4& _vec2,
	const unsigned long _digit)
{
	val.Cross(_vec1.val, _vec2.val,_digit);
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion Method//
///////////////////////////////////////////////////////////////////////////////////

std::string ChQua::Serialize(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	return val.Serialize(_cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChQua::Deserialize(
	const std::string& _str
	, const size_t _fPos
	, const std::string& _cutChar
	, const std::string& _endChar
	, const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChQua::GetEulerAngleForVec3()const
{

	float xx = x * x;
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float yy = y * y;
	float yz = y * z;
	float yw = y * w;
	float zz = z * z;
	float zw = z * w;
	float ww = w * w;

	ChVec3 out;

	out.x = std::asin(2.0f * (xz - yw));
	out.y = std::atan2(2.0f * (yz + xw), xx + yy - zz - ww);
	out.z = std::atan2(2.0f * (zw + xy), xx - yy - zz + ww);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQua::RotYPR(
	const float _x
	, const float _y
	, const float _z)
{

	ChVec3 Cos;
	ChVec3 Sin;

	Cos.x = cos(_x / 2.0f);
	Sin.x = sin(_x / 2.0f);

	Cos.y = cos(_y / 2.0f);
	Sin.y = sin(_y / 2.0f);

	Cos.z = cos(_z / 2.0f);
	Sin.z = sin(_z / 2.0f);

	x = (Cos.y * Cos.x * Cos.z) + (Sin.y * Sin.x * Sin.z);
	y = (Cos.y * Cos.x * Sin.z) - (Sin.y * Sin.x * Cos.z);
	z = (Cos.y * Sin.x * Cos.z) + (Sin.y * Cos.x * Sin.z);
	w = (Sin.y * Cos.x * Cos.z) + (Cos.y * Sin.x * Sin.z);

}

///////////////////////////////////////////////////////////////////////////////////
//ChLMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator =(const ChLMatrix& _mat)
{
	if (this == &_mat)return *this;
	m.Set(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator += (const ChLMatrix& _mat)
{
	m.Add(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator + (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out += _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator -= (const ChLMatrix& _mat)
{
	m.Sub(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator - (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out -= _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator *= (const ChLMatrix& _mat)
{
	m.Mul(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator * (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out *= _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator /= (const ChLMatrix& _mat)
{
	m.Div(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator / (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out /= _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetPosition(const ChVec3& _vec)
{
	SetPosition(_vec.x, _vec.y, _vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetPosition(const float _x, const float _y, const float _z)
{
	l_41 = _x;
	l_42 = _y;
	l_43 = _z;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::ChLMatrix::SetRotation(
	const ChVec3& _vec,
	const unsigned long _digit)
{
	SetRotation(_vec.x, _vec.y, _vec.z,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotation(
	const float _x, 
	const float _y, 
	const float _z,
	const unsigned long _digit)
{

	ChLMat XAxis, YAxis, ZAxis;

	XAxis.SetRotationXAxis(_x);
	YAxis.SetRotationYAxis(_y);
	ZAxis.SetRotationZAxis(_z);

	YAxis = XAxis * YAxis;

	YAxis = ZAxis * YAxis;

	YAxis.SetPosition(GetPosition());
	YAxis.SetScalling(GetScalling(_digit),_digit);

	m.Set(YAxis.m);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationXAxis(const float _x)
{
	float x = -std::fmod(_x, ChMath::PI * 2.0f);

	l_22 = std::cos(x);
	l_23 = std::sin(x);

	l_32 = -std::sin(x);
	l_33 = std::cos(x);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationYAxis(const float _y)
{
	float  y = -std::fmod(_y, ChMath::PI * 2.0f);

	l_11 = std::cos(y);
	l_13 = -std::sin(y);

	l_31 = std::sin(y);
	l_33 = std::cos(y);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationZAxis(const float _z)
{
	float z = -std::fmod(_z, ChMath::PI * 2.0f);

	l_11 = std::cos(z);
	l_12 = std::sin(z);

	l_21 = -std::sin(z);
	l_22 = std::cos(z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetScalling(
	const ChVec3& _vec,
	const unsigned long _digit)
{
	SetScalling(_vec.x, _vec.y, _vec.z,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetPosition()const
{
	return ChVec3(l_41, l_42, l_43);
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetRotation(const unsigned long _digit)const
{
	ChVec3 tmpScl = GetScalling(_digit);

	float outM[4][4];

	for (unsigned char i = 0; i < 3; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
		{
			outM[i][j] = m[i][j];
			outM[i][j] /= tmpScl.val[i] != 0.0f ? tmpScl.val[i] : 1.0f;
		}
	}

	ChVec3 out = ChVec3(
		(std::atan2f(outM[2][1], outM[2][2])),
		(std::asinf(-outM[2][0])),
		(std::atan2f(outM[1][0], outM[0][0])));

	//ChVec3 out = ChVec3(
	//	(std::atan2f(_32,_33)),
	//	(std::asinf(_31)),
	//	(std::atan2f(_21,_11)));


	return out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetScalling(const unsigned long _digit)const
{
	return ChVec3(m[0].GetLen(_digit), m[1].GetLen(_digit), m[2].GetLen(_digit));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::Transform(const ChVec4& _Base)const
{
	ChVec4 out;

	out = _Base;

	out.w = 1.0f;

	out.val = m.HorizontalMul(out.val);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::TransformCoord(const ChVec4& _Base)const
{
	ChLMatrix tmp = *this;

	tmp.l_41 = 0.0f;
	tmp.l_42 = 0.0f;
	tmp.l_43 = 0.0f;

	return tmp.Transform(_Base);
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix ChLMatrix::ConvertAxis()
{
	ChRMatrix tmp;

	for (unsigned long i = 0; i < m.GetColumn(); i++)
	{
		for (unsigned long j = 0; j < m.GetRow(); j++)
		{
			tmp.m[i][j] = m[j][i];
		}
	}

	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////
//ChRMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

ChRMatrix& ChRMatrix::operator =(const ChRMatrix& _mat)
{
	if (this == &_mat)return *this;
	m.Set(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix& ChRMatrix::operator += (const ChRMatrix& _mat)
{
	m.Add(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix const ChRMatrix::operator + (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out += _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix& ChRMatrix::operator -= (const ChRMatrix& _mat)
{
	m.Sub(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix const ChRMatrix::operator - (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out -= _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix& ChRMatrix::operator *= (const ChRMatrix& _mat)
{
	m.Mul(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix const ChRMatrix::operator * (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out *= _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix& ChRMatrix::operator /= (const ChRMatrix& _mat)
{
	m.Div(_mat.m);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix const ChRMatrix::operator / (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out /= _mat;
	return out;
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetPosition(const ChVec3& _vec)
{
	SetPosition(_vec.x, _vec.y, _vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetPosition(const float _x, const float _y, const float _z)
{
	r_41 = _x;
	r_42 = _y;
	r_43 = _z;
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::ChRMatrix::SetRotation(
	const ChVec3& _vec,
	const unsigned long _digit)
{
	SetRotation(_vec.x, _vec.y, _vec.z,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetRotation(
	const float _x, 
	const float _y, 
	const float _z,
	const unsigned long _digit)
{

	ChRMat XAxis, YAxis, ZAxis;

	XAxis.SetRotationXAxis(_x);
	YAxis.SetRotationYAxis(_y);
	ZAxis.SetRotationZAxis(_z);

	YAxis = XAxis * YAxis;

	YAxis = ZAxis * YAxis;

	YAxis.SetPosition(GetPosition());
	YAxis.SetScalling(GetScalling(_digit),_digit);

	m.Set(YAxis.m);
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetRotationXAxis(const float _x)
{
	float x = -std::fmod(_x, ChMath::PI * 2.0f);

	r_22 = std::cos(x);
	r_23 = std::sin(x);

	r_32 = -std::sin(x);
	r_33 = std::cos(x);
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetRotationYAxis(const float _y)
{
	float  y = -std::fmod(_y, ChMath::PI * 2.0f);

	r_11 = std::cos(y);
	r_13 = -std::sin(y);

	r_31 = std::sin(y);
	r_33 = std::cos(y);
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetRotationZAxis(const float _z)
{
	float z = -std::fmod(_z, ChMath::PI * 2.0f);

	r_11 = std::cos(z);
	r_12 = std::sin(z);

	r_21 = -std::sin(z);
	r_22 = std::cos(z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChRMatrix::SetScalling(
	const ChVec3& _vec,
	const unsigned long _digit)
{
	SetScalling(_vec.x, _vec.y, _vec.z,_digit);
}

///////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChRMatrix::GetPosition()const
{
	return ChVec3(r_41, r_42, r_43);
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChRMatrix::GetRotation(const unsigned long _digit)const
{
	ChVec3 tmpScl = GetScalling(_digit);

	float outM[4][4];

	for (unsigned char i = 0; i < 3; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
		{
			outM[i][j] = m[j][i];
			outM[i][j] /= tmpScl.val[j] != 0.0f ? tmpScl.val[j] : 1.0f;
		}
	}

	ChVec3 out = ChVec3(
		(std::atan2f(outM[2][1], outM[2][2])),
		(std::asinf(-outM[2][0])),
		(std::atan2f(outM[1][0], outM[0][0])));


	return out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChRMatrix::GetScalling(const unsigned long _digit)const
{
	ChVector4 vec[3];

	for (unsigned long i = 0; i < m.GetRow() - 1; i++)
	{
		for (unsigned long j = 0; j < m.GetColumn() - 1; j++)
		{
			vec[i].val[j] = m[j][i];
		}
	}

	return ChVec3(vec[0].val.GetLen(_digit), vec[1].val.GetLen(_digit), vec[2].val.GetLen(_digit));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChRMatrix::Transform(const ChVec4 _Base)const
{
	ChVec4 out;

	out = _Base;

	out.w = 1.0f;

	out.val = m.VerticalMul(out.val);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChRMatrix::TransformCoord(const ChVec4 _Base)const
{
	ChRMatrix tmp = *this;

	tmp.r_41 = 0.0f;
	tmp.r_42 = 0.0f;
	tmp.r_43 = 0.0f;

	return tmp.Transform(_Base);
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix ChRMatrix::ConvertAxis()
{
	ChLMatrix tmp;

	for (unsigned long i = 0; i < m.GetColumn(); i++)
	{
		for (unsigned long j = 0; j < m.GetRow(); j++)
		{
			tmp.m[i][j] = m[j][i];
		}
	}

	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////
//ChUIMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

ChUIMatrix& ChUIMatrix::operator =(const ChUIMatrix _mat)
{
	m.Set(_mat.m);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChUIMatrix::Serialize(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	return m.Serialize(_cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChUIMatrix::SerializeUpper(
	const std::string& _cutChar
	, const std::string& _endChar
	, const std::string& _cutTo4Char)
{
	return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
}

///////////////////////////////////////////////////////////////////////////////////

void ChUIMatrix::Deserialize(
	const std::string& _str
	, const size_t _fPos
	, const std::string& _cutChar
	, const std::string& _endChar)
{
	m.Deserialize(_str, _fPos, _cutChar, _endChar);
}

///////////////////////////////////////////////////////////////////////////////////
//Math Function//
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//Degree Method//
///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator=(const float _num)
{
	val = _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator+=(const float _num)
{

	val += _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator+(const float _num)const
{
	Degree tmp = *this;
	tmp += _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator-=(const float _num)
{
	val -= _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator-(const float _num)const
{

	Degree tmp = *this;
	tmp -= _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator*=(const float _num)
{
	val *= _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator*(const float _num)const
{

	Degree tmp = *this;
	tmp *= _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator/=(const float _num)
{
	val /= _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator/(const float _num)const
{

	Degree tmp = *this;
	tmp /= _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::operator float()const
{
	float tmp;
	tmp = val;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator=(const ChMath::Radian _num)
{
	*this = ToDegree(_num);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::Degree()
{
	val = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::Degree(const float _val)
{
	*this = _val;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::Degree(const Degree& _val)
{
	val = _val;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::Degree(const Radian& _val)
{
	*this = _val;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMath::Degree::Math()
{
	if (val < 0.0f)
	{
		unsigned int tmp;
		tmp = static_cast<unsigned int>(std::floor((val / -360.0f)));
		val += (tmp + 1) * 360.0f;
		return;
	}

	if (val >= 360.0f)
	{
		unsigned int tmp;
		tmp = static_cast<unsigned int>(std::floor((val / 360.0f)));
		val -= (tmp) * 360.0f;
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////
//Radian Method//
///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator=(const float _num)
{
	val = _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator+=(const float _num)
{

	val += _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator+(const float _num)const
{
	Radian tmp = *this;
	tmp += _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator-=(const float _num)
{
	val -= _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator-(const float _num)const
{

	Radian tmp = *this;
	tmp -= _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator*=(const float _num)
{
	val *= _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator*(const float _num)const
{

	Radian tmp = *this;
	tmp *= _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator/=(const float _num)
{
	val /= _num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator/(const float _num)const
{

	Radian tmp = *this;
	tmp /= _num;
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::operator float()const
{
	float tmp;
	tmp = val;
	return tmp;
}


///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator=(const Degree _num)
{
	*this = ToRadian(_num);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::Radian()
{
	val = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::Radian(const float _val)
{
	*this = _val;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::Radian(const Radian& _val)
{
	val = _val;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::Radian(const Degree& _val)
{
	*this = _val;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMath::Radian::Math()
{
	float tmpVal;
	tmpVal = (val / PI);
	if (tmpVal < 0.0f)
	{
		unsigned int tmp;
		tmp = static_cast<unsigned int>(std::floor((tmpVal / -2.0f)));
		val += (tmp + 1) * 2.0f * PI;
		return;
	}

	if (tmpVal >= 360.0f)
	{
		unsigned int tmp;
		tmp = static_cast<unsigned int>(std::floor((tmpVal / 2.0f)));
		val -= (tmp) * 2.0f * PI;
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////
//Math Function//
///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChMath::GetFaceNormal(
	const ChVec3& _Pos1
	, const ChVec3& _Pos2
	, const ChVec3& _Pos3,
	const unsigned long _digit)
{

	ChVec3 tmpVec, tmpVec2;

	tmpVec = _Pos1 - _Pos2;
	tmpVec2 = _Pos2 - _Pos3;

	tmpVec.Cross(tmpVec, tmpVec2,_digit);

	tmpVec.Normalize(_digit);

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChMath::GetFaceNormal(
	const TriVertex& _PlEq,
	const unsigned long _digit)
{
	return GetFaceNormal(_PlEq.Ver1, _PlEq.Ver2, _PlEq.Ver3,_digit);
}
