#ifdef _WINDOWS_

#ifndef Ch_Win_WCls_h
#define Ch_Win_WCls_h

namespace ChWin
{
	//WindowStyleを管理するクラス//
	class WindStyle
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//Set Function//

		inline void SetStyle(const unsigned long _windStyles) { windStyle = _windStyles; }

		void SetBorder();

		void SetCaption();

		void SetChild();

		void SetClipChildren();

		void SetClipSiblings();

		void SetDisabled();

		void SetDLGFrame();

		void SetGroup();

		void SetHScroll();

		void SetMaxmize();

		void SetMaximaizeBox();

		void SetMinimize();

		void SetMinimizeBox();

		void SetOverlapped();

		void SetOverlappedWindow();

		void SetPopup();

		void SetSizeBox();

		void SetSysMenu();

		void SetTabStop();

		void SetVisible();

		void SetVScroll();

		///////////////////////////////////////////////////////////////////////////////////
		//Get Function//

		inline unsigned long GetStyle() { return windStyle; }

		///////////////////////////////////////////////////////////////////////////////////

		void Clear();

	private:

		unsigned long windStyle = 0;


	};


	//WindowsAPIの内、Windowの作成と管理を司るクラス//
	class WindObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const { return hWnd; }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Windowのサイズを取得する関数//
		inline const ChMath::Vector2Base<unsigned int> GetWindSize()const { return windSize; }

		///////////////////////////////////////////////////////////////////////////////////

	private:

		HWND hWnd = nullptr;
		MSG msg = {0};
		ChMath::Vector2Base<unsigned int> windSize;
	};

}

#endif

#endif
