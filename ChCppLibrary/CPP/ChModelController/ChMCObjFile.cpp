#include"ChMCObjFile.h"

#define SET_VECTOR_FUNCTION(_SetVecPascal, _SetVecCamel,_VectorStruct) \
template<typename CharaType>\
inline void ChCpp::ModelController::ObjFile<CharaType>::Set##_SetVecPascal(const std::basic_string<CharaType>& _line){\
	std::basic_string<CharaType>tag = ObjTag::Get##_SetVecPascal##Tag<CharaType>();\
	if (!IsPrefix(_line, tag, tag.length()))return;\
	NullModelTest();\
	auto _SetVecCamel = ChPtr::Make_S<_VectorStruct>();\
	_SetVecCamel->template Deserialize<CharaType>(_line, tag.length() + 1, ChStd::GetSpaceChara<CharaType>());\
	makeObject->vertex##_SetVecPascal##List.push_back(_SetVecCamel);}

#define SET_METHOD(_FunctionName, _TagValue,_SetMethod) \
template<typename CharaType>\
inline void ChCpp::ModelController::ObjFile<CharaType>::_FunctionName(const std::basic_string<CharaType>& _line){\
	std::basic_string<CharaType>tag = _TagValue;\
	if (!IsPrefix(_line, tag, tag.length()))return;\
	_SetMethod }


#define OBJECT_FILE_NAME_TYPE_FUNCTION(type) CH_NUMBER_FUNCTION(GetNullObjectName,type)

#define OBJECT_MATERIAL_NAME_TYPE_FUNCTION(type) CH_NUMBER_FUNCTION(GetNullObjectName,type)

#define NULL_OBJECT_NAME_FUNCTION(type) CH_NUMBER_FUNCTION(GetNullObjectName,type)

#define TAG_COMMENT_FUNCTION(type) CH_NUMBER_FUNCTION(GetCommentTag,type)

#define TAG_USE_MATERIAL_FILE_NAME_FUNCTION(type) CH_NUMBER_FUNCTION(GetUseMaterialFileNameTag,type)

#define TAG_MATERIAL_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION(GetMaterialBlockTag,type)

#define TAG_OBJECT_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION(GetObjectBlockTag,type)

#define TAG_GROUP_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION(GetGroupBlockTag,type)

#define TAG_SMOUTH_SHADING_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION(GetSmouthShadingBlockTag,type)

#define TAG_VERTEX_FUNCTION(type) CH_NUMBER_FUNCTION(GetVertexTag,type)

#define TAG_UV_FUNCTION(type) CH_NUMBER_FUNCTION(GetUVTag,type)

#define TAG_NORMAL_FUNCTION(type) CH_NUMBER_FUNCTION(GetNormalTag,type)

#define TAG_MESH_FUNCTION(type) CH_NUMBER_FUNCTION(GetMeshTag,type)

#define TAG_LINE_FUNCTION(type) CH_NUMBER_FUNCTION(GetLineTag,type)

#define TAG_PARAM_VERTEX_FUNCTION(type) CH_NUMBER_FUNCTION(GetParamVertexTag,type)

#define TAG_MAT_MATERIAL_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatMaterialBlockTag,type)

#define TAG_MAT_AMBIENT_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatAmbientTag,type)

#define TAG_MAT_DIFFUSE_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatDiffuseTag,type)

#define TAG_MAT_SPECULAR_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatSpecularTag,type)

#define TAG_MAT_SPECULAR_HIGH_LIGHT_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatSpecularHighLightTag,type)

#define TAG_MAT_DISSOLVE_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatDissolveTag,type)

#define TAG_MAT_UN_DISSOLVE_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatUnDissolveTag,type)

#define TAG_MAT_O_DENSITY_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatODensityTag,type)

#define TAG_MAT_LIGHT_OBJECT_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatLightObjectTag,type)

#define TAG_MAT_AMBIENT_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatAmbientMapTag,type)

#define TAG_MAT_DIFFUSE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatDiffuseMapTag,type)

#define TAG_MAT_SPECULAR_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatSpecularMapTag,type)

#define TAG_MAT_SPECULAR_HIGH_LIGHT_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatSpecularHighLightMapTag,type)

#define TAG_MAT_DISSOLVE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatDissolveMapTag,type)

#define TAG_MAT_BUMP_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatBumpMapTag,type)

#define TAG_MAT_BUMP_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatBumpMapTag2,type)

#define TAG_MAT_DISPLATE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatDisplateMapTag,type)

#define TAG_MAT_DECAL_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatDecalMapTag,type)

#define TAG_MAT_ROUGHNESS_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatRoughnessMapTag,type)

#define TAG_MAT_ROUGHNESS_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatRoughnessMapTag2,type)

#define TAG_MAT_METALLIC_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatMetallicMapTag,type)

#define TAG_MAT_METALLIC_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatMetallicMapTag2,type)

#define TAG_MAT_SHEEN_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatSheenMapTag,type)

#define TAG_MAT_SHEEN_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatSheenMapTag2,type)

#define TAG_MAT_CLEARCOAT_THICKNESS_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatClearcoatThicknessMapTags,type)

#define TAG_MAT_CLEARCOAT_ROUGHNESS_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatClearcoatRoughnessMapTags,type)

#define TAG_MAT_RADIATION_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatRadiationMapTag,type)

#define TAG_MAT_RADIATION_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatRadiationMapTag2,type)

#define TAG_MAT_ANISOTROPY_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatAnisotropyMapTag,type)

#define TAG_MAT_ANISOTROPY_ROTATE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatAnisotropyRotateMapTag,type)

#define TAG_MAT_NORMAL_MAP_FUNCTION(type) CH_NUMBER_FUNCTION(GetMatNormalMapTag,type)




namespace ChCpp
{

	namespace ModelController
	{

		namespace ObjTag
		{
			CH_TO_NUMBER_FUNCTION(NULL_OBJECT_NAME_FUNCTION, "Root");

			CH_TO_NUMBER_FUNCTION(TAG_COMMENT_FUNCTION, "#");
			CH_TO_NUMBER_FUNCTION(TAG_USE_MATERIAL_FILE_NAME_FUNCTION, "mtllib");
			CH_TO_NUMBER_FUNCTION(TAG_MATERIAL_BLOCK_FUNCTION, "usemtl");
			CH_TO_NUMBER_FUNCTION(TAG_OBJECT_BLOCK_FUNCTION, "o");
			CH_TO_NUMBER_FUNCTION(TAG_GROUP_BLOCK_FUNCTION, "g");
			CH_TO_NUMBER_FUNCTION(TAG_SMOUTH_SHADING_BLOCK_FUNCTION, "s");

			CH_TO_NUMBER_FUNCTION(TAG_VERTEX_FUNCTION, "v");
			CH_TO_NUMBER_FUNCTION(TAG_UV_FUNCTION, "vt");
			CH_TO_NUMBER_FUNCTION(TAG_NORMAL_FUNCTION, "vn");
			CH_TO_NUMBER_FUNCTION(TAG_MESH_FUNCTION, "f");
			CH_TO_NUMBER_FUNCTION(TAG_LINE_FUNCTION, "l");
			CH_TO_NUMBER_FUNCTION(TAG_PARAM_VERTEX_FUNCTION, "vp");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_MATERIAL_BLOCK_FUNCTION, "newmtl");

			CH_TO_NUMBER_FUNCTION(TAG_MAT_AMBIENT_FUNCTION, "Ka");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_DIFFUSE_FUNCTION, "Kd");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_SPECULAR_FUNCTION, "Ks");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_SPECULAR_HIGH_LIGHT_FUNCTION, "Ns");

			CH_TO_NUMBER_FUNCTION(TAG_MAT_DISSOLVE_FUNCTION, "d");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_UN_DISSOLVE_FUNCTION, "Tr");

			CH_TO_NUMBER_FUNCTION(TAG_MAT_O_DENSITY_FUNCTION, "Ni");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_LIGHT_OBJECT_FUNCTION, "illum");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_AMBIENT_MAP_FUNCTION, "map_Ka");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_DIFFUSE_MAP_FUNCTION, "map_Kd");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_SPECULAR_MAP_FUNCTION, "map_Ks");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_SPECULAR_HIGH_LIGHT_MAP_FUNCTION, "map_Ns");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_DISSOLVE_MAP_FUNCTION, "map_d");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_BUMP_MAP_FUNCTION, "map_bump");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_BUMP_MAP2_FUNCTION, "bump");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_DISPLATE_MAP_FUNCTION, "disp");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_DECAL_MAP_FUNCTION, "decal");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_ROUGHNESS_MAP_FUNCTION, "map_Pr");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_ROUGHNESS_MAP2_FUNCTION, "Pr");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_METALLIC_MAP_FUNCTION, "map_Pm");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_METALLIC_MAP2_FUNCTION, "Pm");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_SHEEN_MAP_FUNCTION, "map_Ps");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_SHEEN_MAP2_FUNCTION, "Ps");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_CLEARCOAT_THICKNESS_MAP_FUNCTION, "Pc");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_CLEARCOAT_ROUGHNESS_MAP_FUNCTION, "Pcr");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_RADIATION_MAP_FUNCTION, "map_Ke");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_RADIATION_MAP2_FUNCTION, "Ke");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_ANISOTROPY_MAP_FUNCTION, "aniso");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_ANISOTROPY_ROTATE_MAP_FUNCTION, "anisor");
			CH_TO_NUMBER_FUNCTION(TAG_MAT_NORMAL_MAP_FUNCTION, "norm");
		}
	}
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::Release()
{
	objects.clear();
	materialMaps.clear();
	makeObject = nullptr;
	targetMaterial = nullptr;
	folderPath = ChStd::GetZeroChara<CharaType>();
	blockMaterial = ChStd::GetZeroChara<CharaType>();
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::LoadModel(const std::basic_string<CharaType>& _filePath)
{
	if (_filePath.size() <= 0)return;

	ChCpp::TextObject<CharaType> text;
	text.SetCutChar(ChStd::GetLFChara<CharaType>());

	{
		ChCpp::CharFile files;
		files.FileOpen(_filePath, false);
		std::string tmp = files.FileRead();
		files.FileClose();

		if (tmp.length() <= 0)return;

		text.SetText(ChCpp::GetConvertText<CharaType>(tmp));
	}

	folderPath = ModelControllerBase<CharaType>::GetRoutePath(_filePath);

	Release();

	for (auto line : text)
	{
		if (line.length() <= 0)continue;
		if (line[0] == ObjTag::GetCommentTag<CharaType>()[0])continue;

		CreateMaterials(line);

		CreateObject(line);
		SetVertex(line);
		SetUV(line);
		SetNormal(line);
		SetFace(line);
		SetMateBlock(line);
	}

	if (objects.size() <= 0)return;

	filePath = _filePath;
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::OutModel(const std::basic_string<CharaType>& _filePath)
{
	if (objects.empty())return;
	if (_filePath.size() <= 0)return;
	if (_filePath.rfind(ChStd::GetDotChara<CharaType>()) == std::basic_string<CharaType>::npos)return;

	std::basic_string<CharaType> tmpFolderPath = ChStd::GetZeroChara<CharaType>();
	std::basic_string<CharaType> tmpMtlFilePath = ChStd::GetZeroChara<CharaType>();

	size_t slashPos = _filePath.rfind(ChStd::GetSlashChara<CharaType>()) + 1;
	if (slashPos > _filePath.length())slashPos = 0;

	tmpMtlFilePath = _filePath.substr(slashPos, _filePath.rfind(ChStd::GetDotChara<CharaType>()) - slashPos);
	tmpFolderPath = ModelControllerBase<CharaType>::GetRoutePath(_filePath);






}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model)
{
	if (_model == nullptr)return;
	if (objects.empty())return;

	ChCpp::ModelControllerBase<CharaType>::Init();

	_model->SetModelName(filePath);

	_model->SetMyName(ObjTag::GetNullObjectName<CharaType>());

	_model->template SetComponent<FrameComponent<CharaType>>();

	CreateChFrame(_model);

	ChCpp::ModelControllerBase<CharaType>::SetMaxPos(*_model, ChCpp::ModelControllerBase<CharaType>::maxPos);
	ChCpp::ModelControllerBase<CharaType>::SetMinPos(*_model, ChCpp::ModelControllerBase<CharaType>::minPos);
	ChCpp::ModelControllerBase<CharaType>::SetCenterPos(*_model, ChCpp::ModelControllerBase<CharaType>::CreateCenterPos(ChCpp::ModelControllerBase<CharaType>::minPos, ChCpp::ModelControllerBase<CharaType>::maxPos));
	ChCpp::ModelControllerBase<CharaType>::SetBoxSize(*_model, ChCpp::ModelControllerBase<CharaType>::CreateBoxSize(ChCpp::ModelControllerBase<CharaType>::minPos, ChCpp::ModelControllerBase<CharaType>::maxPos));

	_model->Create();
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::SetModel(const ChPtr::Shared<ModelObject<CharaType>> _model)
{
	if (_model == nullptr)return;
	objects.clear();
	materialMaps.clear();


	filePath = _model->GetModelName();
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::CreateObject(const std::basic_string<CharaType>& _objectName)
{
	std::basic_string<CharaType>tag = ObjTag::GetObjectBlockTag<CharaType>();
	if (!IsPrefix(_objectName, tag, tag.length()))return;

	auto name = _objectName.substr(2);

	auto obj = ChPtr::Make_S<ObjFileModelData>();

	obj->sVertex = makeObject != nullptr ? makeObject->sVertex + makeObject->vertexVertexList.size() : 0;
	obj->sUV = makeObject != nullptr ? makeObject->sUV + makeObject->vertexUVList.size() : 0;
	obj->sNormal = makeObject != nullptr ? makeObject->sNormal + makeObject->vertexNormalList.size() : 0;

	makeObject = nullptr;

	makeObject = obj;
	//ObjectMaps[Name] = MakeObject;
	makeObject->objectName = name;
	objects.push_back(makeObject);
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::CreateMaterials(const std::basic_string<CharaType>& _fileName)
{
	std::basic_string<CharaType>tag = ObjTag::GetUseMaterialFileNameTag<CharaType>();
	if (!IsPrefix(_fileName, tag, tag.length()))return;

	std::basic_string<CharaType> fileName = &_fileName[7];

	ChCpp::TextObject<CharaType> text;
	text.SetCutChar(ChStd::GetLFChara<CharaType>());

	{
		ChCpp::CharFile files;
		files.FileOpen(folderPath + fileName, false);

		std::string test = files.FileRead();

		std::basic_string<CharaType> tmp = ChStd::GetZeroChara<CharaType>();

		tmp = ChCpp::GetConvertText<CharaType>(test);

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp.c_str());
	}

	for (auto line : text)
	{
		if (line.length() <= 0)continue;
		if (line[0] == ObjTag::GetCommentTag<CharaType>()[0])continue;

		CreateMaterial(line);
		SetMatAmbient(line);
		SetMatDiffuse(line);
		SetMatSpecular(line);
		SetMatSpecularHighLight(line);
		SetMatDissolve(line);
		SetMatODensity(line);
		SetMatAmbientMap(line);
		SetMatDiffuseMap(line);
		SetMatSpecularMap(line);
		SetMatSpecularHighLightMap(line);
		SetMatBumpMap(line);
		SetMatMetallicMap(line);
		SetMatNormalMap(line);
	}

}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::CreateMaterial(const std::basic_string<CharaType>& _matName)
{
	std::basic_string<CharaType>tag = ObjTag::GetMatMaterialBlockTag<CharaType>();
	if (!IsPrefix(_matName, tag, tag.length()))return;

	targetMaterial = nullptr;

	targetMaterial = ChPtr::Make_S<ObjFileMaterialData>();

	materialMaps[&_matName[7]] = targetMaterial;
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::CreateChFrame(ChPtr::Shared<ChCpp::FrameObject<CharaType>> _frame)
{
	//for (auto&& Obj : ObjectMaps)
	for (auto&& obj : objects)
	{
		unsigned long materialNo = 0;

		auto&& mesh = ChPtr::Make_S<ChCpp::FrameObject<CharaType>>();

		auto&& primitive = mesh->template SetComponent<ChCpp::FrameComponent<CharaType>>();

		//for (auto&& Vertexs : Obj.second->vertexPosList)
		for (auto&& vertexs : obj->vertexVertexList)
		{
			auto ver = ChPtr::Make_S<Ch3D::SavePolyVertex>();

			ver->pos = *vertexs;

			primitive->vertexList.push_back(ver);

			primitive->maxPos = ModelControllerBase<CharaType>::TestMaxPos(primitive->maxPos, ver->pos);
			primitive->minPos = ModelControllerBase<CharaType>::TestMinPos(primitive->minPos, ver->pos);
		}

		primitive->centerPos = ModelControllerBase<CharaType>::CreateCenterPos(primitive->minPos, primitive->maxPos);
		primitive->boxSize = ModelControllerBase<CharaType>::CreateBoxSize(primitive->minPos, primitive->maxPos);

		//for (auto&& Face : Obj.second->MeshDatas)
		for (auto&& face : obj->meshDatas)
		{
			if (materialMaps.empty())
			{
				primitive->mateNames[ChStd::GetZeroChara<CharaType>()] = materialNo;

				auto&& mate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

				mate->mateName = face->targetMaterialName;

				mate->mate.diffuse = ChVec4(1.0f);

				mate->mate.specularColor = ChVec3(1.0f);

				mate->mate.specularPower = 0.0f;

				mate->mate.ambient = 0.3f;

				primitive->materialList.push_back(mate);
				materialNo++;

				mate = nullptr;
			}
			else if (primitive->mateNames.find(face->targetMaterialName) == primitive->mateNames.end())
			{

				primitive->mateNames[face->targetMaterialName] = materialNo;

				auto mate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

				mate->mateName = face->targetMaterialName;
				auto& tmpMate = materialMaps[mate->mateName];

				mate->mate.diffuse = tmpMate->diffuse;
				mate->mate.diffuse.a = tmpMate->alpha;

				mate->mate.specularColor = tmpMate->specular;

				mate->mate.specularPower = tmpMate->spePow;

				mate->mate.ambient = tmpMate->ambient.r + tmpMate->ambient.g + tmpMate->ambient.b;

				mate->mate.ambient /= 3;

				mate->textures[Ch3D::TextureType::Diffuse] = (tmpMate->diffuseMap);
				mate->textures[Ch3D::TextureType::Ambient] = (tmpMate->ambientMap);
				mate->textures[Ch3D::TextureType::Specular] = (tmpMate->specularMap);
				mate->textures[Ch3D::TextureType::SpecularHighLight] = (tmpMate->specularHighLightMap);
				mate->textures[Ch3D::TextureType::Bump] = (tmpMate->bumpMap);
				mate->textures[Ch3D::TextureType::Alpha] = (tmpMate->alphaMap);
				mate->textures[Ch3D::TextureType::Normal] = (tmpMate->normalMap);
				mate->textures[Ch3D::TextureType::Metallic] = (tmpMate->metallicMap);


				primitive->materialList.push_back(mate);
				materialNo++;

				mate = nullptr;
			}

			auto fVList = ChPtr::Make_S<Ch3D::Primitive>();

			fVList->mateNo = static_cast<unsigned long>(primitive->mateNames[face->targetMaterialName]);

			for (auto&& values : face->values)
			{

				//unsigned long NVertex = Values->VertexNum - Obj.second->SVertex - 1;
				//unsigned long NUV = Values->UVNum - Obj.second->SUV - 1;
				//unsigned long NNormal = Values->NormalNum - Obj.second->SNormal - 1;
				size_t nVertex = values->vertexNum - 1 - obj->sVertex;
				size_t nUV = values->uvNum - 1 - obj->sUV;
				size_t nNormal = values->normalNum - 1 - obj->sNormal;

				auto faceVertex = ChPtr::Make_S<Ch3D::SavePolyData>();

				faceVertex->vertexNo = static_cast<unsigned long>(nVertex);
				//if(Obj.second->UVDatas.size() > NUV)faceVertex->UVPos = *Obj.second->UVDatas[NUV];
				if (obj->vertexUVList.size() > nUV)faceVertex->uv = *obj->vertexUVList[nUV];

				fVList->vertexData.push_back(faceVertex);

				//mesh->VertexList[NVertex]->Normal += *Obj.second->vertexNormalList[NNormal];
				primitive->vertexList[nVertex]->normal += *obj->vertexNormalList[nNormal];
				fVList->faceNormal += *obj->vertexNormalList[nNormal];

			}

			fVList->faceNormal.Normalize();

			primitive->primitives.push_back(fVList);
		}

		for (auto&& ver : primitive->vertexList)
		{
			ver->normal.Normalize();
		}

		mesh->SetMyName(obj->objectName);

		_frame->SetChild(mesh);

		ChCpp::ModelControllerBase<CharaType>::maxPos = ModelControllerBase<CharaType>::TestMaxPos(primitive->maxPos, ChCpp::ModelControllerBase<CharaType>::maxPos);
		ChCpp::ModelControllerBase<CharaType>::minPos = ModelControllerBase<CharaType>::TestMinPos(primitive->minPos, ChCpp::ModelControllerBase<CharaType>::minPos);
	}
}

SET_VECTOR_FUNCTION(Vertex, vertex, ChVec3);

SET_VECTOR_FUNCTION(UV, uv, ChVec2);

SET_VECTOR_FUNCTION(Normal, normal, ChVec3);

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::SetFace(const std::basic_string<CharaType>& _line)
{
	std::basic_string<CharaType>tag = ObjTag::GetMeshTag<CharaType>();
	if (!IsPrefix(_line, tag, tag.length()))return;

	NullModelTest();

	size_t pos = _line.find(ChStd::GetSpaceChara<CharaType>());

	size_t tmpPos = pos;

	size_t end = 0;

	auto data = ChPtr::Make_S<typename ObjFile<CharaType>::ObjFileModelData::MeshData>();

	data->targetMaterialName = blockMaterial;

	makeObject->meshDatas.push_back(data);

	bool endFlg = false;

	while (1)
	{

		tmpPos = _line.find(ChStd::GetSpaceChara<CharaType>(), pos + 1);

		if (_line.size() < tmpPos)
		{
			endFlg = true;
			tmpPos = _line.size();
		}

		auto&& mdata = ChPtr::Make_S<typename ObjFile<CharaType>::ObjFileModelData::MeshData::Data>();


		std::basic_string<CharaType> tmp = _line.substr(pos, tmpPos - pos);

		unsigned long val[3] = { 0xffffffff,0xffffffff ,0xffffffff };

		//SrashCount//
		size_t sCount = 0;

		size_t start = 0;

		while (1)
		{
			end = tmp.find(ChStd::GetSlashChara<CharaType>()[0], start);

			if (tmp.size() <= end)end = tmp.size();

			if (tmp[start] != ChStd::GetSlashChara<CharaType>()[0])
			{
				val[sCount] = ChStr::GetNumFromText<unsigned long>(tmp.substr(start, end - start));
			}

			if (tmp.size() <= end)break;

			sCount++;
			start = end + 1;
		}

		pos += tmp.length();

		mdata->vertexNum = val[0];
		mdata->uvNum = val[1];
		mdata->normalNum = val[2];

		data->values.push_back(mdata);
		if (endFlg)break;

		end = 0;
	}
}

SET_METHOD(SetMateBlock, ObjTag::GetMaterialBlockTag<CharaType>(), (blockMaterial = &_line[tag.length() + 1]););

SET_METHOD(SetMatAmbient, ObjTag::GetMatAmbientTag<CharaType>(), (targetMaterial->ambient.template Deserialize<CharaType>(&_line[tag.length() + 1], 0, ChStd::GetSpaceChara<CharaType>())););

SET_METHOD(SetMatDiffuse, ObjTag::GetMatDiffuseTag<CharaType>(), (targetMaterial->diffuse.template Deserialize<CharaType>(&_line[tag.length() + 1], 0, ChStd::GetSpaceChara<CharaType>())););

SET_METHOD(SetMatSpecular, ObjTag::GetMatSpecularTag<CharaType>(), (targetMaterial->specular.template Deserialize<CharaType>(&_line[tag.length() + 1], 0, ChStd::GetSpaceChara<CharaType>())););

SET_METHOD(SetMatSpecularHighLight, ObjTag::GetMatSpecularHighLightTag<CharaType>(), (targetMaterial->spePow = ChStr::GetNumFromText<float>(&_line[tag.length() + 1], 0)););

SET_METHOD(SetMatDissolve, ObjTag::GetMatDissolveTag<CharaType>(), (targetMaterial->alpha = ChStr::GetNumFromText<float>(&_line[tag.length() + 1], 0)););

SET_METHOD(SetMatODensity, ObjTag::GetMatODensityTag<CharaType>(), (targetMaterial->ODensity = ChStr::GetNumFromText<float>(&_line[tag.length() + 1], 0)););

SET_METHOD(SetMatAmbientMap, ObjTag::GetMatAmbientMapTag<CharaType>(), (targetMaterial->ambientMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatDiffuseMap, ObjTag::GetMatDiffuseMapTag<CharaType>(), (targetMaterial->diffuseMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatSpecularMap, ObjTag::GetMatSpecularMapTag<CharaType>(), (targetMaterial->specularMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatSpecularHighLightMap, ObjTag::GetMatSpecularHighLightMapTag<CharaType>(), (targetMaterial->specularHighLightMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatBumpMap, ObjTag::GetMatBumpMapTag<CharaType>(), (targetMaterial->bumpMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatBumpMap2, ObjTag::GetMatBumpMapTag2<CharaType>(), (targetMaterial->bumpMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatMetallicMap, ObjTag::GetMatMetallicMapTag<CharaType>(), (targetMaterial->metallicMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatMetallicMap2, ObjTag::GetMatMetallicMapTag2<CharaType>(), (targetMaterial->metallicMap = LoadTextureName(&_line[tag.length() + 1])););

SET_METHOD(SetMatNormalMap, ObjTag::GetMatNormalMapTag<CharaType>(), (targetMaterial->normalMap = LoadTextureName(&_line[tag.length() + 1])););

template<typename CharaType>
bool ChCpp::ModelController::ObjFile<CharaType>::IsPrefix(const std::basic_string<CharaType>& _str, const std::basic_string<CharaType>& _prefix, const size_t _prefixSize)
{
	if (_str.size() <= (_prefixSize + 1))return false;

	if (_str[_prefixSize] != ' ')return false;

	for (unsigned long i = 0; i < _prefixSize; i++)
	{

		if (_str[_prefixSize - i - 1] != _prefix[_prefixSize - i - 1])return false;
	}

	return true;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::ModelController::ObjFile<CharaType>::LoadTextureName(const std::basic_string<CharaType>& _line)
{
	bool loadFlg = false;
	std::basic_string<CharaType> name = ChStd::GetZeroChara<CharaType>();

	size_t nowPos = 0;
	size_t nowEndPos = 0;

	while (1)
	{
		nowPos = nowEndPos;
		nowEndPos = _line.find(ChStd::GetSpaceChara<CharaType>(), nowPos + 1);

		if (nowEndPos == _line.npos)nowEndPos = _line.length();

		if (_line[nowPos + 1] == ChStd::GetHyphenChara<CharaType>()[0])
		{
			nowPos = nowEndPos;
			nowEndPos = _line.find(ChStd::GetSpaceChara<CharaType>(), nowPos + 1);

			continue;
		}

		name = _line.substr(nowPos, nowEndPos - nowPos);
		break;
	}
	return name;
}

template<typename CharaType>
void ChCpp::ModelController::ObjFile<CharaType>::NullModelTest()
{
	if (makeObject != nullptr)return;

	std::basic_string<CharaType> createText = ObjTag::GetObjectBlockTag<CharaType>();

	createText = createText + ChStd::GetSpaceChara<CharaType>() + ObjTag::GetNullObjectName<CharaType>();

	CreateObject(createText);
}


CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::ModelController::ObjFile);