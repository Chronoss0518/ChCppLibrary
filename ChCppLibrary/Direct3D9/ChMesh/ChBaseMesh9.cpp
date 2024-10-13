
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

template<typename CharaType>
void BaseMesh9<CharaType>::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		BaseMesh9<CharaType>::SetOffsetVertex((tmpVer + ver)->pos);
	}

	mesh->UnlockVertexBuffer();
	return;
}

template<typename CharaType>
void BaseMesh9<CharaType>::CreateEasyFace(MeshFace9& _out, unsigned long _faceNum, MeshVertex9* _meshData, WORD* _p)
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

template<typename CharaType>
void BaseMesh9<CharaType>::Draw(
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

template<typename CharaType>
ChPtr::Shared<ChMesh::BaseMesh9<CharaType>> ChMesh::BaseMesh9<CharaType>::MeshType(const std::basic_string<CharaType>& _fileName)
{
	std::basic_string<CharaType> tmpStr;
	{
		size_t tmpNum = _fileName.rfind(ChStd::GetDotChara<CharaType>());
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseMesh9<CharaType>>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(ChMesh::GetXFileExtension<CharaType>()) != tmpStr.npos)
	{
		return ChPtr::Make_S<XFileMesh9<CharaType>>();
	}

	return ChPtr::Make_S<BaseMesh9<CharaType>>();

}

template<typename CharaType>
ChPtr::Shared<ChMesh::BaseMesh9<CharaType>> ChMesh::BaseMesh9<CharaType>::SkinMeshType(const std::basic_string<CharaType>& _fileName)
{
	std::basic_string<CharaType> tmpStr;
	{
		size_t tmpNum = _fileName.rfind(ChStd::GetDotChara<CharaType>());
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<SkinMesh9<CharaType>>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(ChMesh::GetXFileExtension<CharaType>()) != tmpStr.npos)
	{
		return ChPtr::Make_S<SXFileMesh9<CharaType>>();
	}

	return ChPtr::Make_S<SkinMesh9<CharaType>>();
}

template<typename CharaType>
void ChMesh::SkinMesh9<CharaType>::Release()
{
	boneList.clear();
	boneNameList.clear();
	tAni.Release();
}

template<typename CharaType>
void ChMesh::SkinMesh9<CharaType>::SetAnimation(
	const std::basic_string<CharaType>& _animationName,
	const std::basic_string<CharaType>& _XFileName)
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

template<typename CharaType>
void ChMesh::SkinMesh9<CharaType>::SetSkin()
{
	if (ChPtr::NullCheck(BaseMesh9<CharaType>::mesh))return;
	if (animations.size() <= 0)return;
	if (boneList.size() <= 0)return;

	MeshVertex9* tmpVer = nullptr;
	BaseMesh9<CharaType>::mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

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
	for (unsigned long ver = 0; ver < BaseMesh9<CharaType>::mesh->GetNumVertices(); ver++)
	{
		ChMat_9 tmpMat;
		tmpMat.Clear0();
		ChVec3_9 tmpVec;

		tmpVec = BaseMesh9<CharaType>::GetOffsetVertex(ver);

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

	BaseMesh9<CharaType>::mesh->UnlockVertexBuffer();

}

template<typename CharaType>
void ChMesh::SkinMesh9<CharaType>::SetOffsetVertex()
{
	if (ChPtr::NullCheck(BaseMesh9<CharaType>::mesh))return;

	MeshVertex9* tmpVer = nullptr;
	BaseMesh9<CharaType>::mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < BaseMesh9<CharaType>::mesh->GetNumVertices(); ver++)
	{
		auto tmpPos = ChPtr::Make_S<ChVec3_9>();
		auto tmpVertex = ChPtr::Make_S<BoneVertex>();

		*tmpPos = (tmpVer + ver)->pos;

		tmpVertex->pos = (tmpVer + ver)->pos;

		BaseMesh9<CharaType>::offsetVertexList.push_back(tmpPos);

		boneVertexList.push_back(tmpVertex);
	}

	BaseMesh9<CharaType>::mesh->UnlockVertexBuffer();
	return;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(BaseMesh9);