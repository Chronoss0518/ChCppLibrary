
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../CPP/ChFile/ChFile.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChBaseMesh9.h"
#include"MeshIncluder9.h"

using namespace ChTex;
using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		SetOffsetVertex((tmpVer + ver)->pos);
	}

	mesh->UnlockVertexBuffer();
	return;
}

void BaseMesh9::CreateEasyFace(MeshFace9& _out, unsigned long _faceNum, MeshVertex9* _meshData, WORD* _p)
{
	for (unsigned char i = 0; i < 3; i++)
	{
		_out.vertexNum[i] = (*(_p + _faceNum * 3 + i));
	}

	_out.normal = (_meshData + _out.vertexNum[0])->normal;
	_out.centerPos = GetOffsetVertex(_out.vertexNum[0]);

	for (unsigned char i = 1; i < 3; i++)
	{
		_out.normal += (_meshData + _out.vertexNum[i])->normal;
		_out.centerPos += GetOffsetVertex(_out.vertexNum[i]);
	}

	_out.normal.Normalize();
	_out.centerPos /= 3.0f;
}

void BaseMesh9::Draw(
	const ChMat_9& _mat,
	const LPDIRECT3DDEVICE9& _dev,
	const unsigned long _subNum)
{

	D3DMATERIAL9 tmpMate;
	ChMat_9 tmpMat;

	if (_subNum >= GetMaterialCount())
	{

		for (unsigned short i = 0; i < GetMaterialCount(); i++) {
			tmpMate = GetMaterial(i);

			//頂点情報の整理//
			_dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			_dev->SetMaterial(&tmpMate);
			_dev->SetTexture(0, GetTexture(i)->GetTex());

			tmpMat = GetMaterial(i).mat * _mat;
			_dev->SetTransform(D3DTS_WORLD, &tmpMat);
			_dev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

			mesh->DrawSubset(i);
		}
		return;
	}

	tmpMate = GetMaterial(_subNum);

	_dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	_dev->SetMaterial(&tmpMate);
	_dev->SetTexture(0, GetTexture(_subNum)->GetTex());

	tmpMat = GetMaterial(_subNum).mat * _mat;
	_dev->SetTransform(D3DTS_WORLD, &tmpMat);
	_dev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	mesh->DrawSubset(_subNum);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSXFileMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

const char* SXFileMesh9::frameMat = "FrameTransformMatrix {";

const char* SXFileMesh9::skinWaights = "SkinWeights {";
