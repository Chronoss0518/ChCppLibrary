
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

void ChMesh::BaseMesh9::SetOffsetVertex(const ChVec3_9& _vertex)
{
	auto&& ver = ChPtr::Make_S<ChVec3_9>();
	*ver = _vertex;
	offsetVertexList.push_back(ver);
}


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

ChVec3_9 ChMesh::BaseMesh9::GetOffsetVertex(unsigned long _num)const
{
	if (offsetVertexList.size() <= _num)return ChVec3_9();
	return (*offsetVertexList[_num]);
}

size_t ChMesh::BaseMesh9::GetMaterialCount()const
{
	return material.size();
}

ChMaterial9 ChMesh::BaseMesh9::GetMaterial(size_t _num)const
{
	if (material.size() <= _num)return ChMaterial9();
	return *material[_num];
}

size_t ChMesh::BaseMesh9::GetTextureCount()const
{
	return texList.size();
}

ChTex::BaseTexture9* ChMesh::BaseMesh9::GetTexture(size_t _num)const
{
	if (texList.size() <= _num)return nullptr;
	return texList[_num].get();
}

size_t ChMesh::BaseMesh9::GetNormalTextureCount()const
{
	return normalTex.size();
}

ChTex::BaseTexture9* ChMesh::BaseMesh9::GetNormalTexture(size_t _num)const
{
	if (texList.size() <= _num)return nullptr;
	return normalTex[_num].get();
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

void ChMesh::SkinMesh9::Release()
{
	boneList.clear();
	boneNameList.clear();
	tAni.Release();
}

void ChMesh::SkinMesh9::SetAnimation(
	const std::string& _animationName,
	const std::string& _XFileName)
{
	BoneAnimation tmpAni;

	tmpAni = ChANiSupport().CreateKeyFrame(_XFileName);

	size_t aniNum = 0;
	for (auto&& bones : boneList)
	{
		if (tmpAni.find(bones.first) == tmpAni.end())continue;
		aniNum = tmpAni[bones.first]->GetAniCnt();
		break;
	}

	for (auto&& bones : boneList)
	{
		if (tmpAni.find(bones.first) != tmpAni.end())continue;
		auto ani = ChPtr::Make_S<ChAnimationObject9>();

		for (size_t i = 0; i < aniNum; i++)
		{
			ani->SetAniObject(ChMat_9());
		}
		tmpAni[bones.first] = ani;

	}

	if (tmpAni.size() < boneList.size())return;

	animations[_animationName] = tmpAni;

	if (startPlayAniCheck)return;
	startPlayAniCheck = true;
	nowPlayAniName = _animationName;

	for (auto&& ani : animations[nowPlayAniName])
	{
		ani.second->Play();
	}
}

void ChMesh::SkinMesh9::SetSkin()
{
	if (ChPtr::NullCheck(mesh))return;
	if (animations.size() <= 0)return;
	if (boneList.size() <= 0)return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	//BoneUpdate//
	for (auto&& boneName : boneNameList)
	{
		ChMat_9 tmpMat = boneList[boneName]->offMat;

		boneList[boneName]->updateMat = animations[nowPlayAniName][boneName]->Update();
	}

	//LastUpdateBone//

	for (unsigned long i = boneNameList.size() - 1; i + 1 > 0; i--)
	{

		ChMat_9 tmpMat = boneList[boneNameList[i]]->offMat;

		if (boneList[boneNameList[i]]->offsetBone == nullptr)
		{

			boneList[boneNameList[i]]->updateMat
				= tmpMat * boneList[boneNameList[i]]->updateMat;

			continue;
		}

		boneList[boneNameList[i]]->updateMat
			= tmpMat
			* boneList[boneNameList[i]]->updateMat
			* boneList[boneNameList[i]]->offsetBone->updateMat;
	}

	//UpdateVertex//
	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		ChMat_9 tmpMat;
		tmpMat.Clear0();
		ChVec3_9 tmpVec;

		tmpVec = GetOffsetVertex(ver);

		for (auto&& bones : boneVertexList[ver]->updateMat)
		{

			if (bones->waitPow <= 0.0f)continue;

			ChMat_9 tmp;
			tmp = (*bones->updateMat
				* bones->waitPow);

			tmpMat += tmp;

		}

		tmpVec.MatPos(tmpMat, tmpVec);

		(tmpVer + ver)->pos = tmpVec;
	}

	mesh->UnlockVertexBuffer();

}


void ChMesh::SkinMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		auto tmpPos = ChPtr::Make_S<ChVec3_9>();
		auto tmpVertex = ChPtr::Make_S<BoneVertex>();

		*tmpPos = (tmpVer + ver)->pos;

		tmpVertex->pos = (tmpVer + ver)->pos;

		offsetVertexList.push_back(tmpPos);

		boneVertexList.push_back(tmpVertex);
	}


	mesh->UnlockVertexBuffer();
	return;
}
ChPtr::Shared<ChMesh::BaseMesh9> ChMesh::BaseMesh9::MeshType(const std::string& _fileName)
{
	std::string tmpStr;
	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseMesh9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(XFILE_EXTENTION) != tmpStr.npos)
	{
		return ChPtr::Make_S<XFileMesh9>();
	}

	return ChPtr::Make_S<BaseMesh9>();

}

ChPtr::Shared<ChMesh::BaseMesh9> ChMesh::BaseMesh9::SkinMeshType(const std::string& _fileName)
{
	std::string tmpStr;
	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<SkinMesh9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(XFILE_EXTENTION) != tmpStr.npos)
	{
		return ChPtr::Make_S<SXFileMesh9>();
	}

	return ChPtr::Make_S<SkinMesh9>();
}