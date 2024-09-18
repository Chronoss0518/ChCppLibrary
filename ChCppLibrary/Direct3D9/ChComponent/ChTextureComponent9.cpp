
#include<Windows.h>
#include"../../BaseIncluder/CHBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChObjectManager.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChSprite/ChSprite9.h"
#include"../ChPolygonBoard/ChPolygonBoard9.h"
#include"ChComponent9.h"
#include"ChTextureComponent9.h"

///////////////////////////////////////////////////////////////////////////////////
//ChSpriteTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChSpriteTextureComponent9::Draw2D()
{
	if (ChPtr::NullCheck(GetTex()))return;

	for (unsigned char i = 0; i < 4; i++)
	{
		ver.spData[i].pos.z = 0.0f;
	}

	ChMat_9 TmpMat;

	//{
	//	auto Trans = LookObj()->GetTransform<ChTransformCom9>();
	//	if (nullptr != Trans)
	//	{
	//		TmpMat = Trans->GetMat();
	//	}
	//}

	ChD3D9::Shader().DrawSprite(*GetTex(), TmpMat,ver);
}

///////////////////////////////////////////////////////////////////////////////////
//ChPolygonTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPolygonTextureComponent9::Draw3D()
{
	if (ChPtr::NullCheck(GetTex()))return;

	ChMat_9 TmpMat;

	{
		//auto Trans = LookObj()->GetTransform<ChTransformCom9>();

		//if (nullptr != Trans)
		//{

		//	TmpMat = Trans->GetMat();
		//}
	}

	ChD3D9::Shader().DrawPolygonBoard(*GetTex(), ver, TmpMat);
}
