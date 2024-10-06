
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

CH_TO_NUMBER_FUNCTION(GET_GET_XFILE_EXTENSION, ".x");

template<typename CharaType>
void ChMesh::XFileMeshBase<CharaType>::SetMaterialName(const std::basic_string<CharaType>& _fileName)
{
	ChCpp::File<CharaType> file;
	file.FileOpen(_fileName);

	std::basic_string<CharaType> tmpStr;
	tmpStr = file.FileReadText();

	std::basic_string<CharaType> tmpMateName = GetMaterialTag<CharaType>();

	size_t size = 0;

	unsigned int i = 0;

	while ((size = tmpStr.find(tmpMateName, size)) != std::string::npos)
	{
		size += tmpMateName.length();
		size_t tmpNum = tmpStr.find(ChStd::GetStartBraceChara<CharaType>(), size);
		if (tmpNum == std::string::npos)break;
		tmpNum -= (size + 1);
		BaseMesh9<CharaType>::material[i]->name = tmpStr.substr(size, tmpNum);
		size += tmpNum;
		i++;
	}

}

template<typename CharaType>
void ChMesh::XFileMesh9<CharaType>::OpenFile(
	const std::basic_string<CharaType>& _fileName,
	const std::basic_string<CharaType>& _pathName,
	const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(ChMesh::GetXFileExtension<CharaType>()) == std::basic_string<CharaType>::npos)return;

	std::basic_string<CharaType> tmpStr;
	tmpStr = _pathName + ChStd::GetSlashChara<CharaType>() + _fileName;

	if (_pathName.length() <= 0)tmpStr = ChStd::GetCommaChara<CharaType>() + tmpStr;

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
			&(BaseMesh9<CharaType>::mesh));

		if (ChPtr::NullCheck(BaseMesh9<CharaType>::mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::basic_string<CharaType> tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {


			auto tmpMat = ChPtr::Make_S<ChBaseMaterial_9<CharaType>>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = ChStd::GetZeroChara<CharaType>();

			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + ChStd::GetSlashChara<CharaType>() + tmpString;
				if (_pathName.length() <= 0)tmpString = ChStd::GetCommaChara<CharaType>() + tmpString;

			}
			BaseMesh9<CharaType>::material.push_back(tmpMat);

			auto tmpTex = ChTex::BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex()))
				tmpTex->CreateColTexture(_dev);

			BaseMesh9::texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{
		LPD3DXMESH tmpMesh = nullptr;
		HRESULT res;
		res = BaseMesh9<CharaType>::mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1,//テクスチャ座標
			_dev,
			&tmpMesh//クローン先
		);

		BaseMesh9<CharaType>::mesh->Release();

		BaseMesh9<CharaType>::mesh = tmpMesh;
	}

	SetMaterialName(tmpStr);
}

//SXFlieMesh9 Method//

template<typename CharaType>
void ChMesh::SXFileMesh9<CharaType>::OpenFile(
	const std::basic_string<CharaType>& _fileName,
	const std::basic_string<CharaType>& _pathName,
	const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(ChMesh::GetXFileExtension<CharaType>)() == std::basic_string<CharaType>::npos)return;

	std::basic_string<CharaType> tmpStr;
	tmpStr = _pathName + ChStd::GetSlashChara<CharaType>() + _fileName;

	if (_pathName.length() <= 0)tmpStr = ChStd::GetCommaChara<CharaType>() + tmpStr;

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
			&(BaseMesh9<CharaType>::mesh));

		if (ChPtr::NullCheck(BaseMesh9<CharaType>::mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::basic_string<CharaType> tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {

			auto tmpMat = ChPtr::Make_S<ChMaterialA_9>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = ChStd::GetZeroChara<CharaType>();
			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + tmpString;
			}
			BaseMesh9<CharaType>::material.push_back(tmpMat);

			auto tmpTex = ChTex::BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex()))
				tmpTex->CreateColTexture(_dev);

			BaseMesh9<CharaType>::texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{
		LPD3DXMESH tmpMesh = nullptr;

		HRESULT res;
		res = BaseMesh9<CharaType>::mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1,//テクスチャ座標
			_dev,
			&tmpMesh//クローン先
		);


		BaseMesh9<CharaType>::mesh->Release();

		BaseMesh9<CharaType>::mesh = tmpMesh;
	}

	if (ChPtr::NullCheck(BaseMesh9<CharaType>::mesh))return;

	SetMaterialName(tmpStr);

	BaseMesh9<CharaType>::SetOffsetVertex();

	{
		std::basic_string<CharaType> fStr;
		{

			ChCpp::File<CharaType> file;
			file.FileOpen(_pathName + _fileName);
			fStr = file.FileReadText();
			file.FileClose();

		}
		SetBone(fStr);

		if (BaseMesh9<CharaType>::testName.size() <= 0)return;
	}
	BaseMesh9<CharaType>::testName.clear();
}

template<typename CharaType>
void ChMesh::SXFileMesh9<CharaType>::SetBone(const std::basic_string<CharaType>& _fStr)
{

	{
		size_t fPos = _fStr.find(GetFrameTag<CharaType>());

		if (fPos == std::basic_string<CharaType>::npos)return;

		CreateBoneTree(_fStr, fPos);
	}

	SetBoneVertex(_fStr);

	for (auto&& boneName : SkinMesh9<CharaType>::boneNameList)
	{
		/*
				ChMat_9 tmpMat;

				tmpMat = boneList[boneName]->baseMat;

				boneList[boneName]->baseMat
					= tmpMat * boneList[boneName]->offsetbone->baseMat;
		*/

		if (SkinMesh9<CharaType>::boneList[boneName]->offsetBone == nullptr)continue;

		/*
				ChMat_9 tmpMat;

				tmpMat = boneList[boneName]->offMat;

				tmpMat.Inverse();

				boneList[boneName]->offMat
					=  tmpMat * boneList[boneName]->offsetBone->offMat;
		*/
	}

}

template<typename CharaType>
void ChMesh::SXFileMesh9<CharaType>::SetBoneVertex(const std::basic_string<CharaType>& _fStr)
{
	std::basic_string<CharaType> End = ChStd::GetSemiColonChara<CharaType>();
	size_t fPos = 0;

	std::basic_string<CharaType>tmpTag = GetTemplateTag<CharaType>();

	tmpTag = tmpTag + GetSkinWaightsTag<CharaType>();

	size_t tmpPos = _fStr.find(tmpTag, fPos);
	if (tmpPos != std::basic_string<CharaType>::npos)
	{
		fPos = tmpPos;
		fPos += tmpTag.size();
	}

	{
		std::basic_string<CharaType> boneName;

		tmpPos = _fStr.find(BaseMesh9<CharaType>::skinWaights, fPos);
		while (tmpPos != std::basic_string<CharaType>::npos)
		{

			fPos = tmpPos;
			fPos = _fStr.find(ChStd::GetDBQuotation<CharaType>(), fPos);

			tmpTag = ChStd::GetDBQuotation<CharaType>();
			tmpTag = tmpTag + ChStd::GetSemiColonChara<CharaType>();
			boneName = _fStr.substr(fPos + 1, _fStr.find(tmpTag, fPos) - fPos - 1);

			if (BaseMesh9<CharaType>::testName == boneName)break;
			if (BaseMesh9<CharaType>::testName.size() <= 0)BaseMesh9<CharaType>::testName = boneName;


			fPos = _fStr.find(tmpTag, fPos);
			fPos += tmpTag.size();
			fPos = _fStr.find(ChStd::GetSemiColonChara<CharaType>(), fPos);
			fPos += 2;

			std::vector<unsigned long> tmpNum;

			while (1)
			{
				std::basic_string<CharaType> num = _fStr.substr(fPos, _fStr.find(ChStd::GetCommaChara<CharaType>(), fPos + 1) - fPos);
				auto ver = ChPtr::Make_S<typename SkinMesh9<CharaType>::BoneVertex::BonePow>();
				auto VertexNo = std::atol(num.c_str());
				tmpNum.push_back(VertexNo);
				ver->updateMat = &SkinMesh9<CharaType>::boneList[boneName]->updateMat;
				ver->offMat = &SkinMesh9<CharaType>::boneList[boneName]->offMat;
				SkinMesh9<CharaType>::boneVertexList[VertexNo]->updateMat.push_back(ver);
				if (_fStr.find(End, fPos) <= _fStr.find(ChStd::GetCommaChara<CharaType>(), fPos))break;
				fPos = _fStr.find(ChStd::GetCommaChara<CharaType>(), fPos + 1);
				fPos += 2;


			}
			fPos = _fStr.find(End, fPos);
			fPos += 2;


			for (auto&& VerNum : tmpNum)
			{
				std::basic_string<CharaType> num = _fStr.substr(fPos, _fStr.find(ChStd::GetCommaChara<CharaType>(), fPos + 1) - fPos);

				SkinMesh9<CharaType>::boneVertexList[VerNum]->
					updateMat[SkinMesh9<CharaType>::boneVertexList[VerNum]->
					updateMat.size() - 1]->
					waitPow = (float)std::atof(num.c_str());

				if (_fStr.find(End, fPos) <= _fStr.find(ChStd::GetCommaChara<CharaType>(), fPos))break;
				fPos = _fStr.find(ChStd::GetCommaChara<CharaType>(), fPos + 1);
				fPos += 2;


			}

			fPos = _fStr.find(End, fPos);
			fPos += 2;
			{
				ChLMatrix tmpMat;
				tmpMat.Deserialize(_fStr, fPos);

				SkinMesh9<CharaType>::boneList[boneName]->offMat = tmpMat;
			}

		}
	}
}

template<typename CharaType>
void ChMesh::SXFileMesh9<CharaType>::CreateBoneTree(
	const std::basic_string<CharaType>& _fStr,
	size_t& _fPos,
	const ChPtr::Shared<typename ChMesh::SkinMesh9<CharaType>::Bone>& _bone)
{
	_fPos += 6;
	std::basic_string<CharaType> tmpTag = ChStd::GetSpaceChara<CharaType>();
	tmpTag = tmpTag + ChStd::GetStartBraceChara<CharaType>();

	size_t tmpPos = _fStr.find(tmpTag, _fPos);

	if (SkinMesh9<CharaType>::boneList.find(_fStr.substr(_fPos, tmpPos - _fPos)) != SkinMesh9<CharaType>::boneList.end())return;

	auto tmpBone = ChPtr::Make_S<typename SkinMesh9<CharaType>::Bone>();
	tmpBone->offsetBone = _bone;

	std::basic_string<CharaType> test = _fStr.substr(_fPos, tmpPos - _fPos);
	SkinMesh9<CharaType>::boneList[test] = tmpBone;
	tmpBone->myName = test;
	SkinMesh9<CharaType>::boneNameList.push_back(test);

	_fPos = _fStr.find(BaseMesh9<CharaType>::frameMat, _fPos);

	_fPos += std::strlen(BaseMesh9<CharaType>::frameMat);

	{
		ChLMatrix tmpMat;
		tmpMat.Deserialize(_fStr, _fPos);
		tmpBone->baseMat = tmpMat;
	}

	_fPos = _fStr.find(ChStd::GetEndBraceChara<CharaType>(), _fPos);
	_fPos += 1;

	////メッシュ取得//
	//if (_fStr.find("mesh {", _fPos) <= _fStr.find("}", _fPos))
	//{
	//	size_t tmp = vertexNum;
	//	_fPos = _fStr.find("mesh {", _fPos);
	//	_fPos = _fStr.find("\n", _fPos);
	//	_fPos += 1;
	//	std::basic_string<CharaType> num = _fStr.substr(_fPos, _fStr.find(";", _fPos) - _fPos);
	//	vertexNum += std::atol(num.c_str());
	//}

	size_t framePos = _fStr.find(GetFrameTag<CharaType>(), _fPos);

	size_t endPos = _fStr.find(ChStd::GetEndBraceChara<CharaType>(), _fPos);

	while (endPos >= framePos)
	{
		_fPos = framePos;
		if (_fPos == std::basic_string<CharaType>::npos)break;
		CreateBoneTree(_fStr, _fPos, tmpBone);
		framePos = _fStr.find(GetFrameTag<CharaType>(), _fPos);
	}

	_fPos = endPos;
	_fPos += 1;
}
