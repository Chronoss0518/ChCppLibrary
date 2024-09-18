
#ifndef Ch_D3D9_TBmp_h
#define Ch_D3D9_TBmp_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class BmpTex9 : BaseTexture9
	{
	public:

#ifdef CRT

		void OpenFile(const char* _fileName)override {};

#endif 

	};

}

#include"ChTextureShared9.h"

#endif
