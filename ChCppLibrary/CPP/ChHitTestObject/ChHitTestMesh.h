#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	class HitTestMesh :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//


		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestPanel* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestSphere* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestMesh* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;

	private:



	};




}

#endif