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
cbuffer SpriteData : register(CHANGE_CBUFFER(SPRITE_DATA_REGISTERNO))
#else
struct ChS_SpriteData
#endif
{
	row_major float4x4 spriteMat;
	float4 baseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
};


#ifdef __SHADER__
texture2D baseTex : register(CHANGE_TBUFFER(BASE_TEXTURE_REGISTER));

sampler baseSmp :register(CHANGE_SBUFFER(BASE_TEXTURE_REGISTER));
#endif

#endif
