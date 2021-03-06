#ifdef _WINDOWS_

#ifndef Ch_Win_TextBox_h
#define Ch_Win_TextBox_h

#include"../WindObject/ChWindObject.h"

namespace ChWin
{

	class TextBox :public WindObject
	{
	public://Create Functions//

		//TextBoxの作成//
		void CreateA(
			HINSTANCE _hIns,
			const std::string& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void CreateA(
			HINSTANCE _hIns,
			const std::string& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void CreateA(
			const std::string& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind);

		//TextBoxの作成//
		void CreateA(
			const std::string& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObject& _parentWind);

		//TextBoxの作成//
		void CreateW(
			HINSTANCE _hIns,
			const std::wstring& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void CreateW(
			HINSTANCE _hIns,
			const std::wstring& _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void CreateW(
			const std::wstring& _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObject& _parentWind);

		//TextBoxの作成//
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
		//GetFunction//

		//TextBoxからTextの出力//
		std::string GetTextA();

		std::wstring GetTextW();

#ifdef UNICODE
		std::wstring
#else
		std::string
#endif
			GetText()
		{
			return
#ifdef UNICODE
				GetTextW();
#else
				GetTextA();
#endif
		}

		//TextBoxへ入力できる文字数の制限//
		inline unsigned long GetCharLimit()
		{
			return charLimit;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//TextBoxへTextの入力//
		void SetTextA(const std::string& _text);

		void SetTextW(const std::wstring& _text);


		void SetText(
			const
#ifdef UNICODE
			std::wstring&
#else
			std::string&
#endif 
			_text)
		{
#ifdef UNICODE
			SetTextW(_text);
#else
			SetTextA(_text);
#endif
		}

		//TextBoxへ入力できる文字数の制限//
		void SetCharLimitA(const unsigned long _size);

		//TextBoxへ入力できる文字数の制限//
		void SetCharLimitW(const unsigned long _size);

		void SetText(const unsigned long _size)
		{
#ifdef UNICODE
			SetCharLimitW(_size);
#else
			SetCharLimitA(_size);
#endif
		}

	public://Is Functions//

		inline ChStd::Bool IsSelect() { return selectFlg; }

		inline ChStd::Bool IsChange() { return isChangeFlg; }

	public://Other Functions//

		void Select();

		void UnSelect();

	private://Member Value//

		unsigned long charLimit = 50;

		ChStd::Bool selectFlg = false;
		ChStd::Bool isChangeFlg = false;

	};

}


#endif

#endif
