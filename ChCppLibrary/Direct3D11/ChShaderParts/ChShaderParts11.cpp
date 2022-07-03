#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChShaderParts11.h"

using namespace ChD3D11::ShaderParts;

///////////////////////////////////////////////////////////////////////////////////
//ViewPort Method//
///////////////////////////////////////////////////////////////////////////////////

void ViewPort::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;

	_dc->RSSetViewports(1, &View);
}

///////////////////////////////////////////////////////////////////////////////////
//DrawWindow Method//
///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Init(
	ID3D11Device* _device
	, IDXGISwapChain* _SC)
{

	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_SC))return;

	Release();

	window = _SC;

	ID3D11Texture2D* pBackBuffer = nullptr;

	window->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	_device->CreateRenderTargetView(pBackBuffer, nullptr, &bbTargetView);

	pBackBuffer->Release();

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Release()
{
	if (!*this)return;


	if (ChPtr::NotNullCheck(bbTargetView))
	{
		bbTargetView->Release();
		bbTargetView = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::SetDrawData(ID3D11DeviceContext* _dc,ID3D11DepthStencilView* _dsView)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!*this)return;

	_dc->OMSetRenderTargets(1, &bbTargetView, _dsView);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::ClearView(ID3D11DeviceContext* _dc,const ChVec4& _color)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!*this)return;

	_dc->ClearRenderTargetView(bbTargetView, _color.val.GetVal());
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Draw()
{
	if (!*this)return;

	window->Present(sEffect, 0);
}

///////////////////////////////////////////////////////////////////////////////////
//LightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void LightHeader::Init(ID3D11Device* _device, const unsigned long _bufferRegisterNo, const unsigned long _textureRegisterNo)
{
	Release();

	device = _device;

	buf.CreateBuffer(_device, _bufferRegisterNo);
	textureRegisterNo = _textureRegisterNo;

	{
		ChVec4 tmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			tmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		lightPow.CreateColorTexture(device, tmpCol, 256, 1);


		D3D11_SAMPLER_DESC samp;

		samp.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		lightPow.SetSampler(samp);
	}



	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::Release()
{
	if (!*this)return;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetLightDiffuse(const ChVec3& _dif)
{
	if (!*this)return;

	lightDatas.light.dif = _dif;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetUseLightFlg(const ChStd::Bool& _flg)
{
	if (!*this)return;

	lightDatas.light.useLightFlg = _flg;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetLightDir(const ChVec3& _dir)
{
	if (!*this)return;

	lightDatas.light.dir = _dir;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetLightAmbientPow(const float _amb)
{
	if (!*this)return;

	lightDatas.light.ambPow = _amb;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetPLightPos(const ChVec3& _pos, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].pos = _pos;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetPLightLen(const float _len, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].len = _len;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].dif = _dif;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetPLightUseFlg(const ChStd::Bool& _flg, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].useFlg = _flg;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetCamPos(const ChVec3& _camPos)
{
	if (!*this)return;

	lightDatas.camPos = _camPos;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetLightData(const LightHeader::LightData& _ld)
{
	if (!*this)return;

	lightDatas.camPos = _ld.camPos;
	lightDatas.light = _ld.light;
	for (unsigned long i = 0; i < 10; i++)
	{
		lightDatas.pLight[i] = _ld.pLight[i];
	}

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	buf.SetToPixelShader(_dc);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	buf.SetToVertexShader(_dc);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetDrawData(ID3D11DeviceContext* _dc)
{

	if (!*this)return;

	Update(_dc);

	buf.SetToVertexShader(_dc);
	buf.SetToPixelShader(_dc);


	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetImportLightPowMap(ChPtr::Shared<Texture11>& _lightPowMap)
{
	if (!*this)return;

	importLightPowMap = _lightPowMap;
}

///////////////////////////////////////////////////////////////////////////////////

LightHeader::LightData LightHeader::GetLightData()
{
	LightData Out;

	if (!*this)return Out;

	Out.camPos = lightDatas.camPos;
	Out.light = lightDatas.light;

	for (unsigned long i = 0; i < 10; i++)
	{
		Out.pLight[i] = lightDatas.pLight[i];
	}

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::ClearImportLightPowMap()
{
	if (!*this)return;

	importLightPowMap = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::SetTexture(ID3D11DeviceContext* _dc)
{

	Texture11* tmpLightPow = &lightPow;

	if (importLightPowMap != nullptr)
	{
		if (importLightPowMap->IsTex())
		{
			tmpLightPow = importLightPowMap.get();
		}
	}

	tmpLightPow->SetDrawData(_dc, textureRegisterNo);
}

///////////////////////////////////////////////////////////////////////////////////

void LightHeader::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	buf.UpdateResouce(_dc, &lightDatas);
}