#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChShaderParts11.h"

using namespace ChD3D11::ShaderParts;

///////////////////////////////////////////////////////////////////////////////////
//ViewPort Method//
///////////////////////////////////////////////////////////////////////////////////

void ViewPort::SetDrawData(ID3D11DeviceContext* _DC)
{
	if (ChPtr::NullCheck(_DC))return;

	_DC->RSSetViewports(1, &View);
}

///////////////////////////////////////////////////////////////////////////////////
//DrawWindow Method//
///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Init(
	ID3D11Device* _Device
	, IDXGISwapChain* _SC)
{

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_SC))return;

	Release();

	Window = _SC;

	ID3D11Texture2D* pBackBuffer = nullptr;

	Window->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	_Device->CreateRenderTargetView(pBackBuffer, nullptr, &BBTargetView);

	pBackBuffer->Release();

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Release()
{
	if (!*this)return;


	if (ChPtr::NotNullCheck(BBTargetView))
	{
		BBTargetView->Release();
		BBTargetView = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::SetDrawData(ID3D11DeviceContext* _DC,ID3D11DepthStencilView* _DSView)
{
	if (ChPtr::NullCheck(_DC))return;
	if (!*this)return;

	_DC->OMSetRenderTargets(1, &BBTargetView, _DSView);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::ClearView(ID3D11DeviceContext* _DC,const ChVec4& _Color)
{
	if (ChPtr::NullCheck(_DC))return;
	if (!*this)return;

	_DC->ClearRenderTargetView(BBTargetView, _Color.val.GetVal());
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Draw()
{
	if (!*this)return;

	Window->Present(SEffect, 0);
}

///////////////////////////////////////////////////////////////////////////////////
//ChLightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::Init(ID3D11Device* _Device)
{
	Release();

	Device = _Device;

	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));

	Desc.ByteWidth = sizeof(UseLightData);
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	Device->CreateBuffer(&Desc, nullptr, &Buf);

	{
		ChVec4 TmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			TmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		LightPow.CreateColorTexture(Device, TmpCol, 256, 1);


		D3D11_SAMPLER_DESC samp;

		samp.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		LightPow.SetSampler(samp);
	}



	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::Release()
{
	if (!*this)return;

	if (ChPtr::NotNullCheck(Buf))
	{
		Buf->Release();
		Buf = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightDiffuse(const ChVec3& _Dif)
{
	if (!*this)return;

	LightDatas.Light.Dif = _Dif;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetUseLightFlg(const ChStd::Bool& _Flg)
{
	if (!*this)return;

	LightDatas.Light.UseLightFlg = _Flg;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightDir(const ChVec3& _Dir)
{
	if (!*this)return;

	LightDatas.Light.Dir = _Dir;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightAmbientPow(const float _Amb)
{
	if (!*this)return;

	LightDatas.Light.AmbPow = _Amb;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightPos(const ChVec3& _Pos, const unsigned long _No)
{
	if (!*this)return;
	if (_No > 10)return;

	LightDatas.PLight[_No].Pos = _Pos;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightLen(const float _Len, const unsigned long _No)
{
	if (!*this)return;
	if (_No > 10)return;

	LightDatas.PLight[_No].Len = _Len;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightDiffuse(const ChVec3& _Dif, const unsigned long _No)
{
	if (!*this)return;
	if (_No > 10)return;

	LightDatas.PLight[_No].Dif = _Dif;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightUseFlg(const ChStd::Bool& _Flg, const unsigned long _No)
{
	if (!*this)return;
	if (_No > 10)return;

	LightDatas.PLight[_No].UseFlg = _Flg;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetCamPos(const ChVec3& _CamPos)
{
	if (!*this)return;

	LightDatas.CamPos = _CamPos;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightData(const ChLightHeader::LightData& _LD)
{
	if (!*this)return;

	LightDatas.CamPos = _LD.CamPos;
	LightDatas.Light = _LD.Light;
	for (unsigned long i = 0; i < 10; i++)
	{
		LightDatas.PLight[i] = _LD.PLight[i];
	}

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPSDrawData(ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	Update(_DC);

	_DC->PSSetConstantBuffers(10, 1, &Buf);

	SetTexture(_DC);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetVSDrawData(ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	Update(_DC);

	_DC->VSSetConstantBuffers(10, 1, &Buf);

	SetTexture(_DC);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetDrawData(ID3D11DeviceContext* _DC)
{

	if (!*this)return;

	Update(_DC);

	_DC->VSSetConstantBuffers(10, 1, &Buf);
	_DC->PSSetConstantBuffers(10, 1, &Buf);

	SetTexture(_DC);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetImportLightPowMap(ChPtr::Shared<Texture11>& _LightPowMap)
{
	if (!*this)return;

	ImportLightPowMap = _LightPowMap;
}

///////////////////////////////////////////////////////////////////////////////////

ChLightHeader::LightData ChLightHeader::GetLightData()
{
	LightData Out;

	if (!*this)return Out;

	Out.CamPos = LightDatas.CamPos;
	Out.Light = LightDatas.Light;

	for (unsigned long i = 0; i < 10; i++)
	{
		Out.PLight[i] = LightDatas.PLight[i];
	}

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::ClearImportLightPowMap()
{
	if (!*this)return;

	ImportLightPowMap = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetTexture(ID3D11DeviceContext* _DC)
{

	Texture11* TmpLightPow = &LightPow;

	if (ImportLightPowMap != nullptr)
	{
		if (ImportLightPowMap->IsTex())
		{
			TmpLightPow = ImportLightPowMap.get();
		}
	}

	TmpLightPow->SetDrawData(_DC, 10);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::Update(ID3D11DeviceContext* _DC)
{
	if (!UpdateFlg)return;

	_DC->UpdateSubresource(Buf, 0, nullptr, &LightDatas, 0, 0);

	UpdateFlg = false;
}