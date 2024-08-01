#ifndef Ch_CPP_ObjMesh_h
#define Ch_CPP_ObjMesh_h

#ifdef CRT

#include<string>

#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChStr.h"

#include"ChModelLoaderBase.h"

#include"../ChFile/ChFile.h"
#include"../ChTextObject/ChTextObject.h"

#ifndef CH_LM_OBJ_TAG_COMMENT_FUNCTION
#define CH_LM_OBJ_TAG_COMMENT_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetCommentTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_USE_MATERIAL_FILE_NAME_FUNCTION
#define CH_LM_OBJ_TAG_USE_MATERIAL_FILE_NAME_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetUseMaterialFileNameTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MATERIAL_BLOCK_FUNCTION
#define CH_LM_OBJ_TAG_MATERIAL_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMaterialBlockTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_OBJECT_BLOCK_FUNCTION
#define CH_LM_OBJ_TAG_OBJECT_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetObjectBlockTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_GROUP_BLOCK_FUNCTION
#define CH_LM_OBJ_TAG_GROUP_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetGroupBlockTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_SMOUTH_SHADING_BLOCK_FUNCTION
#define CH_LM_OBJ_TAG_SMOUTH_SHADING_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetSmouthShadingBlockTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_VERTEX_FUNCTION
#define CH_LM_OBJ_TAG_VERTEX_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetVertexTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_UV_FUNCTION
#define CH_LM_OBJ_TAG_UV_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetUVTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_NORMAL_FUNCTION
#define CH_LM_OBJ_TAG_NORMAL_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetNormalTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MESH_FUNCTION
#define CH_LM_OBJ_TAG_MESH_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMeshTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_LINE_FUNCTION
#define CH_LM_OBJ_TAG_LINE_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetLineTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_PARAM_VERTEX_FUNCTION
#define CH_LM_OBJ_TAG_PARAM_VERTEX_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetParamVertexTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_MATERIAL_BLOCK_FUNCTION
#define CH_LM_OBJ_TAG_MAT_MATERIAL_BLOCK_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatMaterialBlockTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_AMBIENT_FUNCTION
#define CH_LM_OBJ_TAG_MAT_AMBIENT_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatAmbientTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_DIFFUSE_FUNCTION
#define CH_LM_OBJ_TAG_MAT_DIFFUSE_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatDiffuseTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_SPECULAR_FUNCTION
#define CH_LM_OBJ_TAG_MAT_SPECULAR_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatSpecularTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_SPECULAR_HIGH_LIGHT_FUNCTION
#define CH_LM_OBJ_TAG_MAT_SPECULAR_HIGH_LIGHT_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatSpecularHighLightTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_DISSOLVE_FUNCTION
#define CH_LM_OBJ_TAG_MAT_DISSOLVE_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatDissolveTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_UN_DISSOLVE_FUNCTION
#define CH_LM_OBJ_TAG_MAT_UN_DISSOLVE_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatUnDissolveTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_O_DENSITY_FUNCTION
#define CH_LM_OBJ_TAG_MAT_O_DENSITY_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatODensityTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_LIGHT_OBJECT_FUNCTION
#define CH_LM_OBJ_TAG_MAT_LIGHT_OBJECT_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatLightObjectTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_AMBIENT_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_AMBIENT_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatAmbientMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_DIFFUSE_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_DIFFUSE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatDiffuseMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_SPECULAR_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_SPECULAR_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatSpecularMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_SPECULAR_HIGH_LIGHT_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_SPECULAR_HIGH_LIGHT_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatSpecularHighLightMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_DISSOLVE_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_DISSOLVE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatDissolveMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_BUMP_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_BUMP_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatBumpMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_BUMP_MAP2_FUNCTION
#define CH_LM_OBJ_TAG_MAT_BUMP_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatBumpMapTag2,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_DISPLATE_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_DISPLATE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatDisplateMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_DECAL_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_DECAL_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatDecalMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_ROUGHNESS_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_ROUGHNESS_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatRoughnessMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_ROUGHNESS_MAP2_FUNCTION
#define CH_LM_OBJ_TAG_MAT_ROUGHNESS_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatRoughnessMapTag2,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_METALLIC_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_METALLIC_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatMetallicMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_METALLIC_MAP2_FUNCTION
#define CH_LM_OBJ_TAG_MAT_METALLIC_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatMetallicMapTag2,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_SHEEN_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_SHEEN_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatSheenMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_SHEEN_MAP2_FUNCTION
#define CH_LM_OBJ_TAG_MAT_SHEEN_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatSheenMapTag2,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_CLEARCOAT_THICKNESS_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_CLEARCOAT_THICKNESS_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatClearcoatThicknessMapTags,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_CLEARCOAT_ROUGHNESS_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_CLEARCOAT_ROUGHNESS_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatClearcoatRoughnessMapTags,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_RADIATION_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_RADIATION_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatRadiationMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_RADIATION_MAP2_FUNCTION
#define CH_LM_OBJ_TAG_MAT_RADIATION_MAP2_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatRadiationMapTag2,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_ANISOTROPY_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_ANISOTROPY_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatAnisotropyMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_ANISOTROPY_ROTATE_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_ANISOTROPY_ROTATE_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatAnisotropyRotateMapTag,type)
#endif

#ifndef CH_LM_OBJ_TAG_MAT_NORMAL_MAP_FUNCTION
#define CH_LM_OBJ_TAG_MAT_NORMAL_MAP_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMatNormalMapTag,type)
#endif



#ifndef CH_LM_OBJ_NULL_OBJECT_NAME_FUNCTION
#define CH_LM_OBJ_NULL_OBJECT_NAME_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetNullObjectName,type)
#endif

#ifndef CH_LM_OBJ_SET_VECTOR_FUNCTION
#define CH_LM_OBJ_SET_VECTOR_FUNCTION(_SetVecPascal, _SetVecCamel,_VectorStruct) \
template<typename CharaType>\
void ChCpp::ModelLoader::ObjFile<CharaType>::Set##_SetVecPascal##(const std::basic_string<CharaType>& _line){\
	std::basic_string<CharaType>tag = ObjTag::Get##_SetVecPascal##Tag<CharaType>();\
	if (!IsPrefix(_line, tag, tag.length()))return;\
	NullModelTest();\
	auto _SetVecCamel = ChPtr::Make_S<##_VectorStruct##>();\
	_SetVecCamel##->Deserialize<CharaType>(_line, tag.length() + 1, ChStd::GetSpaceChara<CharaType>());\
	makeObject->vertex##_SetVecPascal##List.push_back(_SetVecCamel);}
#endif

#ifndef CH_LM_OBJ_SET_METHOD
#define CH_LM_OBJ_SET_METHOD(_FunctionName, _TagValue,_SetMethod) \
template<typename CharaType>\
void ChCpp::ModelLoader::ObjFile<CharaType>::##_FunctionName##(const std::basic_string<CharaType>& _line){\
	std::basic_string<CharaType>tag = _TagValue;\
	if (!IsPrefix(_line, tag, tag.length()))return;\
	_SetMethod }

#endif

namespace ChCpp
{

	namespace ModelLoader
	{

		namespace ObjTag
		{
#ifdef CRT
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_NULL_OBJECT_NAME_FUNCTION, "Root");

			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_COMMENT_FUNCTION, "#");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_USE_MATERIAL_FILE_NAME_FUNCTION, "mtllib");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MATERIAL_BLOCK_FUNCTION, "usemtl");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_OBJECT_BLOCK_FUNCTION, "o");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_GROUP_BLOCK_FUNCTION, "g");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_SMOUTH_SHADING_BLOCK_FUNCTION, "s");

			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_VERTEX_FUNCTION, "v");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_UV_FUNCTION, "vt");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_NORMAL_FUNCTION, "vn");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MESH_FUNCTION, "f");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_LINE_FUNCTION, "l");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_PARAM_VERTEX_FUNCTION, "vp");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_MATERIAL_BLOCK_FUNCTION, "newmtl");

			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_AMBIENT_FUNCTION, "Ka");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_DIFFUSE_FUNCTION, "Kd");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_SPECULAR_FUNCTION, "Ks");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_SPECULAR_HIGH_LIGHT_FUNCTION, "Ns");

			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_DISSOLVE_FUNCTION, "d");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_UN_DISSOLVE_FUNCTION, "Tr");

			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_O_DENSITY_FUNCTION, "Ni");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_LIGHT_OBJECT_FUNCTION, "illum");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_AMBIENT_MAP_FUNCTION, "map_Ka");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_DIFFUSE_MAP_FUNCTION, "map_Kd");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_SPECULAR_MAP_FUNCTION, "map_Ks");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_SPECULAR_HIGH_LIGHT_MAP_FUNCTION, "map_Ns");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_DISSOLVE_MAP_FUNCTION, "map_d");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_BUMP_MAP_FUNCTION, "map_bump");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_BUMP_MAP2_FUNCTION, "bump");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_DISPLATE_MAP_FUNCTION, "disp");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_DECAL_MAP_FUNCTION, "decal");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_ROUGHNESS_MAP_FUNCTION, "map_Pr");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_ROUGHNESS_MAP2_FUNCTION, "Pr");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_METALLIC_MAP_FUNCTION, "map_Pm");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_METALLIC_MAP2_FUNCTION, "Pm");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_SHEEN_MAP_FUNCTION, "map_Ps");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_SHEEN_MAP2_FUNCTION, "Ps");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_CLEARCOAT_THICKNESS_MAP_FUNCTION, "Pc");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_CLEARCOAT_ROUGHNESS_MAP_FUNCTION, "Pcr");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_RADIATION_MAP_FUNCTION, "map_Ke");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_RADIATION_MAP2_FUNCTION, "Ke");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_ANISOTROPY_MAP_FUNCTION, "aniso");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_ANISOTROPY_ROTATE_MAP_FUNCTION, "anisor");
			CH_TO_NUMBER_FUNCTION(CH_LM_OBJ_TAG_MAT_NORMAL_MAP_FUNCTION, "norm");
#endif
		}

		template<typename CharaType>
		class ObjFile :public ModelLoaderBase<CharaType>
		{
		protected:

			struct ObjFileMaterialData
			{
				ChVec3 ambient;
				ChVec3 diffuse;
				ChVec3 specular;

				float spePow = 1.0f;
				float alpha = 1.0f;
				float ODensity = 1.0f;

#ifdef CRT
				std::basic_string<CharaType> ambientMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> diffuseMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> specularMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> specularHighLightMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> bumpMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> metallicMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> alphaMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> normalMap = ChStd::GetZeroChara<CharaType>();
#endif
			};

			struct ObjFileModelData
			{
				struct MeshData
				{
					struct Data
					{
						unsigned long vertexNum;
						unsigned long normalNum;
						unsigned long uvNum;
					};
#ifdef CRT
					std::basic_string<CharaType> targetMaterialName = ChStd::GetZeroChara<CharaType>();
					std::vector<ChPtr::Shared<Data>> values;
#endif

				};

#ifdef CRT
				std::vector<ChPtr::Shared<ChVec3>> vertexVertexList;
				std::vector<ChPtr::Shared<ChVec2>> vertexUVList;
				std::vector<ChPtr::Shared<ChVec3>> vertexNormalList;
#endif

				unsigned long sVertex = 0;
				unsigned long sUV = 0;
				unsigned long sNormal = 0;

#ifdef CRT
				std::vector<ChPtr::Shared<MeshData>> meshDatas;
				std::basic_string<CharaType> objectName = ChStd::GetZeroChara<CharaType>();
#endif
			};

		public:

#ifdef CRT
			//モデルデータの読み込み口//
			void CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)override;

			void OutModelFile(const ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)override;
#endif
		protected:

			void Release();

#ifdef CRT
			void CreateObject(const std::basic_string<CharaType>& _objectName);

			void CreateMaterials(const std::basic_string<CharaType>& _fileName);

			void CreateMaterial(const std::basic_string<CharaType>& _aatName);

			void CreateChFrame(ChPtr::Shared<ChCpp::FrameObject<CharaType>> _frame);
#endif
		protected://SetFunction//

#ifdef CRT

			void SetVertex(const std::basic_string<CharaType>& _line);

			void SetUV(const std::basic_string<CharaType>& _line);

			void SetNormal(const std::basic_string<CharaType>& _line);

			void SetFace(const std::basic_string<CharaType>& _line);

			void SetMateBlock(const std::basic_string<CharaType>& _line);

			void SetMatAmbient(const std::basic_string<CharaType>& _line);

			void SetMatDiffuse(const std::basic_string<CharaType>& _line);

			void SetMatSpecular(const std::basic_string<CharaType>& _line);

			void SetMatSpecularHighLight(const std::basic_string<CharaType>& _line);

			//Alpha値//
			void SetMatDissolve(const std::basic_string<CharaType>& _line);

			//屈折率//
			void SetMatODensity(const std::basic_string<CharaType>& _line);

			void SetMatAmbientMap(const std::basic_string<CharaType>& _line);

			void SetMatDiffuseMap(const std::basic_string<CharaType>& _line);

			void SetMatSpecularMap(const std::basic_string<CharaType>& _line);

			void SetMatSpecularHighLightMap(const std::basic_string<CharaType>& _line);

			void SetMatBumpMap(const std::basic_string<CharaType>& _line);
			void SetMatBumpMap2(const std::basic_string<CharaType>& _line);

			void SetMatMetallicMap(const std::basic_string<CharaType>& _line);
			void SetMatMetallicMap2(const std::basic_string<CharaType>& _line);

			void SetMatNormalMap(const std::basic_string<CharaType>& _line);

#endif

		protected://Is Functions//

#ifdef CRT
			bool IsPrefix(const std::basic_string<CharaType>& _str, const std::basic_string<CharaType>& _prefix, const unsigned long _prefixSize);
#endif
		protected://Other Functions//

#ifdef CRT
			std::basic_string<CharaType> LoadTextureName(const std::basic_string<CharaType>& _line);
#endif
			void NullModelTest();

		protected://Values//

#ifdef CRT

			std::basic_string<CharaType> folderPath = ChStd::GetZeroChara<CharaType>();

			std::vector<ChPtr::Shared<ObjFileModelData>>objects;

			std::map<std::basic_string<CharaType>, ChPtr::Shared<ObjFileMaterialData>>materialMaps;

			std::basic_string<CharaType> blockMaterial = ChStd::GetZeroChara<CharaType>();

			ChPtr::Shared<ObjFileModelData>makeObject = nullptr;
			ChPtr::Shared<ObjFileMaterialData>targetMaterial = nullptr;
#endif
		};
	}
}


#ifdef CRT

template<typename CharaType>
void ChCpp::ModelLoader::ObjFile<CharaType>::Release()
{
	objects.clear();
	materialMaps.clear();
	makeObject = nullptr;
	targetMaterial = nullptr;
	folderPath = ChStd::GetZeroChara<CharaType>();
	blockMaterial = ChStd::GetZeroChara<CharaType>();
}

template<typename CharaType>
void ChCpp::ModelLoader::ObjFile<CharaType>::CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)
{

	if (!_model->IsInit())return;

	if (_filePath.size() <= 0)return;

	ChCpp::TextObject<CharaType> text;
	text.SetCutChar(ChStd::GetLFChara<CharaType>());

	{
		std::basic_string<CharaType> tmp = ChStd::GetZeroChara<CharaType>();

		ChCpp::File<CharaType> files;
		files.SetLocaleName("Japanese");
		files.FileOpen(_filePath);
		tmp = files.FileReadText();
		files.FileClose();

		if (tmp.length() <= 0)return;

		text.SetText(tmp.c_str());
	}

	folderPath = ModelLoaderBase<CharaType>::GetRoutePath(_filePath);

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

	ChCpp::ModelLoaderBase<CharaType>::Init();

	_model->SetModelName(_filePath);

	_model->SetMyName(ObjTag::GetNullObjectName<CharaType>());

	_model->SetComponent<FrameComponent<CharaType>>();

	CreateChFrame(_model);

	ChCpp::ModelLoaderBase<CharaType>::SetMaxPos(*_model, ChCpp::ModelLoaderBase<CharaType>::maxPos);
	ChCpp::ModelLoaderBase<CharaType>::SetMinPos(*_model, ChCpp::ModelLoaderBase<CharaType>::minPos);
	ChCpp::ModelLoaderBase<CharaType>::SetCenterPos(*_model, ChCpp::ModelLoaderBase<CharaType>::CreateCenterPos(ChCpp::ModelLoaderBase<CharaType>::minPos, ChCpp::ModelLoaderBase<CharaType>::maxPos));
	ChCpp::ModelLoaderBase<CharaType>::SetBoxSize(*_model, ChCpp::ModelLoaderBase<CharaType>::CreateBoxSize(ChCpp::ModelLoaderBase<CharaType>::minPos, ChCpp::ModelLoaderBase<CharaType>::maxPos));

	_model->Create();
}

template<typename CharaType>
void ChCpp::ModelLoader::ObjFile<CharaType>::CreateObject(const std::basic_string<CharaType>& _objectName)
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
void ChCpp::ModelLoader::ObjFile<CharaType>::CreateMaterials(const std::basic_string<CharaType>& _fileName)
{
	std::basic_string<CharaType>tag = ObjTag::GetUseMaterialFileNameTag<CharaType>();
	if (!IsPrefix(_fileName, tag, tag.length()))return;

	std::basic_string<CharaType> fileName = &_fileName[7];

	ChCpp::TextObject<CharaType> text;
	text.SetCutChar(ChStd::GetLFChara<CharaType>());

	{
		std::basic_string<CharaType> tmp;

		ChCpp::File<CharaType> files;
		files.SetLocaleName("Japanese");
		files.FileOpen(folderPath + fileName);

		tmp = files.FileReadText();

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
void ChCpp::ModelLoader::ObjFile<CharaType>::CreateMaterial(const std::basic_string<CharaType>& _matName)
{
	std::basic_string<CharaType>tag = ObjTag::GetMatMaterialBlockTag<CharaType>();
	if (!IsPrefix(_matName, tag, tag.length()))return;

	targetMaterial = nullptr;

	targetMaterial = ChPtr::Make_S<ObjFileMaterialData>();

	materialMaps[&_matName[7]] = targetMaterial;
}

template<typename CharaType>
void ChCpp::ModelLoader::ObjFile<CharaType>::CreateChFrame(ChPtr::Shared<ChCpp::FrameObject<CharaType>> _frame)
{
	//for (auto&& Obj : ObjectMaps)
	for (auto&& obj : objects)
	{
		unsigned long materialNo = 0;

		auto&& mesh = ChPtr::Make_S<ChCpp::FrameObject<CharaType>>();

		auto&& primitive = mesh->SetComponent<ChCpp::FrameComponent<CharaType>>();

		//for (auto&& Vertexs : Obj.second->vertexPosList)
		for (auto&& vertexs : obj->vertexVertexList)
		{
			auto ver = ChPtr::Make_S<Ch3D::SavePolyVertex>();

			ver->pos = *vertexs;

			primitive->vertexList.push_back(ver);

			primitive->maxPos = ModelLoaderBase<CharaType>::TestMaxPos(primitive->maxPos, ver->pos);
			primitive->minPos = ModelLoaderBase<CharaType>::TestMinPos(primitive->minPos, ver->pos);
		}

		primitive->centerPos = ModelLoaderBase<CharaType>::CreateCenterPos(primitive->minPos, primitive->maxPos);
		primitive->boxSize = ModelLoaderBase<CharaType>::CreateBoxSize(primitive->minPos, primitive->maxPos);

		//for (auto&& Face : Obj.second->MeshDatas)
		for (auto&& face : obj->meshDatas)
		{
			if (materialMaps.empty())
			{
				primitive->mateNames[ChStd::GetZeroChara<CharaType>()] = materialNo;

				auto mate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

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

			fVList->mateNo = primitive->mateNames[face->targetMaterialName];

			for (auto&& values : face->values)
			{

				//unsigned long NVertex = Values->VertexNum - Obj.second->SVertex - 1;
				//unsigned long NUV = Values->UVNum - Obj.second->SUV - 1;
				//unsigned long NNormal = Values->NormalNum - Obj.second->SNormal - 1;
				unsigned long nVertex = values->vertexNum - 1 - obj->sVertex;
				unsigned long nUV = values->uvNum - 1 - obj->sUV;
				unsigned long nNormal = values->normalNum - 1 - obj->sNormal;

				auto faceVertex = ChPtr::Make_S<Ch3D::SavePolyData>();

				faceVertex->vertexNo = nVertex;
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

		ChCpp::ModelLoaderBase<CharaType>::maxPos = ModelLoaderBase<CharaType>::TestMaxPos(primitive->maxPos, ChCpp::ModelLoaderBase<CharaType>::maxPos);
		ChCpp::ModelLoaderBase<CharaType>::minPos = ModelLoaderBase<CharaType>::TestMinPos(primitive->minPos, ChCpp::ModelLoaderBase<CharaType>::minPos);
	}
}

template<typename CharaType>
void ChCpp::ModelLoader::ObjFile<CharaType>::OutModelFile(const ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)
{
	if (_filePath.size() <= 0)return;
	if (_filePath.rfind(ChStd::GetDotChara<CharaType>()) == std::basic_string<CharaType>::npos)return;

}

CH_LM_OBJ_SET_VECTOR_FUNCTION(Vertex, vertex, ChVec3);

CH_LM_OBJ_SET_VECTOR_FUNCTION(UV, uv, ChVec2);

CH_LM_OBJ_SET_VECTOR_FUNCTION(Normal, normal, ChVec3);

template<typename CharaType>
void ChCpp::ModelLoader::ObjFile<CharaType>::SetFace(const std::basic_string<CharaType>& _line)
{
	std::basic_string<CharaType>tag = ObjTag::GetMeshTag<CharaType>();
	if (!IsPrefix(_line, tag, tag.length()))return;

	NullModelTest();

	unsigned long pos = _line.find(ChStd::GetSpaceChara<CharaType>());

	unsigned long tmpPos = pos;

	unsigned long end = 0;

	auto data = ChPtr::Make_S<ObjFile<CharaType>::ObjFileModelData::MeshData>();

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

		auto&& mdata = ChPtr::Make_S<ObjFile<CharaType>::ObjFileModelData::MeshData::Data>();


		std::basic_string<CharaType> tmp = _line.substr(pos, tmpPos - pos);

		unsigned long val[3] = { 0xffffffff,0xffffffff ,0xffffffff };

		//SrashCount//
		unsigned long sCount = 0;

		unsigned long start = 0;

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

CH_LM_OBJ_SET_METHOD(SetMateBlock, ObjTag::GetMaterialBlockTag<CharaType>(), (blockMaterial = &_line[tag.length() + 1]););

CH_LM_OBJ_SET_METHOD(SetMatAmbient, ObjTag::GetMatAmbientTag<CharaType>(), (targetMaterial->ambient.Deserialize<CharaType>(&_line[tag.length() + 1], 0, ChStd::GetSpaceChara<CharaType>())););

CH_LM_OBJ_SET_METHOD(SetMatDiffuse, ObjTag::GetMatDiffuseTag<CharaType>(), (targetMaterial->diffuse.Deserialize<CharaType>(&_line[tag.length() + 1], 0, ChStd::GetSpaceChara<CharaType>())););

CH_LM_OBJ_SET_METHOD(SetMatSpecular, ObjTag::GetMatSpecularTag<CharaType>(), (targetMaterial->specular.Deserialize<CharaType>(&_line[tag.length() + 1], 0, ChStd::GetSpaceChara<CharaType>())););

CH_LM_OBJ_SET_METHOD(SetMatSpecularHighLight, ObjTag::GetMatSpecularHighLightTag<CharaType>(), (targetMaterial->spePow = ChStr::GetNumFromText<float, CharaType>(&_line[tag.length() + 1], 0)););

CH_LM_OBJ_SET_METHOD(SetMatDissolve, ObjTag::GetMatDissolveTag<CharaType>(), (targetMaterial->alpha = ChStr::GetNumFromText<float, CharaType>(&_line[tag.length() + 1], 0)););

CH_LM_OBJ_SET_METHOD(SetMatODensity, ObjTag::GetMatODensityTag<CharaType>(), (targetMaterial->ODensity = ChStr::GetNumFromText<float, CharaType>(&_line[tag.length() + 1], 0)););

CH_LM_OBJ_SET_METHOD(SetMatAmbientMap, ObjTag::GetMatAmbientMapTag<CharaType>(), (targetMaterial->ambientMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatDiffuseMap, ObjTag::GetMatDiffuseMapTag<CharaType>(), (targetMaterial->diffuseMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatSpecularMap, ObjTag::GetMatSpecularMapTag<CharaType>(), (targetMaterial->specularMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatSpecularHighLightMap, ObjTag::GetMatSpecularHighLightMapTag<CharaType>(), (targetMaterial->specularHighLightMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatBumpMap, ObjTag::GetMatBumpMapTag<CharaType>(), (targetMaterial->bumpMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatBumpMap2, ObjTag::GetMatBumpMapTag2<CharaType>(), (targetMaterial->bumpMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatMetallicMap, ObjTag::GetMatMetallicMapTag<CharaType>(), (targetMaterial->metallicMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatMetallicMap2, ObjTag::GetMatMetallicMapTag2<CharaType>(), (targetMaterial->metallicMap = LoadTextureName(&_line[tag.length() + 1])););

CH_LM_OBJ_SET_METHOD(SetMatNormalMap, ObjTag::GetMatNormalMapTag<CharaType>(), (targetMaterial->normalMap = LoadTextureName(&_line[tag.length() + 1])););

template<typename CharaType>
bool ChCpp::ModelLoader::ObjFile<CharaType>::IsPrefix(const std::basic_string<CharaType>& _str, const std::basic_string<CharaType>& _prefix, const unsigned long _prefixSize)
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
std::basic_string<CharaType> ChCpp::ModelLoader::ObjFile<CharaType>::LoadTextureName(const std::basic_string<CharaType>& _line)
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
void ChCpp::ModelLoader::ObjFile<CharaType>::NullModelTest()
{
	if (makeObject != nullptr)return;

	std::basic_string<CharaType> createText = ObjTag::GetObjectBlockTag<CharaType>();

	createText = createText + ChStd::GetSpaceChara<CharaType>() + ObjTag::GetNullObjectName<CharaType>();

	CreateObject(createText);
}

#endif

#endif