#ifdef _WINDOWS_

#ifndef Ch_Game_Windows_h
#define Ch_Game_Windows_h

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/WindObject/ChWindObject.h"
#include"../../WindowsObject/WindClassObject/ChWindClassObject.h"

namespace ChSystem
{
	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);


	//Windowsで作成されたWindとWindowsに関する入出力などを管理した、//
	//WIndows全体の管理クラス//
	class Windows :public BaseSystem
	{
	public:

		Windows() {};

		virtual ~Windows()
		{
			Release();
		}


		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Windの生成(stringVer)//
		void Init(
			const std::string& _appName,
			const std::string& _windClassName,
			const ChINTPOINT& _windSize,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::string& _appName,
			const std::string& _windClassName,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::string& _appName,
			const std::string& _className,
			const unsigned long _dwStyle,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		//Windの生成(stringVer)//
		void Init(
			const std::string& _appName,
			const std::string& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::string& _appName,
			const std::string& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const int _initWindPosX,
			const int _initWindPosY,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const ChWin::WindCreater& _creater,
			const std::string& _appName,
			const std::string& _windClassName,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::string& _appName,
			const std::string& _className,
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

		//Windの生成(wstringVer)//
		void Init(
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const ChINTPOINT& _windSize,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::wstring& _appName,
			const std::wstring& _className,
			const unsigned long _dwStyle,
			const ChINTPOINT& _windSize,
			const ChINTPOINT& _windPos,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		//Windの生成(wstringVer)//
		void Init(
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const int _initWindPosX,
			const int _initWindPosY,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const ChWin::WindCreater& _creater,
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::wstring& _appName,
			const std::wstring& _className,
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

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetDefaultWinProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce)
		{
			wndObject.SetDefaultWindProcedure(_proce);
		}

		inline void SetWinProcedure(const unsigned int _windowMessage ,const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce)
		{
			wndObject.SetWindProcedure(_windowMessage, _proce);
		}

		inline void SetEnableFlg(const bool _flg) { wndObject.SetEnableFlg(_flg); }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const { return wndObject.GethWnd(); }

		inline HINSTANCE GetInstance(void)const { return wndObject.GetInstance(); }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return wndObject.GetReturnMassage(); }

		unsigned long GetNowTime()override { return timeGetTime(); }

		ChWin::WindObject& GetWindObject() { return wndObject; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//標準のカーソルの表示フラグ//
		inline void IsCursollShou(const bool _f) { ShowCursor(_f); }

		//キーを押した際のチェックを行う関数//
		bool IsPushKey(const int _key)override;

		//キーを押した際に長押しを含んだのチェックを行う関数//
		bool IsPushKeyNoHold(const int _key)override;

		//ポーズ中かどうかを判断する関数。//
		//第一引数はポーズへ移行するボタン//
		//戻り値がTrueだった場合はポーズ中//
		bool IsPause(const int _key)override;

		//WindMassageを確認する関数//
		bool IsUpdate()override;

		inline bool IsCursorPosOnWindow() { return wndObject.IsCursorPosOnWindow(); }

		///////////////////////////////////////////////////////////////////////////////////

		void ErrerMessage(
			const std::string& _mainStr
			, const std::string& _subStr)override
		{
			WMessageA(_mainStr, _subStr);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//メッセージボックス用関数//
		inline void WMessageA(
			const std::string& _mainStr
			, const std::string& _subStr)
		{
			if (ChPtr::NullCheck(wndObject.GethWnd()))return;

			MessageBoxA(
				wndObject.GethWnd()
				, &_mainStr[0]
				, &_subStr[0]
				, MB_OK);

		}

		//メッセージボックス用関数//
		inline void WMessageW(
			const std::wstring& _mainStr
			, const std::wstring& _subStr)
		{
			if (ChPtr::NullCheck(wndObject.GethWnd()))return;

			MessageBoxW(
				wndObject.GethWnd()
				, &_mainStr[0]
				, &_subStr[0]
				, MB_OK);

		}

		inline void InvalidateWind(const bool _clear = true)
		{
			wndObject.InvalidateWind(_clear);
		}

		friend LRESULT CALLBACK ChSystem::WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		//Windowsでのキー全体をチェックするための関数//
		void SetKeyCode();

		///////////////////////////////////////////////////////////////////////////////////

		bool isKeyUpdate;

		HINSTANCE inst = nullptr;
		ChWin::WindObject wndObject;
		ChWin::WindClassObject cObject;


	};

}

namespace ChWin
{

	std::string ToRelativePath(const std::string& _path);

	inline ChINTPOINT GetScreenSize()
	{
		return ChINTPOINT(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}
}

#endif
//CopyRight Chronoss0518 2018/08

#endif