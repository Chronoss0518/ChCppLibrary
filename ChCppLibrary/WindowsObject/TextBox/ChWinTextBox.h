#ifdef _WINDOWS_

#ifndef Ch_Win_TextBox_h
#define Ch_Win_TextBox_h

#include<string>

#include"../WindObject/ChWindObject.h"

namespace ChWin
{

	class TextBoxBase
	{
		
	public://Get Functions//

		//TextBoxへ入力できる文字数の制限//
		inline unsigned long GetCharLimit()
		{
			return charLimit;
		}

	public://Is Functions//

		inline bool IsSelect() { return selectFlg; }

		inline bool IsChange() { return isChangeFlg; }

	protected://Member Value//

		unsigned long charLimit = 50;

		bool selectFlg = false;
		bool isChangeFlg = false;

	};

	class TextBoxA :public TextBoxBase, public WindObjectA
	{
	public://Create Functions//

		//TextBoxの作成//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void Create(
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObjectA& _parentWind);

		//TextBoxの作成//
		void Create(
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObjectA& _parentWind);

	public://SetFunction//

		//TextBoxへTextの入力//
		void SetText(const std::string& _text);

		//TextBoxへTextの入力//
		void SetText(const char* _text,const unsigned int _textLen);

		//TextBoxへ入力できる文字数の制限//
		void SetCharLimit(const unsigned int _size);

	public://Get Functions//

		//TextBoxからTextの出力//
		std::string GetText();

	public://Other Functions//

		void Select();

		void UnSelect();

	};

	class TextBoxW :public TextBoxBase, public WindObjectW
	{
	public://Create Functions//

		//TextBoxの作成//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBoxの作成//
		void Create(
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObjectW& _parentWind);

		//TextBoxの作成//
		void Create(
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObjectW& _parentWind);

	public://SetFunction//

		//TextBoxへTextの入力//
		void SetText(const std::wstring& _text);
		
		//TextBoxへTextの入力//
		void SetText(const wchar_t* _text, const unsigned int _textLen);

		//TextBoxへ入力できる文字数の制限//
		void SetCharLimit(const unsigned int _size);

	public://Get Functions//

		//TextBoxからTextの出力//
		std::wstring GetText();

	public://Other Functions//

		void Select();

		void UnSelect();

	};

	using TextBox =
#ifdef UNICODE
		TextBoxW;
#else
		TextBoxA;
#endif
}

#endif

#endif
