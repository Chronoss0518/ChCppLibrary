#ifdef _WINDOWS_

#ifndef Ch_Win_DWind_h
#define Ch_Win_DWind_h

namespace ChWin
{
	//WindowsAPIの内、描画を司るクラス//
	class WindDrawer
	{
	public:

	private:

		HWND hWnd = nullptr;
		HDC hDC = nullptr;
		HBITMAP bb = nullptr;
		HBRUSH brush = nullptr;

	};

}

#endif

#endif
