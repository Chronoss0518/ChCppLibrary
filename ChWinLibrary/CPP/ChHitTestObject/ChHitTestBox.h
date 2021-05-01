#ifndef Ch_CPP_HTB_h
#define Ch_CPP_HTB_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	//R=Right,L=Left,T=Top,D=Down,F=Front,B=Back//
	enum class HitTestBoxVertexs:unsigned char
	{
		RTF,RTB,LTF,LTB,RDF,RDB,LDF,LDB,None
	};

	class HitTestBox :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const HitTestBoxVertexs& _vertexNum, const ChVec3& _pos)
		{
			vPos[ChStd::EnumCast(_vertexNum)] = _pos;
		}

		//R=Right,L=Left,T=Top,D=Down,F=Front,B=Back//
		inline void SetPosition(
			const ChVec3& _RTF,
			const ChVec3& _RTB,
			const ChVec3& _LTF,
			const ChVec3& _LTB,
			const ChVec3& _RDF,
			const ChVec3& _RDB,
			const ChVec3& _LDF,
			const ChVec3& _LDB)
		{
			vPos[0] = _RTF;
			vPos[1] = _RTB;
			vPos[2] = _LTF;
			vPos[3] = _LTB;
			vPos[4] = _RDF;
			vPos[5] = _RDB;
			vPos[6] = _LDF;
			vPos[7] = _LDB;
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

		ChVec3 vPos[8];


	};




}

#endif