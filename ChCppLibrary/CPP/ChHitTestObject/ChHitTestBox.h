#ifndef Ch_CPP_HTB_h
#define Ch_CPP_HTB_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	struct Cube
	{
		ChVec3 pos[8] = {
			ChVec3(0.5f,0.5f,0.5f),
			ChVec3(-0.5f,0.5f,0.5f),
			ChVec3(-0.5f,-0.5f,0.5f),
			ChVec3(0.5f,-0.5f,0.5f),
			ChVec3(0.5f,0.5f,-0.5f),
			ChVec3(-0.5f,0.5f,-0.5f),
			ChVec3(-0.5f,-0.5f,-0.5f),
			ChVec3(0.5f,-0.5f,-0.5f)
		};

		unsigned char faces[12][3] =
		{
			{0,1,2},
			{0,2,3},
			{0,4,5},
			{0,5,1},
			{1,5,6},
			{1,6,2},
			{0,4,7},
			{0,7,3},
			{2,6,7},
			{2,7,3},
			{4,7,6},
			{4,6,5}
		};
	};

	class HitTestBox :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestPanel* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestSphere* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestMesh* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;


		///////////////////////////////////////////////////////////////////////////////////////
		
		Cube CreateCube();



	};




}

#endif