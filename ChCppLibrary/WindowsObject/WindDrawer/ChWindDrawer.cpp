#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"ChWindDrawer.h"

using namespace ChWin;

void WindDrawer::SetBrush(Brush& _brush)
{
	if (ChPtr::NullCheck(hDC))return;
	baseBrush.SetBrush(_brush.SelectBrush(hDC));
}

void WindDrawer::SetPen(Pen& _pen)
{
	if (ChPtr::NullCheck(hDC))return;
	basePen.SetPen(_pen.SelectPen(hDC));
}

TEXTMETRIC WindDrawer::GetTextMetric()
{
	TEXTMETRIC out;
	if (ChPtr::NullCheck(hDC))return out;
	GetTextMetrics(hDC, &out);
	return out;
}

void WindDrawer::DrawStart(HWND _hWind)
{
	if (ChPtr::NotNullCheck(hDC))return;
	hWind = _hWind;
	hDC = GetDC(hWind);
}

void WindDrawer::DrawString(const std::string& _str, unsigned short x, unsigned short y)
{
	if (ChPtr::NullCheck(hDC))return;
	TextOut(hDC, x, y, _str.c_str(), _str.length());
}

void WindDrawer::DrawEnd()
{
	if (ChPtr::NullCheck(hDC))return;
	ReleaseDC(hWind,hDC);
	hDC = nullptr;
	hWind = nullptr;
}
