#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChPolygonBoard/ChPolygonBoard11.h"

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"

#include"ChBaseDrawPolygonBoard11.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define DEBUG 0


void BaseDrawPolygonBoard11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());

	vertexBuffer.CreateBuffer(_device, drawVertexs, 3);

	unsigned long indexs[3] = { 0,1,2 };

	indexBuffer.CreateBuffer(_device, indexs, 3);


}

void BaseDrawPolygonBoard11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	polyData.Release();

	vertexBuffer.Release();
	indexBuffer.Release();
}

void BaseDrawPolygonBoard11::InitVertexShader()
{

#include"../PolygonShader/BasePoboVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[4];


	decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


	SampleShaderBase11::InitVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));

}

void BaseDrawPolygonBoard11::InitPixelShader()
{
#include"../PolygonShader/BasePolygonPixcel.inc"

	SampleShaderBase11::InitPixelShader(main, sizeof(main));
}

void BaseDrawPolygonBoard11::SetProjectionMatrix(const ChLMat& _mat)
{
	polyData.SetProjectionMatrix(_mat);
}

void BaseDrawPolygonBoard11::SetViewMatrix(const ChLMat& _mat)
{
	polyData.SetViewMatrix(_mat);
}

void BaseDrawPolygonBoard11::SetFillMode(const D3D11_FILL_MODE _fill)
{
	fill = _fill;

	updateFlg = true;
}

void BaseDrawPolygonBoard11::SetCullMode(const D3D11_CULL_MODE _cull)
{
	cull = _cull;

	updateFlg = true;
}

void BaseDrawPolygonBoard11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;

	polyData.SetVSDrawData(_dc);
}

void BaseDrawPolygonBoard11::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;

	polyData.SetVSCharaData(_dc);
}

void BaseDrawPolygonBoard11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SampleShaderBase11::DrawStart(_dc);

	SetShaderDrawData(_dc);

}

void BaseDrawPolygonBoard11::Draw(
	ID3D11DeviceContext* _dc,
	TextureBase11& _tex,
	PolygonBoard11& _polygon,
	const ChMat_11& _mat)
{

	if (!IsInit())return;
	if (!IsDraw())return;
	if (_polygon.GetVertexSize() < 3)return;

	polyData.SetWorldMatrix(_mat);
	polyData.SetFrameMatrix(ChLMat());

	polyData.SetShaderCharaData(_dc);

	auto mate = _polygon.GetMaterial();

	polyData.SetMateDiffuse(mate.diffuse);
	polyData.SetMateSpecularColor(mate.specularColor);
	polyData.SetMateSpecularPower(mate.specularPower);
	polyData.SetMateAmbientColor(mate.ambient);

	polyData.SetShaderMaterialData(_dc);

	polyData.SetBaseTexture(&_tex);
	polyData.SetNormalTexture(nullptr);

	polyData.SetShaderTexture(_dc);

	unsigned int offsets = 0;

	auto&& vertexs = _polygon.GetVertexs();

	drawVertexs[0] = *vertexs[0];

	for (unsigned long i = 1; i < vertexs.size() - 1; i++)
	{
		drawVertexs[1] = *vertexs[i];
		drawVertexs[2] = *vertexs[i + 1];

		vertexBuffer.UpdateResouce(_dc, &drawVertexs[0]);

		vertexBuffer.SetVertexBuffer(_dc, offsets);

		indexBuffer.SetIndexBuffer(_dc);

		_dc->DrawIndexed(3, 0, 0);

	}
}

void BaseDrawPolygonBoard11::Update()
{
	if (!updateFlg)return;

	//�`����@//
	D3D11_RASTERIZER_DESC desc
	{
		fill,
		cull,
		false,
		0,
		0.0f,
		0.0f,
		false,
		false,
		true,
		false
	};


	SampleShaderBase11::CreateRasteriser(desc);

	updateFlg = false;
}
