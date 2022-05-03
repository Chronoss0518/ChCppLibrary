#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../Texture/ChWinTexture.h"
#include"ChWinBrush.h"

using namespace ChWin;

void Brush::Release()
{
	if (ChPtr::NotNullCheck(brush))return;
	DeleteObject(brush);
	brush = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::CreateSolidBrush(const unsigned char _r, const unsigned char _g, const unsigned char _b)
{
	Release();
	brush = ::CreateSolidBrush(RGB(_r, _b, _g));
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::CreateHatchBrush(const unsigned char _r, const unsigned char _g, const unsigned char _b, const int _type)
{
	Release();
	brush = ::CreateHatchBrush(_type, RGB(_r, _g, _b));
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::CreateNullBrush()
{
	Release();

	LOGBRUSH brushBase;
	ChStd::MZero(&brushBase);
	brushBase.lbStyle = BS_NULL;

	brush = ::CreateBrushIndirect(&brushBase);
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::CreatePatterBrush(const Texture* _tex)
{
	if (ChPtr::NullCheck(_tex))return;
	CreatePatterBrush(_tex->GetBitMap());
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::CreatePatterBrush(const ChPtr::Shared<Texture>& _tex)
{
	if (_tex == nullptr)return;
	CreatePatterBrush(_tex->GetBitMap());
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::CreatePatterBrush(const HBITMAP _tex)
{
	if (ChPtr::NullCheck(_tex))return;
	Release();

	brush = ::CreatePatternBrush(_tex);
}

///////////////////////////////////////////////////////////////////////////////////

void Brush::SetBrush(HBRUSH _brush)
{
	if (ChPtr::NullCheck(_brush))return;

	Release();

	brush = _brush;
};

///////////////////////////////////////////////////////////////////////////////////

HBRUSH Brush::SelectBrush(HDC _dc)
{
	return static_cast<HBRUSH>(SelectObject(_dc, brush));
}
