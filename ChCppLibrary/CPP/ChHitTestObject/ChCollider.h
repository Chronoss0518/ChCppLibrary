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


	//�Ώۂ�HitTestObject����Փ˂������𔻒f����N���X//
	class Collider :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g�̊O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestBox* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g�̊O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestSphere* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g�̊O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestRay* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsInnerHit(
			HitTestBox* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsInnerHit(
			HitTestSphere* _target) = 0;

	protected:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChStd::Bool HitTestTri(ChVec3& _thisHitVectol, const ChVec3& _pos, const ChVec3& _dir, const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChStd::Bool IsHitSphereToPanel(ChVec3& _thisHitVectol, const ChStd::Bool _leftHandFlg, const ChVec3& _spherePos, const ChVec3& _sphereSize, const std::vector<ChVec3*> _vertexs);

	private:

		ChStd::Bool IsHitSphereToLine(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _v1, const ChVec3& _v2);

		ChStd::Bool IsHitSphereToPos(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _vertex);

	};

}


#endif