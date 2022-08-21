
#include<windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChMesh/ChMesh11.h"
#include"../ChTexture/ChTexture11.h"
#include"../ChPolygonBoard/ChPolygonBoard11.h"
#include"../ChSprite/ChSprite11.h"

#include"../ChCB/ChCBSprite/ChCBSprite11.h"

#include"../ChSampleShader/SpriteShader/ChBaseDrawSprite11.h"

#include"ChShader11.h"

#define TEST_FLG 0

using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderController11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	DirectX3D11& _chDevice
	, const ChVec2& _windSize)
{
	if (!_chDevice.IsInit())return;

	Init(_chDevice.GetDevice(), _chDevice.GetDC(), _chDevice.GetSC(), _windSize.w, _windSize.h);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	DirectX3D11& _chDevice
	, const float& _windWitdh
	, const float& _windHeight)
{
	if (!_chDevice.IsInit())return;

	Init(_chDevice.GetDevice(), _chDevice.GetDC(), _chDevice.GetSC(), _windWitdh, _windHeight);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _device
	, ID3D11DeviceContext* _dc
	, IDXGISwapChain* _SC
	, const ChVec2& _windSize) 
{
	Init(_device, _dc, _SC, _windSize.w, _windSize.h);
}


///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _device
	, ID3D11DeviceContext* _dc
	, IDXGISwapChain* _SC
	, const float& _width
	, const float& _height)
{

	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(_SC))return;

	device = (_device);
	dc = (_dc);

	spvTex.InitChSpriteTextureVertexShader(_device);
	bpTex.InitChBaseSpritePixelShader(_device);

	spriteShader = ChPtr::Make_U<Shader::BaseDrawSprite>();
	spriteShader->Init(_device);

	dsBuffer.CreateDepthBuffer(_device, _width, _height);

	out3D.CreateRenderTarget(
		_device,
		static_cast<unsigned long>(_width),
		static_cast<unsigned long>(_height));

	out2D.CreateRenderTarget(
		_device,
		static_cast<unsigned long>(_width),
		static_cast<unsigned long>(_height));

	outSprite.Init(device);

	window.Init(_device, _SC);

	window.SetSwapEffect(DXGI_SWAP_EFFECT_DISCARD);

	view.SetDrawDepth(0.0f, 1.0f);
	view.SetTopLeftPos(ChVec2(0.0f, 0.0f));
	view.SetSize(ChVec2(_width, _height));

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Release()
{
	window.Release();

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetRenderTarget(RenderTarget11& _tex)
{
	if (!*this)return;
	if (drawFlg)return;
	if (ChPtr::NullCheck(_tex.GetRTView()))return;

	renderTargets.push_back(const_cast<ID3D11RenderTargetView*>(_tex.GetRTView()));

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawStart()
{

	if (!*this)return;
	if (drawFlg)return;

	rtDrawFlg = !renderTargets.empty();

	if (rtDrawFlg)
	{
		tmpView = &renderTargets[0];
		dc->OMSetRenderTargets(renderTargets.size(), tmpView, nullptr);

	}
	else
	{
		window.SetBackGroundColor(dc, backColor);

		dsBuffer.ClearDepthBuffer(dc);

		out3D.SetBackColor(dc, backColor);
		out2D.SetBackColor(dc, ChVec4(0.0f, 0.0f, 0.0f, 0.0f));

	}

	drawFlg = true;

	view.SetDrawData(dc);


}

//3Dの描画開始前に呼ぶ関数//
void ShaderController11::DrawStart3D()
{
	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());
	}

}

//2Dの描画開始前に呼ぶ関数//
void ShaderController11::DrawStart2D()
{
	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out2D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, nullptr);

		out3D.SetDrawData(dc, 12);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawEnd()
{

	if (!*this)return;
	if (!drawFlg)return;

	drawFlg = false;

	if (rtDrawFlg)return;

	if (ChPtr::NullCheck(device))return;

	window.SetDrawData(dc, nullptr);

	spriteShader->DrawStart(dc);

	spriteShader->Draw(dc, out3D, outSprite);

	spriteShader->Draw(dc, out2D, outSprite);

	spriteShader->DrawEnd();

	// バックバッファをプライマリバッファにコピー//
	window.Draw();

}
