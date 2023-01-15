#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChSampleShaderBase11.h"

using namespace ChD3D11;
using namespace Shader;

void SampleShaderBase11::Init(ID3D11Device* _device)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(_device))return;

	device = _device;

	whiteTex = ChPtr::Make_U<Texture11>();
	normalTex = ChPtr::Make_U<Texture11>();

	whiteTex->CreateColorTexture(_device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);
	normalTex->CreateColorTexture(_device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	InitVertexShader();
	InitPixelShader();

	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_COLOR;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	SampleShaderBase11::CreateBlender(desc);

	SetInitFlg(true);
}

void SampleShaderBase11::InitVertexShader(
	const D3D11_INPUT_ELEMENT_DESC* _decl,
	unsigned long _declNum,
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;

	vs.Init(device, _decl, _declNum, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::InitPixelShader(
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;

	ps.Init(device, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::Release()
{
	if (!IsInit())return;
	if (ChPtr::NotNullCheck(rasteriser))
	{
		rasteriser->Release();
		rasteriser = nullptr;
	}

	if (ChPtr::NotNullCheck(blender))
	{
		blender->Release();
		blender = nullptr;
	}

	vs.Release();
	ps.Release();

	whiteTex = nullptr;
	normalTex = nullptr;

	SetInitFlg(false);
}


void SampleShaderBase11::SetShader(ID3D11DeviceContext* _dc)
{

	if (ChPtr::NullCheck(_dc))return;
	vs.SetShader(_dc);
	ps.SetShader(_dc);
}

void SampleShaderBase11::SetShaderRasteriser(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(rasteriser))return;

	_dc->RSSetState(rasteriser);
}

void SampleShaderBase11::SetShaderBlender(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(blender))return;

	_dc->OMSetBlendState(blender, nullptr, 0xffffffff);
}

void SampleShaderBase11::SetShaderDefaultBlender(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;

	_dc->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void SampleShaderBase11::CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(rasteriser))
	{
		rasteriser->Release();
		rasteriser = nullptr;
	}

	device->CreateRasterizerState(&_desc, &rasteriser);

}

void SampleShaderBase11::CreateBlender(const D3D11_BLEND_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(blender))
	{
		blender->Release();
		blender = nullptr;
	}

	device->CreateBlendState(&_desc, &blender);

}

void SampleShaderBase11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (GetShaderNowRunFlg())return;

	_dc->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	SetShader(_dc);

	Update();

	SetShaderRasteriser(_dc);


	drawFlg = true; 

	GetShaderNowRunFlg() = true;
}

