
#ifndef Ch_CPP_ModelObject_h
#define Ch_CPP_ModelObject_h

#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{

	struct SavePolyVertex :
		public Ch3D::Position,
		public Ch3D::Color,
		public Ch3D::Normal
	{};

	struct BoneObject :public ChCpp::BaseObject
	{
		Ch3D::Transform transform;
	};

	struct FrameComponent:public ChCpp::BaseComponent
	{
		std::vector<ChPtr::Shared<Ch3D::Primitive>> primitives;
		std::vector<ChPtr::Shared<Ch3D::MaterialData>>materialList;
		std::vector<ChPtr::Shared<SavePolyVertex>> vertexList;
		std::map<std::string, unsigned long>mateNames;
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

		void SetFrameTransform(const Ch3D::Transform& _mat);

		void SetFrameTransform(const ChLMat& _mat);

		void SetFrameTransform(const ChRMat& _mat);

	public://Get Functions//

		inline ChLMat GetDrawTransform()
		{
			return drawMat;
		};

		ChLMat GetDrawLHandMatrix();

		ChRMat GetDrawRHandMatrix();

	public://Update Functions//

		void Update()override;

		void UpdateDrawTransform();

		void SetAnimationName(const std::string& _name);

	public://Is Function//

	protected:

		ChLMat frameMat;
		ChLMat outSideMat;
		ChLMat animationMat;

	private:

		ChLMat drawMat;
		std::string animationName = "";

	};

	class ModelObject :public FrameObject
	{
	public:

		inline void SetShaderAxisType(const Ch3D::ShaderAxisType _type)
		{
			axisType = _type;
		}

		void SetModelName(const std::string& _name);

		inline std::string GetModelName() 
		{
			return modelName; 
		}

		void AddAnimationName(const std::string& _name);

	private:

		std::vector<std::string>animationNames;
		std::string modelName = "";

		Ch3D::ShaderAxisType axisType = Ch3D::ShaderAxisType::LeftHand;
	};

}

#endif