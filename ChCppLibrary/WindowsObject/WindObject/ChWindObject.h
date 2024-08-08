#ifdef _WINDOWS_

#ifndef Ch_Win_WO_h
#define Ch_Win_WO_h

#ifdef CRT

#include<map>
#include<string>
#include<functional>

#endif


#include"../../BasePack/ChPtr.h"

#include"../../ClassParts/ChCPInitializer.h"

#include"../PackData/ChPoint.h"

namespace ChWin
{
	LRESULT CALLBACK BaseWndProc(
		HWND _hWnd,
		UINT _uMsg,
		WPARAM _wParam,
		LPARAM _lParam,
		LONG(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int),
		LRESULT(WINAPI* DefWindowProcFunction)(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM));

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

	class WindProcedure
	{
	public:

		void Init();

	public:

#ifdef CRT
		//このウィンドウが子ウィンドウ以外の場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline virtual void SetWindProcedure(const unsigned long _message, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc) { (wndProc)[_message] = _proc; }

		//登録されたどのメッセージも受け取らなかった場合に呼ばれる関数//
		inline void SetDefaultWindProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc) { defaultWindProc = _proc; }

		//子ウィンドウが動作して呼ばれたときに実行される関数//
		//このウィンドウが子ウィンドウの場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline void SetChildWindProcedure(const unsigned long _message, const std::function<void(HWND, UINT)>& _proc) { (childWindProc)[_message] = _proc; }
#endif
	public:

		LRESULT UpdateProcedure(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam, LONG(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int));

	private:

#ifdef CRT
		std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> defaultWindProc = [](
			HWND _hWnd,
			UINT _uMsg,
			WPARAM _wParam,
			LPARAM _lParam)->LRESULT
			{return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam); };

		std::map<unsigned int, std::function<void(HWND, UINT)>> childWindProc;

		std::map<unsigned int, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> wndProc;
#endif
	};

	//WindowsAPIの内、Windowの管理するクラス//
	class WindObjectBase :public ChCp::Initializer
	{
	public://InitAndRelease//

		void Init(HWND _hWnd,const int _nShowCmd);

		virtual void Release() = 0;

	public://SetFunction//
		
#ifdef CRT
		//このウィンドウが子ウィンドウ以外の場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline virtual void SetWindProcedure(const unsigned long _message, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc) 
		{
			if (ChPtr::NullCheck(windProcedures))return;
			windProcedures->SetWindProcedure(_message, _proc); 
		}

		//登録されたどのメッセージも受け取らなかった場合に呼ばれる関数//
		inline void SetDefaultWindProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc) 
		{
			if (ChPtr::NullCheck(windProcedures))return;
			windProcedures->SetDefaultWindProcedure(_proc); 
		}

		//子ウィンドウが動作して呼ばれたときに実行される関数//
		//このウィンドウが子ウィンドウの場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline void SetChildWindProcedure(const unsigned long _message, const std::function<void(HWND, UINT)>& _proc) 
		{
			if (ChPtr::NullCheck( windProcedures))return;
			windProcedures->SetChildWindProcedure(_message, _proc); 
		}
#endif
		void SetWindPos(const unsigned int _x, const unsigned int _y,const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER);

		inline void SetWindPos(const ChPOINT& _pos, const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER) { SetWindPos(_pos.x, _pos.y, _flgs); }

		void SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER);

		inline void SetWindSize(const ChPOINT& _size, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER) { SetWindSize(_size.w, _size.h, _flgs); }

		void SetWindRect(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOZORDER);

		inline void SetWindRect(const RECT& _rec, const unsigned int _flgs = SWP_NOZORDER) { SetWindRect(_rec.left, _rec.top, _rec.right - _rec.left, _rec.bottom - _rec.top, _flgs); }

		void SetEnableFlg(const bool _flg) { EnableWindow(hWnd, _flg); }

		virtual void SetWindID(long _IDPtr) = 0;

	public://GetFunction//

		virtual long GetWindID() = 0;

		//Windハンドルの取得//
		HWND GethWnd(void)const { return hWnd; }

		//メッセージの値を返す関数//
		const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Windowのサイズを取得する関数//
		const ChPOINT GetWindSize()const;

		//Windowの左上の位置を取得する関数//
		const ChPOINT GetWindPos()const;

		virtual const HINSTANCE GetInstance()const = 0;

	public://Is Functions//

		//ウィンドウの範囲内でクリックされたかを確認//
		bool IsCursorPosOnWindow();

	public://Update Functions//

		virtual bool Update() = 0;

	public://Other Functions//

		//メッセージを送る。戻り値は変更があった場合の数値//
		virtual LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0) = 0;

		//描画を行う前に以前の描画情報を全て消す命令と再描画命令を送る//
		void InvalidateWind(const bool _clear = true)
		{
			InvalidateRect(hWnd, nullptr, _clear);
			UpdateWindow(hWnd);
		}

		//WIndCreaterにWindObjectのPrivate部分も見えるようにする//
		friend WindCreater;

	protected://CreateBaseFunction//

		void CreateEnd(const int _nCmdShow);

	protected://MemberValue//
		
		WindProcedure* windProcedures = nullptr;

		HWND hWnd = nullptr;
		HWND parent = nullptr;
		MSG msg = { 0 };

	};

	class WindObjectA : public WindObjectBase
	{
	public://ConstructorDestructor//

		~WindObjectA() { Release(); }

	public://InitAndRelease//

		void Init(HWND _hWnd, const int _nShowCmd);

		void Release()override final;

	public://Set Functions//

		void SetWindID(long _IDPtr)override final;

	public://Get Functions//

		long GetWindID()override final;

		const HINSTANCE GetInstance()const override final;

	public://Update Functions//

		bool Update()override final;

	public://Other Functions//

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0)override final;

	};

	class WindObjectW : public WindObjectBase
	{
	public://ConstructorDestructor//

		~WindObjectW() { Release(); }

	public://InitAndRelease//

		void Init(HWND _hWnd, const int _nShowCmd);

		void Release()override final;

	public://Set Functions//

		void SetWindID(long _IDPtr)override final;

	public://Get Functions//

		long GetWindID()override final;

		const HINSTANCE GetInstance()const override final;

	public://Update Functions//

		bool Update()override final;

	public://Other Functions//

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0)override final;

	};

	class WindCreater
	{
	public://ConstructorDestructor//

		WindCreater(HINSTANCE _ins) { Init(_ins); }

	public://Init And Release//

		void Init(HINSTANCE _ins) { hInst = _ins; }

	public://Set Function//

		inline void SetWindStyle(const unsigned int _style) { style = _style; }

		void SetWindStyle(const WindStyle* _style);

		inline void SetEXStyle(const unsigned long _style) { exStyle = _style; }

		inline void SetParentWind(const WindObjectA& _wObj) { parent = _wObj.GethWnd(); }

		inline void SetParentWind(const WindObjectW& _wObj) { parent = _wObj.GethWnd(); }

		inline void SetParentWind(const HWND _wind) { parent = _wind; }

		inline void SetMenu(const HMENU _menu) { hMenu = _menu; }

		void SetInitPosition(const ChINTPOINT& _pos);

		void SetInitPosition(const int _x, const int _y);

		void SetInitSize(const ChINTPOINT& _size);

		void SetInitSize(const int _w, const int _h);

		void SetParam(LPVOID _param) { param = _param; }

	public://Get Function//

		inline const ChINTPOINT GetPosition()const { return pos; }

		inline const ChINTPOINT GetSize()const { return size; }

	public://Create Functino//

		//Set Functionを先に行う//
		bool Create(WindObjectA* _out, const char* _appName, const char* _windClassName, const int _nShowCmd = true)const;

		bool Create(WindObjectW* _out, const wchar_t* _appName, const wchar_t* _windClassName, const int _nShowCmd = true)const;

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

	using WindObject =
#ifdef UNICODE
		WindObjectW;
#else
		WindObjectA;
#endif
}

#ifdef CRT


void ChWin::WindProcedure::Init()
{
	wndProc[WM_DESTROY] = [&](
		HWND _hWnd,
		UINT _uMsg,
		WPARAM _wParam,
		LPARAM _lParam)->LRESULT
		{
			PostQuitMessage(0);
			return 0;
		};
}

LRESULT ChWin::WindProcedure::UpdateProcedure(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam, LONG(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int))
{

	auto it = wndProc.find(_uMsg);
	if (it != (wndProc).end())
	{
		LRESULT res;
		res = (it)->second(_hWnd, _uMsg, _wParam, _lParam);
		if (_uMsg != WM_COMMAND && _uMsg != WM_SYSCOMMAND)return res;
	}

	if (_uMsg != WM_COMMAND && _uMsg != WM_SYSCOMMAND)return defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);

	if (_lParam <= 0)
	{
		auto param = LOWORD(_wParam);

		auto it = wndProc.find(param);
		if (it != (wndProc).end())
		{
			(it)->second(_hWnd, _uMsg, _wParam, _lParam);
			return 0;
		}

	}
	else
	{
		auto child = ((ChWin::WindProcedure*)GetWindowLongPtrFunction((HWND)LOWORD(_wParam), GWLP_USERDATA));

		if (ChPtr::NotNullCheck(child))
		{
			if (!child->childWindProc.empty())
			{
				auto cit = child->childWindProc.find(HIWORD(_wParam));
				if (cit != (child->childWindProc).end())
				{
					(cit)->second((HWND)LOWORD(_wParam), HIWORD(_wParam));
				}
			}
			child->defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
			
			return 0;
		}
	}

	 return defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
}

void ChWin::WindObjectBase::CreateEnd(const int _nCmdShow)
{
	windProcedures = new WindProcedure();
	windProcedures->Init();

	SetInitFlg(true);
	SetWindID(reinterpret_cast<long>(hWnd));

	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);
}


#endif

#endif

#endif
