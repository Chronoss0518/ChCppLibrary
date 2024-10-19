#ifdef _WINDOWS_

#ifndef Ch_Win_Inc_h
#define Ch_Win_Inc_h

#ifndef CRT
#define CRT
#endif

#include <mmsystem.h>
#include <mmreg.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"user32.lib")

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

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib,"ChWinLibrary_MDd.lib")
#else
#pragma comment(lib,"ChWinLibrary_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib,"ChWinLibrary_MD.lib")
#else
#pragma comment(lib,"ChWinLibrary_MT.lib")
#endif

#endif

#endif

#endif