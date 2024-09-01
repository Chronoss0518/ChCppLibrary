#ifndef Ch_D3D9_TexMa_h
#define Ch_D3D9_TexMa_h

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

#ifdef CRT
		//テクスチャを登録する//
		//第二引数に登録するテクスチャをわかりやすくするための名前を入れる//
		void SetTexture(
			const std::string& _textureName,
			const std::string& _dataName,
			const std::string& _usePathName,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR& _colorKey = D3DCOLOR_ARGB(255,255,255,255)
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
#endif

	public://Get Functions//

#ifdef CRT
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
#endif

	public://Other Functions//

#ifdef CRT
		//対象のテクスチャを解放する//
		void ClearData(const std::string _DataName);
#endif

	private:
		LPDIRECT3DDEVICE9 device = nullptr;
#ifdef CRT
		std::map<std::string, ChPtr::Shared<BaseTexture9>>texList;

		std::map<std::string, ChPtr::Shared<std::string>> pathList;
#endif

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

#ifdef CRT

void ChTex::TextureManager9::Release()
{
	if (!texList.empty()) {
		texList.clear();
	}
	if (!pathList.empty())
	{
		pathList.clear();
	}

	SetInitFlg(false);
}

void ChTex::TextureManager9::SetTexture(
	const std::string& _textureName,
	const std::string& _dataName,
	const std::string& _usePathName,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const D3DCOLOR& _colorKey)
{
	if (texList.find(_dataName) != texList.end())return;
	if (_textureName.length() <= 0)return;

	std::string tmpPath = "./";


	if (pathList.find(_usePathName) != pathList.end())
	{
		tmpPath = *pathList[_usePathName];
		tmpPath += "/";
	}

	std::string tmpString = _textureName;

	tmpString = tmpPath + tmpString;

	auto tmpTex = ChTex::Texture9::TextureType(tmpString);

	tmpTex->CreateTexture(tmpString, device, _colorKey);

	if (ChPtr::NullCheck(tmpTex->GetTex()))
	{
		tmpTex = nullptr;
		return;
	}

	if (ChPtr::NullCheck(tmpTex->GetTex())) return;

	tmpTex->SetSclXSize(0.0f);
	tmpTex->SetSclYSize(0.0f);
	if (_gameReSizeWidth != NULL && _gameReSizeHeight != NULL) {
		float tmpX, tmpY;
		tmpX = (float)_gameReSizeWidth / (float)tmpTex->GetOriginalWidth();
		tmpY = (float)_gameReSizeHeight / (float)tmpTex->GetOriginalHeight();
		if (_gameReSizeWidth == tmpTex->GetOriginalWidth())tmpX = 0.0f;
		if (_gameReSizeHeight == tmpTex->GetOriginalHeight())tmpY = 0.0f;
		tmpTex->SetSclXSize(tmpX);
		tmpTex->SetSclYSize(tmpY);
	}

	texList[_dataName] = tmpTex;
}

void ChTex::TextureManager9::SetColorTex(
	const unsigned long& _color,
	const std::string& _dataName,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const unsigned long _type)
{
	if (texList.find(_dataName) != texList.end())return;

	auto tmpTex = ChPtr::Make_S<Texture9>();

	tmpTex->CreateColTexture(device, _color);

	tmpTex->SetSclXSize(1.0f);
	tmpTex->SetSclYSize(1.0f);

	if (_gameReSizeWidth != 0 && _gameReSizeHeight != 0)
	{
		tmpTex->SetSclXSize((float)_gameReSizeWidth);
		tmpTex->SetSclYSize((float)_gameReSizeHeight);
	}

	texList[_dataName] = tmpTex;

	return;
}

void ChTex::TextureManager9::SetBlendColor(
	const ChVec4& _color,
	const std::string _dataName)
{

	if (texList.find(_dataName) == texList.end())return;
	texList[_dataName]->SetBaseColor(_color);
}

void ChTex::TextureManager9::SetBlendAlpha(
	const unsigned char _a,
	std::string _dataName)
{
	if (texList.find(_dataName) == texList.end())return;
	ChVec4 tmp = texList[_dataName]->GetBaseColor();
	tmp.a = _a;
	texList[_dataName]->SetBaseColor(tmp);
}

void ChTex::TextureManager9::SetDirectoryPath(
	std::string _directoryPath,
	const std::string _useDirectoryPashName)
{
	if (pathList.find(_useDirectoryPashName) != pathList.end())return;
	if (_directoryPath.length() <= 0)return;

	pathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_useDirectoryPashName, ChPtr::Make_S<std::string>()));
	*pathList[_useDirectoryPashName] = _directoryPath;
}

void ChTex::TextureManager9::ClearData(const std::string _dataName)
{
	if (texList.empty())return;

	if (texList.find(_dataName) == texList.end()) return;

	texList.erase(_dataName);

	return;

}

#endif

#endif