#ifdef _WINDOWS_

#ifndef Ch_Win_WO_h
#define Ch_Win_WO_h

#ifdef CRT

#include<map>
#include<string>
#include<functional>

#endif

#ifndef CH_WIND_OBJECT_INHERITANCE_FUNCTIONS
#define CH_WIND_OBJECT_INHERITANCE_FUNCTIONS(_AorW,_CharaType) \
void ChWin::WindObject##_AorW##::Release(){\
	if (!IsInit())return;\
	if (ChPtr::NotNullCheck(windProcedures)){\
		delete windProcedures;\
		windProcedures = nullptr;}\
	if(ChPtr::NotNullCheck(hWnd)){\
		SetWindowLongPtr##_AorW##(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));\
		DestroyWindow(hWnd);\
		hWnd = nullptr;}\
	SetInitFlg(false);}\
\
void ChWin::WindObject##_AorW##::SetWindID(LONG_PTR _IDPtr){\
	if (!IsInit())return;\
	SetWindowLongPtr##_AorW##(hWnd, GWLP_ID, _IDPtr);}\
\
LONG_PTR ChWin::WindObject##_AorW##::GetWindID(){\
	if (!IsInit())return 0;\
	return GetWindowLongPtr##_AorW##(hWnd, GWLP_ID);}\
\
const HINSTANCE ChWin::WindObject##_AorW##::GetInstance()const{ return (HINSTANCE)GetWindowLongPtr##_AorW##(hWnd, GWLP_HINSTANCE); }\
\
LPARAM ChWin::WindObject##_AorW##::Send(const unsigned int _msg, WPARAM _wParam, LPARAM _lParam){\
	LPARAM res = _lParam;\
	if (!*this)return res;\
	WPARAM wParam = _wParam;\
	SendMessage##_AorW##(hWnd, _msg, wParam, res);\
	return res;}\
\
bool ChWin::WindCreater::Create(WindObject##_AorW##& _out, const _CharaType* _appName, const _CharaType* _windClassName, const int _nShowCmd)const{\
	_out.hWnd = Create(_appName,_windClassName);\
	if (ChPtr::NullCheck(_out.hWnd))return false;\
	_out.CreateEnd(_nShowCmd);\
	_out.parent = parent;\
	return true;}\
\
HWND ChWin::WindCreater::Create(const _CharaType* _appName, const _CharaType* _windClassName)const {\
		return CreateWindowEx##_AorW##(\
			exStyle, \
			_windClassName, \
			_appName, \
			style, \
			pos.x, pos.y, \
			size.w, size.h, \
			parent, \
			hMenu, \
			hInst, \
			param);}\
\
void ChWin::WindObject##_AorW##::CreateEnd(const int _nCmdShow){\
	WindObjectBase::CreateEnd(_nCmdShow);\
	SetWindowLongPtr##_AorW##(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windProcedures));}\
\
bool ChWin::WindObject##_AorW##::Update() {\
	if (!IsInit())return false;\
	UpdateWindow(hWnd);\
	if (!PeekMessage##_AorW##(&msg, nullptr, 0, 0, PM_NOREMOVE))return true;\
	if ((GetMessage##_AorW##(&msg, nullptr, 0, 0)) <= 0)return false;\
	TranslateMessage(&msg);\
	DispatchMessage##_AorW##(&msg);\
	return true;}
#endif

#include"../../BasePack/ChPtr.h"

#include"../../ClassParts/ChCPInitializer.h"

#include"../PackData/ChPoint.h"

namespace ChSystem
{
	class WindowsA;
	class WindowsW;
}

namespace ChWin
{
	LRESULT CALLBACK BaseWndProc(
		HWND _hWnd,
		UINT _uMsg,
		WPARAM _wParam,
		LPARAM _lParam,
		LONG_PTR(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int),
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

		struct WindProcedureCRT
		{
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

	public:

		WindProcedure();
		
		virtual ~WindProcedure();

	public:

		void Init();

	public:

#ifdef CRT
		//このウィンドウが子ウィンドウ以外の場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline virtual void SetWindProcedure(const unsigned long _message, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc) { (value->wndProc)[_message] = _proc; }

		//登録されたどのメッセージも受け取らなかった場合に呼ばれる関数//
		inline void SetDefaultWindProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proc) { value->defaultWindProc = _proc; }

		//子ウィンドウが動作して呼ばれたときに実行される関数//
		//このウィンドウが子ウィンドウの場合のみ実行される//
		//_messageにはWM_やメッセージプロシージャ―が受け取れる方にしてください//
		inline void SetChildWindProcedure(const unsigned long _message, const std::function<void(HWND, UINT)>& _proc) { (value->childWindProc)[_message] = _proc; }
#endif
	public:

		LRESULT UpdateProcedure(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam, LONG_PTR(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int));

	private:

		LRESULT DefaultWindProc(HWND, UINT, WPARAM, LPARAM);

	private:

		WindProcedureCRT* value;

	};

	//WindowsAPIの内、Windowの管理するクラス//
	class WindObjectBase :public ChCp::Initializer
	{
	public://InitAndRelease//

		void Init(HWND _hWnd, const int _nShowCmd);

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
			if (ChPtr::NullCheck(windProcedures))return;
			windProcedures->SetChildWindProcedure(_message, _proc);
		}
#endif
		void SetWindPos(const unsigned int _x, const unsigned int _y, const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER);

		inline void SetWindPos(const ChPOINT& _pos, const unsigned int _flgs = SWP_NOSIZE | SWP_NOZORDER) { SetWindPos(_pos.x, _pos.y, _flgs); }

		void SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER);

		inline void SetWindSize(const ChPOINT& _size, const unsigned int _flgs = SWP_NOMOVE | SWP_NOZORDER) { SetWindSize(_size.w, _size.h, _flgs); }

		void SetWindRect(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h, const unsigned int _flgs = SWP_NOZORDER);

		inline void SetWindRect(const RECT& _rec, const unsigned int _flgs = SWP_NOZORDER) { SetWindRect(_rec.left, _rec.top, _rec.right - _rec.left, _rec.bottom - _rec.top, _flgs); }

		//ウィンドウの有効・無効を切り替える//
		inline void SetEnableFlg(const bool _flg) { EnableWindow(hWnd, _flg); }

		virtual void SetWindID(LONG_PTR _IDPtr) = 0;

	public://GetFunction//

		virtual LONG_PTR GetWindID() = 0;

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

	protected://CreateBaseFunction//

		virtual void CreateEnd(const int _nCmdShow);

	protected://MemberValue//

		HWND hWnd = nullptr;
		HWND parent = nullptr;
		MSG msg = { 0 };

		WindProcedure* windProcedures = nullptr;

	};

	class WindObjectA : public WindObjectBase
	{
	public:

		friend WindCreater;
		friend ChSystem::WindowsA;

	public://ConstructorDestructor//

		~WindObjectA() { Release(); }

	public://InitAndRelease//

		void Init(HWND _hWnd, const int _nShowCmd);

		void Release()override final;

	public://Set Functions//

		void SetWindID(LONG_PTR _IDPtr)override final;

	public://Get Functions//

		LONG_PTR GetWindID()override final;

		const HINSTANCE GetInstance()const override final;

	public://Update Functions//

		bool Update()override final;

	public://Other Functions//

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0)override final;

	protected://CreateBaseFunction//

		void CreateEnd(const int _nCmdShow)override;

	};

	class WindObjectW : public WindObjectBase
	{
	public:

		friend WindCreater;
		friend ChSystem::WindowsW;

	public://ConstructorDestructor//

		~WindObjectW() { Release(); }

	public://InitAndRelease//

		void Init(HWND _hWnd, const int _nShowCmd);

		void Release()override final;

	public://Set Functions//

		void SetWindID(LONG_PTR _IDPtr)override final;

	public://Get Functions//

		LONG_PTR GetWindID()override final;

		const HINSTANCE GetInstance()const override final;

	public://Update Functions//

		bool Update()override final;

	public://Other Functions//

		//メッセージを送る。戻り値は変更があった場合の数値//
		LPARAM Send(const unsigned int _msg, WPARAM _wParam = 0, LPARAM _lParam = 0)override final;

	protected://CreateBaseFunction//

		void CreateEnd(const int _nCmdShow)override;

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
		bool Create(WindObjectA& _out, const char* _appName, const char* _windClassName, const int _nShowCmd = true)const;

		bool Create(WindObjectW& _out, const wchar_t* _appName, const wchar_t* _windClassName, const int _nShowCmd = true)const;

		HWND Create(const char* _appName, const char* _windClassName)const;

		HWND Create(const wchar_t* _appName, const wchar_t* _windClassName)const;

	private://MemberValue//

		unsigned long exStyle = 0;
		unsigned int style = 0;
		HWND parent = nullptr;
		HMENU hMenu = nullptr;
		HINSTANCE hInst = nullptr;
		LPVOID param = nullptr;
		ChINTPOINT pos = ChINTPOINT(0, 0);
		ChINTPOINT size = ChINTPOINT(100, 100);

	};

	using WindObject =
#ifdef UNICODE
		WindObjectW;
#else
		WindObjectA;
#endif
}

#ifdef CRT

ChWin::WindProcedure::WindProcedure()
{
	value = new WindProcedureCRT();
}

ChWin::WindProcedure::~WindProcedure()
{
	delete value;
}

void ChWin::WindProcedure::Init()
{
	value->wndProc[WM_DESTROY] = [&](
		HWND _hWnd,
		UINT _uMsg,
		WPARAM _wParam,
		LPARAM _lParam)->LRESULT
		{
			PostQuitMessage(0);
			return 0;
		};
}

LRESULT ChWin::WindProcedure::UpdateProcedure(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam, LONG_PTR(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int))
{

	auto it = value->wndProc.find(_uMsg);
	if (it != (value->wndProc).end())
	{
		LRESULT res;
		res = (it)->second(_hWnd, _uMsg, _wParam, _lParam);
		if (_uMsg != WM_COMMAND && _uMsg != WM_SYSCOMMAND)return res;
	}

	if (_uMsg != WM_COMMAND && _uMsg != WM_SYSCOMMAND)return DefaultWindProc(_hWnd, _uMsg, _wParam, _lParam);

	if (_lParam <= 0)
	{
		auto param = LOWORD(_wParam);

		auto it = value->wndProc.find(param);
		if (it != (value->wndProc).end())
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
			if (!child->value->childWindProc.empty())
			{
				auto cit = child->value->childWindProc.find(HIWORD(_wParam));
				if (cit != (child->value->childWindProc).end())
				{
					(cit)->second((HWND)LOWORD(_wParam), HIWORD(_wParam));
				}
			}
			child->DefaultWindProc(_hWnd, _uMsg, _wParam, _lParam);

			return 0;
		}
	}

	return DefaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
}

LRESULT ChWin::WindProcedure::DefaultWindProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	return value->defaultWindProc(_hWnd, _uMsg, _wParam, _lParam);
}

void ChWin::WindObjectBase::CreateEnd(const int _nCmdShow)
{
	windProcedures = new WindProcedure();
	windProcedures->Init();

	SetInitFlg(true);
	SetWindID(reinterpret_cast<LONG_PTR>(hWnd));

	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);
}

CH_WIND_OBJECT_INHERITANCE_FUNCTIONS(A, char);

CH_WIND_OBJECT_INHERITANCE_FUNCTIONS(W, wchar_t);

#endif

#endif

#endif
