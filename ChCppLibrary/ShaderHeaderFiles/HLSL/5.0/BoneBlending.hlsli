#ifndef ChShader_PublicHeader_BoneBlending
#define ChShader_PublicHeader_BoneBlending

#ifndef BONE_DATA_REGISTERNO
#define BONE_DATA_REGISTERNO 11
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


#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer BoneData :register(b11)
#else
cbuffer BoneData : register(b[BONE_DATA_REGISTERNO])
#endif
#else
struct BoneData
#endif
{
	row_major float4x4 skinWeightMat[4 * 16];
};

#ifdef __SHADER__

float4x4 BlendMatrix(uint4x4 _blend, float4x4 _blendPow, uint _blendNum)
{
	float4x4 BlendMat;

	for (uint i = 0; i < _blendNum; i++)
	{
		uint first = i / 4;
		uint second = i % 4;

		BlendMat += skinWeightMat[_blend[first][second]] * _blendPow[first][second];
	}

	return BlendMat;


}
#endif

#endif