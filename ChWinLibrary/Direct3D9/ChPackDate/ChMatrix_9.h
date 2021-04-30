#ifndef Ch_D3D9_ChMat_h
#define Ch_D3D9_ChMat_h

//D3DXMATRIXをパック化したクラス//
typedef class ChMatrix_9 :public D3DXMATRIX
{
public:

	operator D3DXVECTOR3()const
	{
		D3DXVECTOR3 tmpVec;

		tmpVec.x = _41;
		tmpVec.y = _42;
		tmpVec.z = _43;

		return tmpVec;
	}

	operator D3DXQUATERNION()const
	{
		D3DXQUATERNION tmpQua;

		D3DXQuaternionRotationMatrix(&tmpQua, this);

		return tmpQua;
	}

	ChMatrix_9&operator =(const D3DXMATRIX&_cm)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			for (unsigned j = 0; j < 4; j++)
			{
				m[i][j] = _cm.m[i][j];
			}
		}
		return *this;
	}

	D3DXMATRIX&operator = (const D3DXVECTOR3& _vec)
	{
		_41 = _vec.x;
		_42 = _vec.y;
		_43 = _vec.z;
		return *this;
	}

	D3DXMATRIX&operator = (const D3DXQUATERNION& _qua)
	{
		D3DXMatrixRotationQuaternion(this, &_qua);

		return *this;
	}

	D3DXMATRIX&operator *= (const D3DXMATRIX& _Mat) 
	{
		*this = _Mat * *this;
		return *this;
	}

	ChMatrix_9&operator *= (const D3DXVECTOR3& _vec)
	{
		_41 += _vec.x;
		_42 += _vec.y;
		_43 += _vec.z;
		return *this;
	}

	ChMatrix_9&operator *= (const D3DXQUATERNION& _qua)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixRotationQuaternion(&tmpMat, &_qua);

		*this = tmpMat * *this;

		return *this;
	}

	ChMatrix_9&operator *= (const float& _num)
	{
		_11 *= _num;
		_12 *= _num;
		_13 *= _num;
		_14 *= _num;
		_21 *= _num;
		_22 *= _num;
		_23 *= _num;
		_24 *= _num;
		_31 *= _num;
		_32 *= _num;
		_33 *= _num;
		_34 *= _num;
		_41 *= _num;
		_42 *= _num;
		_43 *= _num;
		_44 *= _num;

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChMatrix_9(D3DXMATRIX &_cm) :D3DXMATRIX(_cm) {};

	ChMatrix_9(const D3DXMATRIX &_cm)
	{
		*this = _cm;
	}

	ChMatrix_9()
	{
		Identity();
	}

	ChMatrix_9(const D3DXVECTOR3& _vec)
	{
		_41 = _vec.x;
		_42 = _vec.y;
		_43 = _vec.z;
	}

	ChMatrix_9(const D3DXQUATERNION& _qua)
	{
		D3DXMatrixRotationQuaternion(this, &_qua);
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//


	D3DXVECTOR3 GetPosition()
	{
		D3DXVECTOR3 tmpVec;
		tmpVec.x = _41;
		tmpVec.y = _42;
		tmpVec.z = _43;
		return tmpVec;
	}

	D3DXQUATERNION GetRotation()
	{
		D3DXQUATERNION tmpQua;
		D3DXQuaternionRotationMatrix(&tmpQua, this);
		return tmpQua;
	}

	D3DXVECTOR3 GetScaleSize()
	{
		D3DXMATRIX tmpMat;

		{
			D3DXQUATERNION tmpQua;

			D3DXQuaternionRotationMatrix(&tmpQua, this);

			D3DXMatrixRotationQuaternion(&tmpMat, &tmpQua);

		}

		D3DXMatrixInverse(&tmpMat, NULL, &tmpMat);

		tmpMat = tmpMat * *this;

		return D3DXVECTOR3(tmpMat._11, tmpMat._22, tmpMat._33);

	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Identity() { D3DXMatrixIdentity(this); }

	///////////////////////////////////////////////////////////////////////////////////

	inline void Inverse() 
	{
		D3DXMatrixInverse(this, NULL, this);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Inverse(const D3DXMATRIX& tmpMat)
	{
		D3DXMatrixInverse(this, NULL, &tmpMat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const float _x, const float _y, const float _z)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixRotationYawPitchRoll(&tmpMat, D3DXToRadian(_y), D3DXToRadian(_x), D3DXToRadian(_z));
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const D3DXVECTOR3& _vec)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixRotationYawPitchRoll(&tmpMat, D3DXToRadian(_vec.y), D3DXToRadian(_vec.x), D3DXToRadian(_vec.z)); 
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotQua(const D3DXQUATERNION& _qua)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixRotationQuaternion(&tmpMat, &_qua); 
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotQua(const float _x, const float _y, const float _z)
	{
		D3DXQUATERNION tmpQua;
		D3DXQuaternionRotationYawPitchRoll(&tmpQua, D3DXToRadian(_y), D3DXToRadian(_x), D3DXToRadian(_z));
		D3DXMATRIX tmpMat;
		D3DXMatrixRotationQuaternion(&tmpMat, &tmpQua);
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotVec(const D3DXVECTOR3& _vec)
	{
		D3DXVECTOR3 tmpCross ,tmpVec;
		tmpVec = _vec;
		float tmpRot;

		auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		D3DXVec3Normalize(&tmpVec, &tmpVec);
		D3DXVec3Cross(&tmpCross, &tmp, &tmpVec);
		tmpRot = D3DXVec3Dot(&tmpVec, &tmp);

		D3DXMATRIX tmpMat;
		D3DXMatrixRotationAxis(&tmpMat, &tmpCross, std::acos(tmpRot));
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotAxis(const D3DXVECTOR3& _vec,const float _Ang)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixRotationAxis(&tmpMat, &_vec, D3DXToRadian(_Ang));
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Trans(const float _x, const float _y, const float _z)
	{
		D3DXMatrixTranslation(this, _x, _y, _z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Trans(const D3DXVECTOR3& _vec)
	{
		D3DXMatrixTranslation(this, _vec.x, _vec.y, _vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void VectorMove(const D3DXVECTOR3& _vec)
	{
		this->_41 += _vec.x;
		this->_42 += _vec.y;
		this->_43 += _vec.z;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move(const float _x, const float _y, const float _z)
	{
		ChMatrix_9 tmpMat;
		tmpMat.Trans(_x, _y, _z);
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const float _x, const float _y, const float _z)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixScaling(&tmpMat, _x, _y, _z);
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const D3DXVECTOR3& _tmpVec)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixScaling(&tmpMat, _tmpVec.x, _tmpVec.y, _tmpVec.z);
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const float _scl)
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixScaling(&tmpMat, _scl, _scl, _scl);
		*this = tmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Clear0()
	{
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = 0.0f;
			}
		}
	}

private:

}ChMat_9;


#endif