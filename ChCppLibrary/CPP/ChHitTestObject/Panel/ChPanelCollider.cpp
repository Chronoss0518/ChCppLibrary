#include"../../../BaseIncluder/ChBase.h"
#include<cmath>
#include"../../ChModel/ChModel.h"

#include"ChPanelCollider.h"

#include"../Box/ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"../Sphere/ChSphereCollider.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestRay Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool PanelCollider::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  PanelCollider::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  PanelCollider::IsHit(
	HitTestRay* _target)
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
		{
			pos = tmpMat.Transform(pos);
		}
	}

	ChStd::Bool hitFlg = HitTestTri(tmpVec, pos ,ray, square.pos[0], square.pos[1], square.pos[2]);

	if (tmpVec.Len() > maxLen)hitFlg = false;

	if (!hitFlg)hitFlg = HitTestTri(tmpVec, pos, ray, square.pos[0], square.pos[2], square.pos[3]);

	if (tmpVec.Len() > maxLen)hitFlg = false;

	if (hitFlg)
	{
		SetHitVector(tmpVec);
		_target->SetHitVector(tmpVec * -1.0f);
	}

	return hitFlg;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  PanelCollider::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool PanelCollider::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

Square PanelCollider::GetSquarePositions()
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