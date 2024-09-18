
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChMeshList9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//ChMeshListƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

MeshList9::~MeshList9()
{
	Release();
}

void ChMeshList9::CreateEasyFace(
	const unsigned short _dataNum,
	const unsigned short _BaseMatNum)
{

	auto&& mesh = GetMesh(_dataNum);
	if (ChPtr::NullCheck(mesh))return;

	mesh->CreateEasyFaceList();
}
