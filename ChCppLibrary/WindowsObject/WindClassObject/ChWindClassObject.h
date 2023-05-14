#ifdef _WINDOWS_

#ifndef Ch_Win_CWind_h
#define Ch_Win_CWind_h

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

		void SetMenuName(const std::string& _name);

	public://GetFunction//

		inline std::string GetWindClassName() { return className; }

	public:

		bool IsSystemRegistClassName(const std::string& _className);

	public://Other Fucntions//

		//Set関数よりセットされた情報を元にクラスを登録する//
		//クラス名が空文字の場合は登録されない//
		void RegistClass(const std::string& _className);


	protected:

		WNDCLASSA cls;
		std::string className = "";
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

		void SetMenuName(const std::wstring& _name);

	public://GetFunction//

		inline std::wstring GetWindClassName() { return className; }

	public:

		bool IsSystemRegistClassName(const std::wstring& _className);

	public://Other Fucntions//

		//Set関数よりセットされた情報を元にクラスを登録する//
		//クラス名が空文字の場合は登録されない//
		void RegistClass(const std::wstring& _className);


	protected:

		WNDCLASSW cls;
		std::wstring className = L"";
};


	using WindClassObject =
#ifdef UNICODE
		WindClassObjectW;
#else
		WindClassObjectA;
#endif

}

#endif

#endif
