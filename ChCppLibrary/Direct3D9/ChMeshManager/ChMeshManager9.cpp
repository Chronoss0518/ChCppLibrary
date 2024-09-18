
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
//MeshManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void MeshManager9::Init(const LPDIRECT3DDEVICE9 _dev)
{
	device = _dev;
	SetInitFlg(true);
}
