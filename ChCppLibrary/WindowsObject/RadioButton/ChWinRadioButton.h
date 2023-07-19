#ifdef _WINDOWS_

#ifndef Ch_Win_RdBu_h
#define Ch_Win_RdBu_h

#include"../BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class RadioButton :public WindBaseObject
	{
	public:

		virtual ~RadioButton()
		{
			Release();
		}


	public:

		///////////////////////////////////////////////////////////////////////////////////////

		void Create(
			const std::string& _buttonText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _parentHandl = nullptr
			, const bool _glpFlg = false);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		bool isSelection()
		{
			return (SendMessage(hIns, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}

		///////////////////////////////////////////////////////////////////////////////////////

	protected:




	};

}

#endif

#endif