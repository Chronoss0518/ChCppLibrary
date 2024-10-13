
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChPolygonBoard/ChPolygonBoard9.h"
#include"../ChObjectController/ChObjectController9.h"
#include"ChPhysicalBase9.h"

using namespace ChMesh;

template<typename CharaType>
ChMesh::BaseMesh9<CharaType>* ChPhysicalBase9<CharaType>::GetMesh(unsigned long _num)
{
	if (_num >= wpXList.size())return nullptr;
	return wpXList[_num].lock().get();
}

template<typename CharaType>
unsigned long ChPhysicalBase9<CharaType>::GetMeshCount()
{
	return wpXList.size();
}

template<typename CharaType>
void ChPhysicalBase9<CharaType>::RemoveMesh(unsigned long _num)
{
	if (_num >= wpXList.size())return;
	wpXList.erase(wpXList.begin() + _num);
}

///////////////////////////////////////////////////////////////////////////////////
//ChGravity9メソッド
///////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChGravity9<CharaType>::Init(const float _FPS)
{
	ChPhysicalBase9<CharaType>::FPS = _FPS;
}

template<typename CharaType>
bool ChGravity9<CharaType>::UpDate(
	ChVec3_9* _pos,
	const ChVec3_9* _moveDir)
{
	ChPhysicalBase9<CharaType>::vec = ChVec3_9(0.0f, 0.0f, 0.0f);

	
	for (unsigned short i = 0; i < ChPhysicalBase9<CharaType>::GetMeshCount(); i++)
	{
		if (ChPhysicalBase9<CharaType>::GetMeshCount() <= 0)return false;

		auto tmpX = ChPhysicalBase9<CharaType>::GetMesh(i);

		if (tmpX == nullptr)
		{
			ChPhysicalBase9<CharaType>::RemoveMesh(i);
			i--;
			continue;
		}

		float tmpLen;
		ChVec3_9 tmpVec(0.0f, 0.0f, 0.0f);

		ChPhysicalBase9<CharaType>::vec = ChVec3_9(0.0f, -1.0f, 0.0f);

		ChPhysicalBase9<CharaType>::pow += g / ChPhysicalBase9<CharaType>::FPS;

		ChPhysicalBase9<CharaType>::pow -= _moveDir->y;

		if (_moveDir->y > 0.0f)
		{
			tmpSpeed = _moveDir->y;
			return true;
		}

		if (-tmpSpeed >= ChPhysicalBase9<CharaType>::pow)ChPhysicalBase9<CharaType>::pow = -tmpSpeed;
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
			ChPhysicalBase9<CharaType>::vec))continue;

		if (tmpLen - ChPhysicalBase9<CharaType>::baseLen - virtualHeight < ChPhysicalBase9<CharaType>::pow) {
			ChPhysicalBase9<CharaType>::vec *= (tmpLen - ChPhysicalBase9<CharaType>::baseLen - virtualHeight);
			*_pos = ChPhysicalBase9<CharaType>::vec + tmpPos;
			_pos->y -= _moveDir->y;
			ChPhysicalBase9<CharaType>::pow = 0.0f;

			return true;
		}

		ChPhysicalBase9<CharaType>::vec *= ChPhysicalBase9<CharaType>::pow;
		*_pos += ChPhysicalBase9<CharaType>::vec;
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////
//ChPushBack9メソッド
///////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChPushBack9<CharaType>::Init()
{

}

template<typename CharaType>
bool ChPushBack9<CharaType>::UpDate(ChVec3_9* _pos, const ChVec3_9* _dir)
{
	ChPhysicalBase9<CharaType>::vec = ChVec3_9(0.0f, 0.0f, 0.0f);
	ChVec3_9 tmpVec;
	ChVec3_9 tmpPos;
	float len;

	for (unsigned short i = 0; i < ChPhysicalBase9<CharaType>::GetMeshCount(); i++)
	{
		if (ChPhysicalBase9<CharaType>::GetMeshCount() <= 0)return false;

		auto tmpX = ChPhysicalBase9<CharaType>::GetMesh(i);

		if (tmpX == nullptr)
		{
			ChPhysicalBase9<CharaType>::RemoveMesh(i);
			i--;
			continue;
		}

		tmpVec = *_dir;
		tmpPos = *_pos;

		len = tmpVec.GetLen();

		tmpVec.Normalize();

		float tmpLen = 0.0f;
		DWORD faceNum;

		if (!ChPhysicalBase9<CharaType>::objCon->MeshHitRay(
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
