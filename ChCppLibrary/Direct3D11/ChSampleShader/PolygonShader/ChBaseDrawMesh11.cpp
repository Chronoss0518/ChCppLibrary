#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../../CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBLight/ChCBLight11.h"
#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"../../ChCB/ChCBBone/ChCBBone11.h"

#include"ChBaseDrawMesh11.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define ALPHA_VALUE 0.99f
#define DEBUG 0

void BaseDrawMesh11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);
	
	polyData.Init(_device,&GetWhiteTexture(), &GetNormalTexture());

	boneData.Init(_device);
}

void BaseDrawMesh11::Release()
{
	SamplePolygonShaderBase11::Release();

	polyData.Release();
}

void BaseDrawMesh11::InitVertexShader()
{

#include"../PolygonShader/BaseMeshVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[10];

	decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[4] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[5] = { "BLENDINDEX",  0, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[6] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[7] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[8] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[9] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	

	SamplePolygonShaderBase11::CreateVertexShader(decl, sizeof(decl)/sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));
}

void BaseDrawMesh11::InitPixelShader()
{

#include"../PolygonShader/BasePolygonPixcel.inc"

	SamplePolygonShaderBase11::CreatePixelShader(main, sizeof(main));

}

void BaseDrawMesh11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SamplePolygonShaderBase11::DrawStart(_dc);

}

void BaseDrawMesh11::Draw(
	Mesh11& _mesh,
	const ChMat_11& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (ChPtr::NullCheck(GetDC()))return;

	worldMat = _mat;

	DrawUpdate(_mesh);

}

void BaseDrawMesh11::DrawUpdate(FrameObject& _object)
{

#if DEBUG
	unsigned long start, end;

	std::string debug;

	debug = "Draw Start:" + _object->GetMyName() + "\n";

	OutputDebugString(debug.c_str());

	start = timeGetTime();
#endif

	DrawMain(_object);

#if DEBUG
	end = timeGetTime();
	debug = "Draw End Time:" + std::to_string(end - start) + "\n";
	OutputDebugString(debug.c_str());
	OutputDebugString(">\n");
	OutputDebugString(">\n");
#endif

	auto&& childlen = _object.GetChildlen();

	for (auto&& child : childlen)
	{
		auto childObj = ChPtr::SharedSafeCast<FrameObject>(child);
		if (childObj == nullptr)continue;
		DrawUpdate(*childObj);
	}

}

void BaseDrawMesh11::DrawMain(ChCpp::FrameObject& _object)
{

	ChLMat drawMatrix = _object.GetDrawLHandMatrix();

	auto&& frameCom = _object.GetComponent<FrameComponent11>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->GetPrimitives();

	if (primitives.empty())return;

	auto&& frame = _object.GetComponent<FrameComponent>();

	auto drawData = ChPtr::Make_S<DrawData>();

	drawData->worldMatrix = worldMat;
	drawData->frameMatrix = drawMatrix;
	drawData->drawFrame = frameCom.get();

	drawDatas[frame.get()].push_back(drawData);

}

void BaseDrawMesh11::DrawEnd()
{
	unsigned int offsets = 0;

	for (auto&& drawData : drawDatas)
	{
		if (drawData.second.empty())continue;
		auto&& primitiveData = drawData.second[0]->drawFrame->GetPrimitives();

		for (auto&& prim : primitiveData)
		{
			if (prim == nullptr)continue;

			auto&& mate11 = *prim->mate;

			if (mate11.mate.diffuse.a < ALPHA_VALUE)
			{
				SamplePolygonShaderBase11::SetShaderBlender(GetDC());
			}
			else
			{
				SamplePolygonShaderBase11::SetShaderDefaultBlender(GetDC());
			}

			polyData.SetMateDiffuse(mate11.mate.diffuse);
			polyData.SetMateSpecularColor(mate11.mate.specularColor);
			polyData.SetMateSpecularPower(mate11.mate.specularPower);
			polyData.SetMateAmbientColor(mate11.mate.ambient);

			polyData.SetShaderMaterialData(GetDC());

			prim->vertexBuffer.SetVertexBuffer(GetDC(), offsets);
			prim->indexBuffer.SetIndexBuffer(GetDC());

			for (auto&& drawFrame : drawData.second)
			{

				polyData.SetWorldMatrix(drawFrame->worldMatrix);

				polyData.SetFrameMatrix(drawFrame->frameMatrix);

				polyData.SetVSCharaData(GetDC());

				drawFrame->drawFrame->SetBoneData(boneData);

				boneData.SetVSDrawData(GetDC());

				polyData.SetBaseTexture(prim->textures[Ch3D::TextureType::Diffuse].get());
				polyData.SetNormalTexture(prim->textures[Ch3D::TextureType::Normal].get());

				polyData.SetShaderTexture(GetDC());

				GetDC()->DrawIndexed(prim->indexArray.size(), 0, 0);
			}
		}

		SamplePolygonShaderBase11::SetShaderDefaultBlender(GetDC());

	}
	if(!drawDatas.empty())drawDatas.clear();

	SamplePolygonShaderBase11::DrawEnd();
}

void BaseDrawMesh11::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	SamplePolygonShaderBase11::Update(_dc);

	updateFlg = false;
}
