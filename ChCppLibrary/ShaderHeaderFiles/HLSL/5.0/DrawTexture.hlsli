#ifndef	Ch_TextureBase_h
#define Ch_TextureBase_h

#ifndef DRAW_DATA_REGISTERNO
#define DRAW_DATA_REGISTERNO 0
#endif

#ifndef POLYGON_DATA_REGISTERNO
#define POLYGON_DATA_REGISTERNO 1
#endif

#ifndef BASE_TEXTURE_REGISTER
#define	BASE_TEXTURE_REGISTER 0
#endif

//#define __SHADER__‚Íhlsl‘¤‚Å’è‹`‚·‚é//

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

#ifndef __SHADER__
#ifdef _SM5_0_
cbuffer DrawData :register(b0)
#else
cbuffer DrawData : register(b[DRAW_DATA_REGISTERNO])
#endif
#else
struct DrawData
#endif
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
	float4 WindSize = float4(1280.0f, 720.0f, 0, 0);
};

#ifndef __SHADER__
#ifdef _SM5_0_
cbuffer PolygonData:register(b1)
#else
cbuffer PolygonData : register(b[POLYGON_DATA_REGISTERNO])
#endif
#else
struct DrawData
#endif
{
	row_major float4x4 ModelMat;
	float4 BaseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
}


#ifdef __SHADER__
#ifdef _SM5_0_
texture2D tex : register(t0);

sampler smp :register(s0);
#else
texture2D tex : register(t[BASE_TEXTURE_REGISTER]);

sampler smp :register(s[BASE_TEXTURE_REGISTER]);
#endif
#endif

#endif
