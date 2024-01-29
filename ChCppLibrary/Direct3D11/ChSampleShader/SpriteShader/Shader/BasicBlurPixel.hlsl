
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawSprite.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/Blur.hlsli"

//�s�N�Z���V�F�_(PixelShader)//
//���p//
float4 main(VS_OUT _in) : SV_Target0
{
    float4 res = _in.color;
    res *= Blur(_in.uv) * baseColor;

    clip(res.a - 0.01f);
    
    return res;

}