#ifndef Ch_D3D9_ChMat_h
#define Ch_D3D9_ChMat_h

//D3DXMATRIXをパック化したクラス//
typedef class ChMatrix_9 :public D3DXMATRIX
{
public://Operator Functions//

	operator D3DXVECTOR3()const;

	operator D3DXQUATERNION()const;

	ChMatrix_9& operator =(const D3DXMATRIX& _cm);

	D3DXMATRIX& operator = (const D3DXVECTOR3& _vec);

	D3DXMATRIX& operator = (const D3DXQUATERNION& _qua);

	D3DXMATRIX& operator *= (const D3DXMATRIX& _mat);

	ChMatrix_9& operator *= (const D3DXVECTOR3& _vec);

	ChMatrix_9& operator *= (const D3DXQUATERNION& _qua);

public://ConstructerDestructer//

	ChMatrix_9(const D3DXMATRIX &_cm) :D3DXMATRIX(_cm) {};

	ChMatrix_9() { Identity(); }

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

public://GetFunction//

	D3DXVECTOR3 GetPosition();

	D3DXQUATERNION GetRotation();

	D3DXVECTOR3 GetScaleSize();

public://Other Functions//

	void Identity();

	void Inverse();

	void Inverse(const D3DXMATRIX& tmpMat);

	void RotYPR(const float _x, const float _y, const float _z);

	void RotYPR(const D3DXVECTOR3& _vec);

	void RotQua(const D3DXQUATERNION& _qua);

	void RotQua(const float _x, const float _y, const float _z);

	void RotVec(const D3DXVECTOR3& _vec);
	
	void RotAxis(const D3DXVECTOR3& _vec, const float _Ang);

	void Trans(const float _x, const float _y, const float _z);

	void Trans(const D3DXVECTOR3& _vec);

	void VectorMove(const D3DXVECTOR3& _vec);

	void Move(const float _x, const float _y, const float _z);

	void Scaling(const float _x, const float _y, const float _z);

	void Scaling(const D3DXVECTOR3& _tmpVec);

	void Scaling(const float _scl);

	void Clear0();

private:

}ChMat_9;


#endif