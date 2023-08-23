#ifdef _WINDOWS_

#ifndef Ch_Win_RdBu_h
#define Ch_Win_RdBu_h

#include"../WindObject/ChWindObject.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class RadioButton : public WindObject
	{
	public:

		virtual ~RadioButton()
		{
			Release();
		}


	public:

		///////////////////////////////////////////////////////////////////////////////////////

		//TextBox�̍쐬//
		void CreateA(
			HINSTANCE _hIns,
			const std::string& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateA(
			HINSTANCE _hIns,
			const std::string& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateA(
			const std::string& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void CreateA(
			const std::string& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void CreateW(
			HINSTANCE _hIns,
			const std::wstring& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateW(
			HINSTANCE _hIns,
			const std::wstring& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
			const HWND _parentHandl = nullptr);

		//TextBox�̍쐬//
		void CreateW(
			const std::wstring& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const bool _glpFlg,
			const WindObject& _parentWind);

		//TextBox�̍쐬//
		void CreateW(
			const std::wstring& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const bool _glpFlg,
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
			const bool _glpFlg,
			const HWND _parentHandl = nullptr
		)
		{

#ifdef UNICODE
			CreateW(_hIns, _startText, _pos, _size, _glpFlg, _parentHandl);
#else
			CreateA(_hIns, _startText, _pos, _size, _glpFlg, _parentHandl);
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
			const bool _glpFlg,
			const HWND _parentHandl = nullptr
		)
		{

#ifdef UNICODE
			CreateW(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentHandl);
#else
			CreateA(_hIns, _startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentHandl);
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
			const bool _glpFlg,
			const WindObject& _parentWind
		)
		{

#ifdef UNICODE
			CreateW(_startText, _pos, _size, _glpFlg, _parentWind);
#else
			CreateA(_startText, _pos, _size, _glpFlg, _parentWind);
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
			const bool _glpFlg,
			const WindObject& _parentWind
		)
		{

#ifdef UNICODE
			CreateW(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentWind);
#else
			CreateA(_startText, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), _glpFlg, _parentWind);
#endif
		}

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		bool isSelection()
		{
			return (SendMessage(GethWnd(), BM_GETCHECK, 0, 0) == BST_CHECKED);
		}

		///////////////////////////////////////////////////////////////////////////////////////

	protected:




	};

}

#endif

#endif