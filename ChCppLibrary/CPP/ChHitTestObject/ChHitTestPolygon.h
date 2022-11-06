#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	struct HitTestVertexs
	{
		ChVec3 normal;
		std::vector<ChPtr::Shared<ChVec3>> posList;
	};

	class HitTestPolygon :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPolygon(const std::vector<ChPtr::Shared<HitTestVertexs>>& _poly) { polygonList = _poly; }

		inline void SetPolygon(const std::vector<ChPtr::Shared<Ch3D::Primitive>>& _polyList,const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const ChLMat& _frameMatrix)
		{ 
			
			for (auto&& poly : _polyList)
			{
				if (poly->vertexData.size() <= 2)continue;

				auto vertexs = ChPtr::Make_S<HitTestVertexs>();

				for (unsigned long i = 0; i < poly->vertexData.size(); i++)
				{
					auto&& pos = _frameMatrix.Transform(_vertexList[poly->vertexData[i]->vertexNo]->pos);
					vertexs->normal += pos;
					vertexs->posList.push_back(ChPtr::Make_S<ChVec3>(pos));
				}
				vertexs->normal /= vertexs->posList.size() > 0 ? vertexs->posList.size() : 1;
				polygonList.push_back(vertexs);
			}
		}

		inline void AddPolygon(const HitTestVertexs& _vertexs)
		{
			auto hitTestVertexs = ChPtr::Make_S<HitTestVertexs>();
			*hitTestVertexs = _vertexs;

			polygonList.push_back(hitTestVertexs);
		}

		inline void AddPolygon(const ChVec3& _pos1, const ChVec3& _pos2, const ChVec3& _pos3)
		{
			auto hitTestVertexs = ChPtr::Make_S<HitTestVertexs>();

			hitTestVertexs->posList.push_back(ChPtr::Make_S<ChVec3>(_pos1));
			hitTestVertexs->posList.push_back(ChPtr::Make_S<ChVec3>(_pos2));
			hitTestVertexs->posList.push_back(ChPtr::Make_S<ChVec3>(_pos3));

			hitTestVertexs->normal = (_pos1 + _pos2, _pos3) / 3.0f;

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