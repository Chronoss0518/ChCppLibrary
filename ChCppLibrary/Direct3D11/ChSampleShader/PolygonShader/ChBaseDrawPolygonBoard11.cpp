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

	polyData.Init(_device);

	SetInitFlg(true);

}

void BaseDrawPolygonBoard11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	SetInitFlg(false);
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
	if (IsDraw())return;

	SampleShaderBase11::DrawStart(_dc);

	SetShaderDrawData(_dc);

	Update();

	SetShaderRasteriser(_dc);
}

void BaseDrawPolygonBoard11::Draw(
	ID3D11DeviceContext* _dc,
	TextureBase11& _tex,
	PolygonBoard11& _polygon,
	const ChMat_11& _mat)
{
	if (!IsDraw())return;
	if (_polygon.GetVertexSize() < 3)return;

	polyData.SetWorldMatrix(_mat);

	auto mate = _polygon.GetMaterial();

	polyData.SetMateDiffuse(mate.diffuse);
	polyData.SetMateSpecularColor(mate.specularColor);
	polyData.SetMateSpecularPower(mate.specularPower);
	polyData.SetMateAmbientColor(mate.ambient);

	polyData.SetShaderMaterialData(_dc);

	polyData.SetBaseTexture(&_tex);
	polyData.SetNormalTexture(nullptr);

	polyData.SetShaderTexture(_dc);

	_polygon.SetDrawData(_dc);
}

void BaseDrawPolygonBoard11::Update()
{
	if (!updateFlg)return;

	//•`‰æ•û–@//
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
