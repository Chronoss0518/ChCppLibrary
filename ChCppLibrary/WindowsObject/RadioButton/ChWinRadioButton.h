#ifdef _WINDOWS_

#ifndef Ch_Win_RdBu_h
#define Ch_Win_RdBu_h

#include"../WindObject/ChWindObject.h"

namespace ChWin
{

	class RadioButtonA : public WindObjectA
	{
	public:

		virtual ~RadioButtonA()
		{
			Release();
		}

	public://Create Functions//

		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const WindObjectA& _parentWind);

		//TextBox�̍쐬//
		void Create(
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const WindObjectA& _parentWind);

	public:

		void SetCheck()
		{
			SendMessageA(hWnd, BM_SETCHECK, BST_CHECKED, 0);
		}

		void SetUnCheck()
		{
			SendMessageA(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
		}

	public://IsFunction//

		bool isSelection()
		{
			return (SendMessageA(GethWnd(), BM_GETCHECK, 0, 0) == BST_CHECKED);
		}

	protected:

	};

	class RadioButtonW : public WindObjectW
	{
	public:

		virtual ~RadioButtonW()
		{
			Release();
		}

	public://Create Functions//

		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void Create(
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const WindObjectW& _parentWind);

		//TextBox�̍쐬//
		void Create(
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const WindObjectW& _parentWind);

	public:

		void SetCheck()
		{
			SendMessageW(hWnd, BM_SETCHECK, BST_CHECKED, 0);
		}

		void SetUnCheck()
		{
			SendMessageW(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
		}

	public://IsFunction//

		bool isSelection()
		{
			return (SendMessageW(GethWnd(), BM_GETCHECK, 0, 0) == BST_CHECKED);
		}

	protected:

	};


	using RadioButton =
#ifdef UNICODE
		RadioButtonW;
#else
		RadioButtonA;
#endif
}

#ifdef CRT

void ChWin::RadioButtonA::Create(
	HINSTANCE _hIns,
	const char* _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const bool _glpFlg,
	const HWND _parentHandl)
{
	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, "BUTTON");
	CreateEnd(true);
}

void ChWin::RadioButtonW::Create(
	HINSTANCE _hIns,
	const wchar_t* _startText,
	const ChINTPOINT& _pos,
	const ChINTPOINT& _size,
	const bool _glpFlg,
	const HWND _parentHandl)
{
	Release();

	auto pos = _pos;
	auto size = _size;
	pos.val.Abs();
	size.val.Abs();

	WindCreater creater(_hIns);

	creater.SetEXStyle(WS_EX_CLIENTEDGE);

	creater.SetWindStyle(
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, L"BUTTON");
	CreateEnd(true);
}


#endif

#endif

#endif