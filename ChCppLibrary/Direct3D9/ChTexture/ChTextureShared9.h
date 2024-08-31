
#ifdef Ch_D3D9_BTex_h
#ifdef Ch_D3D9_TPng_h
#ifdef Ch_D3D9_TJpeg_h
#ifdef Ch_D3D9_TBmp_h

#ifndef Ch_D3D9_Texture_Shared_h
#define Ch_D3D9_Texture_Shared_h



#ifdef CRT

ChPtr::Shared<ChTex::BaseTexture9> ChTex::BaseTexture9::TextureType(const std::string& _fileName)
{
	std::string tmpStr;

	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return nullptr;
		tmpStr = &_fileName[tmpNum];
			}

	if (tmpStr.find("png") != tmpStr.npos)
	{
		return ChPtr::Make_S<PngTex9>();
	}

	if (tmpStr.find("jpeg") != tmpStr.npos
		|| tmpStr.find("jpg") != tmpStr.npos)
	{
		return ChPtr::Make_S<JpegTex9>();
	}

	return nullptr;
}

#endif

#endif

#endif
#endif
#endif
#endif

