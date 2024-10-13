#ifndef Ch_D3D9_MeLi_h
#define Ch_D3D9_MeLi_h

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
	template<typename CharaType>
	class BaseMesh9;


	template<typename CharaType>
	class SkinMesh9;

	//SmpXFile��p��enum class������āASetSmpXFile�̑������ɓ����B//
	//�ȍ~�������ɓ��ꂽ�������g����SmpXFile�𑀍삷��B//
	template<typename  CharaType>
	class MeshList9:public ChCp::Initializer
	{
	public://Operator Functions//

		MeshList9& operator =(const MeshList9& _xList)
		{
			return *this;
		}

	public://Constructer Destructer//

		virtual ~MeshList9();

	public://InitAndRelease//

		//�����AXFile�t�H���_�[�Ȃǂ�����Ă��Ȃ��ꍇ�͑�������""������B//
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv,
			const std::basic_string<CharaType>& _fileInDirectoryPath)
		{
			device = _dv;
			directoryPath = _fileInDirectoryPath;
			SetInitFlg(true);
		}

		virtual void Release();

	public://Set Functions//

		//Mesh�̓o�^(DataName���g����3D���f����I������)//
		void SetMesh(
			const std::basic_string<CharaType>& _meshName,
			const unsigned short _dataNum)
		{
			if (meshList.find(_dataNum) != meshList.end())return;
			if (_meshName.length() <= 0)return;

			std::basic_string<CharaType> tmpString = _meshName;
			std::basic_string<CharaType> tmpPathName = ChStd::GetDotChara<CharaType>();
			tmpPathName = tmpPathName + ChStd::GetSlashChara<CharaType>();
			if (directoryPath.length() > 0)
			{
				tmpPathName = directoryPath + ChStd::GetSlashChara<CharaType>();
			}

			auto tmpMesh = BaseMesh9<CharaType>::MeshType(_meshName);

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
			const std::basic_string<CharaType>& _meshName,
			const unsigned short _dataNum)
		{

			if (meshList.find(_dataNum) != meshList.end())return;

			if (_meshName.length() <= 0)return;

			std::basic_string<CharaType> tmpString = _meshName;
			std::basic_string<CharaType> tmpPathName = ChStd::GetDotChara<CharaType>();
			tmpPathName = tmpPathName + ChStd::GetSlashChara<CharaType>();
			if (directoryPath.length() > 0)
			{
				tmpPathName = directoryPath + ChStd::GetSlashChara<CharaType>();
			}

			auto&& tmpMesh = BaseMesh9<CharaType>::SkinMeshType(_meshName);

			tmpMesh->CreateMesh(_meshName, tmpPathName, device);

			if (tmpMesh->InsMesh() == nullptr)
			{

				//ChSystem::ErrerMessage("���b�V�����ǂݍ��܂�܂���ł���", "�x��");

				return;
			}

			{
				auto tmpSkinMesh = ChPtr::SharedSafeCast<SkinMesh9<CharaType>>(tmpMesh);

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
			const std::basic_string<CharaType>& _aniamtionName,
			const std::basic_string<CharaType>& _xFileName)
		{
			if (_dataNum >= meshList.size())
			{
				//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9<CharaType>>(meshList[_dataNum]);

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
			const std::basic_string<CharaType>& _aniamtionName,
			const std::map<std::basic_string<CharaType>,
			ChPtr::Shared<ChAnimationObject9>>& _animes)
		{

			if (_dataNum >= meshList.size())
			{
				//ChSystem::ErrerMessage("�o�^����Ă��Ȃ����l�ł�", "�x��");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9<CharaType>>(meshList[_dataNum]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("�X�L�����b�V���ł͂���܂���", "�x��");
				return;
			}

			skinMesh->SetAnimation(_aniamtionName, _animes);

		}

	public://Get Functions//

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

		//�o�^����Ă���Mesh�̐�//
		const unsigned short GetMeshSize();

		//�o�^����Ă���Mesh�̃}�e���A�����擾//
		std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>>& GetMeshMaterials(const unsigned short _dataNum)
		{
			static std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>> tmpMateList;

			if (meshList.empty())return nMaterial();
			if (meshList.size() <= _dataNum)return nMaterial();
			return meshList[_dataNum]->InsMaterials();
		}

		//�`�掞�Ȃǂɗ��p�����Mesh���o��//
		BaseMesh9<CharaType>* GetMesh(const unsigned short _dataNum);

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

		std::basic_string<CharaType> directoryPath;

		static std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>>& nMaterial()
		{
			static std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>> ins;
			return ins;
		};

		std::map<unsigned short, ChPtr::Shared<BaseMesh9<CharaType>>>meshList;
	};

#ifdef CPP20
	using MeshListA9 = MeshList9<char>;
	using MeshListW9 = MeshList9<wchar_t>;
#else
	using MeshListA9 = MeshList9<char>;
#endif

}

#endif
//CopyRight Chronoss0518 2018/08