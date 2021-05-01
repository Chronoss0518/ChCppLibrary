#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	//R=Right,L=Left,T=Top,D=Down//
	enum class HitTestPanelVertexs :unsigned char
	{
		RT, LT, RD, LD, None
	};

	class HitTestPanel :public HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const HitTestPanelVertexs& _vertexNum, const ChVec3& _pos)
		{
			vPos[ChStd::EnumCast(_vertexNum)] = _pos;
		}

		//R=Right,L=Left,T=Top,D=Down//
		inline void SetPosition(
			const ChVec3& _rt,
			const ChVec3& _lt,
			const ChVec3& _rd,
			const ChVec3& _ld)
		{
			vPos[0] = _rt;
			vPos[1] = _lt;
			vPos[2] = _rd;
			vPos[3] = _ld;
		}

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

		ChVec3 vPos[4];


	};




}

#endif