
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinRadioButton.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//RadioButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void RadioButton::CreateA(
	HINSTANCE _hIns,
	const std::string& _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const bool _glpFlg,
	const HWND _parentHandl)
{
	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText.c_str(), "BUTTON");

}

void RadioButton::CreateA(
	HINSTANCE _hIns,
	const std::string& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const bool _glpFlg,
	const HWND _parentHandl)
{
	CreateA(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentHandl);
}

//RadioButtonÇÃçÏê¨//
void RadioButton::CreateA(
	const std::string& _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const bool _glpFlg,
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

	creater.SetWindStyle(
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText.c_str(), "BUTTON");

}

//RadioButtonÇÃçÏê¨//
void RadioButton::CreateA(
	const std::string& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const bool _glpFlg,
	const WindObject& _parentWind)
{
	CreateA(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentWind);
}

void RadioButton::CreateW(
	HINSTANCE _hIns,
	const std::wstring& _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const bool _glpFlg,
	const HWND _parentHandl)
{
	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText.c_str(), L"BUTTON");

}

void RadioButton::CreateW(
	HINSTANCE _hIns,
	const std::wstring& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const bool _glpFlg,
	const HWND _parentHandl)
{
	CreateW(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentHandl);
}

//RadioButtonÇÃçÏê¨//
void RadioButton::CreateW(
	const std::wstring& _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const bool _glpFlg,
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

	creater.SetWindStyle(
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText.c_str(), L"BUTTON");

}

//RadioButtonÇÃçÏê¨//
void RadioButton::CreateW(
	const std::wstring& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const bool _glpFlg,
	const WindObject& _parentWind)
{
	CreateW(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentWind);
}
