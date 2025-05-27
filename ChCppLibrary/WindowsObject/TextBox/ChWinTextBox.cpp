#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"


#include"../PackData/ChPoint.h"
#include"ChWinTextBox.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//TextBoxÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

#ifndef CH_WIN_TEXT_BOX_FUNCTIONS
#define CH_WIN_TEXT_BOX_FUNCTIONS(_CharaType,_AorW)\
void TextBox##_AorW::Create(\
	HINSTANCE _hIns,\
	const _CharaType##* _startText,\
	const int _x,\
	const int _y,\
	const int _w,\
	const int _h,\
	const HWND _parentHandl){\
	Create(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);}\
\
void TextBox##_AorW::Create(\
	const _CharaType##* _startText,\
	const ChINTPOINT& _pos,\
	const ChINTPOINT& _size,\
	const WindObject##_AorW##& _parentWind){\
	Create(_parentWind.GetInstance(), _startText, _pos, _size, _parentWind.GethWnd());}\
\
void TextBox##_AorW::Create(\
	const _CharaType##* _startText,\
	const int _x,\
	const int _y,\
	const int _w,\
	const int _h,\
	const WindObject##_AorW##& _parentWind){\
	Create(_parentWind.GetInstance(), _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind.GethWnd());}\
\
void ChWin::TextBox##_AorW::SetText(const _CharaType##* _text, const unsigned int _textLen){\
	if (selectFlg)return;\
	Send(WM_SETTEXT, (WPARAM)_textLen, (LPARAM)_text);}\
\
void ChWin::TextBox##_AorW::SetCharLimit(const unsigned int _size){\
	if (selectFlg)return;\
	Send(EM_SETLIMITTEXT, (WPARAM)_size, (LPARAM)NULL);\
	charLimit = _size;}\
\
void ChWin::TextBox##_AorW::Select(){\
	Send(EN_SETFOCUS);\
	SetEnableFlg(true);}\
\
void ChWin::TextBox##_AorW::UnSelect(){\
	Send(EN_KILLFOCUS);\
	SetEnableFlg(false);}
#endif

CH_WIN_TEXT_BOX_FUNCTIONS(char, A);

CH_WIN_TEXT_BOX_FUNCTIONS(wchar_t, W);

void ChWin::TextBoxA::Create(
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

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL |
		WS_GROUP);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, "EDIT");

	if (ChPtr::NullCheck(hWnd))return;

	CreateEnd(true);

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });
}

std::string ChWin::TextBoxA::GetText()
{
	std::string Text = "";

	char tmp[1500] = "\0";

	GetWindowTextA(GethWnd(), tmp, 1500);

	Text = tmp;

	isChangeFlg = false;
	return Text;
}

void ChWin::TextBoxA::SetText(const std::string& _text)
{
	SetText(_text.c_str(), static_cast<unsigned int>(_text.size()));
}

void ChWin::TextBoxW::Create(
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

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL |
		WS_GROUP);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, L"EDIT");

	if (ChPtr::NullCheck(hWnd))return;

	CreateEnd(true);

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });
}

std::wstring ChWin::TextBoxW::GetText()
{
	std::wstring Text = L"";

	wchar_t tmp[1500] = L"\0";

	GetWindowTextW(GethWnd(), tmp, 1500);

	Text = tmp;

	isChangeFlg = false;
	return Text;
}

void ChWin::TextBoxW::SetText(const std::wstring& _text)
{
	SetText(_text.c_str(), static_cast<unsigned int>(_text.size()));
}
