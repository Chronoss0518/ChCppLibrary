#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"ChWindObject.h"
#include"ChWindStyle.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////
//WindowObject Method
///////////////////////////////////////////////////////////////////////////////////

static WindStyle style;

void WindObject::Init()
{

	wndProc[WM_DESTROY] = [&](HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam)->LRESULT
	{
		PostQuitMessage(0);
		return 0;
	};
}

void WindObject::Init(HWND _hWnd, const int _nShowCmd)
{
	if (ChPtr::NullCheck(_hWnd))return;
	Release();
	hWnd = _hWnd;
	CreateEnd(_nShowCmd);
}

void WindObject::Release()
{
	if (!IsInit())return;

	Send(WM_CLOSE, 0, 0);
	SetInitFlg(false);


}

void WindObject::CreateEnd(const int _nCmdShow)
{
	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);

	SetInitFlg(true);

}

void WindObject::SetWindPos(const unsigned int _x, const unsigned int _y, const unsigned int _flgs)
{
	if (!IsInit())return;

	SetWindowPos(hWnd, HWND_TOP, _x, _y, 0, 0, _flgs);
}

void WindObject::SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs)
{
	if (!IsInit())return;

	SetWindowPos(hWnd, HWND_TOP, 0, 0, _w, _h, _flgs);
}

void WindObject::SetWindRect(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h, const unsigned int _flgs)
{
	if (!IsInit())return;

	SetWindowPos(hWnd, HWND_TOP, _x, _y, _w, _h, _flgs);
}

const ChMath::Vector2Base<unsigned int> WindObject::GetWindSize()const
{
	ChMath::Vector2Base<unsigned int> out;
	if (!*this)return out;

	RECT rect;
	GetClientRect(hWnd, &rect);

	out.w = rect.right - rect.left;
	out.h = rect.bottom - rect.top;

	return out;
}

const ChMath::Vector2Base<unsigned int> WindObject::GetWindPos()const
{
	ChMath::Vector2Base<unsigned int> out;
	if (!*this)return out;
	RECT rect;
	GetClientRect(hWnd, &rect);


	out.w = rect.left;
	out.h = rect.top;

	return out;
}

const HINSTANCE WindObject::GetInstanceA()const
{
	return (HINSTANCE)GetWindowLongA(hWnd, GWL_HINSTANCE);
}

const HINSTANCE WindObject::GetInstanceW()const
{
	return (HINSTANCE)GetWindowLongW(hWnd, GWL_HINSTANCE);
}

LPARAM WindObject::SendA(const unsigned int _msg, WPARAM _wParam, LPARAM _lParam)
{
	LPARAM out = _lParam;
	if (!*this)return out;
	WPARAM wParam = _wParam;
	SendMessageA(hWnd, _msg, wParam, out);
	return out;
}

LPARAM WindObject::SendW(const unsigned int _msg, WPARAM _wParam, LPARAM _lParam)
{
	LPARAM out = _lParam;
	if (!*this)return out;
	WPARAM wParam = _wParam;
	SendMessageW(hWnd, _msg, wParam, out);
	return out;
}

ChStd::Bool WindObject::UpdateA()
{
	UpdateWindow(hWnd);

	if (!IsInit())return false;

	if (!PeekMessageA(&msg, hWnd, 0, 0, PM_NOREMOVE))
	{
		if(ChPtr::NullCheck(msg.hwnd))return false;
		return true;
	}
	

	if ((GetMessageA(&msg, NULL, 0, 0)) <= 0)return false;
	TranslateMessage(&msg);
	DispatchMessageA(&msg);

	return true;
}

ChStd::Bool WindObject::UpdateW()
{

	UpdateWindow(hWnd);
	
	if (!IsInit())return false;

	if (!PeekMessageW(&msg, NULL, 0, 0, PM_NOREMOVE))return true;

	if ((GetMessageW(&msg, NULL, 0, 0)) <= 0)return false;
	TranslateMessage(&msg);
	DispatchMessageW(&msg);

	return true;
}

//WindowObjectCreate Method//

void WindCreater::SetWindStyle(const WindStyle* _style)
{
	style = _style->GetStyle();
}

void WindCreater::SetInitPosition(const ChMath::Vector2Base<int>& _pos)
{
	SetInitPosition(_pos.x, _pos.y);
}

void WindCreater::SetInitPosition(const int _x, const int _y)
{
	pos.x = _x >= 0 ? _x : _x * -1;
	pos.y = _y >= 0 ? _y : _y * -1;
}

void WindCreater::SetInitSize(const ChMath::Vector2Base<int>& _size)
{
	SetInitSize(_size.w, _size.h);
}

void WindCreater::SetInitSize(const int _w, const int _h)
{

	size.w = _w >= 0 ? _w : _w * -1;
	size.y = _h >= 0 ? _h : _h * -1;
}

ChStd::Bool WindCreater::Create(WindObject* _out, const std::string& _appName, const std::string& _windClassName, const int _nShowCmd)const
{
	if (ChPtr::NullCheck(_out))return false;

	_out->Init();

	_out->hWnd = CreateWindowExA(
		exStyle,
		_windClassName.c_str(),
		_appName.c_str(),
		style,
		pos.x, pos.y,
		size.w, size.h,
		parent,
		hMenu,
		hInst,
		param);

	if (ChPtr::NullCheck(_out->hWnd))return false;

	_out->CreateEnd(_nShowCmd);

	SetWindowLongPtrA(_out->hWnd, GWLP_USERDATA, reinterpret_cast<long>(_out));

	return true;
}

ChStd::Bool WindCreater::Create(WindObject* _out, const std::wstring& _appName, const std::wstring& _windClassName, const int _nShowCmd)const
{

	if (ChPtr::NullCheck(_out))return false;

	_out->Init();

	_out->hWnd = CreateWindowExW(
		exStyle,
		_windClassName.c_str(),
		_appName.c_str(),
		style,
		pos.x, pos.y,
		size.w, size.h,
		parent,
		hMenu,
		hInst,
		param);

	if (ChPtr::NullCheck(_out->hWnd))return false;

	_out->CreateEnd(_nShowCmd);

	SetWindowLongPtrW(_out->hWnd, GWLP_USERDATA, reinterpret_cast<long>(_out));

	return true;
}