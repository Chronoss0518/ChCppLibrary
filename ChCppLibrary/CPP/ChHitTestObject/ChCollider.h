#ifndef Ch_CPP_Collider_h
#define Ch_CPP_Collider_h

#include<vector>

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
	public://Is Functions//

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestBox* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestSphere* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestRay* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual bool IsInnerHit(HitTestBox* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual bool IsInnerHit(HitTestSphere* _target) = 0;

	protected:

		bool HitTestTri(ChVec3& _thisHitVectol, const ChVec3& _pos, const ChVec3& _dir, const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		bool IsHitSphereToPanel(ChVec3& _thisHitVectol, const bool _leftHandFlg, const ChVec3& _spherePos, const ChVec3& _sphereSize, const std::vector<ChVec3*>& _vertexs);

	private:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChVec3 MovePosToPanelUp(const ChVec3& _v1, const ChVec3& _v2, const ChVec3& _v3, const ChVec3& _pos);

		bool IsHitSphereToLine(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _v1, const ChVec3& _v2);

		bool IsHitSphereToPos(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _vertex);

	};
}


#endif