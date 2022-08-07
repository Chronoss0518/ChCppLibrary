
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture/ChTexture11.h"
#include"ChMesh11.h"

using namespace Ch3D;
using namespace ChCpp;
using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChMesh11 Method
///////////////////////////////////////////////////////////////////////////////////////

void FrameComponent11::CreateAll(ID3D11Device* _device)
{
	if (ChPtr::NullCheck(_device))return;

	auto&& frameBase = LookObj()->GetComponent<ChCpp::FrameComponent>();

	if (frameBase != nullptr)
	{
		frameCom = frameBase.get();
		mateList = frameBase->materialList;

		for (auto&& primitive : frameBase->primitives)
		{
			auto&& primitive11 = ChPtr::Make_S<DrawPrimitiveData11>();

			std::vector<unsigned long>indexs;

			unsigned long indexCount = 0;

			for (auto&& vertex : primitive->vertexData)
			{
				unsigned long vertexNo = vertex->vertexNo;

				auto tmpVertex = frameBase->vertexList[vertexNo];

				indexs.push_back(indexCount);

				Ch3D::MeshVertex mVertex;
				Ch3D::SetPosition(&mVertex, tmpVertex->pos);
				Ch3D::SetUV(&mVertex, vertex->uv);
				Ch3D::SetColor(&mVertex, tmpVertex->color);
				Ch3D::SetNormal(&mVertex, tmpVertex->normal);
				Ch3D::SetFaceNormal(&mVertex, primitive->faceNormal);

				primitive11->vertexArray.push_back(mVertex);

				indexCount++;
			}

			bool lRotFlg = true;

			for (unsigned long i = 1; i < indexs.size() - 1; i++)
			{

				unsigned long tmpIndexs[] = { 0,i,i + 1 };

				if (!lRotFlg)
				{
					tmpIndexs[1] += tmpIndexs[2];
					tmpIndexs[2] = tmpIndexs[1] - tmpIndexs[2];
					tmpIndexs[1] = tmpIndexs[1] - tmpIndexs[2];
				}

				for (unsigned long j = 0; j < 3; j++)
				{
					primitive11->indexArray.push_back(tmpIndexs[j]);
				}

				lRotFlg = !lRotFlg;

			}

			primitive11->indexBuffer.CreateBuffer(
				_device,
				&primitive11->indexArray[0],
				primitive11->indexArray.size());

			primitive11->vertexBuffer.CreateBuffer(
				_device,
				&primitive11->vertexArray[0],
				primitive11->vertexArray.size());

			primitive11->mateNo = primitive->mateNo;

			auto&& material = frameBase->materialList[primitive11->mateNo];

			for (unsigned char i = 0; i < ChStd::EnumCast(Ch3D::TextureType::None); i++)
			{
				Ch3D::TextureType type = static_cast<Ch3D::TextureType>(i);

				std::string texPath = material->textures[type];
				if (texPath.empty())continue;

				auto texture = ChPtr::Make_S<Texture11>();
				texture->CreateTexture(texPath, _device);

				if (!texture->IsTex())texture = nullptr;

				primitive11->textures[type] = texture;
			}

			primitives.push_back(primitive11);

		}

	}

	for (auto&& wObj : LookObj<FrameObject>()->GetChildlen())
	{
		if (wObj.expired())continue;
		auto child = wObj.lock();

		auto&& com = child->SetComponent<FrameComponent11>();

		com->CreateAll(_device);
	}

}

void Mesh11::Init(ID3D11Device* _device)
{
	if (_device == nullptr)return;

	Release();

	device = _device;
	Texture11::CreateWhiteTex(_device);
	Texture11::CreateNormalTex(_device);

	ModelObject::Init();

}

///////////////////////////////////////////////////////////////////////////////////////

void Mesh11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());

}

///////////////////////////////////////////////////////////////////////////////////////

void Mesh11::Release()
{
	ModelObject::Release();
}

///////////////////////////////////////////////////////////////////////////////////////

void Mesh11::Create()
{
	if (!IsInit())return;

	CreateFrames();

}

///////////////////////////////////////////////////////////////////////////////////////

void Mesh11::CreateFrames()
{

	auto fCom11 = GetComponent<FrameComponent11>();

	if (fCom11 != nullptr)return;

	auto frame = SetComponent<FrameComponent11>();

	frame->CreateAll(device);

}

///////////////////////////////////////////////////////////////////////////////////////
