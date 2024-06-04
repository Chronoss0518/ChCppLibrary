#include"../BaseIncluder/ChBase.h"

#define FLOAT_ZERO_TEST(val, testSize) val >= -testSize && val <= testSize

#include <float.h>
#include <cmath>

///////////////////////////////////////////////////////////////////////////////////
//ChVector2 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVector2::FromPosition(const float& _x, const float& _y)
{
	ChVector2 res;
	res.x = _x;
	res.y = _y;
	return res;
}

ChVector2 ChVector2::FromSize(const float& _w, const float& _h)
{
	ChVector2 res;
	res.w = _w;
	res.h = _h;
	return res;
}

ChVector2 ChVector2::FromTime(const float& _start, const float& _end)
{
	ChVector2 res;
	res.start = _start;
	res.end = _end;
	return res;
}

ChVector2 ChVector2::FromHighLow(const float& _high, const float& _low)
{
	ChVector2 res;
	res.high = _high;
	res.low = _low;
	return res;
}

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

std::wstring ChVec2::Serialize(
	const std::wstring& _cutChar
	, const std::wstring& _endChar)
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

void ChVec2::Deserialize(
	const std::wstring& _str
	, const size_t _fPos
	, const std::wstring& _cutChar
	, const std::wstring& _endChar
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

bool ChVec2::Normalize(const unsigned long _digit)
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

ChVector3 ChVector3::FromPosition(const float& _x, const float& _y, const float _z)
{
	ChVector3 res;
	res.x = _x;
	res.y = _y;
	res.z = _z;
	return res;
}

ChVector3 ChVector3::FromColor(const float& _r, const float& _g, const float& _b)
{
	ChVector3 res;
	res.r = _r;
	res.g = _g;
	res.b = _b;
	return res;
}

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

std::wstring ChVec3::Serialize(
	const std::wstring& _cutChar
	, const std::wstring& _endChar)
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

void ChVec3::Deserialize(
	const std::wstring& _str
	, const size_t _fPos
	, const std::wstring& _cutChar
	, const std::wstring& _endChar
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

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
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

bool ChVec3::Normalize(
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

ChVector4 ChVector4::FromPosition(const float& _x, const float& _y, const float _z, const float& _w)
{
	ChVector4 res;
	res.x = _x;
	res.y = _y;
	res.z = _z;
	res.w = _w;
	return res;
}

ChVector4 ChVector4::FromColor(const float& _r, const float& _g, const float& _b, const float& _a)
{
	ChVector4 res;
	res.r = _r;
	res.g = _g;
	res.b = _b;
	res.a = _a;
	return res;
}

ChVector4 ChVector4::FromRect(const float& _left, const float& _top, const float& _right, const float& _bottom)
{
	ChVector4 res;
	res.left = _left;
	res.top = _top;
	res.right = _right;
	res.bottom = _bottom;
	return res;
}

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

std::wstring ChVec4::Serialize(
	const std::wstring& _cutChar
	, const std::wstring& _endChar)
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

std::wstring ChVec4::SerializeARGB(
	const std::wstring& _cutChar
	, const std::wstring& _endChar)
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

void ChVec4::Deserialize(
	const std::wstring& _str
	, const size_t _fPos
	, const std::wstring& _cutChar
	, const std::wstring& _endChar
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

void ChVec4::DeserializeARGB(
	const std::wstring& _str
	, const size_t _fPos
	, const std::wstring& _cutChar
	, const std::wstring& _endChar
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

	tmpVec.val.Cross(_vec1.val, _vec2.val, _digit);

	return tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetCos(
	const ChVector4& _vec1,
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetCos(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetRadian(
	const ChVector4& _vec1,
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetRadian(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetDot(
	const ChVector4& _vec1,
	const ChVector4& _vec2,
	const unsigned long _digit)
{
	return _vec1.val.GetDot(_vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
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

bool ChVec4::Normalize(const unsigned long _digit)
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
	val.Cross(_vec1.val, _vec2.val, _digit);
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion Method//
///////////////////////////////////////////////////////////////////////////////////

ChQuaternion& ChQuaternion::operator=(const ChQuaternion& _qua)
{
	val.Set(_qua.val);
	return *this;
}

ChQuaternion& ChQuaternion::operator+=(const ChQuaternion& _num)
{
	Sum(_num);
	return *this;
}

ChQuaternion ChQuaternion::operator+(const ChQuaternion& _num) const
{
	return  GetSum(*this, _num);
}

ChQuaternion& ChQuaternion::operator*=(const ChQuaternion& _num)
{
	Mul(_num);
	return *this;
}

ChQuaternion ChQuaternion::operator*(const ChQuaternion& _num)const
{
	return  GetMul(*this, _num);
}

std::string ChQua::Serialize(
	const std::string& _cutChar
	, const std::string& _endChar)
{
	return val.Serialize(_cutChar, _endChar);
}

std::wstring ChQua::Serialize(
	const std::wstring& _cutChar
	, const std::wstring& _endChar)
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

void ChQua::Deserialize(
	const std::wstring& _str
	, const size_t _fPos
	, const std::wstring& _cutChar
	, const std::wstring& _endChar
	, const unsigned int _digit)
{
	val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
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

void ChQua::SetRotationXAxis(const float _x)
{
	SetRotation(ChVec3(1.0f, 0.0f, 0.0f), _x);
}

void ChQua::SetRotationYAxis(const float _y)
{
	SetRotation(ChVec3(0.0f, 1.0f, 0.0f), _y);
}

void ChQua::SetRotationZAxis(const float _z)
{
	SetRotation(ChVec3(0.0f, 0.0f, 1.0f), _z);
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

void ChQua::SetRotation(const ChVec3& _from, const ChVec3& _to)
{

	ChVec3 from = _from, to = _to;

	from.Normalize();
	to.Normalize();

	auto&& axis = ChVec3::GetCross(from, to);
	
	if (!axis.Normalize())
	{
		Identity();
		return;
	}

	auto&& cos = ChVec3::GetRadian(from, to);

	SetRotation(axis, cos);

}

ChLMatrix ChQua::GetRotationLMatrix(const unsigned long _digit)const
{
	ChLMat mat;
	mat.SetRotation(*this, _digit);
	return mat;
}

ChRMatrix ChQua::GetRotationRMatrix(const unsigned long _digit)const
{
	ChRMat mat;
	mat.SetRotation(*this, _digit);
	return mat;
}

ChVec3 ChQua::GetAxis()const
{
	ChVec3 res = ChVec3(x, y, z);

	if (res.Len() <= 0.00001f)return ChVec3(0.0f, 1.0f, 0.0f);

	float sin = std::sinf(GetRadian() / 2.0f);

	if (sin <= 0.00001f)return ChVec3(0.0f, 1.0f, 0.0f);

	return res / sin;

}

ChEularXYZ ChQua::GetEularRotationXYZ(const unsigned long _digit)const
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

ChEularXZY ChQua::GetEularRotationXZY(const unsigned long _digit)const
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

ChEularYXZ ChQua::GetEularRotationYXZ(const unsigned long _digit)const
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

ChEularYZX ChQua::GetEularRotationYZX(const unsigned long _digit)const
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

ChEularZXY ChQua::GetEularRotationZXY(const unsigned long _digit)const
{
	ChEularZXY res;

	res.x = std::asinf((2.0f * y * z + 2.0f * x * w));

	float ww = 2.0f * w * w;

	float xz = 2.0f * x * z;
	float yw = 2.0f * y * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.x), 0.000001f))
	{
		res.y = 0.0f;
		res.z = std::atanf(-(xz + yw) / (ww + 2.0f * x * x - 1.0f));
	}
	else
	{
		res.y = std::atanf((2.0f * x * y - 2.0f * z * w) / (ww + 2.0f * y * y - 1.0f));
		res.z = std::atanf((xz - yw) / (ww + 2.0f * z * z - 1.0f));
	}

	return res;
}

ChEularZYX ChQua::GetEularRotationZYX(const unsigned long _digit)const
{
	ChEularZYX res;

	res.y = std::asinf((2.0f * x * z - 2.0f * y * w));

	float ww = 2.0f * w * w;

	float xy = 2.0f * x * y;
	float zw = 2.0f * z * w;

	if (FLOAT_ZERO_TEST(std::cosf(res.y), 0.000001f))
	{
		res.x = 0.0f;
		res.z = std::atanf((xy - zw) / (ww + 2.0f * y * y - 1.0f));
	}
	else
	{
		res.x = std::atanf(-(2.0f * x * y + 2.0f * z * w) / (ww + 2.0f * y * y - 1.0f));
		res.z = std::atanf(-(xy + zw) / (ww + 2.0f * z * z - 1.0f));
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

void ChQua::AddRotationXAxis(float _x)
{
	ChQua qua;
	qua.SetRotationXAxis(_x);

	*this = qua * *this;
}

void ChQua::AddRotationYAxis(float _y)
{
	ChQua qua;
	qua.SetRotationYAxis(_y);

	*this = qua * *this;
}

void ChQua::AddRotationZAxis(float _z)
{
	ChQua qua;
	qua.SetRotationZAxis(_z);

	*this = qua * *this;
}

void ChQua::Sum(const ChQua& _value)
{
	val.Set(GetSum(*this, _value).val);
}

void ChQua::Mul(const ChQua& _value)
{
	val.Set(GetMul(*this, _value).val);
}

ChVec3 ChQua::Mul(const ChVec3& _dir)
{
	return GetMul(*this, _dir);
}

ChQuaternion ChQuaternion::GetSum(const ChQuaternion& _qua1, const ChQuaternion& _qua2)
{
	ChQuaternion res = _qua1;
	res.val.Add(_qua2.val);
	return res;
}

////
//https://qiita.com/drken/items/0639cf34cce14e8d58a5#1-4-%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%AE%E3%81%8B%E3%81%91%E7%AE%97
////
// = q1 * q2;
ChQua ChQua::GetMul(const ChQua& _qua1, const ChQua& _qua2)
{
	ChQua res;

	res.x = (_qua1.w * _qua2.x) - (_qua1.z * _qua2.y) + (_qua1.y * _qua2.z) + (_qua1.x * _qua2.w);
	res.y = (_qua1.z * _qua2.x) + (_qua1.w * _qua2.y) - (_qua1.x * _qua2.z) + (_qua1.y * _qua2.w);
	res.z = -(_qua1.y * _qua2.x) + (_qua1.x * _qua2.y) + (_qua1.w * _qua2.z) + (_qua1.z * _qua2.w);

	res.w = (_qua1.w * _qua2.w) - (_qua1.x * _qua2.x) - (_qua1.y * _qua2.y) - (_qua1.z * _qua2.z);

	return res;
}

ChVec3 ChQua::GetMul(const ChQuaternion& _qua, const ChVec3& _dir)
{
	ChVec3 res = _dir;
	res.Normalize();

	ChQua tmp = ChQua(res.x, res.y, res.z);

	ChQua idn = _qua;
	idn.Inverse();
	tmp = _qua * tmp * idn;

	res = ChVec3(tmp.x, tmp.y, tmp.z);

	return res;
}

ChQuaternion ChQuaternion::SLerp(const ChQuaternion& _start, const ChQuaternion& _end, const float _pow)
{
	ChQua res;
	res.val.Set(_start.val.SLerp(_start.val, _end.val, _pow));

	return res;
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

bool ChLMatrix::operator == (const ChLMatrix& _mat)const
{
	return m.IsValue(_mat.m);
}

bool ChLMatrix::operator != (const ChLMatrix& _mat)const
{
	return !m.IsValue(_mat.m);
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

void ChLMatrix::SetRotationYPR(const float _x, const float _y, const float _z, const unsigned long _digit)
{
	ChVec3 scale = GetScalling();
	ChVec3 pos = GetPosition();

	SetRotationYAxis(_y);

	ChLMat tmp;

	tmp.SetRotationXAxis(_x);

	*this = tmp * *this;

	tmp.SetRotationZAxis(_z);

	*this = tmp * *this;

	SetPosition(pos);
	SetScalling(scale);
}

void ChLMatrix::SetRotationYPR(const ChVec3& _vec, const unsigned long _digit)
{
	SetRotationYPR(_vec.x, _vec.y, _vec.z, _digit);
}

//à»â∫ÇÃURLÇéQè∆//
//https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf#%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%8B%E3%82%89%E5%9B%9E%E8%BB%A2%E8%A1%8C%E5%88%97
//
void ChLMatrix::SetRotation(const ChQua& _qua, const unsigned long _digit)
{

	float squaredW = 2.0f * _qua.w * _qua.w;

	ChVec3 scl = GetScalling(_digit);

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

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationXAxis(const float _x)
{
	Identity();

	float x = -std::fmod(_x, ChMath::PI * 2.0f);

	l_22 = std::cos(x);
	l_23 = std::sin(x);

	l_32 = -std::sin(x);
	l_33 = std::cos(x);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationYAxis(const float _y)
{
	Identity();

	float  y = -std::fmod(_y, ChMath::PI * 2.0f);

	l_11 = std::cos(y);
	l_13 = -std::sin(y);

	l_31 = std::sin(y);
	l_33 = std::cos(y);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationZAxis(const float _z)
{
	Identity();

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
	SetScalling(_vec.x, _vec.y, _vec.z, _digit);
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

ChQua ChLMatrix::GetRotation(const unsigned long _digit)const
{
	ChQua res;
	res.SetRotationLMatrix(*this);
	return res;

}

ChEularXYZ ChLMatrix::GetEularRotationXYZ(const unsigned long _digit)const
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

ChEularXZY ChLMatrix::GetEularRotationXZY(const unsigned long _digit)const
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

ChEularYXZ ChLMatrix::GetEularRotationYXZ(const unsigned long _digit)const
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

ChEularYZX ChLMatrix::GetEularRotationYZX(const unsigned long _digit)const
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

ChEularZXY ChLMatrix::GetEularRotationZXY(const unsigned long _digit)const
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
	res.z = std::atanf(zeroFlg ? -outM.m[1][0] / outM.m[0][0]  : outM.m[0][1] / outM.m[1][1]);

	return res;
}

ChEularZYX ChLMatrix::GetEularRotationZYX(const unsigned long _digit)const
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

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetScalling(const unsigned long _digit)const
{
	return ChVec3(m[0].GetLen(_digit), m[1].GetLen(_digit), m[2].GetLen(_digit));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetXAxisDirection()const
{
	ChVec3 res;
	res.val.Set(m[0]);

	return res;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetYAxisDirection()const
{
	ChVec3 res;
	res.val.Set(m[1]);

	return res;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetZAxisDirection()const
{
	ChVec3 res;
	res.val.Set(m[2]);

	return res;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::Transform(const ChVec4& _base)const
{
	ChVec4 out;

	out = _base;

	out.w = 1.0f;

	out.val = m.HorizontalMul(out.val);

	return out;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::TransformCoord(const ChVec4& _base)const
{
	ChLMatrix tmp = *this;

	tmp.l_41 = 0.0f;
	tmp.l_42 = 0.0f;
	tmp.l_43 = 0.0f;

	return tmp.Transform(_base);
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

bool ChRMatrix::operator == (const ChRMatrix& _mat)const
{
	return m.IsValue(_mat.m);
}

bool ChRMatrix::operator != (const ChRMatrix& _mat)const
{
	return !m.IsValue(_mat.m);
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

void ChRMatrix::SetRotation(const ChQua& _qua, const unsigned long _digit)
{

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
	SetScalling(_vec.x, _vec.y, _vec.z, _digit);
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

ChVec3 ChRMatrix::GetXAxisDirection()const
{
	ChVec3 res = ChVec3(m[0][0], m[1][0], m[2][0]);

	return res;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChRMatrix::GetYAxisDirection()const
{
	ChVec3 res = ChVec3(m[0][1], m[1][1], m[2][1]);

	return res;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChRMatrix::GetZAxisDirection()const
{
	ChVec3 res = ChVec3(m[0][2], m[1][2], m[2][2]);

	return res;
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

ChLMatrix ChRMatrix::ConvertAxis()const
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

ChVector3 ChMath::GetFaceNormal(
	const ChVec3& _Pos1
	, const ChVec3& _Pos2
	, const ChVec3& _Pos3,
	const unsigned long _digit)
{

	ChVec3 tmpVec, tmpVec2;

	tmpVec = _Pos1 - _Pos2;
	tmpVec2 = _Pos2 - _Pos3;

	tmpVec.Cross(tmpVec, tmpVec2, _digit);

	tmpVec.Normalize(_digit);

	return tmpVec;
}
