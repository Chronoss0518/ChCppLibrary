
#ifndef Ch_D3D9_ModelCom_h
#define Ch_D3D9_ModelCom_h

typedef class ChModelComponent9 :public ChCpp::BaseComponent
{
public:

	virtual void SetModel(const std::string& _modelName);
	
	ChMesh::BaseMesh9* GetModel();
	
	void Draw3D()override;

protected:

	void DIvidePathToName(
		std::string& _path,
		std::string& _name,
		const std::string& _fullPathName);

protected:

	ChPtr::Shared<ChMesh::BaseMesh9>model = nullptr;


}ChModelCom9;



typedef class ChMModelComponent9 :public ChModelCom9
{
public:

	void SetModel(const std::string& _modelName)override;

protected:

}ChMModelCom9;

typedef class ChSkinMeshModelComponent9 :public ChModelCom9
{
public:

	void SetModel(const std::string& _modelName)override;

	ChMesh::SkinMesh9* GetSkinModel();

	void Update()override;

private:

}ChSkModelCom9;

typedef class ChMSkinMeshModelComponent9 :public ChSkModelCom9
{
public:

	void SetModel(const std::string& _modelName)override;

private:

}ChMSkModelCom9;

#endif
