
cbuffer BoneData :register(b10)
{
	uint skinWeightCount = 0;
	uint3 tmpBuffer;
	row_major float4x4 SkinWeightMat[96];
	row_major float4x4 frameToBone[96];
};

struct BlendData
{
	float blend[96];
};

float4x4 BlendMatrix(BlendData _blendPow)
{
	float4x4 BlendMat
		= float4x4(
			1.0f, 0.0f, 0.0f, 0.0f
			, 0.0f, 1.0f, 0.0f, 0.0f
			, 0.0f, 0.0f, 1.0f, 0.0f
			, 0.0f, 0.0f, 0.0f, 1.0f);

	for (uint i = 0; i < skinWeightCount; i++)
	{
		uint first = (i / 4) % 4;
		uint second = i % 4;

		BlendMat +=  mul(SkinWeightMat[i], frameToBone[i]) * _blendPow.blend[i];
	}

	return BlendMat;


}