#ifdef _WINDOWS_

#ifndef Ch_Win_DfBu_h
#define Ch_Win_DfBu_h

#include"ChWinButton.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class DefaultPushButton :public Button
	{
	protected:

		void CreateStyle()override;

	};

}

#endif

#endif