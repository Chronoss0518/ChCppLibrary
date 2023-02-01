#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

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

	SampleShaderBase11::Init(_device);
	
	polyData.Init(_device,&GetWhiteTexture(), &GetNormalTexture());

	boneData.Init(_device);
}

void BaseDrawMesh11::Release()
{
	SampleShaderBase11::Release();

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
	decl[5] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[6] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[7] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[8] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[9] = { "BLENDINDEX",  0, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

	SampleShaderBase11::CreateVertexShader(decl, sizeof(decl)/sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));
}

void BaseDrawMesh11::InitPixelShader()
{

#include"../PolygonShader/BasePolygonPixcel.inc"

	SampleShaderBase11::CreatePixelShader(main, sizeof(main));

}

void BaseDrawMesh11::SetProjectionMatrix(const ChLMat& _mat)
{
	polyData.SetProjectionMatrix(_mat);
}

void BaseDrawMesh11::SetViewMatrix(const ChLMat& _mat)
{
	polyData.SetViewMatrix(_mat);
}

void BaseDrawMesh11::SetFillMode(const D3D11_FILL_MODE _fill)
{
	fill = _fill;

	updateFlg = true;
}

void BaseDrawMesh11::SetCullMode(const D3D11_CULL_MODE _cull)
{
	cull = _cull;

	updateFlg = true;
}

void BaseDrawMesh11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SampleShaderBase11::DrawStart(_dc);

	polyData.SetVSDrawData(_dc);

}

void BaseDrawMesh11::Draw(
	ID3D11DeviceContext* _dc,
	Mesh11& _mesh,
	const ChMat_11& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (ChPtr::NullCheck(_dc))return;

	polyData.SetWorldMatrix(_mat);

	DrawUpdate(_dc, _mesh);

}

void BaseDrawMesh11::DrawUpdate(
	ID3D11DeviceContext* _dc,
	FrameObject& _object)
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

	auto&& childlen = _object.GetChildlen();

	for (auto&& child : childlen)
	{
		auto childObj = ChPtr::SharedSafeCast<FrameObject>(child);
		if (childObj == nullptr)continue;
		DrawUpdate(_dc,*childObj);
	}

}

void BaseDrawMesh11::DrawMain(
	ID3D11DeviceContext* _dc,
	ChCpp::FrameObject& _object)
{

	ChLMat drawMatrix = _object.GetDrawLHandMatrix();

	auto&& frameCom = _object.GetComponent<FrameComponent11>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->GetPrimitives();

	if (primitives.empty())return;

	auto&& materialList = frameCom->GetMaterialList();

	if (materialList.empty())return;

	unsigned int offsets = 0;


	polyData.SetFrameMatrix(drawMatrix);

	polyData.SetVSCharaData(_dc);

	frameCom->SetBoneData(boneData);

	boneData.SetVSDrawData(_dc);

	for (auto&& prim : primitives)
	{
		if (prim == nullptr)continue;

		auto&& mate11 = *prim->mate;

		if (mate11.mate.diffuse.a < ALPHA_VALUE)
		{
			SampleShaderBase11::SetShaderBlender(_dc);
		}
		else
		{
			SampleShaderBase11::SetShaderDefaultBlender(_dc);
		}

		polyData.SetMateDiffuse(mate11.mate.diffuse);
		polyData.SetMateSpecularColor(mate11.mate.specularColor);
		polyData.SetMateSpecularPower(mate11.mate.specularPower);
		polyData.SetMateAmbientColor(mate11.mate.ambient);

		polyData.SetShaderMaterialData(_dc);

		polyData.SetBaseTexture(prim->textures[Ch3D::TextureType::Diffuse].get());
		polyData.SetNormalTexture(prim->textures[Ch3D::TextureType::Normal].get());

		polyData.SetShaderTexture(_dc);

		prim->vertexBuffer.SetVertexBuffer(_dc, offsets);
		prim->indexBuffer.SetIndexBuffer(_dc);

		_dc->DrawIndexed(prim->indexArray.size(), 0, 0);

	}

	SampleShaderBase11::SetShaderDefaultBlender(_dc);

}

void BaseDrawMesh11::Update(ID3D11DeviceContext* _dc)
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
		false,
		true
	};


	SampleShaderBase11::CreateRasteriser(desc);

	updateFlg = false;
}
