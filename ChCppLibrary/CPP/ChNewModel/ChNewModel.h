#ifndef Ch_CPP_ModelObject_h
#define Ch_CPP_ModelObject_h

#include"../ChModel/ChModel.h"
#include"../ChModelLoader/ChModelLoader.h"
#include"../ChModelLoader/ChAnimationCreater.h"


namespace ChCpp
{

	struct BoneObject :public ChCpp::BaseObject
	{
		Ch3D::Transform transform;
	};

	template<class vertex = Ch3D::Vertex>
	struct FrameComponent:public ChCpp::BaseComponent
	{
		Ch3D::Frame<vertex>frame;
	};

	struct BoneComponent :public ChCpp::BaseComponent
	{
		Ch3D::BoneData boneDatas;
		BoneObject* boneObject = nullptr;
	};

	struct AnimationComponent:public ChCpp::BaseComponent
	{
		struct AnimationObject
		{
			Ch3D::Transform start;
			Ch3D::Transform end;
			float animationTime = 0;
		};

		std::vector<ChPtr::Shared<AnimationObject>>keyframeAnimation;

		std::string animationName = "";

	};

	class FrameObject : public ChCpp::BaseObject
	{
	public://Set Functions//

		void SetAnimationTransform(const Ch3D::Transform& _trans);

		void SetAnimationTransform(const ChLMat& _mat);

		void SetAnimationTransform(const ChRMat& _mat);

		void SetOutSizdTransform(const Ch3D::Transform& _trans);

		void SetOutSizdTransform(const ChLMat& _mat);

		void SetOutSizdTransform(const ChRMat& _mat);


	public://Update Functions//

		void Update()override;

		void UpdateDrawTransform();

		void SetAnimationName(const std::string& _name);

	protected:

		Ch3D::Transform frameTrans;
		Ch3D::Transform outSideTrans;
		Ch3D::Transform animationTrans;

	private:

		Ch3D::Transform drawTrans;
		std::string animationName = "";

	};

	class NewModelObject :public ChCpp::BaseObject
	{
		void SetShaderAxisType(const Ch3D::ShaderAxisType _type);

		void AddAnimationName(const std::string& _name);

		void SetModelName(const std::string& _name);

	private:

		std::vector<std::string>animationNames;
		std::string modelName = "";

		Ch3D::ShaderAxisType axisType = Ch3D::ShaderAxisType::LeftHand;
	};

}

#endif