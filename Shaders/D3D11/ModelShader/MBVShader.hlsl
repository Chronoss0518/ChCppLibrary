
//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"
#include"BoneBlending.hlsli"

//--------------------------
//外部行列
//--------------------------

struct VS_IN
{
	float4 Pos : POSITION0;
	float2 UV : TEXCOORD0;
	float4 Color : COLOR0;
	float3 Normal : NORMAL0;
	float3 FaceNormal : NORMAL1;
	float4 BlendPow[16] : BLENDWEIGHT0;
};


//頂点シェーダ(VertexShader)//
//通常描画//
VS_OUT main(VS_IN _in)
{

	VS_OUT Out;

	Out.Pos = _in.Pos;

	BlendData bData;

	for (uint i = 0; i < 96; i++)
	{
		bData.blend[i] = _in.BlendPow[i / 16][i % 4];
	}

	float4x4 TmpMat = BlendMatrix(bData);

	float4x4 WorldMat = mul(FrameMatrix, ModelMat);

	//WorldMat = mul(WorldMat, TmpMat);

	Out.Pos = mul(Out.Pos, WorldMat);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);

	Out.ProPos = Out.Pos;

	Out.UV = _in.UV;

	//Out.Normal = normalize(mul(_in.Normal, (float3x3)ModelMat));

	float3x3 RotMat = WorldMat;

	Out.Normal = normalize(mul(_in.Normal, RotMat));
	Out.FaceNormal = normalize(mul(_in.FaceNormal, RotMat));

	//Out.Color = _in.BlendPow[0][0];
	Out.Color = 1.0f;

	Out.Temperature = 1.0f;
	//Out.Temperature = 0.0f;

	return Out;
}


