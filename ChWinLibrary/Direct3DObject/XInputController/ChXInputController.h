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
			VibFlgs.wLeftMotorSpeed = _Speed;
		}

		inline void SetRMoterSpeed(const unsigned short _Speed)
		{
			VibFlgs.wRightMotorSpeed = _Speed;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChStd::Bool GetUpFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP : false;
		}

		inline ChStd::Bool GetDownFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN : false;
		}

		inline ChStd::Bool GetLeftFlg() 
		{ 
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT : false;
		}

		inline ChStd::Bool GetRightFlg()
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT : false;
		}

		inline ChStd::Bool GetStartFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_START : false;
		}

		inline ChStd::Bool GetBackFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK : false;
		}

		inline ChStd::Bool GetAFlg()
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_A : false;
		}

		inline ChStd::Bool GetBFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_B : false;
		}

		inline ChStd::Bool GetXFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_X : false;
		}

		inline ChStd::Bool GetYFlg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_Y : false;
		}

		inline ChStd::Bool GetL1Flg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB : false;
		}

		inline ChStd::Bool GetL2Flg()
		{
			return *this ? State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD : false;
		}

		inline ChStd::Bool GetR1Flg() 
		{
			return *this ? State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB : false;
		}

		inline ChStd::Bool GetR2Flg() 
		{
			return *this ? State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD : false;
		}

		inline float GetLXStick()
		{
			return LDeadZoneTest(State.Gamepad.sThumbLX);
		}

		inline float GetLYStick()
		{
			return LDeadZoneTest(State.Gamepad.sThumbLY);
		}

		inline float GetRXStick()
		{
			return RDeadZoneTest(State.Gamepad.sThumbRX);
		}

		inline float GetRYStick()
		{
			return RDeadZoneTest(State.Gamepad.sThumbRY);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

		///////////////////////////////////////////////////////////////////////////////////

		float RDeadZoneTest(const float _sThumb);

		float LDeadZoneTest(const float _sThumb);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		static ChCpp::BitBool ControllerFlgs;
		unsigned char MyNo = 5;
		XINPUT_STATE State = { 0,{0,0,0,0,0,0,0} };
		XINPUT_VIBRATION VibFlgs = {0,0};
	};

}


#endif
