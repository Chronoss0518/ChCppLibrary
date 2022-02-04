
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

	MeshVertex11 bufVertex[3];

	vertexBuffer.SetUsageFlg(D3D11_USAGE::D3D11_USAGE_DYNAMIC);
	vertexBuffer.SetCPUAccessFlg(D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE);

	vertexBuffer.CreateBuffer(_device, bufVertex, 3);

	SetInitSquare();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	if (!vertexs.empty())vertexs.clear();
	vertexBuffer.Release();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetVertexList(const std::vector<ChPtr::Shared<MeshVertex11>>& _vertexList)
{
	Release();

	for (auto ver : _vertexList)
	{
		vertexs.push_back(ver);
	}
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetPos(const unsigned char  _posNames, const  ChVec3& _posData)
{

	if (_posNames >= vertexs.size())return;

	vertexs[_posNames]->pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{

	if (_posNames >= vertexs.size())return;

	vertexs[_posNames]->uv = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetInitSquare()
{

	{
		auto vertex = ChPtr::Make_S<MeshVertex11>();
		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<MeshVertex11>();
		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<MeshVertex11>();
		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<MeshVertex11>();
		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexs.push_back(vertex);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (vertexs.size() < 3)return;

	unsigned int offsets = 0;

	MeshVertex11 ver[3];

	ver[0] = *vertexs[0];

	for (unsigned long i = 1; i < vertexs.size() - 1; i++)
	{
		ver[1] = *vertexs[i];
		ver[2] = *vertexs[i + 1];

		vertexBuffer.SetDynamicBuffer(_dc, ver, 3);

		vertexBuffer.SetVertexBuffer(_dc, offsets);

		_dc->Draw(3, 0);

		_dc->Flush();
	}


}

///////////////////////////////////////////////////////////////////////////////////

