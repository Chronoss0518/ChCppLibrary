#ifdef _WINDOWS_

#ifndef Ch_Win_SubWin_h
#define Ch_Win_SubWin_h

#include"../BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class SubWind :public WindBaseObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		void Create(
			const std::string& _title
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _parentHandl = nullptr);

		///////////////////////////////////////////////////////////////////////////////////////

		void Update(const WPARAM& _wParam)override;

		///////////////////////////////////////////////////////////////////////////////////////
	private:

		bool drawUpdateFlg = true;

	};

}

#endif

#endif