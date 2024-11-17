#ifndef Ch_GIF_h
#define Ch_GIF_h

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef CopyRight_Chronoss_2018Y_08M
#define CopyRight_Chronoss_2018Y_08M
#endif

#ifndef CRT
#define CRT
#endif

///////////////////////////////////////////////////////////////////////////////////////
//includefile
///////////////////////////////////////////////////////////////////////////////////////

#include"BaseIncluder/ChBase.h"

#include"CPP/ChBaseObject/ChBaseComponent.h"
#include"CPP/ChBaseObject/ChBaseObject.h"
#include"CPP/ChBaseObject/ChObjectList.h"
#include"CPP/ChBaseObject/ChObjectManager.h"

#include"CPP/ChHitTestObject/ChHitTestObject.h"
#include"CPP/ChHitTestObject/ChCollider.h"
#include"CPP/ChHitTestObject/Panel/ChPanelCollider.h"
#include"CPP/ChHitTestObject/Box/ChBoxCollider.h"
#include"CPP/ChHitTestObject/Sphere/ChSphereCollider.h"
#include"CPP/ChHitTestObject/Polygon/ChPolygonCollider.h"
#include"CPP/ChHitTestObject/ChHitTestRay.h"

#include"CPP/ChCounter/ChCounter.h"
#include"CPP/ChCumulative/ChCumulative.h"

#include"CPP/ChJsonObject/ChJsonObject.h"
#include"CPP/ChJsonObject/ChJsonArray.h"
#include"CPP/ChJsonObject/ChJsonNumber.h"
#include"CPP/ChJsonObject/ChJsonString.h"
#include"CPP/ChJsonObject/ChJsonBoolean.h"

#include"CPP/ChFile/ChFile.h"
#include"CPP/ChFile/ChBinaryFile.h"

#include"CPP/ChModel/ChModel.h"
#include"CPP/ChModel/ChModelObject.h"
#include"CPP/ChModelController/ChMCXFile.h"
#include"CPP/ChModelController/ChMCObjFile.h"

#include"CPP/ChBaseFrame/ChBaseFrame.h"
#include"CPP/ChTextObject/ChTextObject.h"
#include"CPP/ChMultiThread/ChMultiThread.h"
#include"CPP/ChMathSquare/ChMathSquare.h"

#include"BaseSystem/ChBaseSystem/ChBaseSystem.h"

//#include"CPP/ChScript/ChScript.h"

#ifdef _WINDOWS_

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib,"ChCppBaseLibrary_MDd.lib")
#else
#pragma comment(lib,"ChCppBaseLibrary_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib,"ChCppBaseLibrary_MD.lib")
#else
#pragma comment(lib,"ChCppBaseLibrary_MT.lib")
#endif

#endif


#endif

#endif //Ch_GIF_h//
//CopyRight Chronoss0518 2018/08//