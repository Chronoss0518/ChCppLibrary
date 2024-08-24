#ifdef _WINDOWS_

#ifndef Ch_Win_Mou_h
#define Ch_Win_Mou_h

#include"../WindObject/ChWindObject.h"

namespace ChWin
{

	class MouseController :public ChCp::Initializer
	{
	public://Init And Release//

		void Init(WindObjectA& _windObject);

		void Init(WindObjectW& _windObject);

		void Init(ChSystem::WindowsA& _win);

		void Init(ChSystem::WindowsW& _win);

		virtual void Release();

		inline void SetWindSize(
			const unsigned long _windWidth
			, const unsigned long _windHeight)
		{
			if (!*this)return;
			windSize.w = _windWidth;
			windSize.h = _windHeight;
		}

	public://Set Functions//

		void SetCursolFromClient(unsigned long _x, unsigned long _y);
		
		void SetCursolFromClient(const ChPOINT& _point);
		
		void SetCursolFromScreen(unsigned long _x, unsigned long _y);

		void SetCursolFromScreen(const ChPOINT& _point);

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

	public://Get Functions//

		inline ChPOINT GetWheelMove()
		{
			if (!*this)return ChPOINT();
			return wheelMoveVal;
		}

		inline ChPOINT GetNowPos()
		{
			if (!*this)return { 0,0 };
			return nowPos; 
		}

		ChVec2 GetNowPosToChVec2();

		ChVec2 GetNowProPosToChVec2();

		ChPOINT GetMoveValue();

		ChVec2 GetMoveValueToChVec2();
	
	public://Update Functions//

		void Update();

	private:
		
		ChPOINT wheelMoveVal{ 0,0 };
		ChPOINT centerPos{ 0,0 };
		ChPOINT nowPos{ 0,0 };
		ChPOINT beforPos{ 0,0 };

		bool wheelHMoveFlg = false;
		bool wheelVMoveFlg = false;
		bool visFlg = false;
		bool setCenterPosFlg = false;

		ChPOINT windSize;

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

	inline MouseController& Mouse() { return MouseController::GetIns(); };

}

#ifdef CRT

void ChWin::MouseController::Init(WindObjectA& _windObject)
{
	hWnd = _windObject.GethWnd();

	if (ChPtr::NullCheck(hWnd))return;

	_windObject.SetWindProcedure(
		WM_MOUSEWHEEL,
		[&](
			HWND _hWnd,
			UINT _uMsg,
			WPARAM _wParam,
			LPARAM _lParam)->LRESULT
		{
			wheelMoveVal.y = GET_WHEEL_DELTA_WPARAM(_wParam);
			wheelVMoveFlg = true;
			return 0;
		});

	_windObject.SetWindProcedure(
		WM_MOUSEHWHEEL,
		[&](
			HWND _hWnd,
			UINT _uMsg,
			WPARAM _wParam,
			LPARAM _lParam)->LRESULT
		{
			wheelMoveVal.x = GET_WHEEL_DELTA_WPARAM(_wParam);
			wheelHMoveFlg = true;
			return 0;
		});

	windSize = _windObject.GetWindSize();

	centerPos.x = windSize.w / 2;
	centerPos.y = windSize.h / 2;

	ScreenToClient(hWnd, &centerPos.pt);

	SetInitFlg(true);
}

void ChWin::MouseController::Init(WindObjectW& _windObject)
{
	hWnd = _windObject.GethWnd();

	if (ChPtr::NullCheck(hWnd))return;

	_windObject.SetWindProcedure(
		WM_MOUSEWHEEL,
		[&](
			HWND _hWnd,
			UINT _uMsg,
			WPARAM _wParam,
			LPARAM _lParam)->LRESULT
		{
			wheelMoveVal.y = GET_WHEEL_DELTA_WPARAM(_wParam);
			wheelVMoveFlg = true;
			return 0;
		});

	_windObject.SetWindProcedure(
		WM_MOUSEHWHEEL,
		[&](
			HWND _hWnd,
			UINT _uMsg,
			WPARAM _wParam,
			LPARAM _lParam)->LRESULT
		{
			wheelMoveVal.x = GET_WHEEL_DELTA_WPARAM(_wParam);
			wheelHMoveFlg = true;
			return 0;
		});

	windSize = _windObject.GetWindSize();

	centerPos.x = windSize.w / 2;
	centerPos.y = windSize.h / 2;

	ScreenToClient(hWnd, &centerPos.pt);

	SetInitFlg(true);
}

#endif

#endif

#endif