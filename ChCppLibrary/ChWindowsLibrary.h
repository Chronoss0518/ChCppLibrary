#ifdef _WINDOWS

#ifndef Ch_Win_Inc_h
#define Ch_Win_Inc_h

#include <mmsystem.h>
#include <mmreg.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"user32.lib")

#ifndef CRT
#define CRT
#endif

//PackingClass//
#include"WindowsObject/PackData/ChPoint.h"
#include"WindowsObject/PackData/ChRect.h"

#include"WindowsObject/Mouse/ChWinMouse.h"
#include"WindowsObject/DrawTexter/ChWinDrawTexter.h"

//NewVersionWindowsClass//

#include"WindowsObject/WindObject/ChWindStyle.h"
#include"WindowsObject/WindClassObject/ChWindClassStyle.h"

#include"WindowsObject/WindObject/ChWindObject.h"
#include"WindowsObject/WindClassObject/ChWindClassObject.h"

#include"WindowsObject/Texture/ChWinTexture.h"
#include"WindowsObject/TextBox/ChWinTextBox.h"

#include"WindowsObject/Button/ChWinButton.h"
#include"WindowsObject/Button/ChWinDefaultPushButton.h"

#include"BaseSystem/ChWindows/ChWindows.h"

#include"WindowsObject/FileDialog/ChWinFileDialog.h"
#include"WindowsObject/MsgBox/ChMsgBox.h"

#ifdef _WINDOWS
#pragma comment(lib,"ChWinLibrary.lib")
#endif

#endif

#endif