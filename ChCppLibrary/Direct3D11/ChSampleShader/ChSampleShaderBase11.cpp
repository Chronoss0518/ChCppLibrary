#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChSampleShaderBase11.h"

using namespace ChD3D11;
using namespace Shader;

void SampleShaderBase11::Init(ID3D11Device* _device)
{
	if (ChPtr::NullCheck(_device))return;

	device = _device;
}

void SampleShaderBase11::Release()
{
	GetVBaseMesh().Release();
	GetVBasePobo().Release();
	GetPBasePolygon().Release();

	GetVBaseSprite().Release();
	GetPBaseSprite().Release();

	if (ChPtr::NotNullCheck(rasteriser))
	{
		rasteriser->Release();
		rasteriser = nullptr;
	}
}

void SampleShaderBase11::InitBaseMesh()
{
	if (ChPtr::NullCheck(device))return;

	InitVBaseMesh(device);
	InitPBasePolygon(device);
}

void SampleShaderBase11::InitBasePolygonBoard()
{
	if (ChPtr::NullCheck(device))return;

	InitVBasePobo(device);
	InitPBasePolygon(device);
}

void SampleShaderBase11::InitBaseSprite()
{
	if (ChPtr::NullCheck(device))return;

	InitVBaseSprite(device);
	InitPBaseSprite(device);
}

void SampleShaderBase11::SetShaderRasteriser(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(rasteriser))return;

	_dc->RSSetState(rasteriser);
}

void SampleShaderBase11::CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(rasteriser))return;

	device->CreateRasterizerState(&_desc, &rasteriser);

}

void SampleShaderBase11::InitVBaseMesh(ID3D11Device* _device)
{
	auto vertex = GetVBaseMesh();
	if (vertex.IsInit())return;

#include"PolygonShader/BaseMeshVertex.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[14];

		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[4] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[5] = { "BLENDINDEX",  0, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[6] = { "BLENDINDEX",  1, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[7] = { "BLENDINDEX",  2, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[8] = { "BLENDINDEX",  3, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[9] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[10] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[11] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[12] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[13] = { "BLENDINDEX",  4, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

		vertex.Init(_device, Decl, 14, main, sizeof(main));

	
}

void SampleShaderBase11::InitVBasePobo(ID3D11Device* _device)
{

	auto vertex = GetVBasePobo();
	if (vertex.IsInit())return;

#include"PolygonShader/BasePoboVertex.inc"

	D3D11_INPUT_ELEMENT_DESC Decl[4];


	Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	Decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


	vertex.Init(_device, Decl, 4, main, sizeof(main));
}

void SampleShaderBase11::InitPBasePolygon(ID3D11Device* _device)
{

	auto pixel = GetPBasePolygon();
	if (pixel.IsInit())return;
#include"PolygonShader/BasePolygonPixcel.inc"

	pixel.Init(_device, main, sizeof(main));

}

void SampleShaderBase11::InitVBaseSprite(ID3D11Device* _device)
{
	auto vertex = GetVBaseSprite();
	if (vertex.IsInit())return;

#include"SpriteShader/BaseSpriteVertex.inc"

	D3D11_INPUT_ELEMENT_DESC Decl[3];

	Decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	Decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


	vertex.Init(_device, Decl, 3, main, sizeof(main));

}

void SampleShaderBase11::InitPBaseSprite(ID3D11Device* _device)
{
	auto pixel = GetPBaseSprite();
	if (pixel.IsInit())return;

#include"../ChSampleShader/SpriteShader/BaseSpritePixel.inc"

	pixel.Init(_device, &main, sizeof(main));

}
