#ifndef Ch_D3D11_Qua_h
#define Ch_D3D11_Qua_h

#ifdef CRT

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<DirectXColors.h>
#include<DirectXMath.h>
#include<DirectXCollision.h>

//D3DXQUATERNION���p�b�N�������N���X//
typedef class ChQuaternion_11 :public DirectX::XMFLOAT4
{
public:

	ChQuaternion_11&operator=(const DirectX::XMFLOAT4& _cm);

	ChQuaternion_11&operator+=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator+(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator-=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator-(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator*=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator*(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator/=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator/(const DirectX::XMFLOAT4& _cm)const;

	ChQuaternion_11&operator=(const DirectX::XMVECTOR& _cm);

	operator DirectX::XMVECTOR()const;

	ChQuaternion_11&operator = (const DirectX::XMFLOAT3& _vec);

	ChQuaternion_11&operator =(const DirectX::XMFLOAT4X4& _mat);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer

	ChQuaternion_11()
	{
		Identity();
	}

	ChQuaternion_11(const DirectX::XMFLOAT4& _cm) :DirectX::XMFLOAT4(_cm) {}

	ChQuaternion_11(const DirectX::XMFLOAT4X4& _cm)
	{
		*this = _cm;

	}

	ChQuaternion_11(const  DirectX::XMFLOAT3& _cm)
	{
		*this = _cm;

	}

	ChQuaternion_11(
		const float _x
		, const float _y
		, const float _z
		, const float _w = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	///////////////////////////////////////////////////////////////////////////////////
	
	void RotYPR(const float _x, const float _y, const float _z);

	inline void RotYPR(const ChVec3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	inline void RotYPR(const DirectX::XMFLOAT3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void RotLookAt(
		const DirectX::XMFLOAT3& _pos
		, const DirectX::XMFLOAT3& _basePos);

	///////////////////////////////////////////////////////////////////////////////////

	void RotAxis(const DirectX::XMFLOAT3& _vec, const float _ang);

	///////////////////////////////////////////////////////////////////////////////////

	void RotMat(const DirectX::XMFLOAT4X4& _mat);

	///////////////////////////////////////////////////////////////////////////////////

	void Lerp(
		const ChQuaternion_11& _sQua
		, const ChQuaternion_11& _eQua
		, const float _NowTime);

	///////////////////////////////////////////////////////////////////////////////////

	void Identity();

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{
		Inverse(*this);
	}

	void Inverse(const DirectX::XMFLOAT4& _qua)
	{
		ChQuaternion_11 tmpQua;
		tmpQua = _qua;
		Inverse(tmpQua);
	}

	void Inverse(const ChQuaternion_11& _qua);

private:

}ChQua_11;

ChQuaternion_11& ChQuaternion_11::operator=(const DirectX::XMFLOAT4& _cm)
{
	if (this == &_cm)return *this;
	DirectX::XMFLOAT4::operator=(_cm);
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
	ChQuaternion_11 tmpVec;
	tmpVec = _cm;
	*this = DirectX::XMQuaternionMultiply(tmpVec, *this);
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator*(const DirectX::XMFLOAT4& _cm)const
{
	ChQuaternion_11 out = *this;
	out *= _cm;
	return out;
}

ChQuaternion_11& ChQuaternion_11::operator/=(const DirectX::XMFLOAT4& _cm)
{

	ChQuaternion_11 tmpVec;
	tmpVec = _cm;
	*this = DirectX::XMQuaternionInverse(*this);
	*this = tmpVec * *this;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator/(const DirectX::XMFLOAT4& _cm)const
{
	ChQuaternion_11 out = *this;
	out /= _cm;
	return out;
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

ChQuaternion_11& ChQuaternion_11::operator = (const DirectX::XMFLOAT3& _vec)
{

	DirectX::XMVECTOR tmpVec, tmpVec2;
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

void ChQuaternion_11::RotYPR(const float _x, const float _y, const float _z)
{
	DirectX::XMVECTOR tmpVec;
	tmpVec = DirectX::XMQuaternionRotationRollPitchYaw(y, _x, _z);
	*this = tmpVec;
}

void ChQuaternion_11::RotMat(const DirectX::XMFLOAT4X4& _mat)
{
	DirectX::XMVECTOR tmpVec;
	DirectX::XMMATRIX tmpMat;
	tmpMat = DirectX::XMLoadFloat4x4(&_mat);
	tmpVec = DirectX::XMQuaternionRotationMatrix(tmpMat);
	*this = tmpVec;
}

void ChQuaternion_11::Lerp(
	const ChQuaternion_11& _sVec,
	const ChQuaternion_11& _eVec,
	const float _nowTime) {
	*this = DirectX::XMQuaternionSlerp(_sVec, _eVec, _nowTime);}

void ChQuaternion_11::Identity() { *this = DirectX::XMQuaternionIdentity(); }

void ChQuaternion_11::Inverse(const ChQuaternion_11& _qua) { *this = DirectX::XMQuaternionInverse(_qua); }

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

ChQua::operator const DirectX::XMFLOAT4* ()const { return reinterpret_cast<DirectX::XMFLOAT4*>(const_cast<ChQua*>(this)); }

ChQua& ChQua::operator= (const DirectX::XMFLOAT4& _qua)
{
	x = _qua.x;
	y = _qua.y;
	z = _qua.z;
	w = _qua.w;
	return *this;
}

ChQua& ChQua::operator= (const DirectX::XMFLOAT3& _vec)
{
	ChQuaternion_11 tmp;
	tmp = _vec;
	*this = tmp;
	return *this;
}

ChQua& ChQua::operator= (const DirectX::XMFLOAT4X4& _mat)
{
	ChQuaternion_11 tmp;
	tmp = _mat;
	*this = tmp;
	return *this;
}

#include"ChSharedVectorQuaternion.h"

#endif

#endif