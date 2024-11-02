#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../PackData/ChPoint.h"
#include"ChWindObject.h"
#include"ChWindStyle.h"


using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////
//WindowObject Method
///////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ChWin::BaseWndProc(
	HWND _hWnd,
	UINT _uMsg,
	WPARAM _wParam,
	LPARAM _lParam,
	LONG_PTR(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int),
	LRESULT(WINAPI* DefWindowProcFunction)(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM))
{
	ChWin::WindProcedure* base = ((ChWin::WindProcedure*)GetWindowLongPtrFunction(_hWnd, GWLP_USERDATA));

	if (ChPtr::NotNullCheck(base))
	{
		return base->UpdateProcedure(_hWnd,_uMsg,_wParam,_lParam, GetWindowLongPtrFunction);
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

	return DefWindowProcFunction(_hWnd, _uMsg, _wParam, _lParam);
}

void WindObjectBase::Init(HWND _hWnd, const int _nShowCmd)
{
	if (ChPtr::NullCheck(_hWnd))return;
	Release();
	hWnd = _hWnd;
	CreateEnd(_nShowCmd);
}

void WindObjectBase::SetWindPos(const unsigned int _x, const unsigned int _y, const unsigned int _flgs)
{
	if (!IsInit())return;
	SetWindowPos(hWnd, HWND_TOP, _x, _y, 0, 0, _flgs);
}

void WindObjectBase::SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs)
{
	if (!IsInit())return;
	SetWindowPos(hWnd, HWND_TOP, 0, 0, _w, _h, _flgs);
}

void WindObjectBase::SetWindRect(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h, const unsigned int _flgs)
{
	if (!IsInit())return;
	SetWindowPos(hWnd, HWND_TOP, _x, _y, _w, _h, _flgs);
}

const ChPOINT WindObjectBase::GetWindSize()const
{
	ChPOINT out;
	if (!*this)return out;
	RECT rect;
	GetWindowRect(hWnd, &rect);

	out.w = rect.right - rect.left;
	out.h = rect.bottom - rect.top;

	return out;
}

const ChPOINT WindObjectBase::GetWindPos()const
{
	ChPOINT out;
	if (!*this)return out;
	RECT rect;
	GetWindowRect(hWnd, &rect);

	out.x = rect.left;
	out.y = rect.top;

	return out;
}

HDC WindObjectBase::DrawStart()
{
	return GetDC(hWnd);
}

void WindObjectBase::DrawEnd(HDC _dc)
{
	ReleaseDC(hWnd, _dc);
}

bool WindObjectBase::IsCursorPosOnWindow()
{
	auto size = GetWindSize();

	POINT cPos;
	GetCursorPos(&cPos);
	ScreenToClient(hWnd, &cPos);

	if (0 <= cPos.x && size.w > cPos.x && 0 <= cPos.y && size.h > cPos.y) { return true; }

	return false;
}

void ChWin::WindProcedure::Init()
{
	value->wndProc[WM_DESTROY] = [&](
		HWND _hWnd,
		UINT _uMsg,
		WPARAM _wParam,
		LPARAM _lParam)->LRESULT
		{
			PostQuitMessage(0);
			return 0;
		};
}

LRESULT ChWin::WindProcedure::UpdateProcedure(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam, LONG_PTR(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int))
{

	auto it = value->wndProc.find(_uMsg);
	if (it != (value->wndProc).end())
	{
		LRESULT res;
		res = (it)->second(_hWnd, _uMsg, _wParam, _lParam);
		if (_uMsg != WM_COMMAND && _uMsg != WM_SYSCOMMAND)return res;
	}

	if (_uMsg != WM_COMMAND && _uMsg != WM_SYSCOMMAND)return DefaultWindProc(_hWnd, _uMsg, _wParam, _lParam);

	if (_lParam <= 0)
	{
		auto param = LOWORD(_wParam);

		auto it = value->wndProc.find(param);
		if (it != (value->wndProc).end())
		{
			(it)->second(_hWnd, _uMsg, _wParam, _lParam);
			return 0;
		}

	}
	else
	{
		auto child = ((ChWin::WindProcedure*)GetWindowLongPtrFunction((HWND)LOWORD(_wParam), GWLP_USERDATA));

		if (ChPtr::NotNullCheck(child))
		{
			if (!child->value->childWindProc.empty())
			{
				auto cit = child->value->childWindProc.find(HIWORD(_wParam));
				if (cit != (child->value->childWindProc).end())
				{
					(cit)->second((HWND)LOWORD(_wParam), HIWORD(_wParam));
				}
			}
			child->DefaultWindProc(_hWnd, _uMsg, _wParam, _lParam);

			return 0;
		}
	}

	return DefaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
}

void ChWin::WindProcedure::CRTInit()
{
	value = new WindProcedureCRT();
}

void ChWin::WindProcedure::CRTRelease()
{
	delete value;
}

LRESULT ChWin::WindProcedure::DefaultWindProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	return value->defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
}

void ChWin::WindObjectBase::CreateEnd(const int _nCmdShow)
{
	windProcedures = new WindProcedure();
	windProcedures->Init();

	SetInitFlg(true);
	SetWindID(reinterpret_cast<LONG_PTR>(hWnd));

	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);
}

CH_WIND_OBJECT_INHERITANCE_FUNCTIONS(A, char);

CH_WIND_OBJECT_INHERITANCE_FUNCTIONS(W, wchar_t);

//WindowObjectCreate Method//

void WindCreater::SetWindStyle(const WindStyle* _style)
{
	style = _style->GetStyle();
}

void WindCreater::SetInitPosition(const ChINTPOINT& _pos)
{
	SetInitPosition(_pos.x, _pos.y);
}

void WindCreater::SetInitPosition(const int _x, const int _y)
{
	pos.x = _x >= 0 ? _x : _x * -1;
	pos.y = _y >= 0 ? _y : _y * -1;
}

void WindCreater::SetInitSize(const ChINTPOINT& _size)
{
	SetInitSize(_size.w, _size.h);
}

void WindCreater::SetInitSize(const int _w, const int _h)
{
	size.w = _w >= 0 ? _w : _w * -1;
	size.y = _h >= 0 ? _h : _h * -1;
}
