
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

void PolygonBoard11::Init(ID3D11Device* _Device)
{
	Release();

	SetDevice((_Device));

	{
		vertexs[0].pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertexs[0].uvPos = ChVec2(0.0f, 0.0f);
		vertexs[0].color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		vertexs[1].pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertexs[1].uvPos = ChVec2(1.0f, 0.0f);
		vertexs[1].color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		vertexs[2].pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertexs[2].uvPos = ChVec2(1.0f, 1.0f);
		vertexs[2].color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		vertexs[3].pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertexs[3].uvPos = ChVec2(0.0f, 1.0f);
		vertexs[3].color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}


	vertexBuf.SetCPUAccessFlg(D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE);
	vertexBuf.SetUsageFlg(D3D11_USAGE::D3D11_USAGE_DYNAMIC);

	vertexBuf.CreateBuffer(_Device, vertexs, 4);

	unsigned long indexArray[6] = { 0,1,2,0,2,3 };


	indexBuf.CreateBuffer(_Device, indexArray, 6);

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	ShaderObject<MeshVertex11>::Release();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetPos(const unsigned char  _posNames, const  ChVec3& _posData)
{

	if (_posNames >= 4)return;

	ChVec3 tmpVec;

	vertexs[_posNames].pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	ChVec2 tmpVec;

	vertexs[_posNames].uvPos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _dc)
{
	unsigned int Offsets = 0;
	vertexBuf.SetDynamicBuffer(_dc, vertexs, 4);

	vertexBuf.SetVertexBuffer(_dc, Offsets);
	indexBuf.SetIndexBuffer(_dc);


	_dc->DrawIndexed(6, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////

