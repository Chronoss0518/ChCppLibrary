
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChSprite11.h"

using namespace ChD3D11;

void Sprite11::Init()
{
	SetInitPosition();
	SetInitUV();
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetPos(const unsigned char _posNames, const  ChVec2& _posData)
{

	if (_posNames >= 4)return;

	vertexs[_posNames].pos = _posData;

}

void Sprite11::SetPosRect(const  ChVec4& _rect)
{
	vertexs[0].pos = ChVec2(_rect.left, _rect.top);
	vertexs[1].pos = ChVec2(_rect.right, _rect.top);
	vertexs[2].pos = ChVec2(_rect.right, _rect.bottom);
	vertexs[3].pos = ChVec2(_rect.left, _rect.bottom);
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	vertexs[_posNames].uv = ToUseUV(_posData);

}

void Sprite11::SetUVPosRect(const  ChVec4& _rect)
{
	vertexs[0].uv = ToUseUV(ChVec2(_rect.left, _rect.top));
	vertexs[1].uv = ToUseUV(ChVec2(_rect.right, _rect.top));
	vertexs[2].uv = ToUseUV(ChVec2(_rect.right, _rect.bottom));
	vertexs[3].uv = ToUseUV(ChVec2(_rect.left, _rect.bottom));
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetInitPosition()
{
	vertexs[0].pos = ChVec2(-1.0f, 1.0f);
	vertexs[1].pos = ChVec2(1.0f, 1.0f);
	vertexs[2].pos = ChVec2(1.0f, -1.0f);
	vertexs[3].pos = ChVec2(-1.0f, -1.0f);
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetInitUV()
{

	vertexs[0].uv = ToUseUV(ChVec2(0.0f, 1.0f));
	vertexs[1].uv = ToUseUV(ChVec2(1.0f, 1.0f));
	vertexs[2].uv = ToUseUV(ChVec2(1.0f, 0.0f));
	vertexs[3].uv = ToUseUV(ChVec2(0.0f, 0.0f));
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Move(const float _x, const float _y)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		vertexs[i].pos.x += _x;
		vertexs[i].pos.y += _y;
	}

}

ChVec2 Sprite11::ToUseUV(const ChVec2& _uv)
{
	ChVec2 res = _uv;
	res.y = 1.0f - res.y;
	return res;
}