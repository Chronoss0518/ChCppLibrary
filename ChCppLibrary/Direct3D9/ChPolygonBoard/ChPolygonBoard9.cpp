
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChPolygonBoard9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChPolygonBord9���\�b�h
///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::Init(const LPDIRECT3DDEVICE9& _dv)
{
	device = _dv;
	SetXYPosition(ChVec3_9(1.0f, 1.0f, 0.0f), 2.0f, 2.0f);
	for (unsigned char i = 0; i < vertexMaxCnt; i++) {
		SetColor(D3DCOLOR_ARGB(255, 255, 255, 255), i);
		//ver[i].specular = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	alphaFlg = FALSE;
	ver[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ver[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	ver[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	ver[3].tex = D3DXVECTOR2(0.0f, 1.0f);

	SetInitFlg(true);
}

void PolygonBoard9::SetXYPosition(const ChVec3_9& _leftTopPos, const float _x, const float _y)
{
	for (char i = 0; i < vertexMaxCnt; i++) {
		ver[i].pos = _leftTopPos;
	}

	ver[1].pos.x += _x;
	ver[2].pos.x += _x;
	ver[2].pos.y -= _y;
	ver[3].pos.y -= _y;
}

void PolygonBoard9::SetYZPosition(const ChVec3_9& _leftTopPos, const float _z, const float _y)
{
	for (char i = 0; i < vertexMaxCnt; i++) {
		ver[i].pos = _leftTopPos;
	}

	ver[1].pos.z += _z;
	ver[2].pos.z += _z;
	ver[2].pos.y -= _y;
	ver[3].pos.y -= _y;
}

void PolygonBoard9::SetZXPosition(const ChVec3_9& _leftTopPos, const float _x, const float _z)
{
	for (char i = 0; i < vertexMaxCnt; i++) {
		ver[i].pos = _leftTopPos;
	}

	ver[1].pos.x += _x;
	ver[2].pos.x += _x;
	ver[2].pos.z -= _z;
	ver[3].pos.z -= _z;
}

void PolygonBoard9::SetPositionVector(const D3DXVECTOR3& _pos, const char _posNo)
{
	if (_posNo > vertexMaxCnt)return;
	ver[_posNo].pos = _pos;
}

void PolygonBoard9::SetColor(const D3DCOLOR& _col, const unsigned char _posNo)
{
	if (_posNo > vertexMaxCnt)return;
	ver[_posNo].col = _col;
}

void PolygonBoard9::SetTex(const D3DXVECTOR2& _tex, const unsigned char _posNo)
{
	if (_posNo > vertexMaxCnt)return;
	ver[_posNo].tex = _tex;
}
