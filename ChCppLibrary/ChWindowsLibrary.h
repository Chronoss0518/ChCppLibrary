#ifdef _WIN32

#ifndef Ch_Win_Inc_h
#define Ch_Win_Inc_h

#ifdef _WINDEF_
#include <mmsystem.h>
#include <mmreg.h>
#endif

#ifdef _WINDEF_
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"user32.lib")
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

#ifndef Ch_Library_Create
#ifdef _MT
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"ChWin_MDd.lib")
#else
#pragma comment(lib,"ChWin_MD.lib")
#endif//_DEBUG
#else//_DLL
#ifdef _DEBUG
#pragma comment(lib,"ChWin_MTd.lib")
#else
#pragma comment(lib,"ChWin_MT.lib")
#endif//_DEBUG
#endif//else
#endif//_MT
#endif//Ch_Library_Create

#endif

#endif