#ifndef Ch_CPP_HTO_h
#define Ch_CPP_HTO_h

#include"../../BasePack/ChMath3D.h"

namespace ChCpp
{
	//�����蔻����s����@//
	class HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const ChVec3& _pos) { mat.SetPosition(_pos); }

		inline void SetRotation(const ChQua& _rot) { mat.SetRotation(_rot); }

		inline void SetScalling(const ChVec3& _scl) { mat.SetScalling(_scl); }

		inline void SetMatrix(const ChLMat& _mat) { mat = _mat; }

		inline void SetHitVector(const ChVec3& _vec) { hitVector = _vec; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�Փ˂��Ă����ꍇ�ɒ��S���猩�Ăǂ̈ʒu�܂ł߂荞��ł������̐��l//
		inline ChVec3 GetHitVectol() { return hitVector; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec3 GetPos() const { return mat.GetPosition(); }

		inline ChQua GetRot()const { return mat.GetRotation(); }

		inline ChVec3 GetScl()const { return mat.GetScalling(); }

		inline ChLMat GetMat()const { return mat; }

		inline ~HitTestObject() {}

	private:

		ChLMat mat;

		//���̐��l���ړ�������ΏՓ˂���Ƃ��ړ����l//
		ChVec3 hitVector = 0.0f;

	};

}

#endif