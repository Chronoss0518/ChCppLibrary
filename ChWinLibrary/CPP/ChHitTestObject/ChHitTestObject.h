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

		//衝突していた場合に中心から見てどの位置までめり込んでいたかの数値//
		inline ChVec3 GetHitVectol() { return hitVector; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestPanel* _target) = 0;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestBox* _target) = 0;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestSphere* _target) = 0;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestMesh* _target) = 0;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		virtual ChStd::Bool IsInnerHit(
			HitTestBox* _target) = 0;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
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