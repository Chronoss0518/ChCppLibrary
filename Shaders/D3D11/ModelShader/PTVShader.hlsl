
//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"

struct PolygonBoardVertex
{

	float4 pos;
	float4 color;
	float2 uv;
	uint2 tmpBuf;
	float3 normal;
	uint tmpBuf2;
};

cbuffer PolygonBoardBuffer : register(b5)
{
	PolygonBoardVertex vertex[3];
};

//--------------------------
//シェーダー
//--------------------------
//頂点シェダ(VertexShader)//
//板ポリゴンバージョン//
VS_OUT main(
	uint _no : BLENDINDICES0
) {
	VS_OUT Out;

	Out.Pos = vertex[_no].pos;

	Out.Pos = mul(Out.Pos, ModelMat);
	//Out.Pos = mul(ModelMat, Out.Pos);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);
	//Out.Pos = mul(ViewMat, Out.Pos);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);
	//Out.Pos = mul(ProMat, Out.Pos);

	Out.ProPos = Out.Pos;

	//テクスチャマップ上の位置情報//
	Out.UV = vertex[_no].uv;

	//頂点の色情報//
	Out.Color = vertex[_no].color;

	Out.Normal = vertex[_no].normal;
	Out.FaceNormal = vertex[_no].normal;

	Out.Temperature = 0.0f;
	//出力//
	return Out;
}
