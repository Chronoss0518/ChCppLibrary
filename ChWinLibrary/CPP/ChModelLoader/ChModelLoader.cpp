#include"../../BaseIncluder/ChBase.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChModelLoader Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::Init(ModelObject* _model)
{
	oModel = _model;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::SetModel(ChPtr::Shared<ModelFrame> _models)
{
	oModel->model = _models;
}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::ModelLoader::GetRoutePath(const std::string& _filePath)
{

	if (_filePath.find("\\") == _filePath.find("/"))return "";

	std::string tmpPath = ChStr::StrReplase(_filePath, "\\", "/");

	unsigned long tmp = tmpPath.rfind("/");

	return tmpPath.substr(0, tmp + 1);

}
