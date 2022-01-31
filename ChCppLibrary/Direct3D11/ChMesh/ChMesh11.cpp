
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

		normalTex = ChPtr::Make_S<Texture11>();
		whiteTex = ChPtr::Make_S<Texture11>();

		normalTex->CreateColorTexture(_device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);
		whiteTex->CreateColorTexture(_device, ChVec4(1.0f), 1, 1);

		mateBuffer.CreateBuffer(_device, ChStd::EnumCast(ModelConstantRegisterNo::Material));
		boneData.CreateBuffer(_device, ChStd::EnumCast(ModelConstantRegisterNo::BoneDatas));

		SetDevice(_device);
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
		, const ChCpp::ModelFrame::Frame& _baseModels
		, const ChMat_11& _parentMat)
	{

		_frames = ChPtr::Make_S<FrameData11>();

		CreatePrimitiveData(_frames, _baseModels);

		_frames->toWorldMat = _frames->baseMat * _parentMat;

		for (auto&& models : _baseModels.childFrames)
		{
			ChPtr::Shared<FrameData11> tmp;
			CreateFrames(tmp, *models,_frames->toWorldMat);
			_frames->childFrame.push_back(tmp);
			tmp->parentFrame = _frames;
		}
		_frames->frameName = _baseModels.myName;

		_frames->toWorldMat.Inverse();

		frameNames[_frames->frameName] = _frames;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreatePrimitiveData(
		ChPtr::Shared<FrameData11>& _frames
		, const ChCpp::ModelFrame::Frame& _baseModels)
	{

		if (_baseModels.mesh == nullptr)return;

		_frames->baseMat = _baseModels.baseLMat;

		for (auto&& skinWeight : _baseModels.mesh->boneList)
		{
			_frames->boneNameAddOrderList.push_back(skinWeight->frameBoneName);
			auto mat = ChPtr::Make_S<ChMat_11>();
			*mat = skinWeight->frameToBoneLMat;
			_frames->skinDataList[skinWeight->frameBoneName] = mat;
		}

		_frames->boneData.skinWeightCount = _frames->skinDataList.size();

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
			
			auto prim = ChPtr::Make_S<PrimitiveData11<SkinMeshVertex11>>();

			for (auto&& face : faces)
			{
				prim->vertexNum += face->vertexData.size();

			}

			prim->indexNum = prim->vertexNum;

			prim->vertexArray = new SkinMeshVertex11[prim->vertexNum];

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
				for (unsigned long j = 0; j < faces[fCount]->vertexData.size(); j++)
				{

					auto& vertexs = (prim->vertexArray[nowCount]);

					vertexs.pos = verList[faces[fCount]->vertexData[j]->vertexNo]->pos;
					vertexs.normal = verList[faces[fCount]->vertexData[j]->vertexNo]->normal;
					vertexs.faceNormal = faceNormal;
					//vertexs.blendPow = verList[faces[fCount]->vertexData[j].vertexNo]->blendPow;
					//vertexs.blendIndex = verList[faces[fCount]->vertexData[j].vertexNo]->boneNo;

					vertexs.uvPos = faces[fCount]->vertexData[j]->uvPos;

					for (unsigned long i = 0;i<_frames->boneNameAddOrderList.size();i++)
					{
						vertexs.blendPow[i] = verList[faces[fCount]->vertexData[j]->vertexNo]->skinWeight[_frames->boneNameAddOrderList[i]];
					}

					prim->indexArray[nowCount] = nowCount;

					nowCount++;

				}

			}

			
			prim->vertexBuffer.CreateBuffer(GetDevice(), prim->vertexArray, prim->vertexNum);
			prim->indexBuffer.CreateBuffer(GetDevice(),prim->indexArray, prim->indexNum);

			prim->mate = ChPtr::Make_S<Material11>();

			prim->mate->material.ambient = ChVec4(mateList[i]->ambient);
			prim->mate->material.diffuse = mateList[i]->diffuse;
			prim->mate->material.specular = mateList[i]->specular;
			prim->mate->materialName = mateList[i]->materialName;

			prim->mate->material.frameMatrix = _baseModels.baseLMat;

			prim->mate->diffuseMap->CreateTexture(mateList[i]->diffuseMap, GetDevice());
			prim->mate->ambientMap->CreateTexture(mateList[i]->ambientMap, GetDevice());
			prim->mate->specularMap->CreateTexture(mateList[i]->specularMap, GetDevice());
			prim->mate->specularHighLightMap->CreateTexture(mateList[i]->specularHighLightMap, GetDevice());
			prim->mate->bumpMap->CreateTexture(mateList[i]->bumpMap, GetDevice());
			prim->mate->alphaMap->CreateTexture(mateList[i]->alphaMap, GetDevice());
			prim->mate->normalMap->CreateTexture(mateList[i]->normalMap, GetDevice());
			prim->mate->metallicMap->CreateTexture(mateList[i]->metallicMap, GetDevice());

			if (!prim->mate->diffuseMap->IsTex())prim->mate->diffuseMap = whiteTex;
			if (prim->mate->normalMap->IsTex())prim->mate->normalMap = normalTex;

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

		unsigned int strides = sizeof(PrimitiveVertex11);
		unsigned int offsets = 0;
		BoneData11 tmpBoneData;
		UpdateFrame(_dc);

		for (auto&& frame : frameList)
		{

			boneData.UpdateResouce(_dc, &tmpBoneData);

			if (!frame->boneNameAddOrderList.empty())
			{
				boneData.UpdateResouce(_dc, &frame->boneData);
			}

			boneData.SetToVertexShader(_dc,1);

			for (auto&& prim : frame->primitiveDatas)
			{
				prim.second->vertexBuffer.SetVertexBuffer(_dc, offsets);
				prim.second->indexBuffer.SetIndexBuffer(_dc);

				mateBuffer.UpdateResouce(_dc, &prim.second->mate->material);

				if(prim.second->mate->diffuseMap->IsTex())prim.second->mate->diffuseMap->SetDrawData(_dc, ChStd::EnumCast(TextureRegisterNo::DiffesTex));

				if (prim.second->mate->normalMap->IsTex())prim.second->mate->normalMap->SetDrawData(_dc, ChStd::EnumCast(TextureRegisterNo::NormalMap));

				mateBuffer.SetToVertexShader(_dc);
				mateBuffer.SetToPixelShader(_dc);

				_dc->DrawIndexed(prim.second->indexNum, 0, 0);

			}
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::UpdateFrame(ID3D11DeviceContext* _dc)
	{

		if (modelData == nullptr)return;
		
		for (auto&& frame : frameList)
		{
			if (frame->boneNameAddOrderList.size() <= 0)continue;
			for (unsigned long i = 0; i < frame->boneNameAddOrderList.size(); i++)
			{
				auto boneFrame = frameNames[frame->boneNameAddOrderList[i]];

				//ChMat_11 inversWorldMat = boneFrame->worldMat;
				//inversWorldMat.Inverse();
				ChMat_11 offMat = *frame->skinDataList[frame->boneNameAddOrderList[i]];

				ChMat_11 aniMat = UpdateAnimation(boneFrame);
				//frame->boneData.animationMat[i] = aniMat * inversWorldMat * offMat;
				frame->boneData.animationMat[i] = aniMat * offMat;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////

	ChMat_11 Mesh11::UpdateAnimation(const ChPtr::Shared<FrameData11>& _frame)
	{
		ChMat_11 frameOffset = _frame->baseMat;
		ChMat_11 aniMat = _frame->animationMat;
		aniMat = frameOffset * aniMat;

		auto parent = _frame->parentFrame.lock();

		if (parent == nullptr)
		{
			return aniMat;
		}

		ChMat_11 parentMat = UpdateAnimation(parent);

		aniMat = parentMat * aniMat;

		return aniMat;
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