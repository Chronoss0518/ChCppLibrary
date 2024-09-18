
#ifdef Ch_D3D11_Qua_h
#ifdef Ch_D3D11_Vec3_h

#ifndef Ch_CPP_Shared_Vector_Matrix
#define Ch_CPP_Shared_Vector_Matrix


void ChQuaternion_11::RotLookAt(
	const DirectX::XMFLOAT3& _Pos,
	const DirectX::XMFLOAT3& _BasePos)
{
	ChVec3_11 tmp = _Pos;
	tmp = tmp - _BasePos;
	*this = (DirectX::XMFLOAT3)(tmp);
}


void ChQuaternion_11::RotAxis(const DirectX::XMFLOAT3& _vec, const float _ang)
{
	ChVec3_11 tmpVec = _vec;
	tmpVec = DirectX::XMQuaternionRotationAxis(tmpVec, _ang);
	*this = tmpVec;
}


#endif

#endif
#endif