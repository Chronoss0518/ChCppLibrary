#include"../../../BaseIncluder/ChBase.h"
#include<cmath>
#include"../../ChModel/ChModel.h"

#include"../Box/ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"ChSphereCollider.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////

bool SphereCollider::IsHit(
	HitTestBox* _target)
{
	return _target->IsHit(this);
}

///////////////////////////////////////////////////////////////////////////////////////

bool  SphereCollider::IsHit(
	HitTestSphere* _target)
{
	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();

	ChVec3 mPos = GetPos();

	ChVec3 tScl = _target->GetScl(), mScl = GetScl();

	ChVec3 tmpVec = (tPos)-(mPos);

	ChVec3 objVec = tmpVec;
	objVec.Abs();

	ChVec3 testVec = objVec; 
	
	objVec.Normalize();

	tScl = objVec * tScl;
	mScl = objVec * mScl;

	objVec = tScl + mScl;

	//objVec = tScl + mScl;
	//objVec.Abs();

	//三角形の定理//
	//三辺にそれぞれa,b,cと置く//
	//bとcが垂直の時、aの長さは√(b)^2 + (c)^2 = aとなる。

	//float objectSize = mSize.Len() + tSize.Len();
	//float testLen = testVec.Len();

	//if (testVec.x > objVec.x)return false;
	//if (testVec.y > objVec.y)return false;
	//if (testVec.z > objVec.z)return false;
	if (testVec.Len() > objVec.Len())return false;
	
	{
		//auto len = (objectSize - testLen);
		auto lenVec = (objVec - testVec);
		//auto lenVec = testVec;
		lenVec.Abs();
		//tmpVec = testVec * -1.0f;
		tmpVec.Normalize();

		//tmpVec.val.SetLen(len);

		tmpVec.x *= lenVec.x;
		tmpVec.y *= lenVec.y;
		tmpVec.z *= lenVec.z;

	}

	SetHitVector(tmpVec * -1.0f);

	_target->SetHitVector(tmpVec);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

bool  SphereCollider::IsHit(
	HitTestRay* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

bool  SphereCollider::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

bool  SphereCollider::IsInnerHit(
	HitTestSphere* _target)
{

	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();


	ChVec3 tmpVec = mPos - tPos;

	float tmpLen = tmpVec.Len();

	//if (tmpLen + len <= _target->GetLen())return false;

	tmpVec.Normalize();

	//float moveSize = tmpLen + len;

	//moveSize = moveSize - _target->GetLen();

	//SetHitVector(tmpVec * -moveSize);

	//_target->SetHitVector(tmpVec * (moveSize));

	return true;

}
