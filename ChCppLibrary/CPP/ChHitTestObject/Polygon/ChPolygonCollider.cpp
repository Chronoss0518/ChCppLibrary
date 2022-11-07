#include"../../../BaseIncluder/ChBase.h"
#include<cmath>
#include"../../ChModel/ChModel.h"
#include"../../ChModel/ChModelObject.h"

#include"ChPolygonCollider.h"

#include"../Box/ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"../Sphere/ChSphereCollider.h"


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
	float maxLen = _target->GetMaxLen();
	float minLen = maxLen;
	ChVec3 ray = _target->GetRayDir();
	ChStd::Bool hitFlg = false;
	ChVec3 hitVec;
	ChVec3 tmpVec;

	auto&& model = GetPolygonList();

#if 0
	for (auto poly :)
	{
		if (!HitTestTri(tmpVec, ray,poly->poss[0], poly->poss[1], poly->poss[2],_target))continue;
		float tmpLen = tmpVec.Len();
		if (tmpLen > maxLen)continue;
		hitFlg = true;
		if (minLen < tmpLen)continue;
		minLen = tmpLen;
		hitVec = tmpVec;
	}

	if (hitFlg)
	{
		SetHitVector(hitVec);
		_target->SetHitVector(hitVec * -1.0f);
	}

	return hitFlg;
#endif

	return false;
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
