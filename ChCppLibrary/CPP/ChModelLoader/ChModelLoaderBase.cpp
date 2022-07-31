#include"../../BaseIncluder/ChBase.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoaderBase.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChModelLoader Method//
///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::ModelLoaderBase::GetRoutePath(const std::string& _filePath)
{

	if (_filePath.find("\\") == _filePath.find("/"))return "";

	std::string tmpPath = ChStr::StrReplase(_filePath, "\\", "/");

	unsigned long tmp = tmpPath.rfind("/");

	return tmpPath.substr(0, tmp + 1);

}
