
#ifndef Ch_D3D9_TPng_h
#define Ch_D3D9_TPng_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class PngTex9 :public BaseTexture9
	{
	protected:

		void OpenFile(const char* _fileName)override;

		void OpenFile(const wchar_t* _fileName)override;

		struct CIHDR
		{
			//�`�����N�f�[�^�̃T�C�Y//
			unsigned long Length = 0;
			//�`�����N�^�C�v//
			const unsigned char CType[4] = { 'I','H','D','R' };
			//�摜�̕�//
			unsigned long CWData = 0;
			//�摜�̍���//
			unsigned long CHData = 0;
			//�r�b�g�[�x//
			unsigned char BD = 0;
			//�J���[�^�C�v//
			unsigned char ColType = 0;
			//���k��@//
			unsigned char Zips = 0;
			//�t�B���^�[//
			unsigned char Fillter = 0;
			//�C���^�[���[�X��@//
			unsigned char Interlase = 0;
			//CType��CData�����ƂɌv�Z�����//
			unsigned long CRC = 0;

			CIHDR()
			{
				Length = 0;
				CWData = 0;
				CHData = 0;
				BD = 0;
				ColType = 0;
				Zips = 0;
				Fillter = 0;
				Interlase = 0;
				CRC = 0;
			}
		};

		void SetChank(const std::vector<char>& _str);
	};
}

#endif