
#include<windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"


#include"../ChMesh/ChMesh11.h"
#include"../ChTexture/ChTexture11.h"
#include"../ChPolygonBoard/ChPolygonBoard11.h"
#include"../ChSprite/ChSprite11.h"
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

	bvModel.InitChBaseModelVertexShader(_device);
	pvTex.InitChPolygonboardTextureVertexShader(_device);
	bpModel.InitChBasePolygonPixelShader(_device);

	spvTex.InitChSpriteTextureVertexShader(_device);
	bpTex.InitChBaseSpritePixelShader(_device);

	Texture11::CreateWhiteTex(_device);
	whiteTex = &Texture11::GetWhiteTex();

	Texture11::CreateNormalTex(_device);
	normalTex = &Texture11::GetNormalTex();

	baseData.CreateBuffer(_device, 0);

	charaData.CreateBuffer(_device, 1);

	polygonData.CreateBuffer(_device, 0);

	boneData.CreateBuffer(_device, 11);

	bdObject.projMat.CreateProjectionMat(
		ChMath::ToRadian(60.0f)
		, _width
		, _height
		, 1.0f
		, 1000.0f);

	bdObject.viewMat.CreateViewMat(
		ChVec3(0.0f, 0.0f, -1.0f)
		, ChVec3(0.0f, 0.0f, 1.0f)
		, ChVec3(0.0f, 1.0f, 0.0f));

	bdObject.windSize = ChVec4(_width, _height, 0.0f, 0.0f);

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

void ShaderController11::SetDrawDatas()
{

	dc->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (rasteriserUpdate)
	{
		if (ChPtr::NotNullCheck(rasteriser)) 
		{
			rasteriser->Release();
			rasteriser = nullptr;
		}

		//描画方法//
		D3D11_RASTERIZER_DESC RasteriserDesc
		{
			fill,
			cull,
			false,
			0,
			0.0f,
			0.0f,
			false,
			false,
			true,
			false
		};

		device->CreateRasterizerState(&RasteriserDesc, &rasteriser);

		rasteriserUpdate = false;

	}

	dc->RSSetState(rasteriser);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawStart()
{

	if (!*this)return;
	if (drawFlg)return;

	if (!renderTargets.empty())
	{
		tmpView = &renderTargets[0];
		dc->OMSetRenderTargets(renderTargets.size(), tmpView, nullptr);

		rtDrawFlg = true;
	}
	else
	{
		window.SetBackGroundColor(dc, backColor);

		dsBuffer.ClearDepthBuffer(dc);

		out3D.SetBackColor(dc, backColor);
		out2D.SetBackColor(dc, ChVec4(0.0f, 0.0f, 0.0f, 0.0f));

		rtDrawFlg = false;

	}

	view.SetDrawData(dc);

	SetDrawDatas();

	if (bdUpdateFlg)
	{
		baseData.UpdateResouce(dc,&bdObject);
		bdUpdateFlg = false;
	}

	baseData.SetToVertexShader(dc, 1);
	baseData.SetToPixelShader(dc, 1);

	drawFlg = true;


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

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	pdObject.modelMat.Identity();

	polygonData.UpdateResouce(dc, &pdObject);

	polygonData.SetToVertexShader(dc, 1);
	polygonData.SetToPixelShader(dc, 1);

	out3D.SetDrawData(dc, 0);

	outSprite.SetDrawData(dc);

	out2D.SetDrawData(dc, 0);

	outSprite.SetDrawData(dc);

	// バックバッファをプライマリバッファにコピー//
	window.Draw();

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Mesh11& _mesh
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());
	}

	cdObject.modelMat = _mat;

	bvModel.SetShader(dc);

	bpModel.SetShader(dc);

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc, 1);
	charaData.SetToPixelShader(dc, 1);

	//_mesh.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Mesh11& _mesh,
	VertexShader11& _userVS,
	PixelShader11& _userPS,
	const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;
	if (!_userVS.IsInit())return;
	if (!_userPS.IsInit())return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

#if TEST_FLG

	cdObject.modelMat = _mat;

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc, 1);
	charaData.SetToPixelShader(dc, 1);

#endif

	_userVS.SetShader(dc);

	_userPS.SetShader(dc);

	//_mesh.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

//Mesh描画用関数//
void ShaderController11::DrawOutLine(
	Mesh11& _Mesh
	, const ChVec4& _Color
	, const ChMat_11& _mat
	, const float _Size)
{
	if (!*this)return;
	if (_Size < 0.0f)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());
	}

	D3D11_CULL_MODE tmpCull = GetCullMode();
	SetCullMode(D3D11_CULL_MODE::D3D11_CULL_FRONT);

	bvModel.SetShader(dc);

	bpModel.SetShader(dc);

	SetCullMode(tmpCull);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::TextureBase11& _tex
	, PolygonBoard11& _polygon
	, const ChMat_11& _mat)
{
	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());
	}

	cdObject.modelMat = _mat;

	ChD3D11::TextureBase11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = whiteTex;

	pvTex.SetShader(dc);

	bpModel.SetShader(dc);

	cdObject.frameMatrix.Identity();

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc, 1);
	charaData.SetToPixelShader(dc, 1);

	drawTex->SetDrawData(dc, 0);

	_polygon.SetDrawData(dc);

}

void ShaderController11::Draw(
	TextureBase11& _tex,
	PolygonBoard11& _polygon,
	VertexShader11& _userVS,
	PixelShader11& _userPS,
	const ChMat_11& _mat )
{
	if (!*this)return;
	if (!drawFlg)return;
	if (!_userVS.IsInit())return;
	if (!_userPS.IsInit())return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());
	}

#if TEST_FLG

	cdObject.modelMat = _mat;

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc, 1);
	charaData.SetToPixelShader(dc, 1);

#endif

	ChD3D11::TextureBase11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = whiteTex;

	_userPS.SetShader(dc);

	_userVS.SetShader(dc);

	drawTex->SetDrawData(dc, 0);

	_polygon.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::TextureBase11& _tex
	, Sprite11& _sprite
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out2D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, nullptr);

		out3D.SetDrawData(dc, 12);
	}

	pdObject.modelMat = _mat;

	ChD3D11::TextureBase11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = whiteTex;

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	polygonData.UpdateResouce(dc, &pdObject);

	polygonData.SetToVertexShader(dc, 1);
	polygonData.SetToPixelShader(dc, 1);

	drawTex->SetDrawData(dc, 0);

	_sprite.SetDrawData(dc);

}

void ShaderController11::Draw(
	TextureBase11& _tex,
	Sprite11& _sprite,
	VertexShader11& _userVS,
	PixelShader11& _userPS,
	const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;
	if (!_userVS.IsInit())return;
	if (!_userPS.IsInit())return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out2D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, nullptr);

		out3D.SetDrawData(dc, 12);
	}

	ChD3D11::TextureBase11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = whiteTex;

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

#if TEST_FLG

	pdObject.modelMat = _mat;

	polygonData.UpdateResouce(dc, &pdObject);

	polygonData.SetToVertexShader(dc, 1);
	polygonData.SetToPixelShader(dc, 1);

#endif

	drawTex->SetDrawData(dc, 0);

	_sprite.SetDrawData(dc);

}
