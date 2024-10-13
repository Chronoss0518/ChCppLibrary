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

	template<typename CharaType>
	class BaseMesh9;

	template<typename CharaType>
	class SkinMesh9;


	//全体で利用されるシングルトン生成されたメッシュマネージャー//
	//全体管理を行っているため、適度にClearしなければならない//
	template<typename CharaType>
	class MeshManager9:public ChCp::Initializer
	{
	public://Init And Release//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release();

	public://Set Functions//

		//使用するディレクトリの登録//
		void SetDirectoryPath(
			const std::basic_string<CharaType>& _directoryPath,
			const std::basic_string<CharaType>& _useDirectoryPashName)
		{
			if (pathList.find(_useDirectoryPashName) != pathList.end())return;
			if (_directoryPath.length() <= 0)return;

			pathList.insert(std::pair<std::basic_string<CharaType>, ChPtr::Shared<std::basic_string<CharaType>>>(_useDirectoryPashName, ChPtr::Make_S<std::basic_string<CharaType>>()));
			*pathList[_useDirectoryPashName] = _directoryPath;
		}

		//登録したディレクトリよりMeshの登録//
		void SetMesh(
			const std::basic_string<CharaType>& _meshName,
			const std::basic_string<CharaType>& _dataName,
			const std::basic_string<CharaType>& _usePashName)
		{
			if (meshList.find(_dataName) != meshList.end())return;
			if (_meshName.length() <= 0)return;

			std::basic_string<CharaType> tmpString;
			std::basic_string<CharaType> tmpPathName = "./";
			if (pathList.find(_usePashName) != pathList.end())
			{
				tmpPathName = *pathList[_usePashName] + '/';
			}

			auto tmpMesh = ChMesh::BaseMesh9<CharaType>::MeshType(_meshName);
			tmpMesh->CreateMesh(_meshName, tmpPathName, device);

			if (tmpMesh->InsMesh() == nullptr)
			{
				//ChSystem::ErrerMessage("メッシュが読み込まれませんでした","警告");
				tmpMesh = nullptr;
				return;
			}

			meshList[_dataName] = tmpMesh;
		}

		//※登録できるSkinMeshがまだ完成していない//
		//登録したディレクトリよりMeshの登録//
		void SetSkinMesh(
			const std::basic_string<CharaType>& _meshName,
			const std::basic_string<CharaType>& _dataName,
			const std::basic_string<CharaType>& _usePashName)
		{
			if (meshList.find(_dataName) != meshList.end())return;
			if (_meshName.length() <= 0)return;

			std::basic_string<CharaType> tmpString;
			std::basic_string<CharaType> tmpPathName = "./";
			if (pathList.find(_usePashName) != pathList.end())
			{
				tmpPathName = *pathList[_usePashName] + '/';
			}

			auto tmpMesh = ChMesh::BaseMesh9<CharaType>::SkinMeshType(_meshName);
			tmpMesh->CreateMesh(_meshName, tmpPathName, device);

			if (tmpMesh->InsMesh() == nullptr)
			{
				//ChSystem::ErrerMessage("メッシュが読み込まれませんでした", "警告");
				return;
			}

			auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9<CharaType>>(tmpMesh);
			if (tmpSkinMesh->boneList.size() <= 0)
			{
				//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");
				tmpMesh->Release();
				return;
			}

			meshList[_dataName] = tmpMesh;
		}

		//登録されているテクスチャを取得//
		void SetTexture(
			const std::basic_string<CharaType>& _dataName,
			const unsigned long _texNum,
			const ChPtr::Shared<ChTex::Texture9> _tex)
		{
			if (_tex == nullptr)return;
			if (meshList.find(_dataName) == meshList.end())return;
			if (meshList[_dataName]->InsTex().size() <= _texNum)return;

			meshList[_dataName]->InsTex()[_texNum] = nullptr;
			meshList[_dataName]->InsTex()[_texNum] = _tex;
		}

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const std::basic_string<CharaType>& _meshName,
			const std::basic_string<CharaType>& _aniamtionName,
			const std::basic_string<CharaType>& _xFileName)
		{
			if (meshList.find(_meshName) == meshList.end())
			{
				//ChSystem::ErrerMessage("登録されていない数値です", "警告");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");
				return;
			}

			skinMesh->SetAnimation(_aniamtionName, _xFileName);
		}


		//SkinMesh専用//
		//外部で作成したアニメーションをセット//
		void SetAnimation(
			const std::basic_string<CharaType>& _meshName,
			const std::basic_string<CharaType>& _aniamtionName,
			const std::map<std::basic_string<CharaType>, ChPtr::Shared<ChAnimationObject9>>& _animes)
		{
			if (meshList.find(_meshName) == meshList.end())
			{
				//ChSystem::ErrerMessage("登録されていない数値です", "警告");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");
				return;
			}

			skinMesh->SetAnimation(_aniamtionName, _animes);
		}

		//SkinMesh専用//
		//アニメーションが何フレームで終了するかを設定//
		void SetAnimationTime(
			const std::basic_string<CharaType>& _meshName,
			const std::basic_string<CharaType>& _aniamtionName,
			const float _playAniTime)
		{
			if (_playAniTime <= 0.0f)
			{
				//ChSystem::ErrerMessage("最低でも0より大きい数値が必要です", "警告");
				return;
			}

			if (meshList.find(_meshName) == meshList.end())
			{
				//ChSystem::ErrerMessage("登録されていない数値です", "警告");
				return;
			}

			auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_meshName]);

			if (skinMesh == nullptr)
			{
				//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");
				return;
			}

			skinMesh->SetAniTime(_aniamtionName, _playAniTime);
		}

	public://Get Functions//

		//現在登録されているディレクトリパスの数//
		size_t GetPathCnt();

		//現在登録されているMeshの数//
		size_t GetMeshCnt();

		//外部で利用するMeshの取得//
		inline ChPtr::Shared<ChMesh::BaseMesh9<CharaType>> GetMesh(const std::basic_string<CharaType>& _dataName)
		{
			if (meshList.empty())return nullptr;
			auto&& res = meshList.find(_dataName);
			if (res == meshList.end())return nullptr;
			return res.second;
		}

		//Meshに登録されているマテリアルデータすべてを取得//
		std::vector<ChPtr::Shared<ChMaterialA_9>>& GetMeshMaterials(const std::basic_string<CharaType>& _dataName)
		{
			if (meshList.empty())return nMaterial();
			auto&& res = meshList.find(_dataName);
			if (res == meshList.end())return nMaterial();
			return res.second->InsMaterials();
		}

		//登録されているMeshの選択した面の法線の取得//
		MeshFace9 GetEasyFace(
			const std::basic_string<CharaType>& _dataName,
			const unsigned long _faseNum)
		{
			MeshFace9 face;

			if (meshList.find(_dataName) == meshList.end())return nFace();
			if (meshList[_dataName]->InsFace().size() <= _faseNum)return nFace();
			face = *meshList[_dataName]->InsFace()[_faseNum];
			return face;
		}

	public://Is Functions//

		//登録されているパスが存在するかの確認//
		//見つかった場合はtrueを返す//
		inline bool IsPath(const std::basic_string<CharaType>& _find)
		{
			return pathList.find(_find) != pathList.end();
		}

		//登録されているMeshリスト取得//
		//見つかった場合はtrueを返す//
		inline bool IsMesh(const std::basic_string<CharaType>& _find)
		{
			return meshList.find(_find) != meshList.end();
		}

	public:

		//GetFaseBaseNormalを利用する際先に呼ぶ必要がある関数//
		//各面に対しての法線を作成する//
		void CreateEasyFace(
			const std::basic_string<CharaType>& _dataName,
			const unsigned short _baseMatNum)
		{
			if (meshList.find(_dataName) == meshList.end())return;
			meshList[_dataName]->CreateEasyFaceList();
		}

		//選択したXFileを解放する//
		void ClearData(const std::basic_string<CharaType>& _dataName)
		{
			if (meshList.empty())return;
			if (meshList.find(_dataName) == meshList.end()) return;
			meshList.erase(_dataName);
		}

		//登録されているXFileを固定機能で描画する//
		void DrawMesh(
			const ChMat_9& _mat,
			const std::basic_string<CharaType>& _dataName,
			const long _subNum = -1)
		{
			if (meshList.find(_dataName) == meshList.end())return;
			meshList[_dataName]->SetSkin();
			meshList[_dataName]->Draw(_mat, device, _subNum);
		}

	protected:

		LPDIRECT3DDEVICE9 device = nullptr;

		static MeshFace9& nFace()
		{
			static MeshFace9 ins;
			return ins;
		}

		static std::vector<ChPtr::Shared<ChMaterialA_9>>& nMaterial()
		{
			static std::vector<ChPtr::Shared<ChMaterialA_9>> ins;
			return ins;
		}

		std::map<std::basic_string<CharaType>, ChPtr::Shared<ChMesh::BaseMesh9<CharaType>>> meshList;

		std::map<std::basic_string<CharaType>, ChPtr::Shared<std::basic_string<CharaType>>> pathList;


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

	template<typename CharaType>
	inline MeshManager9<CharaType>& MeManager9() { return MeshManager9<CharaType>::GetInstance(); };

	inline MeshManager9<char>& MeManagerA9() { return MeshManager9<char>::GetInstance(); };

#ifdef CPP20
	inline MeshManager9<wchar_t>& MeManagerW9() { return MeshManager9<wchar_t>::GetInstance(); };
#endif


}

#endif