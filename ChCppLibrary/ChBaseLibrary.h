#ifndef Ch_GIF_h
#define Ch_GIF_h

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef CopyRight_Chronoss_2018Y_08M
#define CopyRight_Chronoss_2018Y_08M
#endif

///////////////////////////////////////////////////////////////////////////////////////
//includefile
///////////////////////////////////////////////////////////////////////////////////////

#include"BaseIncluder/ChBase.h"

#include"CPP/ChTextObject/ChTextObject.h"
//#include"CPP/ChMemoryManager/ChMemoryManager.h"
#include"CPP/ChMultiThread/ChMultiThread.h"
#include"CPP/ChBaseObject/ChObjectList.h"
#include"CPP/ChBaseObject/ChObjectManager.h"
#include"CPP/ChHitTestObject/ChHitTestObject.h"

#include"CPP/ChMathSquare/ChMathSquare.h"

#include"CPP/ChHitTestObject/Panel/ChPanelCollider.h"
#include"CPP/ChHitTestObject/Box/ChBoxCollider.h"
#include"CPP/ChHitTestObject/Sphere/ChSphereCollider.h"
#include"CPP/ChHitTestObject/Polygon/ChPolygonCollider.h"
#include"CPP/ChHitTestObject/ChCollider.h"
#include"CPP/ChHitTestObject/ChHitTestRay.h"

#include"CPP/ChFile/ChFile.h"
#include"CPP/ChModel/ChModel.h"
#include"CPP/ChScript/ChScript.h"
#include"CPP/ChBaseFrame/ChBaseFrame.h"
#include"CPP/ChBaseObject/ChBaseComponent.h"
#include"CPP/ChBaseObject/ChBaseObject.h"
#include"CPP/ChModel/ChModelObject.h"

#include"CPP/ChModelLoader/ChLMXFile.h"
#include"CPP/ChModelLoader/ChLMObjFile.h"

#include"BaseSystem/ChBaseSystem/ChBaseSystem.h"


#ifndef Ch_Library_Create
#ifdef _MT
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"ChCpp_MDd.lib")
#else
#pragma comment(lib,"ChCpp_MD.lib")
#endif//_DEBUG
#else//_DLL
#ifdef _DEBUG
#pragma comment(lib,"ChCpp_MTd.lib")
#else
#pragma comment(lib,"ChCpp_MT.lib")
#endif//_DEBUG
#endif//else
#endif//_MT
#endif//Ch_Library_Create


#endif //Ch_GIF_h//
//CopyRight Chronoss0518 2018/08//