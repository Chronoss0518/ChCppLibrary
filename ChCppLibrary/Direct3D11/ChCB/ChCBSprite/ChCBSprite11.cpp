#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBSprite11.h"

using namespace ChD3D11;
using namespace CB;

///////////////////////////////////////////////////////////////////////////////////
//LightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void CBSprite11::Init(ID3D11Device* _device)
{
	Release();

	device = _device;

	drawBuf.CreateBuffer(device, DRAW_DATA_REGISTERNO);
	spBuf.CreateBuffer(device, SPRITE_DATA_REGISTERNO);

	Texture11::CreateWhiteTex(device);

	SetInitFlg(true);
}

void CBSprite11::Release()
{
	if (!*this)return;

	drawBuf.Release();
	spBuf.Release();

	SetInitFlg(false);

	dUpdateFlg = true;
	sUpdateFlg = true;
}

void CBSprite11::SetSpriteMatrix(const ChLMat& _mat)
{
	if (!*this)return;

	spData.spriteMat = _mat;

	sUpdateFlg = true;
}
\
void CBSprite11::SetWindSize(const ChVec2& _size)
{
	if (!*this)return;

	drawData.windSize = _size;

	dUpdateFlg = true;
}

void CBSprite11::SetBaseColor(const ChVec4& _color)
{
	if (!*this)return;

	spData.baseColor = _color;

	sUpdateFlg = true;
}

void CBSprite11::SetDrawData(const ChS_DrawData& _data)
{
	if (!*this)return;

	drawData = _data;

	dUpdateFlg = true;
}

void CBSprite11::SetSpriteData(const ChS_SpriteData& _data)
{
	if (!*this)return;

	spData = _data;

	sUpdateFlg = true;
}

void CBSprite11::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateDD(_dc);

	drawBuf.SetToPixelShader(_dc);
}

void CBSprite11::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateDD(_dc);

	drawBuf.SetToVertexShader(_dc);
}

void CBSprite11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSDrawData(_dc);
	SetPSDrawData(_dc);
}

void CBSprite11::SetPSSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	spBuf.SetToPixelShader(_dc);
}

void CBSprite11::SetVSSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	spBuf.SetToVertexShader(_dc);
}

void CBSprite11::SetShaderSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSSpriteData(_dc);
	SetPSSpriteData(_dc);
}

void CBSprite11::SetShaderTexture(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetShaderTexture(_dc, baseTex, Texture11::GetWhiteTex(), BASE_TEXTURE_REGISTER);

}

void CBSprite11::SetShaderTexture(ID3D11DeviceContext* _dc, ChPtr::Weak<TextureBase11> _tex, TextureBase11& _defaultTex, const unsigned long _registerNo)
{

	TextureBase11* tmpTex = &_defaultTex;

	if (!_tex.expired())
	{
		auto tex = _tex.lock();
		if (tex->IsTex())
		{
			tmpTex = tex.get();
		}
	}

	tmpTex->SetDrawData(_dc, _registerNo);
}

void CBSprite11::UpdateDD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!dUpdateFlg)return;
	drawBuf.UpdateResouce(_dc, &drawData);
	dUpdateFlg = false;
}

void CBSprite11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!sUpdateFlg)return;
	spBuf.UpdateResouce(_dc, &spData);
	sUpdateFlg = false;
}
