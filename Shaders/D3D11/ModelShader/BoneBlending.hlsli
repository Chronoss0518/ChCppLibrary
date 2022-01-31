
cbuffer BoneDatas :register(b11)
{
	uint skinWeightCount = 0;
	uint3 tmpBuffer;
	row_major float4x4 animationMat[96];
};

struct BlendData
{
	float4 blend[24];
};

float4 BlendMatrix(BlendData _blendPow,float4 _pos)
{
	float4 pos = skinWeightCount > 0 ? 0 : _pos;

	for (uint i = 0; i < skinWeightCount; i++)
	{
		pos += mul(_pos, animationMat[i] * _blendPow.blend[i / 4][i % 4]);
	}

	return pos;


}