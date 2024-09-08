
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture/ChTexture11.h"
#include"ChMesh11.h"

using namespace Ch3D;
using namespace ChCpp;
using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChMesh11 Method
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void Mesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (_device == nullptr)return;

	Release();

	device = _device;

	ModelObject<CharaType>::Init();

}
template void Mesh11<char>::Init(ID3D11Device* _device);
template void Mesh11<wchar_t>::Init(ID3D11Device* _device);

template<typename CharaType>
void Mesh11<CharaType>::Init()
{
	if (!D3D11API().IsInit())return;
	Init(D3D11Device());
}
template void Mesh11<char>::Init();
template void Mesh11<wchar_t>::Init();

template<typename CharaType>
void Mesh11<CharaType>::Release()
{
	ModelObject<CharaType>::Release();
}
template void Mesh11<char>::Release();
template void Mesh11<wchar_t>::Release();

template<typename CharaType>
void Mesh11<CharaType>::Create()
{
	if (!ModelObject<CharaType>::IsInit())return;
	CreateFrames();
}
template void Mesh11<char>::Create();
template void Mesh11<wchar_t>::Create();
