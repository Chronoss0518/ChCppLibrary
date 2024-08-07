#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#define NULL_CHECK(val) (val == NULL || val == nullptr)

#include"../PackData/ChPoint.h"
#include"../WindObject/ChWindObject.h"
#include"ChWindClassObject.h"
#include"ChWindClassStyle.h"

using namespace ChWin;

LRESULT CALLBACK ChWin::WndProcA(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return ChWin::BaseWndProc(
		_hWnd,
		_uMsg,
		_wParam,
		_lParam,
		GetWindowLongA,
		DefWindowProcA
	);
}

LRESULT CALLBACK ChWin::WndProcW(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return ChWin::BaseWndProc(
		_hWnd,
		_uMsg,
		_wParam,
		_lParam,
		GetWindowLongW,
		DefWindowProcW
	);
}

//WindClassObjectA Method//

void WindClassObjectA::Init()
{
	Release();

	WindClassStyle cstyle;
	cstyle.AddHReDraw();
	cstyle.AddHReDraw();

	ChStd::MZero(&cls);

	cls.style = cstyle.GetStyle();
	cls.lpfnWndProc = ChWin::WndProcA;
	cls.cbClsExtra = 0;
	cls.cbWndExtra = 0;
	cls.hInstance = 0;
	cls.hIcon = NULL;
	cls.hCursor = LoadCursorA(NULL, MAKEINTRESOURCEA(32512));
	cls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	cls.lpszMenuName = "\0";
	cls.lpszClassName = "\0";
}

void WindClassObjectA::Init(const WNDCLASSA& _cls)
{
	cls = _cls;
}

void WindClassObjectA::Release()
{

	if (!IsInit())return;

	UnregisterClassA(cls.lpszClassName, cls.hInstance);

	ChStd::MZero(&cls);

	SetInitFlg(false);
}

void WindClassObjectA::SetStyle(const unsigned int _style)
{
	cls.style = _style;
}

void WindClassObjectA::SetStyle(const WindClassStyle* _style)
{
	if (NULL_CHECK(_style))return;
	SetStyle(_style->GetStyle());
}

void WindClassObjectA::SetIcon(const HICON _icon)
{
	if (NULL_CHECK(_icon))return;
	cls.hIcon = _icon;
}

void WindClassObjectA::SetCursol(const HCURSOR _cursor)
{
	if (NULL_CHECK(_cursor))return;
	cls.hCursor = _cursor;
}

//ウィンドウクラス構造の後の追加バイト数//
void WindClassObjectA::SetClsExtra(const int _byteNum)
{
	if (_byteNum < 0)return;
	cls.cbClsExtra = _byteNum;
}

//ウィンドウインスタンスの後の追加バイト数//
void WindClassObjectA::SetWndExtra(const int _byteNum)
{
	if (_byteNum < 0)return;
	cls.cbWndExtra = _byteNum;
}

void WindClassObjectA::SetBackgroundColor(const HBRUSH _brush)
{
	if (NULL_CHECK(_brush))return;
	cls.hbrBackground = _brush;
}

void WindClassObjectA::SetInstance(const HINSTANCE _hInst)
{
	cls.hInstance = _hInst;
}

void WindClassObjectA::SetWindProcedure(WNDPROC _windProc)
{
	if (NULL_CHECK(_windProc))return;
	cls.lpfnWndProc = _windProc;
}

void WindClassObjectA::SetMenuName(const char* _name)
{
	cls.lpszMenuName = _name;
}

//WindClassObjectW Method//

void WindClassObjectW::Init()
{
	Release();

	WindClassStyle cstyle;
	cstyle.AddHReDraw();
	cstyle.AddHReDraw();

	ChStd::MZero(&cls);

	cls.style = cstyle.GetStyle();
	cls.lpfnWndProc = ChWin::WndProcW;
	cls.cbClsExtra = 0;
	cls.cbWndExtra = 0;
	cls.hInstance = 0;
	cls.hIcon = NULL;
	cls.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
	cls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	cls.lpszMenuName = L"\0";
	cls.lpszClassName = L"\0";
}

void WindClassObjectW::Init(const WNDCLASSW& _cls)
{
	cls = _cls;
}

void WindClassObjectW::Release()
{

	if (!IsInit())return;

	UnregisterClassW(cls.lpszClassName, cls.hInstance);

	ChStd::MZero(&cls);

	SetInitFlg(false);
}

void WindClassObjectW::SetStyle(const unsigned int _style)
{
	cls.style = _style;
}

void WindClassObjectW::SetStyle(const WindClassStyle* _style)
{
	if (NULL_CHECK(_style))return;
	SetStyle(_style->GetStyle());
}

void WindClassObjectW::SetIcon(const HICON _icon)
{
	if (NULL_CHECK(_icon))return;
	cls.hIcon = _icon;
}

void WindClassObjectW::SetCursol(const HCURSOR _cursor)
{
	if (NULL_CHECK(_cursor))return;
	cls.hCursor = _cursor;
}

//ウィンドウクラス構造の後の追加バイト数//
void WindClassObjectW::SetClsExtra(const int _byteNum)
{
	if (_byteNum < 0)return;
	cls.cbClsExtra = _byteNum;
}

//ウィンドウインスタンスの後の追加バイト数//
void WindClassObjectW::SetWndExtra(const int _byteNum)
{
	if (_byteNum < 0)return;
	cls.cbWndExtra = _byteNum;
}

void WindClassObjectW::SetBackgroundColor(const HBRUSH _brush)
{
	if (NULL_CHECK(_brush))return;
	cls.hbrBackground = _brush;
}

void WindClassObjectW::SetInstance(const HINSTANCE _hInst)
{
	cls.hInstance = _hInst;
}

void WindClassObjectW::SetWindProcedure(WNDPROC _windProc)
{
	if (NULL_CHECK(_windProc))return;
	cls.lpfnWndProc = _windProc;
}

void WindClassObjectW::SetMenuName(const wchar_t* _name)
{
	cls.lpszMenuName = _name;
}
