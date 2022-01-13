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

		//Windowに枠を付ける//
		void SetBorder();

		//Windowにタイトルを付ける//
		void SetCaption();

		//Windowに子階層属性を付ける//
		void SetChild();

		//Window配下のWindowの描画範囲を描画しないようにする//
		void SetClipChildren();

		//Window配下のWindow同士が重なっている部分を描画しないようにする//
		void SetClipSiblings();

		//Windowは初期時点で無効状態にする//
		void SetDisabled();

		//Windowにダイアログボックスと同じ境界線を付ける//
		void SetDLGFrame();

		//WindowがControlできるグループの最初であることを定義する//
		void SetGroup();

		//Windowに水平のスクロールバーを付ける//
		void SetHScroll();

		//Windowは最初からサイズが最大状態で表示される//
		void SetMaxmize();

		//Windowに最大化ボタンを付ける//
		void SetMaximaizeBox();

		//Windowは最初からサイズが最小状態で表示される//
		void SetMinimize();

		//Windowに最小化ボタンを付ける//
		void SetMinimizeBox();

		//Windowにタイトルバーと境界線を持ったWindowを重ねる//
		void SetOverlapped();

		//OverlappedにCaption,SysMenu,SyzeBox,MinimizeBox,MaximizeBoxを追加した複合スタイル//
		void SetOverlappedWindow();

		//Windowをポップアップウィンドウにする。こちらはChildと併用できない//
		void SetPopup();

		//PopupにBorder,SysMenuを追加した複合スタイル//
		void SetPopupWindow();

		//Windowにサイズを変更可能な境界線を付ける//
		void SetSizeBox();

		//Windowのタイトルバーにウィンドウメニューを付ける//
		void SetSysMenu();

		//WindowはUserがTabキーを押した際にフォーカスを受け取れるようにする//
		void SetTabStop();

		//Windowが最初から表示されるようにする//
		void SetVisible();

		//Windowに垂直スクロールバーを付ける//
		void SetVScroll();

		///////////////////////////////////////////////////////////////////////////////////
		//Get Function//

		inline unsigned long GetStyle()const  { return windStyle; }

		///////////////////////////////////////////////////////////////////////////////////

		//セットされていたStyleを0にする//
		inline void Clear() { windStyle = 0; }

	private:

		unsigned long windStyle = 0;

	};


	//WindowsAPIの内、Windowの作成と管理を司るクラス//
	class WindObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{
			CreateWindowWChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, WS_OVERLAPPEDWINDOW
				| WS_CLIPCHILDREN
				| WS_GROUP
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{
			CreateWindowWChar(
				_appName
				, _windClassName
				, _windSize.w
				, _windSize.h
				, WS_OVERLAPPEDWINDOW
				| WS_CLIPCHILDREN
				| WS_GROUP
				, _hInst
				, _windPos.x
				, _windPos.y);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, _windStyle
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windSize.w
				, _windSize.h
				, _windStyle
				, _hInst
				, _windPos.x
				, _windPos.y);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, _windStyle.GetStyle()
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windSize.w
				, _windSize.h
				, _windStyle.GetStyle()
				, _hInst
				, _windPos.x
				, _windPos.y);
		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{
			CreateWindowChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, WS_OVERLAPPEDWINDOW
				| WS_CLIPCHILDREN
				| WS_GROUP
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const { return hWnd; }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Windowのサイズを取得する関数//
		inline const ChMath::Vector2Base<unsigned int> GetWindSize()const { return windSize; }

		//Windowの左上の位置を取得する関数//
		inline const ChMath::Vector2Base<unsigned int> GetWindPos()const { return windPos; }

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

	private:

		void SetRegister();

		///////////////////////////////////////////////////////////////////////////////////

		void CreateWindowWChar(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos,
			const unsigned int _windYPos);

		void CreateWindowChar(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos,
			const unsigned int _windYPos);

		///////////////////////////////////////////////////////////////////////////////////



		HWND hWnd = nullptr;
		MSG msg = {0};
		ChMath::Vector2Base<unsigned int> windSize;
		ChMath::Vector2Base<unsigned int> windPos;
	};

}

#endif

#endif
