
cbuffer BoneData :register(b11)
{
	row_major float4x4 SkinWeightMat[4 * 16];
};

float4x4 BlendMatrix(uint4x4 _blend, float4x4 _blendPow, uint _blendNum)
{
	float4x4 BlendMat;

	for (uint i = 0; i < _blendNum; i++)
	{
		uint first = i / 4;
		uint second = i % 4;

		BlendMat += SkinWeightMat[_blend[first][second]] * _blendPow[first][second];
	}

	return BlendMat;


}