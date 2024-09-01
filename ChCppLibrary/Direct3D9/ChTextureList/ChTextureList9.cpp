
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChTextureList9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChTextureList9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetBlendColor(
	const ChVec4& _color,
	const unsigned short _dataNum)
{
	auto&& tex = GetTexBase(_dataNum);
	if (tex == nullptr)return;

	tex->SetBaseColor(_color);
}

void TextureList9::SetBlendAlpha(const unsigned char _a, const unsigned short _dataNum) {

	auto&& tex = GetTexBase(_dataNum);
	if (tex == nullptr)return;

	ChVec4 tmpCol = tex->GetBaseColor();
	tmpCol.a = _a;
	tex->SetBaseColor(tmpCol);
}

