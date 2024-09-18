
#ifndef Ch_D3D9_XMe_h
#define Ch_D3D9_XMe_h

#include"ChBaseMesh9.h"

namespace ChMesh
{

	class XFileMesh9 :public BaseMesh9
	{
	public:

#ifdef CRT
		void OpenFile(
			const std::string& _fileName,
			const std::string& _pathName,
			const LPDIRECT3DDEVICE9& _dev)override;
#endif

	};
}

#ifdef CRT


void ChMesh::XFileMesh9::OpenFile(
	const std::string& _fileName,
	const std::string& _pathName,
	const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(".x") == std::string::npos)return;

	std::string tmpStr;
	tmpStr = _pathName + "/" + _fileName;

	if (_pathName.length() <= 0)tmpStr = "." + tmpStr;

	{
		LPD3DXBUFFER tmpBuffer;

		DWORD numMaterial;

		D3DXLoadMeshFromXA(
			tmpStr.c_str(),
			D3DXMESH_MANAGED,
			_dev,
			NULL,
			&tmpBuffer,
			NULL,
			&(numMaterial),
			&(mesh));

		if (ChPtr::NullCheck(mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::string tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {


			auto tmpMat = ChPtr::Make_S<ChMaterialA_9>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = "";

			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + "/" + tmpString;
				if (_pathName.length() <= 0)tmpString = "." + tmpString;

			}
			material.push_back(tmpMat);

			auto tmpTex = ChTex::BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex()))
				tmpTex->CreateColTexture(_dev);

			texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{
		LPD3DXMESH tmpMesh = nullptr;
		HRESULT res;
		res = mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1,//テクスチャ座標
			_dev,
			&tmpMesh//クローン先
		);

		mesh->Release();

		mesh = tmpMesh;
	}

	SetMaterialName(tmpStr);
}


#endif

#include"ChMeshShared9.h"

#endif