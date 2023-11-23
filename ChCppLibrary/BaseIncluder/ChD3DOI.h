#ifndef Ch_D3DOI_h
#define Ch_D3DOI_h

#ifdef _WINDOWS

#ifdef WIN32

#include<XInput.h>
#include<xaudio2.h>
#include<d2d1.h>
#include<dwrite.h>

#include"../Direct3DObject/XInputController/ChXInputController.h"
#include"../Direct3DObject/XAudios/ChXAudio.h"
#include"../Direct3DObject/WICBitmapCreator/ChWICBitmapCreator.h"
#include"../Direct3DObject/DirectFont/ChDirectFont.h"

#else

#include<XInput.h>
#include<xaudio2.h>
#include<d2d1.h>
#include<dwrite.h>

#include"../Direct3DObject/XInputController/ChXInputController.h"
#include"../Direct3DObject/XAudios/ChXAudio.h"

#endif

#ifndef Ch_Library_Create
#ifdef _MT
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"ChDirect3DObject_MDd.lib")
#else
#pragma comment(lib,"ChDirect3DObject_MD.lib")
#endif//_DEBUG
#else//_DLL
#ifdef _DEBUG
#pragma comment(lib,"ChDirect3DObject_MTd.lib")
#else
#pragma comment(lib,"ChDirect3DObject_MT.lib")
#endif//_DEBUG
#endif//else
#endif//_MT
#endif//Ch_Library_Create

#endif
#endif