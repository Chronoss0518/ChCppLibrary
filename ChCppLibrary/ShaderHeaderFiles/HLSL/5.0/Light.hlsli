#ifndef ChShader_PublicHeader_Light
#define ChShader_PublicHeader_Light

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

#ifndef LIGHT_DATA_REGISTERNO
#define LIGHT_DATA_REGISTERNO 10
#endif

#ifndef LIGHT_DATA_REGISTERNO
#define LIGHT_TEXTURE_REGISTERNO 10
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

cbuffer LightData :register(b[LIGHT_DATA_REGISTERNO])
{
	float3 camPos = float3(0.0f, 0.0f, 0.0f);

	int pLightCnt = 10;

	Light light;

	PLight pLight[10];

};

texture2D lightPowMap :register(t[LIGHT_TEXTURE_REGISTERNO]);

//画像から1ピクセルの色を取得するための物//
sampler lightSmp :register(s[LIGHT_TEXTURE_REGISTERNO])
= sampler_state{
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
	float3 oCol = _bCol.Color;

	if (!light.LightUseFlg)return oCol;

	float dotSize = dot(_bCol.wfNormal, -light.dir);

	dotSize = (dotSize + 1) * 0.5f;

	dotSize = dotSize > light.ambPow ? dotSize : light.ambPow;

	float3 lamPowMapCol = lightPowMap.Sample(lightSmp, float2(dotSize, dotSize)).rgb;

	float lamPow = lamPowMapCol.r > lamPowMapCol.g ? lamPowMapCol.r : lamPowMapCol.g > lamPowMapCol.b ? lamPowMapCol.g : lamPowMapCol.b;

	oCol *= lamPow * light.dif;

	float3 tmpVec = normalize(camPos - _bCol.wPos);//ピクセルからのカメラ方向

	tmpVec = normalize(-light.dir + tmpVec);

	float lcDot = dot(tmpVec, _bCol.WFNormal);

	float pow = saturate(lcDot);

	oCol += _bCol.specular.rgb * pow(pow, _bCol.specular.a);

	return oCol;

}

float3 lamLightCol(float3 _dif, float _pow)
{

	float3 tmpLightCol = _dif;

	tmpLightCol *= _pow;

	return tmpLightCol;
}

float3 speLightCol(float3 _dir, float3 _modelPos, float3 _normal, float4 _speculer)
{

	float3 tmpVec = normalize(camPos - _modelPos);//ピクセルからのカメラ方向

	tmpVec = normalize(-_dir + tmpVec);

	float lcDot = dot(TmpVec, _Normal);

	float Pow = saturate(LCDot);

	float3 TmpLightCol = _Speculer.rgb * pow(Pow, _Speculer.a);

	return TmpLightCol;
}

float3 AmbLightCol()
{

	float3 TmpLightCol = light.Dif.rgb;

	TmpLightCol *= light.AmbPow;

	return TmpLightCol;

}

#endif