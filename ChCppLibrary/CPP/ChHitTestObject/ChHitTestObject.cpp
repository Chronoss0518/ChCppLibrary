#include"../../BaseIncluder/ChBase.h"

#include"ChHitTestObject.h"
#include"ChHitTestRay.h"
#include"ChHitTestPanel.h"
#include"ChHitTestBox.h"
#include"ChHitTestSphere.h"
#include"ChHitTestMesh.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestRay Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestPanel Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestPanel::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestPanel::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestBox Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestBox::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestBox::IsHit(
	HitTestBox* _target)
{


	//�ʒu��񂾂��̓����蔻��//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();

	ChVec3 tmpVec = mPos - tPos;
	ChVec3 tSize = _target->GetSize();
	ChVec3 mSize = size;

	ChVec3 testVec = tmpVec;
	testVec.Abs();


	if (tSize.x + mSize.x < testVec.x)return false;
	if (tSize.y + mSize.y < testVec.y)return false;
	if (tSize.z + mSize.z < testVec.z)return false;

	ChVec3 moveSize = testVec - (tSize + mSize);

	tmpVec *= moveSize;

	SetHitVector(tmpVec);

	_target->SetHitVector(tmpVec * -1.0f);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsInnerHit(
	HitTestBox* _target)
{

	//�ʒu��񂾂��̓����蔻��//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();

	ChVec3 tSize = _target->GetSize();
	ChVec3 mSize = size;

	ChVec3 testVec = mPos - tPos;
	testVec.Abs();


	ChVec3 hitFlgs = 0.0f;

	{

		if (tSize.x < testVec.x + mSize.x)hitFlgs.x = testVec.x + mSize.x - tSize.x;
		if (tSize.y < testVec.y + mSize.y)hitFlgs.y = testVec.y + mSize.y - tSize.y;
		if (tSize.z < testVec.z + mSize.z)hitFlgs.z = testVec.z + mSize.z - tSize.z;


		if (hitFlgs.Len() <= 0.0f)return false;
	}

	SetHitVector(hitFlgs);

	_target->SetHitVector(hitFlgs * -1.0f);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestSphere Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestSphere::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestSphere::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsHit(
	HitTestSphere* _target)
{
	//�ʒu��񂾂��̓����蔻��//

	ChVec3 tPos = _target->GetPos();

	ChVec3 mPos = GetPos();

	ChVec3 tmpVec = mPos - tPos;

	float tmpLen = tmpVec.Len();

	if (tmpLen >= (_target->GetLen() + len))return false;

	tmpVec.Normalize();

	float moveSize = tmpLen - len;

	moveSize = _target->GetLen() - moveSize;

	SetHitVector(tmpVec * moveSize);

	_target->SetHitVector(tmpVec * (-moveSize));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsInnerHit(
	HitTestSphere* _target)
{

	//�ʒu��񂾂��̓����蔻��//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();


	ChVec3 tmpVec = mPos - tPos;

	float tmpLen = tmpVec.Len();

	if (tmpLen + len <= _target->GetLen())return false;

	tmpVec.Normalize();

	float moveSize = tmpLen + len;

	moveSize = moveSize - _target->GetLen();

	SetHitVector(tmpVec * -moveSize);

	_target->SetHitVector(tmpVec * (moveSize));

	return true;

}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestMesh::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestMesh::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}
