#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../ChCB/ChCBBone/ChCBBone11.h"


#ifdef CRT

#include<string>
#include<vector>
#include<map>

#endif

namespace ChD3D11
{

	class Texture11;

	template<typename CharaType>
	class Mesh11 : public ChCpp::ModelObject<CharaType>
	{
	public://Init And Release//

		void Init(ID3D11Device* _device);

		void Init()override;

		void Release()override;

	public://Create Functions//

		void Create()override;

	protected://Create Functions//

		void CreateFrames();

	public://Get Functions//

		inline ID3D11Device* GetDevice() { return device; }

	private:

		ID3D11Device* device = nullptr;
	};


	template<typename CharaType>
	struct TargetBoneData11
	{
#ifdef CRT
		ChPtr::Shared<ChCpp::TargetBoneData<CharaType>> boneData;
		ChPtr::Shared<ChCpp::FrameObject<CharaType>>targetObject;
#endif
	};

	template<typename CharaType>
	struct  DrawPrimitiveData11
	{
		virtual ~DrawPrimitiveData11()
		{
			vertexBuffer.Release();
			indexBuffer.Release();
		}

		ChLMat drawMat;
		IndexBuffer11 indexBuffer;
		VertexBuffer11<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexBuffer;
#ifdef CRT
		std::vector<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexArray;
		std::vector<unsigned long> indexArray;

		ChPtr::Shared<Ch3D::MaterialData<CharaType>> mate;
		std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
#endif
	};

	template<typename CharaType>
	class FrameComponent11 :public ChCpp::BaseComponent
	{
	public://Create Functions//

		//子オブジェクトすべてを作成する。//
		void CreateAll(ID3D11Device* _device, Mesh11<CharaType>& _rootObject);

	public://Set Functions//

		void SetBoneData(CB::CBBone11& _bone);

#ifdef CRT
		void SetPrimitives(ChPtr::Shared<DrawPrimitiveData11<CharaType>> _primitive)
		{
			primitives.push_back(_primitive);
		}

		std::vector<ChPtr::Shared<DrawPrimitiveData11<CharaType>>>& GetPrimitives()
		{
			return primitives;
		}
#endif

		ChCpp::FrameComponent<CharaType>* GetFrameCom() { return frameCom; }

	private:
		ChCpp::FrameComponent<CharaType>* frameCom = nullptr;
		ChLMat boneLMats[16];
#ifdef CRT
		std::vector<ChPtr::Shared<DrawPrimitiveData11<CharaType>>>primitives;
		std::vector<ChPtr::Shared<TargetBoneData11<CharaType>>>boneList;
#endif
	};
}

#ifdef CRT

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::CreateAll(ID3D11Device* _device, Mesh11<CharaType>& _rootObject)
{
	if (ChPtr::NullCheck(_device))return;

	auto&& frameBase = LookObj()->GetComponent<ChCpp::FrameComponent<CharaType>>();

	if (frameBase != nullptr)
	{
		frameCom = frameBase.get();

		for (auto&& material : frameBase->materialList)
		{
			auto&& primitive11 = ChPtr::Make_S<DrawPrimitiveData11<CharaType>>();
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
				primitive11->indexArray.push_back(firstIndex);
				primitive11->indexArray.push_back(firstIndex + i);
				primitive11->indexArray.push_back(firstIndex + i + 1);
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
			auto bone = ChPtr::Make_S<TargetBoneData11<CharaType>>();
			bone->boneData = boneData;
			auto&& objectList = _rootObject.GetAllChildlenConstainsName<ChCpp::FrameObject<CharaType>>(boneData->boneObjectName);
			bone->targetObject = objectList.empty() ? nullptr : objectList[0].lock();
			boneList.push_back(bone);
		}

	}

	for (auto&& cbildObj : LookObj()->GetChildlen())
	{
		auto child = ChPtr::SharedSafeCast<ChCpp::FrameObject<CharaType>>(cbildObj);

		if (child == nullptr)continue;

		auto&& com = child->SetComponent<FrameComponent11<CharaType>>();

		com->CreateAll(_device, _rootObject);
	}

}

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::SetBoneData(CB::CBBone11& _bone)
{
	if (boneList.empty())return;

	boneList[boneList.size() - 1]->targetObject->UpdateAllDrawTransform();
	for (unsigned long i = 0; i < boneList.size(); i++)
	{
		unsigned long useNum = boneList.size() - 1 - i;

		_bone.SetBoneObjectDrawMatrix(boneList[useNum]->targetObject->GetDrawLHandMatrix(), i);
		_bone.SetBoneOffsetMatrix(boneList[useNum]->boneData->boneOffset, i);
	}
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::CreateFrames()
{
	auto fCom11 = ChCpp::BasicObject::GetComponent<ChD3D11::FrameComponent11<CharaType>>();

	if (fCom11 != nullptr)return;

	auto frame = ChCpp::BasicObject::SetComponent<ChD3D11::FrameComponent11<CharaType>>();

	frame->CreateAll(device, *this);
}


#endif

#endif