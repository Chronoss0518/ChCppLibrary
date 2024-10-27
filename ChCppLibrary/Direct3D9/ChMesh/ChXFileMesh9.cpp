
#include<Windows.h>

#include"../../CPP/ChFile/ChFile.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChBaseMesh9.h"
#include"MeshIncluder9.h"

CH_NUMBER_FUNCTION_BASE(GetMaterialTag);
#ifndef GET_MATERIAL_TAG
#define GET_MATERIAL_TAG(type) CH_NUMBER_FUNCTION(GetMaterialTag,type)
#endif

CH_NUMBER_FUNCTION_BASE(GetFrameMatTag);
#ifndef GET_FRAME_MATRIX_TAG
#define GET_FRAME_MATRIX_TAG(type) CH_NUMBER_FUNCTION(GetFrameMatTag,type)
#endif

CH_NUMBER_FUNCTION_BASE(GetSkinWaightsTag);
#ifndef GET_SKIN_WAIGHTS_TAG
#define GET_SKIN_WAIGHTS_TAG(type) CH_NUMBER_FUNCTION(GetSkinWaightsTag,type)
#endif

CH_NUMBER_FUNCTION_BASE(GetFrameTag);
#ifndef GET_FRAME_TAG
#define GET_FRAME_TAG(type) CH_NUMBER_FUNCTION(GetFrameTag,type)
#endif

CH_NUMBER_FUNCTION_BASE(GetTemplateTag);
#ifndef GET_TEMPLATE_TAG
#define GET_TEMPLATE_TAG(type) CH_NUMBER_FUNCTION(GetTemplateTag,type)
#endif

#ifndef GET_GET_XFILE_EXTENSION
#define GET_GET_XFILE_EXTENSION(type) CH_NUMBER_FUNCTION(ChMesh::GetXFileExtension,type)
#endif


CH_TO_NUMBER_FUNCTION(GET_MATERIAL_TAG, "Material ");

CH_TO_NUMBER_FUNCTION(GET_FRAME_MATRIX_TAG, "FrameTransformMatrix {");

CH_TO_NUMBER_FUNCTION(GET_SKIN_WAIGHTS_TAG, "SkinWeights {");

CH_TO_NUMBER_FUNCTION(GET_FRAME_TAG, "Frame ");

CH_TO_NUMBER_FUNCTION(GET_TEMPLATE_TAG, "template ");

static constexpr char MATERIAL_TAG[] = "Material ";

static constexpr char FRAME_TRANSFORM_MATRINX_TAG[] = "FrameTransformMatrix {";

static constexpr char SKIN_WEIGHTS_TAG[] = "SkinWeights {";

void SetMaterialName(ChMesh::BaseMesh9& _mesh,const std::string& _fileName)
{
	ChCpp::CharFile file;
	file.FileOpen(_fileName);

	std::string tmpStr;
	tmpStr = file.FileRead();

	std::string tmpMateName = MATERIAL_TAG;

	size_t size = 0;

	unsigned int i = 0;

	while ((size = tmpStr.find(tmpMateName, size)) != std::string::npos)
	{
		size += tmpMateName.length();
		size_t tmpNum = tmpStr.find(ChStd::GetStartBraceChara<char>(), size);
		if (tmpNum == std::string::npos)break;
		tmpNum -= (size + 1);
		_mesh.InsMaterials()[i]->name = tmpStr.substr(size, tmpNum);
		size += tmpNum;
		i++;
	}

}

void ChMesh::XFileMesh9::OpenFile(
	const std::string& _fileName,
	const std::string& _pathName,
	const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(".x") == std::string::npos)return;

	std::string tmpStr;
	tmpStr = _pathName + "/" + _fileName;

	if (_pathName.length() <= 0)tmpStr = "." + tmpStr;

	{
		LPD3DXBUFFER tmpBuffer;

		DWORD numMaterial;

		D3DXLoadMeshFromXA(
			tmpStr.c_str(),
			D3DXMESH_MANAGED,
			_dev,
			NULL,
			&tmpBuffer,
			NULL,
			&(numMaterial),
			&(mesh));

		if (ChPtr::NullCheck(mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::string tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {


			auto tmpMat = ChPtr::Make_S<ChMaterial9>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = "";

			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + "/" + tmpString;
				if (_pathName.length() <= 0)tmpString = "." + tmpString;

			}
			material.push_back(tmpMat);

			auto tmpTex = ChTex::BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex()))
				tmpTex->CreateColTexture(_dev);

			texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{
		LPD3DXMESH tmpMesh = nullptr;
		HRESULT res;
		res = mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1,//テクスチャ座標
			_dev,
			&tmpMesh//クローン先
		);

		mesh->Release();

		mesh = tmpMesh;
	}

	SetMaterialName(*this,tmpStr);
}

//SXFlieMesh9 Method//

void ChMesh::SXFileMesh9::OpenFile(
	const std::string& _fileName,
	const std::string& _pathName,
	const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(".x") == std::string::npos)return;

	std::string tmpStr;
	tmpStr = _pathName + "/" + _fileName;

	if (_pathName.length() <= 0)tmpStr = "." + tmpStr;

	{
		LPD3DXBUFFER tmpBuffer;

		DWORD numMaterial;

		D3DXLoadMeshFromXA(
			tmpStr.c_str(),
			D3DXMESH_MANAGED,
			_dev,
			NULL,
			&tmpBuffer,
			NULL,
			&(numMaterial),
			&(mesh));

		if (ChPtr::NullCheck(mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::string tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {

			auto tmpMat = ChPtr::Make_S<ChMaterial9>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = "";
			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + tmpString;
			}
			material.push_back(tmpMat);

			auto tmpTex = ChTex::BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex()))
				tmpTex->CreateColTexture(_dev);

			texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{
		LPD3DXMESH tmpMesh = nullptr;

		HRESULT res;
		res = mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1,//テクスチャ座標
			_dev,
			&tmpMesh//クローン先
		);


		mesh->Release();

		mesh = tmpMesh;
	}

	if (ChPtr::NullCheck(mesh))return;

	SetMaterialName(*this, tmpStr);

	SetOffsetVertex();

	{
		std::string fStr;
		{

			ChCpp::CharFile file;
			file.FileOpen(_pathName + _fileName);
			fStr = file.FileRead();
			file.FileClose();

		}
		SetBone(fStr);

		if (testName.size() <= 0)return;
	}
	testName.clear();
}

void ChMesh::SXFileMesh9::SetBone(const std::string& _fStr)
{

	{
		if (_fStr.find("Frame ") == std::string::npos)return;

		size_t fPos = _fStr.find("Frame ");

		CreateBoneTree(_fStr, fPos);
	}

	SetBoneVertex(_fStr);

	for (auto&& boneName : boneNameList)
	{
		/*
				ChMat_9 tmpMat;

				tmpMat = boneList[boneName]->baseMat;

				boneList[boneName]->baseMat
					= tmpMat * boneList[boneName]->offsetbone->baseMat;
		*/

		if (boneList[boneName]->offsetBone == nullptr)continue;

		/*
				ChMat_9 tmpMat;

				tmpMat = boneList[boneName]->offMat;

				tmpMat.Inverse();

				boneList[boneName]->offMat
					=  tmpMat * boneList[boneName]->offsetBone->offMat;
		*/
	}

}

void ChMesh::SXFileMesh9::SetBoneVertex(const std::string& _fStr)
{
	std::string End = ";";
	size_t fPos = 0;
	if (_fStr.find("template SkinWeights {", fPos) != std::string::npos)
	{
		fPos = _fStr.find("template SkinWeights {", fPos);
		fPos += std::strlen("template SkinWeights {");
	}

	{
		std::string boneName;

		while (_fStr.find(SKIN_WEIGHTS_TAG, fPos) != std::string::npos)
		{

			fPos = _fStr.find(SKIN_WEIGHTS_TAG, fPos);
			fPos = _fStr.find("\"", fPos);
			boneName = _fStr.substr(fPos + 1, _fStr.find("\";", fPos) - fPos - 1);

			if (testName == boneName)break;
			if (testName.size() <= 0)testName = boneName;


			fPos = _fStr.find("\";", fPos);
			fPos += 2;
			fPos = _fStr.find(";", fPos);
			fPos += 2;

			std::vector<unsigned long> tmpNum;

			while (1)
			{
				std::string num = _fStr.substr(fPos, _fStr.find(",", fPos + 1) - fPos);
				auto ver = ChPtr::Make_S<BoneVertex::BonePow>();
				auto VertexNo = std::atol(num.c_str());
				tmpNum.push_back(VertexNo);
				ver->updateMat = &boneList[boneName]->updateMat;
				ver->offMat = &boneList[boneName]->offMat;
				boneVertexList[VertexNo]->updateMat.push_back(ver);
				if (_fStr.find(End, fPos) <= _fStr.find(",", fPos))break;
				fPos = _fStr.find(",", fPos + 1);
				fPos += 2;


			}
			fPos = _fStr.find(End, fPos);
			fPos += 2;


			for (auto&& VerNum : tmpNum)
			{
				std::string num = _fStr.substr(fPos, _fStr.find(",", fPos + 1) - fPos);

				boneVertexList[VerNum]->
					updateMat[boneVertexList[VerNum]->
					updateMat.size() - 1]->
					waitPow = (float)std::atof(num.c_str());

				if (_fStr.find(End, fPos) <= _fStr.find(",", fPos))break;
				fPos = _fStr.find(",", fPos + 1);
				fPos += 2;


			}

			fPos = _fStr.find(End, fPos);
			fPos += 2;
			{
				ChLMatrix tmpMat;
				tmpMat.Deserialize(_fStr, fPos);

				boneList[boneName]->offMat = tmpMat;
			}

		}
	}
}

void ChMesh::SXFileMesh9::CreateBoneTree(
	const std::string& _fStr
	, size_t& _fPos
	, const ChPtr::Shared<Bone>& _bone)
{
	_fPos += 6;
	size_t tmpPos = _fStr.find(" {", _fPos);

	if (boneList.find(_fStr.substr(_fPos, tmpPos - _fPos)) != boneList.end())return;

	auto tmpBone = ChPtr::Make_S<Bone>();
	tmpBone->offsetBone = _bone;

	std::string test = _fStr.substr(_fPos, tmpPos - _fPos);
	boneList[test] = tmpBone;
	tmpBone->myName = test;
	boneNameList.push_back(test);

	_fPos = _fStr.find(FRAME_TRANSFORM_MATRINX_TAG, _fPos);

	_fPos += sizeof(FRAME_TRANSFORM_MATRINX_TAG);

	{
		ChLMatrix tmpMat;
		tmpMat.Deserialize(_fStr, _fPos);
		tmpBone->baseMat = tmpMat;
	}

	_fPos = _fStr.find("}", _fPos);
	_fPos += 1;

	////メッシュ取得//
	//if (_fStr.find("mesh {", _fPos) <= _fStr.find("}", _fPos))
	//{
	//	size_t tmp = vertexNum;
	//	_fPos = _fStr.find("mesh {", _fPos);
	//	_fPos = _fStr.find("\n", _fPos);
	//	_fPos += 1;
	//	std::string num = _fStr.substr(_fPos, _fStr.find(";", _fPos) - _fPos);
	//	vertexNum += std::atol(num.c_str());
	//}

	while (_fStr.find("}", _fPos) >= _fStr.find("Frame ", _fPos))
	{
		_fPos = _fStr.find("Frame ", _fPos);
		if (_fPos == std::string::npos)break;
		CreateBoneTree(_fStr, _fPos, tmpBone);

	}

	_fPos = _fStr.find("}", _fPos);
	_fPos += 1;
}
