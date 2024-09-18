#ifdef _WINDOWS_

#ifndef Ch_Win_DfBu_h
#define Ch_Win_DfBu_h

#include"ChWinButton.h"

namespace ChWin
{
	class DefaultPushButtonA :public ButtonA
	{
	protected:

		void CreateStyle()override;
	};

	class DefaultPushButtonW :public ButtonW
	{
	protected:

		void CreateStyle()override;
	};

	using DefaultPushButton =
#ifdef UNICODE
		DefaultPushButtonW;
#else
		DefaultPushButtonA;
#endif


}

#endif

#endif