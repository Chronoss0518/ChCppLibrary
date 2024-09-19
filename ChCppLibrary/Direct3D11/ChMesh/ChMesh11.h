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
		struct DrawPrimitiveData11CRT
		{
#ifdef CRT
			std::vector<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexArray;
			std::vector<unsigned long> indexArray;

			ChPtr::Shared<Ch3D::MaterialData<CharaType>> mate;
			std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
#endif
		};

		DrawPrimitiveData11();

		virtual ~DrawPrimitiveData11();

		ChLMat drawMat;
		IndexBuffer11 indexBuffer;
		VertexBuffer11<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexBuffer;

		DrawPrimitiveData11CRT& ValueIns() { return *value; }

	private:

		DrawPrimitiveData11CRT* value = nullptr;

	};

	template<typename CharaType>
	class FrameComponent11 :public ChCpp::BaseComponent
	{
	public:

		struct FrameComponent11CRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<DrawPrimitiveData11<CharaType>>>primitives;
			std::vector<ChPtr::Shared<TargetBoneData11<CharaType>>>boneList;
#endif
		};

	public:

		FrameComponent11();

		virtual ~FrameComponent11();

	public://Create Functions//

		//子オブジェクトすべてを作成する。//
		void CreateAll(ID3D11Device* _device, Mesh11<CharaType>& _rootObject);

	public://Set Functions//

		void SetBoneData(CB::CBBone11& _bone);

#ifdef CRT
		void SetPrimitives(ChPtr::Shared<DrawPrimitiveData11<CharaType>> _primitive)
		{
			value->primitives.push_back(_primitive);
		}

		std::vector<ChPtr::Shared<DrawPrimitiveData11<CharaType>>>& GetPrimitives()
		{
			return value->primitives;
		}
#endif

		ChCpp::FrameComponent<CharaType>* GetFrameCom() { return frameCom; }

	private:
		ChCpp::FrameComponent<CharaType>* frameCom = nullptr;
		ChLMat boneLMats[16];

		FrameComponent11CRT* value = nullptr;
	};
}

#ifdef CRT

template<typename CharaType>
ChD3D11::DrawPrimitiveData11<CharaType>::DrawPrimitiveData11()
{
	value = new DrawPrimitiveData11CRT();
}

template<typename CharaType>
ChD3D11::DrawPrimitiveData11<CharaType>::~DrawPrimitiveData11()
{
	vertexBuffer.Release();
	indexBuffer.Release();

	delete value;
}

template<typename CharaType>
ChD3D11::FrameComponent11<CharaType>::FrameComponent11()
{
	value = new FrameComponent11CRT();
}

template<typename CharaType>
ChD3D11::FrameComponent11<CharaType>::~FrameComponent11()
{
	delete value;
}

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::CreateAll(ID3D11Device* _device, Mesh11<CharaType>& _rootObject)
{
	if (ChPtr::NullCheck(_device))return;

	auto&& frameBase = LookObj()->GetComponent<ChCpp::FrameComponent<CharaType>>();

	if (frameBase != nullptr)
	{
		frameCom = frameBase.get();

		for (auto&& material : frameBase->ValueIns().materialList)
		{
			auto&& primitive11 = ChPtr::Make_S<DrawPrimitiveData11<CharaType>>();
			primitive11->ValueIns().mate = material;

			for (unsigned char i = 0; i < ChStd::EnumCast(Ch3D::TextureType::None); i++)
			{
				Ch3D::TextureType type = static_cast<Ch3D::TextureType>(i);

				auto&& texPath = material->ValueIns().textures.find(type);
				if (texPath == material->ValueIns().textures.end())continue;
				if ((*texPath).second.empty())continue;

				auto texture = ChPtr::Make_S<Texture11>();
				texture->CreateTexture((*texPath).second, _device);

				if (!texture->IsTex())texture = nullptr;

				primitive11->ValueIns().textures[type] = texture;
			}

			value->primitives.push_back(primitive11);
		}

		for (auto&& primitive : frameBase->ValueIns().primitives)
		{
			auto&& primitive11 = value->primitives[primitive->mateNo];

			size_t firstIndex = primitive11->ValueIns().vertexArray.size();
			size_t indexCount = 0;

			for (auto&& vertex : primitive->ValueIns().vertexData)
			{
				size_t vertexNo = vertex->vertexNo;

				auto&& tmpVertex = *frameBase->ValueIns().vertexList[vertexNo];

				Ch3D::SkinMeshVertex<16> mVertex;
				Ch3D::SetPosition(&mVertex, tmpVertex.pos);
				Ch3D::SetUV(&mVertex, vertex->uv);
				Ch3D::SetColor(&mVertex, tmpVertex.color);
				Ch3D::SetNormal(&mVertex, tmpVertex.normal);
				Ch3D::SetFaceNormal(&mVertex, primitive->faceNormal);
				mVertex.boneNum = static_cast<unsigned long>(tmpVertex.ValueIns().blendPow.size());
				for (size_t i = 0; i < mVertex.boneNum; i++)
				{
					mVertex.blendPows[i] = tmpVertex.ValueIns().blendPow[i];
				}

				primitive11->ValueIns().vertexArray.push_back(mVertex);

				indexCount++;
			}

			for (unsigned long i = 1; i < indexCount - 1; i++)
			{
				primitive11->ValueIns().indexArray.push_back(static_cast<unsigned long>(firstIndex));
				primitive11->ValueIns().indexArray.push_back(static_cast<unsigned long>(firstIndex + i));
				primitive11->ValueIns().indexArray.push_back(static_cast<unsigned long>(firstIndex + i + 1));
			}
		}

		for (auto&& prim : value->primitives)
		{

			if (prim->ValueIns().indexArray.empty())continue;
			if (prim->ValueIns().vertexArray.empty())continue;

			prim->indexBuffer.CreateBuffer(
				_device,
				&prim->ValueIns().indexArray[0],
				static_cast<unsigned long>(prim->ValueIns().indexArray.size()));

			prim->vertexBuffer.CreateBuffer(
				_device,
				&prim->ValueIns().vertexArray[0],
				static_cast<unsigned long>(prim->ValueIns().vertexArray.size()));
		}

		for (auto boneData : frameBase->ValueIns().boneDatas)
		{
			auto bone = ChPtr::Make_S<TargetBoneData11<CharaType>>();
			bone->boneData = boneData;
			auto&& objectList = _rootObject.GetAllChildlenConstainsName<ChCpp::FrameObject<CharaType>>(boneData->ValueIns().boneObjectName);
			bone->targetObject = objectList.empty() ? nullptr : objectList[0].lock();
			value->boneList.push_back(bone);
		}
	}

	for (auto&& cbildObj : LookObj()->GetAllChildlen())
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
	if (value->boneList.empty())return;

	value->boneList[value->boneList.size() - 1]->targetObject->UpdateAllDrawTransform();
	for (size_t i = 0; i < value->boneList.size(); i++)
	{
		size_t useNum = value->boneList.size() - 1 - i;

		_bone.SetBoneObjectDrawMatrix(value->boneList[useNum]->targetObject->GetDrawLHandMatrix(), static_cast<unsigned long>(i));
		_bone.SetBoneOffsetMatrix(value->boneList[useNum]->boneData->boneOffset, static_cast<unsigned long>(i));
	}
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (_device == nullptr)return;

	Release();

	device = _device;

	ChCpp::ModelObject<CharaType>::Init();

}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Init()
{
	if (!D3D11API().IsInit())return;
	Init(D3D11Device());
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::CreateFrames()
{
	auto fCom11 = ChCpp::BasicObject::GetComponent<ChD3D11::FrameComponent11<CharaType>>();

	if (fCom11 != nullptr)return;

	auto frame = ChCpp::BasicObject::SetComponent<ChD3D11::FrameComponent11<CharaType>>();

	frame->CreateAll(device, *this);
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Release()
{
	ChCpp::ModelObject<CharaType>::Release();
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Create()
{
	if (!ChCpp::ModelObject<CharaType>::IsInit())return;
	CreateFrames();
}

#endif

#endif