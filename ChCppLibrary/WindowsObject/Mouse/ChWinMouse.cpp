
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../PackData/ChPoint.h"
#include"../../BaseSystem/ChWindows/ChWindows.h"
#include"ChWinMouse.h"

///////////////////////////////////////////////////////////////////////////////////
//MouseControllerÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Init(
	const HWND& _hWnd
	, const unsigned long _windWidth
	, const unsigned long _windHeight)
{
	if (ChPtr::NullCheck(_hWnd))return;

	hWnd = _hWnd;

	windSize.w = _windWidth;
	windSize.h = _windHeight;

	centerPos.x = windSize.w / 2;
	centerPos.y = windSize.h / 2;

	ScreenToClient(_hWnd, &centerPos);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Init(const ChSystem::Windows& _win)
{
	Init(_win.GethWnd(), _win.GetWindWidth(), _win.GetWindHeight());
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Release()
{
	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::SetCursolFromClient(unsigned long _x, unsigned long _y)
{
	if (ChPtr::NullCheck(hWnd))return;
	POINT tmp = {_x,_y};

	ClientToScreen(hWnd, &tmp);

	SetCursolFromScreen(tmp);
}

void ChWin::MouseController::SetCursolFromClient(const POINT& _point)
{
	if (ChPtr::NullCheck(hWnd))return;
	POINT tmp = _point;

	ClientToScreen(hWnd, &tmp);

	SetCursolFromScreen(tmp);
}

void ChWin::MouseController::SetCursolFromScreen(unsigned long _x, unsigned long _y)
{
	SetCursorPos(_x, _y);
}

void ChWin::MouseController::SetCursolFromScreen(const POINT& _point)
{
	SetCursorPos(_point.x, _point.y);
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2 ChWin::MouseController::GetNowPosToChVec2()
{
	if (!*this)return { 0.0f,0.0f };

	ChVec2 tmpVec;
	tmpVec.x = static_cast<float>(nowPos.x);
	tmpVec.y = static_cast<float>(nowPos.y);
	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2 ChWin::MouseController::GetNowProPosToChVec2()
{
	if (!*this)return { 0.0f,0.0f };

	ChVec2 tmpWSize;

	tmpWSize.val = windSize.val;

	ChVec2 tmpVec;
	tmpVec.x = static_cast<float>(nowPos.x);
	tmpVec.y = static_cast<float>(nowPos.y);

	tmpVec /= tmpWSize;

	tmpVec *= 2.0f;
	tmpVec -= 1.0f;
	tmpVec.y *= -1.0f;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

POINT ChWin::MouseController::GetMoveValue()
{
	if (!*this)return { 0,0 };

	POINT tmp;
	tmp.x = (nowPos.x - beforPos.x);
	tmp.y = (nowPos.y - beforPos.y);

	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2 ChWin::MouseController::GetMoveValueToChVec2()
{

	if (!*this)return { 0.0f,0.0f };

	ChVec2 tmpVec;
	tmpVec.x = static_cast<float>(nowPos.x - beforPos.x);
	tmpVec.y = static_cast<float>(nowPos.y - beforPos.y);

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Update()
{
	if (!*this)return;

	beforPos = nowPos;

	GetCursorPos(&nowPos);

	ScreenToClient(hWnd, &nowPos);

	if (setCenterPosFlg)
	{
		beforPos = centerPos;
		POINT tmp;

		tmp = centerPos;

		ClientToScreen(hWnd, &tmp);
		SetCursorPos(tmp.x, tmp.y);
	}

	RECT Rec;

	GetClientRect(hWnd, &Rec);

	windSize.w = Rec.right - Rec.left;
	windSize.h = Rec.bottom - Rec.top;

	if (setCenterPosFlg)
	{
		centerPos.x = static_cast<long>((Rec.right - Rec.left) / 2);
		centerPos.y = static_cast<long>((Rec.bottom - Rec.top) / 2);
	}

}