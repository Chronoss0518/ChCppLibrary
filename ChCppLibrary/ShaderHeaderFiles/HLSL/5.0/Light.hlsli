#ifndef ChShader_PublicHeader_Light
#define ChShader_PublicHeader_Light

//#define __SHADER__をhlsl側で定義する//

#include"../ShaderPublicInclude.hlsli"

#ifndef LIGHT_PLIGHTCOUNT
#define LIGHT_PLIGHTCOUNT 10
#endif

#ifndef LIGHT_DATA_REGISTERNO
#define LIGHT_DATA_REGISTERNO 10
#endif

#ifndef LIGHT_TEXTURE_REGISTERNO
#define LIGHT_TEXTURE_REGISTERNO 10
#endif

struct ChDirectionalLight
{
	//diffuse//
	float3 dif;
	bool useFlg;
	//direction//
	float3 dir;
	float ambPow;
};

struct ChPointLight
{
	float3 pos;
	float len;
	//diffuse//
	float3 dif;
	bool useFlg;
};


#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer LightData :register(CHANGE_CBUFFER_5(LIGHT_DATA_REGISTERNO))
#else
cbuffer LightData : register(b[LIGHT_DATA_REGISTERNO])
#endif
#else
struct ChLightData
#endif
{
	float3 camPos = float3(0.0f, 0.0f, 0.0f);

	int colorType = 0;

	ChDirectionalLight light;

	ChPointLight pLight[LIGHT_PLIGHTCOUNT];
};

#ifdef __SHADER__

#ifdef _SM5_0_
texture2D lightPowMap :register(CHANGE_TBUFFER_5(LIGHT_TEXTURE_REGISTERNO));

//画像から1ピクセルの色を取得するための物//
sampler lightSmp :register(CHANGE_SBUFFER_5(LIGHT_TEXTURE_REGISTERNO))
#else
texture2D lightPowMap : register(t[LIGHT_TEXTURE_REGISTERNO]);

//画像から1ピクセルの色を取得するための物//
sampler lightSmp :register(s[LIGHT_TEXTURE_REGISTERNO])
#endif
= sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};


float3 LamLightCol(float3 _dif, float _pow);

float3 SpeLightCol(float3 _dir, float3 _modelPos, float3 _normal,float4 _speculer);

float3 AmbLightCol();

struct L_BaseColor
{
	float3 color;
	float3 wPos;
	float3 wfNormal;
	float4 specular;
};

float3 GetDirectionalLightColor(L_BaseColor _bCol)
{
	float3 oCol = _bCol.color;

	if (!light.useFlg)return oCol;

	float dotSize = dot(_bCol.wfNormal, -light.dir);

	dotSize = (dotSize + 1) * 0.5f;

	dotSize = dotSize > light.ambPow ? dotSize : light.ambPow;

	float3 lamPowMapCol = lightPowMap.Sample(lightSmp, float2(dotSize, dotSize)).rgb;

	float lamPow = lamPowMapCol[colorType];

	oCol *= lamPow * light.dif;

	float3 tmpVec = normalize(camPos.xyz - _bCol.wPos);//ピクセルからのカメラ方向

	tmpVec = normalize(-light.dir + tmpVec);

	float lcDot = dot(tmpVec, _bCol.wfNormal);

	float power = saturate(lcDot);

	oCol += _bCol.specular.rgb * pow(power, _bCol.specular.a);

	return oCol;

}

float3 LamLightCol(float3 _dif, float _pow)
{

	float3 tmpLightCol = _dif;

	tmpLightCol *= _pow;

	return tmpLightCol;
}

float3 SpeLightCol(float3 _dir, float3 _modelPos, float3 _normal, float4 _speculer)
{

	float3 tmpVec = normalize(camPos.xyz - _modelPos);//ピクセルからのカメラ方向

	tmpVec = normalize(-_dir + tmpVec);

	float lcDot = dot(tmpVec, _normal);

	float power = saturate(lcDot);

	float3 tmpLightCol = _speculer.rgb * pow(power, _speculer.a);

	return tmpLightCol;
}

float3 AmbLightCol()
{

	float3 tmpLightCol = light.dif.rgb;

	tmpLightCol *= light.ambPow;

	return tmpLightCol;

}
#endif

#endif