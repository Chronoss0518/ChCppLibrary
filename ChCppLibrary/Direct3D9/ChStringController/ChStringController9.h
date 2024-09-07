#ifndef Ch_D3D9_StCo_h
#define Ch_D3D9_StCo_h

#include"../ChSprite/ChSprite9.h"

//(���ǒ�)(�g�p�s��)//
//���̏�ŕ�����p�e�N�X�`���𐶐��A�x�[�X�ƂȂ�e�N�X�`����p�ӂ���K�v������//
//����t�H���_�ɒu���ꂽ�ꕶ���Â̉摜�𑀍삷��R���g���[���[�B//
//�n�߂ɂ��̉摜�Q�̒u���ꂽ�f�B���N�g���p�X����͂���B//
//�摜�T�C�Y�͓��ꂷ��B//

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	typedef class StringController9:public ChCp::Initializer
	{
	public://Constructer Dextructer//

#ifdef CRT
		StringController9(
			const LPDIRECT3DDEVICE9 _dv,
			const std::string& _path,
			const std::string& _type,
			const unsigned short _originalWedth,
			const unsigned short _originalHeight)
		{
			size.w = _originalWedth;
			size.h = _originalHeight;
			if (size.w == 0 || size.h == 0)return;
			device = _dv;
			strPath = _path;
			typeName = _type;

			SetInitFlg(true);
	}
#endif

		~StringController9() { SetInitFlg(false); };

	public://SetFunction//

		void SetStringColor(const ChVec4& _color);

		void SetStringAlpha(const unsigned char _a);

	private://Set Functions//

#ifdef CRT
		void SetStrTexture(const std::string& _str)
		{
			strTex.CreateTexture(strPath + _str + strPath, device);
		}
#endif

	public://Draw Functions//

#ifdef CRT
		void DrawSprightString(
			const std::string& _str,
			const ChMat_9& _mat,
			Sprite9 &_sp)
		{
			if (device == nullptr)return;
			if (_str.length() <= 0)return;

			std::string tmpStr;
			tmpStr = _str + strPath;

			for (unsigned short i = 0; i < _str.length(); i++)
			{
				//char tmpChar[3];
				SetStrTexture(_str);

				_sp.DrawSprite(
					strTex,
					_mat,
					ChVec3_9(0.0f, 0.0f, 0.0f));
			}

		}

#endif

	private://Mmember Values//
		
		ChMath::Vector2Base<unsigned short>size;

		LPDIRECT3DDEVICE9 device = nullptr;

		Texture9 strTex;

#ifdef CRT

		std::string strPath;
		std::string typeName;

#endif

	}StrCon;
}


#endif