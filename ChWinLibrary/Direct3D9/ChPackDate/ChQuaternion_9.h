#ifndef Ch_D3D9_Qua_h
#define Ch_D3D9_Qua_h

//D3DXQUATERNIONをパック化したクラス//
typedef class ChQuaternion_9 :public D3DXQUATERNION
{
public:

	operator D3DXVECTOR3()
	{
		D3DXVECTOR3 tmpVec;

		D3DXMATRIX tmpMat;

		D3DXMatrixRotationQuaternion(&tmpMat, this);

		auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		D3DXVec3TransformNormal(&tmpVec, &tmp, &tmpMat);

		return tmpVec;
	}

	operator D3DXMATRIX()
	{
		D3DXMATRIX tmpMat;

		D3DXMatrixRotationQuaternion(&tmpMat, this);

		return tmpMat;
	}

	ChQuaternion_9&operator=(const D3DXQUATERNION& _cm)
	{
		if (this == &_cm)return *this;
		D3DXQUATERNION::operator =(_cm);
		return *this;
	}

	ChQuaternion_9&operator = (const D3DXMATRIX& _cm)
	{
		D3DXQuaternionRotationMatrix(this, &_cm);

		return *this;
	}

	ChQuaternion_9&operator =(const D3DXVECTOR3& _cm)
	{
		D3DXVECTOR3 tmpVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 tmpVec2 = _cm;

		D3DXVec3Normalize(&tmpVec, &tmpVec);
		D3DXVec3Normalize(&tmpVec2, &tmpVec2);

		float tmpDot = D3DXVec3Dot(&tmpVec, &tmpVec2);

		D3DXVec3Cross(&tmpVec, &tmpVec, &tmpVec2);

		D3DXQuaternionRotationAxis(this, &tmpVec, tmpDot);

		return *this;

	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer

	ChQuaternion_9(D3DXQUATERNION &_cm) :D3DXQUATERNION(_cm) {};

	ChQuaternion_9()
	{
		Identity();
	}

	ChQuaternion_9(const D3DXMATRIX& _cm)
	{
		D3DXQuaternionRotationMatrix(this, &_cm);

	}

	ChQuaternion_9(const D3DXVECTOR3& _cm)
	{
		D3DXVECTOR3 tmpVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 tmpVec2 = _cm;

		D3DXVec3Normalize(&tmpVec, &tmpVec);
		D3DXVec3Normalize(&tmpVec2, &tmpVec2);

		float tmpDot = D3DXVec3Dot(&tmpVec, &tmpVec2);

		D3DXVec3Cross(&tmpVec, &tmpVec, &tmpVec2);

		D3DXQuaternionRotationAxis(this, &tmpVec, tmpDot);

	}

	ChQuaternion_9(
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
	
	inline void RotYPR(const float _x, const float _y, const float _z)
	{
		D3DXQuaternionRotationYawPitchRoll(
			this
			, D3DXToRadian(_y)
			, D3DXToRadian(_x)
			, D3DXToRadian(_z));
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const D3DXVECTOR3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotAxis(const D3DXVECTOR3 *_vec,const float _ang)
	{
		D3DXQuaternionRotationAxis(
			this
			, _vec
			, D3DXToRadian(_ang));
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotMat(const D3DXMATRIX *_mat)
	{
		D3DXQuaternionRotationMatrix(this, _mat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Lerp(
		const D3DXQUATERNION& _sQua
		, const D3DXQUATERNION& _eQua
		, const float _nowTime)
	{
		D3DXQuaternionSlerp(this, &_sQua, &_eQua, _nowTime);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Identity()
	{
		D3DXQuaternionIdentity(this);
	}

private:

}ChQua_9;

#endif