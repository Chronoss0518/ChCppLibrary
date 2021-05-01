#ifndef Ch_CPP_D3DOBJ_XICon_h
#define Ch_CPP_D3DOBJ_XICon_h

namespace ChD3D
{

	class XInputController:public ChCpp::ClassPerts::Initializer,public ChCpp::ClassPerts::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetLMoterSpeed(const unsigned short _Speed)
		{
			vibFlgs.wLeftMotorSpeed = _Speed;
		}

		inline void SetRMoterSpeed(const unsigned short _Speed)
		{
			vibFlgs.wRightMotorSpeed = _Speed;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChStd::Bool GetUpFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP : false;
		}

		inline ChStd::Bool GetDownFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN : false;
		}

		inline ChStd::Bool GetLeftFlg() 
		{ 
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT : false;
		}

		inline ChStd::Bool GetRightFlg()
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT : false;
		}

		inline ChStd::Bool GetStartFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_START : false;
		}

		inline ChStd::Bool GetBackFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK : false;
		}

		inline ChStd::Bool GetAFlg()
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_A : false;
		}

		inline ChStd::Bool GetBFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_B : false;
		}

		inline ChStd::Bool GetXFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_X : false;
		}

		inline ChStd::Bool GetYFlg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_Y : false;
		}

		inline ChStd::Bool GetL1Flg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB : false;
		}

		inline ChStd::Bool GetL2Flg()
		{
			return *this ? state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD : false;
		}

		inline ChStd::Bool GetR1Flg() 
		{
			return *this ? state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB : false;
		}

		inline ChStd::Bool GetR2Flg() 
		{
			return *this ? state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD : false;
		}

		inline float GetLXStick()
		{
			return LDeadZoneTest(state.Gamepad.sThumbLX);
		}

		inline float GetLYStick()
		{
			return LDeadZoneTest(state.Gamepad.sThumbLY);
		}

		inline float GetRXStick()
		{
			return RDeadZoneTest(state.Gamepad.sThumbRX);
		}

		inline float GetRYStick()
		{
			return RDeadZoneTest(state.Gamepad.sThumbRY);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

		///////////////////////////////////////////////////////////////////////////////////

		float RDeadZoneTest(const float _sThumb);

		float LDeadZoneTest(const float _sThumb);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		static ChCpp::BitBool controllerFlgs;
		unsigned char myNo = 5;
		XINPUT_STATE state = { 0,{0,0,0,0,0,0,0} };
		XINPUT_VIBRATION vibFlgs = {0,0};
	};

}


#endif
