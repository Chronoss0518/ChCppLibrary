#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../WindObject/ChWindStyle.h"
#include"ChWinDefaultPushButton.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//DefaultPushButton���\�b�h//
///////////////////////////////////////////////////////////////////////////////////////

void DefaultPushButton::CreateStyle()
{
	Button::CreateStyle();

	style.AddStyle(BS_DEFPUSHBUTTON);

}