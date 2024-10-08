#ifndef Ch_D3D9_vec3_h
#define Ch_D3D9_Vec3_h

//パック化したD3DXVECTOR3型//
typedef class ChVector3_9 :public D3DXVECTOR3
{
public://Operator Functions//

	ChVector3_9& operator=(const D3DXVECTOR3& _cm);

	ChVector3_9& operator = (const D3DXQUATERNION& _cm);

	ChVector3_9& operator =(const D3DXMATRIX& _mat);

public://ConstructerDestructer//

	inline ChVector3_9(const D3DXVECTOR3& _cm) :D3DXVECTOR3(_cm){}

	inline ChVector3_9() { Set0Param(); }

	inline ChVector3_9(const D3DXMATRIX& _mat) { *this = _mat; }

	ChVector3_9(const D3DXQUATERNION& _qua) { *this = _qua; }

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

public://GetFunction//

	float GetLen(const D3DXVECTOR3& _vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	float GetRadian(const D3DXVECTOR3& _vec);

	float GetDegree(const D3DXVECTOR3& _vec);

public://SetFunction//

	void Set0Param();

public://Other Functions//

	bool CheckNormals();

	bool CheckAll0();

	void Move(const float _x, const float _y, const float _z);

	void Move2D(const D3DXVECTOR3* _vec);

	void MatPos(const D3DXMATRIX& _mat, const D3DXVECTOR3& _vec);

	void MatNormal(const D3DXMATRIX& _mat, const D3DXVECTOR3& _vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	void Normalize();

	void Lerp(
		const D3DXVECTOR3& _sVec,
		const D3DXVECTOR3& _eVec,
		const float _nowTime);

	void CrossVec(const D3DXVECTOR3& _vec1, const D3DXVECTOR3& _vec2);

	float DotVec(const D3DXVECTOR3& _vec);

}ChVec3_9;



#endif