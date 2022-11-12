
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

void FrameObject::GetLenIsPointToPrimitive(std::vector<ChPtr::Shared<NearPointData>>& _res, const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{
	auto&& com = GetComponent<FrameComponent>();

	if (com == nullptr)return;
	if (com->vertexList.size() <= 2)return;

	auto&& vertexList = com->vertexList;

	{
		ChLMat tmpMat = _mat;
		tmpMat = GetDrawLHandMatrix() * tmpMat;

		for (auto&& ver : vertexList)
		{
			ver->pos = _mat.Transform(ver->pos);
		}

	}

	std::vector<ChPtr::Shared<ChMultiThread>>threadList;
	
	for (auto&& prim : com->primitives)
	{
		auto thread = ChPtr::Make_S<ChMultiThread>();
		thread->Init([&] {
			
			auto primitive = prim;
			
			if (primitive->vertexData.size() <= 2)return;
			
			auto&& vertexDataList = primitive->vertexData;
	

			ChVec3 firstPos = vertexList[vertexDataList[0]->vertexNo]->pos;
			
			ChVec3 faceNormal = vertexList[vertexDataList[1]->vertexNo]->pos - firstPos;
			faceNormal.Cross(
				faceNormal,
				vertexList[vertexDataList[vertexDataList.size() - 1]->vertexNo]->pos - firstPos);

			{
				ChVec3 testNormal = _point - firstPos;
				testNormal.Normalize();
				if (faceNormal.GetCos(faceNormal,testNormal) == 0.0f)return;
			}

			float len = ChVec3::GetDot(faceNormal, _point - firstPos);
			
			if (len < 0.0f)return;

			ChVec3 tmpPoint = _point + (faceNormal * -len);
			
			ChStd::Bool onFaceFlg = true;
			
			ChVec3 tmpNormal = ChVec3::GetCross(
				firstPos - tmpPoint,
				vertexList[vertexDataList[1]->vertexNo]->pos - tmpPoint);

			for (unsigned long i = 1;i< vertexDataList.size() - 1;i++)
			{
				if(tmpNormal == ChVec3::GetCross(
					firstPos - tmpPoint,
					vertexList[vertexDataList[1]->vertexNo]->pos - tmpPoint))continue;

				onFaceFlg = false;
				break;
			}

			if (!onFaceFlg)return;
			auto data = ChPtr::Make_S<NearPointData>();

			data->toVector = faceNormal * -len;
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

