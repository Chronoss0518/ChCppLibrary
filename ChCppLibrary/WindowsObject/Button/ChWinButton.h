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

void ChWin::ButtonA::Create(
	HINSTANCE _hIns,
	const char* _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const HWND _parentHandl)
{

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	CreateStyle();
	creater.SetWindStyle(&style);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, "BUTTON");
	CreateEnd(true);
}

Ch_Win_Button_Set_Functions(W);

//TextBox�̍쐬//
void ChWin::ButtonW::Create(
	HINSTANCE _hIns,
	const wchar_t* _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const HWND _parentHandl)
{

	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	CreateStyle();
	creater.SetWindStyle(&style);


	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, L"BUTTON");
	CreateEnd(true);
}

#endif

#endif

#endif