
#ifndef Ch_D3D9_TPng_h
#define Ch_D3D9_TPng_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class PngTex9 :public BaseTexture9
	{
	protected:

		void OpenFile(const char* _fileName)override;

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

#ifdef CRT
		CIHDR SetChank(const std::vector<char>& _str);
#endif

	};
}

#ifdef CRT

void ChTex::PngTex9::OpenFile(const char* _fileName)
{
	ChCpp::CharFile file;

	file.FileOpen(_fileName, std::ios::binary | std::ios::in | std::ios::out);

	std::vector<char> tmp;

	file.FileReadBinary(tmp);

	file.FileClose();

	if (static_cast<unsigned char>(tmp[0]) != 0x89)return;
	if (static_cast<unsigned char>(tmp[1]) != 0x50)return;
	if (static_cast<unsigned char>(tmp[2]) != 0x4E)return;
	if (static_cast<unsigned char>(tmp[3]) != 0x47)return;
	if (static_cast<unsigned char>(tmp[4]) != 0x0D)return;
	if (static_cast<unsigned char>(tmp[5]) != 0x0A)return;
	if (static_cast<unsigned char>(tmp[6]) != 0x1A)return;
	if (static_cast<unsigned char>(tmp[7]) != 0x0A)return;

	auto chank = SetChank(tmp);

	if (chank.Length <= 0)return;

	ChStr::Bytes<unsigned long> wData;
	wData.val = chank.CWData;


	ChStr::Bytes<unsigned long> hData;
	hData.val = chank.CHData;

	for (unsigned char i = 0; i < 2; i++)
	{
		wData.byte[i] += wData.byte[4 - i - 1];
		wData.byte[4 - i - 1] = wData.byte[i] - wData.byte[4 - i - 1];
		wData.byte[i] = wData.byte[i] - wData.byte[4 - i - 1];

		hData.byte[i] += hData.byte[4 - i - 1];
		hData.byte[4 - i - 1] = hData.byte[i] - hData.byte[4 - i - 1];
		hData.byte[i] = hData.byte[i] - hData.byte[4 - i - 1];
	}

	original.w = wData.val;
	original.h = hData.val;
}

inline ChTex::PngTex9::CIHDR ChTex::PngTex9::SetChank(const std::vector<char>& _str)
{
	CIHDR chank;
	if (_str.size() <= sizeof(CIHDR))return chank;

	if (static_cast<unsigned char>(_str[0 + sizeof(chank.Length) + 8]) != 'I')return chank;
	if (static_cast<unsigned char>(_str[1 + sizeof(chank.Length) + 8]) != 'H')return chank;
	if (static_cast<unsigned char>(_str[2 + sizeof(chank.Length) + 8]) != 'D')return chank;
	if (static_cast<unsigned char>(_str[3 + sizeof(chank.Length) + 8]) != 'R')return chank;

	return ChStr::StrBinaryToNum<CIHDR, char>(&_str[0], _str.size(), 8);
}

#endif

#include"ChTextureShared9.h"

#endif