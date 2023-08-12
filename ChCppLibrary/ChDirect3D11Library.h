#ifndef Ch_D3D11_Inc_h
#define Ch_D3D11_Inc_h


///////////////////////////////////////////////////////////////////////////////////////
//DirectX関連
///////////////////////////////////////////////////////////////////////////////////////


#include"BaseIncluder/ChD3D11I.h"

///////////////////////////////////////////////////////////////////////////////////////
//D3D11AddStruct
///////////////////////////////////////////////////////////////////////////////////////

//Object本体//
#include"Direct3D11/ChTexture/ChTexture11.h"
#include"Direct3D11/ChMesh/ChMesh11.h"
#include"Direct3D11/ChPolygonBoard/ChPolygonBoard11.h"
#include"Direct3D11/ChSprite/ChSprite11.h"
//ライブラリで用意したShaderを利用するクラス//
#include"Direct3D11/ChCB/ChCBBase11.h"
#include"Direct3D11/ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"Direct3D11/ChCB/ChCBSprite/ChCBSprite11.h"
#include"Direct3D11/ChCB/ChCBLight/ChCBLight11.h"
#include"Direct3D11/ChCB/ChCBBone/ChCBBone11.h"
#include"Direct3D11/ChCB/ChCBCircleCulling/ChCBCircleCulling11.h"
//サンプルシェーダー//
#include"Direct3D11/ChSampleShader/PolygonShader/ChBaseDrawMesh11.h"
#include"Direct3D11/ChSampleShader/PolygonShader/ChBaseDrawPolygonBoard11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChBaseDrawSprite11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChCircleCullingSpriteShader11.h"

//空間操作//
#include"Direct3D11/ChCameraController/ChCameraController11.h"
//Object操作//
#include"Direct3D11/ChShader/ChShader11.h"
//Component//

//D3DObject//
#include"BaseIncluder/ChD3DOI.h"


#ifndef Ch_Library_Create
#ifdef _MT
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"ChD3D11_MDd.lib")
#else
#pragma comment(lib,"ChD3D11_MD.lib")
#endif//_DEBUG
#else//_DLL
#ifdef _DEBUG
#pragma comment(lib,"ChD3D11_MTd.lib")
#else
#pragma comment(lib,"ChD3D11_MT.lib")
#endif//_DEBUG
#endif//else
#endif//_MT
#endif//Ch_Library_Create


//CopyRight Chronoss0518 2018/08//
#endif
