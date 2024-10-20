
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"ChMeshManager9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//MeshManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void MeshManager9::Init(const LPDIRECT3DDEVICE9 _dev)
{
	device = _dev;
	SetInitFlg(true);
}

void ChMesh::MeshManager9::Release()
{
	if (!meshList.empty())meshList.clear();
	if (!pathList.empty())pathList.clear();
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

void ChMesh::MeshManager9::SetDirectoryPath(
	const std::string& _directoryPath,
	const std::string& _useDirectoryPashName)
{
	if (pathList.find(_useDirectoryPashName) != pathList.end())return;
	if (_directoryPath.length() <= 0)return;

	pathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_useDirectoryPashName, ChPtr::Make_S<std::string>()));
	*pathList[_useDirectoryPashName] = _directoryPath;
}

void MeshManager9::SetMesh(
	const std::string& _meshName,
	const std::string& _dataName,
	const std::string& _usePashName)
{
	if (meshList.find(_dataName) != meshList.end())return;
	if (_meshName.length() <= 0)return;

	std::string tmpString;
	std::string tmpPathName = "./";
	if (pathList.find(_usePashName) != pathList.end())
	{
		tmpPathName = *pathList[_usePashName] + '/';
	}

	auto tmpMesh = ChMesh::BaseMesh9::MeshType(_meshName);
	tmpMesh->CreateMesh(_meshName, tmpPathName, device);

	if (tmpMesh->InsMesh() == nullptr)
	{
		//ChSystem::ErrerMessage("ÉÅÉbÉVÉÖÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ","åxçê");
		tmpMesh = nullptr;
		return;
	}

	meshList[_dataName] = tmpMesh;
}

void MeshManager9::SetSkinMesh(
	const std::string& _meshName,
	const std::string& _dataName,
	const std::string& _usePashName)
{
	if (meshList.find(_dataName) != meshList.end())return;
	if (_meshName.length() <= 0)return;

	std::string tmpString;
	std::string tmpPathName = "./";
	if (pathList.find(_usePashName) != pathList.end())
	{
		tmpPathName = *pathList[_usePashName] + '/';
	}

	auto tmpMesh = ChMesh::BaseMesh9::SkinMeshType(_meshName);
	tmpMesh->CreateMesh(_meshName, tmpPathName, device);

	if (tmpMesh->InsMesh() == nullptr)
	{
		//ChSystem::ErrerMessage("ÉÅÉbÉVÉÖÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");
		return;
	}

	auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(tmpMesh);
	if (tmpSkinMesh->boneList.size() <= 0)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");
		tmpMesh->Release();
		return;
	}

	meshList[_dataName] = tmpMesh;
}

void MeshManager9::SetTexture(
	const std::string& _dataName,
	const unsigned long _texNum,
	const ChPtr::Shared<ChTex::Texture9> _tex)
{
	if (_tex == nullptr)return;
	if (meshList.find(_dataName) == meshList.end())return;
	if (meshList[_dataName]->InsTex().size() <= _texNum)return;

	meshList[_dataName]->InsTex()[_texNum] = nullptr;
	meshList[_dataName]->InsTex()[_texNum] = _tex;
}

void MeshManager9::SetAnimation(
	const std::string& _meshName,
	const std::string& _aniamtionName,
	const std::string& _xFileName)
{
	if (meshList.find(_meshName) == meshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");
		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");
		return;
	}

	skinMesh->SetAnimation(_aniamtionName, _xFileName);
}

void MeshManager9::SetAnimation(
	const std::string& _meshName,
	const std::string& _aniamtionName,
	const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
{
	if (meshList.find(_meshName) == meshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");
		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");
		return;
	}

	skinMesh->SetAnimation(_aniamtionName, _animes);
}

void MeshManager9::SetAnimationTime(
	const std::string& _meshName,
	const std::string& _aniamtionName,
	const float _playAniTime)
{
	if (_playAniTime <= 0.0f)
	{
		//ChSystem::ErrerMessage("ç≈í·Ç≈Ç‡0ÇÊÇËëÂÇ´Ç¢êîílÇ™ïKóvÇ≈Ç∑", "åxçê");
		return;
	}

	if (meshList.find(_meshName) == meshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");
		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");
		return;
	}

	skinMesh->SetAniTime(_aniamtionName, _playAniTime);
}

size_t ChMesh::MeshManager9::GetPathCnt()
{
	return pathList.size();
}

//åªç›ìoò^Ç≥ÇÍÇƒÇ¢ÇÈMeshÇÃêî//
size_t ChMesh::MeshManager9::GetMeshCnt()
{
	return meshList.size();
}

ChPtr::Shared<ChMesh::BaseMesh9> MeshManager9::GetMesh(const std::string& _dataName)
{
	if (meshList.empty())return nullptr;
	auto&& res = meshList.find(_dataName);
	if (res == meshList.end())return nullptr;
	return res->second;
}

std::vector<ChPtr::Shared<ChMaterial9>>& MeshManager9::GetMeshMaterials(const std::string& _dataName)
{
	if (meshList.empty())return nMaterial();
	auto&& res = meshList.find(_dataName);
	if (res == meshList.end())return nMaterial();
	return res->second->InsMaterials();
}

MeshFace9 MeshManager9::GetEasyFace(
	const std::string& _dataName,
	const unsigned long _faseNum)
{
	MeshFace9 face;

	if (meshList.find(_dataName) == meshList.end())return nFace();
	if (meshList[_dataName]->InsFace().size() <= _faseNum)return nFace();
	face = *meshList[_dataName]->InsFace()[_faseNum];
	return face;
}

void MeshManager9::CreateEasyFace(
	const std::string& _dataName,
	const unsigned short _baseMatNum)
{
	if (meshList.find(_dataName) == meshList.end())return;
	meshList[_dataName]->CreateEasyFaceList();
}

void MeshManager9::ClearData(const std::string& _dataName)
{
	if (meshList.empty())return;
	if (meshList.find(_dataName) == meshList.end()) return;
	meshList.erase(_dataName);
}

void MeshManager9::DrawMesh(
	const ChMat_9& _mat,
	const std::string& _dataName,
	const long _subNum)
{
	if (meshList.find(_dataName) == meshList.end())return;
	meshList[_dataName]->SetSkin();
	meshList[_dataName]->Draw(_mat, device, _subNum);
}