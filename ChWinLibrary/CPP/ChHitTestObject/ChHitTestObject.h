#ifndef Ch_CPP_HTO_h
#define Ch_CPP_HTO_h

namespace ChCpp
{
	class HitTestRay;
	class HitTestPanel;
	class HitTestBox;
	class HitTestSphere;
	class HitTestMesh;

	class HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const ChVec3& _pos) { mat.SetPosition(_pos); }

		inline void SetRotation(const ChVec3& _rot) { mat.SetRotation(_rot); }

		inline void SetScalling(const ChVec3& _scl) { mat.SetScalling(_scl); }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�Փ˂��Ă����ꍇ�ɒ��S���猩�Ăǂ̈ʒu�܂ł߂荞��ł������̐��l//
		inline ChVec3 GetHitVectol() { return hitVector; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestPanel* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestBox* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestSphere* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHit(
			HitTestMesh* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsInnerHit(
			HitTestBox* _target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsInnerHit(
			HitTestSphere* _target) = 0;

	protected:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetHitVector(const ChVec3& _vec) { hitVector = _vec; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec3 GetPos() const { return mat.GetPosition(); }

		inline ChVec3 GetRot()const { return mat.GetRotation(); }

		inline ChVec3 GetScl()const { return mat.GetScalling(); }

		inline ChLMat GetLMat()const { return mat; }

		inline ~HitTestObject() {}

	private:

		ChLMat mat;

		ChVec3 hitVector = 0.0f;

	};

}

#endif