#ifndef Ch_CPP_HTB_h
#define Ch_CPP_HTB_h

#include"../ChCollider.h"

namespace ChCpp
{

	struct Cube
	{
		ChVec3 pos[8] = {
			ChVec3(1.0f,1.0f,1.0f),
			ChVec3(-1.0f,1.0f,1.0f),
			ChVec3(-1.0f,-1.0f,1.0f),
			ChVec3(1.0f,-1.0f,1.0f),
			ChVec3(1.0f,1.0f,-1.0f),
			ChVec3(-1.0f,1.0f,-1.0f),
			ChVec3(-1.0f,-1.0f,-1.0f),
			ChVec3(1.0f,-1.0f,-1.0f)
		};

		const unsigned char faces[6][4] =
		{
			{0,1,2,3},
			{0,4,5,1},
			{1,5,6,2},
			{0,4,7,3},
			{2,6,7,3},
			{4,7,6,5},
		};
	};

	class BoxCollider :public Collider
	{
	public://IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestSphere* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestRay* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		bool IsInnerHit(HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		bool IsInnerHit(HitTestSphere* _target)override;

	public://Create Functions//

		Cube CreateCube(const ChLMat& _mat);

	};
}

#endif