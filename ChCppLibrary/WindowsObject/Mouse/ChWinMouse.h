#ifdef _WINDOWS_

#ifndef Ch_Win_Mou_h
#define Ch_Win_Mou_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	class WindObject;
}

namespace ChWin
{

	class MouseController :public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			WindObject& _windObject
			, const unsigned long _windWidth
			, const unsigned long _windHeight);

		void Init(ChSystem::Windows& _win);

		virtual void Release();

		inline void SetWindSize(
			const unsigned long _windWidth
			, const unsigned long _windHeight)
		{
			if (!*this)return;
			windSize.w = _windWidth;
			windSize.h = _windHeight;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetCursolFromClient(unsigned long _x, unsigned long _y);
		
		void SetCursolFromClient(const POINT& _point);
		
		void SetCursolFromScreen(unsigned long _x, unsigned long _y);

		void SetCursolFromScreen(const POINT& _point);

		inline void SetVisibleFlg(const bool _flg)
		{
			if (!*this)return;
			visFlg = _flg;
			ShowCursor(visFlg);
		}

		inline void SetCenterFixedFlg(const bool _flg)
		{
			if (!*this)return;
			setCenterPosFlg = _flg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline POINT GetWheelMove()
		{
			if (!*this)return POINT();
			return wheelMoveVal;
		}

		inline POINT GetNowPos() 
		{
			if (!*this)return { 0,0 };
			return nowPos; 
		}

		ChVec2 GetNowPosToChVec2();

		ChVec2 GetNowProPosToChVec2();

		POINT GetMoveValue();

		ChVec2 GetMoveValueToChVec2();

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

		friend ChSystem::Windows;

	protected:

		///////////////////////////////////////////////////////////////////////////////////

	private:
		
		POINT wheelMoveVal{ 0,0 };
		POINT centerPos{ 0,0 };
		POINT nowPos{ 0,0 };
		POINT beforPos{ 0,0 };

		bool wheelHMoveFlg = false;
		bool wheelVMoveFlg = false;
		bool visFlg = false;
		bool setCenterPosFlg = false;

		ChMath::Vector2Base<unsigned long>windSize;

		HWND hWnd = nullptr;

		MouseController(){}

		virtual ~MouseController()
		{
			Release();
		}

	public:

		static MouseController& GetIns()
		{
			static MouseController ins;
			return ins;
		}

	};

	static const std::function<MouseController&()>Mouse = MouseController::GetIns;

}

#endif

#endif