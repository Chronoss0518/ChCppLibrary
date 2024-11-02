#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"
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
		GetWindowLongPtrA,
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
		GetWindowLongPtrW,
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
	if (ChPtr::NullCheck(_style))return;
	SetStyle(_style->GetStyle());
}

void WindClassObjectA::SetIcon(const HICON _icon)
{
	if (ChPtr::NullCheck(_icon))return;
	cls.hIcon = _icon;
}

void WindClassObjectA::SetCursol(const HCURSOR _cursor)
{
	if (ChPtr::NullCheck(_cursor))return;
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
	if (ChPtr::NullCheck(_brush))return;
	cls.hbrBackground = _brush;
}

void WindClassObjectA::SetInstance(const HINSTANCE _hInst)
{
	cls.hInstance = _hInst;
}

void WindClassObjectA::SetWindProcedure(WNDPROC _windProc)
{
	if (ChPtr::NullCheck(_windProc))return;
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
	if (ChPtr::NullCheck(_style))return;
	SetStyle(_style->GetStyle());
}

void WindClassObjectW::SetIcon(const HICON _icon)
{
	if (ChPtr::NullCheck(_icon))return;
	cls.hIcon = _icon;
}

void WindClassObjectW::SetCursol(const HCURSOR _cursor)
{
	if (ChPtr::NullCheck(_cursor))return;
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
	if (ChPtr::NullCheck(_brush))return;
	cls.hbrBackground = _brush;
}

void WindClassObjectW::SetInstance(const HINSTANCE _hInst)
{
	cls.hInstance = _hInst;
}

void WindClassObjectW::SetWindProcedure(WNDPROC _windProc)
{
	if (ChPtr::NullCheck(_windProc))return;
	cls.lpfnWndProc = _windProc;
}

void WindClassObjectW::SetMenuName(const wchar_t* _name)
{
	cls.lpszMenuName = _name;
}

const char* ChWin::WindClassObjectA::GetWindClassName() { return className.c_str(); }

bool ChWin::WindClassObjectA::IsSystemRegistClassName(const char* _className)
{
	std::string tmpClassName = _className;
	std::string systemRegistClassName[] =
	{
		"BUTTON",
		"COMBOBOX",
		"EDIT",
		"LISTBOX",
		"MDICLIENT",
		"RichEdit",
		"RICHEDIT_CLASS",
		"SCROLLBAR",
		"STATIC" };

	switch (tmpClassName.length())
	{
	case 4:
		for (char i = 3; i >= 0; i--)
		{
			if (tmpClassName[i] == systemRegistClassName[2][i])continue;
			return false;
		}
		return true;
	case 6:

		if (tmpClassName[5] == systemRegistClassName[0][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[0][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[5] == systemRegistClassName[8][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[8][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 7:

		for (char i = 6; i >= 0; i--)
		{
			if (tmpClassName[i] == systemRegistClassName[3][i])continue;
			return false;
		}

		return true;

	case 8:
		if (tmpClassName[7] == systemRegistClassName[1][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[1][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[7] == systemRegistClassName[5][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[5][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 9:
		if (tmpClassName[8] == systemRegistClassName[4][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[4][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[8] == systemRegistClassName[7][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[7][i])continue;
				return false;
			}
			return true;
		}

		return false;
	case 15:

		for (char i = 14; i >= 0; i--)
		{
			if (tmpClassName[i] == systemRegistClassName[6][i])continue;
			return false;
		}

		return true;

	default:
		return false;
	}

	return false;
}

void ChWin::WindClassObjectA::RegistClass(const char* _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	std::string tmpClassName = _className;
	if (tmpClassName == "")return;
	className = tmpClassName;
	if (IsSystemRegistClassName(className.c_str()))return;

	cls.lpszClassName = className.c_str();
	RegisterClassA(&cls);

	SetInitFlg(true);
}

const wchar_t* ChWin::WindClassObjectW::GetWindClassName() { return className.c_str(); }

bool ChWin::WindClassObjectW::IsSystemRegistClassName(const wchar_t* _className)
{
	std::wstring tmpClassName = _className;
	std::wstring systemRegistClassName[] =
	{
		L"BUTTON",
		L"COMBOBOX",
		L"EDIT",
		L"LISTBOX",
		L"MDICLIENT",
		L"RichEdit",
		L"RICHEDIT_CLASS",
		L"SCROLLBAR",
		L"STATIC" };

	switch (tmpClassName.length())
	{
	case 4:
		for (char i = 3; i >= 0; i--)
		{
			if (tmpClassName[i] != systemRegistClassName[2][i])continue;
			return false;
		}
		return true;
	case 6:

		if (tmpClassName[5] != systemRegistClassName[0][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[0][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[5] != systemRegistClassName[8][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[8][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 7:

		for (char i = 6; i >= 0; i--)
		{
			if (tmpClassName[i] != systemRegistClassName[3][i])continue;
			return false;
		}

		return true;

	case 8:
		if (tmpClassName[7] != systemRegistClassName[1][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[1][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[7] != systemRegistClassName[5][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[5][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 9:
		if (tmpClassName[8] != systemRegistClassName[4][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[4][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[8] != systemRegistClassName[7][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[7][i])continue;
				return false;
			}
			return true;
		}

		return false;
	case 15:

		for (char i = 14; i >= 0; i--)
		{
			if (tmpClassName[i] != systemRegistClassName[6][i])continue;
			return false;
		}

		return true;

	default:
		return false;
	}

	return false;
}

void ChWin::WindClassObjectW::RegistClass(const wchar_t* _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	std::wstring tmpClassName = _className;
	if (tmpClassName == L"")return;
	className = tmpClassName;
	if (IsSystemRegistClassName(className.c_str()))return;

	cls.lpszClassName = className.c_str();
	RegisterClassW(&cls);

	SetInitFlg(true);
}