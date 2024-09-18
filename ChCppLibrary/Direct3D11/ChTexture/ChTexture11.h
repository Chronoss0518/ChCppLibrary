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

#ifndef Ch_D3D11_Tex_h
#define Ch_D3D11_Tex_h

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

#include"../../BasePack/ChStr.h"

struct IWICBitmap;

namespace ChD3D11
{

	class TextureBase11
	{
	public:

		struct TextureBase11CRT
		{
#ifdef CRT
			std::vector<ChVec4> pixelData;
#endif
		};

	public:

		TextureBase11();

		virtual ~TextureBase11();

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
		unsigned long textureSize = 0;

		ID3D11Device* device = nullptr;

		TextureBase11CRT& ValueIns() { return *value; }

	private:

		TextureBase11CRT* value = nullptr;

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

		D3D11_TEXTURE2D_DESC CreateDESC(
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg);

		ChVec4* SetPixel(const ChVec4* _colorArray, const unsigned long _textureSize);

		ChVec4* SetPixel(const ChVec4& _colorArray, const unsigned long _textureSize);
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

ChD3D11::TextureBase11::TextureBase11()
{
	value = new TextureBase11CRT();
}

ChD3D11::TextureBase11::~TextureBase11()
{
	Release();
	delete value;
}

void ChD3D11::Texture11::CreateColorTexture(
	ID3D11Device* _device,
	IWICBitmap* _bitmap,
	const unsigned int _CPUFlg)
{
	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_bitmap))return;

	Release();

	unsigned int w, h;
	_bitmap->GetSize(&w, &h);

	UINT stride = w * sizeof(ChVec4);

	std::vector<unsigned char>testVector;
	testVector.resize(stride * h);

	auto&&hresult = _bitmap->CopyPixels(nullptr, stride, stride * h, &testVector[0]);

	std::vector<ChVec4>tmpPixelData;
	tmpPixelData.resize(h * w);

	ChStr::Bytes<ChVec4> byte;

	ChVec4 test;
	for (unsigned long i = 0; i < h * w; i++)
	{
		for (unsigned long j = 0; j < sizeof(ChVec4); j++)
		{
			byte.byte[j] = testVector[j + (i * sizeof(ChVec4))];
		}
		if (test != byte.val)
		{
			test = byte.val;
		}
		tmpPixelData[i] = byte.val;
	}
	CreateColorTexture(_device, &tmpPixelData[0], w, h, _CPUFlg);
}

ChVec4* ChD3D11::Texture11::SetPixel(const ChVec4* _colorArray, const unsigned long _textureSize)
{
	textureSize = _textureSize;
	ValueIns().pixelData.resize(textureSize);

	ChVec4 test;

	for (unsigned long i = 0; i < textureSize; i++)
	{
		ValueIns().pixelData[i] = _colorArray[i];

		if (test != ValueIns().pixelData[i])
		{
			test = ValueIns().pixelData[i];
		}
	}
	return &ValueIns().pixelData[0];
}

ChVec4* ChD3D11::Texture11::SetPixel(const ChVec4& _color, const unsigned long _textureSize)
{
	textureSize = _textureSize;
	ValueIns().pixelData.resize(textureSize);

	ChVec4 test;

	for (unsigned long i = 0; i < textureSize; i++)
	{
		ValueIns().pixelData[i] = _color;

		if (test != ValueIns().pixelData[i])
		{
			test = ValueIns().pixelData[i];
		}
	}
	return &ValueIns().pixelData[0];
}

#endif

#endif
