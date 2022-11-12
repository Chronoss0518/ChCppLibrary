
#include"../../BaseIncluder/ChBase.h"

//#include"../ChTexture/ChBaseTexture.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"ChModelObject.h"
#include"../ChMultiThread/ChMultiThread.h"

using namespace ChCpp;

void FrameObject::SetOutSizdTransform(const Ch3D::Transform& _trans)
{
	outSideMat.SetPosition(_trans.pos);
	outSideMat.SetRotation(_trans.rot);
	outSideMat.SetScalling(_trans.scl);
}

void FrameObject::SetOutSizdTransform(const ChLMat& _mat)
{
	outSideMat = _mat;
}

void FrameObject::SetOutSizdTransform(const ChRMat& _mat)
{
	outSideMat = _mat.ConvertAxis();
}

void FrameObject::SetFrameTransform(const Ch3D::Transform& _trans)
{
	frameMat.SetPosition(_trans.pos);
	frameMat.SetRotation(_trans.rot);
	frameMat.SetScalling(_trans.scl);
}

void FrameObject::SetFrameTransform(const ChLMat& _mat)
{
	frameMat = _mat;
}

void FrameObject::SetFrameTransform(const ChRMat& _mat)
{
	frameMat = _mat.ConvertAxis();
}

void FrameObject::Update()
{
	UpdateDrawTransform();
}

ChLMat FrameObject::GetDrawLHandMatrix()
{

	ChLMat parentDrawMat;

	{
		auto parent = ChPtr::SharedSafeCast<FrameObject>(GetParent().lock());

		if (parent != nullptr)
		{
			parentDrawMat = parent->drawMat;
		}

	}

	drawMat = outSideMat * frameMat * parentDrawMat;

	return drawMat;
}

ChRMat FrameObject::GetDrawRHandMatrix()
{
	ChLMat parentDrawMat;

	{
		auto parent = ChPtr::SharedSafeCast<FrameObject>(GetParent().lock());

		if (parent != nullptr)
		{
			parentDrawMat = parent->drawMat;
		}

	}

	drawMat = outSideMat * frameMat * parentDrawMat;

	return drawMat.ConvertAxis();
}

ChStd::Bool FrameObject::GetLenIsPointToPolyBoard(ChVec3& _outVector, const ChVec3& _point, const Ch3D::Primitive& _prim, const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen, const ChLMat& _mat)
{

	if (_prim.vertexData.size() <= 2)return false;

	std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;

	for (auto&& vertex : _vertexList)
	{
		auto ver = ChPtr::Make_S< Ch3D::SavePolyVertex>();
		*ver = *vertex;
		ver->pos = _mat.Transform(ver->pos);
		vertexList.push_back(ver);
	}

	return GetLenIsPointToPolyBoardFunction(_outVector,_point,_prim, vertexList,_maxLen);
}

ChStd::Bool FrameObject::GetLenIsPointToPolyBoardFunction(ChVec3& _outVector, const ChVec3& _point, const Ch3D::Primitive& _prim, const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen)
{

	if (_prim.vertexData.size() <= 2)return false;

	auto&& vertexDataList = _prim.vertexData;


	ChVec3 firstPos = _vertexList[vertexDataList[0]->vertexNo]->pos;

	ChVec3 faceNormal = _vertexList[vertexDataList[1]->vertexNo]->pos - firstPos;
	faceNormal.Cross(
		faceNormal,
		_vertexList[vertexDataList[vertexDataList.size() - 1]->vertexNo]->pos - firstPos);

	{
		ChVec3 testNormal = _point - firstPos;
		testNormal.Normalize();
		if (faceNormal.GetCos(faceNormal, testNormal) == 0.0f)return false;
	}

	float len = ChVec3::GetDot(faceNormal, _point - firstPos);

	if (len < 0.0f)return false;
	if (_maxLen < len)return false;

	ChVec3 tmpPoint = _point + (faceNormal * -len);

	ChStd::Bool onFaceFlg = true;

	ChVec3 tmpNormal = ChVec3::GetCross(
		firstPos - tmpPoint,
		_vertexList[vertexDataList[1]->vertexNo]->pos - tmpPoint);

	for (unsigned long i = 1; i < vertexDataList.size() - 1; i++)
	{
		if (tmpNormal == ChVec3::GetCross(
			firstPos - tmpPoint,
			_vertexList[vertexDataList[1]->vertexNo]->pos - tmpPoint))continue;

		onFaceFlg = false;
		break;
	}

	if (!onFaceFlg)return false;
	auto data = ChPtr::Make_S<NearPointData>();

	_outVector = faceNormal * -len;

	return true;
}

void FrameObject::GetLenIsPointToPrimitive(std::vector<ChPtr::Shared<NearPointData>>& _res, const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{
	auto&& com = GetComponent<FrameComponent>();

	if (com == nullptr)return;
	if (com->vertexList.size() <= 2)return;

	std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;

	{
		ChLMat tmpMat = _mat;
		tmpMat = GetDrawLHandMatrix() * tmpMat;

		for (auto&& vertex : com->vertexList)
		{
			auto ver = ChPtr::Make_S< Ch3D::SavePolyVertex>();
			*ver = *vertex;
			ver->pos = _mat.Transform(ver->pos);
			vertexList.push_back(ver);
		}


	}

	std::vector<ChPtr::Shared<ChMultiThread>>threadList;
	
	for (auto&& prim : com->primitives)
	{
		auto thread = ChPtr::Make_S<ChMultiThread>();
		thread->Init([&] {
			
			auto primitive = prim;
			ChVec3 res;
			if (!GetLenIsPointToPolyBoardFunction(res,_point,*primitive, vertexList,_maxLen))return;
			auto data = ChPtr::Make_S<NearPointData>();

			data->toVector = res;
			data->materialName = com->materialList[primitive->mateNo]->mateName;

			_res.push_back(data);
		});

		threadList.push_back(thread);
	}

	for (auto&& thread : threadList)
	{
		thread->Join();
	}

	return;
}

std::vector<ChPtr::Shared<NearPointData>> FrameObject::GetLenToPointAllChildTest(const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{
	
	std::vector<ChPtr::Shared<NearPointData>> res;
	GetLenIsPointToPrimitive(res,_point, _maxLen, _mat);

	for (auto&& child : GetChildlen<FrameObject>())
	{
		if (child.expired())continue;
		
		child.lock()->GetLenToPointAllChildTest(res, _point, _maxLen, _mat);
		
	}

	return res;
}

void FrameObject::GetLenToPointAllChildTest(std::vector<ChPtr::Shared<NearPointData>>& _outData, const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{


	GetLenIsPointToPrimitive(_outData, _point, _maxLen, _mat);

	for (auto&& child : GetChildlen<FrameObject>())
	{
		if (child.expired())continue;

		child.lock()->GetLenToPointAllChildTest(_outData, _point, _maxLen, _mat);
	}

	return;
}

void FrameObject::UpdateDrawTransform()
{
	ChLMat parentDrawMat;

	{
		auto parent = ChPtr::SharedSafeCast<FrameObject>(GetParent().lock());

		if (parent != nullptr)
		{
			parentDrawMat = parent->drawMat;
		}

	}

	drawMat = outSideMat * frameMat * parentDrawMat;
}

void FrameObject::UpdateAllDrawTransform()
{

	ChLMat parentDrawMat;

	{
		auto parent = ChPtr::SharedSafeCast<FrameObject>(GetParent().lock());

		if (parent != nullptr)
		{
			parent->UpdateAllDrawTransform();
			parentDrawMat = parent->drawMat;
		}
	}

	drawMat = outSideMat * frameMat * parentDrawMat;
}

void ModelObject::AddAnimationName(const std::string& _name)
{
	animationNames.push_back(_name);
}

void ModelObject::SetModelName(const std::string& _name)
{
	modelName = _name;
}

