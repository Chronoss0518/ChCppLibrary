
//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

struct SpriteVertex
{
	float4 color;
	float2 pos;
	float2 uv;
};

cbuffer SpriteVertexBuffer:register(b6)
{
	SpriteVertex vertexs[4];
}

//頂点シェダ(VertexShader)//
//スプライトバージョン//
VS_OUT main(
	uint _no	: BLENDINDICES0
) {
	VS_OUT Out;

	Out.Pos = float4(vertexs[_no].pos,0.0f,0.0f);

	Out.Pos = mul(Out.Pos, ModelMat);

	//テクスチャマップ上の位置情報//
	Out.UV = vertexs[_no].uv;

	Out.Color = vertexs[_no].color;

	//出力//
	return Out;
}
