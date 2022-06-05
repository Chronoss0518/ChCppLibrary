#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../WindObject/ChWindStyle.h"
#include"ChWinDefaultPushButton.h"

using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////////
//DefaultPushButtonƒƒ\ƒbƒh//
///////////////////////////////////////////////////////////////////////////////////////

WindStyle* DefaultPushButton::CreateStyle()
{
	auto style = Button::CreateStyle();

	style->AddStyle(BS_PUSHBUTTON);

	return style;
}