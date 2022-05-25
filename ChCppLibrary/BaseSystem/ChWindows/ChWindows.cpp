
#include<windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../ChBaseSystem/ChBaseSystem.h"
#include"ChWindows.h"
#include"../../WindowsObject/Mouse/ChWinMouse.h"

using namespace ChSystem;

ChStd::Bool BaseWndProcs(
	const HWND _hWnd
	, const UINT _uMsg
	, const WPARAM _wParam
	, const LPARAM _lParam);

///////////////////////////////////////////////////////////////////////////////////////
//ChWindowsÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void Windows::Init(
	const std::string& _appName
	, const std::string& _windClassName
	, const int _windWidth
	, const int _windHeight
	, const HINSTANCE _hInst
	, const int _nCmdShow)
{

	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);

	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(10, 10);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);

	creater.Create(&wndObject, _appName, _windClassName, _nCmdShow);

	inst = _hInst;

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);
}

void Windows::Init(
	const std::string& _appName,
	const std::string& _windClassName,
	const int _windWidth,
	const int _windHeight,
	const int _initWindPosX,
	const int _initWindPosY,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{

	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);

	creater.Create(&wndObject, _appName, _windClassName, _nCmdShow);

	inst = _hInst;

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

}

void Windows::Init(
	const ChWin::WindCreater& _creater,
	const std::string& _appName,
	const std::string& _windClassName,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{

	_creater.Create(&wndObject, _appName, _windClassName, _nCmdShow);

	inst = _hInst;

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);
}

void Windows::Init(
	const std::string& _appName,
	const std::string& _className,
	const unsigned long _dwStyle,
	const int _initWindPosX,
	const int _initWindPosY,
	const int _windWidth,
	const int _windHeight,
	HINSTANCE _hInst,
	const int _nCmdShow,
	const unsigned long _exStyle,
	HWND _parent,
	HMENU _hMenu,
	LPVOID _param)
{
	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);


	HWND hWnd = CreateWindowExA(
		_exStyle,
		_className.c_str(),
		_appName.c_str(),
		_dwStyle,
		pos.x,
		pos.y, 
		size.w,
		size.h,
		_parent,
		_hMenu ,
		_hInst,
		_param);

	wndObject.Init(hWnd,_nCmdShow);

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

	SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<long>(&wndObject));

}

void Windows::Init(
	const std::wstring& _appName
	, const std::wstring& _windClassName
	, const int _windWidth
	, const int _windHeight
	, const HINSTANCE _hInst
	, const int _nCmdShow)
{

	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);

	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(10, 10);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);

	creater.Create(&wndObject, _appName, _windClassName, _nCmdShow);

	inst = _hInst;

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

}

void Windows::Init(
	const std::wstring& _appName,
	const std::wstring& _windClassName,
	const int _windWidth,
	const int _windHeight,
	const int _initWindPosX,
	const int _initWindPosY,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{

	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);

	creater.Create(&wndObject, _appName, _windClassName, _nCmdShow);

	inst = _hInst;

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

}

void Windows::Init(
	const ChWin::WindCreater& _creater,
	const std::wstring& _appName,
	const std::wstring& _windClassName,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{

	_creater.Create(&wndObject, _appName, _windClassName, _nCmdShow);

	inst = _hInst;

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);
}

void Windows::Init(
	const std::wstring& _appName,
	const std::wstring& _className,
	const unsigned long _dwStyle,
	const int _initWindPosX,
	const int _initWindPosY,
	const int _windWidth,
	const int _windHeight,
	HINSTANCE _hInst,
	const int _nCmdShow,
	const unsigned long _exStyle,
	HWND _parent,
	HMENU _hMenu,
	LPVOID _param)
{
	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);


	HWND hWnd = CreateWindowExW(
		_exStyle,
		_className.c_str(),
		_appName.c_str(),
		_dwStyle,
		pos.x,
		pos.y,
		size.w,
		size.h,
		_parent,
		_hMenu,
		_hInst,
		_param);

	wndObject.Init(hWnd, _nCmdShow);

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

	SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<long>(&wndObject));

}

///////////////////////////////////////////////////////////////////////////////////

void Windows::Release()
{
	wndObject.Release();
	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPushKey(const int _Key)
{
	SetKeyCode();

	if (buttonList.GetBitFlg(_Key))
	{
		isNowPush.SetBitTrue(_Key);
		return true;
	}
	isNowPush.SetBitFalse(_Key);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPushKeyNoHold(const int _Key)
{
	SetKeyCode();

	if (buttonList.GetBitFlg(_Key))
	{
		if (!isNowPush.GetBitFlg(_Key))
		{
			isNowPush.SetBitTrue(_Key);
			return true;
		}
		return false;
	}
	isNowPush.SetBitFalse(_Key);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPause(const int _Key)
{
	SetKeyCode();

	ChStd::Bool tmpFlg;
	tmpFlg = IsPushKey(_Key);

	if (tmpFlg && nowKey)return pauseFlg;
	nowKey = false;

	if (!tmpFlg)return pauseFlg;

	pauseFlg = !pauseFlg;
	nowKey = true;

	return pauseFlg;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsUpdate()
{
	auto hWnd = wndObject.GethWnd();
	if (ChPtr::NullCheck(hWnd))return false;

	isKeyUpdate = false;
	
	{

		RECT tmp;
		GetClientRect(hWnd, &tmp);

		windSize.w = tmp.right - tmp.left;
		windSize.h = tmp.bottom - tmp.top;

	}

	return wndObject.Update();
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::SetKeyCode()
{
	if (!system->IsUseSystemButtons())return;
	if (isKeyUpdate)return;
	unsigned char keyCode[256];
	int tmp = GetKeyboardState(keyCode);
	buttonList.SetAllDownFlg();

	for (unsigned short i = 0; i < 256; i++)
	{
		if (!(keyCode[i] & ChStd::MAX_CHAR_BIT))continue;

		buttonList.SetBitTrue((unsigned char)i);
	}

	isKeyUpdate = true;
}
