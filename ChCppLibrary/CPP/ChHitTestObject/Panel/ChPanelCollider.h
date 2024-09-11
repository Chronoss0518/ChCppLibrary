#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"../ChCollider.h"

namespace ChCpp
{


	//基本的に面は上向き//
	class PanelCollider :public Collider
	{
	public:

		struct Square
		{
			ChVec3 pos[4];
		};

	public://Set Functions//

		inline void SetSize(const ChVec2& _size)
		{
			size = _size;
		}

		inline void SetRightHandFlg() { leftHandFlg = false; }

		inline void SetLeftHandFlg() { leftHandFlg = true; }
	
	public://GetFunction//

		inline ChVec2 GetSize() { return size; }

		Square GetSquarePositions();
	
	public://IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestSphere* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestRay* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		bool IsInnerHit(HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		bool IsInnerHit(HitTestSphere* _target)override;

	private:

		bool leftHandFlg = true;

		ChVec2 size;
	};

}

#endif