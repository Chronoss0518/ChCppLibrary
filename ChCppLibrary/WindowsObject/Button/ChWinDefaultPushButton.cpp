#include<Windows.h>

#include"ChWinDefaultPushButton.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//DefaultPushButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void DefaultPushButtonA::CreateStyle()
{
	ButtonA::CreateStyle();

	style.AddStyle(BS_DEFPUSHBUTTON);

}

void DefaultPushButtonW::CreateStyle()
{
	ButtonW::CreateStyle();

	style.AddStyle(BS_DEFPUSHBUTTON);

}