#ifndef Ch_CPP_HTB_h
#define Ch_CPP_HTB_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	class HitTestBox :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetSize(const ChVec3& _size) 
		{
			size = _size; 
			size.Abs();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline ChVec3 GetSize() { return size; }

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

		ChVec3 size;


	};




}

#endif