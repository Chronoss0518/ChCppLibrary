#ifdef _WINDOWS_

#ifndef Ch_Win_DfBu_h
#define Ch_Win_DfBu_h

#ifndef Ch_Win_BuOb_h
#include"ChWinButton.h"
#endif

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class DefaultPushButton :public Button
	{
	protected:

		WindStyle* CreateStyle()override;

	};

}

#endif

#endif