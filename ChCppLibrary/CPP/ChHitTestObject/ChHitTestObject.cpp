#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"ChHitTestObject.h"
#include"ChHitTestRay.h"
#include"ChHitTestPanel.h"
#include"ChHitTestBox.h"
#include"ChHitTestSphere.h"
#include"ChHitTestPolygon.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestRay Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsHit(
	HitTestPanel* _target)
{
	auto square = _target->GetSquarePositions();

	ChStd::Bool hitFlg = HitTestTri(square.pos[0], square.pos[1], square.pos[2]);

	if (!hitFlg)hitFlg = HitTestTri(square.pos[0], square.pos[2], square.pos[3]);

	return hitFlg;
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
	HitTestPolygon* _target)
{
	ChVec3 minLenVec = maxLen;
	ChStd::Bool hitFlg = false;

	for (auto poly : _target->GetPolygonList())
	{
		if (!HitTestTri(poly->poss[0], poly->poss[1], poly->poss[2]))continue;
		hitFlg = true;
		if (minLenVec.Len() < GetHitVectol().Len())continue;
		minLenVec = GetHitVectol();
	}

	if (hitFlg)_target->SetHitVector(minLenVec);

	return hitFlg;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

float HitTestRay::CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3)
{

	ChMath::BaseMatrix3x3<float> mat;

	ChVec3 tmp[3] = { _vec1,_vec2,_vec3 };

	for (unsigned char i = 0; i < mat.m.GetColumn(); i++)
	{
		for (unsigned char j = 0; j < mat.m.GetRow(); j++)
		{
			mat.m[i][j] = tmp[j].val[i];
		}
	}

	return mat.m.GetDeterminant();
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::HitTestTri(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3)
{
	//eg1 = (v1 - v0), eg2 = (v2 - v0);
	//hitPos = spos + (dir * len)
	//hitPos = (eg1 * u) + (eg2 * v) + v0
	//spos + (dir * len) = (eg1 * u) + (eg2 * v) + v0
	//spos - v0 = (eg1 * u) + (eg2 * v) - (dir * len)

	//spos1 - v01 = eg11 * u + eg21 * v - dir1 * len
	//spos2 - v02 = eg12 * u + eg22 * v - dir2 * len
	//spos3 - v03 = eg13 * u + eg23 * v - dir3 * len
	//spos - v0 = v2sp

	//u = dat(v2sp,eg2,-dir)/dat(eg1.eg2.-dir)
	//v = dat(eg1,v2sp,-dir)/dat(eg1.eg2.-dir)
	//len = dat(eg1,eg2,v2sp)/dat(eg1.eg2.-dir)

	ChVec3 pos = GetPos();
	ChVec3 dir = GetMat().TransformCoord(rayDir);

	float u = 0.0f, v = 0.0f, len = 0.0f;

	ChVec3 eg1 = _vec2 - _vec1, eg2 = _vec3 - _vec1, v2sp = pos - _vec1;

	ChVec3 mdir = dir * -1;
	float divDat = 0.0f;


	divDat = CreateDat(eg1, eg2, mdir);

	if (divDat <= 0.0f)return false;

	u = CreateDat(v2sp, eg2, mdir);

	u = u / divDat;

	if (u < 0.0f || u > 1.0f)return false;

	v = CreateDat(eg1, v2sp, mdir);
	v = v / divDat;

	if (v < 0.0f || v > 1.0f)return false;

	float tmpVal = u + v;

	if (tmpVal < 0.0f || tmpVal > 1.0f)return false;

	len = CreateDat(eg1, eg2, v2sp);
	len = len / divDat;

	if (len < 0.0f || len > maxLen)return false;

	SetHitVector(dir * len);

	return true;
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
	HitTestPolygon* _target)
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

Square HitTestPanel::GetSquarePositions()
{
	Square out;

	ChVec3 tmpPos[4] = {
		ChVec3(-size.x / 2.0f,size.y / 2.0f,0.0f),
		ChVec3(size.x / 2.0f,size.y / 2.0f,0.0f),
		ChVec3(size.x / 2.0f,-size.y / 2.0f,0.0f),
		ChVec3(-size.x / 2.0f,-size.y / 2.0f,0.0f) };

	{
		auto tmpMat = GetMat();

		for (unsigned char i = 0; i < 4; i++)
		{
			out.pos[i] = tmpMat.Transform(tmpPos[i]);
		}

	}

	return out;

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
	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();

	ChVec3 tmpVec = tPos - mPos;
	ChVec3 tSize = _target->GetScl();
	ChVec3 mSize = GetScl();
	ChVec3 testVec = tmpVec;

	testVec.Abs();

	tSize.Abs();
	mSize.Abs();

	//x1,w1,x2,w2
	//x1 < x2 && x1 + w1 > x2

	if (testVec.x > mSize.x + tSize.x)return false;
	if (testVec.y > mSize.y + tSize.y)return false;
	if (testVec.z > mSize.z + tSize.z)return false;

	SetHitVector(tmpVec);

	_target->SetHitVector(tmpVec * -1.0f);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsHit(
	HitTestSphere* _target)
{
	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();

	ChVec3 mPos = GetPos();

	ChVec3 tmpVec = tPos - mPos;

	ChVec3 testVec = tmpVec;

	testVec.Abs();

	ChVec3 mSize = GetScl();

	ChVec3 tSize = testVec;

	tSize.Normalize();

	tSize *= _target->GetScl();

	//x1,w1,x2,w2
	//x1 < x2 && x1 + w1 > x2

	ChVec3 objVec = mSize + tSize;

	if (testVec.x > objVec.x)return false;
	if (testVec.y > objVec.y)return false;
	if (testVec.z > objVec.z)return false;

	tmpVec.Normalize();

	{
		auto lenVec = objVec - testVec;
		tmpVec.x *= lenVec.x;
		tmpVec.y *= lenVec.y;
		tmpVec.z *= lenVec.z;
	}
	//tmpVec *= _target->GetScl().Len() * _target->GetScl().Len();

	SetHitVector(tmpVec * -1.0f);

	_target->SetHitVector(tmpVec);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsHit(
	HitTestPolygon* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsInnerHit(
	HitTestBox* _target)
{

	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();

	ChVec3 tSize = _target->GetScl();
	ChVec3 mSize = GetScl();

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


Cube HitTestBox::CreateCube(const ChLMat& _mat)
{
	auto pos = _mat.GetPosition();
	auto scl = _mat.GetScalling();

	ChLMat mat;
	mat.SetPosition(pos);
	mat.SetScalling(scl);

	Cube out;

	for (unsigned long i = 0; i < 8; i++)
	{
		out.pos[i] = mat.Transform(out.pos[i]);
	}

	return out;
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
	return _target->IsHit(this);
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsHit(
	HitTestSphere* _target)
{
	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();

	ChVec3 mPos = GetPos();

	ChVec3 tScl = _target->GetScl(), mScl = GetScl();

	for (unsigned char i = 0; i < 3; i++)
	{
		if (tScl.val[i] > 0.0001f && tScl.val[i] < -0.0001f)
		{
			tScl.val[i] = tScl.val[i] < 1.0f ? -1.0f / tScl.val[i] : tScl.val[i] - 1.0f;
		}
		if (mScl.val[i] > 0.0001f && mScl.val[i] < -0.0001f)
		{
			mScl.val[i] = mScl.val[i] < 1.0f ? -1.0f / mScl.val[i] : mScl.val[i] - 1.0f;
		}
	}

	ChVec3 tmpVec = (tPos)-(mPos);

	ChVec3 objVec = tmpVec;
	objVec.Abs();
	objVec += ((tScl)) - ((mScl));
	objVec.Abs();

	auto testVec = objVec;

	objVec.Normalize();

	objVec *= 2;

	//三角形の定理//
	//三辺にそれぞれa,b,cと置く//
	//bとcが垂直の時、aの長さは√(b)^2 + (c)^2 = aとなる。

	//float objectSize = mSize.Len() + tSize.Len();
	//float testLen = testVec.Len();

	if (testVec.x > objVec.x)return false;
	if (testVec.y > objVec.y)return false;
	if (testVec.z > objVec.z)return false;

	//if (objectSize < testLen)return false;

	{
		//auto len = (objectSize - testLen);
		auto lenVec = (objVec - testVec);
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

ChStd::Bool  HitTestSphere::IsHit(
	HitTestPolygon* _target)
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

///////////////////////////////////////////////////////////////////////////////////////
//HitTestMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestPolygon::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestPolygon::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPolygon::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPolygon::IsHit(
	HitTestPolygon* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPolygon::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPolygon::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}
