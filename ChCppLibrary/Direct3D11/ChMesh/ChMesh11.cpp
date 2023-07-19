
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

void FrameComponent11::CreateAll(ID3D11Device* _device, Mesh11& _rootObject)
{
	if (ChPtr::NullCheck(_device))return;

	auto&& frameBase = LookObj()->GetComponent<ChCpp::FrameComponent>();

	if (frameBase != nullptr)
	{
		frameCom = frameBase.get();
		mateList = frameBase->materialList;

		for (auto&& material : frameBase->materialList)
		{
			auto&& primitive11 = ChPtr::Make_S<DrawPrimitiveData11>();

			primitive11->mate = material;

			for (unsigned char i = 0; i < ChStd::EnumCast(Ch3D::TextureType::None); i++)
			{
				Ch3D::TextureType type = static_cast<Ch3D::TextureType>(i);

				auto&& texPath = material->textures.find(type);
				if (texPath == material->textures.end())continue;
				if ((*texPath).second.empty())continue;

				auto texture = ChPtr::Make_S<Texture11>();
				texture->CreateTexture((*texPath).second, _device);

				if (!texture->IsTex())texture = nullptr;

				primitive11->textures[type] = texture;
			}

			primitives.push_back(primitive11);
		}

		for (auto&& primitive : frameBase->primitives)
		{
			auto&& primitive11 = primitives[primitive->mateNo];

			unsigned long firstIndex = primitive11->vertexArray.size();
			unsigned long indexCount = 0;

			for (auto&& vertex : primitive->vertexData)
			{
				unsigned long vertexNo = vertex->vertexNo;

				auto&& tmpVertex = *frameBase->vertexList[vertexNo];

				Ch3D::SkinMeshVertex<16> mVertex;
				Ch3D::SetPosition(&mVertex, tmpVertex.pos);
				Ch3D::SetUV(&mVertex, vertex->uv);
				Ch3D::SetColor(&mVertex, tmpVertex.color);
				Ch3D::SetNormal(&mVertex, tmpVertex.normal);
				Ch3D::SetFaceNormal(&mVertex, primitive->faceNormal);
				mVertex.boneNum = tmpVertex.blendPow.size();
				for (unsigned long i = 0; i < mVertex.boneNum; i++)
				{
					mVertex.blendPows[i] = tmpVertex.blendPow[i];
				}

				primitive11->vertexArray.push_back(mVertex);

				indexCount++;
			}

			for (unsigned long i = 1; i < indexCount - 1; i++)
			{

				unsigned long tmpIndexs[] = { firstIndex,firstIndex + i,firstIndex + i + 1 };

				for (unsigned long j = 0; j < 3; j++)
				{
					primitive11->indexArray.push_back(tmpIndexs[j]);
				}

			}

		}

		for (auto&& prim : primitives)
		{

			if (prim->indexArray.empty())continue;
			if (prim->vertexArray.empty())continue;

			prim->indexBuffer.CreateBuffer(
				_device,
				&prim->indexArray[0],
				prim->indexArray.size());

			prim->vertexBuffer.CreateBuffer(
				_device,
				&prim->vertexArray[0],
				prim->vertexArray.size());
		}

		for (auto boneData : frameBase->boneDatas)
		{
			auto bone = ChPtr::Make_S<TargetBoneData11>();
			bone->boneData = boneData;
			auto&& objectList = _rootObject.GetAllChildlenConstainsName<FrameObject>(boneData->boneObjectName);
			bone->targetObject = objectList.empty() ? nullptr : objectList[0].lock();
			boneList.push_back(bone);
		}

	}

	for (auto&& cbildObj : LookObj()->GetChildlen())
	{
		auto child = ChPtr::SharedSafeCast<FrameObject>(cbildObj);

		if (child == nullptr)continue;

		auto&& com = child->SetComponent<FrameComponent11>();

		com->CreateAll(_device, _rootObject);
	}

}

void FrameComponent11::SetBoneData(CB::CBBone11& _bone)
{
	if (boneList.empty())return;

	boneList[boneList.size() - 1]->targetObject->UpdateAllDrawTransform();
	for (unsigned long i = 0; i < boneList.size(); i++)
	{
		unsigned long useNum = boneList.size() - 1 - i;
		
		_bone.SetBoneObjectDrawMatrix(boneList[useNum]->targetObject->GetDrawLHandMatrix(),i);
		_bone.SetBoneOffsetMatrix(boneList[useNum]->boneData->boneOffset,i);
	}
}

void Mesh11::Init(ID3D11Device* _device)
{
	if (_device == nullptr)return;

	Release();

	device = _device;

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

	frame->CreateAll(device,*this);

}

///////////////////////////////////////////////////////////////////////////////////////
