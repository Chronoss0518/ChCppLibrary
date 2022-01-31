#ifndef Ch_BD11I_h
#define Ch_BD11I_h

#ifdef _WINDEF_
#ifndef __d3d11_h__

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<D3D11.h>
#include<direct.h>
#include<DirectXCollision.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<DirectXColors.h>
#include<DXGI.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib, "dxguid.lib")

#endif

#include"../Direct3D11/ChPackDate/ChMatrix_11.h"
#include"../Direct3D11/ChPackDate/ChVector3_11.h"
#include"../Direct3D11/ChPackDate/ChQuaternion_11.h"
#include"../Direct3D11/ChDirectX11Controller/ChDirectX11Controller.h"
#include"../Direct3D11/ChShaderStructures11.h"

namespace ChD3D11
{

	enum class ModelConstantRegisterNo :unsigned long
	{
		DrawData,
		CharaData,
		Material,
		LightData = 10,
		BoneDatas
	};

	enum class TextureConstantRegisterNo :unsigned long
	{
		DrawData,
		PolygonData,
		PolygonBoardVertex = 5,
		SpriteVertex,
		LightData = 10
	};

	enum class TextureRegisterNo :unsigned long
	{
		DiffesTex,
		NormalMap,
		LightPowerMap = 10
	};

	class DrawObject
	{
	protected:

		inline void SetDevice(ID3D11Device* _device) { device = _device; }

		inline ID3D11Device* GetDevice() { return device; }

	private:

		ID3D11Device* device;

	};

}

#endif

#endif