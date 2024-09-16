#include<Windows.h>
#include<wincodec.h>
#include<roapi.h>

#include"../../BaseIncluder/ChBase.h"

#include"ChWICBitmapCreator.h"

#pragma comment(lib,"WindowsApp.lib")

#ifndef D3DOBJECT_RELEASE
#define D3DOBJECT_RELEASE(obj) if(ChPtr::NotNullCheck(obj)){obj->Release();obj = nullptr;}
#endif

#ifndef D3DOBJECT_NULLCHECK
#define D3DOBJECT_NULLCHECK(obj,method) if(ChPtr::NotNullCheck(obj))obj->method
#endif

using namespace ChD3D;

void WICBitmapCreator::Init()
{
	HRESULT result = Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);

	if (FAILED(result))return;

	result = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&factory);

	if (FAILED(result))
		Release();
}

void WICBitmapCreator::Release()
{

	size_t count = GetBitmapCount();

	if (count <= 0)return;

	for (size_t i = 0; i < count; i++)
	{
		auto&& bitmap = GetBitmap(i);
		D3DOBJECT_RELEASE(bitmap);
	}

	ClearBitmapList();

	D3DOBJECT_RELEASE(factory);

	Windows::Foundation::Uninitialize();
}

WICBitmapObject WICBitmapCreator::CreateBitmapObject(unsigned long _width, unsigned long _height)
{
	WICBitmapObject res;

	if (ChPtr::NullCheck(factory))return res;

	factory->CreateBitmap(_width, _height, GUID_WICPixelFormat128bppPRGBAFloat, WICBitmapCacheOnLoad, &res.bitmap);

	AddBitmap(res.bitmap);

	return res;
}