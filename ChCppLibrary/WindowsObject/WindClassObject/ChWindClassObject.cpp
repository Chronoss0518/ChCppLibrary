#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../WindObject/ChWindObject.h"
#include"ChWindClassObject.h"
#include"ChWindClassStyle.h"

using namespace ChWin;


LRESULT CALLBACK ChWin::WndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{

	auto base = ((ChWin::WindObject*)GetWindowLongPtr(_hWnd, GWLP_USERDATA));

	try
	{
		if (base)
		{
			if ((base->wndProc).find(_uMsg) != (base->wndProc).end())
			{
				return (base->wndProc)[_uMsg](_hWnd, _uMsg, _wParam, _lParam);
			}
		}
	}
	catch (std::exception e)
	{

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

	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);

	/*


	auto base = ((ChWin::WindObject*)GetWindowLongPtr(_hWnd, GWLP_USERDATA));

	if (base)
	{
		if (base->wndProc.find(_uMsg) == base->wndProc.end())
		{
			return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
		}

		base->wndProc[_uMsg](_hWnd, _uMsg, _wParam, _lParam);
	}
	else
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
	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);

	*/
}

void WindClassObject::Init()
{
	Release();

	WindClassStyle cstyle;
	cstyle.AddHReDraw();
	cstyle.AddHReDraw();

	ChStd::MZero(&cls);

	cls.style = cstyle.GetStyle();
	cls.lpfnWndProc = ChWin::WndProc;
	cls.cbClsExtra = 0;
	cls.cbWndExtra = 0;
	cls.hInstance = 0;
	cls.hIcon = NULL;
	cls.hCursor = LoadCursor(NULL, IDC_ARROW);
	cls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//cls.lpszMenuName = "\0";
	//cls.lpszClassName = "\0";
}

void WindClassObject::Init(const WNDCLASS& _cls)
{
	cls = _cls;
}

void WindClassObject::Release()
{

	if (!IsInit())return;

	UnregisterClass(cls.lpszClassName, cls.hInstance);

	ChStd::MZero(&cls);

	SetInitFlg(false);
}

void WindClassObject::SetStyle(const unsigned int _style)
{
	cls.style = _style;
}

void WindClassObject::SetStyle(const WindClassStyle* _style)
{
	if (ChPtr::NullCheck(_style))return;
	SetStyle(_style->GetStyle());
}

void WindClassObject::SetIcon(const HICON _icon)
{
	if (ChPtr::NullCheck(_icon))return;
	cls.hIcon = _icon;
}

void WindClassObject::SetCursol(const HCURSOR _cursor)
{
	if (ChPtr::NullCheck(_cursor))return;
	cls.hCursor = _cursor;
}

//ウィンドウクラス構造の後の追加バイト数//
void WindClassObject::SetClsExtra(const int _byteNum)
{
	if (_byteNum < 0)return;
	cls.cbClsExtra = _byteNum;
}

//ウィンドウインスタンスの後の追加バイト数//
void WindClassObject::SetWndExtra(const int _byteNum)
{
	if (_byteNum < 0)return;
	cls.cbWndExtra = _byteNum;
}

void WindClassObject::SetBackgroundColor(const HBRUSH _brush)
{
	if (ChPtr::NullCheck(_brush))return;
	cls.hbrBackground = _brush;
}

void WindClassObject::SetInstance(const HINSTANCE _hInst)
{
	cls.hInstance = _hInst;
}

void WindClassObject::SetWindProcedure(WNDPROC _windProc)
{
	if (ChPtr::NullCheck(_windProc))return;
	cls.lpfnWndProc = _windProc;
}

void WindClassObject::RegistClass(const std::string& _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	if (_className == "")return;

	cls.lpszClassName = _className.c_str();
	RegisterClass(&cls);
	className = _className;

	SetInitFlg(true);
}