
#ifndef Ch_D3D9_TBmp_h
#define Ch_D3D9_TBmp_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class BmpTex9 : BaseTexture9
	{
	public:

		void OpenFile(const char* _fileName)override {};

		void OpenFile(const wchar_t* _fileName)override {};

	};

}

#endif
