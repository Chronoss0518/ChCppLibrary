
#ifdef Ch_D3D11_ChMat_h
#ifdef Ch_D3D11_Vec3_h

#ifndef Ch_CPP_Shared_Vector_Matrix
#define Ch_CPP_Shared_Vector_Matrix


void ChMatrix_11::CreateViewMat(const ChVec3& _pos, const ChVec3& _dir, const ChVec3& _up)
{

	ChVec3_11 pos;
	pos = _pos;

	ChVec3_11 up;
	up = _up;

	ChVec3_11 dir;
	dir = _dir;

	*this = DirectX::XMMatrixLookToLH(pos, dir, up);
}

void ChMatrix_11::CreateViewMatLookTarget(
	const ChVec3& _pos,
	const ChVec3& _targetPos,
	const ChVec3& _up)
{
	ChVec3_11 pos;
	pos = _pos;

	ChVec3_11 up;
	up = _up;

	ChVec3_11 targetPos;
	targetPos = _targetPos;

	*this = DirectX::XMMatrixLookAtLH(pos, targetPos, up);
}

#endif

#endif
#endif