#ifndef Ch_CPP_Collider_h
#define Ch_CPP_Collider_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	class HitTestRay;
	class BoxCollider;
	class SphereCollider;

	using HitTestSphere = SphereCollider;
	using HitTestBox = BoxCollider;


	//対象のHitTestObjectから衝突したかを判断するクラス//
	class Collider :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestBox* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestSphere* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestRay* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual ChStd::Bool IsInnerHit(
			HitTestBox* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual ChStd::Bool IsInnerHit(
			HitTestSphere* _target) = 0;

	};

}


#endif