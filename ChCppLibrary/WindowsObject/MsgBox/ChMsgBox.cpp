#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../PackData/ChPoint.h"
#include"ChMsgBox.h"

using namespace ChWin;


MsgBox::PushButtonType MsgBox::DisplayW(
	HWND _hWnd,
	const wchar_t* _title,
	const wchar_t* _text)
{
	unsigned int uType = CreateUType();

	return static_cast<PushButtonType>(MessageBoxW(_hWnd, _title, _text, uType));
}

MsgBox::PushButtonType MsgBox::DisplayServiceNotificationW(
	const wchar_t* _title,
	const wchar_t* _text)
{

	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxW(nullptr, _title, _text, uType));
}


MsgBox::PushButtonType MsgBox::DisplayA(
	HWND _hWnd,
	const char* _title,
	const char* _text)
{

	unsigned int uType = CreateUType();

	return static_cast<PushButtonType>(MessageBoxA(_hWnd, _title, _text, uType));
}

MsgBox::PushButtonType MsgBox::DisplayServiceNotificationA(
	const char* _title,
	const char* _text)
{

	unsigned int uType = CreateUType();
	uType |= MB_SERVICE_NOTIFICATION;

	return static_cast<PushButtonType>(MessageBoxA(nullptr, _title, _text, uType));
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