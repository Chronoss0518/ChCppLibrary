#ifndef Ch_D3D9_vec3_h
#define Ch_D3D9_Vec3_h

//ƒpƒbƒN‰»‚µ‚½D3DXVECTOR3Œ^//
typedef class ChVector3_9 :public D3DXVECTOR3
{
public:

	ChVector3_9&operator=(const D3DXVECTOR3& _cm)
	{
		x = _cm.x;
		y = _cm.y;
		z = _cm.z;

		return *this;
	}

	ChVector3_9&operator = (const D3DXQUATERNION& _cm)
	{
		D3DXMATRIX tmpMat;

		D3DXMatrixRotationQuaternion(&tmpMat, &_cm);

		auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		D3DXVec3TransformNormal(this, &tmp, &tmpMat);

		return *this;
	}

	ChVector3_9&operator =(const D3DXMATRIX& _mat)
	{
		x = _mat._41;
		y = _mat._42;
		z = _mat._43;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChVector3_9(const D3DXVECTOR3&_cm)
	{
		*this = _cm;
	}

	ChVector3_9()
	{
		Set0Param();
	}

	ChVector3_9(const D3DXMATRIX& _mat)
	{
		*this = _mat;
	}

	ChVector3_9(const D3DXQUATERNION& _qua)
	{
		*this = _qua;
	}

	ChVector3_9(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	ChVector3_9(const float _num)
	{
		x = _num;
		y = _num;
		z = _num;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	inline float GetLen(const D3DXVECTOR3& _vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		ChVector3_9 tmpVec;
		tmpVec = *this - _vec;

		return D3DXVec3Length(&tmpVec);
	}

	inline float GetRadian(const D3DXVECTOR3& _vec)
	{
		ChVector3_9 tmpVec1, tmpVec2;
		tmpVec1 = *this;
		tmpVec2 = _vec;
		tmpVec1.Normalize();
		tmpVec2.Normalize();

		return acosf(D3DXVec3Dot(&tmpVec1, &tmpVec2));
	}

	inline float GetDegree(const D3DXVECTOR3& _vec)
	{
		ChVector3_9 tmpVec1, tmpVec2;

		tmpVec1 = *this;
		tmpVec2 = _vec;

		tmpVec1.Normalize();
		tmpVec2.Normalize();

		return D3DXToDegree(acosf(D3DXVec3Dot(&tmpVec1, &tmpVec2)));
	}

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	inline void Set0Param()
	{
		*this = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline ChStd::Bool CheckNormals() {

		if (fabsf(this->x) + fabsf(this->y) + fabsf(this->z) == 1.0f)return true;
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline ChStd::Bool CheckAll0() {

		if (fabsf(this->x) == 0.0f
			&& fabsf(this->y) == 0.0f
			&& fabsf(this->z) == 0.0f)return true;

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move(const float _x, const float _y, const float _z)
	{
		*this += D3DXVECTOR3(_x, _y, _z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move2D(const D3DXVECTOR3 *_vec)
	{
		D3DXVECTOR3 tmpVec = *_vec;

		tmpVec.x = 0.0f;
		tmpVec.y = 0.0f;

		*this += (*_vec - tmpVec);
	}

	///////////////////////////////////////////////////////////////////////////////////


	inline void MatPos(const D3DXMATRIX& _mat, const D3DXVECTOR3& _vec)
	{
		D3DXVec3TransformCoord(this, &_vec, &_mat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void MatNormal(const D3DXMATRIX& _mat, const D3DXVECTOR3& _vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f))
	{
		D3DXVec3TransformNormal(this, &_vec, &_mat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Normalize()
	{
		if (CheckNormals())return;
		float tmpLen = std::abs(this->x) + std::abs(this->y) + std::abs(this->z);
		if (tmpLen > 0.0f)*this /= tmpLen;
		else *this = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Lerp(
		const D3DXVECTOR3& _sVec
		,const D3DXVECTOR3& _eVec
		,const float _nowTime)
	{
		D3DXVec3Lerp(this, &_sVec, &_eVec, _nowTime);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void CrossVec(const D3DXVECTOR3& _vec1, const D3DXVECTOR3& _vec2)
	{
		D3DXVec3Cross(this, &_vec1, &_vec2);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline float DotVec(const D3DXVECTOR3& _vec)
	{
		return D3DXVec3Dot(&_vec, this);
	}

	///////////////////////////////////////////////////////////////////////////////////


}ChVec3_9;



#endif