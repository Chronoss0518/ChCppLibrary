#ifndef ChShader_PublicHeader_BLUR
#define ChShader_PublicHeader_BLUR

//#define __SHADER__‚ðhlsl‘¤‚Å’è‹`‚·‚é//

#include"../ShaderPublicInclude.hlsli"
#include"Texture/BaseTexture.hlsli"

#ifndef BLUR_DATA_REGISTERNO
#define BLUR_DATA_REGISTERNO 1
#endif

#ifdef __SHADER__
cbuffer BlurData : register(CHANGE_CBUFFER(BLUR_DATA_REGISTERNO))
#else
struct ChS_Blur
#endif
{
    float2 windowSize = float2(0.0f,0.0f);
    int blurPower = 5;
    float blurTmp = 0.0f;
};

#ifdef __SHADER__

float4 Blur(float2 _uv)
{
    float4 resultColor = GetBaseTextureColor(_uv);
    float baseWidth = windowSize.x > 0.0f ? 1.0f / windowSize.x : 1.0f;
    float baseHeight = windowSize.y > 0.0f ? 1.0f / windowSize.y : 1.0f;
    
    for (int i = 1; i < blurPower;i++)
    {
        resultColor += GetBaseTextureColor(float2(_uv.x + (baseWidth * i), _uv.y));
        resultColor += GetBaseTextureColor(float2(_uv.x + (baseWidth * -i), _uv.y));
        resultColor += GetBaseTextureColor(float2(_uv.x, _uv.y + (baseHeight * i)));
        resultColor += GetBaseTextureColor(float2(_uv.x, _uv.y + (baseHeight * -i)));
    }
    resultColor /= float((blurPower * 4) + 1);
    
    return resultColor;
}

#endif

#endif