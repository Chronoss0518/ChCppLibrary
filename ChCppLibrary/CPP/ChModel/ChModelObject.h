
#ifndef Ch_CPP_ModelObject_h
#define Ch_CPP_ModelObject_h

#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{
	class ModelLoaderBase;

	struct TargetBoneData
	{
		std::string boneObjectName = "";
		ChLMat boneOffset;

	};

	struct FrameComponent:public ChCpp::BaseComponent
	{
		std::vector<ChPtr::Shared<Ch3D::Primitive>> primitives;
		std::vector<ChPtr::Shared<Ch3D::MaterialData>>materialList;
		std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;
		std::vector<ChPtr::Shared<TargetBoneData>>boneDatas;
		std::map<std::string, unsigned long>mateNames;
		ChVec3 maxPos = ChVec3((10e+37f) * -1.0f);
		ChVec3 minPos = ChVec3(10e+37f);
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();
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

		friend ModelLoaderBase;

	public:

		inline void Init()override
		{
			SetInitFlg(true);
		}

		inline void Release()override
		{
			SetInitFlg(false);
		}

	public:

		inline void SetShaderAxisType(const Ch3D::ShaderAxisType _type)
		{
			axisType = _type;
		}

		void SetModelName(const std::string& _name);

	private:

		inline void SetMaxPos(const ChVec3& _pos) { maxPos = _pos; }

		inline void SetMinPos(const ChVec3& _pos) { minPos = _pos; }

		inline void SetCenterPos(const ChVec3& _pos) { centerPos = _pos; }

		inline void SetBoxSize(const ChVec3& _size) { boxSize = _size; }

	public:

		inline std::string GetModelName() 
		{
			return modelName; 
		}

		//初期化時に作成した全フレームの最大地点//
		inline ChVec3 GetInitAllFrameMaxPos() { return maxPos; }

		//初期化時に作成した全フレームの最小地点//
		inline ChVec3 GetInitAllFrameMinPos() { return minPos; }

		//初期化時に作成した全フレームの中央地点//
		inline ChVec3 GetInitAllFrameCenterPos() { return centerPos; }

		//初期化時に作成した全フレームの箱のサイズ//
		//CenterToTopLine And CenterToRightLine//
		inline ChVec3 GetInitAllFrameBoxSize() { return boxSize; }

	public:

		void AddAnimationName(const std::string& _name);

	public:

		virtual void Create(){}

	private:

		std::vector<std::string>animationNames;
		std::string modelName = "";

		ChVec3 maxPos = ChVec3();
		ChVec3 minPos = ChVec3();
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();

		Ch3D::ShaderAxisType axisType = Ch3D::ShaderAxisType::LeftHand;
	};

}

#endif