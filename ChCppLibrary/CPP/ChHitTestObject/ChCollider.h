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

	};

}


#endif