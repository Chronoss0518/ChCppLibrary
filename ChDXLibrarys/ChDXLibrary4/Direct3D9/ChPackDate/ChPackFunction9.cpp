
#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"

#include"../../ChInclude/ChD3D9I.h"


#include"ChVector3_9.h"
#include"ChQuaternion_9.h"
#include"ChMatrix_9.h"

///////////////////////////////////////////////////////////////////////////////////
//ChVector4Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const D3DXVECTOR4()const
{
	D3DXVECTOR4 TmpVec;

	TmpVec.x = x;
	TmpVec.y = y;
	TmpVec.z = z;
	TmpVec.w = w;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const D3DXVECTOR4*()const
{
	return reinterpret_cast<D3DXVECTOR4*>(const_cast<ChVec4*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4& ChVec4::operator= (const D3DXVECTOR4& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;
	w = _Vec.w;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const D3DXVECTOR3()const
{
	D3DXVECTOR3 TmpVec;

	TmpVec.x = x;
	TmpVec.y = y;
	TmpVec.z = z;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const D3DXVECTOR3*()const
{
	return reinterpret_cast<D3DXVECTOR3*>(const_cast<ChVec3*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const D3DXVECTOR3& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const D3DXQUATERNION& _Qua)
{
	D3DXMATRIX TmpMat;
	D3DXVECTOR3 TmpVec;

	D3DXMatrixRotationQuaternion(&TmpMat, &_Qua);

	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &TmpMat);

	*this = TmpVec;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const D3DXMATRIX& _Mat)
{
	x = _Mat._41;
	y = _Mat._42;
	z = _Mat._43;

	return *this;

}

///////////////////////////////////////////////////////////////////////////////////
//ChVector2Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const D3DXVECTOR2()const
{
	D3DXVECTOR2 TmpVec;

	TmpVec.x = x;
	TmpVec.y = y;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const D3DXVECTOR2*()const
{
	return reinterpret_cast<D3DXVECTOR2*>(const_cast<ChVec2*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2& ChVec2::operator= (const D3DXVECTOR2& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternionOperator//
///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const D3DXQUATERNION()const
{
	ChQua_9 TmpQua;
	TmpQua.x = x;
	TmpQua.y = y;
	TmpQua.z = z;
	TmpQua.w = w;

	return TmpQua;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const D3DXQUATERNION*()const
{
	return reinterpret_cast<D3DXQUATERNION*>(const_cast<ChQua*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXQUATERNION& _Qua)
{
	x = _Qua.x;
	y = _Qua.y;
	z = _Qua.z;
	w = _Qua.w;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXVECTOR3& _Vec)
{
	ChQua_9 TmpQua = _Vec;
	*this = TmpQua;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXMATRIX& _Mat)
{

	ChQua_9 TmpQua = _Mat;
	*this = TmpQua;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChMatrixOperator//
///////////////////////////////////////////////////////////////////////////////////

ChMat::operator const D3DXMATRIX()const
{
	ChMat_9 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] = m[i][j];
		}
	}

	return TmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

ChMat::operator const D3DXMATRIX*()const
{
	return reinterpret_cast<D3DXMATRIX*>(const_cast<ChMat*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChMat& ChMat::operator= (const D3DXQUATERNION& _Qua)
{
	ChMat_9 TmpMat = _Qua;
	*this = TmpMat;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMat& ChMat::operator= (const D3DXVECTOR3& _Vec)
{
	ChMat_9 TmpMat = _Vec;
	*this = TmpMat;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChMat& ChMat::operator= (const D3DXMATRIX& _Mat)
{


	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _Mat.m[i][j];
		}
	}

	return *this;
}
