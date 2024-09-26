#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include<string>
#include<vector>

#include"../ChCollider.h"

#include"../../../BasePack/ChStd.h"

#include"../../ChModel/ChModelObject.h"

namespace ChCpp
{
	template<typename CharaType>
	class FrameObject;

	template<typename CharaType>
	class PolygonCollider :public Collider
	{
	public:

		PolygonCollider();

		virtual ~PolygonCollider();

	public://SetFunction//

		void SetModel(FrameObject<CharaType>& _model);

		inline void SetRightHandFlg() { leftHandFlg = false; }

		inline void SetLeftHandFlg() { leftHandFlg = true; }
	
	public://GetFunction//

		FrameObject<CharaType>* GetModel()const;

		std::basic_string<CharaType> GetHitMaterialName() { return value->hitMaterialName; }

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

	private:

		bool IsHitRayToMesh(FrameObject<CharaType>& _object, const ChVec3& _rayPos,const ChVec3& _rayDir,const float rayLen,const bool _nowHitFlg = false);

		bool leftHandFlg = true;
		bool cullHitFlg = true;
		bool lHandWorldFlg = true;
		float minLen = 0.0f;

		std::basic_string<CharaType> hitMaterialName = ChStd::GetZeroChara<CharaType>();
		FrameObject<CharaType>* model = nullptr;
	};
}


#endif