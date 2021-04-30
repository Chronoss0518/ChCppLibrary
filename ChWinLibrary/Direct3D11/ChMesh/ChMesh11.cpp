
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture/ChTexture11.h"
#include"ChMesh11.h"

namespace ChD3D11
{
	///////////////////////////////////////////////////////////////////////////////////////
	//ChMesh11 Method
	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Init(
		ID3D11Device* _Device)
	{
		if (_Device == nullptr)return;

		Release();

		SetDevice(_Device);

		NormalTex = ChPtr::Make_S<Texture11>();
		WhiteTex = ChPtr::Make_S<Texture11>();

		NormalTex->CreateColorTexture(_Device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);
		WhiteTex->CreateColorTexture(_Device, ChVec4(1.0f), 1, 1);

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
		FrameList.clear();
		ShaderObject<PrimitiveVertex11>::Release();
		ModelData = nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Create(const ChCpp::ModelObject& _BaseModels)
	{
		if (_BaseModels.GetModel() == nullptr)return;
		auto Model = _BaseModels.GetModel();
		if (Model->modelData == nullptr)return;

		CreateFrames(ModelData,*Model->modelData);

		ModelData->FrameName = Model->modelData->myName;

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreateFrames(
		ChPtr::Shared<FrameData11>& _Frames
		, const ChCpp::ModelFrame::Frame& _BaseModels)
	{

		_Frames = ChPtr::Make_S<FrameData11>();
		
		CreatePrimitiveData(_Frames, _BaseModels);

		for (auto&& Models : _BaseModels.childFrames)
		{
			ChPtr::Shared<FrameData11> Tmp;
			CreateFrames(Tmp, *Models);
			_Frames->ChildFrame.push_back(Tmp);
			Tmp->ParentFrame = _Frames;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreatePrimitiveData(
		ChPtr::Shared<FrameData11>& _Frames
		, const ChCpp::ModelFrame::Frame& _BaseModels)
	{

		if (_BaseModels.mesh == nullptr)return;


		_Frames->BaseMat = _BaseModels.baseMat;

		auto SurfaceList = CreateSurfaceList(_BaseModels);

		unsigned long MateNum = _BaseModels.mesh->materialList.size();

		if (MateNum <= 0)
		{
			auto Mate = ChPtr::Make_S<ChCpp::ModelFrame::Material>();

			_BaseModels.mesh->materialList.push_back(Mate);

			Mate->diffuse = ChVec4(1.0f);
			Mate->materialName = "Material1";
			Mate->specular = ChVec4(0.0f);
			Mate->spePow = (0.0f);
			Mate->ambientPow = (0.0f);

			MateNum = _BaseModels.mesh->materialList.size();
		}

		auto& MateList = _BaseModels.mesh->materialList;

		auto& VerList = _BaseModels.mesh->vertexList;

		_Frames->PrimitiveCount = MateNum;

		//PrimitiveCount//
		for (unsigned long i = 0; i< MateNum;i++)
		{

			auto& Faces = SurfaceList[i];
			
			auto Prim = ChPtr::Make_S<PrimitiveData11<PrimitiveVertex11>>();

			Prim->VertexNum = Faces.size() * 3;
			Prim->IndexNum = Faces.size() * 3;


			Prim->VertexArray = new PrimitiveVertex11[Prim->VertexNum];

			Prim->IndexArray = new unsigned long[Prim->IndexNum];

			unsigned long NowCount = 0;

			//FaceCount//
			for (unsigned long FCount = 0; FCount < Faces.size(); FCount++)
			{

				ChVec3_11 FaceNormal = 0.0f;
				FaceNormal = Faces[FCount]->normal;
				//ChVec3_11 FaceNormal = 0.0f;
				//FaceNormal += VerList[Faces[FCount]->VertexData[0].VertexNo]->Normal;
				//FaceNormal += VerList[Faces[FCount]->VertexData[1].VertexNo]->Normal;
				//FaceNormal += VerList[Faces[FCount]->VertexData[2].VertexNo]->Normal;

				//FaceNormal.Normalize();

				//VertexCount//
				for (unsigned long j = 0; j < 3; j++)
				{

					auto& Vertexs = (Prim->VertexArray[NowCount]);

					Vertexs.Pos = VerList[Faces[FCount]->vertexData[j].vertexNo]->pos;
					Vertexs.Normal = VerList[Faces[FCount]->vertexData[j].vertexNo]->normal;
					Vertexs.FaceNormal = FaceNormal;
					Vertexs.BlendPow = VerList[Faces[FCount]->vertexData[j].vertexNo]->blendPow;
					Vertexs.BlendIndex = VerList[Faces[FCount]->vertexData[j].vertexNo]->boneNo;

					Vertexs.UVPos = Faces[FCount]->vertexData[j].uvPos;

					Prim->IndexArray[NowCount] = NowCount;

					NowCount++;

				}

			}

			CreateVertexBuffer(*Prim);
			CreateIndexBuffer(*Prim);

			Prim->Mate = ChPtr::Make_S<Material11>();

			Prim->Mate->Material.Ambient = ChVec4(MateList[i]->ambientPow);
			Prim->Mate->Material.Diffuse = MateList[i]->diffuse;
			Prim->Mate->Material.Specular = MateList[i]->specular;
			Prim->Mate->Material.Specular.a = MateList[i]->spePow;
			Prim->Mate->MaterialName = MateList[i]->materialName;

			Prim->Mate->Material.FrameMatrix = _BaseModels.baseMat;

			CreateContentBuffer<ShaderUseMaterial11>(&Prim->Mate->MBuffer);

			for (auto TexName : MateList[i]->textureNames)
			{
				auto Tex = ChPtr::Make_S<Texture11>();

				Tex->CreateTexture(TexName,GetDevice());

				Prim->Mate->TextureList.push_back(Tex);

			}

			if (Prim->Mate->TextureList.size() <= 0)Prim->Mate->TextureList.push_back(WhiteTex);
			if (Prim->Mate->TextureList.size() <= 1)Prim->Mate->TextureList.push_back(NormalTex);


			_Frames->PrimitiveDatas[MateList[i]->materialName] = Prim;

		}

		FrameList.push_back(_Frames);



	}
	
	///////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
		Mesh11::CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _BaseModels)
	{

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>SurfaceList;

		unsigned long MateNum = _BaseModels.mesh->materialList.size();


		if (MateNum < 2)
		{
			SurfaceList.push_back(_BaseModels.mesh->faceList);
			return SurfaceList;
		}

		unsigned long VerCount = _BaseModels.mesh->faceList.size();

		for (unsigned long i = 0; i < MateNum; i++)
		{
			std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>> Tmp;

			for (unsigned long j = 0; j < VerCount; j++)
			{
				if (_BaseModels.mesh->faceList[j]->materialNo != i)continue;

				auto TmpFace = _BaseModels.mesh->faceList[j];

				Tmp.push_back(TmpFace);
			}
			SurfaceList.push_back(Tmp);
		}

		return SurfaceList;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::SetDrawData(ID3D11DeviceContext* _DC)
	{


		if (ModelData == nullptr)return;

		unsigned int Strides = sizeof(PrimitiveVertex11);
		unsigned int Offsets = 0;


		for (auto&& Frame : FrameList)
		{
			for (auto&& Prim : Frame->PrimitiveDatas)
			{
				_DC->IASetVertexBuffers(0, 1, &Prim.second->Vertexs, &Strides, &Offsets);
				_DC->IASetIndexBuffer(Prim.second->Indexs, DXGI_FORMAT_R32_UINT, 0);

				_DC->UpdateSubresource(Prim.second->Mate->MBuffer,0, nullptr, &Prim.second->Mate->Material, 0, 0);

				for (unsigned long i = 0; i < Prim.second->Mate->TextureList.size(); i++)
				{
					ChPtr::Shared<Texture11> tex = Prim.second->Mate->TextureList[i];

					if (!tex->IsTex())tex = WhiteTex;

					tex->SetDrawData(_DC, i);

					if (i - 1 > 128)break;

				}

				_DC->VSSetConstantBuffers(2, 1, &Prim.second->Mate->MBuffer);
				_DC->PSSetConstantBuffers(2, 1, &Prim.second->Mate->MBuffer);

				_DC->DrawIndexed(Prim.second->IndexNum, 0, 0);

			}
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::SetDrawData(ID3D11DeviceContext* _CD,const std::string& _FrameName)
	{
		if (ModelData == nullptr)return;

		for (auto&& Frame : FrameList)
		{
			for (auto&& Prim : Frame->PrimitiveDatas)
			{

			}
		}

	}


}