
//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"
#include"BoneBlending.hlsli"

//--------------------------
//外部行列
//--------------------------

//--------------------------
//出力データ
//--------------------------


//頂点シェーダ(VertexShader)//
//通常描画//
VS_OUT main
(
	float4 Pos			: POSITION0,
	float2 UV			: TEXCOORD0,
	float4 Color		 : COLOR0,
	float3 Normal		: NORMAL0,
	float3 FaceNormal	: NORMAL1,
	row_major uint4x4 Blend		: BLENDINDEX0,
	row_major float4x4 BlendPow	: BLENDWEIGHT0,
	uint BlendNum		: BLENDINDEX4
)
{

	VS_OUT Out;

	Out.Pos = Pos;

	float4x4 TmpMat
		= float4x4(
			1.0f, 0.0f, 0.0f, 0.0f
			, 0.0f, 1.0f, 0.0f, 0.0f
			, 0.0f, 0.0f, 1.0f, 0.0f
			, 0.0f, 0.0f, 0.0f, 1.0f);

	//TmpMat = BlendNum > 0 ?  BlendMatrix(Blend, BlendPow, BlendNum) : TmpMat;

	float4x4 WorldMat = mul(FrameMatrix, ModelMat);

	//WorldMat = mul(WorldMat, TmpMat);

	Out.Pos = mul(Out.Pos, WorldMat);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);

	Out.ProPos = Out.Pos;

	Out.UV = UV;

	//Out.Normal = normalize(mul(Normal, (float3x3)ModelMat));

	float3x3 RotMat = WorldMat;

	Out.Normal = normalize(mul(Normal, RotMat));
	Out.FaceNormal = normalize(mul(FaceNormal, RotMat));

	Out.Color = 1.0f;

	Out.Temperature = 1.0f;
	//Out.Temperature = 0.0f;

	return Out;
}


