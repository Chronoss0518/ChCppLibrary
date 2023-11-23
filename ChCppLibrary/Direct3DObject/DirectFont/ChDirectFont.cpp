#include<Windows.h>

#include<d2d1.h>
#include<dwrite.h>
#include<wincodec.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

#include"../../BaseIncluder/ChBase.h"

#include"ChDirectFont.h"

#pragma warning(disable : 4996)

#ifndef D3DOBJECT_RELEASE
#define D3DOBJECT_RELEASE(obj)if(ChPtr::NotNullCheck(obj)){obj->Release();obj = nullptr;}
#endif

#ifndef D3DOBJECT_NULLCHECK
#define D3DOBJECT_NULLCHECK(obj,method)if(ChPtr::NotNullCheck(obj))obj->method
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

void BrushObject::SetColor(const D2D_COLOR_F& _color)
{
	if (ChPtr::NullCheck(brush))return;
	brush->SetColor(_color);
}

void BrushObject::SetColor(const ChVec4& _color)
{
	if (ChPtr::NullCheck(brush))return;
	brush->SetColor(DirectFontBase::ToD2DCOLORF(_color));
}

void LayoutObject::SetFontSize(float _size, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetFontSize(_size, useRange);
}

void LayoutObject::SetFontStrikethrough(bool _useFlg, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetStrikethrough(_useFlg, useRange);

}

void LayoutObject::SetFontUnderline(bool _useFlg, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetUnderline(_useFlg, useRange);
}

void LayoutObject::SetLayoutBoxWidth(float _width)
{
	D3DOBJECT_NULLCHECK(data->layout,SetMaxWidth(_width));
}

void LayoutObject::SetLayoutBoxHeight(float _height)
{
	D3DOBJECT_NULLCHECK(data->layout, SetMaxHeight(_height));
}

void LayoutObject::SetFamilyName(const std::wstring& _familyName, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetFontFamilyName(_familyName.c_str(), useRange);
}

void LayoutObject::SetFontCollection(IDWriteFontCollection* _collection, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetFontCollection(_collection, useRange);
	
}

void LayoutObject::SetFontWeight(DWRITE_FONT_WEIGHT _weight, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetFontWeight(_weight, useRange);
}

void LayoutObject::SetFontStyle(DWRITE_FONT_STYLE _style, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetFontStyle(_style, useRange);
}

void LayoutObject::SetFontStretch(DWRITE_FONT_STRETCH _stretch, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetFontStretch(_stretch, useRange);
}

void LayoutObject::SetLocaleName(const std::wstring& _localeName, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(data->layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	data->layout->SetLocaleName(_localeName.c_str(), useRange);
}

DWRITE_TEXT_RANGE LayoutObject::GetUseRange(const DWRITE_TEXT_RANGE& _range)
{
	DWRITE_TEXT_RANGE res = _range;
	
	if (res.length <= 0 || (res.length + _range.startPosition) >= textLength)
	{
		res.length = (textLength - _range.startPosition);
	}

	return res;
}

void DirectFontBase::Release()
{
	if (thisDrawerFlg)return;

	ReleaseTextFormat();
	ReleaseBrush();
	ReleaseLayout();

	D3DOBJECT_RELEASE(dwFactory);
	D3DOBJECT_RELEASE(d2dFactory);
	D3DOBJECT_RELEASE(renderTarget);
}

void DirectFontBase::ReleaseTextFormat()
{
	if (thisDrawerFlg)return;

	if (textFormatList.empty())return;

	for (auto&& textFormat : textFormatList)
	{
		D3DOBJECT_RELEASE(textFormat);
	}
	textFormatList.clear();
}

void DirectFontBase::ReleaseBrush()
{
	if (thisDrawerFlg)return;

	if (brushList.empty())return;

	for (auto&& brush : brushList)
	{
		D3DOBJECT_RELEASE(brush);
	}
	brushList.clear();

}

void DirectFontBase::ReleaseLayout()
{
	if (thisDrawerFlg)return;

	if (layoutList.empty())return;

	for (auto&& layout : layoutList)
	{
		D3DOBJECT_RELEASE(layout->layout);
		delete layout;
	}
	layoutList.clear();

}

bool DirectFontBase::InitBase()
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

void DirectFontBase::EndInit(LocaleNameId _localeNameId)
{
	displaySize = renderTarget->GetSize();

	thisDrawerFlg = false;
	localeNameId = _localeNameId;

}

TextFormatObject DirectFontBase::CreateTextFormat(
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

	return CreateTextFormat(_familyName, _collection, _weight, _style, _stretch, _fontSize, localeName);
}

TextFormatObject DirectFontBase::CreateTextFormat(
	const std::wstring& _familyName,
	IDWriteFontCollection* _collection,
	DWRITE_FONT_WEIGHT _weight,
	DWRITE_FONT_STYLE _style,
	DWRITE_FONT_STRETCH _stretch,
	float _fontSize,
	const std::wstring& _localeName)
{
	TextFormatObject res;

	if (_familyName.length() <= 0)return res;
	if (_fontSize <= 0.0f)return res;

	if (ChPtr::NullCheck(dwFactory))return res;

	IDWriteTextFormat* format = nullptr;

	if (FAILED(dwFactory->CreateTextFormat(
		_familyName.c_str(),
		_collection,
		_weight,
		_style,
		_stretch,
		_fontSize,
		_localeName.c_str(),
		&format
	)))return res;

	res.textFormat = format;
	textFormatList.push_back(format);

	return res;
}

BrushObject DirectFontBase::CreateBrush(const ChVec4& _color)
{
	return CreateBrush(ToD2DCOLORF(_color));
}

BrushObject DirectFontBase::CreateBrush(const D2D_COLOR_F& _color)
{
	BrushObject res;

	if (ChPtr::NullCheck(renderTarget))return res;

	ID2D1SolidColorBrush* brush;

	if (FAILED(renderTarget->CreateSolidColorBrush(
		_color,
		&brush
	)))return res;

	res.brush = brush;

	brushList.push_back(brush);

	return res;
}

LayoutObject DirectFontBase::CreateLayout(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	IDWriteTextFormat* _textFormat)
{
	LayoutObject res;

	if (_drawText.length() <= 0)return res;
	if (ChPtr::NullCheck(_textFormat))return res;
	if (ChPtr::NullCheck(dwFactory))return res;
	if (ChPtr::NullCheck(renderTarget))return res;

	IDWriteTextLayout* layout;

	if (FAILED(dwFactory->CreateTextLayout(
		_drawText.c_str(),
		_drawText.length(),
		_textFormat,
		_layoutBoxWidth,
		_layoutBoxHeight,
		&layout)))
	{
		return res;
	}

	res.data = new LayoutObject::LayoutStruct();
	res.data->layout = layout;
	res.textLength = _drawText.length();
	layoutList.push_back(res.data);

	return res;
}

LayoutObject DirectFontBase::CreateLayoutToProjection(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	IDWriteTextFormat* _textFormat)
{
	float width = (_layoutBoxWidth * 0.5f + 0.5f) * displaySize.width;
	float height = (_layoutBoxHeight * 0.5f + 0.5f) * displaySize.height;

	auto&& layout = CreateLayout(_drawText, width, height, _textFormat);

	layout.data->toProjectionFlg = true;
	
	return layout;
}

LayoutObject DirectFontBase::CreateLayoutToProjection(
	const std::wstring& _drawText,
	const ChVec2& _layoutSize,
	IDWriteTextFormat* _textFormat)
{
	float width = (_layoutSize.w * 0.5f + 0.5f) * displaySize.width;
	float height = (_layoutSize.h * 0.5f + 0.5f) * displaySize.height;

	auto&& layout = CreateLayout(_drawText, width, height, _textFormat);

	layout.data->toProjectionFlg = true;

	return layout;
}

LayoutObject DirectFontBase::CreateLayoutToProjection(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	const TextFormatObject& _textFormat)
{
	float width = (_layoutBoxWidth * 0.5f + 0.5f) * displaySize.width;
	float height = (_layoutBoxHeight * 0.5f + 0.5f) * displaySize.height;

	auto&& layout = CreateLayout(_drawText, width, height, _textFormat.textFormat);

	layout.data->toProjectionFlg = true;

	return layout;
}

LayoutObject DirectFontBase::CreateLayoutToProjection(
	const std::wstring& _drawText,
	const ChVec2& _layoutSize,
	const TextFormatObject& _textFormat)
{
	float width = (_layoutSize.w * 0.5f + 0.5f) * displaySize.width;
	float height = (_layoutSize.h * 0.5f + 0.5f) * displaySize.height;

	auto&& layout = CreateLayout(_drawText, width, height, _textFormat.textFormat);

	layout.data->toProjectionFlg = true;

	return layout;
}

LayoutObject DirectFontBase::CreateLayoutToScreen(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	IDWriteTextFormat* _textFormat)
{
	return CreateLayout(_drawText, _layoutBoxWidth, _layoutBoxHeight, _textFormat);
}

LayoutObject DirectFontBase::CreateLayoutToScreen(
	const std::wstring& _drawText,
	const ChVec2& _layoutSize,
	IDWriteTextFormat* _textFormat)
{
	return CreateLayout(_drawText, _layoutSize.w, _layoutSize.h, _textFormat);
}

LayoutObject DirectFontBase::CreateLayoutToScreen(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	const TextFormatObject& _textFormat)
{
	return CreateLayout(_drawText, _layoutBoxWidth, _layoutBoxHeight, _textFormat.textFormat);
}

LayoutObject DirectFontBase::CreateLayoutToScreen(
	const std::wstring& _drawText,
	const ChVec2& _layoutSize,
	const TextFormatObject& _textFormat)
{
	return CreateLayout(_drawText, _layoutSize.w, _layoutSize.h, _textFormat.textFormat);
}

std::wstring DirectFontBase::GetLocaleName(LocaleNameId _localeName)
{
	unsigned long localeNameNo = ChStd::EnumCast(_localeName);
	static std::wstring localeName[] = { L"en-us",L"ja-JP" };

	if (localeNameNo >= (sizeof(localeName) / sizeof(std::wstring)))return L"";

	return localeName[localeNameNo];
}

void DirectFontBase::DrawStart()
{

	if (GetDrawFlg())return;

	if (ChPtr::NullCheck(renderTarget))return;

	auto&& nowDisplaySize = renderTarget->GetSize();
	if (std::abs(nowDisplaySize.height - displaySize.height) >= 0.1f ||
		std::abs(nowDisplaySize.width - displaySize.width) >= 0.1f)
	{
		float width = 0.0f;
		float height = 0.0f;
		for (auto&& layout : layoutList)
		{
			if (!layout->toProjectionFlg)continue;

			width = layout->layout->GetMaxWidth();
			height = layout->layout->GetMaxHeight();

			width = width / displaySize.width * nowDisplaySize.width;
			height = height / displaySize.height * nowDisplaySize.height;

			layout->layout->SetMaxWidth(width);
			layout->layout->SetMaxHeight(height);
		}
		displaySize = nowDisplaySize;
	}


	renderTarget->BeginDraw();

	if (clearDisplayFlg)
	{
		renderTarget->Clear(clearDisplayColor);
	}

	thisDrawerFlg = true;
	GetDrawFlg() = true;
}

//左上から0,0のディスプレイ座標系で計算する//
void DirectFontBase::DrawToProjection(
	const std::wstring& _text,
	IDWriteTextFormat* _textFormat,
	ID2D1SolidColorBrush* _brushObject,
	const D2D1_RECT_F& _drawRect)
{

	if (!thisDrawerFlg)return;
	if (_text.length() <= 0)return;
	if (ChPtr::NullCheck(_textFormat))return;
	if (ChPtr::NullCheck(_brushObject))return;

	DrawTextMethod(_text, _textFormat, _brushObject, ToProjectionCoodinateSystem(_drawRect));
}

//左上から0,0のディスプレイ座標系で計算する//
void DirectFontBase::DrawToProjection(
	const std::wstring& _text,
	IDWriteTextFormat* _textFormat,
	ID2D1SolidColorBrush* _brushObject,
	const ChVec4& _drawRect)
{
	if (!thisDrawerFlg)return;
	if (_text.length() <= 0)return;
	if (ChPtr::NullCheck(_textFormat))return;
	if (ChPtr::NullCheck(_brushObject))return;

	D2D1_RECT_F layoutRect = ToD2DRECTF(_drawRect);

	DrawToProjection(_text, _textFormat, _brushObject, layoutRect);
}

void DirectFontBase::DrawToScreen(
	const std::wstring& _text,
	IDWriteTextFormat* _textFormat,
	ID2D1SolidColorBrush* _brushObject,
	const D2D1_RECT_F& _drawRect)
{

	if (!thisDrawerFlg)return;
	if (_text.length() <= 0)return;
	if (ChPtr::NullCheck(_textFormat))return;
	if (ChPtr::NullCheck(_brushObject))return;

	DrawTextMethod(_text, _textFormat, _brushObject, _drawRect);
}

void DirectFontBase::DrawToScreen(
	const std::wstring& _text,
	IDWriteTextFormat* _textFormat,
	ID2D1SolidColorBrush* _brushObject,
	const ChVec4& _drawRect)
{
	if (!thisDrawerFlg)return;
	if (_text.length() <= 0)return;
	if (ChPtr::NullCheck(_textFormat))return;
	if (ChPtr::NullCheck(_brushObject))return;

	D2D1_RECT_F layoutRect = ToD2DRECTF(_drawRect);

	DrawToScreen(_text, _textFormat, _brushObject, layoutRect);

}

void DirectFontBase::DrawLayout(
	const ChVec2& _drawPosition,
	LayoutObject& _layout,
	BrushObject& _brush,
	D2D1_DRAW_TEXT_OPTIONS _options)
{

	if (!thisDrawerFlg)return;
	if (ChPtr::NullCheck(_layout.data))return;
	if (ChPtr::NullCheck(_layout.data->layout))return;
	if (ChPtr::NullCheck(_brush.brush))return;


	D2D1_POINT_2F drawPosition = ToD2DPOINT2F(_drawPosition);

	if (_layout.data->toProjectionFlg)
	{
		drawPosition.x = (drawPosition.x * 0.5f + 0.5f) * displaySize.width;

		drawPosition.y = (drawPosition.y * -0.5f + 0.5f) * displaySize.height;
	}

	renderTarget->DrawTextLayout(drawPosition, _layout.data->layout, _brush.brush, _options);
}

void DirectFontBase::DrawLayout(
	const D2D1_POINT_2F& _drawPosition,
	LayoutObject& _layout,
	BrushObject& _brush,
	D2D1_DRAW_TEXT_OPTIONS _options)
{

	if (!thisDrawerFlg)return;
	if (ChPtr::NullCheck(_layout.data))return;
	if (ChPtr::NullCheck(_layout.data->layout))return;
	if (ChPtr::NullCheck(_brush.brush))return;

	D2D1_POINT_2F drawPosition = _drawPosition;

	if (_layout.data->toProjectionFlg)
	{
		drawPosition.x = (drawPosition.x * 0.5f + 0.5f) * displaySize.width;

		drawPosition.y = (drawPosition.y * -0.5f + 0.5f) * displaySize.height;
	}

	renderTarget->DrawTextLayout(drawPosition, _layout.data->layout, _brush.brush, _options);

}

void DirectFontBase::DrawLayout(
	const ChVec2& _drawPosition,
	IDWriteTextLayout* _layout,
	ID2D1SolidColorBrush* _brush,
	D2D1_DRAW_TEXT_OPTIONS _options)
{
	if (!thisDrawerFlg)return;
	if (ChPtr::NullCheck(_layout))return;
	if (ChPtr::NullCheck(_brush))return;

	D2D1_POINT_2F drawPosition = ToD2DPOINT2F(_drawPosition);

	renderTarget->DrawTextLayout(drawPosition, _layout, _brush, _options);
}

void DirectFontBase::DrawLayout(
	const D2D1_POINT_2F& _drawPosition,
	IDWriteTextLayout* _layout,
	ID2D1SolidColorBrush* _brush,
	D2D1_DRAW_TEXT_OPTIONS _options)
{

	if (!thisDrawerFlg)return;
	if (ChPtr::NullCheck(_layout))return;
	if (ChPtr::NullCheck(_brush))return;

	renderTarget->DrawTextLayout(_drawPosition, _layout, _brush, _options);

}

void DirectFontBase::DrawEnd()
{
	if (!thisDrawerFlg)return;
	
	renderTarget->EndDraw();

	thisDrawerFlg = false;
	GetDrawFlg() = false;
}

D2D1_RECT_F DirectFontBase::ToProjectionCoodinateSystem(const D2D1_RECT_F& _targetRect)
{
	D2D1_RECT_F res = _targetRect;

	res.top = (res.top * -0.5f + 0.5f) * displaySize.height;
	res.bottom = (res.bottom * -0.5f + 0.5f) * displaySize.height;

	res.left = (res.left * 0.5f + 0.5f) * displaySize.width;
	res.right = (res.right * 0.5f + 0.5f) * displaySize.width;
	return res;
}


void DirectFontFromHWND::Init(
	unsigned long _w,
	unsigned long _h,
	HWND _hwnd,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _w;
	size.height = _h;

	Init(size, _hwnd, _localeNameId);
}

void DirectFontFromHWND::Init(
	ChMath::Vector2Base<unsigned long>& _size,
	HWND _hwnd,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _size.w;
	size.height = _size.h;

	Init(size, _hwnd, _localeNameId);
}

void DirectFontFromHWND::Init(
	D2D1_SIZE_U& _size,
	HWND _hwnd,
	LocaleNameId _localeNameId)
{

	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	ID2D1HwndRenderTarget* tmpRenderTarget = nullptr;

	if (FAILED(d2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			_hwnd,
			_size
		),
		&tmpRenderTarget
	))) {
		Release();
		return;
	};

	renderTarget = tmpRenderTarget;

	EndInit(_localeNameId);
}

void DirectFontFromHDC::Init(
	unsigned long _w,
	unsigned long _h,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _w;
	size.height = _h;

	Init(size, _localeNameId);
}

void DirectFontFromHDC::Init(
	ChMath::Vector2Base<unsigned long>& _size,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _size.w;
	size.height = _size.h;

	Init(size, _localeNameId);
}

void DirectFontFromHDC::Init(
	D2D1_SIZE_U& _size,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	ID2D1DCRenderTarget* tmpRenderTarget = nullptr;

	D2D1_RENDER_TARGET_PROPERTIES property;

	ChStd::MZero(&property);

	property = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		_size.width,
		_size.height);

	if (FAILED(d2dFactory->CreateDCRenderTarget(
		&property,
		&tmpRenderTarget
	))) {
		Release();
		return;
	};

	renderTarget = tmpRenderTarget;

	EndInit(_localeNameId);

}

void DirectFontFromHDC::SetHDC(HDC _dc, const ChVec4& _subRect)
{
	RECT rect;
	rect.top = _subRect.top;
	rect.right = _subRect.right;
	rect.bottom = _subRect.bottom;
	rect.left = _subRect.left;

	SetHDC(_dc, rect);
}

void DirectFontFromHDC::SetHDC(HDC _dc,RECT _subRect)
{
	if (IsThisDrawerFlg())return;

	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(renderTarget))return;

	auto rt = static_cast<ID2D1DCRenderTarget*>(renderTarget);

	D3DOBJECT_NULLCHECK(rt, BindDC(_dc,&_subRect));
}

void DirectFontFromWICBitmap::Init(
	unsigned long _w,
	unsigned long _h,
	IWICBitmap* _bitmap,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _w;
	size.height = _h;

	Init(size, _bitmap, _localeNameId);
}

void DirectFontFromWICBitmap::Init(
	ChMath::Vector2Base<unsigned long>& _size,
	IWICBitmap* _bitmap,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _size.w;
	size.height = _size.h;

	Init(size, _bitmap, _localeNameId);
}

void DirectFontFromWICBitmap::Init(
	D2D1_SIZE_U& _size,
	IWICBitmap* _bitmap,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

	if (!InitBase())return;

	if (FAILED(d2dFactory->CreateWicBitmapRenderTarget(
		_bitmap,
		D2D1::RenderTargetProperties(),
		&renderTarget
	))) {
		Release();
		return;
	};

	EndInit(_localeNameId);
}

void DirectFontFromDXGISurface::Init(
	IDXGISurface* _surface,
	LocaleNameId _localeNameId)
{
	if (IsThisDrawerFlg())return;

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

	EndInit(_localeNameId);

}
