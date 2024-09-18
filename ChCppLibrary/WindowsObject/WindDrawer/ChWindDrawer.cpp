#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"
#include"../PackData/ChPoint.h"

#include"ChWindDrawer.h"

using namespace ChWin;

void WindDrawer::Release()
{
	DrawEnd();
}

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

void WindDrawer::SetRenderTarget(HDC _renderTarget)
{
	if (ChPtr::NotNullCheck(hDC))return;

	if (ChPtr::NullCheck(_renderTarget))return;

	SelectObject(hDC, _renderTarget);
}

void WindDrawer::SetRenderTarget(Texture _renderTarget)
{
	if (ChPtr::NotNullCheck(hDC))return;

	if (!_renderTarget.IsInit())return;

	_renderTarget.SetTextureToHDC(hDC);

	return;
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

	RECT rec;
	GetClientRect(_hWind, &rec);

	bb.CreateRenderTarget(hDC, rec.right - rec.left, rec.bottom - rec.top);

}

void WindDrawer::DrawString(const char* _str, const unsigned long _strLen, const ChINTPOINT& _pos)
{

	if (ChPtr::NullCheck(hDC))return;

	auto pos = _pos;

	pos.val.Abs();

	TextOutA(hDC, pos.x, pos.y, _str, _strLen);
}

void WindDrawer::DrawString(const wchar_t* _str, const unsigned long _strLen, const ChINTPOINT& _pos)
{
	if (ChPtr::NullCheck(hDC))return;

	auto pos = _pos;

	pos.val.Abs();

	TextOutW(hDC, pos.x, pos.y, _str, _strLen);
}

void WindDrawer::DrawLine(const ChINTPOINT& _startPos, const ChINTPOINT& _endPos)
{
	if (ChPtr::NullCheck(hDC))return;

	auto spos = _startPos;
	spos.val.Abs();
	auto epos = _endPos;
	epos.val.Abs();

	MoveToEx(hDC, spos.x, spos.y, nullptr);
	LineTo(hDC, epos.x, epos.y);
	MoveToEx(hDC, 0, 0, nullptr);
}

void WindDrawer::DrawLine(const int _startX, const int _startY, const int _endX, const int _endY)
{
	DrawLine(ChINTPOINT(_startX,_startY), ChINTPOINT(_endX, _endY));
}

void WindDrawer::DrawTexture(HBITMAP _texture, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const unsigned long _opeCode)
{
	auto pos = _pos;
	auto size = _size;
	auto bpos = _basePos;

	HDC tmp = CreateCompatibleDC(hDC);

	SelectObject(tmp, _texture);

	BitBlt(hDC, pos.x, pos.y, size.w, size.h, tmp, bpos.x, bpos.y, _opeCode);

	DeleteDC(tmp);
}

void WindDrawer::DrawTexture(HBITMAP _texture, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const unsigned long _opeCode)
{
	if (ChPtr::NullCheck(hDC))return;

	DrawTexture(_texture, ChINTPOINT(_x,_y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY));
}

void WindDrawer::DrawTexture(Texture& _texture, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos)
{

	auto pos = _pos;
	auto size = _size;
	auto bpos = _basePos;

	HDC tmp = CreateCompatibleDC(hDC);

	_texture.SetTextureToHDC(tmp);

	BitBlt(hDC, pos.x, pos.y, size.w, size.h, tmp, bpos.x, bpos.y, SRCCOPY);

	DeleteDC(tmp);
}

void WindDrawer::DrawTexture(Texture& _texture, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY)
{
	DrawTexture(_texture, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY));

}

void WindDrawer::DrawEnd()
{
	if (ChPtr::NullCheck(hDC))return;

	RECT rec;
	GetClientRect(hWind, &rec);

	BitBlt(hDC, 0, 0, rec.right - rec.left, rec.bottom - rec.top, bb.GetRenderTarget(), 0, 0, SRCCOPY);

	ReleaseDC(hWind,hDC);

	
	hDC = nullptr;
	hWind = nullptr;
}
