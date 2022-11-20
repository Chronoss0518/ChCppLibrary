#include"../../../BaseIncluder/ChBase.h"
#include<cmath>
#include"../../ChModel/ChModel.h"
#include"../../ChModel/ChModelObject.h"

#include"ChPolygonCollider.h"

#include"../Box/ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"../Sphere/ChSphereCollider.h"

#include"../../ChMultiThread/ChMultiThread.h"

using namespace ChCpp;

ChStd::Bool PolygonCollider::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool PolygonCollider::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  PolygonCollider::IsHit(
	HitTestRay* _target)
{

	auto model = GetModel();

	if (ChPtr::NullCheck(model))return false;

	float maxLen = _target->GetMaxLen();
	ChVec3 pos;
	ChVec3 ray = _target->GetRayDir();
	minLen = maxLen;

	{
		ChLMat tmp = _target->GetMat();
		pos = tmp.GetPosition();
		ray = tmp.TransformCoord(ray);
	}

	ChStd::Bool hitFlg = IsHitRayToMesh(*model,pos,ray,minLen);


	if (hitFlg)
	{
		_target->SetHitVector(GetHitVectol() * -1.0f);
	}

	return hitFlg;

}

ChStd::Bool PolygonCollider::IsHitRayToMesh(FrameObject& _object, const ChVec3& _rayPos, const ChVec3& _rayDir, const float _rayLen, const ChStd::Bool _nowHitFlg)
{
	_object.UpdateDrawTransform();

	ChStd::Bool hitFlg = _nowHitFlg;

	auto frameCom = _object.GetComponent<FrameComponent>();
	float minLen = _rayLen;

	ChLMat tmpMat = _object.GetDrawLHandMatrix() * GetMat();

	if (frameCom != nullptr)
	{
		if (frameCom->vertexList.size() >= 3)
		{

			std::vector<ChPtr::Shared<ChVec3>>posList;

			for (unsigned long i = 0; i < frameCom->vertexList.size(); i++)
			{
				posList.push_back(ChPtr::Make_S<ChVec3>(tmpMat.Transform(frameCom->vertexList[i]->pos)));
			}

			for (auto&& primitive : frameCom->primitives)
			{
				ChVec3 poss[3];

				poss[0] = *posList[primitive->vertexData[0]->vertexNo];


				if (!leftHandFlg)
				{
					poss[0] = *posList[primitive->vertexData[primitive->vertexData.size() - 1]->vertexNo];
				}

				poss[1] = *posList[primitive->vertexData[1]->vertexNo];
				poss[2] = *posList[primitive->vertexData[2]->vertexNo];

				if (!leftHandFlg)
				{
					poss[1] = *posList[primitive->vertexData[primitive->vertexData.size() - 2]->vertexNo];
					poss[2] = *posList[primitive->vertexData[primitive->vertexData.size() - 3]->vertexNo];

				}

				{
					ChVec3 faceNormal = ChVec3::GetCross((poss[1] - poss[0]), (poss[2] - poss[0]));
					faceNormal.Normalize();
					ChVec3 pos0ToRay = _rayPos - poss[0];

					float faceLen = ChVec3::GetDot(faceNormal, pos0ToRay);

					if (faceLen > minLen)continue;
				}

				for (unsigned long i = 1; i < primitive->vertexData.size() - 1; i++)
				{
					ChVec3 tmpVec;

					poss[1] = *posList[primitive->vertexData[i]->vertexNo];
					poss[2] = *posList[primitive->vertexData[i + 1]->vertexNo];

					if (!leftHandFlg)
					{
						poss[1] = *posList[primitive->vertexData[primitive->vertexData.size() - 1 - i]->vertexNo];
						poss[2] = *posList[primitive->vertexData[primitive->vertexData.size() - 2 - i]->vertexNo];

					}

					{
						ChVec3 faceNormal = ChVec3::GetCross((poss[1] - poss[0]), (poss[2] - poss[0]));
						faceNormal.Normalize();
						ChVec3 pos0ToRay = _rayPos - poss[0];

						float faceLen = ChVec3::GetDot(faceNormal, pos0ToRay);

						if (faceLen > minLen)break;
					}

					if (!HitTestTri(
						tmpVec,
						_rayPos,
						_rayDir, 
						poss[0],
						poss[1],
						poss[2]))continue;

					float tmpLen = tmpVec.Len();
					if (tmpLen > _rayLen)continue;
					hitFlg = true;
					if (minLen < tmpLen)continue;
					minLen = tmpLen;
					hitMaterialName = frameCom->materialList[primitive->mateNo]->mateName;
					SetHitVector(tmpVec);
					break;
				}

			}
		}
	}

	for (auto&& child : _object.GetChildlen<FrameObject>())
	{
		hitFlg = IsHitRayToMesh(*child.lock(), _rayPos, _rayDir, minLen, hitFlg);
	}


	return hitFlg;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  PolygonCollider::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool PolygonCollider::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

void PolygonCollider::SetModel(FrameObject& _model)
{
	model = &_model;
}

FrameObject* PolygonCollider::GetModel()const
{
	return model;
}