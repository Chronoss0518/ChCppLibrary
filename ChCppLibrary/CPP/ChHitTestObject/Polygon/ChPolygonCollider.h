#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include"../ChCollider.h"

namespace ChCpp
{

	class FrameObject;

	class PolygonCollider :public Collider
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetModel(FrameObject& _model);

		inline void SetRightHandFlg() { leftHandFlg = false; }

		inline void SetLeftHandFlg() { leftHandFlg = true; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		FrameObject* GetModel()const;

		inline std::string GetHitMaterialName() { return hitMaterialName; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestSphere* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestRay* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;

	private:

		ChStd::Bool IsHitRayToMesh(FrameObject& _object, const ChVec3& _rayPos,const ChVec3& _rayDir,const float rayLen,const ChStd::Bool _nowHitFlg = false);

		ChStd::Bool leftHandFlg = true;
		std::string hitMaterialName = "";

		ChStd::Bool cullHitFlg = true;
		ChStd::Bool lHandWorldFlg = true;
		FrameObject* model = nullptr;;
		float minLen = 0.0f;
	};




}

#endif