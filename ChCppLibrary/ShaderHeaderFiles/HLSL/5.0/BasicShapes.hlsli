#ifndef ChShader_PublicHeader_BasicShapes
#define ChShader_PublicHeader_BasicShapes

//#define __SHADER__‚ðhlsl‘¤‚Å’è‹`‚·‚é//

#include"../ShaderPublicInclude.hlsli"

#ifndef MAX_POSITION_DATA
#define MAX_POSITION_DATA 15
#endif

struct ChBasicShapesPositions
{
	float2 positions[MAX_POSITION_DATA];
};

struct ChBasicShapesCirclePosition
{
	float2 centerPosition;
	float size;
};

#ifdef __SHADER__

int IsInPosition(ChBasicShapesPositions _positions,int _usePositionCount , float2 _uv)
{
	if (_usePositionCount <= 3)return 1;

	float3 tmpUVPos = float3(_uv.x, 0.0f, _uv.y);
	
	int i = 0;
	float3 crossDir = 0.0f;
	float3 basePos = 0.0f;
	float3 nextPos = 0.0f;
	int tmpValue = 0;
	for (i = 0; i < _usePositionCount; i++)
	{
		tmpValue = (i + 1) % _usePositionCount;
		basePos = float3(_positions.positions[i].x, 0.0f, _positions.positions[i].y);
		nextPos = float3(_positions.positions[tmpValue].x, 0.0f, _positions.positions[tmpValue].y);
		
		crossDir = cross(nextPos - basePos, tmpUVPos - basePos);
		if (crossDir.y > 0.0f)continue;
		return -1;
	}

	return 1;
}

int IsInCirclePosition(ChBasicShapesCirclePosition _circleData, float2 _uv)
{
	float tmpLen = length(float3(_uv - _circleData.centerPosition,0.0f));

	return tmpLen > _circleData.size ? 1 : -1;
}

#endif

#endif