#ifndef Ch_D3D9_MeMa_h
#define Ch_D3D9_MeMa_h

#include<string>
#include<vector>
#include<map>

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
	class BaseMesh9;

	class SkinMesh9;


	//�S�̂ŗ��p�����V���O���g���������ꂽ���b�V���}�l�[�W���[//
	//�S�̊Ǘ����s���Ă��邽�߁A�K�x��Clear���Ȃ���΂Ȃ�Ȃ�//
	class MeshManager9:public ChCp::Initializer
	{
	public://Init And Release//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release();

	public://Set Functions//

		//�g�p����f�B���N�g���̓o�^//
		void SetDirectoryPath(
			const std::string& _directoryPath,
			const std::string& _useDirectoryPashName);

		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetMesh(
			const std::string& _meshName,
			const std::string& _dataName,
			const std::string& _usePashName);

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetSkinMesh(
			const std::string& _meshName,
			const std::string& _dataName,
			const std::string& _usePashName);

		//�o�^����Ă���e�N�X�`�����擾//
		void SetTexture(
			const std::string& _dataName,
			const unsigned long _texNum,
			const ChPtr::Shared<ChTex::Texture9> _tex);

		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::string& _xFileName);

		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

		//SkinMesh��p//
		//�A�j���[�V���������t���[���ŏI�����邩��ݒ�//
		void SetAnimationTime(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const float _playAniTime);

	public://Get Functions//

		//���ݓo�^����Ă���f�B���N�g���p�X�̐�//
		size_t GetPathCnt();

		//���ݓo�^����Ă���Mesh�̐�//
		size_t GetMeshCnt();

		//�O���ŗ��p����Mesh�̎擾//
		ChPtr::Shared<ChMesh::BaseMesh9> GetMesh(const std::string& _dataName);

		//Mesh�ɓo�^����Ă���}�e���A���f�[�^���ׂĂ��擾//
		std::vector<ChPtr::Shared<ChMaterial9>>& GetMeshMaterials(const std::string& _dataName);

		//�o�^����Ă���Mesh�̑I�������ʂ̖@���̎擾//
		MeshFace9 GetEasyFace(
			const std::string& _dataName,
			const unsigned long _faseNum);

	public://Is Functions//

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

	public:

		//GetFaseBaseNormal�𗘗p����ې�ɌĂԕK�v������֐�//
		//�e�ʂɑ΂��Ă̖@�����쐬����//
		void CreateEasyFace(
			const std::string& _dataName,
			const unsigned short _baseMatNum);

		//�I������XFile���������//
		void ClearData(const std::string& _dataName);

		//�o�^����Ă���XFile���Œ�@�\�ŕ`�悷��//
		void DrawMesh(
			const ChMat_9& _mat,
			const std::string& _dataName,
			const long _subNum = -1);

	protected:

		LPDIRECT3DDEVICE9 device = nullptr;

		static MeshFace9& nFace()
		{
			static MeshFace9 ins;
			return ins;
		}

		static std::vector<ChPtr::Shared<ChMaterial9>>& nMaterial()
		{
			static std::vector<ChPtr::Shared<ChMaterial9>> ins;
			return ins;
		}

		std::map<std::string, ChPtr::Shared<ChMesh::BaseMesh9>> meshList;

		std::map<std::string, ChPtr::Shared<std::string>> pathList;


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

#endif