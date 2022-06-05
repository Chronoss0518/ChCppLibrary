#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../WindObject/ChWindStyle.h"
#include"ChWinButton.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//ButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void Button::CreateA(
	HINSTANCE _hIns,
	const std::string& _startText,
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

	creater.SetWindStyle(CreateStyle());

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText.c_str(), "BUTTON");

}

void Button::CreateA(
	HINSTANCE _hIns,
	const std::string& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const HWND _parentHandl)
{
	CreateA(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);
}

void Button::CreateA(
	const std::string& _startText,
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

	WindCreater creater(_parentWind.GetInstanceA());

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(CreateStyle());

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText.c_str(), "BUTTON");

}

void Button::CreateA(
	const std::string& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const WindObject& _parentWind)
{
	CreateA(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

//TextBoxÇÃçÏê¨//
void Button::CreateW(
	HINSTANCE _hIns,
	const std::wstring& _startText,
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

	creater.SetWindStyle(CreateStyle());

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText.c_str(), L"BUTTON");
}

//TextBoxÇÃçÏê¨//
void Button::CreateW(
	HINSTANCE _hIns,
	const std::wstring& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const HWND _parentHandl)
{
	CreateW(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);
}

//TextBoxÇÃçÏê¨//
void Button::CreateW(
	const std::wstring& _startText,
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

	WindCreater creater(_parentWind.GetInstanceA());

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(CreateStyle());

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText.c_str(), L"BUTTON");
}

//TextBoxÇÃçÏê¨//
void Button::CreateW(
	const std::wstring& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const WindObject& _parentWind)
{
	CreateW(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

void Button::SetClickFunction(std::function<void(HWND, UINT)>& _callBack)
{
	SetChildWindProcedure(BN_CLICKED, _callBack);
}

void Button::SetDblClickFunction(std::function<void(HWND, UINT)>& _callBack)
{
	SetChildWindProcedure(BN_DBLCLK, _callBack);
}

void Button::SetSelectFunction(std::function<void(HWND, UINT)>& _callBack)
{
	SetChildWindProcedure(BN_HILITE, _callBack);
}

WindStyle* Button::CreateStyle()
{

	static WindStyle style;

	style.Clear();

	style.AddVisible();
	style.AddChild();
	style.AddClipChildren();
	style.AddGroup();


	return &style;
}