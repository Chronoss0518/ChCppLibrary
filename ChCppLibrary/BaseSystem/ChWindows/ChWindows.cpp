
#include<windows.h>

#include"../../BaseIncluder/ChBase.h"


#include"../ChBaseSystem/ChBaseSystem.h"

#include"../../WindowsObject/PackData/ChPoint.h"
#include"ChWindows.h"
#include"../../WindowsObject/Mouse/ChWinMouse.h"

#ifndef CH_WINDOWS_INIT_FUNCTION
#define CH_WINDOWS_INIT_FUNCTION(_AorW,_CharaType) \
void ChSystem::Windows##_AorW::Init(\
	const ChWin::WindCreater& _creater,\
	const _CharaType##* _appName,\
	const _CharaType##* _windClassName,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	wndObject.hWnd = _creater.Create(_appName, _windClassName);\
	if(ChPtr::NullCheck(wndObject.hWnd))return;\
	wndObject.CreateEnd(_nCmdShow);\
	inst = _hInst;\
	buttonList.SetSize((256 / 8) + 1);\
	isNowPush.SetSize((256 / 8) + 1);\
	SetInitFlg(true);}\
\
void ChSystem::Windows##_AorW::Init(\
	const _CharaType* _appName,\
	const _CharaType* _windClassName,\
	const ChINTPOINT& _windSize,\
	const ChINTPOINT& _windPos,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	ChINTPOINT pos = _windPos;\
	ChINTPOINT size = _windSize;\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);\
	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW::Init(\
	const _CharaType* _appName,\
	const _CharaType* _className,\
	const unsigned long _dwStyle,\
	const ChINTPOINT& _windSize,\
	const ChINTPOINT& _windPos,\
	HINSTANCE _hInst,\
	const int _nCmdShow,\
	const unsigned long _exStyle,\
	HWND _parent,\
	HMENU _hMenu,\
	LPVOID _param){\
	ChINTPOINT pos = _windPos;\
	ChINTPOINT size = _windSize;\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(_dwStyle);\
	creater.SetEXStyle(_exStyle);\
	creater.SetParentWind(_parent);\
	creater.SetMenu(_hMenu);\
	creater.SetParam(_param);\
	Init(creater, _appName, _className, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW::Init(\
	const _CharaType* _appName,\
	const _CharaType* _windClassName,\
	const int _windWidth,\
	const int _windHeight,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(10, 10);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);\
	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW::Init(\
	const _CharaType* _appName,\
	const _CharaType* _windClassName,\
	const int _windWidth,\
	const int _windHeight,\
	const int _initWindPosX,\
	const int _initWindPosY,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);\
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);\
	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW::Init(\
	const _CharaType* _appName,\
	const _CharaType* _className,\
	const unsigned long _dwStyle,\
	const int _initWindPosX,\
	const int _initWindPosY,\
	const int _windWidth,\
	const int _windHeight,\
	HINSTANCE _hInst,\
	const int _nCmdShow,\
	const unsigned long _exStyle,\
	HWND _parent,\
	HMENU _hMenu,\
	LPVOID _param){\
	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);\
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(_dwStyle);\
	creater.SetEXStyle(_exStyle);\
	creater.SetParentWind(_parent);\
	creater.SetMenu(_hMenu);\
	creater.SetParam(_param);\
	Init(creater, _appName, _className, _hInst, _nCmdShow);}
#endif

#ifndef CH_Win_Path_Cut_CHARA1_FUNCTION
#define CH_Win_Path_Cut_CHARA1_FUNCTION(type) CH_NUMBER_FUNCTION(ChWin::GetWinPathCutChara1,type)
#endif

#ifndef CH_Win_Path_Cut_CHARA2_FUNCTION
#define CH_Win_Path_Cut_CHARA2_FUNCTION(type) CH_NUMBER_FUNCTION(ChWin::GetWinPathCutChara2,type)
#endif

#ifndef CH_Win_Path_Back_CHARA_FUNCTION
#define CH_Win_Path_Back_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION(ChWin::GetWinPathBackChara,type)
#endif

#ifndef Ch_ToRelativePath_Function
#define Ch_ToRelativePath_Function(_CharType, _AorW) \
std::basic_string<_CharType> ToRelativePath##_AorW##(const std::basic_string<_CharType>& _path){\
	if (_path.find(ChWin::GetWinPathCutChara1<_CharType>()) == _path.npos && _path.find(ChWin::GetWinPathCutChara2<_CharType>()) == _path.npos)return _path;\
	std::basic_string<_CharType> tmp;\
	std::basic_string<_CharType> res = _path;\
	{_CharType tmp2[MAX_PATH];\
	GetCurrentDirectory##_AorW##(MAX_PATH, tmp2);\
	tmp = tmp2;}\
\
	{\
		while (1){\
			size_t tmpLen = tmp.find(ChStd::GetYenChara<_CharType>(), 0);\
			if (tmpLen == tmp.npos)break;\
			tmp.replace(tmpLen, 1, ChStd::GetSlashChara<_CharType>());}\
		while (1){\
			size_t tmpLen = _path.find(ChStd::GetYenChara<_CharType>(), 0);\
			if (tmpLen == _path.npos)break;\
			res.replace(tmpLen, 1, ChStd::GetSlashChara<_CharType>());}\
\
		std::basic_string<_CharType> tmpBackChar = ChStd::GetZeroChara<_CharType>();\
\
		while (1){\
			size_t tmpLen = res.find(tmp);\
			if (tmpLen != res.npos)break;\
			tmpLen = tmp.rfind(ChStd::GetSlashChara<_CharType>(), tmp.length());\
			tmp.replace(tmpLen, tmp.length() - tmpLen, ChStd::GetZeroChara<_CharType>());\
			tmpBackChar += ChWin::GetWinPathBackChara<_CharType>();}\
		res.replace(0, tmp.length() + 1, ChStd::GetZeroChara<_CharType>());\
		res = tmpBackChar + res;}\
	return res;}\

#endif

CH_TO_NUMBER_FUNCTION(CH_Win_Path_Cut_CHARA1_FUNCTION, ":\\");

CH_TO_NUMBER_FUNCTION(CH_Win_Path_Cut_CHARA2_FUNCTION, ":/");

CH_TO_NUMBER_FUNCTION(CH_Win_Path_Back_CHARA_FUNCTION, "../");


using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChWindowsÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChSystem::WindowsBase<CharaType>::Update(HWND _hWnd)
{
	if (ChPtr::NullCheck(_hWnd))return;

	isKeyUpdate = false;

	RECT tmp;
	GetClientRect(_hWnd, &tmp);

	windSize.w = tmp.right - tmp.left;
	windSize.h = tmp.bottom - tmp.top;
}

template<typename CharaType>
void ChSystem::WindowsBase<CharaType>::SetKeyCode()
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

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChSystem::WindowsBase);

CH_WINDOWS_INIT_FUNCTION(A, char);

bool ChSystem::WindowsA::IsUpdate()
{
	WindowsBase<char>::Update(wndObject.GethWnd());
	return wndObject.Update();
}

void ChSystem::WindowsA::Release()
{
	wndObject.Release();
	SetInitFlg(false);
}

CH_WINDOWS_INIT_FUNCTION(W, wchar_t);

bool ChSystem::WindowsW::IsUpdate()
{
	WindowsBase<wchar_t>::Update(wndObject.GethWnd());
	return wndObject.Update();
}

void ChSystem::WindowsW::Release()
{
	wndObject.Release();
	SetInitFlg(false);
}

namespace ChWin
{
	Ch_ToRelativePath_Function(char, A);

	Ch_ToRelativePath_Function(wchar_t, W);
}