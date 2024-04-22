#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChSprite/ChSprite11.h"

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"
#include"../../ChCB/ChCBHighlight/ChCBHighlight11.h"

#include"ChBasicHighlightShader11.h"

using namespace ChD3D11;
using namespace Shader;


void BasicHighlightShader11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleSpriteShaderBase11::Init(_device);

	highlightMapData.Init(_device);

	{
		D3D11_BLEND_DESC desc;
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_INV_DEST_COLOR;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_DEST_COLOR;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;


		CreateBlender(desc);
	}

}

void BasicHighlightShader11::Release()
{
	if (!IsInit())return;

	SampleSpriteShaderBase11::Release();

	highlightMapData.Release();
}

void BasicHighlightShader11::InitPixelShader()
{

#include"../SpriteShader/BasicHighlightPixel.inc"

	SampleSpriteShaderBase11::CreatePixelShader(main, sizeof(main));
}


void BasicHighlightShader11::Draw(
	TextureBase11& _tex
	, Sprite11& _sprite
	, const ChMat_11& _mat)
{
	Draw(_tex, _sprite, ChVec4(1.0f), _mat);
}

void BasicHighlightShader11::Draw(
	TextureBase11& _tex
	, Sprite11& _sprite
	, const ChVec4& _baseColor
	, const ChMat_11& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (!_tex.IsTex())return;

	spriteData.SetSpriteMatrix(_mat);

	spriteData.SetBaseColor(_baseColor);

	spriteData.SetShaderSpriteData(GetDC());

	spriteData.SetBaseTexture(&_tex);

	spriteData.SetShaderTexture(GetDC());

	highlightMapData.SetPSSpriteData(GetDC());

	SampleSpriteShaderBase11::SetShaderBlender(GetDC());

	unsigned int offsets = 0;

	auto&& vertexs = _sprite.GetVertexs();

	vertexBuffer.UpdateResouce(GetDC(), &vertexs[0]);

	vertexBuffer.SetVertexBuffer(GetDC(), offsets);

	indexBuffer.SetIndexBuffer(GetDC());

	GetDC()->DrawIndexed(6, 0, 0);

	SampleSpriteShaderBase11::SetShaderDefaultBlender(GetDC());
}
