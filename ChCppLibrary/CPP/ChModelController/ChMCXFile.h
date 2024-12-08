#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#include<vector>
#include<map>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChStr.h"

#include"ChModelControllerBase.h"

#include"../ChFile/ChFile.h"
#include"../ChTextObject/ChTextObject.h"

#ifndef CH_LM_XFILE_BASE_TYPE_CLASS_CHILD
#define CH_LM_XFILE_BASE_TYPE_CLASS_CHILD(_StructName,_BaseType,_BaseTypeInitialize)\
struct _StructName : public BaseType{\
	void Desirialise(\
		const std::basic_string<CharaType>& _text,\
		const size_t& _start,\
		const std::basic_string<CharaType>& _endChar)override{\
		size_t tmp = _text.find(_endChar, _start);\
		value = ChStr::GetNumFromText<_BaseType>(_text, _start, tmp);}\
\
	std::basic_string<CharaType> Serialise()override{\
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
	std::basic_string<CharaType> Serialise()override{\
		return ChStd::GetZeroChara<CharaType>();\
	}\
	_BaseType value = _BaseTypeInitialize;\
};
#endif

namespace ChCpp
{
	namespace ModelController
	{
		namespace XFileTag
		{
			//"xof"//
			CH_NUMBER_FUNCTION_BASE(GetXFilePrefixTag);

			//"template"//
			CH_NUMBER_FUNCTION_BASE(GetTemplateTag);

			//"Frame"//
			CH_NUMBER_FUNCTION_BASE(GetFrameTag);

			//"FrameTransformMatrix"//
			CH_NUMBER_FUNCTION_BASE(GetFrameTransformMatrixTag);

			//"Mesh"//
			CH_NUMBER_FUNCTION_BASE(GetMeshTag);

			//"MeshNormals"//
			CH_NUMBER_FUNCTION_BASE(GetNormalsTag);

			//"MeshMaterialList"//
			CH_NUMBER_FUNCTION_BASE(GetMaterialListTag);

			//"Material"//
			CH_NUMBER_FUNCTION_BASE(GetMaterialTag);

			//"SkinWeights"//
			CH_NUMBER_FUNCTION_BASE(GetSkinWeightsTag);

			//"MeshTextureCoords"//
			CH_NUMBER_FUNCTION_BASE(GetTextureCoordsTag);

			//"TextureFilename"//
			CH_NUMBER_FUNCTION_BASE(GetTextureFileNameTag);

			//"Root"//
			CH_NUMBER_FUNCTION_BASE(GetRootObjectName);

			//"tmp Material"//
			CH_NUMBER_FUNCTION_BASE(GetTmpMaterialName);
		}

		template<typename CharaType>
		class XFile :public ModelControllerBase<CharaType>
		{
		public:

			struct XVertex :public Ch3D::PolyVertex
			{};

			struct XMaterial :public Ch3D::Material
			{
				std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();
				std::vector<std::basic_string<CharaType>>textureNameList;
			};

			struct XFace
			{
				unsigned long mateNo = 0;

				std::vector<unsigned long> vertexNos;
			};

			struct XSkinWeights
			{
				ChLMat boneOffset;
				std::basic_string<CharaType> targetFrameName = ChStd::GetZeroChara<CharaType>();
				std::map<unsigned long, float>weitPow;
			};

			struct XMesh
			{
				std::vector<ChPtr::Shared<XVertex>>vertexList;
				std::vector<ChPtr::Shared<XMaterial>>materialList;
				std::vector<ChPtr::Shared<XFace>>faceList;
			};

			struct XFrame
			{
				ChLMat frameMatrix;

				std::basic_string<CharaType> fName = ChStd::GetZeroChara<CharaType>();
				ChPtr::Shared<XMesh> mesh;
				std::vector<ChPtr::Shared<XFrame>>next;
				std::vector<ChPtr::Shared<XSkinWeights>>skinWeightDatas;
			};

			struct BaseType
			{
				virtual void Desirialise(
					const std::basic_string<CharaType>& _Text,
					const size_t& _Start,
					const std::basic_string<CharaType>& _EndChar) = 0;

				virtual std::basic_string<CharaType> Serialise() = 0;
			};

			struct XFileModelFrame
			{
				ChPtr::Shared<XFrame> modelData = nullptr;
				std::basic_string<CharaType> modelName = ChStd::GetZeroChara<CharaType>();
			};

			struct TemplateRange
			{
				size_t begin = 0;
				size_t end = 0;

				std::vector<ChPtr::Shared<TemplateRange>> nest;
			};

		public:

			void LoadModel(const std::basic_string<CharaType>& _filePath)override;

			void OutModel(const std::basic_string<CharaType>& _filePath)override;

			void CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model)override;

			void SetModel(const ChPtr::Shared<ModelObject<CharaType>> _model)override;

		public:

			inline void SetMaxBoneNum(const unsigned long _boneNum) { maxBoneNum = _boneNum; }

		public:

			inline ChPtr::Weak<XFileModelFrame> GetXModel() { return xModel; }

		protected:

			//ChModel‚Ö•ÏŠ·//
			void XFrameToChFrame(
				ChPtr::Shared<FrameObject<CharaType>> _chFrame,
				const ChPtr::Shared<XFrame>& _xFrame);

		protected://SetFunction//

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
		public:

			inline const unsigned long GetMaxBoneNum() const { return maxBoneNum; }

		protected:

			template<class T>
			typename std::enable_if
				<std::is_base_of<BaseType, T>::value,
				std::vector<ChPtr::Shared<T>>>::type GetArrayValues(
					const std::basic_string<CharaType>& _text,
					const size_t& _startPos = 0,
					const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
					const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>()) {

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
				arrayCount = ChStr::GetNumFromText<unsigned long>(useText, useText.find(ChStd::GetLFChara<CharaType>()), tmpPos);

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
					const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>()) {

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

			protected://IsFunction//

				bool IsTags(
					size_t& _outTagPos,
					const std::basic_string<CharaType>& _tagName,
					const ChPtr::Shared<TemplateRange> _lookTemplate,
					const std::basic_string<CharaType>& _text);

				inline bool IsTags(
					const std::basic_string<CharaType>& _tagName,
					const ChPtr::Shared<TemplateRange> _lookTemplate,
					const std::basic_string<CharaType>& _text)
				{
					size_t tmp;

					return IsTags(tmp, _tagName, _lookTemplate, _text);
				}
			protected://TmplateCreate//

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

		public://XFileBaseTypes//

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

					arrayCount = ChStr::GetNumFromText<unsigned long>(useText, 0, tmpPos);

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

		protected://Member Value//

			bool exceptionFlg = false;

			unsigned long maxBoneNum = 16;
		
			std::basic_string<CharaType> loadFileName = ChStd::GetZeroChara<CharaType>();
			std::basic_string<CharaType> loadFilePath = ChStd::GetZeroChara<CharaType>();

			ChPtr::Shared<XFileModelFrame> xModel = nullptr;

		};
	}
}

#endif