
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChRenderTargetManager9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChRenderTargetManager9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::Init(
	const LPDIRECT3DDEVICE9& _dv
	, const unsigned short _windWidth
	, const unsigned short _windHeight
	, const ChD3D9::ShaderController* _shader)
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

void RenderTargetManager9::Release()
{
	ReturnRT();
	ClearRT();

	SetInitFlg(false);
}

void RenderTargetManager9::ReturnRT()
{
	if (GetDBData() == nullptr)return;
	device->SetRenderTarget(0, GetDBData()->GetSur());
	device->SetDepthStencilSurface(GetDBData()->GetZBu());

	if (ChPtr::NotNullCheck(uShader))
	{
		uShader->SetRTDraw(false);
	}

}
