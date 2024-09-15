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

#ifdef CRT

#include<wincodec.h>
#include"../../External/DirectXTex/DirectXTex/DirectXTex.h"
#include"../../External/DirectXTex/WICTextureLoader/WICTextureLoader11.h"

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib, "DirectXTex_MDd.lib")
#pragma comment(lib, "WICTextureLoader_MDd.lib")
#else
#pragma comment(lib, "DirectXTex_MTd.lib")
#pragma comment(lib, "WICTextureLoader_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib, "DirectXTex_MD.lib")
#pragma comment(lib, "WICTextureLoader_MD.lib")
#else
#pragma comment(lib, "DirectXTex_MT.lib")
#pragma comment(lib, "WICTextureLoader_MT.lib")
#endif

#endif
#endif

#ifndef Ch_D3D11_Tex_h
#define Ch_D3D11_Tex_h

struct IWICBitmap;

namespace ChD3D11
{

	class TextureBase11
	{
	public:

		virtual ~TextureBase11()
		{
			Release();
		}


	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		inline void SetSampler(D3D11_SAMPLER_DESC& _sDesc)
		{
			sDesc = _sDesc;
			sdUpdateFlg = true;
		}

		void SetDrawData(ID3D11DeviceContext* _dc, unsigned int _textureNo);

	public://Get Functions//

		ID3D11ShaderResourceView* GetSRView()
		{
			return texView;
		}

		ID3D11Resource* GetTex()
		{
			return baseTex;
		}

		D3D11_TEXTURE2D_DESC GetTextureDesc();


		D3D11_SAMPLER_DESC GetSamplerDesc()
		{
			return sDesc;
		}

		ChMath::Vector2Base<unsigned int> GetTextureSize();

	public://Is Functionss//

		bool IsTex() { return ChPtr::NotNullCheck(baseTex); }

	protected:

		void Init(ID3D11Device* _device);

		void CreateSRV();

		void InitSampler();

		void UpdateSampler();

		ChVec4 GetBitColor(
			const unsigned int _width,
			const unsigned int _height);

		D3D11_SAMPLER_DESC sDesc;
		bool sdUpdateFlg = true;
		ID3D11SamplerState* sampler = nullptr;

		ID3D11ShaderResourceView* texView = nullptr;

		ID3D11Texture2D* baseTex = nullptr;
		ChVec4* pixelData = nullptr;
		unsigned long textureSize = 0;

		ID3D11Device* device = nullptr;

	};

	class Texture11 :public TextureBase11
	{
	public://Constructer Destructer//

		Texture11() {}

	public://Create Functions//


#ifdef CRT
#ifndef CPP20

		void CreateTexture(
			const std::string& _texPath,
			ID3D11Device* _device)
		{
			CreateTexture(ChStr::UTF8ToWString(_texPath), _device);
		}

		void CreateTexture(const std::string& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = D3D11Device();
			CreateTexture(ChStr::UTF8ToWString(_texPath), tmpDevice);
		}

#endif
		void CreateTexture(
			const std::wstring& _texPath,
			ID3D11Device* _device)
		{
			if (ChPtr::NullCheck(_device))return;
			Release();

			device = _device;

			if (FAILED(DirectX::CreateWICTextureFromFile(
				device,
				_texPath.c_str(),
				(ID3D11Resource**)&baseTex,
				&texView)))
			{
				Release();
				return;
			}

			Init(_device);
		}

		void CreateTexture(const std::wstring& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = (D3D11Device());
			CreateTexture(_texPath, tmpDevice);
		}

#endif

		void CreateColorTexture(
			ID3D11Device* _device,
			const ChVec4& _color,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			const ChVec4& _color,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			ID3D11Device* _device,
			const ChVec4* _colorArray,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			const ChVec4* _colorArray,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			ID3D11Device* _device,
			IWICBitmap* _bitmap,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			IWICBitmap* _bitmap,
			const unsigned int _CPUFlg = 0);

	protected:

	};

	class RenderTarget11 :public TextureBase11
	{
	public://InitAndRelease//

		void Release()override;

	public://Create Functions//

		void CreateRenderTarget(
			ID3D11Device* _device,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateRenderTarget(
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

	public://Set Functions//

		void SetBackColor(ID3D11DeviceContext* _dc, const ChVec4& _buckColor);

	public://Get Functions//

		inline ID3D11RenderTargetView* GetRTView()
		{
			return rtView;
		}

	private://Member Values//

		ID3D11RenderTargetView* rtView = nullptr;
	};

	class DepthStencilTexture11 :public TextureBase11
	{
	public://Init And Release//

		void Release()override;

	public://Create Functions//

		void CreateDepthBuffer(
			ID3D11Device* _device,
			const float& _width,
			const float& _height,
			const unsigned int _CPUFlg = 0);

		void CreateDepthBuffer(
			const float& _width,
			const float& _height,
			const unsigned int _CPUFlg = 0);

	public://Other Functions//

		void ClearDepthBuffer(
			ID3D11DeviceContext* _dc,
			const UINT _flgment = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL);

	public://Get Functions//

		ID3D11DepthStencilView* GetDSView() { return dsView; }

	private://Member Values//

		ID3D11DepthStencilView* dsView = nullptr;

	};
}

#ifdef CRT

void ChD3D11::Texture11::CreateColorTexture(
	ID3D11Device* _device,
	IWICBitmap* _bitmap,
	const unsigned int _CPUFlg)
{
	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_bitmap))return;

	Release();

	WICRect wicRect;
	wicRect.X = 0;
	wicRect.Y = 0;
	{
		unsigned int w, h;
		_bitmap->GetSize(&w, &h);
		wicRect.Width = w;
		wicRect.Height = h;
	}
	device = _device;

	D3D11_TEXTURE2D_DESC Desc;
	ChStd::MZero(&Desc);
	Desc.Width = wicRect.Width;
	Desc.Height = wicRect.Height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags = _CPUFlg;
	Desc.MiscFlags = 0;

	UINT stride = wicRect.Width * 4;

	std::vector<unsigned char>testVector;
	testVector.resize(stride* wicRect.Height * 4);

	_bitmap->CopyPixels(nullptr, stride * 4, stride* wicRect.Height * 4, &testVector[0]);

	D3D11_SUBRESOURCE_DATA data;
	ChStd::MZero(&data);

	std::vector<ChVec4>tmpPixelData;
	tmpPixelData.resize(wicRect.Height* wicRect.Width);

	pixelData = new ChVec4[wicRect.Height * wicRect.Width];
	std::memcpy(&tmpPixelData[0], &testVector[0], testVector.size());

	for (unsigned long i = 0; i < tmpPixelData.size(); i++)
	{
		pixelData[i] = tmpPixelData[i];
	}

	data.pSysMem = pixelData;
	data.SysMemPitch = wicRect.Width * sizeof(ChVec4);
	data.SysMemSlicePitch = 0;


	device->CreateTexture2D(&Desc, &data, &baseTex);

	CreateSRV();

	Init(_device);
}


#endif

#endif
