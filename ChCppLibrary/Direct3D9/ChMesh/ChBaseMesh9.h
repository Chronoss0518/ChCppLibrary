
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

		virtual void Release(){}

	public://Set Functions//

		virtual void SetSkin(){}

		void SetMaterialDiffuse(
			const unsigned long _num,
			const D3DCOLORVALUE& _dif)
		{
			if (material.size() <= _num)return;
			material[_num]->Diffuse = _dif;
		}

		void SetMaterialDiffuse(
			const unsigned long _num,
			const ChVec4& _dif)
		{
			SetMaterialDiffuse(_num, ToD3DCOLORVALUE(_dif));
		}

		void SetMaterialAmbient(
			const unsigned long _num,
			const D3DCOLORVALUE& _amb)
		{
			if (material.size() <= _num)return;
			material[_num]->Ambient = _amb;
		}

		void SetMaterialAmbient(
			const unsigned long _num,
			const ChVec4& _amb)
		{
			SetMaterialAmbient(_num, ToD3DCOLORVALUE(_amb));
		}

		void SetMaterialSepcular(
			const unsigned long _num,
			const D3DCOLORVALUE& _spe)
		{
			if (material.size() <= _num)return;
			material[_num]->Specular = _spe;
		}

		void SetMaterialSepcular(
			const unsigned long _num,
			const ChVec4& _spe)
		{
			SetMaterialSepcular(_num, ToD3DCOLORVALUE(_spe));
		}

		void SetMaterialEmissive(
			const unsigned long _num,
			const D3DCOLORVALUE& _emi)
		{
			if (material.size() <= _num)return;
			material[_num]->Emissive = _emi;
		}

		void SetMaterialEmissive(
			const unsigned long _num,
			const ChVec4& _emi)
		{
			SetMaterialSepcular(_num, ToD3DCOLORVALUE(_emi));
		}

		void SetMaterialEmissive(
			const unsigned long _num,
			const float _pow)
		{
			if (material.size() <= _num)return;
			material[_num]->Power = _pow;
		}

		void SetMaterialMatrix(
			const unsigned long _num,
			const ChLMat& _mat)
		{
			if (material.size() <= _num)return;
		}

		void SetOffsetVertex(const ChVec3_9& _vertex)
		{
			auto&& ver = ChPtr::Make_S<ChVec3_9>();
			*ver = _vertex;
			offsetVertexList.push_back(ver);
		}

	public://Get Functions//

		inline const LPD3DXMESH GetMesh() const { return mesh; }

		ChPtr::Shared<MeshFace9> GetFace(size_t _num) const { return easyFaceList.size() <= _num ? nullptr : easyFaceList[_num]; }

		inline std::vector<ChPtr::Shared<ChVec3_9>> GetVertexList()const { return offsetVertexList; }

		inline std::vector<ChPtr::Shared<ChBaseMaterial_9<CharaType>>> GetMaterials() const { return material; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetTex() const { return texList; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetNormalTex() const { return normalTex; }

		inline std::vector<ChPtr::Shared<MeshFace9>> GetFaceList() const { return easyFaceList; }

		virtual inline ChMat_9 GetBoneMat(const std::basic_string<CharaType>& _str) { return ChMat_9(); }

		ChVec3_9 GetOffsetVertex(unsigned long _num)const { return offsetVertexList.size() <= _num ? ChVec3_9(0.0f) : *offsetVertexList[_num]; }

		size_t GetMaterialCount()const { return easyFaceList.size(); }

		ChBaseMaterial_9<CharaType> GetMaterial(size_t _num)const { return material.size() <= _num ? ChBaseMaterial_9<CharaType>() : *material[_num]; }

		size_t GetTextureCount()const { return texList.size(); }

		ChPtr::Shared<ChTex::BaseTexture9> GetTexture(size_t _num)const { return texList.size() <= _num ? nullptr : texList[_num]; }

		size_t GetNormalTextureCount()const { return normalTex.size(); }

		ChPtr::Shared<ChTex::BaseTexture9> GetNormalTexture(size_t _num)const { return normalTex.size() <= _num ? nullptr : normalTex[_num]; }

	private:

		D3DCOLORVALUE ToD3DCOLORVALUE(const ChVec4& _val)
		{
			D3DCOLORVALUE res;
			res.r = _val.r;
			res.g = _val.g;
			res.b = _val.b;
			res.a = _val.a;
			return res;
		}

	public://Create Functions//

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

	using BaseMeshA9 = BaseMesh9<char>;
	using BaseMeshW9 = BaseMesh9<wchar_t>;

}

#endif