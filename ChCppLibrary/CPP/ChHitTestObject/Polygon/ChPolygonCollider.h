#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include"../ChCollider.h"

namespace ChCpp
{

	class FrameObject;

	class PolygonCollider :public Collider
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetModel(FrameObject& _model);

		inline void SetRightHandFlg() { leftHandFlg = false; }

		inline void SetLeftHandFlg() { leftHandFlg = true; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		FrameObject* GetModel()const;

		inline std::string GetHitMaterialName() { return hitMaterialName; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		bool IsHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		bool IsHit(
			HitTestSphere* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		bool IsHit(
			HitTestRay* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		bool IsInnerHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		bool IsInnerHit(
			HitTestSphere* _target)override;

	private:

		bool IsHitRayToMesh(FrameObject& _object, const ChVec3& _rayPos,const ChVec3& _rayDir,const float rayLen,const bool _nowHitFlg = false);

		bool leftHandFlg = true;
		std::string hitMaterialName = "";

		bool cullHitFlg = true;
		bool lHandWorldFlg = true;
		FrameObject* model = nullptr;;
		float minLen = 0.0f;
	};




}

#endif