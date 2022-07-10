#ifndef ChShader_PublicHeader_DP
#define ChShader_PublicHeader_DP

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

//#define __SHADER__はhlsl側で定義する//

#ifndef __SHADER__
#ifndef SHADER_TO_CPP
#define SHADER_TO_CPP

#define row_magor
using float4x4 = ChLMat;
using float4 = ChVec4;
using float3 = ChVec3;
using float2 = ChVec2;

#endif
#endif


#ifdef __SHADER__
cbuffer DrawData :register(b[DRAW_DATA_REGISTERNO])
#else
struct DrawData
#endif
{
	row_major float4x4 viewMat;

	row_major float4x4 proMat;

	float4 windSize = float4(1280.0f, 720.0f, 0, 0);
};


#ifdef __SHADER__
cbuffer CharaData :register(b[CHARACTOR_POSITION_REGISTERNO])
#else
struct CharaData
#endif
{
	row_major float4x4 modelMat;
};


#ifdef __SHADER__
cbuffer Material :register(b[MATERIAL_DATA_REGISTERNO])
#else
struct Material
#endif
{
	float4 mateDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 speCol;
	float4 ambient;

	row_major float4x4 frameMatrix
#ifdef __SHADER__
		= float4x4(
			1.0f, 0.0f, 0.0f, 1.0f
			, 0.0f, 1.0f, 0.0f, 1.0f
			, 0.0f, 0.0f, 1.0f, 1.0f
			, 0.0f, 0.0f, 0.0f, 1.0f);
#else
		;
#endif
};

#ifdef __SHADER__

texture2D baseTex :register(t[BASE_TEXTURE_REGISTER]);

texture2D normalTex:register(t[NORMAL_TEXTURE_REGISTER]);

//画像から1ピクセルの色を取得するための物//
sampler baseSmp:register(s[BASE_TEXTURE_REGISTER]);

//画像から1ピクセルの色を取得するための物//
sampler normalSmp:register(s[NORMAL_TEXTURE_REGISTER]);

struct MTWStruct
{
	float4 pos;
	float3 normal;
	float3 faceNormal;
	float4 usePos;
	float4 viewPos;
	float4 proPos;
	float2 uv;
};

MTWStruct ModelToWorld(
	float4 _pos,
	float2 _uv,
	float3 _normal,
	float3 _faceNormal)
{
	MTWStruct res;


	res.pos = _pos;

	float4x4 TmpMat
		= float4x4(
			1.0f, 0.0f, 0.0f, 0.0f
			, 0.0f, 1.0f, 0.0f, 0.0f
			, 0.0f, 0.0f, 1.0f, 0.0f
			, 0.0f, 0.0f, 0.0f, 1.0f);

	//TmpMat = BlendNum > 0 ?  BlendMatrix(Blend, BlendPow, BlendNum) : TmpMat;

	float4x4 worldMat = mul(frameMatrix, modelMat);

	//WorldMat = mul(WorldMat, TmpMat);

	res.pos = mul(res.pos, worldMat);

	res.usePos = res.pos;

	res.pos = mul(res.pos, viewMat);

	res.viewPos = res.pos;

	res.pos = mul(res.pos, proMat);

	res.proPos = res.pos;

	res.uv = _uv;

	//Out.Normal = normalize(mul(Normal, (float3x3)ModelMat));

	float3x3 rotMat = worldMat;

	res.normal = normalize(mul(_normal, rotMat));
	res.faceNormal = normalize(mul(_faceNormal, rotMat));

	return res;
}

#endif

#endif