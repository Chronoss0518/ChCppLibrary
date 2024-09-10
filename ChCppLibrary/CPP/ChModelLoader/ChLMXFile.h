#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#ifdef CRT

#include<vector>
#include<map>
#include<string>

#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChStr.h"

#include"ChModelLoaderBase.h"

#include"../ChFile/ChFile.h"
#include"../ChTextObject/ChTextObject.h"

#ifndef	CH_LM_XFILE_TAG_XFILE_PREFIX_FUNCTION
#define	CH_LM_XFILE_TAG_XFILE_PREFIX_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetXFilePrefixTag, type)
#endif

#ifndef	CH_LM_XFILE_TAG_TEMPLATE_FUNCTION
#define	CH_LM_XFILE_TAG_TEMPLATE_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetTemplateTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_FRAME_FUNCTION
#define	CH_LM_XFILE_TAG_FRAME_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetFrameTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_FRAME_TRANSFORM_MATRIX_FUNCTION
#define	CH_LM_XFILE_TAG_FRAME_TRANSFORM_MATRIX_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetFrameTransformMatrixTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_MESH_FUNCTION
#define	CH_LM_XFILE_TAG_MESH_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMeshTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_NORMALS_FUNCTION
#define	CH_LM_XFILE_TAG_NORMALS_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetNormalsTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_MATERIAL_LIST_FUNCTION
#define	CH_LM_XFILE_TAG_MATERIAL_LIST_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMaterialListTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_MATERIAL_FUNCTION
#define	CH_LM_XFILE_TAG_MATERIAL_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetMaterialTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_SKIN_WEIGHTS_FUNCTION
#define	CH_LM_XFILE_TAG_SKIN_WEIGHTS_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetSkinWeightsTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_TEXTURE_COORDS_FUNCTION
#define	CH_LM_XFILE_TAG_TEXTURE_COORDS_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetTextureCoordsTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_TEXTUER_FILE_NAME_FUNCTION
#define	CH_LM_XFILE_TAG_TEXTUER_FILE_NAME_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetTextureFileNameTag,type)
#endif


#ifndef CH_LM_XFILE_ROOT_OBJECT_NAME_FUNCTION
#define CH_LM_XFILE_ROOT_OBJECT_NAME_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetRootObjectName,type)
#endif

#ifndef CH_LM_XFILE_TMP_MATERIAL_NAME_FUNCTION
#define CH_LM_XFILE_TMP_MATERIAL_NAME_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetTmpMaterialName,type)
#endif

#ifndef CH_LM_XFILE_BASE_TYPE_CLASS_CHILD
#define CH_LM_XFILE_BASE_TYPE_CLASS_CHILD(_StructName,_BaseType,_BaseTypeInitialize)\
struct _StructName : public BaseType{\
	void Desirialise(\
		const std::basic_string<CharaType>& _text,\
		const size_t& _start,\
		const std::basic_string<CharaType>& _endChar)override{\
		size_t tmp = _text.find(_endChar, _start);\
		value = ChStr::GetNumFromText<_BaseType, CharaType>(_text, _start, tmp);}\
\
	std::basic_string<CharaType> Serialise()override\
	{\
		return ChStd::GetZeroChara<CharaType>();\
	}\
	_BaseType value = _BaseTypeInitialize;\
};
#endif


#ifndef CH_LM_XFILE_BASE_TYPE_CLASS_CHILD_VECTOR
#define CH_LM_XFILE_BASE_TYPE_CLASS_CHILD_VECTOR(_StructName,_BaseType,_BaseTypeInitialize)\
struct _StructName : public BaseType{\
	void Desirialise(\
		const std::basic_string<CharaType>& _text,\
		const size_t& _start,\
		const std::basic_string<CharaType>& _endChar)override{\
		value.Deserialize<CharaType>(_text, _start, ChStd::GetSemiColonChara<CharaType>(), _endChar); }\
\
	std::basic_string<CharaType> Serialise()override\
	{\
		return ChStd::GetZeroChara<CharaType>();\
	}\
	_BaseType value = _BaseTypeInitialize;\
};
#endif

namespace ChCpp
{
	namespace ModelLoader
	{
		namespace XFileTag
		{
#ifdef CRT
			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_XFILE_PREFIX_FUNCTION, "xof");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_TEMPLATE_FUNCTION,"template");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_FRAME_FUNCTION,"Frame");
			
			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_FRAME_TRANSFORM_MATRIX_FUNCTION,"FrameTransformMatrix");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_MESH_FUNCTION,"Mesh");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_NORMALS_FUNCTION,"MeshNormals");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_MATERIAL_LIST_FUNCTION,"MeshMaterialList");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_MATERIAL_FUNCTION,"Material");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_SKIN_WEIGHTS_FUNCTION,"SkinWeights");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_TEXTURE_COORDS_FUNCTION,"MeshTextureCoords");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_TEXTUER_FILE_NAME_FUNCTION,"TextureFilename");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_ROOT_OBJECT_NAME_FUNCTION,"Root");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TMP_MATERIAL_NAME_FUNCTION,"tmp Material");
#endif
		}

		template<typename CharaType>
		class XFile :public ModelLoaderBase<CharaType>
		{
		public:

			struct XFileCRT
			{
#ifdef CRT
				std::basic_string<CharaType> loadFileName = ChStd::GetZeroChara<CharaType>();
				std::basic_string<CharaType> loadFilePath = ChStd::GetZeroChara<CharaType>();
#endif
			};


		protected:

			struct XVertex :public Ch3D::PolyVertex
			{};

			struct XMaterial :public Ch3D::Material
			{
				struct XMaterialCRT
				{
#ifdef CRT
					std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();
					std::vector<std::basic_string<CharaType>>textureNameList;
#endif
				};

				XMaterial();

				~XMaterial();

				XMaterialCRT& ValueIns() { return *value; }

			private:

				XMaterialCRT* value = nullptr;

			};

			struct XFace
			{
				struct XFaceCRT
				{
#ifdef CRT
					std::vector<unsigned long> vertexNos;
#endif
				};

				XFace();

				~XFace();

				unsigned long mateNo = 0;

				XFaceCRT& ValueIns() { return *value; }

			private:

				XFaceCRT* value = nullptr;

			};

			struct XSkinWeights
			{
				struct XSkinWeightsCRT
				{
#ifdef CRT
					std::basic_string<CharaType> targetFrameName = ChStd::GetZeroChara<CharaType>();
					std::map<unsigned long, float>weitPow;
#endif
				};

				XSkinWeights();

				~XSkinWeights();

				ChLMat boneOffset;

				XSkinWeightsCRT& ValueIns() { return *value; }

			private:

				XSkinWeightsCRT* value = nullptr;

			};

			struct XMesh
			{
				struct XMeshCRT
				{
#ifdef CRT
					std::vector<ChPtr::Shared<XVertex>>vertexList;
					std::vector<ChPtr::Shared<XMaterial>>materialList;
					std::vector<ChPtr::Shared<XFace>>faceList;
#endif
				};

				XMesh();

				~XMesh();

				XMeshCRT& ValueIns() { return *value; }

			private:

				XMeshCRT* value = nullptr;

			};

			struct XFrame
			{
				struct XFrameCRT
				{
#ifdef CRT
					std::basic_string<CharaType> fName = ChStd::GetZeroChara<CharaType>();
					ChPtr::Shared<XMesh> mesh;
					std::vector<ChPtr::Shared<XFrame>>next;
					std::vector<ChPtr::Shared<XSkinWeights>>skinWeightDatas;
#endif
				};

				XFrame();

				~XFrame();

				ChLMat frameMatrix;

				XFrameCRT& ValueIns() { return *value; }

			private:

				XFrameCRT* value = nullptr;

			};

			struct BaseType
			{
#ifdef CRT
				virtual void Desirialise(
					const std::basic_string<CharaType>& _Text,
					const size_t& _Start,
					const std::basic_string<CharaType>& _EndChar) = 0;

				virtual std::basic_string<CharaType> Serialise() = 0;
#endif
			};

			struct XFileModelFrame
			{
				struct XFileModelFrameCRT
				{
#ifdef CRT
					ChPtr::Shared<XFrame> modelData = nullptr;
					std::basic_string<CharaType> modelName = ChStd::GetZeroChara<CharaType>();
#endif
				};

				XFileModelFrame();
				
				~XFileModelFrame();

				XFileModelFrameCRT& ValueIns() { return *value; }

			private:

				XFileModelFrameCRT* value = nullptr;

			};

			struct TemplateRange
			{
				struct TemplateRangeCRT
				{
#ifdef CRT
					std::vector<ChPtr::Shared<TemplateRange>> nest;
#endif
				};

				TemplateRange();

				~TemplateRange();

				size_t begin = 0;
				size_t end = 0;

				TemplateRangeCRT& ValueIns() { return *value; }

			private:

				TemplateRangeCRT* value = nullptr;

			};

		public:

			XFile();

			~XFile();

		public:

#ifdef CRT
			//モデルデータの読み込み口//
			void CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)override;

			void OutModelFile(const ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)override;
#endif
		public:

			inline void SetMaxBoneNum(const unsigned long _boneNum) { maxBoneNum = _boneNum; }

		protected:

#ifdef CRT
			//ChModelへ変換//
			void XFrameToChFrame(
				ChPtr::Shared<FrameObject<CharaType>> _chFrame,
				const ChPtr::Shared<XFrame>& _xFrame);
#endif
		protected://SetFunction//

#ifdef CRT
			bool SetFrame(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetFremeTransformMatrix(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetMesh(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetMeshNormal(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetMeshTextureCoords(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetMeshMaterialList(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetMaterial(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);

			bool SetSkinWeights(
				ChPtr::Shared<XFrame>& _frames,
				const ChPtr::Shared<TemplateRange>& _targetTemplate,
				const std::basic_string<CharaType>& _text);
#endif
		public:

			inline const unsigned long GetMaxBoneNum() const { return maxBoneNum; }

		protected:

#ifdef CRT
			template<class T>
			typename std::enable_if
				<std::is_base_of<BaseType, T>::value,
				std::vector<ChPtr::Shared<T>>>::type GetArrayValues(
					const std::basic_string<CharaType>& _text,
					const size_t& _startPos = 0,
					const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
					const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>()){

				std::vector<ChPtr::Shared<T>> res;

				std::basic_string<CharaType> useText = ChStd::GetZeroChara<CharaType>();

				{
					size_t tmpEnd = _text.find(ChStd::GetSemiColonChara<CharaType>(), _startPos);
					tmpEnd = _text.find(_endChar, tmpEnd + 1);
					tmpEnd += _endChar.length();
					useText = _text.substr(_startPos, tmpEnd - _startPos);
				}

				size_t tmpPos = 0;
				tmpPos = useText.find(ChStd::GetSemiColonChara<CharaType>());

				if (tmpPos > useText.size())tmpPos = useText.size();

				unsigned long arrayCount = 0;
				arrayCount = ChStr::GetNumFromText<unsigned long,CharaType>(useText, useText.find(ChStd::GetLFChara<CharaType>()), tmpPos);

				if (arrayCount <= 0)return res;

				for (unsigned long i = 0; i < arrayCount; i++)
				{
					size_t sPos = tmpPos + 1;
					tmpPos = useText.find(_cutChar, sPos);
					std::basic_string<CharaType> tmpEnd = _cutChar;

					if (i >= arrayCount - 1)
					{
						tmpPos = useText.find(_endChar, sPos);
						tmpEnd = _endChar;
					}

					if (tmpPos >= std::basic_string<CharaType>::npos)
					{
						res.clear();
						return res;
					}

					auto&& value = ChPtr::Make_S<T>();
					value->Desirialise(useText, sPos, tmpEnd);
					res.push_back(value);
					tmpPos += _endChar.length();
				}

				return res;
			}

			template<class T>
			typename std::enable_if
				<std::is_base_of<BaseType, T>::value,
				std::vector<ChPtr::Shared<T>>>::type GetArrayValuesNC(
					const std::basic_string<CharaType>& _text,
					const size_t& _startPos = 0,
					const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
					const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>()){

				std::vector<ChPtr::Shared<T>> res;

				std::basic_string<CharaType> useText = ChStd::GetZeroChara<CharaType>();

				{
					size_t tmpEnd = _text.find(_endChar, _startPos);
					tmpEnd += _endChar.length();
					useText = _text.substr(_startPos, tmpEnd - _startPos);
				}

				size_t tmpPos = 0;

				if (tmpPos >= useText.size())return res;

				while (tmpPos <= useText.size())
				{
					size_t sPos = tmpPos + 1;
					tmpPos = useText.find(_cutChar, sPos);
					std::basic_string<CharaType> tmpEnd = _cutChar;

					if (tmpPos >= useText.size())
					{
						tmpPos = useText.find(_endChar, sPos);
						tmpEnd = _endChar;
					}

					auto&& value = ChPtr::Make_S<T>();
					value->Desirialise(useText, sPos, tmpEnd);
					res.push_back(value);
					tmpPos += _endChar.length();

					if (tmpEnd == ChStd::GetSemiColonChara<CharaType>())break;
				}
				return res;

			}
#endif
			protected://IsFunction//

#ifdef CRT
			bool IsTags(
				size_t& _outTagPos,
				const std::basic_string<CharaType>& _tagName,
				const ChPtr::Shared<TemplateRange> _lookTemplate,
				const std::basic_string<CharaType>& _text);

			bool IsTags(
				const std::basic_string<CharaType>& _tagName,
				const ChPtr::Shared<TemplateRange> _lookTemplate,
				const std::basic_string<CharaType>& _text)
			{
				size_t tmp;

				return IsTags(tmp, _tagName, _lookTemplate, _text);
			}
#endif
			protected://TmplateCreate//

#ifdef CRT
			void LoadToTemplates(
				ChPtr::Shared<TemplateRange>& _templates,
				const size_t& _offset,
				const std::basic_string<CharaType>& _text);

			void SetToTemplate(
				ChPtr::Shared<TemplateRange>& _tmp,
				size_t& _bCnt,
				size_t& _eCnt,
				const std::vector<size_t>& _sTemplateTags,
				const std::vector<size_t>& _eTemplateTags);
#endif
		protected://XFileBaseTypes//

#ifdef CRT
			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD(XDWORD, unsigned long, 0);

			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD(XCHAR, unsigned char, 0);

			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD(XFLOAT, float, 0.0f);

			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD_VECTOR(XVECTOR, ChVec3, ChVec3(0.0f));

			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD_VECTOR(XCOODS2D, ChVec2, ChVec2(0.0f));

			struct XMESHFACE : public BaseType
			{
				void Desirialise(
					const std::basic_string<CharaType>& _text,
					const size_t& _start,
					const std::basic_string<CharaType>& _endChar)override
				{
					size_t end = _text.find(_endChar, _start);

					std::basic_string<CharaType> useText = _text.substr(_start, end - _start);


					size_t tmpPos = 0;
					tmpPos = useText.find(ChStd::GetSemiColonChara<CharaType>());

					if (tmpPos >= end)return;

					unsigned long arrayCount = 0;

					arrayCount = ChStr::GetNumFromText<unsigned long, CharaType>(useText, 0, tmpPos);

					if (arrayCount <= 0)return;

					for (unsigned long i = 0; i < arrayCount; i++)
					{

						size_t sPos = tmpPos + 1;
						tmpPos = useText.find(ChStd::GetCommaChara<CharaType>(), sPos + 1);

						if (i >= arrayCount - 1)
						{
							tmpPos = useText.find(ChStd::GetSemiColonChara<CharaType>(), sPos);
						}

						if (tmpPos >= std::basic_string<CharaType>::npos)
						{
							tmpPos = useText.size();
						}

						unsigned long Value;

						Value = ChStr::GetNumFromText<unsigned long>(useText, sPos, tmpPos);

						value.push_back(Value);
					}
				}

				std::basic_string<CharaType> Serialise()override
				{
					return ChStd::GetZeroChara<CharaType>();
				}

				std::vector<unsigned long> value;

			};


			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD_VECTOR(ColorRGBA, ChVec4, ChVec4(0.0f));

			CH_LM_XFILE_BASE_TYPE_CLASS_CHILD_VECTOR(ColorRGB, ChVec3, ChVec3(0.0f));
#endif
		protected://Member Value//

			bool exceptionFlg = false;

			unsigned long maxBoneNum = 16;
		

			XFileCRT& ValueIns() { return *value; }

		private:

			XFileCRT* value = nullptr;

		};
	}
}

#ifdef CRT

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XMaterial::XMaterial()
{
	value = new XMaterialCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XMaterial::~XMaterial()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFace::XFace()
{
	value = new XFaceCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFace::~XFace()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XSkinWeights::XSkinWeights()
{
	value = new XSkinWeightsCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XSkinWeights::~XSkinWeights()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XMesh::XMesh()
{
	value = new XMeshCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XMesh::~XMesh()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFrame::XFrame()
{
	value = new XFrameCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFrame::~XFrame()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFileModelFrame::XFileModelFrame()
{
	value = new XFileModelFrameCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFileModelFrame::~XFileModelFrame()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::TemplateRange::TemplateRange()
{
	value = new TemplateRangeCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::TemplateRange::~TemplateRange()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::XFile()
{
	value = new XFileCRT();
}

template<typename CharaType>
ChCpp::ModelLoader::XFile<CharaType>::~XFile()
{
	delete value;
}

template<typename CharaType>
void ChCpp::ModelLoader::XFile<CharaType>::CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)
{
	if (_filePath.size() <= 0)return;

	std::basic_string<CharaType> text;
	{
		ValueIns().loadFileName = _filePath;

		ChCpp::File<CharaType> files;

		files.FileOpen(_filePath);

		text = files.FileReadText();

		files.FileClose();

		if (text.length() <= 0)
		{
			return;
		}
	}

	if (text.find(XFileTag::GetXFilePrefixTag<CharaType>()) != 0)return;

	size_t textPos = text.find(XFileTag::GetXFilePrefixTag<CharaType>());

	{
		std::basic_string<CharaType> tmp = XFileTag::GetTemplateTag<CharaType>();
		tmp += XFileTag::GetFrameTag<CharaType>();
		size_t tmpLen = text.find(tmp, textPos);

		if (tmpLen != tmp.npos) {
			textPos = tmpLen;
			textPos += tmp.length();
		}
	}

	size_t tmpLen = text.find(XFileTag::GetFrameTag<CharaType>(), textPos);
	if (tmpLen == text.npos)return;

	tmpLen = text.find(ChStd::GetEndBraceChara<CharaType>(), tmpLen);
	if (tmpLen == text.npos)return;

	ChPtr::Shared<TemplateRange> templates = ChPtr::Make_S<TemplateRange>();

	LoadToTemplates(templates, textPos, text);

	auto xModel = ChPtr::Make_S<XFileModelFrame>();

	for (auto&& tmp : templates->ValueIns().nest)
	{
		SetFrame(xModel->ValueIns().modelData, tmp, text);

		SetMesh(xModel->ValueIns().modelData, tmp, text);
	}

	if (exceptionFlg)return;

	ChCpp::ModelLoaderBase<CharaType>::Init();

	ValueIns().loadFilePath = ChCpp::ModelLoaderBase<CharaType>::GetRoutePath(ValueIns().loadFileName);

	_model->SetModelName(_filePath);

	XFrameToChFrame(_model, xModel->ValueIns().modelData);

	ChCpp::ModelLoaderBase<CharaType>::SetMaxPos(*_model, ChCpp::ModelLoaderBase<CharaType>::maxPos);
	ChCpp::ModelLoaderBase<CharaType>::SetMinPos(*_model, ChCpp::ModelLoaderBase<CharaType>::minPos);
	ChCpp::ModelLoaderBase<CharaType>::SetCenterPos(*_model, ChCpp::ModelLoaderBase<CharaType>::CreateCenterPos(ChCpp::ModelLoaderBase<CharaType>::minPos, ChCpp::ModelLoaderBase<CharaType>::maxPos));
	ChCpp::ModelLoaderBase<CharaType>::SetBoxSize(*_model, ChCpp::ModelLoaderBase<CharaType>::CreateBoxSize(ChCpp::ModelLoaderBase<CharaType>::minPos, ChCpp::ModelLoaderBase<CharaType>::maxPos));

	_model->Create();
}

template<typename CharaType>
void ChCpp::ModelLoader::XFile<CharaType>::OutModelFile(const ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)
{

}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetFrame(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{
	if (exceptionFlg)return false;

	size_t framePos;

	std::basic_string<CharaType> tag = XFileTag::GetFrameTag<CharaType>();

	if (!IsTags(framePos, tag, _targetTemplate, _text))return false;



	framePos += tag.length();

	auto tmpFrame = ChPtr::Make_S<XFrame>();

	tmpFrame->ValueIns().fName = _text.substr(framePos, _targetTemplate->begin - framePos);

	tmpFrame->ValueIns().fName = ChStr::RemoveToWhiteSpaceChars(tmpFrame->ValueIns().fName);

	for (auto&& tmp : _targetTemplate->ValueIns().nest)
	{
		if (SetFremeTransformMatrix(tmpFrame, tmp, _text)) continue;

		{
			ChPtr::Shared<XFrame> obj = nullptr;

			if (SetFrame(obj, tmp, _text))
			{

				tmpFrame->ValueIns().next.push_back(obj);

				continue;
			}
		}

		if (SetMesh(tmpFrame, tmp, _text)) continue;
	}

	_frames = tmpFrame;

	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetFremeTransformMatrix(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetFrameTransformMatrixTag<CharaType>(), _targetTemplate, _text))return false;

	std::basic_string<CharaType> argText = ChStd::GetSemiColonChara<CharaType>();
	argText += ChStd::GetSemiColonChara<CharaType>();
	std::basic_string<CharaType> useText;

	{
		size_t textLen = _targetTemplate->end - _targetTemplate->begin - 1;

		useText = _text.substr(_targetTemplate->begin + 1, textLen);
	}

	_frames->frameMatrix.Deserialize<CharaType>(useText, 0, ChStd::GetCommaChara<CharaType>(), argText);
	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetMesh(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetMeshTag<CharaType>(), _targetTemplate, _text))return false;

	std::basic_string<CharaType> arrayFirstTag = ChStd::GetSemiColonChara<CharaType>();
	arrayFirstTag += ChStd::GetCommaChara<CharaType>();
	std::basic_string<CharaType> arraySeccondTag = ChStd::GetSemiColonChara<CharaType>();
	arraySeccondTag += ChStd::GetSemiColonChara<CharaType>();

	if (_frames == nullptr)
	{
		_frames = ChPtr::Make_S<XFrame>();
		_frames->ValueIns().fName = XFileTag::GetRootObjectName<CharaType>();
	}

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto mesh = ChPtr::Make_S<XMesh>();

	{
		auto values = GetArrayValues<XVECTOR>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

		for (auto&& poss : values)
		{
			auto vertex = ChPtr::Make_S<XVertex>();

			vertex->pos = poss->value;

			mesh->ValueIns().vertexList.push_back(vertex);
		}
	}

	tmpPos = _text.find(arraySeccondTag, tmpPos);
	tmpPos += 2;

	{
		auto values = GetArrayValues<XMESHFACE>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

		for (auto&& poss : values)
		{
			auto face = ChPtr::Make_S<XFace>();

			for (auto&& no : poss->value)
			{
				face->ValueIns().vertexNos.push_back(no);
			}

			mesh->ValueIns().faceList.push_back(face);

		}
	}

	_frames->ValueIns().mesh = mesh;

	for (auto&& tmp : _targetTemplate->ValueIns().nest)
	{

		if (SetMeshNormal(_frames, tmp, _text)) continue;

		if (SetMeshTextureCoords(_frames, tmp, _text)) continue;

		if (SetMeshMaterialList(_frames, tmp, _text)) continue;

		if (SetSkinWeights(_frames, tmp, _text)) continue;

	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetMeshNormal(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetNormalsTag<CharaType>(), _targetTemplate, _text))return false;

	std::basic_string<CharaType> arrayFirstTag = ChStd::GetSemiColonChara<CharaType>();
	arrayFirstTag += ChStd::GetCommaChara<CharaType>();
	std::basic_string<CharaType> arraySeccondTag = ChStd::GetSemiColonChara<CharaType>();
	arraySeccondTag += ChStd::GetSemiColonChara<CharaType>();

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto normals = GetArrayValues<XVECTOR>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

	tmpPos = _text.find(arraySeccondTag, tmpPos);
	tmpPos += 2;

	auto faces = GetArrayValues<XMESHFACE>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

	for (unsigned long i = 0; i < faces.size(); i++)
	{
		auto mesh = _frames->ValueIns().mesh->ValueIns().faceList[i];

		for (unsigned long j = 0; j < mesh->ValueIns().vertexNos.size(); j++)
		{

			_frames->ValueIns().mesh->ValueIns().vertexList[mesh->ValueIns().vertexNos[j]]->normal +=
				normals[faces[i]->value[j]]->value;

		}
	}

	for (auto&& vertex : _frames->ValueIns().mesh->ValueIns().vertexList)
	{
		if (vertex->normal.GetLen() == 1.00000000f)continue;
		vertex->normal.Normalize();
	}

	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetMeshTextureCoords(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetTextureCoordsTag<CharaType>(), _targetTemplate, _text))return false;

	std::basic_string<CharaType> arrayFirstTag = ChStd::GetSemiColonChara<CharaType>();
	arrayFirstTag += ChStd::GetCommaChara<CharaType>();
	std::basic_string<CharaType> arraySeccondTag = ChStd::GetSemiColonChara<CharaType>();
	arraySeccondTag += ChStd::GetSemiColonChara<CharaType>();

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto UVs = GetArrayValues<XCOODS2D>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

	tmpPos = _text.find(arraySeccondTag, tmpPos);
	tmpPos += 2;

	auto& vertexList = _frames->ValueIns().mesh->ValueIns().vertexList;

	for (unsigned long i = 0; i < vertexList.size(); i++)
	{
		vertexList[i]->uv = UVs[i]->value;
	}

	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetMeshMaterialList(
	ChPtr::Shared<XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::basic_string<CharaType>& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetMaterialListTag<CharaType>(), _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	tmpPos = _text.find(ChStd::GetSemiColonChara<CharaType>(), tmpPos);

	tmpPos += 1;

	auto mateNo = GetArrayValues<XDWORD>(_text, tmpPos, ChStd::GetCommaChara<CharaType>(), ChStd::GetSemiColonChara<CharaType>());

	auto& faces = _frames->ValueIns().mesh->ValueIns().faceList;

	for (unsigned long i = 0; i < faces.size(); i++)
	{
		faces[i]->mateNo = mateNo[i]->value;
	}

	for (auto&& tmp : _targetTemplate->ValueIns().nest)
	{
		SetMaterial(_frames, tmp, _text);
	}

	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetMaterial(
	ChPtr::Shared<XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::basic_string<CharaType>& _text)
{
	if (exceptionFlg)return false;

	size_t matePos;

	if (!IsTags(matePos, XFileTag::GetMaterialTag<CharaType>(), _targetTemplate, _text))return false;

	std::basic_string<CharaType> arrayTag = ChStd::GetSemiColonChara<CharaType>();
	arrayTag += ChStd::GetSemiColonChara<CharaType>();

	std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();

	std::basic_string<CharaType>tag = XFileTag::GetMaterialTag<CharaType>();
	matePos += tag.length();

	materialName = _text.substr(matePos, _targetTemplate->begin - matePos);

	materialName = ChStr::RemoveToWhiteSpaceChars(materialName);

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	ColorRGBA diffuse;

	{
		std::basic_string<CharaType> useText = ChStd::GetZeroChara<CharaType>();

		size_t tmpEnd = _text.find(arrayTag, tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		diffuse.Desirialise(useText, 0, arrayTag);
	}

	XFLOAT spePow;

	{
		std::basic_string<CharaType> useText = ChStd::GetZeroChara<CharaType>();

		size_t tmpEnd = _text.find(ChStd::GetSemiColonChara<CharaType>(), tmpPos);
		tmpEnd += 1;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		spePow.Desirialise(useText, 0, ChStd::GetSemiColonChara<CharaType>());
	}

	ColorRGB specular;

	{
		std::basic_string<CharaType> useText = ChStd::GetZeroChara<CharaType>();

		size_t tmpEnd = _text.find(arrayTag, tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		specular.Desirialise(useText, 0, arrayTag);
	}

	ColorRGB ambient;

	{
		std::basic_string<CharaType> useText = ChStd::GetZeroChara<CharaType>();

		size_t tmpEnd = _text.find(arrayTag, tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		ambient.Desirialise(useText, 0, arrayTag);
	}

	auto mate = ChPtr::Make_S<XMaterial>();

	mate->ValueIns().materialName = materialName;
	mate->diffuse = diffuse.value;
	mate->specularPower = spePow.value;
	mate->specularColor = specular.value;
	mate->ambient = ambient.value;

	for (auto&& tmp : _targetTemplate->ValueIns().nest)
	{

		if (!IsTags(XFileTag::GetTextureFileNameTag<CharaType>(), tmp, _text))continue;

		size_t start = _text.find(ChStd::GetDBQuotation<CharaType>(), tmp->begin);

		if (start >= tmp->end)continue;

		size_t end = _text.find(ChStd::GetDBQuotation<CharaType>(), start + 1);

		if (end >= tmp->end)continue;

		std::basic_string<CharaType> texturePath = _text.substr(start + 1, end - start - 1);

		mate->ValueIns().textureNameList.push_back(texturePath);

	}

	_frames->ValueIns().mesh->ValueIns().materialList.push_back(mate);

	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::SetSkinWeights(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetSkinWeightsTag<CharaType>(), _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	std::basic_string<CharaType> argText = ChStd::GetDBQuotation<CharaType>();
	argText += ChStd::GetSemiColonChara<CharaType>();

	std::basic_string<CharaType> boneName;

	{
		size_t tmpStart = _text.find(ChStd::GetDBQuotation<CharaType>(), tmpPos);

		size_t tmpEnd = _text.find(argText, tmpPos);

		if (tmpStart > _targetTemplate->end
			|| tmpEnd > _targetTemplate->end)return true;


		boneName = _text.substr(tmpStart + 1, tmpEnd - tmpStart - 1);

		tmpPos = tmpEnd + 2;
	}

	tmpPos = _text.find(ChStd::GetSemiColonChara<CharaType>(), tmpPos);
	tmpPos += 1;


	auto vertexNo = GetArrayValuesNC<XDWORD>(_text, tmpPos, ChStd::GetCommaChara<CharaType>(), ChStd::GetSemiColonChara<CharaType>());

	tmpPos = _text.find(ChStd::GetSemiColonChara<CharaType>(), tmpPos);
	tmpPos += 1;

	auto weightPow = GetArrayValuesNC<XFLOAT>(_text, tmpPos, ChStd::GetCommaChara<CharaType>(), ChStd::GetSemiColonChara<CharaType>());

	tmpPos = _text.find(ChStd::GetSemiColonChara<CharaType>(), tmpPos);
	tmpPos += 1;

	ChLMat tmpOffMat;

	argText = ChStd::GetSemiColonChara<CharaType>();
	argText += ChStd::GetSemiColonChara<CharaType>();

	tmpOffMat.Deserialize<CharaType>(_text, tmpPos, ChStd::GetCommaChara<CharaType>(), argText);

	auto skinWeight = ChPtr::Make_S<XSkinWeights>();

	skinWeight->boneOffset = tmpOffMat;

	skinWeight->ValueIns().targetFrameName = boneName;

	{
		size_t weightingCount = vertexNo.size();

		if (weightingCount > weightPow.size())weightingCount = weightPow.size();

		for (unsigned long i = 0; i < weightingCount; i++)
		{
			skinWeight->ValueIns().weitPow[vertexNo[i]->value] = weightPow[i]->value;
		}
	}

	_frames->ValueIns().skinWeightDatas.push_back(skinWeight);

	return true;
}

template<typename CharaType>
bool ChCpp::ModelLoader::XFile<CharaType>::IsTags(
	size_t& _outTagPos,
	const std::basic_string<CharaType>& _TagName,
	const ChPtr::Shared<TemplateRange> _LookTemplate,
	const std::basic_string<CharaType>& _text)
{

	size_t checkStartPos
		= _text.rfind(ChStd::GetLFChara<CharaType>(), _LookTemplate->begin);


	if (checkStartPos == _text.npos)
	{
		exceptionFlg = true;
		return false;
	}

	std::basic_string<CharaType> tmp = _text.substr(
		checkStartPos
		, _LookTemplate->begin - checkStartPos);

	size_t checked = tmp.find(_TagName);

	if (checked == _text.npos)return false;

	_outTagPos = _text.find(_TagName, checkStartPos);

	return true;
}

template<typename CharaType>
void ChCpp::ModelLoader::XFile<CharaType>::LoadToTemplates(
	ChPtr::Shared<TemplateRange>& _templates,
	const size_t& _offset,
	const std::basic_string<CharaType>& _text)
{
	std::vector<size_t>templateTags[2];
	CharaType tags[] = { ChStd::GetStartBraceChara<CharaType>()[0],ChStd::GetEndBraceChara<CharaType>()[0] };

	for (size_t i = 0; i < 2; i++)
	{

		size_t offset = _offset;

		while (1)
		{
			offset = _text.find(tags[i], offset + 1);

			if (offset >= _text.npos)break;

			templateTags[i].push_back(offset);

		}
	}


	if (templateTags[0].size() != templateTags[1].size())
	{
		exceptionFlg = true;
		return;
	}


	size_t tempCount = templateTags[0].size();

	size_t beginCount = 0;
	size_t endCount = 0;

	_templates = ChPtr::Make_S<TemplateRange>();

	_templates->begin = 0;
	_templates->end = 0;

	while (1)
	{

		if (beginCount >= templateTags[0].size())
		{
			break;
		}

		SetToTemplate(
			_templates
			, beginCount
			, endCount
			, templateTags[0]
			, templateTags[1]);

	}



}

template<typename CharaType>
void ChCpp::ModelLoader::XFile<CharaType>::SetToTemplate(
	ChPtr::Shared<TemplateRange>& _tmp,
	size_t& _bCnt,
	size_t& _eCnt,
	const std::vector<size_t>& _sTemplateTags,
	const std::vector<size_t>& _eTemplateTags)
{

	if (_eCnt >= _eTemplateTags.size())
	{
		exceptionFlg = true;
		return;
	}

	auto tmp = ChPtr::Make_S<TemplateRange>();

	tmp->begin = _sTemplateTags[_bCnt];

	_tmp->ValueIns().nest.push_back(tmp);

	_bCnt++;

	while (1)
	{

		if (_bCnt >= _sTemplateTags.size())
		{

			tmp->end = _eTemplateTags[_eCnt];
			_eCnt++;
			break;
		}

		if (_sTemplateTags[_bCnt] > _eTemplateTags[_eCnt])
		{
			tmp->end = _eTemplateTags[_eCnt];
			_eCnt++;
			break;
		}

		SetToTemplate(
			tmp
			, _bCnt
			, _eCnt
			, _sTemplateTags
			, _eTemplateTags);


	}


}

template<typename CharaType>
void ChCpp::ModelLoader::XFile<CharaType>::XFrameToChFrame(
	ChPtr::Shared<FrameObject<CharaType>> _chFrame,
	const ChPtr::Shared<XFrame>& _xFrame)
{

	_chFrame->SetMyName(_xFrame->ValueIns().fName);

	_chFrame->SetFrameTransform(_xFrame->frameMatrix);

	_chFrame->GetDrawLHandMatrix();

	for (auto&& frame : _xFrame->ValueIns().next)
	{
		auto chFrame = ChPtr::Make_S<FrameObject<CharaType>>();

		_chFrame->SetChild(chFrame);

		XFrameToChFrame(chFrame, frame);

	}

	if (_xFrame->ValueIns().mesh == nullptr)return;

	std::map<unsigned long, unsigned long>summarizeVertex;

	auto mesh = _chFrame->SetComponent<FrameComponent<CharaType>>();
	auto& chVertexList = mesh->ValueIns().vertexList;
	//SetVertexList//
	{
		auto& xVertexList = _xFrame->ValueIns().mesh->ValueIns().vertexList;


		for (unsigned long i = 0; i < xVertexList.size(); i++)
		{
			bool lookFlg = false;
			ChPtr::Shared<Ch3D::SavePolyVertex> chVertex = nullptr;

			for (unsigned long j = 0; j < chVertexList.size(); j++)
			{

				if (chVertexList[j]->pos != xVertexList[i]->pos)continue;

				summarizeVertex[i] = j;

				chVertex = chVertexList[summarizeVertex[i]];

				chVertex->normal += xVertexList[i]->normal;
				lookFlg = true;

				break;

			}

			if (lookFlg)continue;

			summarizeVertex[i] = chVertexList.size();

			chVertex = ChPtr::Make_S<Ch3D::SavePolyVertex>();

			chVertex->pos = xVertexList[i]->pos;
			chVertex->normal = xVertexList[i]->normal;

			chVertexList.push_back(chVertex);

			mesh->maxPos = ChCpp::ModelLoaderBase<CharaType>::TestMaxPos(mesh->maxPos, chVertex->pos);
			mesh->minPos = ChCpp::ModelLoaderBase<CharaType>::TestMinPos(mesh->minPos, chVertex->pos);

		}

		for (auto&& chVertex : chVertexList)
		{
			chVertex->normal.Normalize();
		}

		for (unsigned long i = 0; i < _xFrame->ValueIns().skinWeightDatas.size() && i < maxBoneNum; i++)
		{
			auto&& skinWeight = _xFrame->ValueIns().skinWeightDatas[i];
			for (unsigned long j = 0; j < chVertexList.size(); j++)
			{
				auto&& chVertex = *chVertexList[j];
				auto weitPow = skinWeight->ValueIns().weitPow.find(j);

				chVertex.ValueIns().blendPow.push_back(weitPow == skinWeight->ValueIns().weitPow.end() ? 0.0f : (*weitPow).second);
			}
			auto boneData = ChPtr::Make_S<ChCpp::TargetBoneData<CharaType>>();
			boneData->ValueIns().boneObjectName = skinWeight->ValueIns().targetFrameName;
			boneData->boneOffset = skinWeight->boneOffset;
			mesh->ValueIns().boneDatas.push_back(boneData);
		};

		mesh->centerPos = ChCpp::ModelLoaderBase<CharaType>::CreateCenterPos(mesh->minPos, mesh->maxPos);
		mesh->boxSize = ChCpp::ModelLoaderBase<CharaType>::CreateBoxSize(mesh->minPos, mesh->maxPos);

	}

	//SetFaceList//
	{
		auto& xVertexList = _xFrame->ValueIns().mesh->ValueIns().vertexList;

		auto& xFaceList = _xFrame->ValueIns().mesh->ValueIns().faceList;

		auto& chFaceList = mesh->ValueIns().primitives;

		for (auto&& xFace : xFaceList)
		{

			auto chFace = ChPtr::Make_S<Ch3D::Primitive>();

			for (unsigned long i = 0; i < xFace->ValueIns().vertexNos.size(); i++)
			{

				auto chVertexData = ChPtr::Make_S<Ch3D::SavePolyData>();

				unsigned long VertexNo = summarizeVertex[xFace->ValueIns().vertexNos[i]];

				chVertexData->vertexNo = VertexNo;
				chVertexData->uv = xVertexList[xFace->ValueIns().vertexNos[i]]->uv;
				chFace->faceNormal += chVertexList[VertexNo]->normal;

				chFace->ValueIns().vertexData.push_back(chVertexData);
			}
			chFace->faceNormal.Normalize();
			chFace->mateNo = xFace->mateNo;
			chFaceList.push_back(chFace);
		}


	}

	//SetMaterial//

	{
		auto& chMateList = mesh->ValueIns().materialList;
		auto& chMateNos = mesh->ValueIns().mateNames;

		unsigned long i = 0;

		for (auto&& xMate : _xFrame->ValueIns().mesh->ValueIns().materialList)
		{
			auto chMate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

			chMate->mate.diffuse = xMate->diffuse;
			chMate->ValueIns().mateName = xMate->ValueIns().materialName;
			chMate->mate.specularColor = xMate->specularColor;
			chMate->mate.specularPower = xMate->specularPower;
			chMate->mate.ambient = xMate->ambient.GetLen() / 4.0f;

			for (unsigned long j = 0; j < xMate->ValueIns().textureNameList.size(); j++)
			{
				if (j > ChStd::EnumCast(Ch3D::TextureType::Metallic))break;
				chMate->ValueIns().textures[static_cast<Ch3D::TextureType>(j)] =
					ValueIns().loadFilePath + xMate->ValueIns().textureNameList[j];

			}

			chMateNos[chMate->ValueIns().mateName] = i;

			chMateList.push_back(chMate);

			i++;

		}

		if (chMateList.empty())
		{

			auto chMate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

			chMate->mate.diffuse = ChVec4(1.0f);
			chMate->ValueIns().mateName = XFileTag::GetTmpMaterialName<CharaType>();
			chMate->mate.specularColor = ChVec3(1.0f);
			chMate->mate.specularPower = 0.3f;
			chMate->mate.ambient = ChVec4(0.3f);

			chMateNos[chMate->ValueIns().mateName] = 0;

			chMateList.push_back(chMate);

		}

	}

	ChVec3 tmpMaxPos = _chFrame->GetDrawLHandMatrix().Transform(mesh->maxPos);
	ChVec3 tmpMinPos = _chFrame->GetDrawLHandMatrix().Transform(mesh->minPos);

	ChCpp::ModelLoaderBase<CharaType>::maxPos = ChCpp::ModelLoaderBase<CharaType>::TestMaxPos(tmpMaxPos, ChCpp::ModelLoaderBase<CharaType>::maxPos);
	ChCpp::ModelLoaderBase<CharaType>::minPos = ChCpp::ModelLoaderBase<CharaType>::TestMinPos(tmpMaxPos, ChCpp::ModelLoaderBase<CharaType>::minPos);

	ChCpp::ModelLoaderBase<CharaType>::maxPos = ChCpp::ModelLoaderBase<CharaType>::TestMaxPos(tmpMinPos, ChCpp::ModelLoaderBase<CharaType>::maxPos);
	ChCpp::ModelLoaderBase<CharaType>::minPos = ChCpp::ModelLoaderBase<CharaType>::TestMinPos(tmpMinPos, ChCpp::ModelLoaderBase<CharaType>::minPos);
}



#endif

#endif