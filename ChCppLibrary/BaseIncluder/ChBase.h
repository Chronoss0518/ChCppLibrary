#ifndef Ch_BGI_h
#define Ch_BGI_h

#include<cstdio>
#include<cstdarg>
#include<cstring>
#include<ctime>
#include<cmath>

#include<float.h>
#include<limits.h>

#include<iostream>
#include<vector>
#include<string>
#include<type_traits>
#include<functional>
#include<thread>
#include<map>
#include<memory>
#include<fstream>
#include<sstream>
#include<chrono>
#include<codecvt>

#ifdef __d3d11_h__
#include<windows.h>
#endif

#ifdef _D3D9_H_
#include<windows.h>
#endif

#include"../BasePack/ChStd.h"
#include"../BasePack/ChStr.h"
#include"../BasePack/ChPtr.h"

#include"../BasePack/ChMath.h"
#include"../BasePack/ChMath3D.h"
#include"../BasePack/Ch3D.h"

#include"../ClassParts/ChCPInitializer.h"
#include"../ClassParts/ChCPClassNameGetter.h"
#include"../ClassParts/ChCPReleaser.h"
#include"../ClassParts/ChCpForEx.h"

#include"../CPP/ChBitBool/ChBitBool.h"

#endif