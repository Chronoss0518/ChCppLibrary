#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"../ChCollider.h"

namespace ChCpp
{

	struct Square
	{
		ChVec3 pos[4];
	};


	//��{�I�ɖʂ͏����//
	class PanelCollider :public Collider
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetSize(const ChVec2& _size)
		{
			size = _size;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec2 GetSize()
		{
			return size;
		}

		Square GetSquarePositions();

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestSphere* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestRay* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;

	private:

		ChVec2 size;

	};




}

#endif