
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChFont9.h"

using namespace ChD3D9;

///////////////////////////////////////////////////////////////////////////////////////
//ChFont9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void DrawFontBase::Release()
{
	if (ChPtr::NullCheck(lpFont))return;
	lpFont->Release();
	lpFont = nullptr;

	SetInitFlg(false);
}

void DrawFontA::Init(const LPDIRECT3DDEVICE9 _dv, const char* _fontTypeText)
{
	Release();

	device = _dv;
	D3DXCreateFontA(
		device,
		fontSize.h,
		fontSize.w,
		fontWeight,
		NULL,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		_fontTypeText,
		&lpFont);

	SetInitFlg(true);
}

void DrawFontA::Draw(
	const char* _drawStr,
	const unsigned long _drawStrLen,
	const long _x,
	const long _y,
	ChVec4 _col)
{
	auto col = D3DCOLOR_ARGB(
		static_cast<unsigned char>(_col.a * 255),
		static_cast<unsigned char>(_col.r * 255),
		static_cast<unsigned char>(_col.g * 255),
		static_cast<unsigned char>(_col.b * 255));

	RECT rc = { _x, _y,_x + fontSize.w, _y + fontSize.h };
	lpFont->DrawTextA(NULL, _drawStr, _drawStrLen, &rc, DT_LEFT | DT_NOCLIP, col);
}

const char* ChD3D9::DrawFontA::GetFontType()
{
	return fontType.c_str();
}

void DrawFontW::Init(const LPDIRECT3DDEVICE9 _dv, const wchar_t* _fontTypeText)
{
	Release();

	device = _dv;
	D3DXCreateFontW(
		device,
		fontSize.h,
		fontSize.w,
		fontWeight,
		NULL,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		_fontTypeText,
		&lpFont);

	SetInitFlg(true);
}

void DrawFontW::Draw(
	const wchar_t* _drawStr,
	const unsigned long _drawStrLen,
	const long _x,
	const long _y,
	ChVec4 _col)
{

	auto col = D3DCOLOR_ARGB(
		static_cast<unsigned char>(_col.a * 255),
		static_cast<unsigned char>(_col.r * 255),
		static_cast<unsigned char>(_col.g * 255),
		static_cast<unsigned char>(_col.b * 255));

	RECT rc = { _x, _y,_x + fontSize.w, _y + fontSize.h };
	lpFont->DrawTextW(NULL, _drawStr, _drawStrLen, &rc, DT_LEFT | DT_NOCLIP, col);
}

const wchar_t* ChD3D9::DrawFontW::GetFontType()
{
	return fontType.c_str();
}
