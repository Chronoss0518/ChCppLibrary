#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChSprite/ChSprite11.h"

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"
#include"../../ChCB/ChCBCircleCulling/ChCBCircleCulling11.h"

#include"ChCircleCullingSpriteShader11.h"

using namespace ChD3D11;
using namespace Shader;


void CircleCullingSprite11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	spriteData.Init(_device, &GetWhiteTexture());
	circleCullingData.Init(_device);

	std::array<Ch3D::Vertex, 4> vertexs;

	vertexBuffer.CreateBuffer(_device, &vertexs[0], vertexs.size());

	std::array<unsigned long, 6> indexs = { 0,1,2,0,2,3 };

	indexBuffer.CreateBuffer(_device, &indexs[0], indexs.size());


	D3D11_RASTERIZER_DESC desc
	{
		D3D11_FILL_MODE::D3D11_FILL_SOLID,
		D3D11_CULL_MODE::D3D11_CULL_NONE,
		true,
		0,
		0.0f,
		0.0f,
		false,
		false,
		true,
		false
	};

	CreateRasteriser(desc);
}

void CircleCullingSprite11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	spriteData.Release();
	circleCullingData.Release();
}

void CircleCullingSprite11::InitVertexShader()
{
#include"../SpriteShader/BaseSpriteVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[3];

	decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


	SampleShaderBase11::CreateVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));

}

void CircleCullingSprite11::InitPixelShader()
{

#include"../SpriteShader/CircleCullingSpritePixel.inc"

	SampleShaderBase11::CreatePixelShader(main, sizeof(main));
}

void CircleCullingSprite11::SetStartDrawDir(const ChVec2& _dir)
{
	if (!IsInit())return;

	circleCullingData.SetDrawStartDir(_dir);
}

void CircleCullingSprite11::SetDirStartPos(const ChVec2& _pos)
{
	if (!IsInit())return;

	circleCullingData.SetDirStartPos(_pos);
}

void CircleCullingSprite11::SetDrawValue(const float& _dir)
{
	if (!IsInit())return;

	circleCullingData.SetDrawValue(_dir);
}


void CircleCullingSprite11::Draw(
	ID3D11DeviceContext* _dc
	, TextureBase11& _tex
	, Sprite11& _sprite
	, const ChMat_11& _mat)
{
	Draw(_dc, _tex, _sprite, ChVec4(1.0f), _mat);
}

void CircleCullingSprite11::Draw(
	ID3D11DeviceContext* _dc
	, TextureBase11& _tex
	, Sprite11& _sprite
	, const ChVec4& _baseColor
	, const ChMat_11& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (!_tex.IsTex())return;

	spriteData.SetSpriteMatrix(_mat);

	spriteData.SetBaseColor(_baseColor);

	spriteData.SetShaderSpriteData(_dc);

	spriteData.SetBaseTexture(&_tex);

	spriteData.SetShaderTexture(_dc);

	if (alphaBlendFlg)
	{
		SampleShaderBase11::SetShaderBlender(_dc);
	}

	circleCullingData.SetDrawData(_dc);

	unsigned int offsets = 0;

	auto&& vertexs = _sprite.GetVertexs();

	vertexBuffer.UpdateResouce(_dc, &vertexs[0]);

	vertexBuffer.SetVertexBuffer(_dc, offsets);

	indexBuffer.SetIndexBuffer(_dc);

	_dc->DrawIndexed(6, 0, 0);

	if (alphaBlendFlg)
	{
		SampleShaderBase11::SetShaderDefaultBlender(_dc);
	}
}
