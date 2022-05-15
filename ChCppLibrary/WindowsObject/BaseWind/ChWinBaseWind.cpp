
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../SubWind/ChWinSubWind.h"
#include"ChWinBaseWind.h"
#include"../../BaseSystem/ChWindows/ChWindows.h"

std::map<unsigned long, ChWin::WindBaseObject*>ChWin::WindBaseObject::objList;

std::string ChWin::WindBaseObject::className = "";

//WindProcedureは登録する際に静的な関数でなければならない//
LRESULT CALLBACK SubWndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{
	switch (_uMsg)
	{	
	case WM_MOVE:
		ChWin::WindMoveUpdate(_hWnd,_lParam);
		break;
	case WM_SIZE:
		ChWin::WindSizeUpdate(_hWnd, _lParam);
		break;

	case WM_COMMAND:
		ChWin::ObjUpdate(_wParam);

		DefWindowProc((HWND)_lParam, _uMsg, _wParam, _lParam);
		break;
	}

	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::ObjUpdate(const WPARAM& _wParam)
{
	if (ChWin::WindBaseObject::objList.empty())return;
	ChWin::WindBaseObject::objList[LOWORD(_wParam)]->Update(_wParam);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindMoveUpdate(const HWND _hWnd, LPARAM _lParam)
{


	if (ChWin::WindBaseObject::objList.empty())return;

	auto wind = ((ChWin::SubWind*)GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	if (ChPtr::NullCheck(wind))return;

	if(!wind->startMoveFlg)return;

	{

		RECT TmpRec;

		GetClientRect(_hWnd, &TmpRec);

		if (TmpRec.bottom != wind->h
			|| TmpRec.right != wind->w) {

			return;
		}
	}

	if (wind->notCMoveFlg)
	{
		MoveWindow(_hWnd, wind->x, wind->y, wind->w, wind->h, true);

		return;
	}

	wind->x = LOWORD(_lParam);
	wind->y = HIWORD(_lParam);



}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindSizeUpdate(const HWND _hWnd, LPARAM _lParam)
{
	if (ChWin::WindBaseObject::objList.empty())return;

	auto wind = ((ChWin::SubWind*)GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	if (ChPtr::NullCheck(wind))return;

	if (!wind->startMoveFlg)
	{

		RECT TmpRec;
		GetClientRect(_hWnd, &TmpRec);

		if (TmpRec.right >= wind->w
			&& TmpRec.bottom >= wind->y
			)
		{
			wind->startMoveFlg = true;
			return;
		}

	}

	if (!wind->notCMoveFlg)
	{

		RECT TmpRec;

		GetWindowRect(_hWnd, &TmpRec);
		wind->x = TmpRec.top;
		wind->y = TmpRec.left;
	}

	if (wind->notCSizeFlg)
	{

		MoveWindow(_hWnd, wind->x, wind->y, wind->w, wind->h, true);

		return;
	}

	wind->w = LOWORD(_lParam);
	wind->h = HIWORD(_lParam);





}

///////////////////////////////////////////////////////////////////////////////////////
//WindBaseObjectメソッド//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindBaseObject::Init(const HWND& _hWnd)
{
	if (ChPtr::NullCheck(_hWnd))return;
	hOwn = _hWnd;
	SetInitFlg(true);


	if (!(className.length() <= 0))return;

	className = "ChSubClass";
	{

		WNDCLASS wc;

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
		wc.lpfnWndProc = SubWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = (HINSTANCE)GetWindowLong(hOwn, GWL_HINSTANCE);
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = (LPSTR)NULL;
		wc.lpszClassName = className.c_str();

		RegisterClass(&wc);

	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindBaseObject::Release()
{
	if (ChPtr::NullCheck(hIns))return;
	DestroyWindow(hIns);
	hIns = nullptr;

	startMoveFlg = false;

	SetInitFlg(false);

	objList.erase(myID);

	if (!objList.empty()) return;

	UnregisterClass(
		className.c_str()
		, (HINSTANCE)GetWindowLong(hOwn, GWL_HINSTANCE));

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindBaseObject::Move(const int _x
	, const int _y
	, const int _w
	, const int _h)
{
	if (ChPtr::NullCheck(hIns))return;
	MoveWindow(hIns, _x, _y, _w, _h, true);
}

void ChWin::WindBaseObject::Move(const int _x
	, const int _y)
{

	if (ChPtr::NullCheck(hIns))return;
	MoveWindow(hIns, _x, _y, w, h, true);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindBaseObject::ReSize(
	const int _w
	, const int _h)
{
	if (ChPtr::NullCheck(hIns))return;
	MoveWindow(hIns, x, y, _w, _h, true);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindBaseObject::RegisterObj()
{
	myID = objList.size();
	objList[myID] = (this);
}

///////////////////////////////////////////////////////////////////////////////////////
