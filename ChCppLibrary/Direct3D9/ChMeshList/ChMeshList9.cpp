
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChMeshList9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//ChMeshList���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

MeshList9::~MeshList9()
{
	Release();
}

void ChMeshList9::CreateEasyFace(
	const unsigned short _dataNum,
	const unsigned short _BaseMatNum)
{

	auto&& mesh = GetMesh(_dataNum);
	if (ChPtr::NullCheck(mesh))return;

	mesh->CreateEasyFaceList();
}

void ChMesh::MeshList9::Release()
{
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

void ChMesh::MeshList9::SetMesh(
	const std::string& _meshName,
	const unsigned short _dataNum)
{
	if (meshList.find(_dataNum) != meshList.end())return;
	if (_meshName.length() <= 0)return;

	std::string tmpString = _meshName;
	std::string tmpPathName = "./";
	if (directoryPath.length() > 0)
	{
		tmpPathName = directoryPath + '/';
	}

	auto tmpMesh = Mesh9::MeshType(_meshName);

	tmpMesh->CreateMesh(_meshName, tmpPathName, device);

	if (tmpMesh->mesh == nullptr)
	{

		//ChSystem::ErrerMessage("���b�V�����ǂݍ��܂�܂���ł���", "�x��");

		return;
	}
	meshList[_dataNum] = tmpMesh;
}

void ChMesh::MeshList9::SetSkinMesh(
	const std::string& _meshName,
	const unsigned short _dataNum)
{

	if (meshList.find(_dataNum) != meshList.end())return;

	if (_meshName.length() <= 0)return;

	std::string tmpString = _meshName;
	std::string tmpPathName = "./";
	if (directoryPath.length() > 0)
	{
		tmpPathName = directoryPath + '/';
	}

	auto tmpMesh = Mesh9::SkinMeshType(_meshName);

	tmpMesh->CreateMesh(_meshName, tmpPathName, device);

	if (tmpMesh->InsMesh() == nullptr)
	{

		//ChSystem::ErrerMessage("���b�V�����ǂݍ��܂�܂���ł���", "�x��");

		return;
	}

	{
		auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(tmpMesh);

		if (tmpSkinMesh->boneList.size() <= 0)
		{
			//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");

			tmpMesh->Release();
			return;
		}
	}
	meshList[_dataNum] = tmpMesh;

}

void ChMesh::MeshList9::SetTexture(
	const unsigned short _dataNum,
	const unsigned long _texNum,
	const ChPtr::Shared<ChTex::Texture9> _tex)
{
	if (_tex == nullptr)return;
	if (meshList.size() <= _dataNum)return;

	if (meshList[_dataNum]->InsTex().size() <= _texNum)return;

	meshList[_dataNum]->InsTex()[_texNum] = nullptr;

	meshList[_dataNum]->InsTex()[_texNum] = _tex;

}

void ChMesh::MeshList9::SetAnimation(
	const unsigned short _dataNum,
	const std::string& _aniamtionName,
	const std::string& _xFileName)
{
	if (_dataNum >= meshList.size())
	{
		//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_dataNum]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
		return;
	}

	skinMesh->SetAnimation(_aniamtionName, _xFileName);
}

void ChMesh::MeshList9::SetAnimation(
	const unsigned short _dataNum,
	const std::string& _aniamtionName,
	const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
{

	if (_dataNum >= meshList.size())
	{
		//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_dataNum]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
		return;
	}

	skinMesh->SetAnimation(_aniamtionName, _animes);

}

MeshFace9 ChMesh::MeshList9::GetEasyFace(
	const unsigned short _dataNum,
	const unsigned long _faceNum)
{
	MeshFace9 face;

	if (meshList.size() <= _dataNum)return nFace();

	if (meshList[_dataNum]->InsFace().size() <= _faceNum)return nFace();

	face = *meshList[_dataNum]->InsFace()[_faceNum];

	return face;

}

const unsigned short ChMesh::MeshList9::GetMeshSize()
{
	return (unsigned short)meshList.size();
}

std::vector<ChPtr::Shared<ChMaterial9>>& ChMesh::MeshList9::GetMeshMaterials(const unsigned short _dataNum)
{
	static std::vector<ChPtr::Shared<ChMaterial9>> tmpMateList;

	if (meshList.empty())return nMaterial();
	if (meshList.size() <= _dataNum)return nMaterial();
	return meshList[_dataNum]->InsMaterials();
}

ChMesh::BaseMesh9* ChMesh::MeshList9::GetMesh(const unsigned short _dataNum)
{
	if (meshList.size() <= _dataNum)return nullptr;

	return meshList[_dataNum].get();
}