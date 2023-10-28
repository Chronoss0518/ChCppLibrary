
#define __SHADER__
#define _SM5_0_


#include"BasicShapesCircle.hlsli"

#include"../../../../ShaderHeaderFiles/HLSL/5.0/BasicShapes.hlsli"


float4 main(VS_OUT _vs) : SV_TARGET
{
	clip(IsInCirclePosition(circleData,_vs.uv));
	return color;
}