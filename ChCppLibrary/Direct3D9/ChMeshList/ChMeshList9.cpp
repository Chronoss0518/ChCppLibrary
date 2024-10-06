
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChMeshList9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//ChMeshListÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChMesh::MeshList9<CharaType>::Release()
{
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

template<typename CharaType>
const unsigned short ChMesh::MeshList9<CharaType>::GetMeshSize()
{
	return (unsigned short)meshList.size();
}

template<typename CharaType>
ChMesh::BaseMesh9<CharaType>* ChMesh::MeshList9<CharaType>::GetMesh(const unsigned short _dataNum)
{
	if (meshList.size() <= _dataNum)return nullptr;

	return meshList[_dataNum].get();
}

template<typename CharaType>
ChMesh::MeshList9<CharaType>::~MeshList9()
{
	Release();
}

template<typename CharaType>
void ChMesh::MeshList9<CharaType>::CreateEasyFace(
	const unsigned short _dataNum,
	const unsigned short _BaseMatNum)
{

	auto&& mesh = GetMesh(_dataNum);
	if (ChPtr::NullCheck(mesh))return;

	mesh->CreateEasyFaceList();
}
