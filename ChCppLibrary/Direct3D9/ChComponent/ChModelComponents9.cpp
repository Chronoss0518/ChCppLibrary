
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChObjectManager.h"


#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"../ChMeshManager/ChMeshManager9.h"
#include"ChComponent9.h"
#include"ChModelComponents9.h"


///////////////////////////////////////////////////////////////////////////////////////
//ChModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChModelComponent9<CharaType>::DIvidePathToName(
	std::basic_string<CharaType>& _path,
	std::basic_string<CharaType>& _name,
	const std::basic_string<CharaType>& _fullPathName)
{
	size_t sPos = 0;

	bool tmpFlg = false;

	size_t slashSize = 1;
	std::basic_string<CharaType> slash[2];
	slash[0] = ChStd::GetSlashChara<CharaType>();
	slash[1] = ChStd::GetYenChara<CharaType>();
	slash[1] += ChStd::GetYenChara<CharaType>();

	for (auto&& sla : slash)
	{
		if ((sPos = _fullPathName.rfind(sla.c_str(), _fullPathName.size()))
			== std::basic_string<CharaType>::npos)continue;

		size_t tmpSize = _fullPathName.size() - sPos;
		slashSize = sla.length();
		tmpFlg = true;
		break;
	}

	if (!tmpFlg)return;

	size_t tmpSize = _fullPathName.size() - sPos;

	_path = _fullPathName.substr(0, sPos);
	_name = _fullPathName.substr(sPos + slashSize, tmpSize);
}


template<typename CharaType>
void ChModelComponent9<CharaType>::SetModel(const std::basic_string<CharaType>& _modelName)
{
	model = nullptr;

	std::basic_string<CharaType> mName = _modelName;
	std::basic_string<CharaType> path = ChStd::GetCommaChara<CharaType>();
	path += ChStd::GetSlashChara<CharaType>();

	DIvidePathToName(path, mName, _modelName);

	model = ChMesh::BaseMesh9<CharaType>::MeshType(mName);

	model->CreateMesh(mName, path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(model->GetMesh()))model = nullptr;
}


template<typename CharaType>
ChMesh::BaseMesh9<CharaType>* ChModelComponent9<CharaType>::GetModel() { return model.get(); }

template<typename CharaType>
ChMesh::SkinMesh9<CharaType>* ChSkinMeshModelComponent9<CharaType>::GetSkinModel()
{
	return ChPtr::SafeCast<ChMesh::SkinMesh9<CharaType>>(ChMesh::BaseMesh9<CharaType>::model.get());
}

template<typename CharaType>
void ChModelComponent9<CharaType>::Draw3D()
{
	if (ChPtr::NullCheck(GetModel()))return;
	if (GetModel()->GetMesh() == nullptr)return;

	ChMat_9 tmpMat;
	{

		//auto Trans = LookObj()->GetTransform<ChTransformCom9>();

		//if (nullptr != Trans)
		//{
		//	tmpMat = Trans->GetMat();
		//}

	}

	ChD3D9::Shader().DrawMesh(*GetModel(), tmpMat);

}

template<typename CharaType>
void ChMModelComponent9<CharaType>::SetModel(const std::basic_string<CharaType>& _modelName)
{
	std::basic_string<CharaType> mName = _modelName;

	std::basic_string<CharaType> path = ChStd::GetCommaChara<CharaType>();
	path += ChStd::GetSlashChara<CharaType>();

	ChModelComponent9<CharaType>::model = nullptr;

	ChModelComponent9<CharaType>::DIvidePathToName(path, mName, _modelName);

	auto&& tmpMesh = ChMesh::MeManager9<CharaType>().GetMesh(mName);

	if (tmpMesh != nullptr)
	{
		ChModelComponent9<CharaType>::model = tmpMesh;
		return;
	}

	if (!ChMesh::MeManager9<CharaType>().IsPath(path))
	{
		ChMesh::MeManager9<CharaType>().SetDirectoryPath(path, path);
	}

	ChMesh::MeManager9<CharaType>().SetMesh(mName, mName, path);

	ChModelComponent9<CharaType>::model = ChMesh::MeManager9<CharaType>().GetMesh(mName);

}
///////////////////////////////////////////////////////////////////////////////////////
//ChSkinMeshModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChSkinMeshModelComponent9<CharaType>::SetModel(const std::basic_string<CharaType>& _modelName)
{
	ChModelComponent9<CharaType>::model = nullptr;

	std::basic_string<CharaType> mName = _modelName;
	std::basic_string<CharaType> path = ChStd::GetCommaChara<CharaType>();
	path += ChStd::GetSlashChara<CharaType>();

	ChModelComponent9<CharaType>::DIvidePathToName(path, mName, _modelName);


	ChModelComponent9<CharaType>::model = ChMesh::BaseMesh9<CharaType>::SkinMeshType(mName);

	ChModelComponent9<CharaType>::model->CreateMesh(mName, path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(ChModelComponent9<CharaType>::model->GetMesh()))ChModelComponent9<CharaType>::model = nullptr;

}

template<typename CharaType>
void ChSkinMeshModelComponent9<CharaType>::Update()
{
	if (ChPtr::NullCheck(ChModelComponent9<CharaType>::GetModel()))return;

	auto&& tmpModel = GetSkinModel();

	if (ChPtr::NullCheck(tmpModel))return;

	tmpModel->SetSkin();
}