#ifndef Ch_D3D9_TexMa_h
#define Ch_D3D9_TexMa_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture��p��const enum������āASetTexture�̑������ɓ����B
	//�ȍ~�������ɓ��ꂽ�������g����Texture�𑀍삷��B
	class TextureManager9:public ChCp::Initializer
	{
	public://Init And Release//

		void Init(LPDIRECT3DDEVICE9 _dv);

		void Release();

	public://Set Functions//

#ifdef CRT
		//�e�N�X�`����o�^����//
		//�������ɓo�^����e�N�X�`�����킩��₷�����邽�߂̖��O������//
		void SetTexture(
			const std::string& _textureName,
			const std::string& _dataName,
			const std::string& _usePathName,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR& _colorKey = D3DCOLOR_ARGB(255,255,255,255)
		);

		//��{�F�̐ݒ�//
		void SetBlendColor(
			const ChVec4& _color,
			const std::string _dataName);

		//�摜�̓������ݒ�//
		void SetBlendAlpha(
			const unsigned char _a,
			std::string _dataName);

		//���߂��F��Texture�̍쐬//
		void SetColorTex(
			const unsigned long& _color,
			const std::string& _dataName,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const unsigned long _type = 0);

		//���p����e�N�X�`���̓����Ă���f�B���N�g����ݒ肷��//
		//SetTexture���ĂԑO�ɂ��̊֐����Ă�//
		void SetDirectoryPath(
			std::string _directoryPath,
			const std::string _useDirectoryPashName);
#endif

	public://Get Functions//

#ifdef CRT
		//�o�^���Ă���e�N�X�`�����擾����//
		inline ChPtr::Shared<Texture9> GetTexture(const std::string _dataName)
		{
			if (texList.empty())return nullptr;
			if (texList.find(_dataName) == texList.end())return nullptr;
			return texList[_dataName];
		}

		//�o�^���Ă���f�B���N�g���p�X�̐����擾//
		inline size_t GetPathCnt() { return pathList.size(); }

		//�o�^���Ă���e�N�X�`���̐����擾//
		inline size_t GetTexCnt() { return texList.size(); }
#endif

	public://Other Functions//

#ifdef CRT
		//�Ώۂ̃e�N�X�`�����������//
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