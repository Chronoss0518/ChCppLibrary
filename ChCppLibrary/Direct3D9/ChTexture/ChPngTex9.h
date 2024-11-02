
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
			//チャンクデータのサイズ//
			unsigned long Length = 0;
			//チャンクタイプ//
			const unsigned char CType[4] = { 'I','H','D','R' };
			//画像の幅//
			unsigned long CWData = 0;
			//画像の高さ//
			unsigned long CHData = 0;
			//ビット深度//
			unsigned char BD = 0;
			//カラータイプ//
			unsigned char ColType = 0;
			//圧縮手法//
			unsigned char Zips = 0;
			//フィルター//
			unsigned char Fillter = 0;
			//インターレース手法//
			unsigned char Interlase = 0;
			//CTypeとCDataをもとに計算される//
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

		void SetChank(const std::vector<unsigned char>& _str);
	};
}

#endif