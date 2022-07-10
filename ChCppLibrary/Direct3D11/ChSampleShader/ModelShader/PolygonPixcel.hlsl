
#define __SHADER__

#include"ModelBase.hlsli"

#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"
#include"../../../ShaderHeaderFiles/HLSL/5.0/Light.hlsli"

float4 LightCol(VS_OUT _base, float4 _color);

float4 PLightCol(PLight _plight, VS_OUT _base, float4 _color);


//ピクセルシェダ(PixelShader)//
//通常描画//
float4 main(VS_OUT _in) :SV_Target0
{
	//カメラの前方にあるかの判定//

	float x = _in.proPos.x / _in.proPos.w;
	float y = _in.proPos.y / _in.proPos.w;
	float z = _in.proPos.z / _in.proPos.w;

	clip(x >= -1.0f && x <= 1.0f ? 1.0f : -1.0f);
	clip(y >= -1.0f && y <= 1.0f ? 1.0f : -1.0f);
	clip(z >= 0.0f && z <= 1.0f ? 1.0f : -1.0f);

	float4 color = _in.color;

	color = mateDiffuse * baseTex.Sample(baseSmp, _in.uv) * color;

	clip(color.a < 0.001f ? -1 : 1);

	L_BaseColor lightCol;
	lightCol.color = color.rgb;
	lightCol.wPos =_in.usePos.xyz;
	lightCol.wfNormal = _in.normal;
	lightCol.specular = speCol;

	color.rgb = GetDirectionalLightColor(lightCol);

	return color;

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

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color)
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