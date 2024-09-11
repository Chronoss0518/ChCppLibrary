#include"ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"../Sphere/ChSphereCollider.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestBox Method//
///////////////////////////////////////////////////////////////////////////////////////

bool BoxCollider::IsHit(HitTestBox* _target)
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

bool BoxCollider::IsHit(HitTestSphere* _target)
{
	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();

	ChVec3 mPos = GetPos();

	
	ChVec3 tScl = _target->GetScl(), mScl = GetScl();

	ChVec3 tmpVec = (tPos)-(mPos);

	ChVec3 tmpPos[4] = { 1.0f,1.0f,1.0f,1.0f };

	tmpPos[1].x = -1.0f;
	tmpPos[2].y = -1.0f;
	tmpPos[3].z = -1.0f;

	{
		auto mat = GetMat();
		for (unsigned char i = 0; i < 4; i++)
		{
			tmpPos[i] = mat.TransformCoord(tmpPos[i]);
		}
	}
	
	//ベクトルABと点Pの距離(交点をV)//
	//AV = AB * x = AP - PV//
	//x = Dot(AB,AP)/(Len[AB]^2)//

	ChVec3 axisCoefficient;

	//それぞれの辺に対応する係数を取得//
	for (unsigned char i = 0; i < 3; i++)
	{
		auto vec = tmpPos[i + 1] - tmpPos[0];
		auto len = vec.GetLen();
		axisCoefficient.val[i] = vec.GetDot(tmpVec, vec) / (len * len);
	}

	//一番近い位置を取得

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

bool  BoxCollider::IsHit(HitTestRay* _target)
{
	return false;
}

bool  BoxCollider::IsInnerHit(HitTestBox* _target)
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

		if (hitFlgs.GetLen() <= 0.0f)return false;
	}

	SetHitVector(hitFlgs);

	_target->SetHitVector(hitFlgs * -1.0f);

	return true;
}

bool  BoxCollider::IsInnerHit(HitTestSphere* _target)
{
	return false;
}

Cube BoxCollider::CreateCube(const ChLMat& _mat)
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
