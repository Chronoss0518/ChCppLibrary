#include"ChPanelCollider.h"

#include"../Box/ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"../Sphere/ChSphereCollider.h"

using namespace ChCpp;

bool PanelCollider::IsHit(HitTestBox* _target)
{
	return false;
}

bool  PanelCollider::IsHit(HitTestSphere* _target)
{
	return false;
}

bool  PanelCollider::IsHit(HitTestRay* _target)
{
	auto square = GetSquarePositions();

	ChVec3 tmpVec;

	ChVec3 pos;
	ChVec3 ray = _target->GetRayDir();
	float maxLen = _target->GetMaxLen();

	{
		auto tmp = _target->GetMat();
		pos = tmp.GetPosition();
		ray = tmp.TransformCoord(ray);
	}

	{
		ChLMat tmpMat = GetMat();

		for (auto&& pos : square.pos)
			pos = tmpMat.Transform(pos);
	}

	unsigned long numbers[4]{ 0,1,2,3 };

	if (!leftHandFlg)
	{
		numbers[0] = 3;
		numbers[1] = 2;
		numbers[2] = 1;
		numbers[3] = 0;
	}

	bool hitFlg = HitTestTri(tmpVec, pos ,ray, square.pos[numbers[0]], square.pos[numbers[1]], square.pos[numbers[2]]);

	if (tmpVec.GetLen() > maxLen)hitFlg = false;

	if (!hitFlg)hitFlg = HitTestTri(tmpVec, pos, ray, square.pos[numbers[0]], square.pos[numbers[2]], square.pos[numbers[3]]);

	if (tmpVec.GetLen() > maxLen)hitFlg = false;

	if (hitFlg)
	{
		SetHitVector(tmpVec);
		_target->SetHitVector(tmpVec * -1.0f);
	}

	return hitFlg;
}

bool  PanelCollider::IsInnerHit(HitTestBox* _target)
{
	return false;
}

bool PanelCollider::IsInnerHit(HitTestSphere* _target)
{
	return false;
}

PanelCollider::Square PanelCollider::GetSquarePositions()
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