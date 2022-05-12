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

	ReleaseDC(hWind, hDC);
	hDC = nullptr;
}

void WindDrawer::DrawString(const std::string& _str, const ChMath::Vector2Base<int>& _pos)
{

	if (ChPtr::NullCheck(hDC))return;

	auto pos = _pos;

	pos.val.Abs();

	TextOutA(hDC, pos.x, pos.y, _str.c_str(), _str.length());
}

void WindDrawer::DrawString(const std::string& _str, const int _x, const int _y)
{
	DrawString(_str, ChMath::Vector2Base<int>(_x, _y));
}

void WindDrawer::DrawString(const std::wstring& _str, const ChMath::Vector2Base<int>& _pos)
{
	if (ChPtr::NullCheck(hDC))return;

	auto pos = _pos;

	pos.val.Abs();

	TextOutW(hDC, pos.x, pos.y, _str.c_str(), _str.length());
}

void WindDrawer::DrawString(const std::wstring& _str, const int _x, const int _y)
{
	DrawString(_str, ChMath::Vector2Base<int>(_x, _y));
}

void WindDrawer::DrawLine(const ChMath::Vector2Base<int>& _startPos, const ChMath::Vector2Base<int>& _endPos)
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
	DrawLine(ChMath::Vector2Base<int>(_startX,_startY), ChMath::Vector2Base<int>(_endX, _endY));
}

void WindDrawer::DrawTexture(HBITMAP _texture, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const unsigned long _opeCode)
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

	DrawTexture(_texture, ChMath::Vector2Base<int>(_x,_y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void WindDrawer::DrawTexture(Texture& _texture, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
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
	DrawTexture(_texture, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));

}

void WindDrawer::DrawEnd()
{
	if (ChPtr::NullCheck(hDC))return;

	RECT rec;
	GetClientRect(hWind, &rec);

	BitBlt(hDC, 0, 0, rec.right - rec.left, rec.bottom - rec.top, bb.GetRenderTarget(), 0, 0, SRCCOPY);

	ReleaseDC(hWind,hDC);

	SendMessage(hWind, WM_PAINT, 0, 0);

	hDC = nullptr;
	hWind = nullptr;
}
