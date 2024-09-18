#ifndef Ch_D3D9_MeMa_h
#define Ch_D3D9_MeMa_h

#ifdef CRT

#include<string>
#include<vector>
#include<map>

#endif

#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"../ChMesh/MeshIncluder9.h"

class ChAnimationObject9;

namespace ChTex
{
	typedef class BaseTexture9 Texture9;
}

namespace ChMesh 
{

	typedef class BaseMesh9 Mesh9;

#ifndef _ChMesh9
#define _ChMesh9

	//���b�V���̒��_�f�[�^//
	struct MeshVertex9
	{
		ChVec3_9 pos;
		ChVec3_9 normal;
		D3DXVECTOR2 tex;
	};

	struct MeshFace9
	{
		unsigned long vertexNum[3];
		ChVec3_9 normal;
		ChVec3_9 centerPos;
	};

#endif

	class SkinMesh9;

	//�S�̂ŗ��p�����V���O���g���������ꂽ���b�V���}�l�[�W���[//
	//�S�̊Ǘ����s���Ă��邽�߁A�K�x��Clear���Ȃ���΂Ȃ�Ȃ�//
	class MeshManager9:public ChCp::Initializer
	{
	public://Init And Release//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release();

	public://Set Functions//

#ifdef CRT

		//�g�p����f�B���N�g���̓o�^//
		void SetDirectoryPath(
			const std::string& _directoryPath,
			const std::string& _useDirectoryPashName)
		{
			if (pathList.find(_useDirectoryPashName) != pathList.end())return;
			if (_directoryPath.length() <= 0)return;

			pathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_useDirectoryPashName, ChPtr::Make_S<std::string>()));
			*pathList[_useDirectoryPashName] = _directoryPath;
		}

		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetMesh(
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

			auto tmpMesh = Mesh9::MeshType(_meshName);
			tmpMesh->CreateMesh(_meshName, tmpPathName, device);

			if (tmpMesh->InsMesh() == nullptr)
			{
				//ChSystem::ErrerMessage("���b�V�����ǂݍ��܂�܂���ł���","�x��");
				tmpMesh = nullptr;
				return;
			}

			meshList[_dataName] = tmpMesh;
		}

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetSkinMesh(
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

			auto tmpMesh = Mesh9::SkinMeshType(_meshName);
			tmpMesh->CreateMesh(_meshName, tmpPathName, device);

			if (tmpMesh->InsMesh() == nullptr)
			{
				//ChSystem::ErrerMessage("���b�V�����ǂݍ��܂�܂���ł���", "�x��");
				return;
			}

			auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(tmpMesh);
			if (tmpSkinMesh->boneList.size() <= 0)
			{
				//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
				tmpMesh->Release();
				return;
			}

			meshList[_dataName] = tmpMesh;
		}

		//�o�^����Ă���e�N�X�`�����擾//
		void SetTexture(
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

		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::string& _xFileName)
		{
			if (meshList.find(_meshName) == meshList.end())
			{
				//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
				return;
			}

			skinMesh->SetAnimation(_aniamtionName, _xFileName);
		}


		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
		{
			if (meshList.find(_meshName) == meshList.end())
			{
				//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
				return;
			}

			skinMesh->SetAnimation(_aniamtionName, _animes);
		}

		//SkinMesh��p//
		//�A�j���[�V���������t���[���ŏI�����邩��ݒ�//
		void SetAnimationTime(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const float _playAniTime)
		{
			if (_playAniTime <= 0.0f)
			{
				//ChSystem::ErrerMessage("�Œ�ł�0���傫�����l���K�v�ł�", "�x��");
				return;
			}

			if (meshList.find(_meshName) == meshList.end())
			{
				//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
				return;
			}

			skinMesh->SetAniTime(_aniamtionName, _playAniTime);
		}

#endif

	public://Get Functions//

		//���ݓo�^����Ă���f�B���N�g���p�X�̐�//
		size_t GetPathCnt();

		//���ݓo�^����Ă���Mesh�̐�//
		size_t GetMeshCnt();

#ifdef CRT

		//�O���ŗ��p����Mesh�̎擾//
		inline ChPtr::Shared<BaseMesh9> GetMesh(const std::string& _dataName)
		{
			if (meshList.empty())return nullptr;
			if (meshList.find(_dataName) == meshList.end())return nullptr;
			return meshList[_dataName];
		}

		//Mesh�ɓo�^����Ă���}�e���A���f�[�^���ׂĂ��擾//
		std::vector<ChPtr::Shared<ChMaterialA_9>>& GetMeshMaterials(const std::string& _dataName)
		{
			if (meshList.empty())return nMaterial();
			if (meshList.find(_dataName) == meshList.end())return nMaterial();
			return meshList[_dataName]->InsMaterials();
		}

		//�o�^����Ă���Mesh�̑I�������ʂ̖@���̎擾//
		MeshFace9 GetEasyFace(
			const std::string& _dataName,
			const unsigned long _faseNum)
		{
			MeshFace9 face;

			if (meshList.find(_dataName) == meshList.end())return nFace();
			if (meshList[_dataName]->InsFace().size() <= _faseNum)return nFace();
			face = *meshList[_dataName]->InsFace()[_faseNum];
			return face;
		}

#endif

	public://Is Functions//

#ifdef CRT

		//�o�^����Ă���p�X�����݂��邩�̊m�F//
		//���������ꍇ��true��Ԃ�//
		inline bool IsPath(const std::string& _find)
		{
			return pathList.find(_find) != pathList.end(); 
		}

		//�o�^����Ă���Mesh���X�g�擾//
		//���������ꍇ��true��Ԃ�//
		inline bool IsMesh(const std::string& _find)
		{
			return meshList.find(_find) != meshList.end();
		}
#endif

	public:

#ifdef CRT

		//GetFaseBaseNormal�𗘗p����ې�ɌĂԕK�v������֐�//
		//�e�ʂɑ΂��Ă̖@�����쐬����//
		void CreateEasyFace(
			const std::string& _dataName,
			const unsigned short _baseMatNum)
		{
			if (meshList.find(_dataName) == meshList.end())return;
			meshList[_dataName]->CreateEasyFaceList();
		}

		//�I������XFile���������//
		void ClearData(const std::string& _dataName)
		{
			if (meshList.empty())return;
			if (meshList.find(_dataName) == meshList.end()) return;
			meshList.erase(_dataName);
		}

		//�o�^����Ă���XFile���Œ�@�\�ŕ`�悷��//
		void DrawMesh(
			const ChMat_9& _mat,
			const std::string& _dataName,
			const long _subNum = -1)
		{
			if (meshList.find(_dataName) == meshList.end())return;
			meshList[_dataName]->SetSkin();
			meshList[_dataName]->Draw(_mat, device, _subNum);
		}

#endif

	protected:

		LPDIRECT3DDEVICE9 device = nullptr;

		static MeshFace9& nFace()
		{
			static MeshFace9 ins;
			return ins;
		}

#ifdef CRT

		static std::vector<ChPtr::Shared<ChMaterialA_9>>& nMaterial()
		{
			static std::vector<ChPtr::Shared<ChMaterialA_9>> ins;
			return ins;
		}

		std::map<std::string, ChPtr::Shared<ChMesh::BaseMesh9>> meshList;

		std::map<std::string, ChPtr::Shared<std::string>> pathList;

#endif

	protected://Constructer Destructer//

		MeshManager9() {}

		virtual ~MeshManager9() { Release(); }

	public:

		static MeshManager9& GetInstance()
		{
			static MeshManager9 ins;
			return ins;
		}

	};

	inline MeshManager9& MeManager9() { return MeshManager9::GetInstance(); };
}

#ifdef CRT

void ChMesh::MeshManager9::Release()
{
	if (!meshList.empty())meshList.clear();
	if (!pathList.empty())pathList.clear();
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

size_t ChMesh::MeshManager9::GetPathCnt()
{
	return pathList.size();
}

//���ݓo�^����Ă���Mesh�̐�//
size_t ChMesh::MeshManager9::GetMeshCnt()
{
	return meshList.size();
}

#endif

#endif