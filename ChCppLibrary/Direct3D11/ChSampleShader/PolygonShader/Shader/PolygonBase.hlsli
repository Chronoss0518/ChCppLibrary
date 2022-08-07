#ifndef Ch_ModelBase_h
#define Ch_ModelBase_h


struct VS_OUT
{
	float4 pos			:SV_POSITION;
	float3 vertexNormal	:NORMAL0;
	float3 faceNormal	:NORMAL1;
	float4 color		:COLOR0;
	float4 worldPos		:TEXCOORD1;
	float4 viewPos		:TEXCOORD2;
	float4 proPos		:TEXCOORD3;
	float2 uv			:TEXCOORD0;
	float temperature	:TEXCOORD4;
};

#endif