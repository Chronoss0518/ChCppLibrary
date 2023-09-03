#include<Windows.h>

#include<d2d1.h>
#include<dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

#include"../../BaseIncluder/ChBase.h"

#include"ChDirectFont.h"

#pragma warning(disable : 4996)

#ifndef D3DOBJECT_RELEASE
#define D3DOBJECT_RELEASE(obj)if(ChPtr::NotNullCheck(obj)){obj->Release();obj = nullptr;}
#endif

using namespace ChD3D;

void TextFormatObject::SetTextAlignment(DWRITE_TEXT_ALIGNMENT _alignment)
{
	if (ChPtr::NullCheck(textFormat))return;
	(textFormat)->SetTextAlignment(_alignment);
}

void TextFormatObject::SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT _alignment)
{
	if (ChPtr::NullCheck(textFormat))return;
	(textFormat)->SetParagraphAlignment(_alignment);
}

void DirectFont::Init(
	unsigned long _w,
	unsigned long _h,
	HWND _hwnd,
	LocaleNameId _localeNameId)
{
	if (thisDrawerFlg)return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _w;
	size.height = _h;

	ID2D1HwndRenderTarget* tmpRenderTarget = nullptr;

	if (FAILED(d2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			_hwnd,
			size
		),
		&tmpRenderTarget
	))) {
		Release();
		return;
	};

	renderTarget = tmpRenderTarget;

	thisDrawerFlg = false;

	localeNameId = _localeNameId;

}

void DirectFont::Init(
	IDXGISurface* _surface,
	LocaleNameId _localeNameId)
{
	if (thisDrawerFlg)return;

	if (!InitBase())return;

	FLOAT dpiX = 0.0f;
	FLOAT dpiY = 0.0f;

	d2dFactory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES property;
	
	ChStd::MZero(&property);

	property = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT, 
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpiX, 
		dpiY);

	if (FAILED(d2dFactory->CreateDxgiSurfaceRenderTarget(
		_surface,
		&property,
		&renderTarget
	))) {
		Release();
		return;
	};

	thisDrawerFlg = false;

	localeNameId = _localeNameId;


}

void DirectFont::Release()
{
	if (thisDrawerFlg)return;

	ReleaseTextFormat();
	ReleaseBrush();

	D3DOBJECT_RELEASE(dwFactory);
	D3DOBJECT_RELEASE(d2dFactory);
	D3DOBJECT_RELEASE(renderTarget);
}

void DirectFont::ReleaseTextFormat()
{
	if (thisDrawerFlg)return;

	if (textFormatList.empty())return;

	for (auto&& textFormat : textFormatList)
	{
		if (ChPtr::NullCheck((textFormat)))continue;
		(textFormat)->Release();
	}
	textFormatList.clear();
}

void DirectFont::ReleaseBrush()
{
	if (thisDrawerFlg)return;

	if (brushList.empty())return;

	for (auto&& brush : brushList)
	{
		if (ChPtr::NullCheck((brush)))continue;
		(brush)->Release();
	}
	brushList.clear();

}

bool DirectFont::InitBase()
{

	Release();

	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory)))return false;

	if (FAILED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&dwFactory)
	)))
	{
		Release();
		return false;
	}

#if false
	if (FAILED(dwFactory->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		72.0f,
		L"en-us",
		&textFormat
	)))
	{
		Release();
		return false;
	}
#endif

	return true;

}

TextFormatObject DirectFont::CreateTextFormat(
	const std::wstring& _familyName,
	IDWriteFontCollection* _collection,
	DWRITE_FONT_WEIGHT _weight,
	DWRITE_FONT_STYLE _style,
	DWRITE_FONT_STRETCH _stretch,
	float _fontSize)
{
	TextFormatObject res;

	if (_familyName.length() <= 0)return res;
	if (_fontSize <= 0.0f)return res;

	auto localeName = GetLocaleName(localeNameId);

	if (localeName.length() <= 0)return res;
	if (ChPtr::NullCheck(dwFactory))return res;

	IDWriteTextFormat* format = nullptr;

	if(FAILED(dwFactory->CreateTextFormat(
		_familyName.c_str(),
		_collection,
		_weight,
		_style,
		_stretch,
		_fontSize,
		localeName.c_str(),
		&format
	)))return res;

	res.textFormat = format;

	textFormatList.push_back(format);

	return res;
}

BrushObject DirectFont::CreateBrush(const ChVec4& _color)
{
	BrushObject res;

	if (ChPtr::NullCheck(renderTarget))return res;

	D2D_COLOR_F color = D2D_COLOR_F();
	color.a = _color.a;
	color.r = _color.r;
	color.g = _color.g;
	color.b = _color.b;

	ID2D1SolidColorBrush* brush;

	if(FAILED(renderTarget->CreateSolidColorBrush(
		color,
		&brush
	)))return res;

	res.brush = brush;
	brushList.push_back(brush);

	return res;
}

void DirectFont::DrawStart()
{

	if (GetDrawFlg())return;

	if (ChPtr::NullCheck(renderTarget))return;

	renderTarget->BeginDraw();

	if (clearDisplayFlg)
	{
		D2D_COLOR_F clearColor;

		clearColor.a = clearDisplayColor.a;
		clearColor.r = clearDisplayColor.r;
		clearColor.g = clearDisplayColor.g;
		clearColor.b = clearDisplayColor.b;

		renderTarget->Clear(clearColor);
	}

	thisDrawerFlg = true;
	GetDrawFlg() = true;
}

void DirectFont::DrawEnd()
{
	if (!thisDrawerFlg)return;
	
	renderTarget->EndDraw();

	thisDrawerFlg = false;
	GetDrawFlg() = false;
}

std::wstring DirectFont::GetLocaleName(LocaleNameId _localeName)
{
	unsigned long localeNameNo = ChStd::EnumCast(_localeName);
	static std::wstring localeName[] = { L"en-us",L"ja-JP" };

	if (localeNameNo >= (sizeof(localeName) / sizeof(std::wstring)))return L"";

	return localeName[localeNameNo];
}
