
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../PackData/ChPoint.h"
#include"../../BaseSystem/ChWindows/ChWindows.h"
#include"ChWinMouse.h"

///////////////////////////////////////////////////////////////////////////////////
//MouseControllerÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Init(const HWND& _hWnd)
{
	if (ChPtr::NullCheck(_hWnd))return;

	hWnd = _hWnd;


	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Init(const ChSystem::Windows& _win)
{
	Init(_win.GethWnd());
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Release()
{
	SetInitFlg(false);
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
	
	UpdateCenterPos();

	beforPos = nowPos;

	GetCursorPos(nowPos);

	ScreenToClient(hWnd, nowPos);

	if (!setCenterPosFlg)return;

	beforPos = centerPos;
	POINT tmp;

	tmp = centerPos;

	ClientToScreen(hWnd, &tmp);
	SetCursorPos(tmp.x, tmp.y);

}

void ChWin::MouseController::UpdateCenterPos()
{
	if (!*this)return;
	if (!setCenterPosFlg)return;

	RECT rec;

	GetClientRect(hWnd, &rec);

	unsigned long w = (rec.right - rec.left);
	unsigned long h = (rec.bottom - rec.top);

	if (windSize.w == (rec.right - rec.left) && windSize.h == h)return;

	windSize.w = w;
	windSize.h = h;

	centerPos.x = static_cast<long>((windSize.w) / 2);
	centerPos.y = static_cast<long>((windSize.h) / 2);

	ScreenToClient(hWnd, centerPos);

}
