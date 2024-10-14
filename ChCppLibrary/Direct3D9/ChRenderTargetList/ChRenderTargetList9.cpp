
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChRenderTargetList9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChRenderTargetList9メソッド
///////////////////////////////////////////////////////////////////////////////////

void RenderTargetList9::Init(
	const LPDIRECT3DDEVICE9& _dv,
	const unsigned short _windWidth,
	const unsigned short _windHeight,
	const ChD3D9::ShaderController* _shader)
{
	CreateDBData();

	GetDBData()->SetOriginalWidth(_windWidth);
	GetDBData()->SetOriginalHeight(_windHeight);

	GetDBData()->SetSclXSize(1.0f);
	GetDBData()->SetSclYSize(1.0f);

	device = _dv;
	auto&& sur = GetDBData()->GetSur();
	device->GetRenderTarget(0, &sur);
	auto&& zbuf = GetDBData()->GetZBu();
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

void RenderTargetList9::Release()
{
	ReturnRT();
	ClearRT();
	ReleaseDBData();
	SetInitFlg(false);

}

void RenderTargetList9::SetRT(
	const unsigned short _dataNum,
	const D3DCOLOR _backCol
)
{
	auto&& rt = GetRTTexture(_dataNum);
	if (ChPtr::NullCheck(rt))return;
	if (ChPtr::NullCheck(GetDBData()))return;
	if (ChPtr::NotNullCheck(uShader))
	{
		if (uShader->IsDraw())return;
	}

	HRESULT Test = device->SetRenderTarget(0, rt->GetSur());

	device->SetDepthStencilSurface(rt->GetZBu());

	if (ChPtr::NotNullCheck(uShader))
	{
		uShader->SetRTDraw(true);
		uShader->SetDrawDatas(_backCol);
	}	
}

void RenderTargetList9::ReturnRT()
{
	if (ChPtr::NullCheck(GetDBData()))return;

	device->SetRenderTarget(0, GetDBData()->GetSur());
	device->SetDepthStencilSurface(GetDBData()->GetZBu());

	if (ChPtr::NotNullCheck(uShader))
	{
		uShader->SetRTDraw(false);
	}
}


void ChTex::RenderTargetList9::CreateDBData()
{
	dbData = ChPtr::Make_S<Texture9>();
}

ChTex::BaseTexture9* ChTex::RenderTargetList9::GetDBData()
{
	return dbData.get();
}

void ChTex::RenderTargetList9::ReleaseDBData()
{
	dbData = nullptr;
}

//作成したテクスチャを取得//
ChTex::BaseTexture9* ChTex::RenderTargetList9::GetRTTexture(const unsigned short _dataNum)
{
	auto&& rt = rtList.find(_dataNum);
	if (rt == rtList.end())return nullptr;
	return rt->second.get();
}

//登録されてるテクスチャを選択して消去//
void ChTex::RenderTargetList9::DeleteRTTexture(const unsigned short _dataNum)
{
	if (rtList.empty())return;
	auto&& rt = rtList.find(_dataNum);
	if (rt == rtList.end())return;

	rtList.erase(rt);
}

//登録してあるすべてのレンダーターゲットテクスチャを解放//
void ChTex::RenderTargetList9::ClearRT()
{
	if (rtList.empty())return;
	rtList.clear();
}