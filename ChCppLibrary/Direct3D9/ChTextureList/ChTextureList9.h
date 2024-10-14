#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

#include<string>

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture専用のconst enumを作って、SetTextureの第二引数に入れる。
	//以降第二引数に入れた数字を使ってTextureを操作する。
	typedef class TextureList9:public ChCp::Initializer
	{
	public://Constructer Destructer//

		~TextureList9()
		{
			Release();
		}

	public://Init And Release//

		//もし、XFileフォルダーなどを作っていない場合は第二引数に""を入れる。//
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv)
		{
			device = _dv;

			SetInitFlg(true);
		}

		void Release();

	public://Set Function//

		//Textureの登録//
		void SetTexture(
			const std::string& _textureName,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

		//Textureの登録//
		void SetTexture(
			const std::wstring& _textureName,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

	protected:

		void SetTextureBase(
			ChPtr::Shared<BaseTexture9> _tex,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0));

	public:

		//合成可色、基本色の設定//
		void SetBlendColor(
			const ChVec4& _color,
			const unsigned short _dataNum);

		//画像の透明化設定//
		void SetBlendAlpha(
			const unsigned char _a,
			const unsigned short _dataNum);

		//決めた色でTextureの作成//
		//登録するための_DataNumはかぶってはならない//
		void SetColorTex(
			const unsigned long& _color,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const unsigned long _type = 0);

	public://Get Functions//

		//外部利用するためのテクスチャを取得する//
		inline ChPtr::Shared<Texture9> GetTex(const unsigned short dataNum)
		{
			if (texList.find(dataNum) == texList.end())return nullptr;

			return texList[dataNum];

		}

	public://Get Functions//

		Texture9* GetTexPtr(const unsigned short dataNum);

	private:

		LPDIRECT3DDEVICE9 device = nullptr;
		
		std::map<unsigned short, ChPtr::Shared<Texture9>>texList;

	}ChTexList9;

}

#endif
//CopyRight Chronoss0518 2018/0
