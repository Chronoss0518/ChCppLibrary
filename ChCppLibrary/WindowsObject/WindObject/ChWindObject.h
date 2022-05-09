#ifdef _WINDOWS_

#ifndef Ch_Win_WO_h
#define Ch_Win_WO_h

namespace ChWin
{
	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);

	class WindStyle;
	class WindCreater;

	//WindowsAPIの内、Windowの管理するクラス//
	class WindObject :public ChCp::Initializer
	{
	public://operator Function//
		
		WindObject& operator = (const WindObject& _obj);

		bool operator == (const WindObject& _obj)const;
		bool operator != (const WindObject& _obj)const;

	public://ConstructorDestructor//


		WindObject(const WindObject& _obj);

		WindObject() { Init(); }

		~WindObject() { Release(); }

	public://InitAndRelease//

		void Init();

		void Release();

	public://SetFunction//

		void Set(const WindObject& _obj);

		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline void SetWindProcedure(const unsigned long _message, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> _proc)
		{
			if (!_proc)return;

			(wndProc)[_message] = _proc;
		}

		void SetWindPos(const unsigned int _x, const unsigned int _y,const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER);

		inline void SetWindPos(const ChMath::Vector2Base<unsigned int>& _pos, const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER)
		{
			SetWindPos(_pos.x, _pos.y, _flgs);
		}

		void SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER);

		inline void SetWindSize(const ChMath::Vector2Base<unsigned int>& _size, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER)
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
		inline HWND GethWnd(void) const { return hWnd; }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Windowのサイズを取得する関数//
		const ChMath::Vector2Base<unsigned int> GetWindSize()const;

		//Windowの左上の位置を取得する関数//
		const ChMath::Vector2Base<unsigned int> GetWindPos()const;

		const HINSTANCE GetInstance()const;

	public://UpdateFunction//

		ChStd::Bool Update();

	public:

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0);

		//WndProcedureを動的にするために外部にあるWndProcから見えるようにする//
		friend LRESULT CALLBACK ChWin::WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		//WIndCreaterにWindObjectのPrivate部分も見えるようにする//
		friend WindCreater;

	private://CreateBaseFunction//

		void CreateEnd(const int _nCmdShow);

	private://MemberValue//
		
		std::map<unsigned int, std::function<LRESULT(HWND,UINT,WPARAM,LPARAM)>> wndProc;
		HWND hWnd = nullptr;
		MSG msg = { 0 };

	};

	class WindCreater
	{
	public://ConstructorDestructor//

		WindCreater(HINSTANCE _ins) { Init(_ins); }

	public://Init And Release//

		void Init(HINSTANCE _ins) { hInst; }

	public://Set Function//

		void SetWindStyle(const unsigned int _style)
		{
			style = _style;
		}

		void SetWindStyle(const WindStyle* _style);

		void SetParentWind(const WindObject& _wObj)
		{
			parent = _wObj.GethWnd();
		}

		void SetParentWind(const HWND _wind)
		{
			parent = _wind;
		}

		void SetMenu(const HMENU _menu)
		{
			hMenu = _menu;
		}

		void SetInitPosition(const ChMath::Vector2Base<int>& _pos);

		void SetInitPosition(const int _x, const int _y);

		void SetInitSize(const ChMath::Vector2Base<int>& _size);

		void SetInitSize(const int _w, const int _h);

	public://Get Function//

		inline const ChMath::Vector2Base<int> GetPosition()const
		{
			return pos;
		}

		inline const ChMath::Vector2Base<int> GetSize()const
		{
			return size;
		}

	public://Create Functino//

		//Set Functionを先に行う//
		ChStd::Bool Create(WindObject* _out,const std::string& _appName,const std::string& _windClassName,const int _nShowCmd = 0);

		ChStd::Bool Create(WindObject* _out,const std::wstring& _appName,const std::wstring& _windClassName, const int _nShowCmd = 0);

	private://MemberValue//

		unsigned int style = 0;
		HWND parent = nullptr;
		HMENU hMenu = nullptr;
		HINSTANCE hInst = nullptr;
		LPVOID param = nullptr;
		ChMath::Vector2Base<int> pos = ChMath::Vector2Base<int>(0, 0);
		ChMath::Vector2Base<int> size = ChMath::Vector2Base<int>(100,100);

	};

}

#endif

#endif
