
#include"../../ChBaseObject/ChBaseObject.h"
#include"../../ChModel/ChModelObject.h"

#include"../ChHitTestRay.h"
#include"ChPolygonCollider.h"
#include"../Sphere/ChSphereCollider.h"
#include"../Box/ChBoxCollider.h"


template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitRayToMesh(FrameObject<CharaType>& _object, const ChVec3& _rayPos, const ChVec3& _rayDir, const float _rayLen, const bool _nowHitFlg)
{
	bool hitFlg = _nowHitFlg;

	float minLen = _rayLen;

	hitFlg = IsHitTest(minLen, _object, _rayPos, _rayDir, hitFlg);

	for (auto&& child : _object.GetChildlen<FrameObject<CharaType>>())
	{
		hitFlg = IsHitRayToMesh(*child.lock(), _rayPos, _rayDir, minLen, hitFlg) || hitFlg;
	}

	return hitFlg;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitTest(float& _outLen, FrameObject<CharaType>& _object, const ChVec3& _rayPos, const ChVec3& _rayDir, const bool _nowHitFlg)
{

	_object.UpdateDrawTransform();

	ChLMat tmpMat = _object.GetDrawLHandMatrix() * GetMat();

	auto&& frameCom = GetFrameComponent(_object);

	if (frameCom == nullptr)return false;

	if (frameCom->vertexList.size() < 3)return false;

	bool hitFlg = _nowHitFlg;

	std::vector<ChPtr::Shared<ChVec3>>posList;

	for (unsigned long i = 0; i < frameCom->vertexList.size(); i++)
		posList.push_back(ChPtr::Make_S<ChVec3>(tmpMat.Transform(frameCom->vertexList[i]->pos)));

	ChVec3 poss[3];
	unsigned long nos[3]{ 0,1,2 };
	for (auto&& primitive : frameCom->primitives)
	{
		for (unsigned char j = 0; j < 3; j++)
		{
			nos[j] = !leftHandFlg ? primitive->vertexData.size() - j - 1 : j;
			poss[j] = *posList[primitive->vertexData[nos[j]]->vertexNo];
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

			for (unsigned char j = 1; j < 3; j++)
			{
				nos[j] = !leftHandFlg ? primitive->vertexData.size() - j - i : i + j - 1;
				poss[j] = *posList[primitive->vertexData[nos[j]]->vertexNo];
			}

			if (!HitTestTri(
				tmpVec,
				_rayPos,
				_rayDir,
				poss[0],
				poss[1],
				poss[2]))continue;

			float tmpLen = tmpVec.GetLen();
			if (tmpLen > _outLen)continue;
			hitFlg = true;
			if (_outLen < tmpLen)continue;
			_outLen = tmpLen;
			hitMaterialName = frameCom->materialList[primitive->mateNo]->mateName;
			SetHitVector(tmpVec);
			return true;
		}
	}
	return false;

}

template<typename CharaType>
void ChCpp::PolygonCollider<CharaType>::SetModel(FrameObject<CharaType>& _model)
{
	model = &_model;
}

template<typename CharaType>
ChCpp::FrameObject<CharaType>* ChCpp::PolygonCollider<CharaType>::GetModel()const
{
	return model;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestBox* _target)
{
	return false;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsInnerHit(HitTestBox* _target)
{
	return false;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestSphere* _target)
{
	auto&& model = GetModel();
	if (ChPtr::NullCheck(model))return false;
	return true;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsInnerHit(HitTestSphere* _target)
{
	return false;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestRay* _target)
{
	auto&& model = GetModel();

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

	bool hitFlg = IsHitRayToMesh(*model, pos, ray, minLen);

	if (hitFlg)
		_target->SetHitVector(GetHitVectol() * -1.0f);

	return hitFlg;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::PolygonCollider);
