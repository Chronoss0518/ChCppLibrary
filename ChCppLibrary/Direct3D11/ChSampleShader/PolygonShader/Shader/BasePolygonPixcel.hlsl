
#define __SHADER__
#define _SM5_0_

#include"PolygonBase.hlsli"

#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/Light.hlsli"

float4 LightCol(VS_OUT _base, float4 _color);

float4 PLightCol(ChPointLight _plight, VS_OUT _base, float4 _color);

#if 1
struct OutColor
{
	float4 color :SV_Target0;
	float depth : SV_Depth;
};
#else
struct OutColor
{
	float4 color :SV_Target0;
	//float depth : SV_Depth;
};
#endif
//ピクセルシェダ(PixelShader)//
//通常描画//
OutColor main(VS_OUT _in)
{
	//カメラの前方にあるかの判定//
	FrustumCulling(_in.proPos);
	

	OutColor outColor;
	
	outColor.color = float4(1.0f, 0.0f, 0.0f, 1.0f);
	//outColor.color = _in.pos;
	//outColor.color.z = 0.0f;
	//outColor.color.x = _in.proPos.x / _in.proPos.w;
	//outColor.color.y = _in.proPos.y / _in.proPos.w;
	//outColor.color.z = _in.proPos.z / _in.proPos.w;
	//outColor.color.r = outColor.depth;


	outColor.color = _in.color;

	outColor.color = mate.dif * baseTex.Sample(baseSmp, _in.uv) * outColor.color;

	clip(outColor.color.a < 0.001f ? -1 : 1);

	outColor.depth = outColor.color.a <= 0.99f ? 1.0f: (_in.proPos.z / _in.proPos.w);
	
	L_BaseColor lightCol;
	lightCol.color = outColor.color.rgb;
	lightCol.wPos =_in.worldPos.xyz;
	lightCol.wfNormal = _in.faceNormal;
	lightCol.specular.rgb = mate.speCol;
	lightCol.specular.a = mate.spePow;

	outColor.color.rgb = GetDirectionalLightColor(lightCol);

	return outColor;

}

/*
float4 LightCol(VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if(!light.LightUseFlg)return Col;

	float Dot;

	float3 BNormal = normalize(_Base.FaceNormal);
	float3 LNormal = normalize(-light.Dir);

	Dot = dot(BNormal, LNormal);

	Dot = (Dot + 1) * 0.5f;
	//Dot = saturate(Dot);

	float TmpPow = LightPowMap.Sample(LightSmp, float2(Dot, 0.0f)).r;
	
	//float TmpPow = Dot;

	Col.rgb *= LamLightCol(light.Dif, TmpPow) + AmbLightCol();

	Col.rgb += SpeLightCol(-light.Dir, _Base.UsePos.xyz, _Base.FaceNormal,SpeCol);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(ChPointLight plight, VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if (!light.LightUseFlg)return Col;
	if (!plight.Flg)return Col;

	bool TmpFlg = false;

	float3 TmpVec = _Base.UsePos.xyz;

	TmpVec = TmpVec - plight.Pos;

	float Len;

	Len = length(TmpVec);

	TmpFlg = Len > plight.Len ? true : false;

	if (TmpFlg)return Col;

	TmpVec = normalize(TmpVec);

	float Par = Len / plight.Len;

	float Dot;

	Dot = dot(_Base.Normal, -TmpVec);

	Dot = saturate(Dot);

	Col.rgb *= LamLightCol(plight.Dif.rgb, Dot) * Par;

	Col.rgb += SpeLightCol(TmpVec, _Base.UsePos.xyz, _Base.Normal,SpeCol) * Par;

	return Col;
}

*/