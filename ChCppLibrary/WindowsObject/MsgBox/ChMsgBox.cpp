#include<Windows.h>

#include"../PackData/ChPoint.h"
#include"ChMsgBox.h"

using namespace ChWin;


MsgBox::PushButtonType MsgBox::DisplayW(
	HWND _hWnd,
	const wchar_t* _title,
	const wchar_t* _text)
{
	unsigned int uType = CreateUType();

	return static_cast<PushButtonType>(MessageBoxW(_hWnd, _text, _title, uType));
}

MsgBox::PushButtonType MsgBox::DisplayServiceNotificationW(
	const wchar_t* _title,
	const wchar_t* _text)
{

	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxW(nullptr, _text, _title, uType));
}


MsgBox::PushButtonType MsgBox::DisplayA(
	HWND _hWnd,
	const char* _title,
	const char* _text)
{

	unsigned int uType = CreateUType();

	return static_cast<PushButtonType>(MessageBoxA(_hWnd, _text, _title, uType));
}

MsgBox::PushButtonType MsgBox::DisplayServiceNotificationA(
	const char* _title,
	const char* _text)
{

	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxA(nullptr, _text, _title, uType));
}

