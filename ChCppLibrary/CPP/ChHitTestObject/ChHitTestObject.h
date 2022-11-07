#ifndef Ch_CPP_HTO_h
#define Ch_CPP_HTO_h

namespace ChCpp
{


	//当たり判定を行う手法//
	class HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const ChVec3& _pos) { mat.SetPosition(_pos); }

		inline void SetRotation(const ChVec3& _rot) { mat.SetRotation(_rot); }

		inline void SetScalling(const ChVec3& _scl) { mat.SetScalling(_scl); }

		inline void SetMatrix(const ChLMat& _mat) { mat = _mat; }

		inline void SetHitVector(const ChVec3& _vec) { hitVector = _vec; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//衝突していた場合に中心から見てどの位置までめり込んでいたかの数値//
		inline ChVec3 GetHitVectol() { return hitVector; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec3 GetPos() const { return mat.GetPosition(); }

		inline ChVec3 GetRot()const { return mat.GetRotation(); }

		inline ChVec3 GetScl()const { return mat.GetScalling(); }

		inline ChLMat GetMat()const { return mat; }

		inline ~HitTestObject() {}

	protected:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChStd::Bool HitTestTri(ChVec3& _thisHitVectol, const ChVec3& _dir, const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3, const HitTestObject* _target);

	private:

		ChLMat mat;

		//この数値文移動させれば衝突から免れる移動数値//
		ChVec3 hitVector = 0.0f;

	};

}

#endif