
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChPolygonBoard11.h"



using namespace ChD3D11;


void PolygonBoard11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Init(ID3D11Device* _device)
{
	Release();

	SetDevice((_device));

	vertexBuffer.CreateBuffer(_device, vertexNos, 3);
	indexBuffer.CreateBuffer(_device, indexNums, 3);
	constantBuffer.CreateBuffer(_device, ChStd::EnumCast(TextureConstantRegisterNo::PolygonBoardVertex));

	SetVertexs(GetInitSquareVertex());
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	if (!vertexList.empty())vertexList.clear();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _dc)
{
	unsigned int strides = sizeof(unsigned long);
	unsigned int offsets = 0;

	unsigned long startPos = 0;
	unsigned long nowReadPos = 1;

	vertexBuffer.SetVertexBuffer(_dc, offsets);
	indexBuffer.SetIndexBuffer(_dc);

	for (unsigned long i = 0; i < vertexList.size() - 2; i++)
	{
		if (nowReadPos + 1 >= vertexList.size())break;

		vertexDatas.vertex[0] = *vertexList[startPos];
		vertexDatas.vertex[1] = *vertexList[nowReadPos];
		vertexDatas.vertex[2] = *vertexList[nowReadPos + 1];

		constantBuffer.UpdateResouce(_dc, &vertexDatas);
		constantBuffer.SetToVertexShader(_dc);

		nowReadPos++;

		_dc->DrawIndexed(3, 0, 0);
	}

}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<PolygonBoardVertex>> PolygonBoard11::GetInitSquareVertex()
{
	std::vector<ChPtr::Shared<PolygonBoardVertex>> out;

	{
		auto vertex = ChPtr::Make_S<PolygonBoardVertex>();
		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		out.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<PolygonBoardVertex>();
		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		out.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<PolygonBoardVertex>();
		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		out.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<PolygonBoardVertex>();
		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		out.push_back(vertex);
	}

	return out;
}
