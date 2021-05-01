#ifndef Ch_CPP_HTR_h
#define Ch_CPP_HTR_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	enum class HitTestRayDirctionAxis
	{
		Top, Down, Front, Back, Right, Left
	};

	class HitTestRay :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestPanel* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestSphere* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHit(
			HitTestMesh* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;

	private:

		const static std::map<HitTestRayDirctionAxis, std::function<ChVec3()>>GetRayAxis;

		HitTestRayDirctionAxis rayAxis;

		float maxLen = FLT_MAX;

	};




}

#endif