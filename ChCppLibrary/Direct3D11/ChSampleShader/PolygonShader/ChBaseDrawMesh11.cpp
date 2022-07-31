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

	//Update();

	polyData.SetWorldMatrix(_mat);

	polyData.UpdateCD(_dc);

	polyData.SetShaderCharaData(_dc);

	Draw(_dc, &_mesh);
}

void BaseDrawMesh::Draw(
	ID3D11DeviceContext* _dc,
	FrameObject* _object,
	const ChLMat _parentFrameMat)
{
	_object->UpdateDrawTransform();

	DrawMain(_dc, _object, _parentFrameMat);

	for (auto&& child : _object->GetChildlen<FrameObject>())
	{
		auto childObj = child.lock();
		if (childObj == nullptr)continue;
		Draw(_dc,childObj.get(), _object->GetDrawTransform().GetLeftHandMatrix());
	}

}

void BaseDrawMesh::DrawMain(
	ID3D11DeviceContext* _dc,
	ChCpp::FrameObject* _object,
	const ChLMat _parentFrameMat)
{

	unsigned int offsets = 0;

	auto baseFrame = _object->GetComponent<FrameComponent>();

	if (baseFrame == nullptr)return;

	if (baseFrame->primitives.empty())return;

	auto frameCom = _object->GetComponent<FrameComponent11>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->GetPrimitives();

	if (primitives.empty())return;

	polyData.SetFrameMatrix(_object->GetDrawTransform().GetLeftHandMatrix());

	for (auto&& prim : primitives)
	{
		if (prim == nullptr)continue;

		prim->vertexBuffer.SetVertexBuffer(_dc, offsets);
		prim->indexBuffer.SetIndexBuffer(_dc);

		auto&& mate11 = baseFrame->materialList[prim->mateNo];

		ChP_Material mate;
		mate.dif = mate11->mate.diffuse;
		mate.speCol = mate11->mate.specularColor;
		mate.spePow = mate11->mate.specularPower;
		mate.ambient = mate11->mate.ambient;

		polyData.SetMaterialData(mate);

		{
			Texture11* diffuseMap = prim->textures[Ch3D::TextureType::Diffuse].get();
			polyData.SetBaseTexture(diffuseMap);
		}

		{
			Texture11* normalMap = prim->textures[Ch3D::TextureType::Normal].get();
			polyData.SetNormalTexture(normalMap);
		}

		polyData.SetShaderTexture(_dc);

		_dc->DrawIndexed(prim->indexArray.size(), 0, 0);

		_dc->Flush();

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
