#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#ifdef CRT

#include<string>
#include<vector>

#endif

#include"../ChCollider.h"

#include"../../../BasePack/ChStd.h"

#include"../../ChModel/ChModelObject.h"

namespace ChCpp
{
	template<typename CharaType>
	class FrameObject;

	template<typename CharaType>
	class PolygonCollider :public Collider
	{
	public:

		struct PolygonColliderCRT
		{
#ifdef CRT
			std::basic_string<CharaType> hitMaterialName = ChStd::GetZeroChara<CharaType>();
			FrameObject<CharaType>* model = nullptr;
#endif
		};

	public:

		PolygonCollider();

		virtual ~PolygonCollider();

	public://SetFunction//

		void SetModel(FrameObject<CharaType>& _model);

		inline void SetRightHandFlg() { leftHandFlg = false; }

		inline void SetLeftHandFlg() { leftHandFlg = true; }
	
	public://GetFunction//

		FrameObject<CharaType>* GetModel()const;

#ifdef CRT
		std::basic_string<CharaType> GetHitMaterialName() { return value->hitMaterialName; }
#endif

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

		bool IsHitRayToMesh(FrameObject<CharaType>& _object, const ChVec3& _rayPos,const ChVec3& _rayDir,const float rayLen,const bool _nowHitFlg = false);

		bool leftHandFlg = true;
		bool cullHitFlg = true;
		bool lHandWorldFlg = true;
		float minLen = 0.0f;

		PolygonColliderCRT* value = nullptr;
	};
}

#ifdef CRT

template<typename CharaType>
ChCpp::PolygonCollider<CharaType>::PolygonCollider()
{
	value = new PolygonColliderCRT();
}

template<typename CharaType>
ChCpp::PolygonCollider<CharaType>::~PolygonCollider()
{
	delete value;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitRayToMesh(FrameObject<CharaType>& _object, const ChVec3& _rayPos, const ChVec3& _rayDir, const float _rayLen, const bool _nowHitFlg)
{
	_object.UpdateDrawTransform();

	bool hitFlg = _nowHitFlg;

	auto frameCom = _object.GetComponent<FrameComponent<CharaType>>();
	float minLen = _rayLen;

	ChLMat tmpMat = _object.GetDrawLHandMatrix() * GetMat();

	if (frameCom != nullptr)
	{
		if (frameCom->ValueIns().vertexList.size() >= 3)
		{
			std::vector<ChPtr::Shared<ChVec3>>posList;

			for (unsigned long i = 0; i < frameCom->ValueIns().vertexList.size(); i++)
				posList.push_back(ChPtr::Make_S<ChVec3>(tmpMat.Transform(frameCom->ValueIns().vertexList[i]->pos)));

			ChVec3 poss[3];
			unsigned long nos[3]{ 0,1,2 };
			for (auto&& primitive : frameCom->ValueIns().primitives)
			{
				for (unsigned char j = 0; j < 3; j++)
				{
					nos[j] = !leftHandFlg ? primitive->ValueIns().vertexData.size() - j - 1 : j;
					poss[j] = *posList[primitive->ValueIns().vertexData[nos[j]]->vertexNo];
				}

				{
					ChVec3 faceNormal = ChVec3::GetCross((poss[1] - poss[0]), (poss[2] - poss[0]));
					faceNormal.Normalize();
					ChVec3 pos0ToRay = _rayPos - poss[0];

					float faceLen = ChVec3::GetDot(faceNormal, pos0ToRay);

					if (faceLen > minLen)continue;
				}

				for (unsigned long i = 1; i < primitive->ValueIns().vertexData.size() - 1; i++)
				{
					ChVec3 tmpVec;

					for (unsigned char j = 1; j < 3; j++)
					{
						nos[j] = !leftHandFlg ? primitive->ValueIns().vertexData.size() - j - i : i + j - 1;
						poss[j] = *posList[primitive->ValueIns().vertexData[nos[j]]->vertexNo];
					}

					if (!HitTestTri(
						tmpVec,
						_rayPos,
						_rayDir,
						poss[0],
						poss[1],
						poss[2]))continue;

					float tmpLen = tmpVec.GetLen();
					if (tmpLen > _rayLen)continue;
					hitFlg = true;
					if (minLen < tmpLen)continue;
					minLen = tmpLen;
					value->hitMaterialName = frameCom->ValueIns().materialList[primitive->mateNo]->ValueIns().mateName;
					SetHitVector(tmpVec);
					break;
				}

			}
		}
	}

	for (auto&& child : _object.GetChildlen<FrameObject<CharaType>>())
	{
		hitFlg = IsHitRayToMesh(*child.lock(), _rayPos, _rayDir, minLen, hitFlg);
	}


	return hitFlg;
}

template<typename CharaType>
void ChCpp::PolygonCollider<CharaType>::SetModel(FrameObject<CharaType>& _model)
{
	value->model = &_model;
}

template<typename CharaType>
ChCpp::FrameObject<CharaType>* ChCpp::PolygonCollider<CharaType>::GetModel()const
{
	return value->model;
}


#endif

#include"ChPolygonColliderSharedRayBoxSphere.h"

#endif