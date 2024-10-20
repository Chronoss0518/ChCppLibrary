#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

#include<string>

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture��p��const enum������āASetTexture�̑������ɓ����B
	//�ȍ~�������ɓ��ꂽ�������g����Texture�𑀍삷��B
	typedef class TextureList9:public ChCp::Initializer
	{
	public://Constructer Destructer//

		~TextureList9()
		{
			Release();
		}

	public://Init And Release//

		//�����AXFile�t�H���_�[�Ȃǂ�����Ă��Ȃ��ꍇ�͑�������""������B//
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv)
		{
			device = _dv;

			SetInitFlg(true);
		}

		void Release();

	public://Set Function//

		//Texture�̓o�^//
		void SetTexture(
			const std::string& _textureName,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

		//Texture�̓o�^//
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

		//�����F�A��{�F�̐ݒ�//
		void SetBlendColor(
			const ChVec4& _color,
			const unsigned short _dataNum);

		//�摜�̓������ݒ�//
		void SetBlendAlpha(
			const unsigned char _a,
			const unsigned short _dataNum);

		//���߂��F��Texture�̍쐬//
		//�o�^���邽�߂�_DataNum�͂��Ԃ��Ă͂Ȃ�Ȃ�//
		void SetColorTex(
			const unsigned long& _color,
			const unsigned short _dataNum,
			const unsigned int _gameReSizeWidth,
			const unsigned int _gameReSizeHeight,
			const unsigned long _type = 0);

	public://Get Functions//

		//�O�����p���邽�߂̃e�N�X�`�����擾����//
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
