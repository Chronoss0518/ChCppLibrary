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


	//全体で利用されるシングルトン生成されたメッシュマネージャー//
	//全体管理を行っているため、適度にClearしなければならない//
	class MeshManager9:public ChCp::Initializer
	{
	public://Init And Release//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release();

	public://Set Functions//

		//使用するディレクトリの登録//
		void SetDirectoryPath(
			const std::string& _directoryPath,
			const std::string& _useDirectoryPashName);

		//登録したディレクトリよりMeshの登録//
		void SetMesh(
			const std::string& _meshName,
			const std::string& _dataName,
			const std::string& _usePashName);

		//※登録できるSkinMeshがまだ完成していない//
		//登録したディレクトリよりMeshの登録//
		void SetSkinMesh(
			const std::string& _meshName,
			const std::string& _dataName,
			const std::string& _usePashName);

		//登録されているテクスチャを取得//
		void SetTexture(
			const std::string& _dataName,
			const unsigned long _texNum,
			const ChPtr::Shared<ChTex::Texture9> _tex);

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::string& _xFileName);

		//SkinMesh専用//
		//外部で作成したアニメーションをセット//
		void SetAnimation(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

		//SkinMesh専用//
		//アニメーションが何フレームで終了するかを設定//
		void SetAnimationTime(
			const std::string& _meshName,
			const std::string& _aniamtionName,
			const float _playAniTime);

	public://Get Functions//

		//現在登録されているディレクトリパスの数//
		size_t GetPathCnt();

		//現在登録されているMeshの数//
		size_t GetMeshCnt();

		//外部で利用するMeshの取得//
		ChPtr::Shared<ChMesh::BaseMesh9> GetMesh(const std::string& _dataName);

		//Meshに登録されているマテリアルデータすべてを取得//
		std::vector<ChPtr::Shared<ChMaterial9>>& GetMeshMaterials(const std::string& _dataName);

		//登録されているMeshの選択した面の法線の取得//
		MeshFace9 GetEasyFace(
			const std::string& _dataName,
			const unsigned long _faseNum);

	public://Is Functions//

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

	public:

		//GetFaseBaseNormalを利用する際先に呼ぶ必要がある関数//
		//各面に対しての法線を作成する//
		void CreateEasyFace(
			const std::string& _dataName,
			const unsigned short _baseMatNum);

		//選択したXFileを解放する//
		void ClearData(const std::string& _dataName);

		//登録されているXFileを固定機能で描画する//
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