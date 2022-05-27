#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

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

	auto base = ((ChWin::WindObject*)GetWindowLongPtrA(_hWnd, GWLP_USERDATA));

	if (base)
	{
		if (base->IsInit() && !base->wndProc.empty())
		{
			auto it = base->wndProc.find(_uMsg);
			if (it != (base->wndProc).end())
			{
				return (it)->second(_hWnd, _uMsg, _wParam, _lParam);
			}
			else if (_uMsg == WM_COMMAND)
			{

				auto child = ((ChWin::WindObject*)GetWindowLongPtrA((HWND)_lParam, GWLP_USERDATA));

				if (child)
				{
					if (child->IsInit() && !child->wndProc.empty())
					{
						auto cit = child->childWindProc.find(HIWORD(_wParam));
						if (cit != (child->childWindProc).end())
						{
							(cit)->second((HWND)_lParam, HIWORD(_wParam));
						}
					}
				}

				return 0;
			}
			return base->defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
		}
	}

	if (ChPtr::NullCheck(base))
	{
		switch (_uMsg)
		{
		case WM_DESTROY:

			PostQuitMessage(0);
			return 0;

		default:
			break;
		}
	}

	return DefWindowProcA(_hWnd, _uMsg, _wParam, _lParam);

}

LRESULT CALLBACK ChWin::WndProcW(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{

	auto base = ((ChWin::WindObject*)GetWindowLongPtrW(_hWnd, GWLP_USERDATA));

	if (base)
	{
		if (base->IsInit() && !base->wndProc.empty())
		{
			auto it = base->wndProc.find(_uMsg);
			if (it != (base->wndProc).end())
			{
				return (it)->second(_hWnd, _uMsg, _wParam, _lParam);
			}
			else if (_uMsg == WM_COMMAND)
			{

				auto child = ((ChWin::WindObject*)GetWindowLongPtrW((HWND)_lParam, GWLP_USERDATA));

				if (child)
				{
					if (child->IsInit() && !child->wndProc.empty())
					{
						auto cit = child->childWindProc.find(HIWORD(_wParam));
						if (cit != (child->childWindProc).end())
						{
							(cit)->second((HWND)_lParam, HIWORD(_wParam));
						}
					}
				}
				child->defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);

				return 0;
			}
			return base->defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
		}
	}

	if (ChPtr::NullCheck(base))
	{
		switch (_uMsg)
		{
		case WM_DESTROY:

			PostQuitMessage(0);
			return 0;

		default:
			break;
		}
	}

	return DefWindowProcW(_hWnd, _uMsg, _wParam, _lParam);

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

void WindClassObjectA::SetMenuName(const std::string& _name)
{
	cls.lpszMenuName = _name.c_str();
}

ChStd::Bool WindClassObjectA::IsSystemRegistClassName(const std::string& _className)
{
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

	switch (_className.length())
	{
	case 4:
		for (char i = 3; i >= 0; i--)
		{
			if (_className[i] == systemRegistClassName[2][i])continue;
			return false;
		}
		return true;
	case 6:

		if (_className[5] == systemRegistClassName[0][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (_className[i] == systemRegistClassName[0][i])continue;
				return false;
			}
			return true;
		}
		else if (_className[5] == systemRegistClassName[8][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (_className[i] == systemRegistClassName[8][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 7:

		for (char i = 6; i >= 0; i--)
		{
			if (_className[i] == systemRegistClassName[3][i])continue;
			return false;
		}

		return true;

	case 8:
		if (_className[7] == systemRegistClassName[1][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (_className[i] == systemRegistClassName[1][i])continue;
				return false;
			}
			return true;
		}
		else if (_className[7] == systemRegistClassName[5][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (_className[i] == systemRegistClassName[5][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 9:
		if (_className[8] == systemRegistClassName[4][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (_className[i] == systemRegistClassName[4][i])continue;
				return false;
			}
			return true;
		}
		else if (_className[8] == systemRegistClassName[7][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (_className[i] == systemRegistClassName[7][i])continue;
				return false;
			}
			return true;
		}

		return false;
	case 15:

		for (char i = 14; i >= 0; i--)
		{
			if (_className[i] == systemRegistClassName[6][i])continue;
			return false;
		}

		return true;

	default:
		return false;
	}

	return false;
}

void WindClassObjectA::RegistClass(const std::string& _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	if (_className == "")return;
	className = _className;
	if (IsSystemRegistClassName(_className))return;

	cls.lpszClassName = _className.c_str();
	RegisterClassA(&cls);
	
	SetInitFlg(true);
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

void WindClassObjectW::SetMenuName(const std::wstring& _name)
{
	cls.lpszMenuName = _name.c_str();
}

ChStd::Bool WindClassObjectW::IsSystemRegistClassName(const std::wstring& _className)
{
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

	switch (_className.length())
	{
	case 4:
		for (char i = 3; i >= 0; i--)
		{
			if (_className[i] != systemRegistClassName[2][i])continue;
			return false;
		}
		return true;
	case 6:

		if (_className[5] != systemRegistClassName[0][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (_className[i] != systemRegistClassName[0][i])continue;
				return false;
			}
			return true;
		}
		else if (_className[5] != systemRegistClassName[8][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (_className[i] != systemRegistClassName[8][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 7:

		for (char i = 6; i >= 0; i--)
		{
			if (_className[i] != systemRegistClassName[3][i])continue;
			return false;
		}

		return true;

	case 8:
		if (_className[7] != systemRegistClassName[1][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (_className[i] != systemRegistClassName[1][i])continue;
				return false;
			}
			return true;
		}
		else if (_className[7] != systemRegistClassName[5][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (_className[i] != systemRegistClassName[5][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 9:
		if (_className[8] != systemRegistClassName[4][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (_className[i] != systemRegistClassName[4][i])continue;
				return false;
			}
			return true;
		}
		else if (_className[8] != systemRegistClassName[7][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (_className[i] != systemRegistClassName[7][i])continue;
				return false;
			}
			return true;
		}

		return false;
	case 15:

		for (char i = 14; i >= 0; i--)
		{
			if (_className[i] != systemRegistClassName[6][i])continue;
			return false;
		}

		return true;

	default:
		return false;
	}

	return false;
}

void WindClassObjectW::RegistClass(const std::wstring& _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	if (_className == L"")return;
	className = _className;
	if (IsSystemRegistClassName(_className))return;

	cls.lpszClassName = _className.c_str();
	RegisterClassW(&cls);

	SetInitFlg(true);
}