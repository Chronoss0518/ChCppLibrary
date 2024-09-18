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
void TextBox##_AorW##::Create(\
	HINSTANCE _hIns,\
	const _CharaType##* _startText,\
	const int _x,\
	const int _y,\
	const int _w,\
	const int _h,\
	const HWND _parentHandl){\
	Create(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);}\
\
void TextBox##_AorW##::Create(\
	const _CharaType##* _startText,\
	const ChINTPOINT& _pos,\
	const ChINTPOINT& _size,\
	const WindObject##_AorW##& _parentWind){\
	Create(_parentWind.GetInstance(), _startText, _pos, _size, _parentWind.GethWnd());}\
\
void TextBox##_AorW##::Create(\
	const _CharaType##* _startText,\
	const int _x,\
	const int _y,\
	const int _w,\
	const int _h,\
	const WindObject##_AorW##& _parentWind){\
	Create(_parentWind.GetInstance(), _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind.GethWnd());}\
\
void ChWin::TextBox##_AorW##::SetText(const _CharaType##* _text, const unsigned int _textLen){\
	if (selectFlg)return;\
	Send(WM_SETTEXT, (WPARAM)_textLen, (LPARAM)_text);}\
\
void ChWin::TextBox##_AorW##::SetCharLimit(const unsigned int _size){\
	if (selectFlg)return;\
	Send(EM_SETLIMITTEXT, (WPARAM)_size, (LPARAM)NULL);\
	charLimit = _size;}\
\
void ChWin::TextBox##_AorW##::Select(){\
	Send(EN_SETFOCUS);\
	SetEnableFlg(true);}\
\
void ChWin::TextBox##_AorW##::UnSelect(){\
	Send(EN_KILLFOCUS);\
	SetEnableFlg(false);}
#endif

CH_WIN_TEXT_BOX_FUNCTIONS(char, A);

CH_WIN_TEXT_BOX_FUNCTIONS(wchar_t, W);
