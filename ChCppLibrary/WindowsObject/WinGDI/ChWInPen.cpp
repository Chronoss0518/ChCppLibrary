#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"ChWinPen.h"

using namespace ChWin;

void Pen::Release()
{
	if (ChPtr::NullCheck(pen))return;
	DeleteObject(pen);
	pen = nullptr;
}

void Pen::CreatePen(
	const unsigned char _r,
	const unsigned char _g,
	const unsigned char _b, 
	unsigned short _width,
	const PenStyle _style)
{

	Release();
	pen = ::CreatePen(ChStd::EnumCast(_style), static_cast<int>(_style), RGB(_r, _g, _b));
}

void Pen::CreateNullPen()
{
	Release();
	pen = ::CreatePen(PS_NULL, 0, 0);
}

HPEN Pen::SelectPen(HDC _dc)
{
	return static_cast<HPEN>(SelectObject(_dc, pen));
}
