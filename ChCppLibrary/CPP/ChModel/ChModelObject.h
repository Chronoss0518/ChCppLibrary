
#ifndef Ch_CPP_ModelObject_h
#define Ch_CPP_ModelObject_h

#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{

	struct BoneObject :public ChCpp::BaseObject
	{
		Ch3D::Transform transform;
	};

	struct FrameComponent:public ChCpp::BaseComponent
	{
		std::vector<ChPtr::Shared<Ch3D::Primitive>> primitives;
		std::vector<ChPtr::Shared<Ch3D::MaterialData>>materialList;
		std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;
		std::map<std::string, unsigned long>mateNames;
		ChVec3 maxPos = ChVec3();
		ChVec3 minPos = ChVec3();
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();
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

	struct NearPointData
	{
		ChVec3 toVector = ChVec3();
		std::string materialName = "";
	};

	class FrameObject : public ChCpp::BaseObject
	{
	public://Set Functions//

		void SetOutSizdTransform(const Ch3D::Transform& _trans);

		void SetOutSizdTransform(const ChLMat& _mat);

		void SetOutSizdTransform(const ChRMat& _mat);
		
		void SetFrameTransform(const Ch3D::Transform& _mat);

		void SetFrameTransform(const ChLMat& _mat);

		void SetFrameTransform(const ChRMat& _mat);

	public://Get Functions//

		ChLMat GetDrawLHandMatrix();

		ChRMat GetDrawRHandMatrix();

		inline ChLMat GetOutSizdTransformLMat()
		{
			return outSideMat;
		}

		inline ChRMat GetOutSizdTransformRMat()
		{
			return outSideMat.ConvertAxis();
		}

		inline ChLMat GetFrameTransformLMat()
		{
			return frameMat;
		}

		inline ChRMat GetFrameTransformRMat()
		{
			return frameMat.ConvertAxis();
		}

		static ChStd::Bool GetLenIsPointToPolyBoard(ChVec3& _outVector, const ChVec3& _point,const Ch3D::Primitive& _prim,const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());

		static ChStd::Bool GetLenIsPointToPolyBoardFunction(ChVec3& _outVector, const ChVec3& _point,const Ch3D::Primitive& _prim,const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen = FLT_MAX);

		void GetLenIsPointToPrimitive(std::vector<ChPtr::Shared<NearPointData>>& _res, const ChVec3& _point, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());

		std::vector<ChPtr::Shared<NearPointData>> GetLenToPointAllChildTest(const ChVec3& _point, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());

	private:

		void GetLenToPointAllChildTest(std::vector<ChPtr::Shared<NearPointData>>& _outData, const ChVec3& _point, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());

	public://Update Functions//

		void Update()override;

		void UpdateDrawTransform();

		void UpdateAllDrawTransform();

		void SetAnimationName(const std::string& _name);

	public://Is Function//

	protected:

		ChLMat frameMat;
		ChLMat outSideMat;

	private:

		ChLMat drawMat;
		std::string animationName = "";

	};

	class ModelObject :public FrameObject, public ChCp::Initializer
	{
	public:

		inline void Init()override
		{
			SetInitFlg(true);
		}

		inline void Release()override
		{
			SetInitFlg(false);
		}

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

		virtual void Create(){}

	private:

		std::vector<std::string>animationNames;
		std::string modelName = "";

		Ch3D::ShaderAxisType axisType = Ch3D::ShaderAxisType::LeftHand;
	};

}

#endif