#ifdef _WINDOWS_

#ifndef Ch_Win_WOStyle_h
#define Ch_Win_WOStyle_h

namespace ChWin
{

	//WindowStyleを管理するクラス//
	class WindStyle
	{
	public://Add Function//

		//Windowに枠を付ける//
		inline void AddBorder() { windStyle |= WS_BORDER; }

		//Windowにタイトルを付ける//
		inline void AddCaption() { windStyle |= WS_CAPTION; }

		//Windowに子階層属性を付ける//
		inline void AddChild() { windStyle |= WS_CHILD; }

		//Window配下のWindowの描画範囲を描画しないようにする//
		inline void AddClipChildren() { windStyle |= WS_CLIPCHILDREN; }

		//Window配下のWindow同士が重なっている部分を描画しないようにする//
		inline void AddClipSiblings() { windStyle |= WS_CLIPSIBLINGS; }

		//Windowは初期時点で無効状態にする//
		inline void AddDisabled() { windStyle |= WS_DISABLED; }

		//Windowにダイアログボックスと同じ境界線を付ける//
		inline void AddDLGFrame() { windStyle |= WS_DLGFRAME; }

		//WindowがControlできるグループの最初であることを定義する//
		inline void AddGroup() { windStyle |= WS_GROUP; }

		//Windowに水平のスクロールバーを付ける//
		inline void AddHScroll() { windStyle |= WS_HSCROLL; }

		//Windowは最初からサイズが最大状態で表示される//
		inline void AddMaxmize() { windStyle |= WS_MAXIMIZE; }

		//Windowに最大化ボタンを付ける//
		inline void AddMaximaizeBox() { windStyle |= WS_MAXIMIZEBOX; }

		//Windowは最初からサイズが最小状態で表示される//
		inline void AddMinimize() { windStyle |= WS_MINIMIZE; }

		//Windowに最小化ボタンを付ける//
		inline void AddMinimizeBox() { windStyle |= WS_MINIMIZEBOX; }

		//Windowにタイトルバーと境界線を持ったWindowを重ねる//
		inline void AddOverlapped() { windStyle |= WS_OVERLAPPED; }

		//OverlappedにCaption,SysMenu,SyzeBox,MinimizeBox,MaximizeBoxを追加した複合スタイル//
		inline void AddOverlappedWindow() { windStyle |= WS_OVERLAPPEDWINDOW; }

		//Windowをポップアップウィンドウにする。こちらはChildと併用できない//
		inline void AddPopup() { windStyle |= WS_POPUP; }

		//PopupにBorder,SysMenuを追加した複合スタイル//
		inline void AddPopupWindow() { windStyle |= WS_POPUPWINDOW; }

		//Windowにサイズを変更可能な境界線を付ける//
		inline void AddSizeBox() { windStyle |= WS_SIZEBOX; }

		//Windowのタイトルバーにウィンドウメニューを付ける//
		inline void AddSysMenu() { windStyle |= WS_SYSMENU; }

		//WindowはUserがTabキーを押した際にフォーカスを受け取れるようにする//
		inline void AddTabStop() { windStyle |= WS_TABSTOP; }

		//Windowが最初から表示されるようにする//
		inline void AddVisible() { windStyle |= WS_VISIBLE; }

		//Windowに垂直スクロールバーを付ける//
		inline void AddVScroll() { windStyle |= WS_VSCROLL; }

		//指定したスタイルを付ける//
		inline void AddStyle(const unsigned long _windStyles) { windStyle |= _windStyles; }

	public://Set Function//

		inline void SetStyle(const unsigned long _windStyles) { windStyle = _windStyles; }

	public://Get Function//

		inline unsigned long GetStyle()const { return windStyle; }

	public:

		//セットされていたStyleを0にする//
		inline void Clear() { windStyle = 0; }

	private:

		unsigned long windStyle = 0;

	};
}

#endif

#endif