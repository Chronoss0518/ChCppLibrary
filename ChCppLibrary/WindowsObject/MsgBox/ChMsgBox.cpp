#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../PackData/ChPoint.h"
#include"ChMsgBox.h"

using namespace ChWin;


MsgBox::PushButtonType MsgBox::DisplayW(
	HWND _hWnd,
	const wchar_t* _text,
	const wchar_t* _title)
{

	if (buttonType <= 0)return PushButtonType::Error;
	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxW(_hWnd, _text, _title, uType));
}

MsgBox::PushButtonType MsgBox::DisplayServiceNotificationW(
	const wchar_t* _text,
	const wchar_t* _title)
{

	if (buttonType <= 0)return PushButtonType::Error;
	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxW(nullptr, _text, _title, uType));
}


MsgBox::PushButtonType MsgBox::DisplayA(
	HWND _hWnd,
	const char* _text,
	const char* _title)
{

	if (buttonType <= 0)return PushButtonType::Error;

	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxA(_hWnd, _text, _title, uType));
}

MsgBox::PushButtonType MsgBox::DisplayServiceNotificationA(
	const char* _text,
	const char* _title)
{
	if (buttonType <= 0)return PushButtonType::Error;

	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxA(nullptr, _text, _title, uType));
}


unsigned int MsgBox::CreateUType()
{
	unsigned int uType = buttonType;
	uType |= ChStd::EnumCast(mType);
	uType |= ChStd::EnumCast(diType);
	uType |= ChStd::EnumCast(tType);
	uType |= ChStd::EnumCast(type);
	return uType;

}