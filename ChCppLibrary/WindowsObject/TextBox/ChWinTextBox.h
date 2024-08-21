#ifdef _WINDOWS_

#ifndef Ch_Win_TextBox_h
#define Ch_Win_TextBox_h

#ifdef CRT

#include<string>

#endif

#include"../WindObject/ChWindObject.h"

namespace ChWin
{

	class TextBoxBase
	{
		
	public://Get Functions//

		//TextBoxÇ÷ì¸óÕÇ≈Ç´ÇÈï∂éöêîÇÃêßå¿//
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

		//TextBoxÇÃçÏê¨//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBoxÇÃçÏê¨//
		void Create(
			HINSTANCE _hIns,
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBoxÇÃçÏê¨//
		void Create(
			const char* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObjectA& _parentWind);

		//TextBoxÇÃçÏê¨//
		void Create(
			const char* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObjectA& _parentWind);

	public://SetFunction//

#ifdef CRT
		//TextBoxÇ÷TextÇÃì¸óÕ//
		void SetText(const std::string& _text);
#endif
		//TextBoxÇ÷TextÇÃì¸óÕ//
		void SetText(const char* _text,const unsigned long _textLen);

		//TextBoxÇ÷ì¸óÕÇ≈Ç´ÇÈï∂éöêîÇÃêßå¿//
		void SetCharLimit(const unsigned long _size);

	public://Get Functions//

#ifdef CRT
		//TextBoxÇ©ÇÁTextÇÃèoóÕ//
		std::string GetText();
#endif

	public://Other Functions//

		void Select();

		void UnSelect();

	};

	class TextBoxW :public TextBoxBase, public WindObjectW
	{
	public://Create Functions//

		//TextBoxÇÃçÏê¨//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const HWND _parentHandl = nullptr);

		//TextBoxÇÃçÏê¨//
		void Create(
			HINSTANCE _hIns,
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const HWND _parentHandl = nullptr);

		//TextBoxÇÃçÏê¨//
		void Create(
			const wchar_t* _startText,
			const ChINTPOINT& _pos,
			const ChINTPOINT& _size,
			const WindObjectW& _parentWind);

		//TextBoxÇÃçÏê¨//
		void Create(
			const wchar_t* _startText,
			const int _x,
			const int _y,
			const int _w,
			const int _h,
			const WindObjectW& _parentWind);

	public://SetFunction//

#ifdef CRT
		//TextBoxÇ÷TextÇÃì¸óÕ//
		void SetText(const std::wstring& _text);
#endif
		
		//TextBoxÇ÷TextÇÃì¸óÕ//
		void SetText(const wchar_t* _text, const unsigned long _textLen);

		//TextBoxÇ÷ì¸óÕÇ≈Ç´ÇÈï∂éöêîÇÃêßå¿//
		void SetCharLimit(const unsigned long _size);

	public://Get Functions//

#ifdef CRT
		//TextBoxÇ©ÇÁTextÇÃèoóÕ//
		std::wstring GetText();
#endif

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

#ifdef CRT

void ChWin::TextBoxA::Create(
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

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL |
		WS_GROUP);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, "EDIT");

	if (ChPtr::NullCheck(hWnd))return;

	CreateEnd(true);

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });
}

std::string ChWin::TextBoxA::GetText()
{
	std::string Text = "";

	char tmp[1500] = "\0";

	GetWindowTextA(GethWnd(), tmp, 1500);

	Text = tmp;

	isChangeFlg = false;
	return Text;
}

void ChWin::TextBoxA::SetText(const std::string& _text)
{
	SetText(_text.c_str(), _text.size());
}

void ChWin::TextBoxW::Create(
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

	creater.SetWindStyle(
		WS_BORDER |
		WS_CHILD |
		WS_VISIBLE |
		WS_VSCROLL |
		ES_LEFT |
		ES_MULTILINE |
		ES_AUTOVSCROLL |
		WS_GROUP);

	creater.SetInitPosition(pos.x, pos.y);
	creater.SetInitSize(size.w, size.h);
	creater.SetParentWind(_parentHandl);

	hWnd = creater.Create(_startText, L"EDIT");

	if (ChPtr::NullCheck(hWnd))return;

	CreateEnd(true);

	if (!IsInit())return;

	SetChildWindProcedure(EN_KILLFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = false; });
	SetChildWindProcedure(EN_SETFOCUS, [&](HWND _hWnd, UINT _msg) {selectFlg = true; });
	SetChildWindProcedure(EN_CHANGE, [&](HWND _hWnd, UINT _msg) {isChangeFlg = true; });
}

std::wstring ChWin::TextBoxW::GetText()
{
	std::wstring Text = L"";

	wchar_t tmp[1500] = L"\0";

	GetWindowTextW(GethWnd(), tmp, 1500);

	Text = tmp;

	isChangeFlg = false;
	return Text;
}

void ChWin::TextBoxW::SetText(const std::wstring& _text)
{
	SetText(_text.c_str(), _text.size());
}

#endif

#endif

#endif
