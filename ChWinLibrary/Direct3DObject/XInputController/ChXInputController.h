#ifndef Ch_CPP_D3DOBJ_XICon_h
#define Ch_CPP_D3DOBJ_XICon_h

namespace ChD3D
{

	class XInputController:public ChCpp::ClassPerts::Initializer,public ChCpp::ClassPerts::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		XInputController();

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

		inline unsigned char GetNo()
		{
			return myNo;
		}

		inline unsigned long GetUpdateCounts()
		{
			return state.dwPacketNumber;
		}

		inline ChStd::Bool GetUpFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		}

		inline ChStd::Bool GetDownFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		}

		inline ChStd::Bool GetLeftFlg() 
		{ 
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		}

		inline ChStd::Bool GetRightFlg()
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		}

		inline ChStd::Bool GetStartFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		}

		inline ChStd::Bool GetBackFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		}

		inline ChStd::Bool GetAFlg()
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
		}

		inline ChStd::Bool GetBFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
		}

		inline ChStd::Bool GetXFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
		}

		inline ChStd::Bool GetYFlg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
		}

		inline ChStd::Bool GetL1Flg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		}

		inline float GetL2Trigger()
		{
			return RL2DeadZoneTest(state.Gamepad.bLeftTrigger);
		}

		inline ChStd::Bool GetR1Flg() 
		{
			return state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		}

		inline float GetR2Trigger() 
		{
			return RL2DeadZoneTest(state.Gamepad.bRightTrigger);
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

		float RL2DeadZoneTest(const unsigned char _sButton);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		static ChCpp::BitBool controllerFlgs;
		unsigned char myNo = 5;
		XINPUT_STATE state = { 0,{0,0,0,0,0,0,0} };
		XINPUT_VIBRATION vibFlgs = {0,0};
	};

}


#endif
