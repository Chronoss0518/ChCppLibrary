
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChRenderTargetManager9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChRenderTargetManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChTex::RenderTargetManager9<CharaType>::CreateDBData()
{
	dbData = ChPtr::Make_S<Texture9>();
}

template<typename CharaType>
void ChTex::RenderTargetManager9<CharaType>::ClearRT()
{
	if (rtList.empty())return;
	rtList.clear();
}

template<typename CharaType>
void RenderTargetManager9<CharaType>::Init(
	const LPDIRECT3DDEVICE9& _dv,
	const unsigned short _windWidth,
	const unsigned short _windHeight,
	const ChD3D9::ShaderController* _shader)
{
	CreateDBData();

	dbData->SetOriginalWidth(_windWidth);
	dbData->SetOriginalHeight(_windHeight);

	dbData->SetSclXSize(1.0f);
	dbData->SetSclYSize(1.0f);

	device = _dv;
	auto&& sur = dbData->GetSur();
	device->GetRenderTarget(0, &sur);
	auto&& zbuf = dbData->GetZBu();
	device->GetDepthStencilSurface(&zbuf);

	SetInitFlg(true);

	if (ChPtr::NullCheck(_shader))
	{
		if (!ChD3D9::Shader())return;
		uShader = &ChD3D9::Shader();
		return;
	}
	if (!*_shader)return;

	uShader = const_cast<ChD3D9::ShaderController*>(_shader);
}

template<typename CharaType>
void RenderTargetManager9<CharaType>::Release()
{
	ReturnRT();
	ClearRT();

	SetInitFlg(false);
}

template<typename CharaType>
void RenderTargetManager9<CharaType>::SetRT(
	const std::basic_string<CharaType>& _dataName,
	const D3DCOLOR _backCol)
{
	if (rtList.find(_dataName) == rtList.end())return;
	if (dbData == nullptr)return;

	if (ChPtr::NotNullCheck(uShader))
	{
		if (uShader->IsDraw())return;
	}

	device->SetRenderTarget(0, rtList[_dataName]->GetSur());
	device->SetDepthStencilSurface(rtList[_dataName]->GetZBu());


	if (ChPtr::NotNullCheck(uShader))
	{
		uShader->SetRTDraw(true);
		uShader->SetDrawDatas(_backCol);
	}

}

template<typename CharaType>
void RenderTargetManager9<CharaType>::CreateRT(
	const std::basic_string<CharaType>& _dataName,
	const UINT _rtWidth,
	const UINT _rtHeight,
	const _D3DFORMAT _format)
{
	if (_rtWidth <= 0 || _rtHeight <= 0)return;
	if (rtList.find(_dataName) != rtList.end())return;

	auto tmpRT = ChPtr::Make_S<Texture9>();

	tmpRT->CreateMinuColTexture<D3DCOLOR>(
		device,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		_rtWidth,
		_rtHeight,
		_format,
		D3DUSAGE_RENDERTARGET,
		D3DPOOL_DEFAULT);

	if (ChPtr::NullCheck(tmpRT->GetTex()))return;

	tmpRT->CreateSurface(0);

	if (ChPtr::NullCheck(tmpRT->GetSur()))return;

	tmpRT->CreateZBuffer(device);

	if (ChPtr::NullCheck(tmpRT->GetZBu()))return;

	rtList[_dataName] = tmpRT;
}

template<typename CharaType>
void RenderTargetManager9<CharaType>::ReturnRT()
{
	if (dbData == nullptr)return;
	device->SetRenderTarget(0, dbData->GetSur());
	device->SetDepthStencilSurface(dbData->GetZBu());

	if (ChPtr::NotNullCheck(uShader))
	{
		uShader->SetRTDraw(false);
	}
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(RenderTargetManager9);