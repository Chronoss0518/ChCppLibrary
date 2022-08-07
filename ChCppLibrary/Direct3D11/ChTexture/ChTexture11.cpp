
//DirectXTex Library License//
/*

The MIT License (MIT)

Copyright (c) 2011-2021 Microsoft Corp

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../../External/DirectXTex/DirectXTex/DirectXTex.h"
#include"../../External/DirectXTex/WICTextureLoader/WICTextureLoader11.h"

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib, "DirectXTex_MDd.lib")
#else
#pragma comment(lib, "DirectXTex_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib, "DirectXTex_MD.lib")
#else
#pragma comment(lib, "DirectXTex_MT.lib")
#endif

#endif

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
//#include"../ChTexture/ChBaseTexture11.h"
//#include"../ChMesh/ChBaseMesh11.h"
//#include"../ChLight/ChLight11.h"
#include"ChTexture11.h"

using namespace ChD3D11;

void TextureBase11::Release()
{

	if (ChPtr::NotNullCheck(sampler)) { sampler->Release(); sampler = nullptr; }
	if (ChPtr::NotNullCheck(texView)) { texView->Release(); texView = nullptr; }
	if (ChPtr::NotNullCheck(baseTex)) { baseTex->Release(); baseTex = nullptr; }

	if (textureSize > 0)
	{
		textureSize < 2 ? delete pixelData : delete[] pixelData;
		textureSize = 0;
		pixelData = nullptr;
	}
}

void TextureBase11::InitSampler()
{

	ZeroMemory(&sDesc, sizeof(D3D11_SAMPLER_DESC));
	sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	UpdateSampler();
}

void TextureBase11::UpdateSampler()
{
	if (!sdUpdateFlg)return;

	device->CreateSamplerState(&sDesc, &sampler);

	sdUpdateFlg = false;
}

void TextureBase11::SetDrawData(ID3D11DeviceContext* _dc, unsigned int _textureNo)
{
	if (ChPtr::NullCheck(texView))return;

	UpdateSampler();

	_dc->PSSetShaderResources(_textureNo, 1, &texView);
	_dc->PSSetSamplers(_textureNo, 1, &sampler);

}

void TextureBase11::CreateSRV()
{


	if (ChPtr::NullCheck(baseTex))return;

	D3D11_TEXTURE2D_DESC txDesc;

	baseTex->GetDesc(&txDesc);



	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = txDesc.Format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = txDesc.MipLevels;
	desc.Texture2D.MostDetailedMip = 0;

	device->CreateShaderResourceView(baseTex, &desc, &texView);

}

void TextureBase11::Init(ID3D11Device* _device)
{

	InitSampler();

	device = _device;
}

void Texture11::CreateTexture(const std::string& _texPath)
{
	if (!D3D11API().IsInit())return;

	ID3D11Device* tmpDevice = D3D11Device();

	CreateTexture(_texPath, tmpDevice);

}

void Texture11::CreateTexture(const std::string& _texPath, ID3D11Device* _device)
{
	if (ChPtr::NullCheck(_device))return;

	Release();

	device = _device;

	if (FAILED(DirectX::CreateWICTextureFromFile(
		device
		, ChStr::UTF8ToWString(_texPath).c_str()
		, (ID3D11Resource**)&baseTex
		, &texView)))
	{
		Release();
		return;
	}

	Init(_device);
}

void Texture11::CreateTexture(const std::wstring& _texPath)
{

	if (!D3D11API().IsInit())return;

	ID3D11Device* tmpDevice = (D3D11Device());

	CreateTexture(_texPath, tmpDevice);
}

void Texture11::CreateTexture(const std::wstring& _texPath, ID3D11Device* _device)
{

	if (ChPtr::NullCheck(_device))return;

	Release();

	device = _device;

	if (FAILED(DirectX::CreateWICTextureFromFile(
		device
		, _texPath.c_str()
		, (ID3D11Resource**)&baseTex
		, &texView)))
	{
		Release();
		return;
	}

	Init(_device);
}

void Texture11::CreateColorTexture(
	const ChVec4& _color
	, const unsigned long _width
	, const unsigned long _height
	, const unsigned int _CPUFlg)
{


	if (!D3D11API().IsInit())return;

	ID3D11Device* tmpDevice = (D3D11Device());

	CreateColorTexture(tmpDevice, _color,_width,_height, _CPUFlg);
}

void Texture11::CreateColorTexture(
	ID3D11Device* _device
	, const ChVec4& _color
	, const unsigned long _width
	, const unsigned long _height
	, const unsigned int _CPUFlg)
{

	if (ChPtr::NullCheck(_device))return;
	if (_width <= 0 || _height <= 0)return;
	if (_width >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION
		|| _height >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)return;


	Release();

	device = _device;

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Width = _width;
	Desc.Height = _height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags = _CPUFlg;
	Desc.MiscFlags = 0;

	textureSize = _height * _width;
	pixelData = new ChVec4[textureSize];

	for (unsigned long h = 0; h < _height; h++)
	{
		for (unsigned long w = 0; w < _width; w++)
		{
			pixelData[w + (h * w)] = (_color);
		}
	}

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = pixelData;
	Data.SysMemPitch = _width * sizeof(ChVec4);
	Data.SysMemSlicePitch = _height * _width * sizeof(ChVec4);

	device->CreateTexture2D(&Desc, &Data, &baseTex);

	CreateSRV();

	Init(_device);
}

void Texture11::CreateColorTexture(
	const ChVec4* _colorArray
	, const unsigned long _width
	, const unsigned long _height
	, const unsigned int _CPUFlg)
{


	if (!D3D11API().IsInit())return;

	ID3D11Device* tmpDevice = (D3D11Device());

	CreateColorTexture(tmpDevice, _colorArray, _width, _height,_CPUFlg);
}

void Texture11::CreateColorTexture(
	ID3D11Device* _device
	, const ChVec4* _colorArray
	, const unsigned long _width
	, const unsigned long _height
	, const unsigned int _CPUFlg)
{

	if (ChPtr::NullCheck(_device))return;
	if (_width <= 0 || _height <= 0)return;
	if (_width >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION
		|| _height >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)return;


	Release();

	device = _device;

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Width = _width;
	Desc.Height = _height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags = _CPUFlg;
	Desc.MiscFlags = 0;

	textureSize = _height * _width;
	pixelData = new ChVec4[textureSize];

	for (unsigned long h = 0; h < _height; h++)
	{
		for (unsigned long w = 0; w < _width; w++)
		{
			pixelData[w + (h * w)] = (_colorArray[w + (h * w)]);
		}
	}

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = pixelData;
	Data.SysMemPitch = _width * sizeof(ChVec4);
	Data.SysMemSlicePitch = 0;

	device->CreateTexture2D(&Desc, &Data, &baseTex);

	CreateSRV();

	Init(_device);
}

void Texture11::CreateWhiteTex(ID3D11Device* _device)
{
	auto&& white = GetWhiteTex();

	if (white.IsTex())return;

	white.CreateColorTexture(_device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

	{

		D3D11_SAMPLER_DESC samp;

		samp.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		white.SetSampler(samp);
	}

}

void Texture11::CreateNormalTex(ID3D11Device* _device)
{
	auto&& normal = GetNormalTex();

	if (normal.IsTex())return;

	normal.CreateColorTexture(_device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	{

		D3D11_SAMPLER_DESC samp;

		samp.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		normal.SetSampler(samp);
	}
}

Texture11& Texture11::GetWhiteTex()
{
	static Texture11 white;
	return white;
}

Texture11& Texture11::GetNormalTex()
{
	static Texture11 normal;
	return normal;
}


void RenderTarget11::Release()
{

	if (ChPtr::NotNullCheck(rtView)) { rtView->Release(); rtView = nullptr; }

	TextureBase11::Release();
}

void RenderTarget11::CreateRenderTarget(
	const unsigned long _width
	, const unsigned long _height
	, const unsigned int _CPUFlg)
{

	if (!D3D11API().IsInit())return;

	ID3D11Device* tmpDevice = (D3D11Device());

	CreateRenderTarget(tmpDevice, _width, _height, _CPUFlg);
}

void RenderTarget11::CreateRenderTarget(
	ID3D11Device* _device
	, const unsigned long _width
	, const unsigned long _height
	, const unsigned int _CPUFlg)
{

	if (ChPtr::NullCheck(_device))return;

	Release();

	device = _device;

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Width = _width;
	Desc.Height = _height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags = _CPUFlg;
	Desc.MiscFlags = 0;

	_device->CreateTexture2D(&Desc, NULL, &baseTex);

	if (ChPtr::NullCheck(baseTex))return;

	if (FAILED(device->CreateRenderTargetView(baseTex, nullptr, &rtView)))
	{
		Release();
		return;
	}

	CreateSRV();

	Init(_device);
}

void RenderTarget11::SetBackColor(ID3D11DeviceContext* _dc, const ChVec4& _backColor)
{
	if (ChPtr::NullCheck(_dc))return;

	_dc->ClearRenderTargetView(rtView, _backColor.val.GetVal());
}

void DepthStencilTexture11::Release()
{

	if (ChPtr::NotNullCheck(dsView)) { dsView->Release(); dsView = nullptr; }

	TextureBase11::Release();
}

void DepthStencilTexture11::CreateDepthBuffer(
	const float& _width
	, const float& _height
	, const unsigned int _CPUFlg)
{

	if (!D3D11API().IsInit())return;

	ID3D11Device* tmpDevice = (D3D11Device());

	CreateDepthBuffer(tmpDevice, _width, _height, _CPUFlg);
}

void DepthStencilTexture11::CreateDepthBuffer(
	ID3D11Device* _device
	, const float& _width
	, const float& _height
	, const unsigned int _CPUFlg)
{
	if (ChPtr::NullCheck(_device))return;

	Release();

	device = _device;

	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = static_cast<unsigned int>(_width);
	txDesc.Height = static_cast<unsigned int>(_height);
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = _CPUFlg;
	txDesc.MiscFlags = 0;
	_device->CreateTexture2D(&txDesc, NULL, &baseTex);

	if (ChPtr::NullCheck(baseTex))return;


	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;

	device->CreateDepthStencilView(baseTex, &dsDesc, &dsView);

	CreateSRV();

	Init(_device);
}

void DepthStencilTexture11::ClearDepthBuffer(
	ID3D11DeviceContext* _dc
	, const UINT _flgment)
{
	if (ChPtr::NullCheck(_dc))return;

	_dc->ClearDepthStencilView(dsView, _flgment, 1.0f, 0);
}
