#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChSprite/ChSprite11.h"

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"

#include"ChBaseDrawSprite11.h"

using namespace ChD3D11;
using namespace Shader;


void BaseDrawSprite::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	SetInitFlg(true);
}

void BaseDrawSprite::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	SetInitFlg(false);
}

void BaseDrawSprite::SetSpriteMatrix(const ChLMat& _mat)
{
	spriteData.SetSpriteMatrix(_mat);
}

void BaseDrawSprite::Draw(
	ID3D11DeviceContext* _dc
	, TextureBase11& _tex
	, Sprite11& _sprite
	, const ChMat_11& _mat)
{
	if (!_tex.IsTex())return;

	SetShaderRasteriser(_dc);

	Update();

	spriteData.SetSpriteMatrix(_mat);

	spriteData.SetShaderSpriteData(_dc);

	_tex.SetDrawData(_dc,);
}

void BaseDrawSprite::Update()
{
	if (!updateFlg)return;

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

	updateFlg = false;
}
