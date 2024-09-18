
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChTexManager9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChTextureManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void TextureManager9::Init(LPDIRECT3DDEVICE9 _dv)
{
	device = _dv;

	SetInitFlg(true);
}

TextureManager9::~TextureManager9()
{
	Release();
}
