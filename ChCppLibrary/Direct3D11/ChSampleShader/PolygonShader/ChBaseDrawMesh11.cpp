#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBLight/ChCBLight11.h"
#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"

#include"ChBaseDrawMesh11.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define DEBUG 0


void BaseDrawMesh::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	polyData.Init(_device);

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
	//if (!_mesh.IsMesh())return;

	SetShaderRasteriser(_dc);

	polyData.SetWorldMatrix(_mat);

	polyData.UpdateCD(_dc);

	polyData.SetShaderCharaData(_dc);

	Draw(_dc, &_mesh);
}

void BaseDrawMesh::Draw(
	ID3D11DeviceContext* _dc,
	FrameObject* _object)
{
#if DEBUG
	unsigned long start, end;

	std::string debug;

	debug = "Draw Start:" + _object->GetMyName() + "\n";

	OutputDebugString(debug.c_str());

	start = timeGetTime();
#endif
	DrawMain(_dc, _object);
#if DEBUG
	end = timeGetTime();
	debug = "Draw End Time:" + std::to_string(end - start) + "\n";
	OutputDebugString(debug.c_str());
	OutputDebugString(">\n");
	OutputDebugString(">\n");
#endif
	auto&& childlen = _object->GetChildlen<FrameObject>();

	for (auto&& child : childlen)
	{
		auto childObj = child.lock();
		if (childObj == nullptr)continue;
		Draw(_dc,childObj.get());
	}

}

void BaseDrawMesh::DrawMain(
	ID3D11DeviceContext* _dc,
	ChCpp::FrameObject* _object)
{

	auto drawMatrix = _object->GetDrawLHandMatrix();

	auto&& frameCom = _object->GetComponent<FrameComponent11>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->GetPrimitives();

	if (primitives.empty())return;

	auto&& materialList = frameCom->GetMaterialList();

	if (materialList.empty())return;

	unsigned int offsets = 0;

	polyData.SetFrameMatrix(drawMatrix);

	for (auto&& prim : primitives)
	{
		if (prim == nullptr)continue;

		auto&& mate11 = *materialList[prim->mateNo];

		polyData.SetMateDiffuse(mate11.mate.diffuse);
		polyData.SetMateSpecularColor(mate11.mate.specularColor);
		polyData.SetMateSpecularPower(mate11.mate.specularPower);
		polyData.SetMateAmbientColor(mate11.mate.ambient);

		polyData.SetBaseTexture(prim->textures[Ch3D::TextureType::Diffuse].get());
		polyData.SetNormalTexture(prim->textures[Ch3D::TextureType::Normal].get());

		prim->vertexBuffer.SetVertexBuffer(_dc, offsets);
		prim->indexBuffer.SetIndexBuffer(_dc);

		polyData.SetShaderMaterialData(_dc);

		polyData.SetShaderTexture(_dc);

		_dc->DrawIndexed(prim->indexArray.size(), 0, 0);

	}

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
