#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include"../ChCollider.h"

namespace ChCpp
{

	class FrameObject;
	class ModelObject;

	class PolygonCollider :public Collider
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetPolygon(const ModelObject& _model);

		ModelObject& GetPolygonList()const;

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

		ChStd::Bool cullHitFlg = true;
		ChStd::Bool lHandWorldFlg = true;
		ModelObject* _model = nullptr;;

	};




}

#endif