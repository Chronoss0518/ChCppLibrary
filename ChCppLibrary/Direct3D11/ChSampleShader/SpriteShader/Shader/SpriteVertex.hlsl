
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawSprite.hlsli"

//頂点シェダ(VertexShader)//
//スプライトバージョン//
VS_OUT main(
	float4 pos : POSITION0
	, float2 uv : TEXCOORD0
	, float4 color : COLOR0
) {
	VS_OUT res;

	res.pos = pos;

	res.pos = mul(res.pos, spriteMat);

	//テクスチャマップ上の位置情報//
	res.uv = uv;

	res.color = color;

	//出力//
	return res;
}
