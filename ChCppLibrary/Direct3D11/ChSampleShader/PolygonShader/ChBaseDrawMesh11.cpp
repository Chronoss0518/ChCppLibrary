#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBLight/ChCBLight11.h"
#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"

#include"ChBaseDrawMesh11.h"

using namespace ChD3D11;
using namespace Shader;


void BaseDrawMesh::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	SetInitFlg(true);
}

void BaseDrawMesh::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	SetInitFlg(false);
}

void BaseDrawMesh::SetDirectionalLightData(const ChDirectionalLight& _data)
{
	light.SetDirectionLightData(_data);
}

void BaseDrawMesh::SetPointLightData(const ChPointLight& _data, const unsigned long _no)
{
	light.SetPointLightData(_data, _no);
}

void BaseDrawMesh::SetProjectionMatrix(const ChLMat& _mat)
{
	polyData.SetProjectionMatrix(_mat);
}

void BaseDrawMesh::SetViewMatrix(const ChLMat& _mat)
{
	polyData.SetViewMatrix(_mat);
}

void BaseDrawMesh::SetFillMode(const D3D11_FILL_MODE _fill)
{
	fill = _fill;

	updateFlg = true;
}

void BaseDrawMesh::SetCullMode(const D3D11_CULL_MODE _cull)
{
	cull = _cull;

	updateFlg = true;
}

void BaseDrawMesh::SetShaderLightData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;

	light.SetPSDrawData(_dc);
}

void BaseDrawMesh::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;

	polyData.SetVSDrawData(_dc);
}

void BaseDrawMesh::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;

	polyData.SetVSCharaData(_dc);
}

void BaseDrawMesh::Draw(
	ID3D11DeviceContext* _dc,
	Mesh11& _mesh,
	const ChMat_11& _mat)
{
	if (!_mesh.IsMesh())return;

	SetShaderRasteriser(_dc);

	Update();

	polyData.SetWorldMatrix(_mat);

	polyData.SetShaderCharaData(_dc);

	_mesh.SetDrawData(_dc);
}

void BaseDrawMesh::Update()
{
	if (!updateFlg)return;

	D3D11_RASTERIZER_DESC desc
	{
		fill,
		cull,
		true,
		0,
		0.0f,
		0.0f,
		false,
		false,
		true,
		false
	};

	CreateRasteriser(desc);

	updateFlg = false;
}
