
//--------------------------
//���ʃf�[�^
//--------------------------

#include"MShader.hlsli"

struct PolygonBoardVertex
{

	float4 pos;
	float4 color;
	float2 uv;
	uint2 tmpBuf;
	float3 normal;
	uint tmpBuf2;
};

cbuffer PolygonBoardBuffer : register(b5)
{
	PolygonBoardVertex vertex[3];
};

//--------------------------
//�V�F�[�_�[
//--------------------------
//���_�V�F�_(VertexShader)//
//�|���S���o�[�W����//
VS_OUT main(
	uint _no : BLENDINDICES0
) {
	VS_OUT Out;

	Out.Pos = vertex[_no].pos;

	Out.Pos = mul(Out.Pos, ModelMat);
	//Out.Pos = mul(ModelMat, Out.Pos);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);
	//Out.Pos = mul(ViewMat, Out.Pos);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);
	//Out.Pos = mul(ProMat, Out.Pos);

	Out.ProPos = Out.Pos;

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.UV = vertex[_no].uv;

	//���_�̐F���//
	Out.Color = vertex[_no].color;

	Out.Normal = vertex[_no].normal;
	Out.FaceNormal = vertex[_no].normal;

	Out.Temperature = 0.0f;
	//�o��//
	return Out;
}
