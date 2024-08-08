#ifdef _WINDOWS_

#ifndef Ch_Win_CWind_h
#define Ch_Win_CWind_h

#include"../../ClassParts/ChCPInitializer.h"

namespace ChWin
{
	class WindClassStyle;

	//WindowsAPIの内WindowClassを用いたオブジェクトを司るクラス//
	class WindClassObjectA:public ChCp::Initializer
	{
	public://ConstructorDestructor//

		inline WindClassObjectA() { Init(); }

		inline WindClassObjectA(const WNDCLASSA& _cls) { Init(_cls); }

		inline ~WindClassObjectA() { Release(); }
		
	public://InitAndRelease//

		void Init();

		void Init(const WNDCLASSA& _cls);

		void Release();

	public://SetFunction//

		void SetStyle(const unsigned int _style);

		void SetStyle(const WindClassStyle* _style);

		void SetIcon(const HICON _icon);

		void SetCursol(const HCURSOR _cursor);

		//ウィンドウクラス構造の後の追加バイト数//
		void SetClsExtra(const int _byteNum = 0);

		//ウィンドウインスタンスの後の追加バイト数//
		void SetWndExtra(const int _byteNum = 0);

		void SetBackgroundColor(const HBRUSH _brush);

		void SetInstance(const HINSTANCE _hInst);

		void SetWindProcedure(WNDPROC _windProc);

		void SetMenuName(const char* _name);

	public://GetFunction//

		const char* GetWindClassName();

	public:

		bool IsSystemRegistClassName(const char* _className);

	public://Other Fucntions//

		//Set関数よりセットされた情報を元にクラスを登録する//
		//クラス名が空文字の場合は登録されない//
		void RegistClass(const char* _className);


	protected:

		WNDCLASSA cls;
#ifdef CRT
		std::string className = "";
#endif
	};

	//WindowsAPIの内WindowClassを用いたオブジェクトを司るクラス//
	class WindClassObjectW :public ChCp::Initializer
	{
	public://ConstructorDestructor//

		inline WindClassObjectW() { Init(); }

		inline WindClassObjectW(const WNDCLASSW& _cls) { Init(_cls); }

		inline ~WindClassObjectW() { Release(); }

	public://InitAndRelease//

		void Init();

		void Init(const WNDCLASSW& _cls);

		void Release();

	public://SetFunction//

		void SetStyle(const unsigned int _style);

		void SetStyle(const WindClassStyle* _style);

		void SetIcon(const HICON _icon);

		void SetCursol(const HCURSOR _cursor);

		//ウィンドウクラス構造の後の追加バイト数//
		void SetClsExtra(const int _byteNum = 0);

		//ウィンドウインスタンスの後の追加バイト数//
		void SetWndExtra(const int _byteNum = 0);

		void SetBackgroundColor(const HBRUSH _brush);

		void SetInstance(const HINSTANCE _hInst);

		void SetWindProcedure(WNDPROC _windProc);

		void SetMenuName(const wchar_t* _name);

	public://GetFunction//

		const wchar_t* GetWindClassName();

	public:

		bool IsSystemRegistClassName(const wchar_t* _className);

	public://Other Fucntions//

		//Set関数よりセットされた情報を元にクラスを登録する//
		//クラス名が空文字の場合は登録されない//
		void RegistClass(const wchar_t* _className);


	protected:

		WNDCLASSW cls;
#ifdef CRT
		std::wstring className = L"";
#endif
};


	using WindClassObject =
#ifdef UNICODE
		WindClassObjectW;
#else
		WindClassObjectA;
#endif

}

#ifdef CRT


const char* ChWin::WindClassObjectA::GetWindClassName() { return className.c_str(); }

bool ChWin::WindClassObjectA::IsSystemRegistClassName(const char* _className)
{
	std::string tmpClassName = _className;
	std::string systemRegistClassName[] =
	{
		"BUTTON",
		"COMBOBOX",
		"EDIT",
		"LISTBOX",
		"MDICLIENT",
		"RichEdit",
		"RICHEDIT_CLASS",
		"SCROLLBAR",
		"STATIC" };

	switch (tmpClassName.length())
	{
	case 4:
		for (char i = 3; i >= 0; i--)
		{
			if (tmpClassName[i] == systemRegistClassName[2][i])continue;
			return false;
		}
		return true;
	case 6:

		if (tmpClassName[5] == systemRegistClassName[0][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[0][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[5] == systemRegistClassName[8][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[8][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 7:

		for (char i = 6; i >= 0; i--)
		{
			if (tmpClassName[i] == systemRegistClassName[3][i])continue;
			return false;
		}

		return true;

	case 8:
		if (tmpClassName[7] == systemRegistClassName[1][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[1][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[7] == systemRegistClassName[5][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[5][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 9:
		if (tmpClassName[8] == systemRegistClassName[4][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[4][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[8] == systemRegistClassName[7][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] == systemRegistClassName[7][i])continue;
				return false;
			}
			return true;
		}

		return false;
	case 15:

		for (char i = 14; i >= 0; i--)
		{
			if (tmpClassName[i] == systemRegistClassName[6][i])continue;
			return false;
		}

		return true;

	default:
		return false;
	}

	return false;
}

void ChWin::WindClassObjectA::RegistClass(const char* _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	std::string tmpClassName = _className;
	if (tmpClassName == "")return;
	className = tmpClassName;
	if (IsSystemRegistClassName(className.c_str()))return;

	cls.lpszClassName = className.c_str();
	RegisterClassA(&cls);

	SetInitFlg(true);
}

const wchar_t* ChWin::WindClassObjectW::GetWindClassName() { return className.c_str(); }

bool ChWin::WindClassObjectW::IsSystemRegistClassName(const wchar_t* _className)
{
	std::wstring tmpClassName = _className;
	std::wstring systemRegistClassName[] =
	{
		L"BUTTON",
		L"COMBOBOX",
		L"EDIT",
		L"LISTBOX",
		L"MDICLIENT",
		L"RichEdit",
		L"RICHEDIT_CLASS",
		L"SCROLLBAR",
		L"STATIC" };

	switch (tmpClassName.length())
	{
	case 4:
		for (char i = 3; i >= 0; i--)
		{
			if (tmpClassName[i] != systemRegistClassName[2][i])continue;
			return false;
		}
		return true;
	case 6:

		if (tmpClassName[5] != systemRegistClassName[0][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[0][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[5] != systemRegistClassName[8][5])
		{
			for (char i = 4; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[8][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 7:

		for (char i = 6; i >= 0; i--)
		{
			if (tmpClassName[i] != systemRegistClassName[3][i])continue;
			return false;
		}

		return true;

	case 8:
		if (tmpClassName[7] != systemRegistClassName[1][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[1][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[7] != systemRegistClassName[5][7])
		{
			for (char i = 6; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[5][i])continue;
				return false;
			}
			return true;
		}

		return false;

	case 9:
		if (tmpClassName[8] != systemRegistClassName[4][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[4][i])continue;
				return false;
			}
			return true;
		}
		else if (tmpClassName[8] != systemRegistClassName[7][8])
		{
			for (char i = 7; i >= 0; i--)
			{
				if (tmpClassName[i] != systemRegistClassName[7][i])continue;
				return false;
			}
			return true;
		}

		return false;
	case 15:

		for (char i = 14; i >= 0; i--)
		{
			if (tmpClassName[i] != systemRegistClassName[6][i])continue;
			return false;
		}

		return true;

	default:
		return false;
	}

	return false;
}

void ChWin::WindClassObjectW::RegistClass(const wchar_t* _className)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(cls.lpfnWndProc))return;
	std::wstring tmpClassName = _className;
	if (tmpClassName == L"")return;
	className = tmpClassName;
	if (IsSystemRegistClassName(className.c_str()))return;

	cls.lpszClassName = className.c_str();
	RegisterClassW(&cls);

	SetInitFlg(true);
}
#endif


#endif

#endif
