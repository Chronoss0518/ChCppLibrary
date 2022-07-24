#include"../../BaseIncluder/ChBase.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoaderBase.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChModelLoader Method//
///////////////////////////////////////////////////////////////////////////////////////

void SetPosition(Ch3D::Position* _pos, ChVec3 _val)
{
	if (ChPtr::NullCheck(_pos))return;

	_pos->pos = _val;
}
void SetPosition(Ch3D::UV* _uv, ChVec2 _val)
{
	if (ChPtr::NullCheck(_uv))return;

	_uv->uv = _val;
}

void ChCpp::ModelLoaderBase::SetPosition(Ch3D::Color* _col, ChVec4 _val)
{
	if (ChPtr::NullCheck(_col))return;

	_col->color = _val;
}

void ChCpp::ModelLoaderBase::SetPosition(Ch3D::Normal* _normal, ChVec3 _val)
{
	if (ChPtr::NullCheck(_normal))return;

	_normal->normal = _val;
}

void ChCpp::ModelLoaderBase::SetPosition(Ch3D::FaceNormal* _faceNormal, ChVec3 _val)
{
	if (ChPtr::NullCheck(_faceNormal))return;

	_faceNormal->faceNormal = _val;
}

std::string ChCpp::ModelLoaderBase::GetRoutePath(const std::string& _filePath)
{

	if (_filePath.find("\\") == _filePath.find("/"))return "";

	std::string tmpPath = ChStr::StrReplase(_filePath, "\\", "/");

	unsigned long tmp = tmpPath.rfind("/");

	return tmpPath.substr(0, tmp + 1);

}
