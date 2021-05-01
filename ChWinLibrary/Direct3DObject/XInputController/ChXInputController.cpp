#include<Windows.h>
#include<Xinput.h>

#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"ChXInputController.h"

#pragma comment(lib,"xinput.lib")

using namespace ChD3D;

ChCpp::BitBool XInputController::controllerFlgs;

///////////////////////////////////////////////////////////////////////////////////

void XInputController::Init()
{
	unsigned char tmp = 0;

	for (unsigned char i = 0; i < 4; i++)
	{
		if (controllerFlgs.GetBitFlg(i))continue;

		myNo = i;
		controllerFlgs.SetBitTrue(i);
		break;
	}

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void XInputController::Release()
{
	state.Gamepad.bLeftTrigger = 0;
	state.Gamepad.bRightTrigger = 0;
	state.Gamepad.sThumbLX = 0;
	state.Gamepad.sThumbLY = 0;
	state.Gamepad.sThumbRX = 0;
	state.Gamepad.sThumbRY = 0;
	state.Gamepad.wButtons = 0;

	controllerFlgs.SetBitFalse(myNo);
	myNo = 5;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void XInputController::Update()
{
	if (!*this) return;

	ZeroMemory(&state, sizeof(XINPUT_STATE));

	XInputGetState(myNo, &state);

	XInputSetState(myNo, &vibFlgs);

}

///////////////////////////////////////////////////////////////////////////////////

float XInputController::LDeadZoneTest(const float _sThumb)
{
	float Out = std::abs(_sThumb) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0.0f : _sThumb / 32767.0f;
	
	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

float XInputController::RDeadZoneTest(const float _sThumb)
{

	float Out = std::abs(_sThumb) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? 0.0f : _sThumb / 32767.0f;

	return Out;
}
