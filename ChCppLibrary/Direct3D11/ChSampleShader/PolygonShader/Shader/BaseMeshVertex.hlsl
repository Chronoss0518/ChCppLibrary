
#define __SHADER__
#define _SM5_0_

#include"PolygonBase.hlsli"

#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/BoneBlending.hlsli"

//���_�V�F�[�_(VertexShader)//
//�ʏ�`��//
VS_OUT main
(
	float4 _pos						: POSITION0,
	float2 _uv						: TEXCOORD0,
	float4 _color					: COLOR0,
	float3 _normal					: NORMAL0,
	float3 _faceNormal				: NORMAL1,
	row_major uint4x4 _blend		: BLENDINDEX0,
	row_major float4x4 _blendPow	: BLENDWEIGHT0,
	uint _blendNum					: BLENDINDEX4
)
{
	VS_OUT res;

	res.worldPos = _pos;

	float4x4 tmpMat = GetInitMatrix4x4();

	//tmpMat = _blendNum > 0 ? BlendMatrix(_blend, _blendPow, _blendNum) : tmpMat;
	
	res.worldPos = mul(res.worldPos, tmpMat);

	MTWStruct tmp = ModelToWorld(res.worldPos, _uv, _normal, _faceNormal);

	res.worldPos = tmp.worldPos;
	res.viewPos = tmp.viewPos;
	res.proPos = tmp.proPos;
	res.pos = tmp.proPos;
	res.vertexNormal = tmp.vertexNormal;
	res.faceNormal = tmp.faceNormal;
	res.uv = tmp.uv;

	res.color = _color;

	res.temperature = 1.0f;

	return res;
}


