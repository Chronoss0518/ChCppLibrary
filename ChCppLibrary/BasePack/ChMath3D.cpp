#include"ChMath3D.h"

#define FLOAT_ZERO_TEST(val, testSize) val >= -testSize && val <= testSize

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

ChVector2& ChVec2::operator*= (const float& _num)
{
	val.Mul(_num);
	return *this;
}

ChVector2 ChVec2::operator * (const float& _num)const
{
	ChVector2 tmpVec = *this;
	tmpVec *= _num;
	return tmpVec;
}

ChVector2& ChVec2::operator/= (const float& _num)
{
	val.Div(_num);
	return *this;
}

ChVector2 ChVec2::operator / (const float& _num)const
{
	ChVector2 tmpVec = *this;
	tmpVec /= _num;
	return tmpVec;
}

ChVector2& ChVec2::operator= (const float& _num)
{
	val.Set(_num);
	return *this;
}

ChVector2& ChVec2::operator += (const ChVector2& _vec)
{
	val.Add(_vec.val);
	return *this;
}

ChVector2 ChVec2::operator + (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;
	tmpVec += _vec;
	return tmpVec;
}

ChVector2& ChVec2::operator -= (const ChVector2& _vec)
{
	val.Sub(_vec.val);
	return *this;
}

ChVector2 ChVec2::operator - (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;
	tmpVec -= _vec;
	return tmpVec;
}

ChVector2& ChVec2::operator *= (const ChVector2& _vec)
{
	val.Mul(_vec.val);
	return *this;
}

ChVector2 ChVec2::operator * (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;
	tmpVec *= _vec;
	return tmpVec;
}

ChVector2& ChVec2::operator /= (const ChVector2& _vec)
{
	val.Div(_vec.val);
	return *this;
}

ChVector2 ChVec2::operator / (const ChVector2& _vec)const
{
	ChVector2 tmpVec = *this;
	tmpVec /= _vec;
	return tmpVec;
}

ChVec2::operator const ChVector4() const
{
	ChVec4 out;
	out.val = static_cast<ChMath::VectorBase<float, 4>>(val);
	return out;

}

ChVec2::operator const ChVector3() const
{

	ChVec3 out;
	out.val = static_cast<ChMath::VectorBase<float, 3>>(val);
	return out;
}

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

ChVector3 ChVec3::operator * (const float& _num)const
{
	ChVector3 tmpVec = *this;
	tmpVec *= _num;
	return tmpVec;
}

ChVector3& ChVec3::operator/= (const float& _num)
{
	val.Div(_num);
	return *this;
}

ChVector3 ChVec3::operator / (const float& _num)const
{
	ChVector3 tmpVec = *this;
	tmpVec /= _num;
	return tmpVec;
}

ChVector3& ChVec3::operator= (const float& _num)
{
	val.Set(_num);
	return *this;
}

ChVector3& ChVector3::operator=(const ChVector3& _vec)
{
	val.Set(_vec.val);
	return *this;
}

ChVector3& ChVec3::operator *= (const ChVector3& _vec)
{
	val.Mul(_vec.val);
	return *this;
}

ChVector3 ChVec3::operator * (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;
	tmpVec *= _vec;
	return tmpVec;
}

ChVector3& ChVec3::operator /= (const ChVector3& _vec)
{
	val.Div(_vec.val);
	return *this;
}

ChVector3 ChVec3::operator / (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;
	tmpVec /= _vec;
	return tmpVec;
}

ChVector3& ChVec3::operator -= (const ChVector3& _vec)
{
	val.Sub(_vec.val);
	return *this;
}

ChVector3 ChVec3::operator - (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;
	tmpVec -= _vec;
	return tmpVec;
}

ChVector3& ChVec3::operator += (const ChVector3& _vec)
{
	val.Add(_vec.val);
	return *this;
}

ChVector3 ChVec3::operator + (const ChVector3& _vec)const
{
	ChVector3 tmpVec = *this;
	tmpVec += _vec;
	return tmpVec;
}

ChVec3::operator const ChVector4() const
{
	ChVec4 out;
	out.val = static_cast<ChMath::VectorBase<float, 4>>(val);
	return out;
}

ChVec3::operator const ChVector2() const
{
	ChVec2 out;
	out.val = static_cast<ChMath::VectorBase<float, 2>>(val);
	return out;
}



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

ChVector4 ChVec4::operator * (const float& _num)const
{
	ChVector4 tmpVec = *this;
	tmpVec *= _num;
	return tmpVec;
}

ChVector4& ChVec4::operator/= (const float& _num)
{
	val.Div(_num);
	return *this;
}

ChVector4 ChVec4::operator / (const float& _num)const
{
	ChVector4 tmpVec = *this;
	tmpVec /= _num;
	return tmpVec;
}

ChVector4& ChVec4::operator= (const float& _num)
{
	val.Set(_num);
	return *this;
}

ChVector4& ChVector4::operator=(const ChVector4& _vec)
{
	val.Set(_vec.val);
	return *this;
}

ChVector4& ChVec4::operator *= (const ChVector4& _vec)
{
	val.Mul(_vec.val);
	return *this;
}

ChVector4 ChVec4::operator * (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;
	tmpVec *= _vec;
	return tmpVec;
}

ChVector4& ChVec4::operator /= (const ChVector4& _vec)
{
	val.Div(_vec.val);
	return *this;
}

ChVector4 ChVec4::operator / (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;
	tmpVec /= _vec;
	return tmpVec;
}

ChVector4& ChVec4::operator -= (const ChVector4& _vec)
{
	val.Sub(_vec.val);
	return *this;
}

ChVector4 ChVec4::operator - (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;
	tmpVec -= _vec;
	return tmpVec;
}

ChVector4& ChVec4::operator += (const ChVector4& _vec)
{
	val.Add(_vec.val);
	return *this;
}

ChVector4 ChVec4::operator + (const ChVector4& _vec)const
{
	ChVector4 tmpVec = *this;
	tmpVec += _vec;
	return tmpVec;
}

ChVec4::operator const ChVector3() const
{
	ChVec3 out;
	out.val = static_cast<ChMath::VectorBase<float, 3>>(val);
	return out;
}

ChVec4::operator const ChVector2() const
{
	ChVec2 out;
	out.val = static_cast<ChMath::VectorBase<float, 2>>(val);
	return out;
}



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
	return GetSum(*this, _num);
}

ChQuaternion& ChQuaternion::operator*=(const ChQuaternion& _num)
{
	Mul(_num);
	return *this;
}

ChQuaternion ChQuaternion::operator*(const ChQuaternion& _num)const
{
	return GetMul(*this, _num);
}

void ChQuaternion::SetRotationXAxis(const float _x)
{
	SetRotation(ChVec3(1.0f, 0.0f, 0.0f), _x);
}

void ChQuaternion::SetRotationYAxis(const float _y)
{
	SetRotation(ChVec3(0.0f, 1.0f, 0.0f), _y);
}

void ChQuaternion::SetRotationZAxis(const float _z)
{
	SetRotation(ChVec3(0.0f, 0.0f, 1.0f), _z);
}

void ChQuaternion::SetRotation(const ChVec3& _from, const ChVec3& _to)
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



ChLMatrix& ChLMatrix::operator =(const ChLMatrix& _mat)
{
	if (this == &_mat)return *this;
	m.Set(_mat.m);
	return *this;
}

ChLMatrix& ChLMatrix::operator += (const ChLMatrix& _mat)
{
	m.Add(_mat.m);
	return *this;
}

ChLMatrix const ChLMatrix::operator + (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out += _mat;
	return out;
}

ChLMatrix& ChLMatrix::operator -= (const ChLMatrix& _mat)
{
	m.Sub(_mat.m);
	return *this;
}

ChLMatrix const ChLMatrix::operator - (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out -= _mat;
	return out;
}

ChLMatrix& ChLMatrix::operator *= (const ChLMatrix& _mat)
{
	m.Mul(_mat.m);
	return *this;
}

ChLMatrix const ChLMatrix::operator * (const ChLMatrix& _mat)const
{
	ChLMatrix out = *this;
	out *= _mat;
	return out;
}

ChLMatrix& ChLMatrix::operator /= (const ChLMatrix& _mat)
{
	m.Div(_mat.m);
	return *this;
}

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

void ChLMatrix::SetPosition(const ChVec3& _vec)
{
	SetPosition(_vec.x, _vec.y, _vec.z);
}

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

void ChLMatrix::SetScalling(
	const ChVec3& _vec,
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

ChVec3 ChLMatrix::GetPosition()const
{
	return ChVec3(l_41, l_42, l_43);
}

ChQua ChLMatrix::GetRotation(const unsigned long _digit)const
{
	ChQua res;
	res.SetRotationLMatrix(*this);
	return res;

}

ChVec3 ChLMatrix::GetScalling(const unsigned long _digit)const
{
	return ChVec3(m[0].GetLen(_digit), m[1].GetLen(_digit), m[2].GetLen(_digit));
}

ChVec3 ChLMatrix::GetXAxisDirection()const
{
	ChVec3 res;
	res.val.Set(m[0]);
	return res;
}

ChVec3 ChLMatrix::GetYAxisDirection()const
{
	ChVec3 res;
	res.val.Set(m[1]);
	return res;
}

ChVec3 ChLMatrix::GetZAxisDirection()const
{
	ChVec3 res;
	res.val.Set(m[2]);
	return res;
}

ChVec4 ChLMatrix::Transform(const ChVec4& _base)const
{
	ChVec4 out;

	out = _base;
	out.w = 1.0f;
	out.val = m.HorizontalMul(out.val);

	return out;
}

ChVec4 ChLMatrix::TransformCoord(const ChVec4& _base)const
{
	ChLMatrix tmp = *this;

	tmp.l_41 = 0.0f;
	tmp.l_42 = 0.0f;
	tmp.l_43 = 0.0f;

	return tmp.Transform(_base);
}

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




ChRMatrix& ChRMatrix::operator =(const ChRMatrix& _mat)
{
	if (this == &_mat)return *this;
	m.Set(_mat.m);
	return *this;
}

ChRMatrix& ChRMatrix::operator += (const ChRMatrix& _mat)
{
	m.Add(_mat.m);
	return *this;
}

ChRMatrix const ChRMatrix::operator + (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out += _mat;
	return out;
}

ChRMatrix& ChRMatrix::operator -= (const ChRMatrix& _mat)
{
	m.Sub(_mat.m);
	return *this;
}

ChRMatrix const ChRMatrix::operator - (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out -= _mat;
	return out;
}

ChRMatrix& ChRMatrix::operator *= (const ChRMatrix& _mat)
{
	m.Mul(_mat.m);
	return *this;
}

ChRMatrix const ChRMatrix::operator * (const ChRMatrix& _mat)const
{
	ChRMatrix out = *this;
	out *= _mat;
	return out;
}

ChRMatrix& ChRMatrix::operator /= (const ChRMatrix& _mat)
{
	m.Div(_mat.m);
	return *this;
}

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

void ChRMatrix::SetPosition(const ChVec3& _vec)
{
	SetPosition(_vec.x, _vec.y, _vec.z);
}

void ChRMatrix::SetPosition(const float _x, const float _y, const float _z)
{
	r_41 = _x;
	r_42 = _y;
	r_43 = _z;
}

void ChRMatrix::SetRotation(const ChQua& _qua, const unsigned long _digit)
{

}

void ChRMatrix::SetScalling(
	const ChVec3& _vec,
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

ChVec3 ChRMatrix::GetPosition()const
{
	return ChVec3(r_41, r_42, r_43);
}

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

ChVec3 ChRMatrix::GetXAxisDirection()const
{
	ChVec3 res = ChVec3(m[0][0], m[1][0], m[2][0]);
	return res;
}

ChVec3 ChRMatrix::GetYAxisDirection()const
{
	ChVec3 res = ChVec3(m[0][1], m[1][1], m[2][1]);
	return res;
}

ChVec3 ChRMatrix::GetZAxisDirection()const
{
	ChVec3 res = ChVec3(m[0][2], m[1][2], m[2][2]);
	return res;
}

ChVec4 ChRMatrix::Transform(const ChVec4 _Base)const
{
	ChVec4 out;

	out = _Base;
	out.w = 1.0f;
	out.val = m.VerticalMul(out.val);

	return out;
}

ChVec4 ChRMatrix::TransformCoord(const ChVec4 _Base)const
{
	ChRMatrix tmp = *this;

	tmp.r_41 = 0.0f;
	tmp.r_42 = 0.0f;
	tmp.r_43 = 0.0f;

	return tmp.Transform(_Base);
}

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



ChUIMatrix& ChUIMatrix::operator =(const ChUIMatrix _mat)
{
	m.Set(_mat.m);
	return *this;
}



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
