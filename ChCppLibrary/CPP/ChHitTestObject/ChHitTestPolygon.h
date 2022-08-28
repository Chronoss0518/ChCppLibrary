#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	struct HitTestVertexs
	{
		ChVec3 poss[3];
	};

	class HitTestPolygon :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPolygon(const std::vector<ChPtr::Shared<HitTestVertexs>>& _poly) { polygonList = _poly; }

		inline void SetPolygon(const std::vector<ChPtr::Shared<Ch3D::Primitive>>& _polyList,const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList)
		{ 
			for (auto&& poly : _polyList)
			{
				if (poly->vertexData.size() <= 2)continue;

				for (unsigned long i = 1; i < poly->vertexData.size() - 1; i++)
				{
					auto vertexs = ChPtr::Make_S<HitTestVertexs>();
					vertexs->poss[0] = _vertexList[poly->vertexData[0]->vertexNo]->pos;
					vertexs->poss[1] = _vertexList[poly->vertexData[i]->vertexNo]->pos;
					vertexs->poss[2] = _vertexList[poly->vertexData[i + 1]->vertexNo]->pos;

					polygonList.push_back(vertexs);
				}


			}
		}

		inline void AddPolygon(const HitTestVertexs& _vertexs)
		{
			auto hitTestVertexs = ChPtr::Make_S<HitTestVertexs>();

			for (unsigned char i = 0; i < 3; i++)
			{
				hitTestVertexs->poss[i] = _vertexs.poss[i];
			}

			polygonList.push_back(hitTestVertexs);
		}

		inline void AddPolygon(const ChVec3& _pos1, const ChVec3& _pos2, const ChVec3& _pos3)
		{
			auto hitTestVertexs = ChPtr::Make_S<HitTestVertexs>();

			hitTestVertexs->poss[0] = _pos1;
			hitTestVertexs->poss[1] = _pos2;
			hitTestVertexs->poss[2] = _pos3;

			polygonList.push_back(hitTestVertexs);
		}

		inline std::vector<ChPtr::Shared<HitTestVertexs>> GetPolygonList()const
		{
			return polygonList;
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
			HitTestPolygon* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;

	private:

		ChStd::Bool cullHitFlg = true;
		ChStd::Bool lHandWorldFlg = true;
		std::vector<ChPtr::Shared<HitTestVertexs>>polygonList;

	};




}

#endif