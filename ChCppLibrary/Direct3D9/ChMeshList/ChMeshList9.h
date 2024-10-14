#ifndef Ch_D3D9_MeLi_h
#define Ch_D3D9_MeLi_h

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

	//SmpXFile��p��enum class������āASetSmpXFile�̑������ɓ����B//
	//�ȍ~�������ɓ��ꂽ�������g����SmpXFile�𑀍삷��B//
	typedef class MeshList9:public ChCp::Initializer
	{
	public://Operator Functions//

		MeshList9& operator =(const MeshList9& _xList)
		{
			return *this;
		}

	public://Constructer Destructer//

		virtual ~MeshList9();

	public://InitAndRelease//

#ifdef CRT
		//�����AXFile�t�H���_�[�Ȃǂ�����Ă��Ȃ��ꍇ�͑�������""������B//
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv,
			const std::string& _fileInDirectoryPath)
		{
			device = _dv;
			directoryPath = _fileInDirectoryPath;
			SetInitFlg(true);
		}

#endif

		virtual void Release();

	public://Set Functions//

#ifdef CRT
		//Mesh�̓o�^(DataName���g����3D���f����I������)//
		void SetMesh(
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

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//SkinMesh�̓o�^(DataName���g����3D���f����I������)//
		void SetSkinMesh(
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

		//�o�^����Ă���Mesh�̉摜���ꕔ�ύX//
		void SetTexture(
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


		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
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

		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
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
#endif

	public://Get Functions//

#ifdef CRT
		//�I������Mesh�̑I�������ʂ̃x�[�X�ƂȂ�@��//
		MeshFace9 GetEasyFace(
			const unsigned short _dataNum,
			const unsigned long _faceNum)
		{
			MeshFace9 face;

			if (meshList.size() <= _dataNum)return nFace();

			if (meshList[_dataNum]->InsFace().size() <= _faceNum)return nFace();

			face = *meshList[_dataNum]->InsFace()[_faceNum];

			return face;

		}
#endif

		//�o�^����Ă���Mesh�̐�//
		const unsigned short GetMeshSize();



#ifdef CRT
		//�o�^����Ă���Mesh�̃}�e���A�����擾//
		std::vector<ChPtr::Shared<ChMaterialA_9>>& GetMeshMaterials(const unsigned short _dataNum)
		{
			static std::vector<ChPtr::Shared<ChMaterialA_9>> tmpMateList;

			if (meshList.empty())return nMaterial();
			if (meshList.size() <= _dataNum)return nMaterial();
			return meshList[_dataNum]->InsMaterials();
		}

#endif

		//�`�掞�Ȃǂɗ��p�����Mesh���o��//
		BaseMesh9* GetMesh(const unsigned short _dataNum);

	public://Other Functions//

		//���̊֐����ĂԂƊe�ʂɉ�������s�����߂̖@�������������B
		void CreateEasyFace(
			const unsigned short _dataNum,
			const unsigned short _baseMatNum);

		//�o�^����Ă���XFile��SubSet���Ƃɕ`�悷��//
		inline void DrawMesh(
			const ChMat_9 &_mat,
			const unsigned short _dataNum,
			const long _subNum = -1)
		{
			auto&& mesh = GetMesh(_dataNum);
			if (ChPtr::NullCheck(mesh))return;

			mesh->Draw(_mat, device, _subNum);
		}

	protected:

		LPDIRECT3DDEVICE9 device;

		static MeshFace9& nFace()
		{
			static MeshFace9 ins;
			return ins;
		};

#ifdef CRT
		std::string directoryPath;

		static std::vector<ChPtr::Shared<ChMaterialA_9>>& nMaterial()
		{
			static std::vector<ChPtr::Shared<ChMaterialA_9>> ins;
			return ins;
		};

		std::map<unsigned short, ChPtr::Shared<BaseMesh9>>meshList;
#endif
	}ChMeshList9;

}

#ifdef CRT

void ChMesh::MeshList9::Release()
{
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

const unsigned short ChMesh::MeshList9::GetMeshSize()
{
	return (unsigned short)meshList.size();
}

ChMesh::BaseMesh9* ChMesh::MeshList9::GetMesh(const unsigned short _dataNum)
{
	if (meshList.size() <= _dataNum)return nullptr;

	return meshList[_dataNum].get();
}
#endif

#endif
//CopyRight Chronoss0518 2018/08