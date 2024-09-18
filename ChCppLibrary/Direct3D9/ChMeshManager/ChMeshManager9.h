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

	//メッシュの頂点データ//
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

	//全体で利用されるシングルトン生成されたメッシュマネージャー//
	//全体管理を行っているため、適度にClearしなければならない//
	class MeshManager9:public ChCp::Initializer
	{
	public://Init And Release//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release();

	public://Set Functions//

#ifdef CRT

		//使用するディレクトリの登録//
		void SetDirectoryPath(
			const std::string& _directoryPath,
			const std::string& _useDirectoryPashName)
		{
			if (pathList.find(_useDirectoryPashName) != pathList.end())return;
			if (_directoryPath.length() <= 0)return;

			pathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_useDirectoryPashName, ChPtr::Make_S<std::string>()));
			*pathList[_useDirectoryPashName] = _directoryPath;
		}

		//登録したディレクトリよりMeshの登録//
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
				//ChSystem::ErrerMessage("メッシュが読み込まれませんでした","警告");
				tmpMesh = nullptr;
				return;
			}

			meshList[_dataName] = tmpMesh;
		}

		//※登録できるSkinMeshがまだ完成していない//
		//登録したディレクトリよりMeshの登録//
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
				//ChSystem::ErrerMessage("メッシュが読み込まれませんでした", "警告");
				return;
			}

			auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(tmpMesh);
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

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::string& _xFileName)
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
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
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
			const std::string& _meshName,
			const std::string& _aniamtionName,
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

#endif

	public://Get Functions//

		//現在登録されているディレクトリパスの数//
		size_t GetPathCnt();

		//現在登録されているMeshの数//
		size_t GetMeshCnt();

#ifdef CRT

		//外部で利用するMeshの取得//
		inline ChPtr::Shared<BaseMesh9> GetMesh(const std::string& _dataName)
		{
			if (meshList.empty())return nullptr;
			if (meshList.find(_dataName) == meshList.end())return nullptr;
			return meshList[_dataName];
		}

		//Meshに登録されているマテリアルデータすべてを取得//
		std::vector<ChPtr::Shared<ChMaterialA_9>>& GetMeshMaterials(const std::string& _dataName)
		{
			if (meshList.empty())return nMaterial();
			if (meshList.find(_dataName) == meshList.end())return nMaterial();
			return meshList[_dataName]->InsMaterials();
		}

		//登録されているMeshの選択した面の法線の取得//
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

		//登録されているパスが存在するかの確認//
		//見つかった場合はtrueを返す//
		inline bool IsPath(const std::string& _find)
		{
			return pathList.find(_find) != pathList.end(); 
		}

		//登録されているMeshリスト取得//
		//見つかった場合はtrueを返す//
		inline bool IsMesh(const std::string& _find)
		{
			return meshList.find(_find) != meshList.end();
		}
#endif

	public:

#ifdef CRT

		//GetFaseBaseNormalを利用する際先に呼ぶ必要がある関数//
		//各面に対しての法線を作成する//
		void CreateEasyFace(
			const std::string& _dataName,
			const unsigned short _baseMatNum)
		{
			if (meshList.find(_dataName) == meshList.end())return;
			meshList[_dataName]->CreateEasyFaceList();
		}

		//選択したXFileを解放する//
		void ClearData(const std::string& _dataName)
		{
			if (meshList.empty())return;
			if (meshList.find(_dataName) == meshList.end()) return;
			meshList.erase(_dataName);
		}

		//登録されているXFileを固定機能で描画する//
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

//現在登録されているMeshの数//
size_t ChMesh::MeshManager9::GetMeshCnt()
{
	return meshList.size();
}

#endif

#endif