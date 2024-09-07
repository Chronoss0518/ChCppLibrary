#ifndef Ch_D3D9_TexCom_h
#define Ch_D3D9_TexCom_h

#include"../ChVertexData9.h"

#include"../../CPP/ChBaseObject/ChBaseComponent.h"

namespace ChTex
{
	class BaseTexture9;
}

typedef class ChTextureComponent9 :public ChCpp::BaseComponent
{
public:

#ifdef CRT

	//�p�X���L�q//
	//�R���|�[�l���g�ɉ摜�f�[�^���쐬����//
	void SetTexture(const std::string& _textureName)
	{
		texture = ChTex::BaseTexture9::TextureType(_textureName);
		texture->CreateTexture(_textureName, ChD3D9::D3D9Device());
	}

#endif

public://Get Functions//

	//�摜�f�[�^���擾//
	ChTex::BaseTexture9* GetTex();

protected://Member Values//

#ifdef CRT
	
	ChPtr::Shared<ChTex::BaseTexture9>texture = nullptr;

#endif

}ChTexCom9;

typedef class ChSpriteTextureComponent9 :public ChTexCom9
{
public:

	void Draw2D()override;

public://Get Functions//

	//�X�v���C�g�z�u�f�[�^//
	ChD3D9::SpriteData& GetSpriteData() { return ver; }

protected:

	ChD3D9::SpriteData ver;

}ChSpTexCom9;

typedef class ChPolygonTextureComponent9 :public ChTexCom9
{
public:

	void Draw3D()override;

public:

	//�|���S���z�u�f�[�^//
	ChD3D9::VertexData& GetPolygonData() { return ver; }

protected:

	ChD3D9::VertexData ver;

}ChPoTexCom9;

#ifdef CRT

ChTex::BaseTexture9* ChTextureComponent9::GetTex() { return texture.get(); }

#endif

#endif