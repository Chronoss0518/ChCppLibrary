

#define __SHADER__
#define _SM5_0_

#include"PolygonBase.hlsli"

#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"

//�|���S���o�[�W����//
VS_OUT main(
	float4 _pos			: POSITION0
	, float2 _uv		: TEXCOORD0
	, float4 _color		: COLOR0
	, float3 _normal	: NORMAL0
) {
	VS_OUT res;

	MTWStruct tmp;
	tmp = ModelToWorld(_pos, _uv, _normal, _normal);

	res.worldPos = tmp.worldPos;
	res.viewPos = tmp.viewPos;
	res.proPos = tmp.proPos;
	res.pos = tmp.proPos;
	res.normal = tmp.normal;
	res.faceNormal = tmp.faceNormal;
	res.uv = tmp.uv;

	res.color = _color;

	res.temperature = 1.0f;
	//Out.Temperature = 0.0f;

	return res;
}
