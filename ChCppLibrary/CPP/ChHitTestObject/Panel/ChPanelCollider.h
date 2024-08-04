#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"../ChCollider.h"

namespace ChCpp
{


	//��{�I�ɖʂ͏����//
	class PanelCollider :public Collider
	{
	public:

		struct Square
		{
			ChVec3 pos[4];
		};

	public://SetFunction//

		inline void SetSize(const ChVec2& _size)
		{
			size = _size;
		}

		inline void SetRightHandFlg() { leftHandFlg = false; }

		inline void SetLeftHandFlg() { leftHandFlg = true; }
	
	public://GetFunction//

		inline ChVec2 GetSize() { return size; }

		Square GetSquarePositions();
	
	public://IsFunction//

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

		bool leftHandFlg = true;

		ChVec2 size;

	};




}

#endif