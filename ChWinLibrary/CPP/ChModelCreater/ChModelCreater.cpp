#include"../../BaseIncluder/ChBase.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelCreater.h"
#include"ChCMXFileMesh.h"
#include"ChCMObjFileMesh.h"

void ChCpp::ModelCreater::Init(ModelObject* _model)
{
	oModel = _model;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelCreater::SetModel(ChPtr::Shared<ModelFrame> _models)
{
	oModel->model = _models;
}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::ModelCreater::GetRoutePath(const std::string& _filePath)
{

	if (_filePath.find("\\") == _filePath.find("/"))return "";

	std::string tmpPath = ChStr::StrReplase(_filePath, "\\", "/");

	unsigned long tmp = tmpPath.rfind("/");

	return tmpPath.substr(0, tmp + 1);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::CreateModel(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;

	std::string text;
	{

		ChFIO::File files;

		files.FileOpen(_filePath);

		text = files.FileRead();

		files.FileClose();

		if (text.length() <= 0)
		{
			return;
		}
	}

	if (text.find("xof") != 0)return;

	size_t textPos = text.find("xof");

	{
		std::string tmp = "template Frame";
		size_t tmpLen = text.find(tmp, textPos);

		if (tmpLen != tmp.npos) {
			textPos = tmpLen;
			textPos += tmp.length();
		}
	}

	size_t tmpLen = text.find("Frame", textPos);
	if (tmpLen == text.npos)return;

	tmpLen = text.find("}", tmpLen);
	if (tmpLen == text.npos)return;

	ChPtr::Shared<TemplateRange> templates = ChPtr::Make_S<TemplateRange>();

	LoadToTemplates(templates, textPos, text);

	auto xModel = ChPtr::Make_S<XFileModelFrame>();

	for (auto&& tmp : templates->nest)
	{

		SetFrame(xModel->modelData, tmp, text);

		SetMesh(xModel->modelData, tmp, text);

	}

	if (exceptionFlg)return;

	ChPtr::Shared<ModelFrame> outModels = nullptr;

	outModels = ChPtr::Make_S<ModelFrame>();

	outModels->modelName = _filePath;

	XFrameToChFrame(outModels->modelData, xModel->modelData);

	SetModel(outModels);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutModelFile(const std::string& _filePath)
{

}

/////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetFrame(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	size_t framePos;

	if (!IsTags(framePos, frameTags, _targetTemplate, _text))return false;

	framePos += frameTags.length();

	auto tmpFrame = ChPtr::Make_S<XFileModelFrame::XFrame>();

	tmpFrame->fName = _text.substr(framePos, _targetTemplate->begin - framePos);

	tmpFrame->fName = ChStr::RemoveToWhiteSpaceChars(tmpFrame->fName);

	for (auto&& tmp : _targetTemplate->nest)
	{
		if (SetFremeTransformMatrix(tmpFrame, tmp, _text)) continue;

		{
			ChPtr::Shared<XFileModelFrame::XFrame> obj = nullptr;

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

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetFremeTransformMatrix(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(frameTransformMatrixTags, _targetTemplate, _text))return false;

	std::string useText;

	{
		size_t textLen = _targetTemplate->end - _targetTemplate->begin - 1;

		useText = _text.substr(_targetTemplate->begin + 1, textLen);
	}

	_frames->frameMatrix.Deserialize(useText, 0, ",", ";;");

	return true;

}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMesh(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(meshTags, _targetTemplate, _text))return false;

	if (_frames == nullptr)
	{
		_frames = ChPtr::Make_S<XFileModelFrame::XFrame>();
		_frames->fName = "Root";
	}

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto mesh = ChPtr::Make_S<XFileModelFrame::XMesh>();

	{

		auto values = GetArrayValues<XVECTOR>(_text, tmpPos, ";,", ";;");

		for (auto&& poss : values)
		{
			auto vertex = ChPtr::Make_S<XFileModelFrame::XVertex>();

			vertex->pos = poss->value;

			mesh->vertexList.push_back(vertex);

		}

	}

	tmpPos = _text.find(";;", tmpPos);
	tmpPos += 2;

	{
		auto values = GetArrayValues<XMESHFACE>(_text, tmpPos, ";,", ";;");

		for (auto&& Poss : values)
		{
			auto face = ChPtr::Make_S<XFileModelFrame::XFace>();

			for (auto&& no : Poss->value)
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

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshNormal(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(normalTags, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto normals = GetArrayValues<XVECTOR>(_text, tmpPos, ";,", ";;");

	tmpPos = _text.find(";;", tmpPos);
	tmpPos += 2;

	auto faces = GetArrayValues<XMESHFACE>(_text, tmpPos, ";,", ";;");

	for (unsigned long i = 0; i < faces.size(); i++)
	{
		auto Mesh = _frames->mesh->faceList[i];

		for (unsigned long j = 0; j < Mesh->vertexNos.size(); j++)
		{

			_frames->mesh->vertexList[Mesh->vertexNos[j]]->normal +=
				normals[faces[i]->value[j]]->value;

		}
	}
	for (auto&& vertex : _frames->mesh->vertexList)
	{
		if (vertex->normal.Len() == 1.00000000f)continue;
		vertex->normal.Normalize();
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshTextureCoords(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(uvTags, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto UVs = GetArrayValues<XCOODS2D>(_text, tmpPos, ";,", ";;");

	tmpPos = _text.find(";;", tmpPos);
	tmpPos += 2;

	auto& vertexList = _frames->mesh->vertexList;

	for (unsigned long i = 0; i < vertexList.size(); i++)
	{
		vertexList[i]->uvPos = UVs[i]->value;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshMaterialList(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(materialListTags, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	tmpPos = _text.find(";", tmpPos);

	tmpPos += 1;

	auto mateNo = GetArrayValues<XDWORD>(_text, tmpPos, ",", ";;");

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

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMaterial(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	size_t matePos;

	if (!IsTags(matePos, materialTags, _targetTemplate, _text))return false;

	std::string materialName = "";

	matePos += materialTags.length();

	materialName = _text.substr(matePos, _targetTemplate->begin - matePos);

	materialName = ChStr::RemoveToWhiteSpaceChars(materialName);

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	ColorRGBA diffuse;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";;", tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		diffuse.Desirialise(useText, 0, ";;");
	}

	XFLOAT spePow;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";", tmpPos);
		tmpEnd += 1;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		spePow.Desirialise(useText, 0, ";");
	}

	ColorRGB specular;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";;", tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		specular.Desirialise(useText, 0, ";;");
	}

	ColorRGB ambient;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";;", tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		ambient.Desirialise(useText, 0, ";;");
	}

	auto mate = ChPtr::Make_S<XFileModelFrame::XMaterial>();

	mate->materialName = materialName;
	mate->diffuse = diffuse.value;
	mate->specularPower = spePow.value;
	mate->specular = specular.value;
	mate->ambient = ambient.value;

	for (auto&& tmp : _targetTemplate->nest)
	{

		if (!IsTags(textureFileNameTag, tmp, _text))continue;

		size_t start = _text.find("\"", tmp->begin);

		if (start >= tmp->end)continue;

		size_t end = _text.find("\"", start + 1);

		if (end >= tmp->end)continue;

		std::string texturePath = _text.substr(start + 1, end - start - 1);

		mate->textureNameList.push_back(texturePath);

	}

	_frames->mesh->materialList.push_back(mate);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetSkinWeights(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(skinWeightsTag, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	std::string boneName;

	{
		size_t tmpStart = _text.find("\"", tmpPos);

		size_t tmpEnd = _text.find("\";", tmpPos);

		if (tmpStart > _targetTemplate->end
			|| tmpEnd > _targetTemplate->end)return true;


		boneName = _text.substr(tmpStart + 1, tmpEnd - tmpStart - 1);

		tmpPos = tmpEnd + 2;
	}

	tmpPos = _text.find(";", tmpPos);
	tmpPos += 1;


	auto vertexNo = GetArrayValuesNC<XDWORD>(_text, tmpPos, ",", ";");

	tmpPos = _text.find(";", tmpPos);
	tmpPos += 1;

	auto weightPow = GetArrayValuesNC<XFLOAT>(_text, tmpPos, ",", ";");

	tmpPos = _text.find(";", tmpPos);
	tmpPos += 1;

	ChLMat tmpOffMat;

	tmpOffMat.Deserialize(_text, tmpPos, ",", ";;");

	auto skinWeight = ChPtr::Make_S<XFileModelFrame::XSkinWeights>();

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

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::IsTags(
	size_t& _outTagPos
	, const std::string& _TagName
	, const ChPtr::Shared<TemplateRange> _LookTemplate
	, const std::string& _text)
{

	size_t checkStartPos
		= _text.rfind("\n", _LookTemplate->begin);


	if (checkStartPos == _text.npos)
	{
		exceptionFlg = true;
		return false;
	}

	std::string tmp = _text.substr(
		checkStartPos
		, _LookTemplate->begin - checkStartPos);

	size_t checked = tmp.find(_TagName);

	if (checked == _text.npos)return false;

	_outTagPos = _text.find(_TagName, checkStartPos);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::LoadToTemplates(
	ChPtr::Shared<TemplateRange>& _templates
	, const size_t& _offset
	, const std::string& _text)
{
	std::vector<size_t>templateTags[2];
	char tags[] = { '{','}' };

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

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetToTemplate(
	ChPtr::Shared<TemplateRange>& _tmp
	, size_t& _bCnt
	, size_t& _eCnt
	, const std::vector<size_t>& _sTemplateTags
	, const std::vector<size_t>& _eTemplateTags)
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
			tmp
			, _bCnt
			, _eCnt
			, _sTemplateTags
			, _eTemplateTags);


	}


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::XFrameToChFrame(
	ChPtr::Shared<ModelFrame::Frame>& _chFrame
	, const ChPtr::Shared<XFileModelFrame::XFrame>& _xFrame)
{


	_chFrame = ChPtr::Make_S<ModelFrame::Frame>();

	_chFrame->baseMat = _xFrame->frameMatrix;
	_chFrame->myName = _xFrame->fName;


	for (auto&& frame : _xFrame->next)
	{
		ChPtr::Shared<ModelFrame::Frame> chFrame = nullptr;

		XFrameToChFrame(chFrame, frame);

		_chFrame->childFrames.push_back(chFrame);

		chFrame->parent = _chFrame;
	}

	std::map<unsigned long, unsigned long>summarizeVertex;

	auto mesh = ChPtr::Make_S<ModelFrame::Mesh>();

	if (_xFrame->mesh == nullptr)return;
	//SetVertexList//
	{
		auto& xVertexList = _xFrame->mesh->vertexList;

		auto& chVertexList = mesh->vertexList;

		for (unsigned long i = 0; i < xVertexList.size(); i++)
		{
			ChStd::Bool lookFlg = false;

			for (unsigned long j = 0; j < chVertexList.size(); j++)
			{

				if (chVertexList[j]->pos != xVertexList[i]->pos)continue;

				summarizeVertex[i] = j;

				chVertexList[j]->normal += xVertexList[i]->normal;

				lookFlg = true;

				break;

			}

			if (lookFlg)continue;


			summarizeVertex[i] = chVertexList.size();

			auto chVertex = ChPtr::Make_S<ModelFrame::VertexData>();

			chVertex->pos = xVertexList[i]->pos;
			chVertex->normal += chVertexList[i]->normal;

			chVertexList.push_back(chVertex);

		}

		for (auto&& chVertex : chVertexList)
		{
			chVertex->normal.Normalize();
		}

	}

	//SetFaceList//
	{
		auto& xVertexList = _xFrame->mesh->vertexList;

		auto& xFaceList = _xFrame->mesh->faceList;

		auto& chFaceList = mesh->faceList;

		for (auto&& xFace : xFaceList)
		{
			unsigned long counters[3];
			counters[0] = 0;
			counters[1] = 1;
			counters[2] = xFace->vertexNos.size() - 1;

			ChStd::Bool upperFlg = true;

			for (unsigned long i = 0; i < xFace->vertexNos.size() - 2; i++)
			{
				auto chFace = ChPtr::Make_S<ModelFrame::SurFace>();

				for (unsigned long j = 0; j < 3; j++)
				{

					auto chVertexData = ChPtr::Make_S<ModelFrame::SurFace::SurFaceVertex>();

					unsigned long VertexNo = summarizeVertex[xFace->vertexNos[counters[j]]];

					chVertexData->vertexNo = VertexNo;
					chVertexData->uvPos = xVertexList[xFace->vertexNos[counters[j]]]->uvPos;


					chFace->vertexData[j].uvPos = chVertexData->uvPos;
					chFace->vertexData[j].vertexNo = chVertexData->vertexNo;

					chFace->normal += xVertexList[xFace->vertexNos[counters[j]]]->normal;
				}

				chFace->normal.Normalize();

				if (upperFlg)
				{
					counters[0] = counters[1];
					counters[1] = counters[2] - 1;
				}
				else
				{
					counters[2] = counters[1];
					counters[1] = counters[0] + 1;
				}

				upperFlg = !upperFlg;

				chFace->materialNo = xFace->mateNo;

				chFaceList.push_back(chFace);
			}
		}


	}

	//SetMaterial//

	{
		auto& chMateList = mesh->materialList;
		auto& chMateNos = mesh->materialNo;

		unsigned long i = 0;

		for (auto&& xMate : _xFrame->mesh->materialList)
		{
			auto chMate = ChPtr::Make_S<ModelFrame::Material>();

			chMate->diffuse = xMate->diffuse;
			chMate->materialName = xMate->materialName;
			chMate->specular = xMate->specular;
			chMate->spePow = xMate->specularPower;
			chMate->ambientPow = xMate->ambient.Len() / 4.0f;

			for (unsigned long i = 0; i < xMate->textureNameList.size(); i++)
			{
				chMate->textureNames.push_back(xMate->textureNameList[i]);

				//switch (i)
				//{
				//case 0:ChMate->diffuseMap = XMate->TextureNameList[i]; break;
				//case 1:ChMate->NormalMap = XMate->TextureNameList[i]; break;
				//case 2:ChMate->AmbientMap = XMate->TextureNameList[i]; break;
				//case 3:ChMate->specularMap = XMate->TextureNameList[i]; break;
				//case 4:ChMate->specularPowMap = XMate->TextureNameList[i]; break;
				//case 5:ChMate->BumpMap = XMate->TextureNameList[i]; break;
				//case 6:ChMate->alphaMap = XMate->TextureNameList[i]; break;
				//case 7:ChMate->MetallicMap = XMate->TextureNameList[i]; break;
				//default:
				//	break;
				//}

			}

			chMateNos[chMate->materialName] = i;

			chMateList.push_back(chMate);

			i++;

		}

	}

	_chFrame->mesh = mesh;

}


///////////////////////////////////////////////////////////////////////////////////////
//ChCMObjeFile Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateModel(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;

	ChCpp::TextObject text;

	{
		std::string tmp;

		ChFIO::File files;

		files.FileOpen(_filePath);

		tmp = files.FileRead();

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp);

	}

	folderPath = GetRoutePath(_filePath);

	for (unsigned long i = 0; i < text.LineCount(); i++)
	{
		if (text[i].length() <= 0)continue;
		if (text[i][0] == commentTags)continue;

		CreateMaterials(text[i]);

		CreateObject(text[i]);
		SetVertex(text[i]);
		SetUV(text[i]);
		SetNormal(text[i]);
		SetFace(text[i]);
		SetMateBlock(text[i]);
	}

	//if (ObjectMaps.size() <= 0)return;
	if (objects.size() <= 0)return;

	auto outModels = ChPtr::Make_S<ModelFrame>();

	outModels->modelName = _filePath;

	outModels->modelData = ChPtr::Make_S<ModelFrame::Frame>();

	outModels->modelData->myName = "Root";

	CreateChFrame(outModels->modelData);

	SetModel(outModels);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateObject(const std::string& _objectName)
{
	if (_objectName.size() < 3)return;
	if (_objectName[0] != objectBlockTags)return;
	if (_objectName[1] != ' ')return;

	auto name = _objectName.substr(2);

	auto obj = ChPtr::Make_S<ObjFileModelData>();

	obj->sVertex = makeObject != nullptr ? makeObject->sVertex + makeObject->vertexDatas.size() : 0;
	obj->sUV = makeObject != nullptr ? makeObject->sUV + makeObject->uvDatas.size() : 0;
	obj->sNormal = makeObject != nullptr ? makeObject->sNormal + makeObject->normalDatas.size() : 0;

	makeObject = nullptr;

	makeObject = obj;
	//ObjectMaps[Name] = MakeObject;
	makeObject->objectName = name;
	objects.push_back(makeObject);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateMaterials(const std::string& _fileName)
{
	if (_fileName.size() < 8)return;
	if (_fileName[0] != useMaterialFileNameTags[0])return;
	if (_fileName[1] != useMaterialFileNameTags[1])return;
	if (_fileName[2] != useMaterialFileNameTags[2])return;
	if (_fileName[3] != useMaterialFileNameTags[3])return;
	if (_fileName[4] != useMaterialFileNameTags[4])return;
	if (_fileName[5] != useMaterialFileNameTags[5])return;

	std::string fileName = &_fileName[7];

	ChCpp::TextObject text;

	{
		std::string tmp;

		ChFIO::File files;

		files.FileOpen(folderPath + fileName);

		tmp = files.FileRead();

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp);
	}

	for (unsigned long i = 0; i < text.LineCount(); i++)
	{
		if (text[i].length() <= 0)continue;
		if (text[i][0] == commentTags)continue;

		CreateMaterial(text[i]);
		SetMatAmbient(text[i]);
		SetMatDiffuse(text[i]);
		SetMatSpecular(text[i]);
		SetMatSpecularHighLight(text[i]);
		SetMatDissolve(text[i]);
		SetMatODensity(text[i]);
		SetMatAmbientMap(text[i]);
		SetMatDiffuseMap(text[i]);
		SetMatSpecularMap(text[i]);
		SetMatSpecularHighLightMap(text[i]);
		SetMatBumpMap(text[i]);
		SetMatMetallicMap(text[i]);
		SetMatNormalMap(text[i]);
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateMaterial(const std::string& _matName)
{

	if (_matName.size() < 7)return;
	if (_matName[0] != matMaterialBlockTags[0])return;
	if (_matName[1] != matMaterialBlockTags[1])return;
	if (_matName[2] != matMaterialBlockTags[2])return;
	if (_matName[3] != matMaterialBlockTags[3])return;
	if (_matName[4] != matMaterialBlockTags[4])return;
	if (_matName[5] != matMaterialBlockTags[5])return;

	targetMaterial = nullptr;

	targetMaterial = ChPtr::Make_S<ObjFileMaterialData>();

	materialMaps[&_matName[7]] = targetMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateChFrame(ChPtr::Shared<ChCpp::ModelFrame::Frame>& _frame)
{

	//for (auto&& Obj : ObjectMaps)
	for (auto&& obj : objects)
	{
		unsigned long materialNo = 0;

		auto mesh = ChPtr::Make_S<ChCpp::ModelFrame::Mesh>();

		//for (auto&& Vertexs : Obj.second->VertexDatas)
		for (auto&& vertexs : obj->vertexDatas)
		{
			auto ver = ChPtr::Make_S<ChCpp::ModelFrame::VertexData>();

			ver->pos = *vertexs;

			mesh->vertexList.push_back(ver);

		}

		//for (auto&& Face : Obj.second->MeshDatas)
		for (auto&& face : obj->meshDatas)
		{

			if (mesh->materialNo.find(face->targetMaterialName) == mesh->materialNo.end())
			{

				mesh->materialNo[face->targetMaterialName] = materialNo;

				auto mate = ChPtr::Make_S<ChCpp::ModelFrame::Material>();

				auto& tmpMate = materialMaps[face->targetMaterialName];

				mate->materialName = face->targetMaterialName;

				mate->diffuse = tmpMate->diffuse;
				mate->diffuse.a = tmpMate->alpha;

				mate->specular = tmpMate->specular;

				mate->spePow = tmpMate->spePow;

				mate->ambientPow = tmpMate->ambient.r + tmpMate->ambient.g + tmpMate->ambient.b;

				mate->ambientPow /= 3;

				mate->textureNames.push_back(tmpMate->diffuseMap);
				mate->textureNames.push_back(tmpMate->ambientMap);
				mate->textureNames.push_back(tmpMate->specularMap);
				mate->textureNames.push_back(tmpMate->specularHighLightMap);
				mate->textureNames.push_back(tmpMate->bumpMap);
				mate->textureNames.push_back(tmpMate->alphaMap);
				mate->textureNames.push_back(tmpMate->normalMap);
				mate->textureNames.push_back(tmpMate->metallicMap);

				//mate->diffuseMap = tmpMate->diffuseMap;
				//mate->AmbientMap = tmpMate->AmbientMap;
				//mate->specularMap = tmpMate->specularMap;
				//mate->specularPowMap = tmpMate->specularHighLightMap;
				//mate->BumpMap = tmpMate->BumpMap;
				//mate->alphaMap = tmpMate->alphaMap;
				//mate->NormalMap = tmpMate->NormalMap;
				//mate->MetallicMap = tmpMate->MetallicMap;

				mesh->materialList.push_back(mate);

				materialNo++;
			}

			std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace::SurFaceVertex>>fVList;

			for (auto&& values : face->values)
			{

				//unsigned long NVertex = Values->VertexNum - Obj.second->SVertex - 1;
				//unsigned long NUV = Values->UVNum - Obj.second->SUV - 1;
				//unsigned long NNormal = Values->NormalNum - Obj.second->SNormal - 1;
				unsigned long nVertex = values->vertexNum - obj->sVertex - 1;
				unsigned long nUV = values->uvNum - obj->sUV - 1;
				unsigned long nNormal = values->normalNum - obj->sNormal - 1;

				auto faceVertex = ChPtr::Make_S<ChCpp::ModelFrame::SurFace::SurFaceVertex>();
				
				faceVertex->vertexNo = nVertex;
				//if(Obj.second->UVDatas.size() > NUV)faceVertex->UVPos = *Obj.second->UVDatas[NUV];
				if(obj->uvDatas.size() > nUV)faceVertex->uvPos = *obj->uvDatas[nUV];

				fVList.push_back(faceVertex);

				//mesh->VertexList[NVertex]->Normal += *Obj.second->NormalDatas[NNormal];
				mesh->vertexList[nVertex]->normal += *obj->normalDatas[nNormal];
			}

			if (fVList.size() >= 3)
			{

				unsigned long counters[3];
				counters[0] = 0;
				counters[1] = 1;
				counters[2] = fVList.size() - 1;

				ChStd::Bool upperFlg = true;
				

				for (unsigned long i = 0; i < fVList.size() - 2; i++)
				{

					auto face = ChPtr::Make_S<ChCpp::ModelFrame::SurFace>();

					face->vertexData[0] = *fVList[counters[2]];
					face->vertexData[1] = *fVList[counters[1]];
					face->vertexData[2] = *fVList[counters[0]];

					//face->VertexData[0] = *FVList[i];
					//face->VertexData[1] = *FVList[i + 1];
					//face->VertexData[2] = *FVList[i + 2];

					face->materialNo = materialNo - 1;

					if (upperFlg)
					{
						counters[0] = counters[1];
						counters[1] = counters[2] - 1;
					}
					else
					{
						counters[2] = counters[1];
						counters[1] = counters[0] + 1;
					}

					upperFlg = !upperFlg;

					mesh->faceList.push_back(face);
				}

			}


			for (auto&& ver : mesh->vertexList)
			{
				ver->normal.Normalize();
			}

		}

		auto frame = ChPtr::Make_S< ChCpp::ModelFrame::Frame>();

		//Frame->MyName = Obj.first;
		frame->myName = obj->objectName;
		frame->parent = _frame;
		frame->mesh = mesh;


		_frame->childFrames.push_back(frame);

	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::OutModelFile(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;
	if (_filePath.rfind(".") == std::string::npos)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetVertex(const std::string& _line)
{
	if (_line.size() < 2)return;
	if (_line[0] != vertexTags)return;
	if (_line[1] != ' ')return;

	auto pos = ChPtr::Make_S<ChVec3>();

	pos->Deserialize(_line, 2, " ");

	makeObject->vertexDatas.push_back(pos);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetUV(const std::string& _line)
{
	if (_line.size() < 3)return;
	if (_line[0] != uvTags[0])return;
	if (_line[1] != uvTags[1])return;

	auto uv = ChPtr::Make_S<ChVec2>();

	uv->Deserialize(_line, 3, " ");

	makeObject->uvDatas.push_back(uv);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetNormal(const std::string& _line)
{
	if (_line.size() < 3)return;
	if (_line[0] != normalTags[0])return;
	if (_line[1] != normalTags[1])return;

	auto normal = ChPtr::Make_S<ChVec3>();

	normal->Deserialize(_line, 3, " ");

	makeObject->normalDatas.push_back(normal);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetFace(const std::string& _line)
{
	if (_line.size() < 2)return;
	if (_line[0] != meshTags)return;
	if (_line[1] != ' ')return;

	unsigned long pos = _line.find(' ');

	unsigned long tmpPos = pos;

	unsigned long end = 0;

	auto data = ChPtr::Make_S<ChCpp::CMObjFile::ObjFileModelData::MeshData>();

	data->targetMaterialName = blockMaterial;

	makeObject->meshDatas.push_back(data);

	ChStd::Bool endFlg = false;

	while (1)
	{

		tmpPos = _line.find(' ', pos + 1);

		if (_line.size() < tmpPos)
		{
			endFlg = true;
			tmpPos = _line.size();
		}

		auto mdata = ChPtr::Make_S<ChCpp::CMObjFile::ObjFileModelData::MeshData::Data>();


		std::string tmp = _line.substr(pos, tmpPos - pos);

		unsigned long val[3] = { 0xffffffff,0xffffffff ,0xffffffff };

		//SrashCount//
		unsigned long sCount = 0;

		unsigned long start = 0;

		while (1)
		{
			end = tmp.find('/', start);

			if (tmp.size() <= end)end = tmp.size();

			std::string ST = tmp.substr(start, end - start);

			if (tmp[start] != '/')
			{
				val[sCount] = ChStr::GetIntegialFromText<unsigned long>(tmp.substr(start, end - start));
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

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMateBlock(const std::string& _line)
{

	if (_line.size() < 7)return;
	if (_line[0] != materialBlockTags[0])return;
	if (_line[1] != materialBlockTags[1])return;
	if (_line[2] != materialBlockTags[2])return;
	if (_line[3] != materialBlockTags[3])return;
	if (_line[4] != materialBlockTags[4])return;
	if (_line[5] != materialBlockTags[5])return;

	blockMaterial = &_line[7];

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatAmbient(const std::string& _line)
{
	if (_line.size() < 3)return;
	if (_line[0] != matAmbientTags[0])return;
	if (_line[1] != matAmbientTags[1])return;

	targetMaterial->ambient.Deserialize(&_line[3], 0, " ");
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatDiffuse(const std::string& _line)
{

	if (_line.size() < 3)return;
	if (_line[0] != matDiffuseTags[0])return;
	if (_line[1] != matDiffuseTags[1])return;

	targetMaterial->diffuse.Deserialize(&_line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecular(const std::string& _line)
{

	if (_line.size() < 3)return;
	if (_line[0] != matSpecularTags[0])return;
	if (_line[1] != matSpecularTags[1])return;

	targetMaterial->specular.Deserialize(&_line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecularHighLight(const std::string& _line)
{

	if (_line.size() < 3)return;
	if (_line[0] != matSpecularHighLightTags[0])return;
	if (_line[1] != matSpecularHighLightTags[1])return;

	targetMaterial->spePow = ChStr::GetFloatingFromText<float>(&_line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatDissolve(const std::string& _line)
{

	if (_line.size() < 2)return;
	if (_line[0] != matDissolveTags)return;
	if (_line[1] != ' ')return;

	targetMaterial->alpha = ChStr::GetFloatingFromText<float>(&_line[2], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatODensity(const std::string& _line)
{
	if (_line.size() < 3)return;
		
	if (_line[0] != matODensityTags[0])return;
	if (_line[1] != matODensityTags[1])return;

	targetMaterial->ODensity = ChStr::GetFloatingFromText<float>(&_line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatAmbientMap(const std::string& _line)
{
	if (_line.size() < 7)return;
		
	if (_line[0] != matAmbientMapTags[0])return;
	if (_line[1] != matAmbientMapTags[1])return;
	if (_line[2] != matAmbientMapTags[2])return;
	if (_line[3] != matAmbientMapTags[3])return;
	if (_line[4] != matAmbientMapTags[4])return;
	if (_line[5] != matAmbientMapTags[5])return;

	targetMaterial->ambientMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatDiffuseMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[0] != matDiffuseMapTags[0])return;
	if (_line[1] != matDiffuseMapTags[1])return;
	if (_line[2] != matDiffuseMapTags[2])return;
	if (_line[3] != matDiffuseMapTags[3])return;
	if (_line[4] != matDiffuseMapTags[4])return;
	if (_line[5] != matDiffuseMapTags[5])return;

	targetMaterial->diffuseMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecularMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[0] != matSpecularMapTags[0])return;
	if (_line[1] != matSpecularMapTags[1])return;
	if (_line[2] != matSpecularMapTags[2])return;
	if (_line[3] != matSpecularMapTags[3])return;
	if (_line[4] != matSpecularMapTags[4])return;
	if (_line[5] != matSpecularMapTags[5])return;

	targetMaterial->specularMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecularHighLightMap(const std::string& _line)
{

	if (_line.size() < 7)return;
		
	if (_line[0] != matSpecularHighLightMapTags[0])return;
	if (_line[1] != matSpecularHighLightMapTags[1])return;
	if (_line[2] != matSpecularHighLightMapTags[2])return;
	if (_line[3] != matSpecularHighLightMapTags[3])return;
	if (_line[4] != matSpecularHighLightMapTags[4])return;
	if (_line[5] != matSpecularHighLightMapTags[5])return;

	targetMaterial->specularHighLightMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatBumpMap(const std::string& _line)
{

	if (_line.size() < 9)return;
		
	if (_line[0] != matBumpMapTags[0])return;
	if (_line[1] != matBumpMapTags[1])return;
	if (_line[2] != matBumpMapTags[2])return;
	if (_line[3] != matBumpMapTags[3])return;
	if (_line[4] != matBumpMapTags[4])return;
	if (_line[5] != matBumpMapTags[5])return;
	if (_line[6] != matBumpMapTags[6])return;
	if (_line[7] != matBumpMapTags[7])return;

	targetMaterial->bumpMap = LoadTextureName(&_line[9]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatBumpMap2(const std::string& _line)
{
	if (_line.size() < 5)return;
		
	if (_line[0] != matBumpMapTags2[0])return;
	if (_line[1] != matBumpMapTags2[1])return;
	if (_line[2] != matBumpMapTags2[2])return;
	if (_line[3] != matBumpMapTags2[3])return;

	targetMaterial->bumpMap = LoadTextureName(&_line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatMetallicMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[0] != matMetallicMapTags[0])return;
	if (_line[1] != matMetallicMapTags[1])return;
	if (_line[2] != matMetallicMapTags[2])return;
	if (_line[3] != matMetallicMapTags[3])return;
	if (_line[4] != matMetallicMapTags[4])return;
	if (_line[5] != matMetallicMapTags[5])return;

	targetMaterial->metallicMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatMetallicMap2(const std::string& _line)
{

	if (_line.size() < 3)return;
		
	if (_line[0] != matMetallicMapTags2[0])return;
	if (_line[1] != matMetallicMapTags2[1])return;

	targetMaterial->metallicMap = LoadTextureName(&_line[3]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatNormalMap(const std::string& _line)
{

	if (_line.size() < 5)return;
		
	if (_line[0] != matNormalMapTags[0])return;
	if (_line[1] != matNormalMapTags[1])return;
	if (_line[2] != matNormalMapTags[2])return;
	if (_line[3] != matNormalMapTags[3])return;

	targetMaterial->normalMap = LoadTextureName(&_line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::CMObjFile::LoadTextureName(const std::string& _line)
{

	ChStd::Bool loadFlg = false;
	std::string name = "";

	size_t nowPos = 0;
	size_t nowEndPos = 0;

	while (1)
	{
		nowPos = nowEndPos;
		nowEndPos = _line.find(' ', nowPos + 1);

		if (nowEndPos == _line.npos)nowEndPos = _line.length();

		if (_line[nowPos + 1] == '-')
		{

			nowPos = nowEndPos;
			nowEndPos = _line.find(' ', nowPos + 1);

			continue;
		}

		name = _line.substr(nowPos, nowEndPos - nowPos);
		break;
	}

	return name;
}