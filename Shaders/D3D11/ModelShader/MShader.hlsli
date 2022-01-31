//--------------------------
//キャラクター構成データ
//--------------------------

cbuffer DrawData :register(b0)
{
	row_major float4x4 ViewMat;

	row_major float4x4 ProMat;

	float4 WindSize = float4(1280.0f, 720.0f, 0, 0);
};

cbuffer CharaData :register(b1)
{
	row_major float4x4 ModelMat;
};

cbuffer Material :register(b2)
{
	float4 Dif = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 SpeCol;
	float4 Anbient;

	row_major float4x4 FrameMatrix = float4x4(
		1.0f, 0.0f, 0.0f, 1.0f
		, 0.0f, 1.0f, 0.0f, 1.0f
		, 0.0f, 0.0f, 1.0f, 1.0f
		, 0.0f, 0.0f, 0.0f, 1.0f);
};

texture2D DiffuesTex :register(t0);

texture2D NormalMap:register(t1);

//画像から1ピクセルの色を取得するための物//
sampler DiffuesSmp:register(s0);

//画像から1ピクセルの色を取得するための物//
sampler NormalSmp:register(s1);

//--------------------------
//出力データ
//--------------------------

struct VS_OUT
{
	float4 Pos			:SV_POSITION;
	float3 Normal		:NORMAL0;
	float3 FaceNormal	:NORMAL1;
	float Temperature	:TEXCOORD4;
	float4 Color		:COLOR0;
	float4 UsePos		:TEXCOORD1;
	float4 ViewPos		:TEXCOORD2;
	float4 ProPos		:TEXCOORD3;
	float2 UV			:TEXCOORD0;
};
