//--------------------------
//外部行列
//--------------------------


//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"

//--------------------------
//ライトデータ
//--------------------------

#include"../ShaderParts/Light.hlsli"

//--------------------------
//BaseShader
//--------------------------

float4 LightCol(VS_OUT _Base, float4 _Color);

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color);

struct RenderDatas
{
	float4 Main : SV_Target0;
	float4 Temperature :SV_Target1;
	float4 NightVision :SV_Target2;
};


//ピクセルシェダ(PixelShader)//
//通常描画//
float4 main(VS_OUT In) :SV_Target0
{
	//カメラの前方にあるかの判定//

	float X = In.ProPos.x / In.ProPos.w;
	float Y = In.ProPos.y / In.ProPos.w;
	float Z = In.ProPos.z / In.ProPos.w;
	//float X = In.Pos.x;
	//float Y = In.Pos.y;
	//float Z = In.Pos.z;

	clip(X >= -1.0f && X <= 1.0f ? 1.0f : -1.0f);
	clip(Y >= -1.0f && Y <= 1.0f ? 1.0f : -1.0f);
	clip(Z >= 0.0f && Z <= 1.0f ? 1.0f : -1.0f);

	//RenderDatas RDColor;

		float4 Color = In.Color;

		Color = Dif * DiffuesTex.Sample(DiffuesSmp, In.UV) * Color;

		//Color = Dif;
		//Color = ModelTex.Sample(ModelSmp, In.UV);

		clip(Color.a > 0.999f ? -1 : 1);

		//Color = LightCol(In, Color);

		L_BaseColor LightCol;
		LightCol.Color = Color.rgb;
		LightCol.WPos = In.UsePos.xyz;
		LightCol.WFNormal = In.Normal;
		LightCol.Specular = SpeCol;

		Color.rgb = GetDirectionalLightColor(LightCol);

		//Color.rgb = BackBuffers.Sample(BackBufferSmp, In.Pos.xy).rgb * (1.0f - Color.a)
		//	+ Color.rgb * Color.a;

		//Color.a = 1.0f;

		//for (int i = 0; i < 10; i++)
		//{
		//	if (!LightUseFlg)break;

		//	Color = PLightCol(pLight[i], In , Color);

		//}

		//float4 Temperature = float4(0.0f, 0.0f, 0.0f, 0.0f);
		//
		//RDColor.Main = Color;
		//RDColor.Temperature = Temperature;

		//float4 NightVision = float4(0.5f, 0.5f, 1.0f, 1.0f) * (length(Color) * 1.5f);

		//NightVision.a = 1.0f;

		//RDColor.NightVision = NightVision;


		return Color;

}


float4 LightCol(VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if (!light.LightUseFlg)return Col;

	float Dot;

	float3 BNormal = normalize(_Base.FaceNormal);
	float3 LNormal = normalize(-light.Dir);

	Dot = dot(BNormal, LNormal);

	Dot = (Dot + 1) * 0.5f;
	//Dot = saturate(Dot);

	float TmpPow = LightPowMap.Sample(LightSmp, float2(Dot, 0.0f)).r;

	//float TmpPow = Dot;

	Col.rgb *= LamLightCol(light.Dif, TmpPow) + AmbLightCol();

	Col.rgb += SpeLightCol(-light.Dir, _Base.UsePos.xyz, _Base.FaceNormal, SpeCol);

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

	Col.rgb += SpeLightCol(TmpVec, _Base.UsePos.xyz, _Base.Normal, SpeCol) * Par;

	return Col;
}
