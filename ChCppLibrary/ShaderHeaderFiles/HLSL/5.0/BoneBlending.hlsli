#ifndef ChShader_PublicHeader_BoneBlending
#define ChShader_PublicHeader_BoneBlending

//#define __SHADER__‚ðhlsl‘¤‚Å’è‹`‚·‚é//

#include"../ShaderPublicInclude.hlsli"

#ifndef BONE_DATA_REGISTERNO
#define BONE_DATA_REGISTERNO 11
#endif


#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer BoneData :register(CHANGE_CBUFFER_5(BONE_DATA_REGISTERNO))
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
	float4x4 blendMat;

	for (uint i = 0; i < _blendNum; i++)
	{
		uint first = i / 4;
		uint second = i % 4;

		blendMat += skinWeightMat[_blend[first][second]] * _blendPow[first][second];
	}

	return blendMat;


}
#endif

#endif