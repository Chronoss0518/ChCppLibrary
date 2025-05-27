#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinDrawTexter.h"

#ifndef CH_WIN_DRAW_TEXTER_FUNCTIONS
#define CH_WIN_DRAW_TEXTER_FUNCTIONS(_CharaType,_AorW)\
void ChWin::DrawTexter##_AorW::Init(const HWND& _baseWindHandl){\
	if (*this)return;\
	if (ChPtr::NullCheck(_baseWindHandl))return;\
	SetWind(_baseWindHandl);\
	fontData = CreateFont##_AorW##(\
		16,\
		8,\
		0,\
		0,\
		2,\
		false,\
		false,\
		false,\
		SHIFTJIS_CHARSET,\
		OUT_DEFAULT_PRECIS,\
		CLIP_DEFAULT_PRECIS,\
		DEFAULT_PITCH,\
		FF_DONTCARE,\
		NULL);\
	SetInitFlg(true);}\
\
void ChWin::DrawTexter##_AorW::SetFontData(\
	const long& _fWidth,\
	const long& _fHeight,\
	const long& _fSize,\
	const bool& _ulFlg){\
	DeleteObject(fontData);\
	fontData = CreateFont##_AorW##(\
		_fHeight,\
		_fWidth,\
		0,\
		0,\
		_fSize,\
		false,\
		_ulFlg,\
		false,\
		SHIFTJIS_CHARSET,\
		OUT_DEFAULT_PRECIS,\
		CLIP_DEFAULT_PRECIS,\
		DEFAULT_PITCH,\
		FF_DONTCARE,\
		NULL);}\
\
void ChWin::DrawTexter##_AorW::Draw(\
	const _CharaType##* _drawText,\
	const int _drawTextLength,\
	const long& _x,\
	const long& _y){\
	HDC tmpDC;\
	tmpDC = GetDC(hOwn);\
	Draw(tmpDC, _drawText, _drawTextLength, _x, _y);\
	DeleteDC(tmpDC);}\
\
void ChWin::DrawTexter##_AorW::Draw(\
	HDC _hdc,\
	const _CharaType##* _drawText,\
	const int _drawTextLength,\
	const long& _x,\
	const long& _y){\
	SelectObject(_hdc, fontData);\
	SetTextColor(_hdc, RGB(fontColor.r, fontColor.g, fontColor.b));\
	if (backColor.a <= 0)\
		SetBkMode(_hdc, TRANSPARENT);\
	else\
		SetBkColor(_hdc, RGB(backColor.r, backColor.g, backColor.b));\
	TextOut##_AorW##(_hdc, _x, _y, _drawText, _drawTextLength);}
#endif

///////////////////////////////////////////////////////////////////////////////////////
//DrawTexterƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexterBase::Release()
{
	if (!*this)return;

	DeleteObject(fontData);

	SetInitFlg(false);
}

CH_WIN_DRAW_TEXTER_FUNCTIONS(char, A);

CH_WIN_DRAW_TEXTER_FUNCTIONS(wchar_t, W);
