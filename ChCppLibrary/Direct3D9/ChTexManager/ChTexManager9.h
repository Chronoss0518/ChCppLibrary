#ifndef Ch_D3D9_TexMa_h
#define Ch_D3D9_TexMa_h

#include<string>
#include<vector>
#include<map>

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture専用のconst enumを作って、SetTextureの第二引数に入れる。
	//以降第二引数に入れた数字を使ってTextureを操作する。
	class TextureManager9:public ChCp::Initializer
	{
	public://Init And Release//

		void Init(LPDIRECT3DDEVICE9 _dv);

		void Release();

	public://Set Functions//

		//テクスチャを登録する//
		//第二引数に登録するテクスチャをわかりやすくするための名前を入れる//
		void SetTexture(
			const std::string& _textureName,
			const std::string& _dataName,
			const std::string& _usePathName,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR& _colorKey = D3DCOLOR_ARGB(255, 255, 255, 255)
		);

		//基本色の設定//
		void SetBlendColor(
			const ChVec4& _color,
			const std::string _dataName);

		//画像の透明化設定//
		void SetBlendAlpha(
			const unsigned char _a,
			std::string _dataName);

		//決めた色でTextureの作成//
		void SetColorTex(
			const unsigned long& _color,
			const std::string& _dataName,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const unsigned long _type = 0);

		//利用するテクスチャの入っているディレクトリを設定する//
		//SetTextureを呼ぶ前にこの関数を呼ぶ//
		void SetDirectoryPath(
			std::string _directoryPath,
			const std::string _useDirectoryPashName);

	public://Get Functions//

		//登録してあるテクスチャを取得する//
		inline ChPtr::Shared<Texture9> GetTexture(const std::string _dataName)
		{
			if (texList.empty())return nullptr;
			if (texList.find(_dataName) == texList.end())return nullptr;
			return texList[_dataName];
		}

		//登録してあるディレクトリパスの数を取得//
		inline size_t GetPathCnt() { return pathList.size(); }

		//登録してあるテクスチャの数を取得//
		inline size_t GetTexCnt() { return texList.size(); }

	public://Other Functions//

		//対象のテクスチャを解放する//
		void ClearData(const std::string _DataName);

	private:
		LPDIRECT3DDEVICE9 device = nullptr;

		std::map<std::string, ChPtr::Shared<BaseTexture9>>texList;

		std::map<std::string, ChPtr::Shared<std::string>> pathList;

	private://Constructer Destructer//

		TextureManager9() {}

		~TextureManager9();

	public:

		static TextureManager9& GetInstance()
		{
			static TextureManager9 ins;
			return ins;
		}

	};

	inline TextureManager9& TexManager9() { return TextureManager9::GetInstance(); }
}

#endif