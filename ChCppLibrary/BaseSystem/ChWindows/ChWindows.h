#ifdef _WINDOWS_

#ifndef Ch_Win_Windows_h
#define Ch_Win_Windows_h

#ifdef CRT

#include<string>

#endif

#ifndef CH_WINDOWS_INIT_FUNCTION
#define CH_WINDOWS_INIT_FUNCTION(_AorW,_CharaType) \
void ChSystem::Windows##_AorW##::Init(\
	const ChWin::WindCreater& _creater,\
	const _CharaType##* _appName,\
	const _CharaType##* _windClassName,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	wndObject->hWnd = _creater.Create(_appName, _windClassName);\
	if(ChPtr::NullCheck(wndObject->hWnd))return;\
	wndObject->CreateEnd(_nCmdShow);\
	inst = _hInst;\
	buttonList->SetSize((256 / 8) + 1);\
	isNowPush->SetSize((256 / 8) + 1);\
	SetInitFlg(true);}\
\
void ChSystem::Windows##_AorW##::Init(\
	const _CharaType* _appName,\
	const _CharaType* _windClassName,\
	const ChINTPOINT& _windSize,\
	const ChINTPOINT& _windPos,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	ChINTPOINT pos = _windPos;\
	ChINTPOINT size = _windSize;\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);\
	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW##::Init(\
	const _CharaType* _appName,\
	const _CharaType* _className,\
	const unsigned long _dwStyle,\
	const ChINTPOINT& _windSize,\
	const ChINTPOINT& _windPos,\
	HINSTANCE _hInst,\
	const int _nCmdShow,\
	const unsigned long _exStyle,\
	HWND _parent,\
	HMENU _hMenu,\
	LPVOID _param){\
	ChINTPOINT pos = _windPos;\
	ChINTPOINT size = _windSize;\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(_dwStyle);\
	creater.SetEXStyle(_exStyle);\
	creater.SetParentWind(_parent);\
	creater.SetMenu(_hMenu);\
	creater.SetParam(_param);\
	Init(creater, _appName, _className, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW##::Init(\
	const _CharaType* _appName,\
	const _CharaType* _windClassName,\
	const int _windWidth,\
	const int _windHeight,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(10, 10);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);\
	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW##::Init(\
	const _CharaType* _appName,\
	const _CharaType* _windClassName,\
	const int _windWidth,\
	const int _windHeight,\
	const int _initWindPosX,\
	const int _initWindPosY,\
	const HINSTANCE _hInst,\
	const int _nCmdShow){\
	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);\
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_GROUP);\
	Init(creater, _appName, _windClassName, _hInst, _nCmdShow);}\
\
void ChSystem::Windows##_AorW##::Init(\
	const _CharaType* _appName,\
	const _CharaType* _className,\
	const unsigned long _dwStyle,\
	const int _initWindPosX,\
	const int _initWindPosY,\
	const int _windWidth,\
	const int _windHeight,\
	HINSTANCE _hInst,\
	const int _nCmdShow,\
	const unsigned long _exStyle,\
	HWND _parent,\
	HMENU _hMenu,\
	LPVOID _param){\
	auto pos = ChMath::Vector2Base<int>(_initWindPosX, _initWindPosY);\
	auto size = ChMath::Vector2Base<int>(_windWidth, _windHeight);\
	pos.val.Abs();\
	size.val.Abs();\
	ChWin::WindCreater creater = ChWin::WindCreater(_hInst);\
	creater.SetInitPosition(pos.x, pos.y);\
	creater.SetInitSize(size.w, size.h);\
	creater.SetWindStyle(_dwStyle);\
	creater.SetEXStyle(_exStyle);\
	creater.SetParentWind(_parent);\
	creater.SetMenu(_hMenu);\
	creater.SetParam(_param);\
	Init(creater, _appName, _className, _hInst, _nCmdShow);}
#endif

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/WindObject/ChWindObject.h"
#include"../../WindowsObject/WindClassObject/ChWindClassObject.h"

#ifndef CH_Win_Path_Cut_CHARA1_FUNCTION
#define CH_Win_Path_Cut_CHARA1_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetWinPathCutChara1,type)
#endif

#ifndef CH_Win_Path_Cut_CHARA2_FUNCTION
#define CH_Win_Path_Cut_CHARA2_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetWinPathCutChara2,type)
#endif

#ifndef CH_Win_Path_Back_CHARA_FUNCTION
#define CH_Win_Path_Back_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetWinPathBackChara,type)
#endif

namespace ChWin
{
#ifdef CRT

	CH_TO_NUMBER_FUNCTION(CH_Win_Path_Cut_CHARA1_FUNCTION, ":\\");

	CH_TO_NUMBER_FUNCTION(CH_Win_Path_Cut_CHARA2_FUNCTION, ":/");

	CH_TO_NUMBER_FUNCTION(CH_Win_Path_Back_CHARA_FUNCTION, "../");

#endif
}

#ifndef Ch_ToRelativePath_Function
#define Ch_ToRelativePath_Function(_CharType, _AorW) \
std::basic_string<_CharType> ToRelativePath##_AorW##(const std::basic_string<_CharType>& _path){\
	if (_path.find(ChWin::GetWinPathCutChara1<_CharType>()) == _path.npos && _path.find(ChWin::GetWinPathCutChara2<_CharType>()) == _path.npos)return _path;\
	std::basic_string<_CharType> tmp;\
	std::basic_string<_CharType> res = _path;\
	{_CharType tmp2[MAX_PATH];\
	GetCurrentDirectory##_AorW##(MAX_PATH, tmp2);\
	tmp = tmp2;}\
\
	{\
		while (1){\
			size_t tmpLen = tmp.find(ChStd::GetYenChara<_CharType>(), 0);\
			if (tmpLen == tmp.npos)break;\
			tmp.replace(tmpLen, 1, ChStd::GetSlashChara<_CharType>());}\
		while (1){\
			size_t tmpLen = _path.find(ChStd::GetYenChara<_CharType>(), 0);\
			if (tmpLen == _path.npos)break;\
			res.replace(tmpLen, 1, ChStd::GetSlashChara<_CharType>());}\
\
		std::basic_string<_CharType> tmpBackChar = ChStd::GetZeroChara<_CharType>();\
\
		while (1){\
			size_t tmpLen = res.find(tmp);\
			if (tmpLen != res.npos)break;\
			tmpLen = tmp.rfind(ChStd::GetSlashChara<_CharType>(), tmp.length());\
			tmp.replace(tmpLen, tmp.length() - tmpLen, ChStd::GetZeroChara<_CharType>());\
			tmpBackChar += ChWin::GetWinPathBackChara<_CharType>();}\
		res.replace(0, tmp.length() + 1, ChStd::GetZeroChara<_CharType>());\
		res = tmpBackChar + res;}\
	return res;}\

#endif


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

		WindowsA() 
		{
#ifdef CRT
			wndObject = new ChWin::WindObjectA();
#endif
		};

		virtual ~WindowsA()
		{
#ifdef CRT
			delete wndObject;
#endif
			Release();
		}

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

#ifdef CRT
		inline void SetDefaultWinProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject->SetDefaultWindProcedure(_proce); }

		inline void SetWinProcedure(const unsigned int _windowMessage, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject->SetWindProcedure(_windowMessage, _proce); }
#endif
		inline void SetEnableFlg(const bool _flg) { wndObject->SetEnableFlg(_flg); }

	public://GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const override { return wndObject->GethWnd(); }

		inline HINSTANCE GetInstance(void)const override { return wndObject->GetInstance(); }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const override { return wndObject->GetReturnMassage(); }

		ChWin::WindObjectA& GetWindObject() { return *wndObject; }

	public://Is Function//

		//WindMassageを確認する関数//
		bool IsUpdate()override;

		inline bool IsCursorPosOnWindow() { return wndObject->IsCursorPosOnWindow(); }

		inline void InvalidateWind(const bool _clear = true) { wndObject->InvalidateWind(_clear); }

	protected://Member Value//

		ChWin::WindObjectA* wndObject = nullptr;
	};

	class WindowsW :public WindowsBase<wchar_t>
	{
	public:

		WindowsW() 
		{
#ifdef CRT
			wndObject = new ChWin::WindObjectW();
#endif
		};

		virtual ~WindowsW()
		{
			Release();
#ifdef CRT
			delete wndObject;
#endif
		}

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

#ifdef CRT
		inline void SetDefaultWinProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject->SetDefaultWindProcedure(_proce); }

		inline void SetWinProcedure(const unsigned int _windowMessage, const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce) { wndObject->SetWindProcedure(_windowMessage, _proce); }
#endif
		inline void SetEnableFlg(const bool _flg) { wndObject->SetEnableFlg(_flg); }

	public://GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const override { return wndObject->GethWnd(); }

		inline HINSTANCE GetInstance(void)const override { return wndObject->GetInstance(); }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const override { return wndObject->GetReturnMassage(); }

		ChWin::WindObjectW& GetWindObject() { return *wndObject; }

	public://Is Function//

		//WindMassageを確認する関数//
		bool IsUpdate()override;

		inline bool IsCursorPosOnWindow() { return wndObject->IsCursorPosOnWindow(); }

		inline void InvalidateWind(const bool _clear = true) { wndObject->InvalidateWind(_clear); }

	protected://Member Value//

		ChWin::WindObjectW* wndObject = nullptr;
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
#ifdef CRT
	Ch_ToRelativePath_Function(char, A);

	Ch_ToRelativePath_Function(wchar_t, W);
#endif

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

#ifdef CRT


CH_WINDOWS_INIT_FUNCTION(A, char);

CH_WINDOWS_INIT_FUNCTION(W, wchar_t);

#endif

#endif
//CopyRight Chronoss0518 2018/08

#endif