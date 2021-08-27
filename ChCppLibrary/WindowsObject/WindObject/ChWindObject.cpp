#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"ChWindObject.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////

void WindObject::Init(
	const wchar_t* _appName,
	const wchar_t* _windClassName,
	const ChMath::Vector2Base<unsigned int> _windSize,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{
	hWnd = CreateWindowW(
		_windClassName
		, _appName
		, WS_OVERLAPPEDWINDOW
		| WS_CLIPCHILDREN
		| WS_GROUP
		, 10
		, 10
		, _windSize.x
		, _windSize.y
		, NULL
		, NULL
		, _hInst
		, nullptr);
}

///////////////////////////////////////////////////////////////////////////////////

void WindObject::Init(
	const wchar_t* _appName,
	const wchar_t* _windClassName,
	const unsigned int _windWidth,
	const unsigned int _windHeight,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{
	hWnd = CreateWindowW(
		_windClassName
		, _appName
		, WS_OVERLAPPEDWINDOW
		| WS_CLIPCHILDREN
		| WS_GROUP
		, 10
		, 10
		, _windWidth
		, _windHeight
		, NULL
		, NULL
		, _hInst
		, nullptr);
}

///////////////////////////////////////////////////////////////////////////////////

void WindObject::Init(
	const char* _appName,
	const char* _windClassName,
	const ChMath::Vector2Base<unsigned int> _windSize,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{

	hWnd = CreateWindowA(
		_windClassName
		, _appName
		, WS_OVERLAPPEDWINDOW
		| WS_CLIPCHILDREN
		| WS_GROUP
		, 10
		, 10
		, _windSize.x
		, _windSize.y
		, NULL
		, NULL
		, _hInst
		, nullptr);
}

///////////////////////////////////////////////////////////////////////////////////

void WindObject::Init(
	const char* _appName,
	const char* _windClassName,
	const unsigned int _windWidth,
	const unsigned int _windHeight,
	const HINSTANCE _hInst,
	const int _nCmdShow)
{

	hWnd = CreateWindowA(
		_windClassName
		, _appName
		, WS_OVERLAPPEDWINDOW
		| WS_CLIPCHILDREN
		| WS_GROUP
		, 10
		, 10
		, _windWidth
		, _windHeight
		, NULL
		, NULL
		, _hInst
		, nullptr);
}
