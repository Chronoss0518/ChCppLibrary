#ifndef Ch_ImGui_BAPI_h
#define Ch_ImGui_BAPI_h

#ifndef IMGUI_VERSION

#include"External/imgui/imconfig.h"
#include"External/imgui/imgui.h"

#endif

#include"BaseIncluder/ChBase.h"
#include"CPP/ChBitBool/ChBitBool.h"

#include"ImGUI/ChImGUIBaseWind/ChImGUIBaseWind.h"

#ifdef _WINDOWS_

#include"External/imgui/backends/imgui_impl_win32.h"

#ifdef _D3D9_H_

#include"External/imgui/backends/imgui_impl_dx9.h"

#endif//_D3D9_H_

#ifdef __d3d11_h__

#include"External/imgui/backends/imgui_impl_dx11.h"

#endif//__d3d11_h__

#endif//_WINDOWS_

#endif