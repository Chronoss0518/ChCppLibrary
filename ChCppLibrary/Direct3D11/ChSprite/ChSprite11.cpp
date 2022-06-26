
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
	
	SetInitPosition();
	SetInitUV();

	vertexBuffer.CreateBuffer(_device, vertexs, vertexSize);

	indexBuffer.CreateBuffer(_device, indexs, indexSize);
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Release()
{
	vertexBuffer.Release();
	indexBuffer.Release();

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetPos(const unsigned char _posNames, const  ChVec2& _posData)
{

	if (_posNames >= 4)return;

	vertexs[_posNames].pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	vertexs[_posNames].uv = _posData;

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

	vertexs[0].uv = ChVec2(0.0f, 0.0f);
	vertexs[1].uv = ChVec2(1.0f, 0.0f);
	vertexs[2].uv = ChVec2(1.0f, 1.0f);
	vertexs[3].uv = ChVec2(0.0f, 1.0f);
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

	vertexBuffer.UpdateResouce(_dc, vertexs);

	vertexBuffer.SetVertexBuffer(_dc, offsets);

	indexBuffer.SetIndexBuffer(_dc);

	_dc->DrawIndexed(6, 0, 0);

	_dc->Flush();
}

///////////////////////////////////////////////////////////////////////////////////

