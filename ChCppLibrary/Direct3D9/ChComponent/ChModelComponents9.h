
#ifndef Ch_D3D9_ModelCom_h
#define Ch_D3D9_ModelCom_h

typedef class ChModelComponent9 :public ChCpp::BaseComponent
{
public:
#ifdef CRT

	virtual void SetModel(const std::string& _modelName)
	{
		model = nullptr;

		std::string mName = _modelName;
		std::string path = "./";

		DIvidePathToName(path, mName, _modelName);

		model = ChMesh::BaseMesh9::MeshType(mName);

		model->CreateMesh(mName, path, ChD3D9::D3D9API().GetDevice());

		if (ChPtr::NullCheck(model->GetMesh()))model = nullptr;
	}

#endif
	
	ChMesh::BaseMesh9* GetModel();
	
	void Draw3D()override;

protected:

#ifdef CRT
	
	void DIvidePathToName(
		std::string& _path,
		std::string& _name,
		const std::string& _fullPathName)
	{
		size_t sPos = 0;

		bool tmpFlg = false;

		size_t slashSize = 1;
		std::string slash[2]
		{
			"/","\\"
		};

		for (auto&& sla : slash)
		{
			if ((sPos = _fullPathName.rfind(sla.c_str(), _fullPathName.size()))
				== std::string::npos)continue;

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

#endif

protected:

#ifdef CRT

	ChPtr::Shared<ChMesh::BaseMesh9>model = nullptr;

#endif

}ChModelCom9;



typedef class ChMModelComponent9 :public ChModelCom9
{
public:

#ifdef CRT

	void SetModel(const std::string& _modelName)override
	{
		std::string mName = _modelName;
		std::string path = "./";

		model = nullptr;

		DIvidePathToName(path, mName, _modelName);

		auto tmpMesh = ChMesh::MeManager9().GetMesh(mName);

		if (tmpMesh != nullptr)
		{
			model = tmpMesh;
			return;
		}

		if (!ChMesh::MeManager9().IsPath(path))
		{
			ChMesh::MeManager9().SetDirectoryPath(path, path);
		}

		ChMesh::MeManager9().SetMesh(mName, mName, path);

		model = ChMesh::MeManager9().GetMesh(mName);

	}

#endif

protected:

}ChMModelCom9;

typedef class ChSkinMeshModelComponent9 :public ChModelCom9
{
public:

#ifdef CRT

	void SetModel(const std::string& _modelName)override
	{
		model = nullptr;

		std::string mName = _modelName;
		std::string path = "./";

		DIvidePathToName(path, mName, _modelName);


		model = ChMesh::BaseMesh9::SkinMeshType(mName);

		model->CreateMesh(mName, path, ChD3D9::D3D9API().GetDevice());

		if (ChPtr::NullCheck(model->GetMesh()))model = nullptr;

	}

#endif

	ChMesh::SkinMesh9* GetSkinModel();

	void Update()override;

private:

}ChSkModelCom9;

typedef class ChMSkinMeshModelComponent9 :public ChSkModelCom9
{
public:

#ifdef CRT

	void SetModel(const std::string& _modelName)override
	{
		std::string mName = _modelName;
		std::string path = "./";

		model = nullptr;

		DIvidePathToName(path, mName, _modelName);

		auto tmpMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(ChMesh::MeManager9().GetMesh(mName));

		if (tmpMesh != nullptr)
		{
			model = tmpMesh;

			return;
		}

		if (ChMesh::MeManager9().IsMesh(mName))return;

		if (!ChMesh::MeManager9().IsPath(path))
		{
			ChMesh::MeManager9().SetDirectoryPath(path, path);
		}

		ChMesh::MeManager9().SetSkinMesh(mName, mName, path);

		model = ChMesh::MeManager9().GetMesh(mName);
	}

#endif

private:

}ChMSkModelCom9;

#ifdef CRT

ChMesh::BaseMesh9* ChModelComponent9::GetModel() { return model.get(); }

ChMesh::SkinMesh9* ChSkinMeshModelComponent9::GetSkinModel()
{
	return ChPtr::SafeCast<ChMesh::SkinMesh9>(model.get());
}

#endif

#endif
