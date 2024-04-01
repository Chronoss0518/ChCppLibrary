
#include<windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../ChBaseSystem/ChBaseSystem.h"

#include"../../WindowsObject/PackData/ChPoint.h"
#include"ChWindows.h"
#include"../../WindowsObject/Mouse/ChWinMouse.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChWindowsÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

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
	const std::string& _windClassName,
	const ChINTPOINT& _windSize,
	const ChINTPOINT& _windPos,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{
	ChINTPOINT pos = _windPos;
	ChINTPOINT size = _windSize;

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);

	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);
}

void Windows::Init(
	const std::string& _appName,
	const std::string& _className,
	const unsigned long _dwStyle,
	const ChINTPOINT& _windSize,
	const ChINTPOINT& _windPos,
	HINSTANCE _hInst,
	const int _nCmdShow,
	const unsigned long _exStyle,
	HWND _parent,
	HMENU _hMenu,
	LPVOID _param)
{
	ChINTPOINT pos = _windPos;
	ChINTPOINT size = _windSize;

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(_dwStyle);
	creater.SetEXStyle(_exStyle);
	creater.SetParentWind(_parent);
	creater.SetMenu(_hMenu);
	creater.SetParam(_param);

	Init(creater, _appName, _className, _hInst, _nCmdShow);
}

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

	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);

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

	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);

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


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(_dwStyle);
	creater.SetEXStyle(_exStyle);
	creater.SetParentWind(_parent);
	creater.SetMenu(_hMenu);
	creater.SetParam(_param);

	Init(creater, _appName, _className, _hInst, _nCmdShow);

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
	const std::wstring& _windClassName,
	const ChINTPOINT& _windSize,
	const ChINTPOINT& _windPos,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{
	ChINTPOINT pos = _windPos;
	ChINTPOINT size = _windSize;

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);

	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);
}

void Windows::Init(
	const std::wstring& _appName,
	const std::wstring& _className,
	const unsigned long _dwStyle,
	const ChINTPOINT& _windSize,
	const ChINTPOINT& _windPos,
	HINSTANCE _hInst,
	const int _nCmdShow,
	const unsigned long _exStyle,
	HWND _parent,
	HMENU _hMenu,
	LPVOID _param)
{
	ChINTPOINT pos = _windPos;
	ChINTPOINT size =_windSize;

	pos.val.Abs();
	size.val.Abs();

	ChWin::WindCreater creater(_hInst);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(_dwStyle);
	creater.SetEXStyle(_exStyle);
	creater.SetParentWind(_parent);
	creater.SetMenu(_hMenu);
	creater.SetParam(_param);

	Init(creater, _appName, _className, _hInst, _nCmdShow);
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

	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);
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

	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);

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


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetWindStyle(_dwStyle);
	creater.SetEXStyle(_exStyle);
	creater.SetParentWind(_parent);
	creater.SetMenu(_hMenu);
	creater.SetParam(_param);

	Init(creater, _appName, _className, _hInst, _nCmdShow);
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::Release()
{
	wndObject.Release();
	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

bool Windows::IsPushKey(const int _Key)
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

bool Windows::IsPushKeyNoHold(const int _Key)
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

bool Windows::IsPause(const int _Key)
{
	SetKeyCode();

	bool tmpFlg;
	tmpFlg = IsPushKey(_Key);

	if (tmpFlg && nowKey)return pauseFlg;
	nowKey = false;

	if (!tmpFlg)return pauseFlg;

	pauseFlg = !pauseFlg;
	nowKey = true;

	return pauseFlg;
}

///////////////////////////////////////////////////////////////////////////////////

bool Windows::IsUpdate()
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
	if (!useSystemButtonFlg)return;
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

std::string ChWin::ToRelativePath(const std::string& _path)
{

	if (_path.find(":\\") == _path.npos && _path.find(":/") == _path.npos)return _path;

	std::string tmp;
	std::string out = _path;

	{

		char* tmp2 = nullptr;
		tmp2 = new char[256];

		GetCurrentDirectory(256, tmp2);
		tmp = tmp2;

		delete[] tmp2;

	}

	std::string SetCutChar = "/";
	{

		std::string OutCutChar = "\\";

		while (1)
		{
			size_t tmpLen = tmp.find(OutCutChar, 0);
			if (tmpLen == tmp.npos)break;
			tmp.replace(tmpLen, OutCutChar.size(), SetCutChar);

		}
		while (1)
		{
			size_t tmpLen = _path.find(OutCutChar, 0);
			if (tmpLen == _path.npos)break;
			out.replace(tmpLen, OutCutChar.size(), SetCutChar);

		}

		std::string tmpBackChar = "";


		while (1)
		{
			size_t tmpLen = out.find(tmp);

			if (tmpLen != out.npos)break;

			tmpLen = tmp.rfind(SetCutChar, tmp.length());

			tmp.replace(tmpLen, tmp.length() - tmpLen, "");

			tmpBackChar += "../";

		}



		out.replace(0, tmp.length() + 1, "");

		out = tmpBackChar + out;



	}

	return out;

}