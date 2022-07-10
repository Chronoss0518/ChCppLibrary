
#define __SHADER__

#include"TextureBase.hlsli"
#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"

//頂点シェダ(VertexShader)//
//スプライトバージョン//
VS_OUT main(
	float4 pos : POSITION0
	, float2 uv : TEXCOORD0
	, float4 color : COLOR0
) {
	VS_OUT Out;

	Out.pos = pos;

	Out.pos = mul(Out.pos, modelMat);

	//テクスチャマップ上の位置情報//
	Out.uv = uv;

	Out.color = color;

	//出力//
	return Out;
}
