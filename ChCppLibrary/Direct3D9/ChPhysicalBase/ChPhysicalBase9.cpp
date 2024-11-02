
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChPolygonBoard/ChPolygonBoard9.h"
#include"../ChObjectController/ChObjectController9.h"
#include"ChPhysicalBase9.h"

using namespace ChMesh;

ChMesh::BaseMesh9* ChPhysicalBase9::GetMesh(unsigned long _num)
{
	if (_num >= wpXList.size())return nullptr;
	return wpXList[_num].lock().get();
}

unsigned long ChPhysicalBase9::GetMeshCount()
{
	return wpXList.size();
}

void ChPhysicalBase9::RemoveMesh(unsigned long _num)
{
	if (_num >= wpXList.size())return;
	wpXList.erase(wpXList.begin() + _num);
}

///////////////////////////////////////////////////////////////////////////////////
//ChGravity9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChGravity9::Init(const float _FPS)
{
	ChPhysicalBase9::FPS = _FPS;
}

bool ChGravity9::UpDate(
	ChVec3_9* _pos,
	const ChVec3_9* _moveDir)
{
	ChPhysicalBase9::vec = ChVec3_9(0.0f, 0.0f, 0.0f);

	
	for (unsigned short i = 0; i < ChPhysicalBase9::GetMeshCount(); i++)
	{
		if (ChPhysicalBase9::GetMeshCount() <= 0)return false;

		auto tmpX = ChPhysicalBase9::GetMesh(i);

		if (tmpX == nullptr)
		{
			ChPhysicalBase9::RemoveMesh(i);
			i--;
			continue;
		}

		float tmpLen;
		ChVec3_9 tmpVec(0.0f, 0.0f, 0.0f);

		ChPhysicalBase9::vec = ChVec3_9(0.0f, -1.0f, 0.0f);

		ChPhysicalBase9::pow += g / ChPhysicalBase9::FPS;

		ChPhysicalBase9::pow -= _moveDir->y;

		if (_moveDir->y > 0.0f)
		{
			tmpSpeed = _moveDir->y;
			return true;
		}

		if (-tmpSpeed >= ChPhysicalBase9::pow)ChPhysicalBase9::pow = -tmpSpeed;
		tmpSpeed = 0.0f;

		ChVec3_9 tmpPos = *_pos;
		tmpPos.y += virtualHeight;
		
		DWORD tmpD;

		if (!ChObjCon9().MeshHitRay(
			tmpD,
			tmpLen,
			*tmpX,
			ChMat_9(),
			tmpPos,
			ChPhysicalBase9::vec))continue;

		if (tmpLen - ChPhysicalBase9::baseLen - virtualHeight < ChPhysicalBase9::pow) {
			ChPhysicalBase9::vec *= (tmpLen - ChPhysicalBase9::baseLen - virtualHeight);
			*_pos = ChPhysicalBase9::vec + tmpPos;
			_pos->y -= _moveDir->y;
			ChPhysicalBase9::pow = 0.0f;

			return true;
		}

		ChPhysicalBase9::vec *= ChPhysicalBase9::pow;
		*_pos += ChPhysicalBase9::vec;
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////
//ChPushBack9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPushBack9::Init()
{

}

bool ChPushBack9::UpDate(ChVec3_9* _pos, const ChVec3_9* _dir)
{
	ChPhysicalBase9::vec = ChVec3_9(0.0f, 0.0f, 0.0f);
	ChVec3_9 tmpVec;
	ChVec3_9 tmpPos;
	float len;

	for (unsigned short i = 0; i < ChPhysicalBase9::GetMeshCount(); i++)
	{
		if (ChPhysicalBase9::GetMeshCount() <= 0)return false;

		auto tmpX = ChPhysicalBase9::GetMesh(i);

		if (tmpX == nullptr)
		{
			ChPhysicalBase9::RemoveMesh(i);
			i--;
			continue;
		}

		tmpVec = *_dir;
		tmpPos = *_pos;

		len = tmpVec.GetLen();

		tmpVec.Normalize();

		float tmpLen = 0.0f;
		DWORD faceNum;

		if (!ChPhysicalBase9::objCon->MeshHitRay(
			faceNum,
			tmpLen,
			*tmpX,
			ChMat_9(),
			tmpPos,
			tmpVec))continue;

		ChVec3_9 tmpDir;

		tmpDir = tmpX->GetFace(faceNum)->normal;

		tmpVec = -tmpVec;

		float tmpDot = D3DXVec3Dot(&tmpDir, &tmpVec);

		tmpVec = -tmpVec;

		if (tmpDot == 0.0f)continue;

		tmpDot = fabsf(tmpDot);

		float Limit = backLine / tmpDot;

		if (Limit < 0)Limit *= -1;

		if (tmpLen - len >= Limit)continue;

		*_pos += tmpDir * (Limit - tmpLen + len) * tmpDot;

		return true;
	}

	return false;

}
