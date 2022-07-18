
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawSprite.hlsli"

//���_�V�F�_(VertexShader)//
//�X�v���C�g�o�[�W����//
VS_OUT main(
	float4 pos : POSITION0
	, float2 uv : TEXCOORD0
	, float4 color : COLOR0
) {
	VS_OUT res;

	res.pos = pos;

	res.pos = mul(res.pos, spriteMat);

	//�e�N�X�`���}�b�v��̈ʒu���//
	res.uv = uv;

	res.color = color;

	//�o��//
	return res;
}
