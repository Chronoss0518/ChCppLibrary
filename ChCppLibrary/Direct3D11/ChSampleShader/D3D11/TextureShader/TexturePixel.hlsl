

//--------------------------
//���ʃf�[�^
//--------------------------

#include"TShader.hlsli"

//--------------------------
//�摜�f�[�^
//--------------------------

texture2D Tex : register(t0);

sampler Smp :register(s0);
//
//texture2D BackBuffers :register(t12);
//
////�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
//sampler BackBufferSmp :register(s12);

//�s�N�Z���V�F�_(PixelShader)//
//���p//
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