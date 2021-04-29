
struct Light
{
	float3 Dif;
	bool LightUseFlg;
	float3 Dir;
	float AmbPow;
};

struct PLight
{
	float3 Pos;
	float Len;
	float3 Dif;
	bool Flg;
};

cbuffer LightData :register(b10)
{
	float3 CamPos = float3(0.0f, 0.0f, 0.0f);

	int PlightCnt = 10;

	Light light;

	PLight pLight[10];

};


texture2D LightPowMap :register(t10);

//画像から1ピクセルの色を取得するための物//
sampler LightSmp :register(s10) = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};


float3 LamLightCol(float3 _Dif, float _Pow);

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal,float4 _Speculer);

float3 AmbLightCol();

struct L_BaseColor
{
	float3 Color;
	float3 WPos;
	float3 WFNormal;
	float4 Specular;
};

float3 GetDirectionalLightColor(L_BaseColor _BCol)
{
	float3 OCol = _BCol.Color;

	if (!light.LightUseFlg)return OCol;

	float Dot = dot(_BCol.WFNormal, -light.Dir);

	Dot = (Dot + 1) * 0.5f;

	Dot = Dot > light.AmbPow ? Dot : light.AmbPow;

	float3 LamPowMapCol = LightPowMap.Sample(LightSmp, float2(Dot, Dot)).rgb;

	float LamPow = LamPowMapCol.r > LamPowMapCol.g ? LamPowMapCol.r : LamPowMapCol.g > LamPowMapCol.b ? LamPowMapCol.g : LamPowMapCol.b;

	OCol *= LamPow * light.Dif;

	float3 TmpVec = normalize(CamPos - _BCol.WPos);//ピクセルからのカメラ方向

	TmpVec = normalize(-light.Dir + TmpVec);

	float LCDot = dot(TmpVec, _BCol.WFNormal);

	float Pow = saturate(LCDot);

	OCol += _BCol.Specular.rgb * pow(Pow, _BCol.Specular.a);

	return OCol;

}

float3 LamLightCol(float3 _Dif, float _Pow)
{

	float3 TmpLightCol = _Dif;

	TmpLightCol *= _Pow;

	return TmpLightCol;
}

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal, float4 _Speculer)
{

	float3 TmpVec = normalize(CamPos - _ModelPos);//ピクセルからのカメラ方向

	TmpVec = normalize(-_Dir + TmpVec);

	float LCDot = dot(TmpVec, _Normal);

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
