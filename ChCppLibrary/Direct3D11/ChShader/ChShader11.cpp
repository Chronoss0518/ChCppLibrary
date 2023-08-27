
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

	spriteShader = ChPtr::Make_U<Shader::BaseDrawSprite11>();
	spriteShader->Init(_device);


	dsBuffer.CreateDepthBuffer(_device, _width, _height);

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

void ShaderController11::DrawStart()
{
	if (!*this)return;

	window.SetBackGroundColor(dc, backColor);
	dsBuffer.ClearDepthBuffer(dc);

	view.SetDrawData(dc);

	window.SetDrawData(dc, dsBuffer.GetDSView());
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawEnd()
{
	if (!*this)return;
	if (ChPtr::NullCheck(device))return;

	window.SetDrawData(dc, dsBuffer.GetDSView());

	// バックバッファをプライマリバッファにコピー//
	window.Draw();

}

void ShaderController11::DrawEnd(ChD3D11::TextureBase11& _tex)
{
	if (!*this)return;
	if (ChPtr::NullCheck(device))return;

	window.SetDrawData(dc, dsBuffer.GetDSView());

	spriteShader->DrawStart(dc);

	spriteShader->Draw(_tex, outSprite);

	spriteShader->DrawEnd();

	// バックバッファをプライマリバッファにコピー//
	window.Draw();

}

