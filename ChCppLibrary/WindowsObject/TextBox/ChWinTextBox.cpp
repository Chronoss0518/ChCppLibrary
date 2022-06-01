#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../PackData/ChPoint.h"
#include"ChWinTextBox.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//TextBoxÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void TextBox::CreateA(
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

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText.c_str(), "EDIT");

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });


}

void TextBox::CreateA(
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

//TextBoxÇÃçÏê¨//
void TextBox::CreateA(
	const std::string& _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const WindObject& _parentWind)
{
	if (!static_cast<bool>(_parentWind))return;

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_parentWind.GetInstanceA());

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(
		WS_BORDER | 
		WS_CHILD | 
		WS_VISIBLE | 
		WS_VSCROLL | 
		ES_LEFT |
		ES_MULTILINE | 
		ES_AUTOVSCROLL);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText.c_str(), "EDIT");

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });

}

//TextBoxÇÃçÏê¨//
void TextBox::CreateA(
	const std::string& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const WindObject& _parentWind)
{
	CreateA(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

void TextBox::CreateW(
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

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	creater.Create(this, _startText.c_str(), L"EDIT");

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });

}

void TextBox::CreateW(
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
void TextBox::CreateW(
	const std::wstring& _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const WindObject& _parentWind)
{
	if (!static_cast<bool>(_parentWind))return;

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_parentWind.GetInstanceA());

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentWind.GethWnd());

	creater.Create(this, _startText.c_str(), L"EDIT");

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });

}

//TextBoxÇÃçÏê¨//
void TextBox::CreateW(
	const std::wstring& _startText,
	const int _x,
	const int _y,
	const int _w,
	const int _h,
	const WindObject& _parentWind)
{
	CreateW(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
}

std::string TextBox::GetTextA()
{
	std::string Text = "";

	char tmp[1500] = "\0";

	GetWindowTextA(GethWnd(), tmp, 1500);

	Text = tmp;

	isChangeFlg = false;
	return Text;
}

std::wstring TextBox::GetTextW()
{
	std::wstring Text = L"";

	wchar_t tmp[1500] = L"\0";

	GetWindowTextW(GethWnd(), tmp, 1500);

	Text = tmp;

	//Text = reinterpret_cast<wchar_t*>(SendW(WM_GETTEXT, (WPARAM)1500, (LPARAM)tmp));

	isChangeFlg = false;
	return Text;
}

void TextBox::SetTextA(const std::string& _text)
{
	if (selectFlg)return;
	SendA(WM_SETTEXT, (WPARAM)_text.size(), (LPARAM)_text.c_str());

}

void TextBox::SetTextW(const std::wstring& _text)
{
	if (selectFlg)return;
	SendW(WM_SETTEXT, (WPARAM)_text.size(), (LPARAM)_text.c_str());
}


///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::SetCharLimitA(const unsigned long _size)
{
	if (selectFlg)return;
	SendA(EM_SETLIMITTEXT, (WPARAM)_size, (LPARAM)NULL);
	charLimit = _size;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::SetCharLimitW(const unsigned long _size)
{
	if (selectFlg)return;
	SendW(EM_SETLIMITTEXT, (WPARAM)_size, (LPARAM)NULL);
	charLimit = _size;
}

void ChWin::TextBox::Select()
{
	Send(EN_SETFOCUS);
	SetEnableFlg(true);
}

void ChWin::TextBox::UnSelect()
{
	Send(EN_KILLFOCUS);
	SetEnableFlg(false);
}
