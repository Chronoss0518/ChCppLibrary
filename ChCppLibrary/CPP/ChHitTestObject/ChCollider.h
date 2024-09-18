#ifndef Ch_CPP_Collider_h
#define Ch_CPP_Collider_h

#include"ChHitTestObject.h"

#ifdef CRT

#include<vector>

#endif

namespace ChCpp
{

	class HitTestRay;
	class BoxCollider;
	class SphereCollider;

	using HitTestSphere = SphereCollider;
	using HitTestBox = BoxCollider;


	//対象のHitTestObjectから衝突したかを判断するクラス//
	class Collider :public HitTestObject
	{
	public://Is Functions//

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestBox* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestSphere* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestRay* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual bool IsInnerHit(HitTestBox* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual bool IsInnerHit(HitTestSphere* _target) = 0;

	protected:

		bool HitTestTri(ChVec3& _thisHitVectol, const ChVec3& _pos, const ChVec3& _dir, const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

#ifdef CRT
		bool IsHitSphereToPanel(ChVec3& _thisHitVectol, const bool _leftHandFlg, const ChVec3& _spherePos, const ChVec3& _sphereSize, const std::vector<ChVec3*> _vertexs)
		{
			if (_vertexs.empty())return false;

			if (_vertexs.size() < 2)
				return IsHitSphereToPos(_thisHitVectol, _spherePos, _sphereSize, *_vertexs[0]);

			if (_vertexs.size() < 3)
				return IsHitSphereToLine(_thisHitVectol, _spherePos, _sphereSize, *_vertexs[0], *_vertexs[1]);

			ChVec3 tmpPos = MovePosToPanelUp(*_vertexs[0], *_vertexs[_leftHandFlg ? 1 : _vertexs.size() - 1], *_vertexs[_leftHandFlg ? 1 : _vertexs.size() - 2], _spherePos);

			ChVec3 posOnPanel = _spherePos - tmpPos;

			ChVec3 testNormal = ChVec3();

			bool hitTest = true;

			for (unsigned long i = 0; i < _vertexs.size() - 1; i++)
			{
				ChVec3 vertex1;
				ChVec3 vertex2;

				{
					unsigned long v1Num = i + 1;
					unsigned long v2Num = i + 2;
					vertex1 = *_vertexs[_leftHandFlg ? v1Num : _vertexs.size() - v1Num];
					vertex2 = *_vertexs[_leftHandFlg ? v2Num : _vertexs.size() - v2Num];
				}

				ChVec3 test = ChVec3::GetCross(posOnPanel - vertex1, vertex2 - vertex1);

				if (testNormal.GetLen() < 0.1f)
				{
					testNormal = test;
				}

				if (testNormal == test)continue;

				hitTest = false;

				break;
			}

			if (hitTest)
			{

			}

			return hitTest;
		}
#endif

	private:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChVec3 MovePosToPanelUp(const ChVec3& _v1, const ChVec3& _v2, const ChVec3& _v3, const ChVec3& _pos);

		bool IsHitSphereToLine(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _v1, const ChVec3& _v2);

		bool IsHitSphereToPos(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _vertex);

	};
}


#endif