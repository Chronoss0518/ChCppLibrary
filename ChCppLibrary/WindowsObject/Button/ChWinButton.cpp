#include<Windows.h>


#include"../PackData/ChPoint.h"
#include"ChWinButton.h"

#ifndef Ch_Win_Button_Set_Functions
#define Ch_Win_Button_Set_Functions(_AorW) \
void ChWin::Button##_AorW::SetClickFunction(const std::function<void(HWND, UINT)>& _callBack){ SetChildWindProcedure(BN_CLICKED, _callBack);}\
\
void ChWin::Button##_AorW::SetDblClickFunction(const std::function<void(HWND, UINT)>& _callBack){SetChildWindProcedure(BN_DBLCLK, _callBack);}\
\
void ChWin::Button##_AorW::SetSelectFunction(const std::function<void(HWND, UINT)>& _callBack){SetChildWindProcedure(BN_HILITE, _callBack);}
#endif

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//ButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::ButtonBase::CreateStyle()
{
	style.Clear();

	style.AddVisible();
	style.AddChild();
	style.AddClipChildren();
	style.AddGroup();
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
	const WindObjectA& _parentWind)
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
	const WindObjectA& _parentWind)
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
	const WindObjectW& _parentWind)
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
	const WindObjectW& _parentWind)
{
	Create(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

Ch_Win_Button_Set_Functions(A);

void ChWin::ButtonA::Create(
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

	hWnd = creater.Create(_startText, "BUTTON");
	CreateEnd(true);
}

Ch_Win_Button_Set_Functions(W);

//TextBoxÇÃçÏê¨//
void ChWin::ButtonW::Create(
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

	hWnd = creater.Create(_startText, L"BUTTON");
	CreateEnd(true);
}
