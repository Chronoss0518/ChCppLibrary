
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

	SetInitSquare();

	vertexBuffer.CreateBuffer(_device, vertexs, 4);

	unsigned long indexs[6] = { 0,1,2,0,2,3 };

	indexBuffer.CreateBuffer(_device, indexs, 6);
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	//if (!vertexs.empty())vertexs.clear();
	vertexBuffer.Release();
	indexBuffer.Release();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetVertexList(const std::vector<ChPtr::Shared<MeshVertex11>>& _vertexList)
{
	Release();

	//for (auto ver : _vertexList)
	//{
	//	vertexs.push_back(ver);
	//}

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetPos(const unsigned char  _posNames, const  ChVec3& _posData)
{

	//if (_posNames >= vertexs.size())return;

	//vertexs[_posNames]->pos = _posData;

	if (_posNames >= 4)return;

	vertexs[_posNames].pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{

	//if (_posNames >= vertexs.size())return;

	//vertexs[_posNames]->uv = _posData;

	if (_posNames >= 4)return;

	vertexs[_posNames].uv = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetInitSquare()
{

	{
		//auto vertex = ChPtr::Make_S<MeshVertex11>();

		auto&& vertex = &vertexs[0];
		
		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		//vertexs.push_back(vertex);
	}

	{
		//auto vertex = ChPtr::Make_S<MeshVertex11>();

		auto&& vertex = &vertexs[1];
		
		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		//vertexs.push_back(vertex);
	}

	{
		//auto vertex = ChPtr::Make_S<MeshVertex11>();

		auto&& vertex = &vertexs[2];

		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	
		//vertexs.push_back(vertex);
	}

	{
		//auto vertex = ChPtr::Make_S<MeshVertex11>();

		auto&& vertex = &vertexs[3];

		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		//vertexs.push_back(vertex);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _dc)
{
	//if (vertexs.size() < 3)return;

	unsigned int offsets = 0;

	//for (unsigned long i = 1; i < vertexs.size() - 1; i++)
	//{
	//	MeshVertex11 ver[3];

	//	ver[0] = *vertexs[0];
	//	ver[1] = *vertexs[i];
	//	ver[2] = *vertexs[i + 1];

	//	vertexBuffer.SetDynamicBuffer(_dc, ver, 3);

	//	vertexBuffer.SetVertexBuffer(_dc, offsets);

	//	indexBuffer.SetIndexBuffer(_dc);

	//	_dc->DrawIndexed(3, 0, 0);

	//	_dc->Flush();
	//}


	vertexBuffer.UpdateResouce(_dc, vertexs);

	vertexBuffer.SetVertexBuffer(_dc, offsets);

	indexBuffer.SetIndexBuffer(_dc);

	_dc->DrawIndexed(6, 0, 0);

	_dc->Flush();

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::AddVertex(const MeshVertex11& _vertexs)
{
	return;
	auto vertex = ChPtr::Make_S<MeshVertex11>();
	vertex->pos = _vertexs.pos;
	vertex->uv = _vertexs.uv;
	vertex->color = _vertexs.color;
	vertex->normal = _vertexs.normal;
	//vertexs.push_back(vertex);
}

///////////////////////////////////////////////////////////////////////////////////

