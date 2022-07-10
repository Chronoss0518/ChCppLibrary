

#define __SHADER__
#define _SM5_0_

#include"ModelBase.hlsli"

#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"

//板ポリゴンバージョン//
VS_OUT main(
	float4 _pos		: POSITION0
	, float2 _uv		: TEXCOORD0
	, float4 _color	: COLOR0
	, float3 _normal : NORMAL0
) {
	VS_OUT res;

	MTWStruct tmp = ModelToWorld(_pos, _uv, _normal, _normal);

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
