#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include"../../BaseIncluder/ChD3D11I.h"

#include"ChQuaternion_11.h"


///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion_11 operator//
///////////////////////////////////////////////////////////////////////////////////

ChQuaternion_11& ChQuaternion_11::operator=(const DirectX::XMFLOAT4& _cm)
{
	x = _cm.x;
	y = _cm.y;
	z = _cm.z;
	return *this;
}

ChQuaternion_11& ChQuaternion_11::operator+=(const DirectX::XMFLOAT4& _cm)
{
	x += _cm.x;
	y += _cm.y;
	z += _cm.z;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator+(const DirectX::XMFLOAT4& _cm)const
{

	ChQuaternion_11 tmp;
	tmp = *this;
	tmp += _cm;

	return tmp;
}

ChQuaternion_11& ChQuaternion_11::operator-=(const DirectX::XMFLOAT4& _cm)
{
	x -= _cm.x;
	y -= _cm.y;
	z -= _cm.z;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator-(const DirectX::XMFLOAT4& _cm)const
{
	ChQuaternion_11 tmp;
	tmp = *this;
	tmp -= _cm;

	return tmp;
}

ChQuaternion_11& ChQuaternion_11::operator*=(const DirectX::XMFLOAT4& _cm)
{
	*this = *this * _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator*(const DirectX::XMFLOAT4& _cm)const
{
	DirectX::XMVECTOR tmpVec;
	ChQuaternion_11 tmpQua;

	tmpVec = DirectX::XMLoadFloat4(&_cm);

	tmpVec = tmpVec * (DirectX::XMVECTOR)*this;

	tmpQua = tmpVec;

	return tmpQua;
}

ChQuaternion_11& ChQuaternion_11::operator/=(const DirectX::XMFLOAT4& _cm)
{

	*this = *this / _cm;

	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator/(const DirectX::XMFLOAT4& _cm)const
{

	DirectX::XMVECTOR tmpVec;
	ChQuaternion_11 tmpQua;

	tmpVec = DirectX::XMLoadFloat4(&_cm);

	tmpVec = DirectX::XMQuaternionInverse(tmpVec);

	tmpVec = tmpVec * (DirectX::XMVECTOR)*this;

	tmpQua = tmpVec;

	return tmpQua;
}

ChQuaternion_11& ChQuaternion_11::operator=(const float& _cm)
{

	x = _cm;
	y = _cm;
	z = _cm;
	return *this;
}

ChQuaternion_11& ChQuaternion_11::operator+=(const float& _cm)
{

	x += _cm;
	y += _cm;
	z += _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator+(const float& _cm)const
{
	ChQuaternion_11 tmp;

	tmp = *this;
	tmp += _cm;
	return tmp;

}

ChQuaternion_11& ChQuaternion_11::operator-=(const float& _cm)
{

	x -= _cm;
	y -= _cm;
	z -= _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator-(const float& _cm)const
{

	ChQuaternion_11 tmp;

	tmp = *this;
	tmp -= _cm;
	return tmp;

}

ChQuaternion_11& ChQuaternion_11::operator*=(const float& _cm)
{

	x *= _cm;
	y *= _cm;
	z *= _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator*(const float& _cm)const
{

	ChQuaternion_11 tmp;

	tmp = *this;
	tmp *= _cm;
	return tmp;

}

ChQuaternion_11& ChQuaternion_11::operator/=(const float& _cm)
{

	if (_cm > 0.0f)x /= _cm;
	if (_cm > 0.0f)y /= _cm;
	if (_cm > 0.0f)z /= _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator/(const float& _cm)const
{

	ChQuaternion_11 tmp;

	tmp = *this;
	tmp /= _cm;
	return tmp;

}

ChQuaternion_11& ChQuaternion_11::operator=(const DirectX::XMVECTOR& _cm)
{
	DirectX::XMStoreFloat4(this, _cm);
	return *this;
}

ChQuaternion_11::operator DirectX::XMVECTOR()const
{
	DirectX::XMVECTOR tmp;

	tmp = DirectX::XMLoadFloat4(this);

	return tmp;
}

ChQuaternion_11::operator DirectX::XMFLOAT4()const
{

	DirectX::XMFLOAT4 tmpVec;

	tmpVec.x = x;
	tmpVec.y = y;
	tmpVec.z = z;

	return tmpVec;

}

ChQuaternion_11& ChQuaternion_11::operator = (const DirectX::XMFLOAT3&  _vec)
{

	DirectX::XMVECTOR tmpVec,tmpVec2;
	DirectX::XMVECTOR dot;

	{
		auto tmp = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
		tmpVec2 = DirectX::XMLoadFloat3(&tmp);
	}


	tmpVec = DirectX::XMLoadFloat3(&_vec);

	tmpVec = DirectX::XMVector3Normalize(tmpVec);

	dot = DirectX::XMVector3Dot(tmpVec, tmpVec2);

	tmpVec = DirectX::XMVector3Cross(tmpVec, tmpVec2);

	tmpVec = DirectX::XMVector3Normalize(tmpVec);

	{
		float tmpDot;
		DirectX::XMStoreFloat(&tmpDot, dot);
		tmpVec = DirectX::XMQuaternionRotationAxis(tmpVec, tmpDot);

	}

	*this = tmpVec;

	return *this;
}

ChQuaternion_11& ChQuaternion_11::operator =(const DirectX::XMFLOAT4X4& _mat)
{
	

	DirectX::XMVECTOR tmpVec;
	DirectX::XMMATRIX tmpMat;


	tmpMat = DirectX::XMLoadFloat4x4(&_mat);

	tmpVec = DirectX::XMQuaternionRotationMatrix(tmpMat);

	*this = tmpVec;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion_11 ÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotYPR(const float _x, const float _y, const float _z)
{


	DirectX::XMVECTOR tmpVec;

	tmpVec = DirectX::XMQuaternionRotationRollPitchYaw(y, _x, _z);

	*this = tmpVec;


}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotLookAt(
	const DirectX::XMFLOAT3& _Pos
	, const DirectX::XMFLOAT3& _BasePos)
{
	ChVec3 tmp = _Pos;

	tmp -= _BasePos;

	*this = (DirectX::XMFLOAT3)(tmp);


}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotAxis(const DirectX::XMFLOAT3& _vec, const float _ang)
{

	DirectX::XMVECTOR tmpVec;

	tmpVec = DirectX::XMLoadFloat3(&_vec);


	tmpVec = DirectX::XMQuaternionRotationAxis(tmpVec, _ang);

	*this = tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotMat(const DirectX::XMFLOAT4X4& _mat)
{

	DirectX::XMVECTOR tmpVec;
	DirectX::XMMATRIX tmpMat;

	tmpMat = DirectX::XMLoadFloat4x4(&_mat);

	tmpVec = DirectX::XMQuaternionRotationMatrix(tmpMat);

	*this = tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::Lerp(
	const ChQuaternion_11& _sVec
	, const ChQuaternion_11& _eVec
	, const float _nowTime)
{
	ChQuaternion_11 tmp;
	tmp = _eVec - _sVec;

	tmp *= _nowTime;

	tmp = _eVec + tmp;

	*this = tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::Identity()
{
	*this = DirectX::XMQuaternionIdentity();
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::Inverse(const ChQuaternion_11& _qua)
{
	*this = DirectX::XMQuaternionInverse(_qua);
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion Operator//
///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const DirectX::XMFLOAT4()const
{
	DirectX::XMFLOAT4 tmpVec;
	tmpVec.x = x;
	tmpVec.y = y;
	tmpVec.z = z;
	tmpVec.w = w;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const DirectX::XMFLOAT4*()const
{
	return reinterpret_cast<DirectX::XMFLOAT4*>(const_cast<ChQua*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const DirectX::XMFLOAT4& _qua)
{
	x = _qua.x;
	y = _qua.y;
	z = _qua.z;
	w = _qua.w;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const DirectX::XMFLOAT3& _vec)
{
	ChQuaternion_11 tmp;
	tmp = _vec;

	*this = tmp;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const DirectX::XMFLOAT4X4& _mat)
{
	ChQuaternion_11 tmp;
	tmp = _mat;

	*this = tmp;

	return *this;

}
