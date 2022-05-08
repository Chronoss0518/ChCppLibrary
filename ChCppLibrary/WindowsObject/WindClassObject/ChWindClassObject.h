#ifdef _WINDOWS_

#ifndef Ch_Win_CWind_h
#define Ch_Win_CWind_h

namespace ChWin
{
	class WindClassStyle;

	//WindowsAPIの内WindowClassを用いたオブジェクトを司るクラス//
	class WindClassObject:public ChCp::Initializer
	{
	public://ConstructorDestructor//

		inline WindClassObject() { Init(); }

		inline WindClassObject(const WNDCLASS& _cls) { Init(_cls); }

		inline ~WindClassObject() { Release(); }
		
	public://InitAndRelease//

		void Init();

		void Init(const WNDCLASS& _cls);

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

	public://GetFunction//

		inline std::string GetWindClassName() { return className; }

	public:

		//Set関数よりセットされた情報を元にクラスを登録する//
		//クラス名が空文字の場合は登録されない//
		void RegistClass(const std::string& _className);

	protected:

		WNDCLASS cls;
		std::string className = "";

	};
}

#endif

#endif
