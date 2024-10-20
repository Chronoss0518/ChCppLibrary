#ifdef _WINDOWS_

#ifndef Ch_Win_Windows_h
#define Ch_Win_Windows_h

#include<string>

#ifndef Ch_ToRelativePath_Function_EXPLICIT_DECLARATION
#define Ch_ToRelativePath_Function_EXPLICIT_DECLARATION(_CharType, _AorW) \
std::basic_string<_CharType> ToRelativePath##_AorW##(const std::basic_string<_CharType>& _path)
#endif

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/WindObject/ChWindObject.h"
#include"../../WindowsObject/WindClassObject/ChWindClassObject.h"

namespace ChWin
{
	//":\\"//
	CH_NUMBER_FUNCTION_BASE(GetWinPathCutChara1);

	//":/"//
	CH_NUMBER_FUNCTION_BASE(GetWinPathCutChara2);

	//"../"//
	CH_NUMBER_FUNCTION_BASE(GetWinPathBackChara);
}


namespace ChSystem
{
	//Windowsで作成されたWindとWindowsに関する入出力などを管理した、//
	//WIndows全体の管理クラス//
	template<typename CharaType>
	class WindowsBase :public BaseSystem
	{
	protected://Set Functions//

		//Windowsでのキー全体をチェックするための関数//
		void SetKeyCode()override;

	public://GetFunction//

		//Windハンドルの取得//
		virtual HWND GethWnd(void) const = 0;

		virtual HINSTANCE GetInstance(void)const = 0;

		//メッセージの値を返す関数//
		virtual const LPMSG GetReturnMassage(void) const = 0;

		unsigned long GetNowTime()override { return timeGetTime(); }

	protected://Update Functions//

		void Update(HWND _hWnd);

	public://Is Function//

		//標準のカーソルの表示フラグ//
		inline void IsCursollShou(const bool _f) { ShowCursor(_f); }

	protected://Member Value//

		bool isKeyUpdate;

		HINSTANCE inst = nullptr;
	};

	class WindowsA :public WindowsBase<char>
	{
	public:

		virtual ~WindowsA() { Release(); }

	public://Init And Release//

		//Windの生成(stringVer)//
		void Init(
			const ChWin::WindCreater& _creater,
			const char* _appName,
			const char* _windClassName,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _className,
			const unsigned long _dwStyle,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const int _windWidth,
			const int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const int _windWidth,
			const int _windHeight,
			const int _initWindPosX,
			const int _initWindPosY,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _className,
			const unsigned long _dwStyle,
			const int _initWindPosX,
			const int _initWindPosY,
			const int _windWidth,
			const int _windHeight,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		//Windの解放//
		void Release()override;

	public://SetFunction//

		inline void SetDefaultWinProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject.SetDefaultWindProcedure(_proce); }

		inline void SetWinProcedure(const unsigned int _windowMessage, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject.SetWindProcedure(_windowMessage, _proce); }
		
		inline void SetEnableFlg(const bool _flg) { wndObject.SetEnableFlg(_flg); }

	public://GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const override { return wndObject.GethWnd(); }

		inline HINSTANCE GetInstance(void)const override { return wndObject.GetInstance(); }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const override { return wndObject.GetReturnMassage(); }

		ChWin::WindObjectA& GetWindObject() { return wndObject; }

	public://Is Function//

		//WindMassageを確認する関数//
		bool IsUpdate()override;

		inline bool IsCursorPosOnWindow() { return wndObject.IsCursorPosOnWindow(); }

		inline void InvalidateWind(const bool _clear = true) { wndObject.InvalidateWind(_clear); }

	protected://Member Value//

		ChWin::WindObjectA wndObject;
	};

	class WindowsW :public WindowsBase<wchar_t>
	{
	public:

		virtual ~WindowsW() { Release(); }

	public://Init And Release//

		//Windの生成(stringVer)//
		void Init(
			const ChWin::WindCreater& _creater,
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _className,
			const unsigned long _dwStyle,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const int _windWidth,
			const int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const int _windWidth,
			const int _windHeight,
			const int _initWindPosX,
			const int _initWindPosY,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _className,
			const unsigned long _dwStyle,
			const int _initWindPosX,
			const int _initWindPosY,
			const int _windWidth,
			const int _windHeight,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		//Windの解放//
		void Release()override;

	public://SetFunction//

		inline void SetDefaultWinProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject.SetDefaultWindProcedure(_proce); }

		inline void SetWinProcedure(const unsigned int _windowMessage, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject.SetWindProcedure(_windowMessage, _proce); }

		inline void SetEnableFlg(const bool _flg) { wndObject.SetEnableFlg(_flg); }

	public://GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const override { return wndObject.GethWnd(); }

		inline HINSTANCE GetInstance(void)const override { return wndObject.GetInstance(); }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const override { return wndObject.GetReturnMassage(); }

		ChWin::WindObjectW& GetWindObject() { return wndObject; }

	public://Is Function//

		//WindMassageを確認する関数//
		bool IsUpdate()override;

		inline bool IsCursorPosOnWindow() { return wndObject.IsCursorPosOnWindow(); }

		inline void InvalidateWind(const bool _clear = true) { wndObject.InvalidateWind(_clear); }

	protected://Member Value//

		ChWin::WindObjectW wndObject;
	};

	using Windows =
#ifdef UNICODE
		WindowsW;
#else
		WindowsA;
#endif
}

namespace ChWin
{
	Ch_ToRelativePath_Function_EXPLICIT_DECLARATION(char, A);

	Ch_ToRelativePath_Function_EXPLICIT_DECLARATION(wchar_t, W);

	inline ChINTPOINT GetScreenSize()
	{
		return ChINTPOINT(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}

	inline HINSTANCE GetInstanceHandle()
	{
#ifdef UNICODE
		return GetModuleHandleW(nullptr);
#else
		return GetModuleHandleA(nullptr);
#endif
	}
}

#endif
//CopyRight Chronoss0518 2018/08

#endif