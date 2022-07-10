
#define __SHADER__

#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"
#include"../../../ShaderHeaderFiles/HLSL/5.0/BoneBlending.hlsli"
#include"ModelBase.hlsli"

//頂点シェーダ(VertexShader)//
//通常描画//
VS_OUT main
(
	float4 _pos			: POSITION0,
	float2 _uv			: TEXCOORD0,
	float4 _color		 : COLOR0,
	float3 _normal		: NORMAL0,
	float3 _faceNormal	: NORMAL1,
	row_major uint4x4 _blend		: BLENDINDEX0,
	row_major float4x4 _blendPow	: BLENDWEIGHT0,
	uint _blendNum		: BLENDINDEX4
)
{

	VS_OUT res;

	res.pos = _pos;

	/*
	float4x4 TmpMat
		= float4x4(
			1.0f, 0.0f, 0.0f, 0.0f
			, 0.0f, 1.0f, 0.0f, 0.0f
			, 0.0f, 0.0f, 1.0f, 0.0f
			, 0.0f, 0.0f, 0.0f, 1.0f);

	TmpMat = BlendNum > 0 ?  BlendMatrix(Blend, BlendPow, BlendNum) : TmpMat;

	float4x4 WorldMat = mul(FrameMatrix, ModelMat);

	//WorldMat = mul(WorldMat, TmpMat);

	*/

	MTWStruct tmp = ModelToWorld(res.pos, _uv, _normal, _faceNormal);

	res.pos = tmp.pos;
	res.viewPos = tmp.viewPos;
	res.proPos = tmp.proPos;
	res.usePos = tmp.usePos;
	res.normal = tmp.normal;
	res.faceNormal = tmp.faceNormal;
	res.uv = tmp.uv;

	res.color = _color;

	res.temperature = 1.0f;
	//Out.Temperature = 0.0f;

	return res;
}


