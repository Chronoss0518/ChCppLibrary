
#ifndef Ch_D3D9_TJpeg_h
#define Ch_D3D9_TJpeg_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class JpegTex9 :public BaseTexture9
	{
	protected:
		
#ifdef CRT
		void OpenFile(const char* _fileName)override;
#endif

		struct S_SOF
		{
			//�}�[�J�[���ʎq//
			const unsigned char MType[3] = { 0xff,0xc0,'\0' };
			//�Z�O�����g�̒���//	
			unsigned short S_Len;
			//�T���v���̐��x//
			unsigned char Sample;
			//�摜�̍���//
			unsigned short TexHeight;
			//�摜�̕�//
			unsigned short TexWidht;
			//�\���v�f��//
			unsigned char TypeCnt;

			S_SOF()
			{
				S_Len = 0;
				Sample = 0;
				TexHeight = 0;
				TexWidht = 0;
				TypeCnt = 0;
			}

		};

#ifdef CRT
		S_SOF SetSegment(const std::vector<char>& _str);
#endif
	};
}


#ifdef CRT

void ChTex::JpegTex9::OpenFile(const char* _fileName)
{
	ChCpp::CharFile file;
	file.FileOpen(_fileName, std::ios::binary | std::ios::in | std::ios::out);

	std::string tmpStr;

	std::vector<char> tmp;

	tmp.resize(file.GetLength());
	file.FileReadBinary(tmp);

	file.FileClose();

	auto&& data = SetSegment(tmp);

	if (data.TexWidht <= 0 || data.TexHeight <= 0)return;

	ChStr::Bytes<unsigned long> wData;
	wData.val = data.TexWidht;


	ChStr::Bytes<unsigned long> hData;
	hData.val = data.TexHeight;

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

ChTex::JpegTex9::S_SOF ChTex::JpegTex9::SetSegment(const std::vector<char>& _str)
{
	S_SOF seg;

	if (_str.size() <= sizeof(S_SOF))return seg;

	if (_str[0] != 0xff)return seg;
	if (_str[1] != 0xc0)return seg;
	if (_str[2] != 0)return seg;

	return ChStr::StrBinaryToNum<S_SOF, char>(&_str[0], _str.size(), 0);
}
#endif

#include"ChTextureShared9.h"

#endif
