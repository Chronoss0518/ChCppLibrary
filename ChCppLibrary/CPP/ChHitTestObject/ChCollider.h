#ifndef Ch_CPP_Collider_h
#define Ch_CPP_Collider_h

#include"../../CRTPack/ChVectorPack/ChVectorPack.h"

#include"ChHitTestObject.h"

namespace ChCpp
{

	class HitTestRay;
	class BoxCollider;
	class SphereCollider;

	using HitTestSphere = SphereCollider;
	using HitTestBox = BoxCollider;


	//�Ώۂ�HitTestObject����Փ˂������𔻒f����N���X//
	class Collider :public HitTestObject
	{
	public://Is Functions//

		//�Ώۂ̃I�u�W�F�N�g�̊O����Փ˂��Ă��邩�̔���//
		virtual bool IsHit(HitTestBox* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g�̊O����Փ˂��Ă��邩�̔���//
		virtual bool IsHit(HitTestSphere* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g�̊O����Փ˂��Ă��邩�̔���//
		virtual bool IsHit(HitTestRay* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual bool IsInnerHit(HitTestBox* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual bool IsInnerHit(HitTestSphere* _target) = 0;

	protected:

		bool HitTestTri(ChVec3& _thisHitVectol, const ChVec3& _pos, const ChVec3& _dir, const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		bool IsHitSphereToPanel(ChVec3& _thisHitVectol, const bool _leftHandFlg, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChCRT::VectorPack<ChVec3*>& _vertexs);

	private:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChVec3 MovePosToPanelUp(const ChVec3& _v1, const ChVec3& _v2, const ChVec3& _v3, const ChVec3& _pos);

		bool IsHitSphereToLine(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _v1, const ChVec3& _v2);

		bool IsHitSphereToPos(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _vertex);

	};
}


#endif