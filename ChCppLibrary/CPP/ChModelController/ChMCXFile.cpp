
#include"ChMCXFile.h"

#ifndef	CH_LM_XFILE_TAG_XFILE_PREFIX_FUNCTION
#define	CH_LM_XFILE_TAG_XFILE_PREFIX_FUNCTION(type) CH_NUMBER_FUNCTION(GetXFilePrefixTag, type)
#endif

#ifndef	CH_LM_XFILE_TAG_TEMPLATE_FUNCTION
#define	CH_LM_XFILE_TAG_TEMPLATE_FUNCTION(type) CH_NUMBER_FUNCTION(GetTemplateTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_FRAME_FUNCTION
#define	CH_LM_XFILE_TAG_FRAME_FUNCTION(type) CH_NUMBER_FUNCTION(GetFrameTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_FRAME_TRANSFORM_MATRIX_FUNCTION
#define	CH_LM_XFILE_TAG_FRAME_TRANSFORM_MATRIX_FUNCTION(type) CH_NUMBER_FUNCTION(GetFrameTransformMatrixTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_MESH_FUNCTION
#define	CH_LM_XFILE_TAG_MESH_FUNCTION(type) CH_NUMBER_FUNCTION(GetMeshTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_NORMALS_FUNCTION
#define	CH_LM_XFILE_TAG_NORMALS_FUNCTION(type) CH_NUMBER_FUNCTION(GetNormalsTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_MATERIAL_LIST_FUNCTION
#define	CH_LM_XFILE_TAG_MATERIAL_LIST_FUNCTION(type) CH_NUMBER_FUNCTION(GetMaterialListTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_MATERIAL_FUNCTION
#define	CH_LM_XFILE_TAG_MATERIAL_FUNCTION(type) CH_NUMBER_FUNCTION(GetMaterialTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_SKIN_WEIGHTS_FUNCTION
#define	CH_LM_XFILE_TAG_SKIN_WEIGHTS_FUNCTION(type) CH_NUMBER_FUNCTION(GetSkinWeightsTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_TEXTURE_COORDS_FUNCTION
#define	CH_LM_XFILE_TAG_TEXTURE_COORDS_FUNCTION(type) CH_NUMBER_FUNCTION(GetTextureCoordsTag,type)
#endif

#ifndef	CH_LM_XFILE_TAG_TEXTUER_FILE_NAME_FUNCTION
#define	CH_LM_XFILE_TAG_TEXTUER_FILE_NAME_FUNCTION(type) CH_NUMBER_FUNCTION(GetTextureFileNameTag,type)
#endif


#ifndef CH_LM_XFILE_ROOT_OBJECT_NAME_FUNCTION
#define CH_LM_XFILE_ROOT_OBJECT_NAME_FUNCTION(type) CH_NUMBER_FUNCTION(GetRootObjectName,type)
#endif

#ifndef CH_LM_XFILE_TMP_MATERIAL_NAME_FUNCTION
#define CH_LM_XFILE_TMP_MATERIAL_NAME_FUNCTION(type) CH_NUMBER_FUNCTION(GetTmpMaterialName,type)
#endif

namespace ChCpp
{
	namespace ModelController
	{
		namespace XFileTag
		{
			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_XFILE_PREFIX_FUNCTION, "xof");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_TEMPLATE_FUNCTION, "template");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_FRAME_FUNCTION, "Frame");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_FRAME_TRANSFORM_MATRIX_FUNCTION, "FrameTransformMatrix");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_MESH_FUNCTION, "Mesh");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_NORMALS_FUNCTION, "MeshNormals");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_MATERIAL_LIST_FUNCTION, "MeshMaterialList");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_MATERIAL_FUNCTION, "Material");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_SKIN_WEIGHTS_FUNCTION, "SkinWeights");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_TEXTURE_COORDS_FUNCTION, "MeshTextureCoords");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TAG_TEXTUER_FILE_NAME_FUNCTION, "TextureFilename");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_ROOT_OBJECT_NAME_FUNCTION, "Root");

			CH_TO_NUMBER_FUNCTION(CH_LM_XFILE_TMP_MATERIAL_NAME_FUNCTION, "tmp Material");
		}
	}
}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::LoadModel(const std::basic_string<CharaType>& _filePath)
{
	if (_filePath.size() <= 0)return;

	std::basic_string<CharaType> text;
	{
		loadFileName = _filePath;

		ChCpp::CharFile files;

		files.FileOpen(_filePath, false);

		text = ChCpp::GetConvertText<CharaType>(files.FileRead());
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

	auto&& tmpXModel = ChPtr::Make_S<XFileModelFrame>();

	for (auto&& tmp : templates->nest)
	{
		SetFrame(tmpXModel->modelData, tmp, text);

		SetMesh(tmpXModel->modelData, tmp, text);
	}

	if (exceptionFlg)return;

	xModel = tmpXModel;
}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::OutModel(const std::basic_string<CharaType>& _filePath)
{

}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model)
{
	if (_model == nullptr)return;
	if (xModel == nullptr)return;

	ChCpp::ModelControllerBase<CharaType>::Init();

	loadFilePath = ChCpp::ModelControllerBase<CharaType>::GetRoutePath(loadFileName);

	_model->SetModelName(loadFileName);

	XFrameToChFrame(_model, xModel->modelData);

	ChCpp::ModelControllerBase<CharaType>::SetMaxPos(*_model, ChCpp::ModelControllerBase<CharaType>::maxPos);
	ChCpp::ModelControllerBase<CharaType>::SetMinPos(*_model, ChCpp::ModelControllerBase<CharaType>::minPos);
	ChCpp::ModelControllerBase<CharaType>::SetCenterPos(*_model, ChCpp::ModelControllerBase<CharaType>::CreateCenterPos(ChCpp::ModelControllerBase<CharaType>::minPos, ChCpp::ModelControllerBase<CharaType>::maxPos));
	ChCpp::ModelControllerBase<CharaType>::SetBoxSize(*_model, ChCpp::ModelControllerBase<CharaType>::CreateBoxSize(ChCpp::ModelControllerBase<CharaType>::minPos, ChCpp::ModelControllerBase<CharaType>::maxPos));

	_model->Create();
}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::SetModel(const ChPtr::Shared<ModelObject<CharaType>> _model)
{

}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetFrame(
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

	tmpFrame->fName = _text.substr(framePos, _targetTemplate->begin - framePos);

	tmpFrame->fName = ChStr::RemoveToWhiteSpaceChars(tmpFrame->fName);

	for (auto&& tmp : _targetTemplate->nest)
	{
		if (SetFremeTransformMatrix(tmpFrame, tmp, _text)) continue;

		{
			ChPtr::Shared<XFrame> obj = nullptr;

			if (SetFrame(obj, tmp, _text))
			{

				tmpFrame->next.push_back(obj);

				continue;
			}
		}

		if (SetMesh(tmpFrame, tmp, _text)) continue;
	}

	_frames = tmpFrame;

	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetFremeTransformMatrix(
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

	_frames->frameMatrix.template Deserialize<CharaType>(useText, 0, ChStd::GetCommaChara<CharaType>(), argText);
	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetMesh(
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
		_frames->fName = XFileTag::GetRootObjectName<CharaType>();
	}

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto&& mesh = ChPtr::Make_S<XMesh>();

	{
		auto values = GetArrayValues<XVECTOR>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

		for (auto&& poss : values)
		{
			auto vertex = ChPtr::Make_S<XVertex>();

			vertex->pos = poss->value;

			mesh->vertexList.push_back(vertex);
		}
	}

	tmpPos = _text.find(arraySeccondTag, tmpPos);
	tmpPos += 2;

	{
		auto&& values = GetArrayValues<XMESHFACE>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

		for (auto&& poss : values)
		{
			auto face = ChPtr::Make_S<XFace>();

			for (auto&& no : poss->value)
			{
				face->vertexNos.push_back(no);
			}

			mesh->faceList.push_back(face);

		}
	}

	_frames->mesh = mesh;

	for (auto&& tmp : _targetTemplate->nest)
	{

		if (SetMeshNormal(_frames, tmp, _text)) continue;

		if (SetMeshTextureCoords(_frames, tmp, _text)) continue;

		if (SetMeshMaterialList(_frames, tmp, _text)) continue;

		if (SetSkinWeights(_frames, tmp, _text)) continue;

	}
	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetMeshNormal(
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
		auto mesh = _frames->mesh->faceList[i];

		for (unsigned long j = 0; j < mesh->vertexNos.size(); j++)
		{

			_frames->mesh->vertexList[mesh->vertexNos[j]]->normal +=
				normals[faces[i]->value[j]]->value;

		}
	}

	for (auto&& vertex : _frames->mesh->vertexList)
	{
		if (vertex->normal.GetLen() == 1.00000000f)continue;
		vertex->normal.Normalize();
	}

	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetMeshTextureCoords(
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

	auto&& UVs = GetArrayValues<XCOODS2D>(_text, tmpPos, arrayFirstTag, arraySeccondTag);

	tmpPos = _text.find(arraySeccondTag, tmpPos);
	tmpPos += 2;

	auto& vertexList = _frames->mesh->vertexList;

	for (unsigned long i = 0; i < vertexList.size(); i++)
	{
		vertexList[i]->uv = UVs[i]->value;
	}

	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetMeshMaterialList(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(XFileTag::GetMaterialListTag<CharaType>(), _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	tmpPos = _text.find(ChStd::GetSemiColonChara<CharaType>(), tmpPos);

	tmpPos += 1;

	auto&& mateNo = GetArrayValues<XDWORD>(_text, tmpPos, ChStd::GetCommaChara<CharaType>(), ChStd::GetSemiColonChara<CharaType>());

	auto& faces = _frames->mesh->faceList;

	for (unsigned long i = 0; i < faces.size(); i++)
	{
		faces[i]->mateNo = mateNo[i]->value;
	}

	for (auto&& tmp : _targetTemplate->nest)
	{
		SetMaterial(_frames, tmp, _text);
	}

	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetMaterial(
	ChPtr::Shared<XFrame>& _frames,
	const ChPtr::Shared<TemplateRange>& _targetTemplate,
	const std::basic_string<CharaType>& _text)
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

	mate->materialName = materialName;
	mate->diffuse = diffuse.value;
	mate->specularPower = spePow.value;
	mate->specularColor = specular.value;
	mate->ambient = ambient.value;

	for (auto&& tmp : _targetTemplate->nest)
	{

		if (!IsTags(XFileTag::GetTextureFileNameTag<CharaType>(), tmp, _text))continue;

		size_t start = _text.find(ChStd::GetDBQuotation<CharaType>(), tmp->begin);

		if (start >= tmp->end)continue;

		size_t end = _text.find(ChStd::GetDBQuotation<CharaType>(), start + 1);

		if (end >= tmp->end)continue;

		std::basic_string<CharaType> texturePath = _text.substr(start + 1, end - start - 1);

		mate->textureNameList.push_back(texturePath);

	}

	_frames->mesh->materialList.push_back(mate);

	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::SetSkinWeights(
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

	skinWeight->targetFrameName = boneName;

	{
		size_t weightingCount = vertexNo.size();

		if (weightingCount > weightPow.size())weightingCount = weightPow.size();

		for (unsigned long i = 0; i < weightingCount; i++)
		{
			skinWeight->weitPow[vertexNo[i]->value] = weightPow[i]->value;
		}
	}

	_frames->skinWeightDatas.push_back(skinWeight);

	return true;
}

template<typename CharaType>
bool ChCpp::ModelController::XFile<CharaType>::IsTags(
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
		checkStartPos,
		_LookTemplate->begin - checkStartPos);

	size_t checked = tmp.find(_TagName);

	if (checked == _text.npos)return false;

	_outTagPos = _text.find(_TagName, checkStartPos);

	return true;
}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::LoadToTemplates(
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
			_templates,
			beginCount,
			endCount,
			templateTags[0],
			templateTags[1]);
	}

}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::SetToTemplate(
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

	_tmp->nest.push_back(tmp);

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
			tmp,
			_bCnt,
			_eCnt,
			_sTemplateTags,
			_eTemplateTags);

	}
}

template<typename CharaType>
void ChCpp::ModelController::XFile<CharaType>::XFrameToChFrame(
	ChPtr::Shared<FrameObject<CharaType>> _chFrame,
	const ChPtr::Shared<XFrame>& _xFrame)
{

	_chFrame->SetMyName(_xFrame->fName);

	bool isNotHaveVertex = _xFrame->mesh == nullptr;

	_chFrame->SetFrameTransform(_xFrame->frameMatrix);

	_chFrame->GetDrawLHandMatrix();

	for (auto&& frame : _xFrame->next)
	{
		auto chFrame = ChPtr::Make_S<FrameObject<CharaType>>();

		_chFrame->SetChild(chFrame);

		XFrameToChFrame(chFrame, frame);
	}

	if (_xFrame->mesh == nullptr)return;

	std::map<size_t, size_t>summarizeVertex;

	auto&& mesh = _chFrame->template SetComponent<FrameComponent<CharaType>>();
	auto&& chVertexList = mesh->vertexList;
	//SetVertexList//
	{
		auto& xVertexList = _xFrame->mesh->vertexList;


		for (size_t i = 0; i < xVertexList.size(); i++)
		{
			bool lookFlg = false;
			ChPtr::Shared<Ch3D::SavePolyVertex> chVertex = nullptr;

			for (size_t j = 0; j < chVertexList.size(); j++)
			{
				if (chVertexList[j]->pos != xVertexList[i]->pos)continue;

				summarizeVertex[i] = j;

				chVertex = chVertexList[j];

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

			mesh->maxPos = ChCpp::ModelControllerBase<CharaType>::TestMaxPos(mesh->maxPos, chVertex->pos);
			mesh->minPos = ChCpp::ModelControllerBase<CharaType>::TestMinPos(mesh->minPos, chVertex->pos);

		}

		for (auto&& chVertex : chVertexList)
		{
			chVertex->normal.Normalize();
		}

		for (unsigned long i = 0; i < _xFrame->skinWeightDatas.size() && i < maxBoneNum; i++)
		{
			auto&& skinWeight = _xFrame->skinWeightDatas[i];
			for (unsigned long j = 0; j < chVertexList.size(); j++)
			{
				auto&& chVertex = *chVertexList[j];
				auto weitPow = skinWeight->weitPow.find(j);

				chVertex.blendPow.push_back(weitPow == skinWeight->weitPow.end() ? 0.0f : (*weitPow).second);
			}
			auto boneData = ChPtr::Make_S<ChCpp::TargetBoneData<CharaType>>();
			boneData->boneObjectName = skinWeight->targetFrameName;
			boneData->boneOffset = skinWeight->boneOffset;
			mesh->boneDatas.push_back(boneData);
		};

		mesh->centerPos = ChCpp::ModelControllerBase<CharaType>::CreateCenterPos(mesh->minPos, mesh->maxPos);
		mesh->boxSize = ChCpp::ModelControllerBase<CharaType>::CreateBoxSize(mesh->minPos, mesh->maxPos);

	}

	//SetFaceList//
	{
		auto& xVertexList = _xFrame->mesh->vertexList;

		auto& xFaceList = _xFrame->mesh->faceList;

		auto& chFaceList = mesh->primitives;

		for (auto&& xFace : xFaceList)
		{

			auto chFace = ChPtr::Make_S<Ch3D::Primitive>();

			for (size_t i = 0; i < xFace->vertexNos.size(); i++)
			{

				auto chVertexData = ChPtr::Make_S<Ch3D::SavePolyData>();

				size_t VertexNo = summarizeVertex[xFace->vertexNos[i]];

				chVertexData->vertexNo = static_cast<unsigned long>(VertexNo);
				chVertexData->uv = xVertexList[xFace->vertexNos[i]]->uv;
				chFace->faceNormal += chVertexList[VertexNo]->normal;

				chFace->vertexData.push_back(chVertexData);
			}
			chFace->faceNormal.Normalize();
			chFace->mateNo = xFace->mateNo;
			chFaceList.push_back(chFace);
		}
	}

	//SetMaterial//

	{
		auto& chMateList = mesh->materialList;
		auto& chMateNos = mesh->mateNames;

		size_t i = 0;

		for (auto&& xMate : _xFrame->mesh->materialList)
		{
			auto chMate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

			chMate->mate.diffuse = xMate->diffuse;
			chMate->mateName = xMate->materialName;
			chMate->mate.specularColor = xMate->specularColor;
			chMate->mate.specularPower = xMate->specularPower;
			chMate->mate.ambient = xMate->ambient.GetLen() / 4.0f;

			for (size_t j = 0; j < xMate->textureNameList.size(); j++)
			{
				if (j > ChStd::EnumCast(Ch3D::TextureType::Metallic))break;
				chMate->textures[static_cast<Ch3D::TextureType>(j)] =
					loadFilePath + xMate->textureNameList[j];
			}

			chMateNos[chMate->mateName] = i;

			chMateList.push_back(chMate);

			i++;
		}

		if (chMateList.empty())
		{
			auto chMate = ChPtr::Make_S<Ch3D::MaterialData<CharaType>>();

			chMate->mate.diffuse = ChVec4(1.0f);
			chMate->mateName = XFileTag::GetTmpMaterialName<CharaType>();
			chMate->mate.specularColor = ChVec3(1.0f);
			chMate->mate.specularPower = 0.3f;
			chMate->mate.ambient = ChVec4(0.3f);

			chMateNos[chMate->mateName] = 0;

			chMateList.push_back(chMate);
		}
	}

	ChVec3 tmpMaxPos = _chFrame->GetDrawLHandMatrix().Transform(mesh->maxPos);
	ChVec3 tmpMinPos = _chFrame->GetDrawLHandMatrix().Transform(mesh->minPos);

	ChCpp::ModelControllerBase<CharaType>::maxPos = ChCpp::ModelControllerBase<CharaType>::TestMaxPos(tmpMaxPos, ChCpp::ModelControllerBase<CharaType>::maxPos);
	ChCpp::ModelControllerBase<CharaType>::minPos = ChCpp::ModelControllerBase<CharaType>::TestMinPos(tmpMaxPos, ChCpp::ModelControllerBase<CharaType>::minPos);

	ChCpp::ModelControllerBase<CharaType>::maxPos = ChCpp::ModelControllerBase<CharaType>::TestMaxPos(tmpMinPos, ChCpp::ModelControllerBase<CharaType>::maxPos);
	ChCpp::ModelControllerBase<CharaType>::minPos = ChCpp::ModelControllerBase<CharaType>::TestMinPos(tmpMinPos, ChCpp::ModelControllerBase<CharaType>::minPos);
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::ModelController::XFile);
