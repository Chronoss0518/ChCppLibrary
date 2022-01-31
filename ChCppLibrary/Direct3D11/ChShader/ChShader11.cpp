
#include<windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"../ChMesh/ChMesh11.h"
#include"../ChPolygonBoard/ChPolygonBoard11.h"
#include"../ChSprite/ChSprite11.h"
#include"ChShader11.h"

using namespace ChD3D11;

//ChStd::FPOINT ShaderController11::windSize = ChStd::FPOINT(1280.0f, 720.0f);

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderController11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderController11::InitShader()
{

	{
#include"MBVShader.inc"

		//D3D11_INPUT_ELEMENT_DESC Decl[14];
		D3D11_INPUT_ELEMENT_DESC Decl[29];

		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[4] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[5] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[6] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[7] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[8] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[9] = { "BLENDWEIGHT",  4, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[10] = { "BLENDWEIGHT",  5, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[11] = { "BLENDWEIGHT",  6, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[12] = { "BLENDWEIGHT",  7, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[13] = { "BLENDWEIGHT",  8, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[14] = { "BLENDWEIGHT",  9, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[15] = { "BLENDWEIGHT",  10, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[16] = { "BLENDWEIGHT",  11, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[17] = { "BLENDWEIGHT",  12, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[18] = { "BLENDWEIGHT",  13, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[19] = { "BLENDWEIGHT",  14, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[20] = { "BLENDWEIGHT",  15, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[21] = { "BLENDWEIGHT",  16, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[22] = { "BLENDWEIGHT",  17, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[23] = { "BLENDWEIGHT",  18, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[24] = { "BLENDWEIGHT",  19, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[25] = { "BLENDWEIGHT",  20, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[26] = { "BLENDWEIGHT",  21, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[27] = { "BLENDWEIGHT",  22, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[28] = { "BLENDWEIGHT",  23, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		//Decl[13] = { "BLENDINDEX",  4, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

		bvModel.Init(device,Decl, 29, main, sizeof(main));

		//VSInputElements Elements;

		//Elements.Add(Semantics::Position, DXGI_FORMAT_R32G32B32_FLOAT);
		//Elements.Add(Semantics::Normal, DXGI_FORMAT_R32G32B32_FLOAT);
		//Elements.Add(Semantics::Normal, DXGI_FORMAT_R32G32B32_FLOAT);
		//Elements.Add(Semantics::Color, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::TexCoord, DXGI_FORMAT_R32G32_FLOAT);
		//Elements.Add(Semantics::TexCoord, DXGI_FORMAT_R32_FLOAT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32_UINT);

		//bvModel.CreateVertexShader(Elements.GetDesc(), Elements.GetCount(), main, sizeof(main));

	}

	{
#include"PTVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl;


		Decl = { "BLENDINDICES",  0, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		
		pvTex.Init(device,&Decl, 1, main, sizeof(main));

	}

	{
#include"MBPShader.inc"


		bpModel.Init(device,main, sizeof(main));

	}


	{
#include"STVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl;

		Decl = { "BLENDINDICES",  0, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

		spvTex.Init(device,&Decl, 1, main, sizeof(main));

		//device->CreateInputLayout(SpDecl, ARRAYSIZE(SpDecl), &main, sizeof(main), &SpILayout);

	}

	{
#include"TPShader.inc"
		
		bpTex.Init(device,&main, sizeof(main));

		//device->CreatePixelShader(&main, sizeof(main), nullptr, &bpTex);
	}

}

///////////////////////////////////////////////////////////////////////////////////

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
	
	InitShader();

	baseData.CreateBuffer(_device, ChStd::EnumCast(ModelConstantRegisterNo::DrawData));
	charaData.CreateBuffer(_device, ChStd::EnumCast(ModelConstantRegisterNo::CharaData));
	polygonData.CreateBuffer(_device, ChStd::EnumCast(TextureConstantRegisterNo::PolygonData));

	polygonBoardObject.Init(_device);

	whiteTex.CreateColorTexture(device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

	normalTex.CreateColorTexture(device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

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


	//描画方法//
	D3D11_RASTERIZER_DESC rasteriserDesc
	{
		fill
		,cull
		,true
		,0
		,0.0f
		,0.0f
		,false
		,false
		,false
		,false
	};

	device->CreateRasterizerState(&rasteriserDesc, &rasteriser);

	dc->RSSetState(rasteriser);

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
	view.SetWindPos(ChVec2(0.0f, 0.0f));
	view.SetWindSize(ChVec2(_width, _height));

	lightDatas.Init(_device);



	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Release()
{
	whiteTex.Release();
	normalTex.Release();

	lightDatas.Release();
	window.Release();

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetRenderTarget(Texture11& _tex)
{
	if (!*this)return;
	if (drawFlg)return;


	renderTargets.push_back(const_cast<ID3D11RenderTargetView*>(_tex.GetRTView()));

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetDrawDatas()
{

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (rasteriserUpdate)
	{
		rasteriser->Release();

		//描画方法//
		D3D11_RASTERIZER_DESC RasteriserDesc
		{
			fill
			,cull
			,true
			,0
			,0.0f
			,0.0f
			,false
			,false
			,false
			,false
		};


		device->CreateRasterizerState(&RasteriserDesc, &rasteriser);

		dc->RSSetState(rasteriser);

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
		dc->ClearRenderTargetView(renderTargets[0], backColor.val.GetVal());
		rtDrawFlg = true;
	}
	else
	{
		//window.SetDrawData(dc, dsBuffer.GetDSView());

		window.ClearView(dc, backColor);

		dsBuffer.ClearDepthBuffer(dc);

		ChVec4 tmpCol = ChVec4(0.0f, 0.0f, 0.0f,0.0f);

		dc->ClearRenderTargetView(out3D.GetRTView(), backColor.val.GetVal());
		dc->ClearRenderTargetView(out2D.GetRTView(), tmpCol.val.GetVal());

		out3D.SetDrawData(dc, 12);

		rtDrawFlg = false;
	}

	view.SetDrawData(dc);

	lightDatas.SetPSDrawData(dc);

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	SetDrawDatas();

	//bdObject.projMat = bdObject.projMat.Transpose();
	//bdObject.viewMat = bdObject.viewMat.Transpose();

	if (bdUpdateFlg)
	{

		baseData.UpdateResouce(dc, &bdObject);

		bdUpdateFlg = false;
	}

	baseData.SetToVertexShader(dc);

	baseData.SetToPixelShader(dc);

	drawFlg = true;


}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawEnd()
{

	if (!*this)return;
	if (!drawFlg)return;

	if (ChPtr::NullCheck(device))return;

	drawFlg = false;

	if (rtDrawFlg)return;
	

	window.SetDrawData(dc, nullptr);

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	polygonData.UpdateResouce(dc, &pdObject);

	polygonData.SetToVertexShader(dc);
	polygonData.SetToPixelShader(dc);

	out3D.SetDrawData(dc, 0);

	outSprite.SetDrawData(dc);

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	polygonData.UpdateResouce(dc, &pdObject);

	polygonData.SetToVertexShader(dc);
	polygonData.SetToPixelShader(dc);

	out2D.SetDrawData(dc, 0);

	outSprite.SetDrawData(dc);

	// バックバッファをプライマリバッファにコピー
	window.Draw();

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Mesh11& _Mesh
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;
	if (!_Mesh.IsMesh())return;


	cdObject.modelMat = _mat.Transpose();

	cdObject.modelMat = _mat;

	bvModel.SetShader(dc);

	bpModel.SetShader(dc);

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc);
	charaData.SetToPixelShader(dc);

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	_Mesh.SetDrawData(dc);

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
	if (_Mesh.IsMesh())return;


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
	ChD3D11::Texture11& _tex
	, PolygonBoard11& _porygon
	, const ChMat_11& _mat)
{
	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	//cdObject.modelMat = _mat.Transpose();
	cdObject.modelMat = _mat;

	ChD3D11::Texture11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = &whiteTex;

	pvTex.SetShader(dc);

	bpModel.SetShader(dc);

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc);
	charaData.SetToPixelShader(dc);

	drawTex->SetDrawData(dc, 0);

	_porygon.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Texture11& _tex
	, const std::vector<ChPtr::Shared<PolygonBoardVertex>>& _vertex
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	polygonBoardObject.SetVertexs(_vertex);

	//cdObject.modelMat = _mat.Transpose();
	cdObject.modelMat = _mat;

	ChD3D11::Texture11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = &whiteTex;

	pvTex.SetShader(dc);

	bpModel.SetShader(dc);

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc);
	charaData.SetToPixelShader(dc);

	drawTex->SetDrawData(dc, 0);

	polygonBoardObject.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::Texture11& _tex
	, Sprite11& _sprite
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;


	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	//if (!rtDrawFlg)
	//{
	//	ID3D11RenderTargetView* tmp = out2D.GetRTView();
	//	dc->OMSetRenderTargets(1, &tmp, nullptr);

	//	out3D.SetDrawData(dc, 12);
	//}

	//pdObject.modelMat = _mat.Transpose();
	pdObject.modelMat = _mat;

	ChD3D11::Texture11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = &whiteTex;

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	charaData.UpdateResouce(dc, &cdObject);

	charaData.SetToVertexShader(dc);
	charaData.SetToPixelShader(dc);

	drawTex->SetDrawData(dc, 0);

	_sprite.SetDrawData(dc);

}
