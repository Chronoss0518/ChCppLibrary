#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"ChWindObject.h"
#include"ChWindStyle.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////
//WindowObject Method
///////////////////////////////////////////////////////////////////////////////////

static WindStyle style;


WindObject& WindObject::operator = (const WindObject& _obj)
{
	Set(_obj);
	return *this;
}

bool WindObject::operator == (const WindObject& _obj)const
{
	return this == &_obj;
}

bool WindObject::operator != (const WindObject& _obj)const
{

	return this != &_obj;
}

WindObject::WindObject(const WindObject& _obj)
{
	Set(_obj);
}

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

void WindObject::Release()
{
	if (IsInit())
	{
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		SetInitFlg(false);
	}

}

void WindObject::CreateEnd(const int _nCmdShow)
{
	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)this);

	SetInitFlg(true);

}

void WindObject::Set(const WindObject& _obj)
{
	wndProc = _obj.wndProc;
	hWnd = _obj.hWnd;
	msg = _obj.msg;
	SetInitFlg(static_cast<bool>(_obj));
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

inline const ChMath::Vector2Base<unsigned int> WindObject::GetWindSize()const
{
	ChMath::Vector2Base<unsigned int> out;
	if (!*this)return out;

	RECT rect;
	GetClientRect(hWnd, &rect);

	out.w = rect.left;
	out.h = rect.top;

	return out;
}

inline const ChMath::Vector2Base<unsigned int> WindObject::GetWindPos()const
{
	ChMath::Vector2Base<unsigned int> out;
	if (!*this)return out;
	RECT rect;
	GetClientRect(hWnd, &rect);

	out.w = rect.right - rect.left;
	out.h = rect.bottom - rect.top;

	return out;
}

const HINSTANCE WindObject::GetInstance()const
{
	return (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
}

LPARAM WindObject::Send(const unsigned int _msg, WPARAM _wParam, LPARAM _lParam)
{
	LPARAM out = _lParam;
	if (!*this)return out;
	WPARAM wParam = _wParam;
	SendMessage(hWnd, _msg, wParam, out);
	return out;
}

ChStd::Bool WindObject::Update()
{
	if (!IsInit())return false;

	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) <= 0)return true;

	if ((GetMessage(&msg, NULL, 0, 0)) <= 0)return false;
	TranslateMessage(&msg);
	DispatchMessage(&msg);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////
//WindowObjectCreate Method
///////////////////////////////////////////////////////////////////////////////////

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

ChStd::Bool WindCreater::Create(WindObject* _out,const std::string& _appName, const std::string& _windClassName, const int _nShowCmd)
{
	if (ChPtr::NullCheck(_out))return false;

	_out->Init();

	_out->hWnd = CreateWindowA(
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

	return true;
}

ChStd::Bool WindCreater::Create(WindObject* _out,const std::wstring& _appName, const std::wstring& _windClassName, const int _nShowCmd)
{

	if (ChPtr::NullCheck(_out))return false;

	_out->Init();

	_out->hWnd = CreateWindowW(
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

	return true;
}