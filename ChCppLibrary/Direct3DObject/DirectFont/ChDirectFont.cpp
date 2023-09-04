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
	brush->SetColor(DirectFont::ToD2DCOLORF(_color));
}

void LayoutObject::SetFontSize(float _size, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetFontSize(_size, useRange);
}

void LayoutObject::SetFontStrikethrough(bool _useFlg, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetStrikethrough(_useFlg, useRange);

}

void LayoutObject::SetFontUnderline(bool _useFlg, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetUnderline(_useFlg, useRange);
}

void LayoutObject::SetLayoutBoxWidth(float _width)
{
	D3DOBJECT_NULLCHECK(layout,SetMaxWidth(_width));
}

void LayoutObject::SetLayoutBoxHeight(float _height)
{
	D3DOBJECT_NULLCHECK(layout, SetMaxHeight(_height));
}

void LayoutObject::SetFamilyName(const std::wstring& _familyName, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetFontFamilyName(_familyName.c_str(), useRange);
}

void LayoutObject::SetFontCollection(IDWriteFontCollection* _collection, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetFontCollection(_collection, useRange);
	
}

void LayoutObject::SetFontWeight(DWRITE_FONT_WEIGHT _weight, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetFontWeight(_weight, useRange);
}

void LayoutObject::SetFontStyle(DWRITE_FONT_STYLE _style, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetFontStyle(_style, useRange);
}

void LayoutObject::SetFontStretch(DWRITE_FONT_STRETCH _stretch, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetFontStretch(_stretch, useRange);
}

void LayoutObject::SetLocaleName(const std::wstring& _localeName, const DWRITE_TEXT_RANGE& _range)
{
	if (ChPtr::NullCheck(layout))return;
	if (_range.startPosition >= textLength)return;

	DWRITE_TEXT_RANGE useRange = GetUseRange(_range);

	layout->SetLocaleName(_localeName.c_str(), useRange);
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

	Init(size, _hwnd, _localeNameId);
}

void DirectFont::Init(
	ChMath::Vector2Base<unsigned long>& _size,
	HWND _hwnd,
	LocaleNameId _localeNameId)
{
	if (thisDrawerFlg)return;

	if (!InitBase())return;

	D2D1_SIZE_U size;
	size.width = _size.w;
	size.height = _size.h;

	Init(size, _hwnd, _localeNameId);
}

void DirectFont::Init(
	D2D1_SIZE_U& _size,
	HWND _hwnd,
	LocaleNameId _localeNameId)
{

	if (thisDrawerFlg)return;

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
	ReleaseLayout();

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

void DirectFont::ReleaseLayout()
{
	if (thisDrawerFlg)return;

	if (layoutList.empty())return;

	for (auto&& layout : layoutList)
	{
		if (ChPtr::NullCheck((layout)))continue;
		(layout)->Release();
	}
	layoutList.clear();

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

	return CreateTextFormat(_familyName, _collection, _weight, _style, _stretch, _fontSize, localeName);
}

TextFormatObject DirectFont::CreateTextFormat(
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

BrushObject DirectFont::CreateBrush(const ChVec4& _color)
{
	return CreateBrush(ToD2DCOLORF(_color));
}

BrushObject DirectFont::CreateBrush(const D2D_COLOR_F& _color)
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

LayoutObject DirectFont::CreateLayout(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	IDWriteTextFormat* _textFormat)
{
	LayoutObject res;

	if (_drawText.length() <= 0)return res;
	if (ChPtr::NullCheck(_textFormat))return res;
	if (ChPtr::NullCheck(dwFactory))return res;

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

	res.layout = layout;
	res.textLength = _drawText.length();
	layoutList.push_back(layout);

	return res;
}

LayoutObject DirectFont::CreateLayout(
	const std::wstring& _drawText,
	const ChVec2& _layoutSize,
	IDWriteTextFormat* _textFormat)
{
	return CreateLayout(_drawText, _layoutSize.w, _layoutSize.h, _textFormat);
}

LayoutObject DirectFont::CreateLayout(
	const std::wstring& _drawText,
	float _layoutBoxWidth,
	float _layoutBoxHeight,
	const TextFormatObject& _textFormat)
{
	return CreateLayout(_drawText, _layoutBoxWidth, _layoutBoxHeight, _textFormat.textFormat);
}

LayoutObject DirectFont::CreateLayout(
	const std::wstring& _drawText,
	const ChVec2& _layoutSize,
	const TextFormatObject& _textFormat)
{
	return CreateLayout(_drawText, _layoutSize.w, _layoutSize.h, _textFormat.textFormat);
}

std::wstring DirectFont::GetLocaleName(LocaleNameId _localeName)
{
	unsigned long localeNameNo = ChStd::EnumCast(_localeName);
	static std::wstring localeName[] = { L"en-us",L"ja-JP" };

	if (localeNameNo >= (sizeof(localeName) / sizeof(std::wstring)))return L"";

	return localeName[localeNameNo];
}

void DirectFont::DrawStart()
{

	if (GetDrawFlg())return;

	if (ChPtr::NullCheck(renderTarget))return;

	renderTarget->BeginDraw();

	if (clearDisplayFlg)
	{
		renderTarget->Clear(clearDisplayColor);
	}

	thisDrawerFlg = true;
	GetDrawFlg() = true;

	if (!toProjectionCoodinateSystemFlg)return;

	auto&& displaySize = renderTarget->GetSize();

	displaySize.height *= 0.5f;
	displaySize.width *= 0.5f;

	toProjectionMat = D2D1::Matrix3x2F::Scale(displaySize);
	toProjectionMat.dx = displaySize.width;
	toProjectionMat.dy = displaySize.height;

	//renderTarget->SetTransform(toProjectionMat);
}

//左上から0,0のディスプレイ座標系で計算する//
void DirectFont::Draw(
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
void DirectFont::Draw(
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

	DrawTextMethod(_text, _textFormat, _brushObject, ToProjectionCoodinateSystem(layoutRect));
}

void DirectFont::DrawEnd()
{
	if (!thisDrawerFlg)return;
	
	renderTarget->EndDraw();

	thisDrawerFlg = false;
	GetDrawFlg() = false;
}

D2D1_RECT_F DirectFont::ToProjectionCoodinateSystem(const D2D1_RECT_F& _targetRect)
{
	//return _targetRect;

	if (!toProjectionCoodinateSystemFlg)return _targetRect;

	D2D1_RECT_F res = _targetRect;

	D2D1_POINT_2F tmpSize;
	tmpSize = D2D1::Point2F(res.left, res.top);
	tmpSize = toProjectionMat.TransformPoint(tmpSize);

	res.left = tmpSize.x;
	res.top = tmpSize.y;

	tmpSize = D2D1::Point2F(res.right, res.bottom);
	tmpSize = toProjectionMat.TransformPoint(tmpSize);
	res.right = tmpSize.x;

	res.bottom = tmpSize.y;

	OutputDebugStringA(("DrawRect left:[" + std::to_string(res.left) + "] top [ " + std::to_string(res.top) + "] right [ " + std::to_string(res.right) + "] bottom [ " + std::to_string(res.bottom) + "]\n").c_str());

	return res;
}