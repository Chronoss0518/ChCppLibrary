#include"../../BaseIncluder/ChBase.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoaderBase.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChModelLoader Method//
///////////////////////////////////////////////////////////////////////////////////////

void ModelLoaderBase::Init()
{
	maxPos = ChVec3();
	minPos = ChVec3(1e+38f);
}

void ModelLoaderBase::SetMaxPos(ModelObject& _model, const ChVec3& _pos)
{
	_model.SetMaxPos(_pos);
}

void ModelLoaderBase::SetMinPos(ModelObject& _model, const ChVec3& _pos)
{
	_model.SetMinPos(_pos);
}

void ModelLoaderBase::SetCenterPos(ModelObject& _model, const ChVec3& _pos)
{
	_model.SetCenterPos(_pos);
}

void ModelLoaderBase::SetBoxSize(ModelObject& _model, const ChVec3& _size)
{
	_model.SetBoxSize(_size);
}

std::string ModelLoaderBase::GetRoutePath(const std::string& _filePath)
{

	if (_filePath.find("\\") == _filePath.find("/"))return "";

	std::string tmpPath = ChStr::StrReplase(_filePath, "\\", "/");

	unsigned long tmp = tmpPath.rfind("/");

	return tmpPath.substr(0, tmp + 1);

}

ChVec3 ModelLoaderBase::TestMaxPos(const ChVec3& _pos1, const ChVec3& _pos2)
{
	ChVec3 res;

	res.x = _pos1.x >= _pos2.x ? _pos1.x : _pos2.x;
	res.y = _pos1.y >= _pos2.y ? _pos1.y : _pos2.y;
	res.z = _pos1.z >= _pos2.z ? _pos1.z : _pos2.z;

	return res;
}

ChVec3 ModelLoaderBase::TestMinPos(const ChVec3& _pos1, const ChVec3& _pos2)
{
	ChVec3 res;

	res.x = _pos1.x <= _pos2.x ? _pos1.x : _pos2.x;
	res.y = _pos1.y <= _pos2.y ? _pos1.y : _pos2.y;
	res.z = _pos1.z <= _pos2.z ? _pos1.z : _pos2.z;

	return res;
}

ChVec3 ModelLoaderBase::CreateCenterPos(const ChVec3& _min, const ChVec3& _max)
{
	return  (_min + _max) / 2.0f;
}

ChVec3 ModelLoaderBase::CreateBoxSize(const ChVec3& _min, const ChVec3& _max)
{
	return (_max - _min) / 2.0f;
}
