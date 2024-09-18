
#ifdef Ch_D3D9_BMe_h
#ifdef Ch_D3D9_XMe_h
#ifdef Ch_D3D9_SkMe_h
#ifdef Ch_D3D9_SXMe_h

#ifndef Ch_D3D9_Mesh_Shared_h
#define Ch_D3D9_Mesh_Shared_h

#ifdef CRT

ChPtr::Shared<ChMesh::BaseMesh9> ChMesh::BaseMesh9::MeshType(const std::string& _fileName)
{
	std::string tmpStr;
	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseMesh9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(".x") != tmpStr.npos)
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

	if (tmpStr.find(".x") != tmpStr.npos)
	{
		return ChPtr::Make_S<SXFileMesh9>();
	}

	return ChPtr::Make_S<SkinMesh9>();
}

#endif

#endif

#endif
#endif
#endif
#endif

