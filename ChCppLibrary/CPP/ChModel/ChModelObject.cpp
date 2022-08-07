
#include"../../BaseIncluder/ChBase.h"

//#include"../ChTexture/ChBaseTexture.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"ChModelObject.h"

using namespace ChCpp;

void FrameObject::SetAnimationTransform(const Ch3D::Transform& _trans)
{
	animationMat.SetPosition(_trans.pos);
	animationMat.SetRotation(_trans.rot);
	animationMat.SetScalling(_trans.scl);
}

void FrameObject::SetAnimationTransform(const ChLMat& _mat)
{
	animationMat = _mat;
}

void FrameObject::SetAnimationTransform(const ChRMat& _mat)
{

	animationMat = _mat.ConvertAxis();
}

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

	drawMat = outSideMat * animationMat * frameMat * parentDrawMat;

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

	drawMat = outSideMat * animationMat * frameMat * parentDrawMat;

	return drawMat.ConvertAxis();
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

	drawMat = outSideMat * animationMat * frameMat * parentDrawMat;
}

void ModelObject::AddAnimationName(const std::string& _name)
{
	animationNames.push_back(_name);
}

void ModelObject::SetModelName(const std::string& _name)
{
	modelName = _name;
}