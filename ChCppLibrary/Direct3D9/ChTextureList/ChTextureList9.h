#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

#ifdef CRT

#include<string>

#endif

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
#ifdef CRT
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv,
			const std::string _fileInDirectoryPath)
		{
			device = _dv;

			directoryPath = _fileInDirectoryPath;

			SetInitFlg(true);
		}

#endif
		void Release();

	public://Set Function//

#ifdef CRT
		//Textureの登録//
		void SetTexture(
			const std::string& _textureName,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);
#endif

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

#ifdef CRT
		//外部利用するためのテクスチャを取得する//
		inline ChPtr::Shared<Texture9> GetTex(const unsigned short dataNum)
		{
			if (texList.find(dataNum) == texList.end())return nullptr;

			return texList[dataNum];

		}
#endif

	public://Get Functions//

		Texture9* GetTexPtr(const unsigned short dataNum);

	private:

		LPDIRECT3DDEVICE9 device = nullptr;
#ifdef CRT
		std::string directoryPath;

		std::map<unsigned short, ChPtr::Shared<Texture9>>texList;
#endif

	}ChTexList9;

}

#ifdef CRT

void ChTex::TextureList9::Release()
{
	if (texList.empty())return;
	texList.clear();

	SetInitFlg(false);
}

ChTex::Texture9* ChTex::TextureList9::GetTexPtr(const unsigned short dataNum)
{
	auto&& tex = texList.find(dataNum);
	if (tex == texList.end())return nullptr;

	return tex->second.get();
}

void ChTex::TextureList9::SetTexture(
	const std::string& _textureName,
	const unsigned short _dataNum,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const D3DCOLOR ColorKey)
{
	if (texList.find(_dataNum) != texList.end())return;

	if (_textureName.length() <= 0)return;

	std::string tmpPath = "./";

	if (directoryPath.length() > 0)
	{
		tmpPath = directoryPath;
		tmpPath += "/";
	}

	std::string tmpString = _textureName;

	tmpString = tmpPath + tmpString;

	auto tmpTex = ChTex::Texture9::TextureType(tmpString);

	tmpTex->CreateTexture(tmpString, device, ColorKey);

	if (ChPtr::NullCheck(tmpTex->GetTex()))
	{
		//ChSystem::ErrerMessage("画像が読み込まれませんでした", "警告");

		tmpTex = nullptr;
		return;
	}

	tmpTex->SetSclXSize(1.0f);
	tmpTex->SetSclYSize(1.0f);

	{
		float tmpX, tmpY;
		tmpX = _gameReSizeWidth > 1.0f ? (float)_gameReSizeWidth / (float)tmpTex->GetOriginalWidth() : 1.0f;
		tmpY = _gameReSizeHeight > 1.0f ? (float)_gameReSizeHeight / (float)tmpTex->GetOriginalHeight() : 1.0f;

		tmpTex->SetSclXSize(tmpX);
		tmpTex->SetSclYSize(tmpY);
	}

	texList[_dataNum] = tmpTex;

}

void ChTex::TextureList9::SetColorTex(
	const unsigned long& _color,
	const unsigned short _dataNum,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const unsigned long _type)
{

	if (texList.find(_dataNum) != texList.end())return;

	auto tmpTex = ChPtr::Make_S<Texture9>();

	tmpTex->CreateColTexture(device, _color);

	tmpTex->SetSclXSize(1.0f);
	tmpTex->SetSclYSize(1.0f);

	if (_gameReSizeWidth > 0 && _gameReSizeHeight > 0)
	{
		tmpTex->SetSclXSize((float)_gameReSizeWidth);
		tmpTex->SetSclYSize((float)_gameReSizeHeight);
	}

	texList[_dataNum] = tmpTex;

	return;
}

void BaseMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		auto tmpPos = ChPtr::Make_S<ChVec3_9>();

		*tmpPos = (tmpVer + ver)->pos;

		offsetVertexList.push_back(tmpPos);
	}


	mesh->UnlockVertexBuffer();
	return;
}

#endif

#endif
//CopyRight Chronoss0518 2018/0
