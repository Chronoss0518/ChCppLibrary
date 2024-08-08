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
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const HWND _parentHandl)
{

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	CreateStyle();
	creater.SetWindStyle(&style);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);
	
	creater.Create(this, _startText, "BUTTON");

}

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

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_parentWind.GetInstance());

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	CreateStyle();
	creater.SetWindStyle(&style);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText, "BUTTON");

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
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const HWND _parentHandl)
{

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	CreateStyle();
	creater.SetWindStyle(&style);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText, L"BUTTON");
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

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_parentWind.GetInstance());

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	CreateStyle();
	creater.SetWindStyle(&style);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText, L"BUTTON");
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