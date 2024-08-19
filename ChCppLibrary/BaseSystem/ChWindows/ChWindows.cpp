
#include<windows.h>

#include"../../BaseIncluder/ChBase.h"


#include"../ChBaseSystem/ChBaseSystem.h"

#include"../../WindowsObject/PackData/ChPoint.h"
#include"ChWindows.h"
#include"../../WindowsObject/Mouse/ChWinMouse.h"


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
template void ChSystem::WindowsBase<char>::Update(HWND _hWnd);
template void ChSystem::WindowsBase<wchar_t>::Update(HWND _hWnd);

template<typename CharaType>
void ChSystem::WindowsBase<CharaType>::SetKeyCode()
{
	if (!useSystemButtonFlg)return;
	if (isKeyUpdate)return;
	unsigned char keyCode[256];
	int tmp = GetKeyboardState(keyCode);
	buttonList->SetAllDownFlg();

	for (unsigned short i = 0; i < 256; i++)
	{
		if (!(keyCode[i] & ChStd::MAX_CHAR_BIT))continue;

		buttonList->SetBitTrue((unsigned char)i);
	}

	isKeyUpdate = true;
}
template void ChSystem::WindowsBase<char>::SetKeyCode();
template void ChSystem::WindowsBase<wchar_t>::SetKeyCode();


bool ChSystem::WindowsA::IsUpdate()
{
	WindowsBase<char>::Update(wndObject->GethWnd());
	return wndObject->Update();
}

void ChSystem::WindowsA::Release()
{
	wndObject->Release();
	SetInitFlg(false);
}

bool ChSystem::WindowsW::IsUpdate()
{
	WindowsBase<wchar_t>::Update(wndObject->GethWnd());
	return wndObject->Update();
}

void ChSystem::WindowsW::Release()
{
	wndObject->Release();
	SetInitFlg(false);
}