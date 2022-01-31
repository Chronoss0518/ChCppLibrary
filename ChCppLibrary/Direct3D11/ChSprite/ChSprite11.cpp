
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChSprite11.h"

using namespace ChD3D11;

SpriteVertexBuffer externalDrawVertexs;

void Sprite11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Init(ID3D11Device* _device)
{

	SetDevice((_device));

	SetInitPos();
	SetInitUV();

	vertexBuffer.CreateBuffer(_device, vertexNos, 4);
	indexBuffer.CreateBuffer(_device, indexNums, 6);
	constantBuffer.CreateBuffer(_device, ChStd::EnumCast(TextureConstantRegisterNo::SpriteVertex));

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetInitPos()
{
	vertexDatas.vertexs[0].pos = ChVec2(-1.0f, 1.0f);	//LeftTop//
	vertexDatas.vertexs[1].pos = ChVec2(1.0f, 1.0f);	//RightTop//
	vertexDatas.vertexs[2].pos = ChVec2(1.0f, -1.0f);	//RightDown//
	vertexDatas.vertexs[3].pos = ChVec2(-1.0f, -1.0f);//LeftDown//

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetInitUV()
{

	vertexDatas.vertexs[0].uv = ChVec2(0.0f, 0.0f);	//LeftTop//
	vertexDatas.vertexs[1].uv = ChVec2(1.0f, 0.0f);	//RightTop//
	vertexDatas.vertexs[2].uv = ChVec2(1.0f, 1.0f);	//RightDown//
	vertexDatas.vertexs[3].uv = ChVec2(0.0f, 1.0f);//LeftDown//

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetPos(const unsigned char _posNames, const  ChVec2& _posData)
{

	if (_posNames >= 4)return;

	vertexDatas.vertexs[_posNames].pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	vertexDatas.vertexs[_posNames].uv = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Move(const float _x, const float _y)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		vertexDatas.vertexs[i].pos.x += _x;
		vertexDatas.vertexs[i].pos.y += _y;
	}

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetDrawData(ID3D11DeviceContext* _dc)
{
	unsigned int offsets = 0;

	constantBuffer.UpdateResouce(_dc, &vertexDatas);

	vertexBuffer.SetVertexBuffer(_dc, offsets);
	indexBuffer.SetIndexBuffer(_dc);

	_dc->DrawIndexed(6, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetDrawData(ID3D11DeviceContext* _dc, const SpriteVertexBuffer& _vertexs)
{

	unsigned int offsets = 0;

	externalDrawVertexs = _vertexs;

	constantBuffer.UpdateResouce(_dc, &externalDrawVertexs);

	vertexBuffer.SetVertexBuffer(_dc, offsets);
	indexBuffer.SetIndexBuffer(_dc);

	_dc->DrawIndexed(6, 0, 0);
}