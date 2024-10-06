
#ifndef Ch_D3D9_BMe_h
#define Ch_D3D9_BMe_h

#include<string>
#include<vector>
#include<map>
#include<functional>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"

namespace ChTex
{
	typedef class BaseTexture9 Texture9;
}

class ChObjectController9;

namespace ChMesh
{
	CH_NUMBER_FUNCTION_BASE(GetXFileExtension);

	template<typename CharaType>
	class MeshManager9;

	template<typename CharaType>
	class MeshList9;

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

	//D3DXMeshを操る基底クラス//
	template<typename CharaType>
	class BaseMesh9
	{
	public:

		friend MeshManager9<CharaType>;
		friend MeshList9<CharaType>;
		friend ChObjectController9;

	public:

		virtual ~BaseMesh9()
		{
			Release();
		}

	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		virtual void SetSkin(){}

		void SetMaterialCol(
			const unsigned long _Num,
			const ChVec4& _Dif);

		void SetMaterialMatrix(
			const unsigned long _Num,
			const ChLMat& _Mat);

		void SetOffsetVertex(const ChVec3_9& _vertex);

	public://Get Functions//

		inline const LPD3DXMESH GetMesh() const { return mesh; }

		const MeshFace9* GetFace(unsigned long _num) const;

		inline std::vector<ChPtr::Shared<ChVec3_9>> GetVertexList()const
		{
			return offsetVertexList;
		}

		inline std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>> GetMaterials() const { return material; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetTex() const { return texList; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetNormalTex() const { return normalTex; }

		inline std::vector<ChPtr::Shared<MeshFace9>> GetFaceList() const { return easyFaceList; }

		virtual inline ChMat_9 GetBoneMat(const std::basic_string<CharaType>& _str) { return ChMat_9(); }

		ChVec3_9 GetOffsetVertex(unsigned long _num)const;

		size_t GetMaterialCount()const;

		ChBaseMaterial_9<CharaType> GetMaterial(size_t _num)const;

		size_t GetTextureCount()const;

		ChTex::BaseTexture9* GetTexture(size_t _num)const;

		size_t GetNormalTextureCount()const;

		ChTex::BaseTexture9* GetNormalTexture(size_t _num)const;

	public://Create Functions//

		void CreateEasyFaceList();

		void CreateMesh(
			const std::basic_string<CharaType>& _fileName,
			const std::basic_string<CharaType>& _pathName,
			const LPDIRECT3DDEVICE9& _dev)
		{
			OpenFile(_fileName, _pathName, _dev);

			SetOffsetVertex();
		}

	protected:

		void CreateEasyFace(MeshFace9& _out, unsigned long _faceNum,MeshVertex9* _meshData, WORD* _p);

	public://Draw Functions//

		virtual void Draw(
			const ChMat_9& _mat,
			const LPDIRECT3DDEVICE9& _dev,
			const unsigned long _subNum = -1);

	public://Static Functions//

		static ChPtr::Shared<BaseMesh9> MeshType(const std::basic_string<CharaType>& _fileName);

		static ChPtr::Shared<BaseMesh9> SkinMeshType(const std::basic_string<CharaType>& _fileName);

	protected:

		virtual void OpenFile(
			const std::basic_string<CharaType>& _fileName,
			const std::basic_string<CharaType>& _pathName,
			const LPDIRECT3DDEVICE9& _dev) {}

	public://Ins Functions//

		virtual LPD3DXMESH InsMesh() { return mesh; }

		std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>>& InsMaterials() { return material; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsTex() { return texList; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsNormalTex() { return normalTex; }

		std::vector<ChPtr::Shared<MeshFace9>>& InsFace() { return easyFaceList; }

		virtual void SetOffsetVertex();

	protected://Member Method//

		LPD3DXMESH mesh = nullptr;//メッシュの形状//

		size_t vertexNum = 0;

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> texList;//テクスチャーの内容//
		std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>> material;//マテリアルの内容//
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> normalTex;//法線マッピング//

		std::vector<ChPtr::Shared<ChVec3_9>>optimalVertexList;//最適化した頂点//
		std::vector<ChPtr::Shared<MeshFace9>>easyFaceList;//最適化した頂点//

		std::vector<ChPtr::Shared<ChVec3_9>>offsetVertexList;//初期の頂点位置//

	};


	template<typename CharaType>
	class XFileMeshBase
	{
	protected:

		void SetMaterialName(const std::basic_string<CharaType>& _fileName);

	};
}

#endif