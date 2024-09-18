#ifndef Ch_CPP_HTS_h
#define Ch_CPP_HTS_h

#include"../ChCollider.h"

namespace ChCpp
{

	class SphereCollider :public Collider
	{
	public://IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		bool IsHit(HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		bool IsHit(HitTestSphere* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		bool IsHit(HitTestRay* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		bool IsInnerHit(HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		bool IsInnerHit(HitTestSphere* _target)override;

	};
}

#include"../Polygon/ChPolygonColliderSharedRayBoxSphere.h"

#endif