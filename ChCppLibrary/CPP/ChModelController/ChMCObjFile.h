#ifndef Ch_CPP_ObjMesh_h
#define Ch_CPP_ObjMesh_h

#include<string>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChStr.h"

#include"ChModelControllerBase.h"

#include"../ChFile/ChFile.h"
#include"../ChTextObject/ChTextObject.h"

namespace ChCpp
{
	namespace ModelController
	{
		namespace ObjTag
		{
			//"Root"//
			CH_NUMBER_FUNCTION_BASE(GetNullObjectName);


			//"#"//
			CH_NUMBER_FUNCTION_BASE(GetCommentTag);

			//"mtllib"//
			CH_NUMBER_FUNCTION_BASE(GetUseMaterialFileNameTag);

			//"usemtl"//
			CH_NUMBER_FUNCTION_BASE(GetMaterialBlockTag);
			
			//"o"//
			CH_NUMBER_FUNCTION_BASE(GetObjectBlockTag);
			
			//"g"//
			CH_NUMBER_FUNCTION_BASE(GetGroupBlockTag);
			
			//"s"//
			CH_NUMBER_FUNCTION_BASE(GetSmouthShadingBlockTag);
			

			//"v"//
			CH_NUMBER_FUNCTION_BASE(GetVertexTag);

			//"vt"//
			CH_NUMBER_FUNCTION_BASE(GetUVTag);

			//"vn"//
			CH_NUMBER_FUNCTION_BASE(GetNormalTag);

			//"f"//
			CH_NUMBER_FUNCTION_BASE(GetMeshTag);

			//"l"//
			CH_NUMBER_FUNCTION_BASE(GetLineTag);

			//"vp"//
			CH_NUMBER_FUNCTION_BASE(GetParamVertexTag);

			//"newmtl"//
			CH_NUMBER_FUNCTION_BASE(GetMatMaterialBlockTag);


			//"Ka"//
			CH_NUMBER_FUNCTION_BASE(GetMatAmbientTag);

			//"Kd"//
			CH_NUMBER_FUNCTION_BASE(GetMatDiffuseTag);

			//"Ks"//
			CH_NUMBER_FUNCTION_BASE(GetMatSpecularTag);

			//"Ns"//
			CH_NUMBER_FUNCTION_BASE(GetMatSpecularHighLightTag);


			//"d"//
			CH_NUMBER_FUNCTION_BASE(GetMatDissolveTag);

			//"Tr"//
			CH_NUMBER_FUNCTION_BASE(GetMatUnDissolveTag);



			//"Ni"//
			CH_NUMBER_FUNCTION_BASE(GetMatODensityTag);

			//"illum"//
			CH_NUMBER_FUNCTION_BASE(GetMatLightObjectTag);

			//"map_Ka"//
			CH_NUMBER_FUNCTION_BASE(GetMatAmbientMapTag);

			//"map_Kd"//
			CH_NUMBER_FUNCTION_BASE(GetMatDiffuseMapTag);

			//"map_Ks"//
			CH_NUMBER_FUNCTION_BASE(GetMatSpecularMapTag);

			//"map_Ns"//
			CH_NUMBER_FUNCTION_BASE(GetMatSpecularHighLightMapTag);

			//"map_d"//
			CH_NUMBER_FUNCTION_BASE(GetMatDissolveMapTag);

			//"map_bump"//
			CH_NUMBER_FUNCTION_BASE(GetMatBumpMapTag);

			//"bump"//
			CH_NUMBER_FUNCTION_BASE(GetMatBumpMapTag2);

			//"disp"//
			CH_NUMBER_FUNCTION_BASE(GetMatDisplateMapTag);

			//"decal"//
			CH_NUMBER_FUNCTION_BASE(GetMatDecalMapTag);

			//"map_Pr"//
			CH_NUMBER_FUNCTION_BASE(GetMatRoughnessMapTag);

			//"Pr"//
			CH_NUMBER_FUNCTION_BASE(GetMatRoughnessMapTag2);

			//"map_Pm"//
			CH_NUMBER_FUNCTION_BASE(GetMatMetallicMapTag);

			//"Pm"//
			CH_NUMBER_FUNCTION_BASE(GetMatMetallicMapTag2);

			//"map_Ps"//
			CH_NUMBER_FUNCTION_BASE(GetMatSheenMapTag);

			//"map_Ps"//
			CH_NUMBER_FUNCTION_BASE(GetMatSheenMapTag2);

			//"Pc"//
			CH_NUMBER_FUNCTION_BASE(GetMatClearcoatThicknessMapTags);

			//"Pcr"//
			CH_NUMBER_FUNCTION_BASE(GetMatClearcoatRoughnessMapTags);

			//"map_Ke"//
			CH_NUMBER_FUNCTION_BASE(GetMatRadiationMapTag);

			//"Ke"//
			CH_NUMBER_FUNCTION_BASE(GetMatRadiationMapTag2);

			//"aniso"//
			CH_NUMBER_FUNCTION_BASE(GetMatAnisotropyMapTag);

			//"ansior"//
			CH_NUMBER_FUNCTION_BASE(GetMatAnisotropyRotateMapTag);

			//"norm"//
			CH_NUMBER_FUNCTION_BASE(GetMatNormalMapTag);
		}

		template<typename CharaType>
		class ObjFile :public ModelControllerBase<CharaType>
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

				std::basic_string<CharaType> ambientMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> diffuseMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> specularMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> specularHighLightMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> bumpMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> metallicMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> alphaMap = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> normalMap = ChStd::GetZeroChara<CharaType>();
			};

			struct ObjFileModelData
			{
				struct MeshData
				{
					struct Data
					{
						size_t vertexNum;
						size_t normalNum;
						size_t uvNum;
					};

					std::basic_string<CharaType> targetMaterialName = ChStd::GetZeroChara<CharaType>();
					std::vector<ChPtr::Shared<Data>> values;
				};

				size_t sVertex = 0;
				size_t sUV = 0;
				size_t sNormal = 0;

				std::vector<ChPtr::Shared<ChVec3>> vertexVertexList;
				std::vector<ChPtr::Shared<ChVec2>> vertexUVList;
				std::vector<ChPtr::Shared<ChVec3>> vertexNormalList;
				std::vector<ChPtr::Shared<MeshData>> meshDatas;
				std::basic_string<CharaType> objectName = ChStd::GetZeroChara<CharaType>();
			};

		public:

			void LoadModel(const std::basic_string<CharaType>& _filePath)override;

			void OutModel(const std::basic_string<CharaType>& _filePath)override;

			void CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model)override;

			void SetModel(const ChPtr::Shared<ModelObject<CharaType>> _model)override;

		protected:

			void Release();

			void CreateObject(const std::basic_string<CharaType>& _objectName);

			void CreateMaterials(const std::basic_string<CharaType>& _fileName);

			void CreateMaterial(const std::basic_string<CharaType>& _aatName);

			void CreateChFrame(ChPtr::Shared<ChCpp::FrameObject<CharaType>> _frame);

		protected://SetFunction//

			// Load Model Methods //

			void SetVertex(const std::basic_string<CharaType>& _line);

			void SetUV(const std::basic_string<CharaType>& _line);

			void SetNormal(const std::basic_string<CharaType>& _line);

			void SetFace(const std::basic_string<CharaType>& _line);

			void SetMateBlock(const std::basic_string<CharaType>& _line);

			void SetMatAmbient(const std::basic_string<CharaType>& _line);

			void SetMatDiffuse(const std::basic_string<CharaType>& _line);

			void SetMatSpecular(const std::basic_string<CharaType>& _line);

			void SetMatSpecularHighLight(const std::basic_string<CharaType>& _line);

			//Alphaíl//
			void SetMatDissolve(const std::basic_string<CharaType>& _line);

			//ã¸ê‹ó¶//
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

			// Set Model Methods //
			


		protected://Is Functions//

			bool IsPrefix(const std::basic_string<CharaType>& _str, const std::basic_string<CharaType>& _prefix, const size_t _prefixSize);

		protected://Other Functions//

			std::basic_string<CharaType> LoadTextureName(const std::basic_string<CharaType>& _line);

			void NullModelTest();

		protected://Values//

			std::basic_string<CharaType> folderPath = ChStd::GetZeroChara<CharaType>();
			std::basic_string<CharaType> filePath = ChStd::GetZeroChara<CharaType>();

			std::vector<ChPtr::Shared<ObjFileModelData>>objects;

			std::map<std::basic_string<CharaType>, ChPtr::Shared<ObjFileMaterialData>>materialMaps;

			std::basic_string<CharaType> blockMaterial = ChStd::GetZeroChara<CharaType>();

			ChPtr::Shared<ObjFileModelData>makeObject = nullptr;
			ChPtr::Shared<ObjFileMaterialData>targetMaterial = nullptr;
		};
	}
}

#endif