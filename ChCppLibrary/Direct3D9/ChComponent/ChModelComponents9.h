
#ifndef Ch_D3D9_ModelCom_h
#define Ch_D3D9_ModelCom_h


template<typename CharaType>
class ChModelComponent9 :public ChCpp::BaseComponent
{
public:

	virtual void SetModel(const std::basic_string<CharaType>& _modelName);

	
	ChMesh::BaseMesh9<CharaType>* GetModel();
	
	void Draw3D()override;

protected:

	void DIvidePathToName(
		std::basic_string<CharaType>& _path,
		std::basic_string<CharaType>& _name,
		const std::basic_string<CharaType>& _fullPathName);

protected:

	ChPtr::Shared<ChMesh::BaseMesh9<CharaType>>model = nullptr;


};


template<typename CharaType>
class ChMModelComponent9 :public ChModelComponent9<CharaType>
{
public:

	void SetModel(const std::basic_string<CharaType>& _modelName)override;

protected:

};

template<typename CharaType>
class ChSkinMeshModelComponent9 :public ChModelComponent9<CharaType>
{
public:

	void SetModel(const std::basic_string<CharaType>& _modelName)override;

	ChMesh::SkinMesh9<CharaType>* GetSkinModel();

	void Update()override;

private:

};

template<typename CharaType>
class ChMSkinMeshModelComponent9 :public ChSkinMeshModelComponent9<CharaType>
{
public:

	void SetModel(const std::basic_string<CharaType>& _modelName)override;

private:

};

#endif
