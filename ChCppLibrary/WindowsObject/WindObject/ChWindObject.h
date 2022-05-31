#ifdef _WINDOWS_

#ifndef Ch_Win_WO_h
#define Ch_Win_WO_h

namespace ChWin
{
	LRESULT CALLBACK WndProcA(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);

	LRESULT CALLBACK WndProcW(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);

	class WindStyle;
	class WindCreater;

	//WindowsAPIの内、Windowの管理するクラス//
	class WindObject :public ChCp::Initializer
	{
	public://ConstructorDestructor//

		WindObject() { Init(); }

		~WindObject() { Release(); }

	public://InitAndRelease//

		void Init();

		void Init(HWND _hWnd,const int _nShowCmd);

		void Release();

	public://SetFunction//
		
		//このウィンドウが子ウィンドウ以外の場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline virtual void SetWindProcedure(const unsigned long _message,const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc)
		{
			if (!_proc)return;

			(wndProc)[_message] = _proc;
		}

		//登録されたどのメッセージも受け取らなかった場合に呼ばれる関数//
		inline void SetDefaultWindProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc)
		{
			if (!_proc)return;

			defaultWindProc = _proc;
		}

		//子ウィンドウが動作して呼ばれたときに実行される関数//
		//このウィンドウが子ウィンドウの場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline void SetChildWindProcedure(const unsigned long _message, const std::function<void(HWND, UINT)>& _proc)
		{
			if (!_proc)return;

			(childWindProc)[_message] = _proc;
		}

		void SetWindPos(const unsigned int _x, const unsigned int _y,const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER);

		inline void SetWindPos(const ChPOINT& _pos, const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER)
		{
			SetWindPos(_pos.x, _pos.y, _flgs);
		}

		void SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER);

		inline void SetWindSize(const ChPOINT& _size, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER)
		{
			SetWindPos(_size.w, _size.h, _flgs);
		}

		void SetWindRect(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOZORDER);

		inline void SetWindRect(const RECT& _rec, const unsigned int _flgs = SWP_NOZORDER)
		{
			SetWindRect(_rec.top, _rec.left, _rec.right - _rec.left, _rec.bottom - _rec.top, _flgs);
		}

	public://GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void)const { return hWnd; }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Windowのサイズを取得する関数//
		const ChPOINT GetWindSize()const;

		//Windowの左上の位置を取得する関数//
		const ChPOINT GetWindPos()const;

		inline const HINSTANCE GetInstance()const
		{
#ifdef UNICODE
			return GetInstanceW();
#else
			return GetInstanceA();
#endif
		}

		const HINSTANCE GetInstanceA()const;

		const HINSTANCE GetInstanceW()const;

	public://UpdateFunction//

		inline virtual ChStd::Bool Update()
		{
#ifdef UNICODE
			return UpdateW();
#else
			return UpdateA();
#endif
		}

		ChStd::Bool UpdateA();
		ChStd::Bool UpdateW();

	public://Other Functions//

		//メッセージを送る。戻り値は変更があった場合の数値//
		inline LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0)
		{

#ifdef UNICODE
			return SendW(_msg, _wParam, _lParam);
#else
			return SendA(_msg,_wParam,_lParam);
#endif
		}

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM SendW(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0);

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM SendA(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0);

		//描画を行う前に以前の描画情報を全て消す命令と再描画命令を送る//
		inline void InvalidateWind(const bool _clear = true)
		{
			InvalidateRect(hWnd, nullptr, _clear);
			UpdateWindow(hWnd);
		}

		//WndProcedureを動的にするために外部にあるWndProcから見えるようにする//
		friend LRESULT CALLBACK ChWin::WndProcA(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		//WndProcedureを動的にするために外部にあるWndProcから見えるようにする//
		friend LRESULT CALLBACK ChWin::WndProcW(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		//WIndCreaterにWindObjectのPrivate部分も見えるようにする//
		friend WindCreater;

	protected://CreateBaseFunction//

		void CreateEnd(const int _nCmdShow);

	private://MemberValue//
		
		std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> defaultWindProc = [](
			HWND _hWnd,
			UINT _uMsg, 
			WPARAM _wParam,
			LPARAM _lParam)->LRESULT 
		{return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam); };

		std::map<unsigned int, std::function<void(HWND, UINT)>> childWindProc;
		std::map<unsigned int, std::function<LRESULT(HWND,UINT,WPARAM,LPARAM)>> wndProc;
		HWND hWnd = nullptr;
		MSG msg = { 0 };

	};

	class WindCreater
	{
	public://ConstructorDestructor//

		WindCreater(HINSTANCE _ins) { Init(_ins); }

	public://Init And Release//

		void Init(HINSTANCE _ins) { hInst = _ins; }

	public://Set Function//

		inline void SetWindStyle(const unsigned int _style)
		{
			style = _style;
		}

		void SetWindStyle(const WindStyle* _style);

		inline void SetEXStyle(const unsigned long _style)
		{
			exStyle = _style;
		}

		inline void SetParentWind(const WindObject& _wObj)
		{
			parent = _wObj.GethWnd();
		}

		inline void SetParentWind(const HWND _wind)
		{
			parent = _wind;
		}

		inline void SetMenu(const HMENU _menu)
		{
			hMenu = _menu;
		}

		void SetInitPosition(const ChINTPOINT& _pos);

		void SetInitPosition(const int _x, const int _y);

		void SetInitSize(const ChINTPOINT& _size);

		void SetInitSize(const int _w, const int _h);

	public://Get Function//

		inline const ChINTPOINT GetPosition()const
		{
			return pos;
		}

		inline const ChINTPOINT GetSize()const
		{
			return size;
		}

	public://Create Functino//

		//Set Functionを先に行う//
		ChStd::Bool Create(WindObject* _out,const std::string& _appName,const std::string& _windClassName,const int _nShowCmd = true)const;

		ChStd::Bool Create(WindObject* _out,const std::wstring& _appName,const std::wstring& _windClassName, const int _nShowCmd = true)const;

	private://MemberValue//

		unsigned long exStyle = 0;
		unsigned int style = 0;
		HWND parent = nullptr;
		HMENU hMenu = nullptr;
		HINSTANCE hInst = nullptr;
		LPVOID param = nullptr;
		ChINTPOINT pos = ChINTPOINT(0, 0);
		ChINTPOINT size = ChINTPOINT(100,100);

	};

}

#endif

#endif
