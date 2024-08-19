#include<Windows.h>


#include"../PackData/ChPoint.h"
#include"ChWinButton.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//ButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ButtonA::Create(
	HINSTANCE _hIns,
	const char* _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const HWND _parentHandl)
{
	Create(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);
}

void ButtonA::Create(
	const char* _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const WindObject& _parentWind)
{

	if (!_parentWind.IsInit())return;

	Create(_parentWind.GetInstance(), _startText, _pos, _size, _parentWind.GethWnd());
}

void ButtonA::Create(
	const char* _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const WindObject& _parentWind)
{
	Create(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

//TextBoxÇÃçÏê¨//
void ButtonW::Create(
	HINSTANCE _hIns,
	const wchar_t* _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const HWND _parentHandl)
{
	Create(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);
}

//TextBoxÇÃçÏê¨//
void ButtonW::Create(
	const wchar_t* _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const WindObject& _parentWind)
{
	if (!_parentWind.IsInit())return;

	Create(_parentWind.GetInstance(), _startText, _pos, _size, _parentWind.GethWnd());
}

//TextBoxÇÃçÏê¨//
void ButtonW::Create(
	const wchar_t* _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const WindObject& _parentWind)
{
	Create(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

void ButtonBase::CreateStyle()
{
	style.Clear();

	style.AddVisible();
	style.AddChild();
	style.AddClipChildren();
	style.AddGroup();
}