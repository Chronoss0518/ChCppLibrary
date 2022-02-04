
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChSprite11.h"

using namespace ChD3D11;

void Sprite11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Init(ID3D11Device* _device)
{
	Release();

	SetDevice(_device);

	unsigned long indexs[6]{ 0,1,2,0,2,3 };
	indexBuf.CreateBuffer(_device, indexs, 6);

	SetInitPos();

	SetInitUV();

	vertexBuf.CreateBuffer(_device, vertexs, 4);

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Release()
{
	ShaderObject<Vertex11>::Release();
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetPos(const unsigned char _posNames, const  ChVec2& _posData)
{

	if (_posNames >= 4)return;

	vertexs[_posNames].pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	vertexs[_posNames].uvPos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetColor(const unsigned char _posNames, const ChVec4& _color)
{
	if (_posNames >= 4)return;

	vertexs[_posNames].color = _color;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetInitPos()
{

	vertexs[0].pos = ChVec2(-1.0f, 1.0f);	//LeftTop//
	vertexs[1].pos = ChVec2(1.0f, 1.0f);	//RightTop//
	vertexs[2].pos = ChVec2(1.0f, -1.0f);	//RightDown//
	vertexs[3].pos = ChVec2(-1.0f, -1.0f);	//LeftDown//

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetInitUV()
{

	vertexs[0].uvPos = ChVec2(0.0f, 0.0f);	//LeftTop//
	vertexs[1].uvPos = ChVec2(1.0f, 0.0f);	//RightTop//
	vertexs[2].uvPos = ChVec2(1.0f, 1.0f);	//RightDown//
	vertexs[3].uvPos = ChVec2(0.0f, 1.0f);	//LeftDown//

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

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetDrawData(ID3D11DeviceContext* _dc)
{
	unsigned int offsets = 0;

	vertexBuf.SetVertexBuffer(_dc, offsets);
	indexBuf.SetIndexBuffer(_dc);

	_dc->DrawIndexed(6, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////

