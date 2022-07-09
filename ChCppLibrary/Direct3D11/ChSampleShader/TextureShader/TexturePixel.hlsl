

//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

//--------------------------
//画像データ
//--------------------------

texture2D Tex : register(t0);

sampler Smp :register(s0);
//
//texture2D BackBuffers :register(t12);
//
////画像から1ピクセルの色を取得するための物//
//sampler BackBufferSmp :register(s12);

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT In) : SV_Target0
{
	float4 Out = In.Color;
	Out *= Tex.Sample(Smp, In.UV);

	//Out = BaseColor;

	clip(Out.a < 0.01f ? -1 : 1);

	//float4 BackCol = BackBuffers.Sample(BackBufferSmp, In.Pos.xy);

	//Out = Out.a == 1.0f ? Out : float4(float3(Out.rgb * Out.a).rgb + float3(BackCol.rgb * (1.0f - Out.a)).rgb, 1);
	//

	return Out;

}