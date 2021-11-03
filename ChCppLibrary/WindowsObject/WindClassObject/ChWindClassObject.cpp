#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../WindObject/ChWindObject.h"
#include"ChWindClassObject.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////

std::map<HWND, WindClassObject*>& WindClassObject::WindManager()
{
	static std::map<HWND, WindClassObject*> mgr;

	return mgr;
}


///////////////////////////////////////////////////////////////////////////////////

WindClassObject* WindClassObject::GetWindObject(const HWND* _hWnd)
{
	auto& mgr = WindManager();

	if (mgr.find(*_hWnd) == mgr.end())return nullptr;

	return mgr[*_hWnd];
}

///////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ChWin::WndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{

	auto base = WindClassObject::GetWindObject(&_hWnd);

	if (base)
	{
		base->WndProc(_hWnd, _uMsg, _wParam, _lParam);
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
}

///////////////////////////////////////////////////////////////////////////////////

void WindClassObject::Init()
{
	Release();

	cls.style = CS_HREDRAW | CS_VREDRAW;
	cls.lpfnWndProc = ChWin::WndProc;
	cls.cbClsExtra = 0;
	cls.cbWndExtra = 0;
	cls.hInstance = 0;
	cls.hIcon = NULL;
	cls.hCursor = LoadCursor(NULL, IDC_ARROW);
	cls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	cls.lpszMenuName = "\0";
	cls.lpszClassName = "\0";
}

///////////////////////////////////////////////////////////////////////////////////

void WindClassObject::Init(const WNDCLASS& _cls)
{
	cls = _cls;
}

///////////////////////////////////////////////////////////////////////////////////

void WindClassObject::Init(const HINSTANCE _hInst)
{
	Init();

	cls.hInstance = _hInst;
}

///////////////////////////////////////////////////////////////////////////////////

void WindClassObject::Release()
{
	ChStd::MZero(&cls);
}
