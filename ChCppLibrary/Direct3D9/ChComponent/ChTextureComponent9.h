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

	//パスも記述//
	//コンポーネントに画像データを作成する//
	void SetTexture(const std::string& _textureName)
	{
		texture = ChTex::BaseTexture9::TextureType(_textureName);
		texture->CreateTexture(_textureName, ChD3D9::D3D9Device());
	}

	//パスも記述//
	//コンポーネントに画像データを作成する//
	void SetTexture(const std::wstring& _textureName)
	{
		texture = ChTex::BaseTexture9::TextureType(_textureName);
		texture->CreateTexture(_textureName, ChD3D9::D3D9Device());
	}

public://Get Functions//

	//画像データを取得//
	inline ChTex::BaseTexture9* GetTex() { return texture.get(); }

protected://Member Values//

	ChPtr::Shared<ChTex::BaseTexture9>texture = nullptr;

}ChTexCom9;

typedef class ChSpriteTextureComponent9 :public ChTexCom9
{
public:

	void Draw2D()override;

public://Get Functions//

	//スプライト配置データ//
	ChD3D9::SpriteData& GetSpriteData() { return ver; }

protected:

	ChD3D9::SpriteData ver;

}ChSpTexCom9;

typedef class ChPolygonTextureComponent9 :public ChTexCom9
{
public:

	void Draw3D()override;

public:

	//板ポリゴン配置データ//
	ChD3D9::VertexData& GetPolygonData() { return ver; }

protected:

	ChD3D9::VertexData ver;

}ChPoTexCom9;

#endif