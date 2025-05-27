
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinRadioButton.h"

using namespace ChWin;


#ifndef CH_WIN_RADIO_BUTTON_FUNCTIONS
#define CH_WIN_RADIO_BUTTON_FUNCTIONS(_CharaType,_AorW)\
void RadioButton##_AorW::Create(\
	HINSTANCE _hIns,\
	const _CharaType##* _startText,\
	const int _x,\
	const int _y,\
	const int _w,\
	const int _h,\
	const bool _glpFlg,\
	const HWND _parentHandl){\
	Create(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentHandl);}\
\
void RadioButton##_AorW::Create(\
	const _CharaType##* _startText,\
	const ChINTPOINT& _pos,\
	const ChINTPOINT& _size,\
	const bool _glpFlg,\
	const WindObject##_AorW##& _parentWind){\
	Create(_parentWind.GetInstance(), _startText, _pos, _size, _glpFlg, _parentWind.GethWnd());}\
\
void RadioButton##_AorW::Create(\
	const _CharaType##* _startText,\
	const int _x,\
	const int _y,\
	const int _w,\
	const int _h,\
	const bool _glpFlg,\
	const WindObject##_AorW##& _parentWind){\
	Create(_parentWind.GetInstance(), _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentWind.GethWnd());}
#endif


CH_WIN_RADIO_BUTTON_FUNCTIONS(char, A);

CH_WIN_RADIO_BUTTON_FUNCTIONS(wchar_t, W);