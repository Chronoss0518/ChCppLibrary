#ifdef _WINDOWS_

#ifndef Ch_Win_BuOb_h
#define Ch_Win_BuOb_h

#include"../WindObject/ChWindObject.h"
#include"../WindObject/ChWindStyle.h"

#ifndef Ch_Win_Button_Set_Functions
#define Ch_Win_Button_Set_Functions(_AorW) \
inline void ChWin::Button##_AorW##::SetClickFunction(const std::function<void(HWND, UINT)>& _callBack){ SetChildWindProcedure(BN_CLICKED, _callBack);}\
\
inline void ChWin::Button##_AorW##::SetDblClickFunction(const std::function<void(HWND, UINT)>& _callBack){SetChildWindProcedure(BN_DBLCLK, _callBack);}\
\
inline void ChWin::Button##_AorW##::SetSelectFunction(const std::function<void(HWND, UINT)>& _callBack){SetChildWindProcedure(BN_HILITE, _callBack);}
#endif

namespace ChWin
{

	class ButtonBase
	{
	protected:

		virtual void CreateStyle();

		WindStyle style;
	};

	class ButtonA :public WindObjectA,public ButtonBase
	{
	public://Set Functions//
#ifdef CRT
		void SetClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetDblClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetSelectFunction(const std::function<void(HWND, UINT)>& _callBack);
#endif
	public:
		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void Create(
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObject& _parentWind);
	};

	class ButtonW :public WindObjectW, public ButtonBase
	{
	public://Set Functions//
#ifdef CRT
		void SetClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetDblClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetSelectFunction(const std::function<void(HWND, UINT)>& _callBack);
#endif
	public:
		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void Create(
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObject& _parentWind);
	};

	using Button =
#ifdef UNICODE
		ButtonW;
#else
		ButtonA;
#endif
}

#ifdef CRT

Ch_Win_Button_Set_Functions(A);

Ch_Win_Button_Set_Functions(W);

#endif

#endif

#endif