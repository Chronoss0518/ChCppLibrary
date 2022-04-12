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

	ChVec3 tmpVec = mPos - tPos;

	ChVec3 tSize = tmpVec;

	//|ap|・|bp| = 0// 
	//(px - ax,py - ay,pz - az) ・ (px - bx,py - by,pz - bz) = 0//

	//LenVec = dirVec * r^2

	tSize.Abs();
	tSize.Normalize();

	{

		// (x^2 + y^2 + z^2) = r^2
		// ((nx * l)^2 + (ny * l)^2 + (nz * l)^2) = r^2
		// l^2 = (r^2) / (nx^2 + ny^2 + nz^2)

		float tmp = ((tSize.x * tSize.x) + (tSize.y * tSize.y) + (tSize.z * tSize.z));
		if (tmp != 0)
		{

			float l = 1 / tmp;

			l = sqrtf(l);

			tSize *= l;

			tSize *= _target->GetScl();
		}

	}

	ChVec3 mSize = GetScl();

	ChVec3 testVec = tmpVec;

	testVec.Abs();
	mSize.Abs();

	//x1,w1,x2,w2
	//x1 < x2 && x1 + w1 > x2

	if (testVec.x > mSize.x + tSize.x)return false;
	if (testVec.y > mSize.y + tSize.y)return false;
	if (testVec.z > mSize.z + tSize.z)return false;

	tmpVec.Normalize();
	
	{
		auto lenVec = mSize + tSize - testVec;
		tmpVec.x *= sqrtf(lenVec.x);
		tmpVec.y *= sqrtf(lenVec.y);
		tmpVec.z *= sqrtf(lenVec.z);
	}

	//tmpVec *= _target->GetScl().Len() * _target->GetScl().Len();

	SetHitVector(tmpVec);

	_target->SetHitVector(tmpVec * -1.0f);

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


Cube HitTestBox::CreateCube()
{
	auto pos = GetPos();
	auto scl = GetScl();

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

	ChVec3 tmpVec = (tPos)- (mPos);

	ChVec3 tSize = tmpVec, mSize;
	tSize.Abs();
	tSize.Normalize();
	mSize = tSize;

	//x^2 + y^2 + z^2 = r^2
	//(nx * l)^2 + (ny * l)^2 + (nz * l)^2 = r^2
	// nx^2 * l^2 + ny^2 * l^2 + nz^2 * l^2 = r^2
	//l^2(nx^2 + ny^2 + nz^2) = r^2
	//l^2 = r^2 / (nx^2 + ny^2 + nz^2)

	float tmp = ((tSize.x * tSize.x) + (tSize.y * tSize.y) + (tSize.z * tSize.z));
	if (tmp != 0)
	{
		float l = 1 / tmp;

		l = sqrtf(l);
		//tSize *= tSize;
		tSize *= l;
		
		float r = ((tSize.x * tSize.x) + (tSize.y * tSize.y) + (tSize.z * tSize.z));

		mSize = tSize;
		tSize *= _target->GetScl();
		mSize *= GetScl();
	}

	auto testVec = tmpVec;

	testVec.Abs();

	//tmpVec *= tmpVec;

	//三角形の定理//
	//三辺にそれぞれa,b,cと置く//
	//bとcが垂直の時、aの長さは√(b)^2 + (c)^2 = aとなる。


	//float testSize = 1.0f;
	//float objectSize = 1.0f;

	//for (unsigned char i = 0; i < 3; i++)
	//{
	//	if (testVec.val[i] > 0.0f)testSize *= testVec.val[i];
	//	if ((mSize.val[i] + tSize.val[i]) > 0.0f)objectSize *= (mSize.val[i] + tSize.val[i]);
	//}

	//if (testSize > objectSize * 2)return false;


	if (testVec.x > mSize.x + tSize.x)return false;
	if (testVec.y > mSize.y + tSize.y)return false;
	if (testVec.z > mSize.z + tSize.z)return false;

	tmpVec.Normalize();


	{
		auto lenVec = mSize + tSize - testVec;
		tmpVec.x *= sqrtf(lenVec.x);
		tmpVec.y *= sqrtf(lenVec.y);
		tmpVec.z *= sqrtf(lenVec.z);
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
