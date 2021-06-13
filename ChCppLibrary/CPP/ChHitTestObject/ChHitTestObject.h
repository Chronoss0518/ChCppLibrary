#ifndef Ch_CPP_HTO_h
#define Ch_CPP_HTO_h

namespace ChCpp
{
	class HitTestRay;
	class HitTestPanel;
	class HitTestBox;
	class HitTestSphere;
	class HitTestMesh;
	
	//引数として与えた物体から見て当たり判定を行うクラス//
	class HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const ChVec3& _pos) { pos = _pos; }

		inline void SetRotation(const ChVec3& _rot) { rot = _rot; }

		inline void SetScalling(const ChVec3& _scl) { scl = _scl;; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//衝突していた場合に中心から見てどの位置までめり込んでいたかの数値//
		inline ChVec3 GetHitVectol() { return hitVector; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestPanel* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestBox* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestSphere* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual ChStd::Bool IsHit(
			HitTestMesh* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual ChStd::Bool IsInnerHit(
			HitTestBox* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual ChStd::Bool IsInnerHit(
			HitTestSphere* _target) = 0;

	protected:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetHitVector(const ChVec3& _vec) { hitVector = _vec; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec3 GetPos() const { return pos; }

		inline ChVec3 GetRot()const { return rot; }

		inline ChVec3 GetScl()const { return scl; }

		inline ~HitTestObject() {}

	private:

		ChVec3 pos;
		ChVec3 rot;
		ChVec3 scl;

		//この数値文移動させれば衝突から免れる移動数値//
		ChVec3 hitVector = 0.0f;

	};

}

#endif