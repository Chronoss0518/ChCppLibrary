#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"../ChCollider.h"

namespace ChCpp
{

	struct Square
	{
		ChVec3 pos[4];
	};


	//基本的に面は上向き//
	class PanelCollider :public Collider
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetSize(const ChVec2& _size)
		{
			size = _size;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec2 GetSize()
		{
			return size;
		}

		Square GetSquarePositions();

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

		ChVec2 size;

	};




}

#endif