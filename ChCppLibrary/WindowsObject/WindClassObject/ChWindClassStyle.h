#ifdef _WINDOWS_

#ifndef Ch_Win_WCStyle_h
#define Ch_Win_WCStyle_h

namespace ChWin
{
	class WindClassStyle
	{
	public://Add Function//

		//ウィドウのクライアント領域をX方向のバイト領域にそろえる//
		inline void AddByteAlingnClient() { classStyle |= CS_BYTEALIGNCLIENT; }

		//ウィドウをX方向のバイト境界にそろえる//
		inline void AddByteAlingnWindow() { classStyle |= CS_BYTEALIGNWINDOW; }

		//クラス内の1つのデバイスコンテキストを共有する//
		inline void AddClassDC() { classStyle |= CS_CLASSDC; }

		//クラスに属するウィンドウ内でダブルクリックをするとウィンドウプロシージャ―が受け取れる//
		inline void AddDBLClick() { classStyle |= CS_DBLCLKS; }

		//ウィンドウにドロップシャドウ効果を付ける(ボタンをクリックしたときの様な挙動)//
		inline void AddDropShadow() { classStyle |= CS_DROPSHADOW; }

		//プロセス内の他のすべてのモジュールで使用できるようにする//
		inline void AddGlobalClass() { classStyle |= CS_GLOBALCLASS; }

		//ウィンドウの幅が移動やサイズ変更によって変化した場合に再描画する//
		inline void AddHReDraw() { classStyle |= CS_HREDRAW; }

		//ウィンドウをの閉じるボタンを無効化する//
		inline void AddNoClose() { classStyle |= CS_NOCLOSE; }

		//このクラスを利用したウィンドウ一つ一つに一意のデバイスコンテキストを与える//
		inline void AddOWNDC() { classStyle |= CS_OWNDC; }

		//子ウィンドウが親ウィンドウに描画できるようにする//
		inline void AddParentDC() { classStyle |= CS_PARENTDC; }

		//ウィンドウによって隠されている部分をビットマップとして保持する//
		inline void AddSaveBits() { classStyle |= CS_SAVEBITS; }

		//ウィンドウの高さが移動やサイズ変更によって変化した場合に再描画する//
		inline void AddVReDraw() { classStyle |= CS_VREDRAW; }

	public://Set Function//

		inline void SetStyle(const unsigned long _style) { classStyle = _style; }

	public://Get Function//

		inline unsigned long GetStyle()const { return classStyle; }

	public:

		//セットされていたStyleを0にする//
		inline void Clear() { classStyle = 0; }

	private:

		unsigned long classStyle = 0;

	};
}

#endif

#endif