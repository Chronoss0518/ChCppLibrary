#ifndef Ch_D3D11_ChMat_h
#define Ch_D3D11_ChMat_h

#ifdef CRT

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<DirectXColors.h>
#include<DirectXMath.h>
#include<DirectXCollision.h>


//D3DXMATRIXをパック化したクラス//
typedef class ChMatrix_11 :public DirectX::XMFLOAT4X4
{
public://Operator Functions//

	ChMatrix_11&operator=(const DirectX::XMFLOAT4X4& _cm);

	ChMatrix_11&operator+=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator+(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator-=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator-(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator*=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator*(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator/=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator/(const DirectX::XMFLOAT4X4& _cm)const;

	ChMatrix_11&operator=(const float& _cm);
	ChMatrix_11&operator*=(const float& _cm);
	ChMatrix_11 operator*(const float& _cm)const;
	ChMatrix_11&operator/=(const float& _cm);
	ChMatrix_11 operator/(const float& _cm)const;

	ChMatrix_11&operator=(const DirectX::XMMATRIX& _cm);

	operator DirectX::XMMATRIX()const;

	operator DirectX::XMFLOAT4X4()const;

	ChMatrix_11&operator = (const DirectX::XMFLOAT3& _vec);

	ChMatrix_11&operator =(const DirectX::XMFLOAT4& _qua);

public://Constructer Destructer//

	inline ChMatrix_11(const DirectX::XMFLOAT4X4& _cm) : DirectX::XMFLOAT4X4(_cm) {}

	inline ChMatrix_11(const DirectX::XMMATRIX& _cm) { *this = _cm; }

	inline ChMatrix_11() { Identity(); }

	inline ChMatrix_11(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChMatrix_11(const DirectX::XMFLOAT4& _qua) { *this = _qua; }

public://Set Functions//

	void SetPosition(const DirectX::XMFLOAT3& _pos);
	
	void SetRotation(const DirectX::XMFLOAT3& _rot);
	
	void SetScaleSize(const DirectX::XMFLOAT3& _sca);

public://Get Functions//

	DirectX::XMFLOAT3 GetPosition()const;

	DirectX::XMFLOAT4 GetRotation()const;

	DirectX::XMFLOAT3 GetScaleSize()const;

public://Other Functions//

	inline void Identity() { *this = DirectX::XMMatrixIdentity(); }

	inline void Inverse() { Inverse(*this); }

	void Inverse(const DirectX::XMFLOAT4X4& _mat);

	void RotYPR(const float _x, const float _y, const float _z);

	void RotYPR(const DirectX::XMFLOAT3& _vec);

	void RotQua(const DirectX::XMFLOAT4& _qua);

	void RotQua(const float _x, const float _y, const float _z);

	void RotVec(const DirectX::XMFLOAT3& _vec);

	void RotAxis(const DirectX::XMFLOAT3& _vec, const float _Ang);

	inline void Trans(const float _x, const float _y, const float _z) { *this = DirectX::XMMatrixTranslation(_x, _y, _z); }

	inline void Trans(const DirectX::XMFLOAT3& _vec) { *this = DirectX::XMMatrixTranslation(_vec.x, _vec.y, _vec.z); }

	inline void VectorMove(const DirectX::XMFLOAT3& _vec)
	{
		this->_41 += _vec.x;
		this->_42 += _vec.y;
		this->_43 += _vec.z;
	}

	inline void Move(const float _x, const float _y, const float _z)
	{
		ChMatrix_11 tmpMat;
		tmpMat.Trans(_x, _y, _z);
		*this = tmpMat * *this;
	}

	void Scaling(
		const float _x,
		const float _y,
		const float _z);

	inline void Scaling(const DirectX::XMFLOAT3& _tmpVec) { Scaling(_tmpVec.x, _tmpVec.y, _tmpVec.z); }

	inline void Scaling(const float _scl) { Scaling(_scl, _scl, _scl); }

	void CreateViewMat(const ChVec3& _pos,const ChVec3& _dir,const ChVec3& _up);

	void CreateViewMatLookTarget(const ChVec3& _pos, const ChVec3& _targetPos, const ChVec3& _up);

	//透視投影射影行列を作成//
	inline void CreateProjectionMat(
		const float _lookAngleRadian,
		const float _windWidth,
		const float _windHeight,
		const float _nearZ,
		const float _farZ)
	{
		*this = DirectX::XMMatrixPerspectiveFovLH(
			_lookAngleRadian
			, _windWidth/ _windHeight
			, _nearZ
			, _farZ);
	}

	//直交射影行列を作成//
	inline void CreateProjectionMat(
		const float _windWidth,
		const float _windHeight,
		const float _nearZ,
		const float _farZ)
	{
		*this = DirectX::XMMatrixOrthographicLH(
			_windWidth,
			_windHeight,
			_nearZ,
			_farZ);
	}

	//座標系変換//
	inline ChMatrix_11 Transpose() const
	{
		ChMatrix_11 tmp;

		tmp = DirectX::XMMatrixTranspose(*this);

		return tmp;
	}

private:

}ChMat_11;


ChMatrix_11& ChMatrix_11::operator=(const DirectX::XMFLOAT4X4& _cm)
{
	if (this == &_cm)return *this;
	DirectX::XMFLOAT4X4::operator=(_cm);
	return *this;
}

ChMatrix_11& ChMatrix_11::operator+=(const DirectX::XMFLOAT4X4& _cm)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] += _cm.m[i][j];
		}
	}
	return *this;
}

ChMatrix_11 ChMatrix_11::operator+(const DirectX::XMFLOAT4X4& _cm)const
{
	ChMatrix_11 out = *this;
	out += _cm;
	return out;
}

ChMatrix_11& ChMatrix_11::operator-=(const DirectX::XMFLOAT4X4& _cm)
{

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] -= _cm.m[i][j];
		}
	}
	return *this;
}

ChMatrix_11 ChMatrix_11::operator-(const DirectX::XMFLOAT4X4& _cm)const
{
	ChMatrix_11 out = *this;
	out -= _cm;
	return out;
}

ChMatrix_11& ChMatrix_11::operator*=(const DirectX::XMFLOAT4X4& _cm)
{
	DirectX::XMMATRIX tmpMat1, tmpMat2;

	tmpMat1 = DirectX::XMLoadFloat4x4(&_cm);
	tmpMat2 = *this;
	*this = DirectX::XMMatrixMultiply(tmpMat1, tmpMat2);

	return *this;
}

ChMatrix_11 ChMatrix_11::operator*(const DirectX::XMFLOAT4X4& _cm)const
{
	ChMatrix_11 out = *this;
	out *= _cm;
	return out;
}

ChMatrix_11& ChMatrix_11::operator/=(const DirectX::XMFLOAT4X4& _cm)
{
	DirectX::XMMATRIX tmpMat1, tmpMat2;

	tmpMat1 = DirectX::XMLoadFloat4x4(&_cm);
	tmpMat2 = *this;
	tmpMat2 = DirectX::XMMatrixInverse(nullptr, tmpMat2);

	*this = tmpMat2 * tmpMat1;
	return *this;
}

ChMatrix_11 ChMatrix_11::operator/(const DirectX::XMFLOAT4X4& _cm)const
{
	ChMatrix_11 out = *this;
	out /= _cm;
	return out;
}

ChMatrix_11& ChMatrix_11::operator=(const float& _num)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _num;
		}
	}
	return *this;
}

ChMatrix_11& ChMatrix_11::operator*=(const float& _num)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] *= _num;
		}
	}
	return *this;
}

ChMatrix_11 ChMatrix_11::ChMatrix_11::operator*(const float& _num)const
{
	ChMatrix_11 out = *this;
	out *= _num;
	return out;
}

ChMatrix_11& ChMatrix_11::ChMatrix_11::operator/=(const float& _num)
{
	if (_num == 0.0f)return *this;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			if (_num == 0.0f)continue;
			m[i][j] /= _num;
		}
	}
	return *this;
}

ChMatrix_11 ChMatrix_11::ChMatrix_11::operator/(const float& _num)const
{
	ChMatrix_11 out = *this;
	out /= _num;
	return out;
}

ChMatrix_11& ChMatrix_11::operator=(const DirectX::XMMATRIX& _mat)
{
	DirectX::XMStoreFloat4x4(this, _mat);
	return *this;
}

ChMatrix_11::operator DirectX::XMMATRIX()const
{
	DirectX::XMMATRIX out;
	out = DirectX::XMLoadFloat4x4(this);
	return out;
}

ChMatrix_11::operator DirectX::XMFLOAT4X4()const
{
	DirectX::XMFLOAT4X4 tmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			tmpMat.m[i][j] = m[i][j];
		}
	}
	return tmpMat;
}

ChMatrix_11& ChMatrix_11::operator = (const DirectX::XMFLOAT3& _vec)
{
	*this = DirectX::XMMatrixTranslation(_vec.x, _vec.y, _vec.z);
	return *this;
}

ChMatrix_11& ChMatrix_11::operator =(const DirectX::XMFLOAT4& _qua)
{
	DirectX::XMVECTOR tmpVec;
	tmpVec = DirectX::XMLoadFloat4(&_qua);
	*this = DirectX::XMMatrixRotationQuaternion(tmpVec);

	return *this;
}

void ChMatrix_11::SetPosition(const DirectX::XMFLOAT3& _pos)
{
	_41 = _pos.x;
	_42 = _pos.y;
	_43 = _pos.z;
}

void ChMatrix_11::SetRotation(const DirectX::XMFLOAT3& _rot)
{

	RotYPR(_rot);
}

void ChMatrix_11::SetScaleSize(const DirectX::XMFLOAT3& _sca)
{
	Scaling(_sca);
}

DirectX::XMFLOAT3 ChMatrix_11::GetPosition()const
{
	DirectX::XMFLOAT3 tmpVec;
	tmpVec.x = _41;
	tmpVec.y = _42;
	tmpVec.z = _43;
	return tmpVec;
}

DirectX::XMFLOAT4 ChMatrix_11::GetRotation()const
{
	DirectX::XMFLOAT4 tmpQua;
	DirectX::XMVECTOR tmpVec;

	tmpVec = DirectX::XMQuaternionRotationMatrix(*this);
	DirectX::XMStoreFloat4(&tmpQua, tmpVec);
	return tmpQua;
}

DirectX::XMFLOAT3 ChMatrix_11::GetScaleSize()const
{
	ChMatrix_11 tmpMat;
	DirectX::XMVECTOR tmpQua;
	tmpQua = DirectX::XMQuaternionRotationMatrix(*this);
	tmpMat = DirectX::XMMatrixRotationQuaternion(tmpQua);
	tmpMat.Inverse();
	tmpMat = tmpMat * *this;
	return DirectX::XMFLOAT3(tmpMat._11, tmpMat._22, tmpMat._33);
}

void ChMatrix_11::Inverse(const DirectX::XMFLOAT4X4& _mat)
{
	DirectX::XMMATRIX tmpMat;
	tmpMat = DirectX::XMLoadFloat4x4(&_mat);
	*this = DirectX::XMMatrixInverse(nullptr, tmpMat);
}

void ChMatrix_11::RotYPR(
	const float _x,
	const float _y,
	const float _z)
{
	ChMatrix_11 tmpMat;

	tmpMat = DirectX::XMMatrixRotationRollPitchYaw(
		ChMath::ToRadian(_y),
		ChMath::ToRadian(_x),
		ChMath::ToRadian(_z));

	*this = tmpMat * *this;
}

void ChMatrix_11::RotYPR(const DirectX::XMFLOAT3& _vec)
{
	ChMatrix_11 tmpMat;

	tmpMat = DirectX::XMMatrixRotationRollPitchYaw(
		ChMath::ToRadian(_vec.x),
		ChMath::ToRadian(_vec.y),
		ChMath::ToRadian(_vec.z));

	*this = tmpMat * *this;
}

void ChMatrix_11::RotQua(const DirectX::XMFLOAT4& _qua)
{
	ChMatrix_11 tmpMat;
	{
		DirectX::XMVECTOR tmpVec;
		tmpVec = DirectX::XMLoadFloat4(&_qua);
		tmpMat = DirectX::XMMatrixRotationQuaternion(tmpVec);
	}
	*this = tmpMat * *this;
}

void ChMatrix_11::RotQua(
	const float _x,
	const float _y,
	const float _z)
{
	ChMatrix_11 tmpMat;
	DirectX::XMVECTOR tmpVec;
	tmpVec = DirectX::XMQuaternionRotationRollPitchYaw(_x, _y, _z);
	tmpMat = DirectX::XMMatrixRotationQuaternion(tmpVec);
	*this = tmpMat * *this;
}

void ChMatrix_11::RotVec(const DirectX::XMFLOAT3& _vec)
{
	DirectX::XMVECTOR tmpVec, tmpBase;
	tmpVec = DirectX::XMLoadFloat3(&_vec);
	float tmpRot;
	{
		auto tmp = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
		tmpBase = DirectX::XMLoadFloat3(&tmp);
	}

	tmpVec = DirectX::XMVector3Normalize(tmpVec);
	{
		DirectX::XMVECTOR tmpDot;
		tmpDot = DirectX::XMVector3Dot(tmpVec, tmpBase);
		DirectX::XMStoreFloat(&tmpRot, tmpDot);
	}

	tmpVec = DirectX::XMVector3Cross(tmpVec, tmpBase);
	DirectX::XMFLOAT3 tmp;
	DirectX::XMStoreFloat3(&tmp, tmpVec);
	RotAxis(tmp, tmpRot);
}

void ChMatrix_11::RotAxis(
	const DirectX::XMFLOAT3& _vec,
	const float _ang)
{
	ChMatrix_11 tmpMat;
	DirectX::XMVECTOR tmpVec;
	tmpVec = DirectX::XMLoadFloat3(&_vec);
	tmpMat = DirectX::XMMatrixRotationAxis(tmpVec, (ChMath::ToRadian(_ang)));
	*this = tmpMat * *this;
}

void ChMatrix_11::Scaling(
	const float _x,
	const float _y,
	const float _z)
{
	ChMatrix_11 tmpMat;
	tmpMat = DirectX::XMMatrixScaling(_x, _y, _z);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////////
//ChMatrix operator
///////////////////////////////////////////////////////////////////////////////////////

ChLMatrix::operator const DirectX::XMFLOAT4X4()const
{
	ChMatrix_11 tmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			tmpMat.m[i][j] = m[i][j];
		}
	}
	return tmpMat;
}

ChLMatrix::operator const DirectX::XMFLOAT4X4* ()const
{
	return reinterpret_cast<DirectX::XMFLOAT4X4*>(const_cast<ChLMat*>(this));
}

ChLMatrix& ChLMatrix::operator= (const DirectX::XMFLOAT3& _vec)
{
	ChMat_11 tmpMat;
	tmpMat = _vec;
	*this = tmpMat;
	return *this;
}

ChLMatrix& ChLMatrix::operator= (const DirectX::XMFLOAT4& _qua)
{
	ChMat_11 tmpMat;
	tmpMat = _qua;
	*this = tmpMat;
	return *this;
}

ChLMatrix& ChLMatrix::operator= (const DirectX::XMFLOAT4X4& _mat)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _mat.m[i][j];
		}
	}
	return *this;
}

#include"ChSharedVectorMatrix_11.h"

#endif

#endif