#ifndef ChShader_PublicHeader_Light
#define ChShader_PublicHeader_Light

#ifndef LIGHT_DATA_REGISTERNO
#define LIGHT_DATA_REGISTERNO 10
#endif

#ifndef LIGHT_TEXTURE_REGISTERNO
#define LIGHT_TEXTURE_REGISTERNO 10
#endif

#ifndef LIGHT_PLIGHTCOUNT
#define LIGHT_PLIGHTCOUNT 10
#endif

//#define __SHADER__��hlsl���Œ�`����//

#ifndef __SHADER__
#ifndef SHADER_TO_CPP
#define SHADER_TO_CPP

#define row_magor
using float4x4 = ChLMat;
using float4 = ChVec4;
using float3 = ChVec3;
using float2 = ChVec2;

#endif
#endif

struct Light
{
	float3 dif;
	bool lightUseFlg;
	float3 dir;
	float ambPow;
};

struct PLight
{
	float3 pos;
	float len;
	float3 dif;
	bool flg;
};


#ifdef __SHADER__
#ifdef _SM5_0_
cbuffer LightData :register(b10)
#else
cbuffer LightData : register(b[LIGHT_DATA_REGISTERNO])
#endif
#else
struct LightData
#endif
{
	float4 camPos = float4(0.0f, 0.0f, 0.0f, 0.0f);

	Light light;

	PLight pLight[LIGHT_PLIGHTCOUNT];
};

#ifdef __SHADER__

#ifdef _SM5_0_
texture2D lightPowMap :register(t10);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler lightSmp :register(s10)
#else
texture2D lightPowMap : register(t[LIGHT_TEXTURE_REGISTERNO]);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
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

	if (!light.lightUseFlg)return oCol;

	float dotSize = dot(_bCol.wfNormal, -light.dir);

	dotSize = (dotSize + 1) * 0.5f;

	dotSize = dotSize > light.ambPow ? dotSize : light.ambPow;

	float3 lamPowMapCol = lightPowMap.Sample(lightSmp, float2(dotSize, dotSize)).rgb;

	float lamPow = lamPowMapCol.r > lamPowMapCol.g ? lamPowMapCol.r : lamPowMapCol.g > lamPowMapCol.b ? lamPowMapCol.g : lamPowMapCol.b;

	oCol *= lamPow * light.dif;

	float3 tmpVec = normalize(camPos.xyz - _bCol.wPos);//�s�N�Z������̃J��������

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

	float3 tmpVec = normalize(camPos.xyz - _modelPos);//�s�N�Z������̃J��������

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