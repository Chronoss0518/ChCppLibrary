
#ifndef Ch_D3D9_BMe_h
#define Ch_D3D9_BMe_h

#ifdef CRT

#include<string>
#include<vector>
#include<map>
#include<memory>
#include<functional>

#endif

#include"../../BasePack/ChPtr.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChTexture/TexIncluder9.h"

namespace ChTex
{
	typedef class BaseTexture9 Texture9;
}


class ChObjectController9;

namespace ChMesh
{

	class MeshManager9;
	class MeshList9;

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

	//D3DXMeshを操る基底クラス//
	typedef class BaseMesh9
	{
	public:

		virtual ~BaseMesh9()
		{
			Release();
		}

	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		virtual void SetSkin(){}

#ifdef CRT
		void SetMaterialName(const std::string& _fileName)
		{
			ChCpp::CharFile file;
			file.FileOpen(_fileName);

			std::string tmpStr;
			tmpStr = file.FileReadText();

			std::string tmpMateName = "Material ";

			size_t size = 0;

			unsigned int i = 0;

			while ((size = tmpStr.find(tmpMateName, size)) != std::string::npos)
			{
				size += tmpMateName.length();
				size_t tmpNum = tmpStr.find("{", size);
				if (tmpNum == std::string::npos)break;
				tmpNum -= (size + 1);
				material[i]->name = tmpStr.substr(size, tmpNum);
				size += tmpNum;
				i++;
			}

		}

#endif

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

#ifdef CRT
		inline std::vector<ChPtr::Shared<ChVec3_9>> GetVertexList()const
		{ 
			return offsetVertexList; 
		}

		inline std::vector<ChPtr::Shared<ChMaterialA_9>> GetMaterials() const { return material; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetTex() const { return texList; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetNormalTex() const { return normalTex; }

		inline std::vector<ChPtr::Shared<MeshFace9>> GetFaceList() const { return easyFaceList; }
		
		virtual inline ChMat_9 GetBoneMat(const std::string& _str){ return ChMat_9(); }
#endif

		ChVec3_9 GetOffsetVertex(unsigned long _num);

		unsigned long GetMaterialCount();

		ChMaterialA_9 GetMaterial(unsigned long _num);

		ChTex::BaseTexture9* GetTexture(unsigned long _num);

	public://Create Functions//

		void CreateEasyFaceList();

#ifdef CRT

		void CreateMesh(
			const std::string& _fileName,
			const std::string& _pathName,
			const LPDIRECT3DDEVICE9& _dev)
		{
			OpenFile(_fileName, _pathName, _dev);

			SetOffsetVertex();
		}

#endif

	protected:

		void CreateEasyFace(MeshFace9& _out, unsigned long _faceNum,MeshVertex9* _meshData, WORD* _p);

	public://Draw Functions//

		virtual void Draw(
			const ChMat_9& _mat,
			const LPDIRECT3DDEVICE9& _dev,
			const long _subNum = -1);

	public://Static Functions//

#ifdef CRT
		
		static ChPtr::Shared<BaseMesh9> MeshType(const std::string& _fileName);

		static ChPtr::Shared<BaseMesh9> SkinMeshType(const std::string& _fileName);

#endif

		friend MeshManager9;
		friend MeshList9;
		friend ChObjectController9;

	protected:

#ifdef CRT
		virtual void OpenFile(
			const std::string& _fileName,
			const std::string& _pathName,
			const LPDIRECT3DDEVICE9& _dev) {}
#endif

	public://Ins Functions//

		virtual LPD3DXMESH InsMesh() { return mesh; }

#ifdef CRT
		std::vector<ChPtr::Shared<ChMaterialA_9>>& InsMaterials() { return material; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsTex() { return texList; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsNormalTex() { return normalTex; }

		std::vector<ChPtr::Shared<MeshFace9>>& InsFace() { return easyFaceList; }
#endif

		virtual void SetOffsetVertex();

	protected://Member Method//

		LPD3DXMESH mesh = nullptr;//メッシュの形状//

		size_t vertexNum = 0;

#ifdef CRT
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> texList;//テクスチャーの内容//
		std::vector<ChPtr::Shared<ChMaterialA_9>> material;//マテリアルの内容//
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> normalTex;//法線マッピング//

		std::vector<ChPtr::Shared<ChVec3_9>>optimalVertexList;//最適化した頂点//
		std::vector<ChPtr::Shared<MeshFace9>>easyFaceList;//最適化した頂点//

		std::vector<ChPtr::Shared<ChVec3_9>>offsetVertexList;//初期の頂点位置//
#endif

	}Mesh9;
}



#ifdef CRT

void ChMesh::BaseMesh9::SetOffsetVertex(const ChVec3_9& _vertex)
{
	auto&& ver = ChPtr::Make_S<ChVec3_9>();
	*ver = _vertex;
	offsetVertexList.push_back(ver);
}

void ChMesh::BaseMesh9::SetMaterialCol(
	const unsigned long _Num,
	const ChVec4& _Dif)
{
	if (material.size() <= _Num)return;

	material[_Num]->Diffuse.a = _Dif.a;
	material[_Num]->Diffuse.r = _Dif.r;
	material[_Num]->Diffuse.g = _Dif.g;
	material[_Num]->Diffuse.b = _Dif.b;
}

void ChMesh::BaseMesh9::SetMaterialMatrix(
	const unsigned long _Num,
	const ChLMat& _Mat)
{
	if (material.size() <= _Num)return;

	material[_Num]->mat = _Mat;
}

ChVec3_9 ChMesh::BaseMesh9::GetOffsetVertex(unsigned long _num)
{
	if (offsetVertexList.size() <= _num)return ChVec3_9();
	return (*offsetVertexList[_num]);
}

unsigned long ChMesh::BaseMesh9::GetMaterialCount()
{
	return material.size();
}

ChMaterialA_9 ChMesh::BaseMesh9::GetMaterial(unsigned long _num)
{
	if (material.size() <= _num)return ChMaterialA_9();
	return *material[_num];
}

ChTex::BaseTexture9* ChMesh::BaseMesh9::GetTexture(unsigned long _num)
{
	if (texList.size() <= _num)return nullptr;
	return texList[_num].get();
}

void ChMesh::BaseMesh9::Release() {

	if (ChPtr::NullCheck(mesh))return;

	if (!material.empty())material.clear();

	if (!texList.empty())texList.clear();
	if (!normalTex.empty())normalTex.clear();
	if (!easyFaceList.empty())easyFaceList.clear();

	mesh->Release();

	mesh = nullptr;

}
const ChMesh::MeshFace9* ChMesh::BaseMesh9::GetFace(unsigned long _num) const
{
	if (easyFaceList.size() >= _num)return nullptr;
	return easyFaceList[_num].get(); 
}

void ChMesh::BaseMesh9::CreateEasyFaceList()
{
	MeshVertex9* meshData = nullptr;

	WORD* p = nullptr;

	mesh->LockIndexBuffer(0, (LPVOID*)&p);
	mesh->LockVertexBuffer(0, (LPVOID*)&meshData);

	for (unsigned long faceNum = 0; faceNum < mesh->GetNumFaces(); faceNum++)
	{

		auto meshFace = ChPtr::Make_S<MeshFace9>();

		CreateEasyFace(*meshFace, faceNum, meshData, p);

		easyFaceList.push_back(meshFace);
	}

	mesh->UnlockIndexBuffer();
	mesh->UnlockVertexBuffer();
}
#endif

#include"ChMeshShared9.h"

#endif