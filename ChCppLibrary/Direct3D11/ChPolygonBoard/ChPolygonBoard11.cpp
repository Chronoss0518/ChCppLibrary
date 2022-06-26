
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

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Init(ID3D11Device* _device)
{
	SetInitSquare();

	vertexBuffer.CreateBuffer(_device, drawVertexs, 3);

	unsigned long indexs[3] = { 0,1,2 };

	indexBuffer.CreateBuffer(_device, indexs, 3);

	material.diffuse = ChVec4(1.0f);
	material.specular = ChVec4(0.0f);
	material.ambient = ChVec4(0.0f);

	materialBuffer.CreateBuffer(_device, 2);

}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	if (!vertexs.empty())vertexs.clear();
	vertexBuffer.Release();
	indexBuffer.Release();
}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetVertexList(const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& _vertexList)
{
	if (!vertexs.empty())vertexs.clear();

	for (auto ver : _vertexList)
	{
		vertexs.push_back(ver);
	}

}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetPos(const unsigned char  _posNames, const  ChVec3& _posData)
{

	if (_posNames >= vertexs.size())return;

	vertexs[_posNames]->pos = _posData;

}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{

	if (_posNames >= vertexs.size())return;

	vertexs[_posNames]->uv = _posData;

}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetInitSquare()
{
	if (!vertexs.empty())vertexs.clear();

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	
		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		
		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		vertexs.push_back(vertex);
	}

}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (vertexs.size() < 3)return;

	unsigned int offsets = 0;

	drawVertexs[0] = *vertexs[0];

	materialBuffer.UpdateResouce(_dc, &material);

	materialBuffer.SetToVertexShader(_dc);
	materialBuffer.SetToPixelShader(_dc);

	for (unsigned long i = 1; i < vertexs.size() - 1; i++)
	{
		drawVertexs[1] = *vertexs[i];
		drawVertexs[2] = *vertexs[i + 1];

		vertexBuffer.UpdateResouce(_dc, drawVertexs);

		vertexBuffer.SetVertexBuffer(_dc, offsets);

		indexBuffer.SetIndexBuffer(_dc);

		_dc->DrawIndexed(3, 0, 0);

		_dc->Flush();
	}

}

/////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::AddVertex(const Ch3D::PolyVertex& _vertexs)
{
	return;
	auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();
	vertex->pos = _vertexs.pos;
	vertex->uv = _vertexs.uv;
	vertex->color = _vertexs.color;
	vertex->normal = _vertexs.normal;
	vertexs.push_back(vertex);
}

/////////////////////////////////////////////////////////////////////////////////

