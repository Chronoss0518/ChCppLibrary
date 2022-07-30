
#include"../../BaseIncluder/ChBase.h"

//#include"../ChTexture/ChBaseTexture.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"ChModelObject.h"

using namespace ChCpp;

void FrameObject::SetAnimationTransform(const Ch3D::Transform& _trans)
{
	animationTrans = _trans;
}

void FrameObject::SetAnimationTransform(const ChLMat& _mat)
{
	animationTrans.pos = _mat.GetPosition();
	animationTrans.rot = _mat.GetRotation();
	animationTrans.scl = _mat.GetScalling();
}

void FrameObject::SetAnimationTransform(const ChRMat& _mat)
{

	animationTrans.pos = _mat.GetPosition();
	animationTrans.rot = _mat.GetRotation();
	animationTrans.scl = _mat.GetScalling();
}

void FrameObject::SetOutSizdTransform(const Ch3D::Transform& _trans)
{
	outSideTrans = _trans;
}

void FrameObject::SetOutSizdTransform(const ChLMat& _mat)
{
	outSideTrans.pos = _mat.GetPosition();
	outSideTrans.rot = _mat.GetRotation();
	outSideTrans.scl = _mat.GetScalling();
}

void FrameObject::SetOutSizdTransform(const ChRMat& _mat)
{

	outSideTrans.pos = _mat.GetPosition();
	outSideTrans.rot = _mat.GetRotation();
	outSideTrans.scl = _mat.GetScalling();
}

void FrameObject::SetFrameTransform(const Ch3D::Transform& _trans)
{
	frameTrans = _trans;
}

void FrameObject::SetFrameTransform(const ChLMat& _mat)
{
	frameTrans.pos = _mat.GetPosition();
	frameTrans.rot = _mat.GetRotation();
	frameTrans.scl = _mat.GetScalling();
}

void FrameObject::SetFrameTransform(const ChRMat& _mat)
{
	frameTrans.pos = _mat.GetPosition();
	frameTrans.rot = _mat.GetRotation();
	frameTrans.scl = _mat.GetScalling();
}

void FrameObject::Update()
{
	UpdateDrawTransform();
}

void FrameObject::UpdateDrawTransform()
{
	Ch3D::Transform parentTransform;

	auto w_parent = GetParent();

	if (!w_parent.expired())
	{
		auto parent = ChPtr::SharedSafeCast<FrameObject>(w_parent.lock());

		if (parent != nullptr)
		{
			parentTransform = parent->drawTrans;
		}

	}

	auto parentDrawMat = parentTransform.GetLeftHandMatrix();

	auto frameMat = frameTrans.GetLeftHandMatrix();

	auto aniMat = animationTrans.GetLeftHandMatrix();

	auto tmpMat = parentDrawMat * aniMat * frameMat;

	drawTrans.pos = tmpMat.GetPosition();
	drawTrans.rot = tmpMat.GetRotation();
	drawTrans.scl = tmpMat.GetScalling();
}

ChStd::Bool FrameObject::IsMesh()
{
	auto frame = GetComponent<FrameComponent>();

	if (frame == nullptr)return false;

	if (frame->vertexList.empty())return false;

	return true;
}

void ModelObject::AddAnimationName(const std::string& _name)
{
	animationNames.push_back(_name);
}

void ModelObject::SetModelName(const std::string& _name)
{
	modelName = _name;
}