
#define __SHADER__

#include"TextureBase.hlsli"
#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"

//���_�V�F�_(VertexShader)//
//�X�v���C�g�o�[�W����//
VS_OUT main(
	float4 pos : POSITION0
	, float2 uv : TEXCOORD0
	, float4 color : COLOR0
) {
	VS_OUT Out;

	Out.pos = pos;

	Out.pos = mul(Out.pos, modelMat);

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.uv = uv;

	Out.color = color;

	//�o��//
	return Out;
}
