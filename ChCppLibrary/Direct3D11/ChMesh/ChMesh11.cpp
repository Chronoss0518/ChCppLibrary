
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
		ID3D11Device* _device)
	{
		if (_device == nullptr)return;

		Release();

		device = _device;

		normalTex = ChPtr::Make_S<Texture11>();
		whiteTex = ChPtr::Make_S<Texture11>();

		normalTex->CreateColorTexture(_device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);
		whiteTex->CreateColorTexture(_device, ChVec4(1.0f), 1, 1);

		materialBuffer.CreateBuffer(_device, 2);

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
		frameList.clear();
		materialBuffer.Release();
		modelData = nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Create(const ChCpp::ModelObject& _baseModels)
	{
		if (_baseModels.GetModel() == nullptr)return;
		auto model = _baseModels.GetModel();
		if (model->modelData == nullptr)return;

		CreateFrames(modelData,*model->modelData);

		modelData->frameName = model->modelData->myName;

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreateFrames(
		ChPtr::Shared<FrameData11>& _frames
		, const ChCpp::ModelFrame::Frame& _baseModels)
	{

		_frames = ChPtr::Make_S<FrameData11>();
		
		CreatePrimitiveData(_frames, _baseModels);

		for (auto&& models : _baseModels.childFrames)
		{
			ChPtr::Shared<FrameData11> tmp;
			CreateFrames(tmp, *models);
			_frames->childFrame.push_back(tmp);
			tmp->parentFrame = _frames;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreatePrimitiveData(
		ChPtr::Shared<FrameData11>& _frames
		, const ChCpp::ModelFrame::Frame& _baseModels)
	{

		if (_baseModels.mesh == nullptr)return;


		_frames->baseMat = _baseModels.baseLMat;

		auto surfaceList = CreateSurfaceList(_baseModels);

		unsigned long mateNum = _baseModels.mesh->materialList.size();

		if (mateNum <= 0)
		{
			auto mate = ChPtr::Make_S<ChCpp::ModelFrame::Material>();

			_baseModels.mesh->materialList.push_back(mate);

			mate->diffuse = ChVec4(1.0f);
			mate->materialName = "Material1";
			mate->specular = ChVec4(0.0f);
			mate->ambient = (0.0f);

			mateNum = _baseModels.mesh->materialList.size();
		}

		auto& mateList = _baseModels.mesh->materialList;

		auto& verList = _baseModels.mesh->vertexList;

		_frames->primitiveCount = mateNum;

		//PrimitiveCount//
		for (unsigned long i = 0; i< mateNum;i++)
		{

			auto& faces = surfaceList[i];
			
			auto prim = ChPtr::Make_S<PrimitiveData11<PrimitiveVertex11>>();

			prim->vertexNum = faces.size() * 3;
			prim->indexNum = faces.size() * 3;


			prim->vertexArray = new PrimitiveVertex11[prim->vertexNum];

			prim->indexArray = new unsigned long[prim->indexNum];

			unsigned long nowCount = 0;

			//FaceCount//
			for (unsigned long fCount = 0; fCount < faces.size(); fCount++)
			{

				ChVec3_11 faceNormal = 0.0f;
				faceNormal = faces[fCount]->normal;
				//ChVec3_11 faceNormal = 0.0f;
				//faceNormal += verList[faces[fCount]->vertexData[0].vertexNo]->normal;
				//faceNormal += verList[faces[fCount]->vertexData[1].vertexNo]->normal;
				//faceNormal += verList[faces[fCount]->vertexData[2].vertexNo]->normal;

				//faceNormal.Normalize();

				//VertexCount//
				for (unsigned long j = 0; j < 3; j++)
				{

					auto& vertexs = (prim->vertexArray[nowCount]);

					vertexs.pos = verList[faces[fCount]->vertexData[j].vertexNo]->pos;
					vertexs.normal = verList[faces[fCount]->vertexData[j].vertexNo]->normal;
					vertexs.faceNormal = faceNormal;
					//vertexs.blendPow = verList[faces[fCount]->vertexData[j].vertexNo]->blendPow;
					//vertexs.blendIndex = verList[faces[fCount]->vertexData[j].vertexNo]->boneNo;

					vertexs.uv = faces[fCount]->vertexData[j].uvPos;

					prim->indexArray[nowCount] = nowCount;

					nowCount++;

				}

			}

			prim->vertexBuffer.CreateBuffer(GetDevice(), prim->vertexArray, prim->vertexNum);
			prim->indexBuffer.CreateBuffer(GetDevice(), prim->indexArray, prim->indexNum);

			prim->mate = ChPtr::Make_S<Material11>();

			prim->mate->material.ambient = ChVec4(mateList[i]->ambient);
			prim->mate->material.diffuse = mateList[i]->diffuse;
			prim->mate->material.specular = mateList[i]->specular;
			prim->mate->materialName = mateList[i]->materialName;

			prim->mate->material.frameMatrix = _baseModels.baseLMat;

			for (auto texName : mateList[i]->textureNames)
			{
				auto tex = ChPtr::Make_S<Texture11>();

				tex->CreateTexture(texName,GetDevice());

				prim->mate->textureList.push_back(tex);

			}

			if (prim->mate->textureList.size() <= 0)prim->mate->textureList.push_back(whiteTex);
			if (prim->mate->textureList.size() <= 1)prim->mate->textureList.push_back(normalTex);


			_frames->primitiveDatas[mateList[i]->materialName] = prim;

		}

		frameList.push_back(_frames);



	}
	
	///////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
		Mesh11::CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _baseModels)
	{

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>surfaceList;

		unsigned long mateNum = _baseModels.mesh->materialList.size();


		if (mateNum < 2)
		{
			surfaceList.push_back(_baseModels.mesh->faceList);
			return surfaceList;
		}

		unsigned long verCount = _baseModels.mesh->faceList.size();

		for (unsigned long i = 0; i < mateNum; i++)
		{
			std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>> tmp;

			for (unsigned long j = 0; j < verCount; j++)
			{
				if (_baseModels.mesh->faceList[j]->materialNo != i)continue;

				auto tmpFace = _baseModels.mesh->faceList[j];

				tmp.push_back(tmpFace);
			}
			surfaceList.push_back(tmp);
		}

		return surfaceList;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::SetDrawData(ID3D11DeviceContext* _dc)
	{


		if (modelData == nullptr)return;

		unsigned int offsets = 0;


		for (auto&& frame : frameList)
		{
			for (auto&& prim : frame->primitiveDatas)
			{
				prim.second->vertexBuffer.SetVertexBuffer(_dc, offsets);
				prim.second->indexBuffer.SetIndexBuffer(_dc);


				materialBuffer.UpdateResouce(_dc, &prim.second->mate->material);

				for (unsigned long i = 0; i < prim.second->mate->textureList.size(); i++)
				{
					ChPtr::Shared<Texture11> tex = prim.second->mate->textureList[i];

					if (!tex->IsTex())tex = whiteTex;

					tex->SetDrawData(_dc, i);

					if (i - 1 > 128)break;

				}

				materialBuffer.SetToVertexShader(_dc, 1);
				materialBuffer.SetToPixelShader(_dc, 1);

				_dc->DrawIndexed(prim.second->indexNum, 0, 0);

				_dc->Flush();
			}
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::SetDrawData(ID3D11DeviceContext* _dc,const std::string& _frameName)
	{
		if (modelData == nullptr)return;

		for (auto&& frame : frameList)
		{
			for (auto&& prim : frame->primitiveDatas)
			{

			}
		}

	}


}