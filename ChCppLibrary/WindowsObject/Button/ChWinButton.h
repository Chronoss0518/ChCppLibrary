#ifdef _WINDOWS_

#ifndef Ch_Win_BuOb_h
#define Ch_Win_BuOb_h

#include<functional>

#include"../WindObject/ChWindObject.h"
#include"../WindObject/ChWindStyle.h"

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

		void SetClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetDblClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetSelectFunction(const std::function<void(HWND, UINT)>& _callBack);

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
			const WindObjectA& _parentWind);

		//TextBox�̍쐬//
		void Create(
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObjectA& _parentWind);
	};

	class ButtonW :public WindObjectW, public ButtonBase
	{
	public://Set Functions//
		void SetClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetDblClickFunction(const std::function<void(HWND, UINT)>& _callBack);

		void SetSelectFunction(const std::function<void(HWND, UINT)>& _callBack);
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
			const WindObjectW& _parentWind);

		//TextBox�̍쐬//
		void Create(
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObjectW& _parentWind);
	};

	using Button =
#ifdef UNICODE
		ButtonW;
#else
		ButtonA;
#endif
}

#endif

#endif