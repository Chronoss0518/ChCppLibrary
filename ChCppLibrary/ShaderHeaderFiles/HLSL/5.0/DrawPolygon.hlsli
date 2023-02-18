#ifndef ChShader_PublicHeader_DP
#define ChShader_PublicHeader_DP

//#define __SHADER__をhlsl側で定義する//

#include"../ShaderPublicInclude.hlsli"

#ifndef DRAW_DATA_REGISTERNO
#define DRAW_DATA_REGISTERNO 0
#endif

#ifndef CHARACTOR_POSITION_REGISTERNO
#define CHARACTOR_POSITION_REGISTERNO 1
#endif

#ifndef MATERIAL_DATA_REGISTERNO 
#define MATERIAL_DATA_REGISTERNO 2
#endif

#ifndef BASE_TEXTURE_REGISTER
#define	BASE_TEXTURE_REGISTER 0
#endif

#ifndef NORMAL_TEXTURE_REGISTER
#define	NORMAL_TEXTURE_REGISTER 1
#endif

#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer DrawData :register(CHANGE_CBUFFER_5(DRAW_DATA_REGISTERNO))
#else
cbuffer DrawData : register(b[DRAW_DATA_REGISTERNO])
#endif
#else
struct ChP_DrawData
#endif
{
	row_major float4x4 viewMat;

	row_major float4x4 proMat;
};


#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer CharaData :register(CHANGE_CBUFFER_5(CHARACTOR_POSITION_REGISTERNO))
#else
cbuffer CharaData : register(b[CHARACTOR_POSITION_REGISTERNO])
#endif
#else
struct ChP_CharaData
#endif
{
	row_major float4x4 worldMat;

	row_major float4x4 frameMatrix;
};

struct ChP_Material
{

	//diffuse//
	float4 dif;
	//specular//
	float3 speCol;
	float spePow;
	//ambient//
	float4 ambient;
};

#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer Material :register(CHANGE_CBUFFER_5(MATERIAL_DATA_REGISTERNO))
#else
cbuffer Material : register(b[MATERIAL_DATA_REGISTERNO])
#endif
{
	uniform ChP_Material mate;
};
#endif

#ifdef __SHADER__

#ifdef _SM5_0_
texture2D baseTex :register(CHANGE_TBUFFER_5(BASE_TEXTURE_REGISTER));
texture2D normalTex:register(CHANGE_TBUFFER_5(NORMAL_TEXTURE_REGISTER));

//画像から1ピクセルの色を取得するための物//
sampler baseSmp:register(CHANGE_SBUFFER_5(BASE_TEXTURE_REGISTER));

//画像から1ピクセルの色を取得するための物//
sampler normalSmp:register(CHANGE_SBUFFER_5(NORMAL_TEXTURE_REGISTER));
#else
texture2D baseTex : register(t[BASE_TEXTURE_REGISTER]);
texture2D normalTex : register(t[NORMAL_TEXTURE_REGISTER]);

//画像から1ピクセルの色を取得するための物//
sampler baseSmp : register(s[BASE_TEXTURE_REGISTER]);

//画像から1ピクセルの色を取得するための物//
sampler normalSmp: register(s[NORMAL_TEXTURE_REGISTER]);
#endif

struct MTWStruct
{
	float3 vertexNormal;
	float3 faceNormal;
	float4 worldPos;
	float4 viewPos;
	float4 proPos;
	float2 uv;
};

float4x4 GetInitMatrix4x4()
{
	return float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

float3x3 GetInitMatrix3x3()
{
	return float3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f);
}

MTWStruct ModelToWorld(
	float4 _pos,
	float2 _uv,
	float3 _normal,
	float3 _faceNormal,
	float4x4 _boneMatrix)
{
	MTWStruct res;

	float4x4 tmpMat = mul(_boneMatrix, mul(frameMatrix, worldMat));

	res.worldPos = mul(_pos, tmpMat);

	res.viewPos = mul(res.worldPos, viewMat);

	res.proPos = mul(res.viewPos, proMat);

	res.uv = _uv;

	res.vertexNormal = normalize(mul(_normal, (float3x3)tmpMat));
	res.faceNormal = normalize(mul(_faceNormal, (float3x3)tmpMat));

	return res;
}

void FrustumCulling(float4 _pos)
{
	float x = _pos.x / _pos.w;
	x *= x;
	float y = _pos.y / _pos.w;
	y *= y;
	float z = (_pos.z / _pos.w) * 2.0f - 1.0f;
	z *= z;
	clip(1.0f - x);
	clip(1.0f - y);
	clip(1.0f - z);
}


#endif

#endif