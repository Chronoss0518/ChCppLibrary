#ifdef _WINDOWS_

#ifndef Ch_Win_DWind_h
#define Ch_Win_DWind_h

namespace ChWin
{
	//WindowsAPI�̓��A�`����i��N���X//
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
