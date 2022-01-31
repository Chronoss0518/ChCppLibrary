#include"../../BaseIncluder/ChBase.h"

#include"../ChFile/ChFile.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"
#include"ChLMObjFile.h"


///////////////////////////////////////////////////////////////////////////////////////
//ChCMObjeFile Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateModel(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;

	ChCpp::TextObject text;

	{
		std::string tmp;

		ChCpp::File<> files;

		files.FileOpen(_filePath);

		tmp = files.FileReadText();

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp);

	}

	folderPath = GetRoutePath(_filePath);

	for (auto line : text)
	{
		if (line.length() <= 0)continue;
		if (line[0] == commentTags)continue;

		CreateMaterials(line);

		CreateObject(line);
		SetVertex(line);
		SetUV(line);
		SetNormal(line);
		SetFace(line);
		SetMateBlock(line);
	}

	if (objects.size() <= 0)return;

	auto outModels = ChPtr::Make_S<ModelFrame>();

	outModels->modelName = _filePath;

	outModels->modelData = ChPtr::Make_S<ModelFrame::Frame>();

	outModels->modelData->myName = "Root";

	CreateChFrame(outModels->modelData);

	SetModel(outModels);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateObject(const std::string& _objectName)
{

	if (!IsPrefix(_objectName, &objectBlockTags, sizeof(objectBlockTags)))return;

	auto name = _objectName.substr(2);

	auto obj = ChPtr::Make_S<ObjFileModelData>();

	obj->sVertex = makeObject != nullptr ? makeObject->sVertex + makeObject->vertexPosList.size() : 0;
	obj->sUV = makeObject != nullptr ? makeObject->sUV + makeObject->vertexUvPosList.size() : 0;
	obj->sNormal = makeObject != nullptr ? makeObject->sNormal + makeObject->vertexNormalList.size() : 0;

	makeObject = nullptr;

	makeObject = obj;
	//ObjectMaps[Name] = MakeObject;
	makeObject->objectName = name;
	objects.push_back(makeObject);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateMaterials(const std::string& _fileName)
{

	if (!IsPrefix(_fileName, useMaterialFileNameTags, sizeof(useMaterialFileNameTags)))return;

	std::string fileName = &_fileName[7];

	ChCpp::TextObject text;

	{
		std::string tmp;

		ChCpp::File<> files;

		files.FileOpen(folderPath + fileName);

		tmp = files.FileReadText();

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp);
	}

	for (auto line : text)
	{
		if (line.length() <= 0)continue;
		if (line[0] == commentTags)continue;

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

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateMaterial(const std::string& _matName)
{

	if (!IsPrefix(_matName, matMaterialBlockTags, sizeof(matMaterialBlockTags)))return;

	targetMaterial = nullptr;

	targetMaterial = ChPtr::Make_S<ObjFileMaterialData>();

	materialMaps[&_matName[7]] = targetMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateChFrame(ChPtr::Shared<ChCpp::ModelFrame::Frame>& _frame)
{


	//for (auto&& Obj : ObjectMaps)
	for (auto&& obj : objects)
	{
		unsigned long materialNo = 0;

		auto mesh = ChPtr::Make_S<ChCpp::ModelFrame::Mesh>();

		//for (auto&& Vertexs : Obj.second->vertexPosList)
		for (auto&& vertexs : obj->vertexPosList)
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

				ChPtr::Shared<ChCpp::ModelFrame::Material> mate = ChPtr::Make_S<ChCpp::ModelFrame::Material>();


				auto& tmpMate = materialMaps[face->targetMaterialName];

				mate->materialName = face->targetMaterialName;

				mate->diffuse = tmpMate->diffuse;
				mate->diffuse.a = tmpMate->alpha;

				mate->specular = tmpMate->specular;

				mate->specular = tmpMate->spePow;

				mate->ambient = tmpMate->ambient.r + tmpMate->ambient.g + tmpMate->ambient.b;

				mate->ambient /= 3;

				//mate->textureNames.push_back(tmpMate->diffuseMap);
				//mate->textureNames.push_back(tmpMate->ambientMap);
				//mate->textureNames.push_back(tmpMate->specularMap);
				//mate->textureNames.push_back(tmpMate->specularHighLightMap);
				//mate->textureNames.push_back(tmpMate->bumpMap);
				//mate->textureNames.push_back(tmpMate->alphaMap);
				//mate->textureNames.push_back(tmpMate->normalMap);
				//mate->textureNames.push_back(tmpMate->metallicMap);


				mate->diffuseMap = tmpMate->diffuseMap;
				mate->ambientMap = tmpMate->ambientMap;
				mate->specularMap = tmpMate->specularMap;
				mate->specularHighLightMap = tmpMate->specularHighLightMap;
				mate->bumpMap = tmpMate->bumpMap;
				mate->alphaMap = tmpMate->alphaMap;
				mate->normalMap = tmpMate->normalMap;
				mate->metallicMap = tmpMate->metallicMap;


				mesh->materialList.push_back(mate);

				materialNo++;

				mate = nullptr;
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
				if (obj->vertexUvPosList.size() > nUV)faceVertex->uvPos = *obj->vertexUvPosList[nUV];

				fVList.push_back(faceVertex);

				//mesh->VertexList[NVertex]->Normal += *Obj.second->vertexNormalList[NNormal];
				mesh->vertexList[nVertex]->normal += *obj->vertexNormalList[nNormal];
			}

			auto face = ChPtr::Make_S<ChCpp::ModelFrame::SurFace>();

			for (unsigned long i = 0; i < fVList.size(); i++)
			{

				face->vertexData.push_back(fVList[fVList.size() - 1 - i]);

				face->materialNo = materialNo - 1;

			}

			mesh->faceList.push_back(face);

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

void ChCpp::ModelLoader::ObjFile::OutModelFile(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;
	if (_filePath.rfind(".") == std::string::npos)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetVertex(const std::string& _line)
{

	if (!IsPrefix(_line, &vertexTags, sizeof(vertexTags)))return;

	auto pos = ChPtr::Make_S<ChVec3>();

	pos->Deserialize(_line, 2, " ");

	makeObject->vertexPosList.push_back(pos);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetUV(const std::string& _line)
{

	if (!IsPrefix(_line, uvTags, sizeof(uvTags)))return;

	auto uv = ChPtr::Make_S<ChVec2>();

	uv->Deserialize(_line, 3, " ");

	makeObject->vertexUvPosList.push_back(uv);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetNormal(const std::string& _line)
{

	if (!IsPrefix(_line, normalTags, sizeof(normalTags)))return;

	auto normal = ChPtr::Make_S<ChVec3>();

	normal->Deserialize(_line, 3, " ");

	makeObject->vertexNormalList.push_back(normal);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetFace(const std::string& _line)
{
	if (!IsPrefix(_line, &meshTags, sizeof(meshTags)))return;

	unsigned long pos = _line.find(' ');

	unsigned long tmpPos = pos;

	unsigned long end = 0;

	auto data = ChPtr::Make_S<ChCpp::ModelLoader::ObjFile::ObjFileModelData::MeshData>();

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

		auto mdata = ChPtr::Make_S<ChCpp::ModelLoader::ObjFile::ObjFileModelData::MeshData::Data>();


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

void ChCpp::ModelLoader::ObjFile::SetMateBlock(const std::string& _line)
{

	if (!IsPrefix(_line, materialBlockTags, sizeof(materialBlockTags)))return;

	blockMaterial = &_line[7];
	
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatAmbient(const std::string& _line)
{

	if (!IsPrefix(_line, matAmbientTags, sizeof(matAmbientTags)))return;

	targetMaterial->ambient.Deserialize(&_line[3], 0, " ");
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatDiffuse(const std::string& _line)
{

	if (!IsPrefix(_line, matDiffuseTags, sizeof(matDiffuseTags)))return;

	targetMaterial->diffuse.Deserialize(&_line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecular(const std::string& _line)
{

	if (!IsPrefix(_line, matSpecularTags, sizeof(matSpecularTags)))return;

	targetMaterial->specular.Deserialize(&_line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecularHighLight(const std::string& _line)
{

	if (!IsPrefix(_line, matSpecularHighLightTags, sizeof(matSpecularHighLightTags)))return;

	targetMaterial->spePow = ChStr::GetFloatingFromText<float>(&_line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatDissolve(const std::string& _line)
{;

	if (!IsPrefix(_line, &matDissolveTags, sizeof(matDissolveTags)))return;

	targetMaterial->alpha = ChStr::GetFloatingFromText<float>(&_line[2], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatODensity(const std::string& _line)
{

	if (!IsPrefix(_line, matODensityTags, sizeof(matODensityTags)))return;

	targetMaterial->ODensity = ChStr::GetFloatingFromText<float>(&_line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatAmbientMap(const std::string& _line)
{

	if (!IsPrefix(_line, matAmbientMapTags, sizeof(matAmbientMapTags)))return;

	targetMaterial->ambientMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatDiffuseMap(const std::string& _line)
{

	if (!IsPrefix(_line, matDiffuseMapTags, sizeof(matDiffuseMapTags)))return;

	targetMaterial->diffuseMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecularMap(const std::string& _line)
{

	if (!IsPrefix(_line, matSpecularMapTags, sizeof(matSpecularMapTags)))return;

	targetMaterial->specularMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecularHighLightMap(const std::string& _line)
{

	if (!IsPrefix(_line, matSpecularHighLightMapTags, sizeof(matSpecularHighLightMapTags)))return;

	targetMaterial->specularHighLightMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatBumpMap(const std::string& _line)
{

	if (!IsPrefix(_line, matBumpMapTags, sizeof(matBumpMapTags)))return;

	targetMaterial->bumpMap = LoadTextureName(&_line[9]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatBumpMap2(const std::string& _line)
{
	if (!IsPrefix(_line, matBumpMapTags2, sizeof(matBumpMapTags2)))return;

	targetMaterial->bumpMap = LoadTextureName(&_line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatMetallicMap(const std::string& _line)
{

	if (!IsPrefix(_line, matMetallicMapTags, sizeof(matMetallicMapTags)))return;

	targetMaterial->metallicMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatMetallicMap2(const std::string& _line)
{
	if (!IsPrefix(_line, matMetallicMapTags2, sizeof(matMetallicMapTags2)))return;

	targetMaterial->metallicMap = LoadTextureName(&_line[3]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatNormalMap(const std::string& _line)
{

	if (!IsPrefix(_line, matNormalMapTags, sizeof(matNormalMapTags)))return;

	targetMaterial->normalMap = LoadTextureName(&_line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::ObjFile::IsPrefix(const std::string _str, const char* _prefix, const unsigned long _prefixSize)
{

	if (_str.size() <= (_prefixSize + 1))return false;

	if (_str[_prefixSize] != ' ')return false;

	for (unsigned long i = 0; i < _prefixSize; i++)
	{

		if (_str[_prefixSize - i - 1] != _prefix[_prefixSize - i - 1])return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::ModelLoader::ObjFile::LoadTextureName(const std::string& _line)
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