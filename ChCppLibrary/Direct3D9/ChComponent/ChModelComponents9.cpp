
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChObjectManager.h"


#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"../ChMeshManager/ChMeshManager9.h"
#include"ChComponent9.h"
#include"ChModelComponents9.h"


///////////////////////////////////////////////////////////////////////////////////////
//ChModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::Draw3D()
{
	if (ChPtr::NullCheck(GetModel()))return;
	if (GetModel()->GetMesh() == nullptr)return;

	ChMat_9 tmpMat;
	{

		//auto Trans = LookObj()->GetTransform<ChTransformCom9>();

		//if (nullptr != Trans)
		//{
		//	tmpMat = Trans->GetMat();
		//}

	}

	ChD3D9::Shader().DrawMesh(*GetModel(), tmpMat);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSkinMeshModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChSkModelCom9::Update()
{
	if (ChPtr::NullCheck(GetModel()))return;

	auto tmpModel = GetSkinModel();

	if (ChPtr::NullCheck(tmpModel))return;

	tmpModel->SetSkin();
}
