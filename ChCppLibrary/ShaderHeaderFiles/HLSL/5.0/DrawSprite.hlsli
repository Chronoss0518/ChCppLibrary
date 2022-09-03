#ifndef ChShader_PublicHeader_DT
#define ChShader_PublicHeader_DT

//#define __SHADER__‚ðhlsl‘¤‚Å’è‹`‚·‚é//

#include"../ShaderPublicInclude.hlsli"

#ifndef SPRITE_DATA_REGISTERNO
#define SPRITE_DATA_REGISTERNO 0
#endif

#ifndef BASE_TEXTURE_REGISTER
#define	BASE_TEXTURE_REGISTER 0
#endif

#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer SpriteData : register(CHANGE_CBUFFER_5(SPRITE_DATA_REGISTERNO))
#else
cbuffer SpriteData : register(b[SPRITE_DATA_REGISTERNO])
#endif
#else
struct ChS_SpriteData
#endif
{
	row_major float4x4 spriteMat;
	float4 baseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
};


#ifdef __SHADER__
#ifdef _SM5_0_
texture2D baseTex : register(CHANGE_TBUFFER_5(BASE_TEXTURE_REGISTER));

sampler baseSmp :register(CHANGE_SBUFFER_5(BASE_TEXTURE_REGISTER));
#else
texture2D baseTex : register(t[BASE_TEXTURE_REGISTER]);

sampler baseSmp :register(s[BASE_TEXTURE_REGISTER]);
#endif
#endif

#endif
