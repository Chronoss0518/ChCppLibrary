#ifdef _WINDOWS_

#ifndef Ch_Win_BuOb_h
#define Ch_Win_BuOb_h

#ifndef Ch_Win_WO_h
#include"../WindObject/ChWindObject.h"
#endif

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class Button :public WindObject
	{

	public:

		//TextBox�̍쐬//
		void CreateA(
			HINSTANCE _hIns,
			const std::string& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateA(
			HINSTANCE _hIns,
			const std::string& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateA(
			const std::string& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void CreateA(
			const std::string& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void CreateW(
			HINSTANCE _hIns,
			const std::wstring& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateW(
			HINSTANCE _hIns,
			const std::wstring& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateW(
			const std::wstring& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void CreateW(
			const std::wstring& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObject& _parentWind);

		void Create(
			HINSTANCE _hIns,
			const
#ifdef UNICODE
			std::wstring
#else
			std::string
#endif
			_startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr
		)
		{

#ifdef UNICODE
			CreateW(_hIns, _startText, _pos, _size, _parentHandl);
#else
			CreateA(_hIns, _startText, _pos, _size, _parentHandl);
#endif
		}

		void Create(
			HINSTANCE _hIns,
			const
#ifdef UNICODE
			std::wstring
#else
			std::string
#endif
			_startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr
		)
		{

#ifdef UNICODE
			CreateW(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);
#else
			CreateA(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentHandl);
#endif
		}

		void Create(
			const
#ifdef UNICODE
			std::wstring
#else
			std::string
#endif
			_startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind
		)
		{

#ifdef UNICODE
			CreateW(_startText, _pos, _size, _parentWind);
#else
			CreateA(_startText, _pos, _size, _parentWind);
#endif
		}

		void Create(
			const
#ifdef UNICODE
			std::wstring
#else
			std::string
#endif
			_startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObject& _parentWind
		)
		{

#ifdef UNICODE
			CreateW(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
#else
			CreateA(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _parentWind);
#endif
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetClickFunction(std::function<void(HWND, UINT)>& _callBack);

		void SetDblClickFunction(std::function<void(HWND, UINT)>& _callBack);

		void SetSelectFunction(std::function<void(HWND, UINT)>& _callBack);

	protected:

		virtual WindStyle* CreateStyle();

	};

}

#endif

#endif