
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"ChMeshManager9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//MeshManager9���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void MeshManager9<CharaType>::Init(const LPDIRECT3DDEVICE9 _dev)
{
	device = _dev;
	SetInitFlg(true);
}

template<typename CharaType>
void ChMesh::MeshManager9<CharaType>::Release()
{
	if (!meshList.empty())meshList.clear();
	if (!pathList.empty())pathList.clear();
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

template<typename CharaType>
size_t ChMesh::MeshManager9<CharaType>::GetPathCnt()
{
	return pathList.size();
}

//���ݓo�^����Ă���Mesh�̐�//
template<typename CharaType>
size_t ChMesh::MeshManager9<CharaType>::GetMeshCnt()
{
	return meshList.size();
}