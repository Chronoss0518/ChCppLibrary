#ifndef Ch_CPP_HTB_h
#define Ch_CPP_HTB_h

#include"../ChCollider.h"

namespace ChCpp
{

	struct Cube
	{
		ChVec3 pos[8] = {
			ChVec3(1.0f,1.0f,1.0f),
			ChVec3(-1.0f,1.0f,1.0f),
			ChVec3(-1.0f,-1.0f,1.0f),
			ChVec3(1.0f,-1.0f,1.0f),
			ChVec3(1.0f,1.0f,-1.0f),
			ChVec3(-1.0f,1.0f,-1.0f),
			ChVec3(-1.0f,-1.0f,-1.0f),
			ChVec3(1.0f,-1.0f,-1.0f)
		};

		const unsigned char faces[6][4] =
		{
			{0,1,2,3},
			{0,4,5,1},
			{1,5,6,2},
			{0,4,7,3},
			{2,6,7,3},
			{4,7,6,5},
		};
	};

	class BoxCollider :public Collider
	{
	public:
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


		///////////////////////////////////////////////////////////////////////////////////////
		
		Cube CreateCube(const ChLMat& _mat);



	};

}

#endif