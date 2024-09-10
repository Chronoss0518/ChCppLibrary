#ifndef Ch_CPP_Model_h
#define Ch_CPP_Model_h


#ifdef CRT

#include<vector>
#include<map>
#include<string>

#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/Ch3D.h"

#include"../ChBaseObject/ChBaseComponent.h"
#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{
	class ModelAnimator :public BaseComponent
	{
	protected:

		ModelAnimator();

		virtual ~ModelAnimator();

	protected:

		float Speed = 0.1f;

		unsigned long AllAnimationCount = 0;

		struct AniDatas
		{
			ChVec3 Pos;
			ChQua Rot;
			ChVec3 Scal;
		};

		struct AnimationData
		{
			AniDatas Start;
			AniDatas End;
			unsigned long AnimationFrameCount = 0;
		};

	private:

		struct ModelAnimatorCRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<AnimationData>>Animation;
#endif
		};

	public:

		ModelAnimatorCRT& ValueIns() { return *value; }

	private:

		ModelAnimatorCRT* value = nullptr;

	};

	template<typename CharaType>
	struct ModelFrame
	{
		ModelFrame();

		virtual ~ModelFrame();

		struct VertexData
		{
			ChVec3 pos;
			ChVec3 normal;
			ChUIMat boneNo;
			ChLMat	blendPow;
		};

		struct Material
		{
			Material();

			virtual ~Material();

			ChVec4 diffuse = 1.0f;
			ChVec4 specular = 1.0f;
			ChVec4 ambient = 0.0f;

		private:

			struct MaterialCRT
			{
#ifdef CRT
				std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();
				std::vector<std::basic_string<CharaType>>textureNames;
#endif
			};

		public:

			MaterialCRT& ValueIns() { return *value; }

		private:

			MaterialCRT* value = nullptr;

		};

		struct SurFace
		{

			struct SurFaceVertex
			{
				size_t vertexNo = 0;
				ChVec2 uvPos;
			};


			SurFaceVertex vertexData[3];
			unsigned long materialNo = 0;
			ChVec3 normal;
		};

		struct Mesh
		{
			Mesh();

			virtual ~Mesh();

		private:

			struct MeshCRT
			{
#ifdef CRT
				std::vector<ChPtr::Shared<VertexData>>vertexList;
				std::vector<ChPtr::Shared<Material>>materialList;
				std::map<std::basic_string<CharaType>, unsigned long> materialNo;
				std::vector<ChPtr::Shared<SurFace>>faceList;
#endif
			};

		public:

			MeshCRT& ValueIns() { return *value; }

		private:

			MeshCRT* value = nullptr;

		};

		struct Frame
		{
			union
			{
				ChLMatrix baseLMat = ChLMat();
				ChRMatrix baseRMat;
			};

		private:

			struct FrameCRT
			{
#ifdef CRT
				std::basic_string<CharaType> myName = ChStd::GetZeroChara<CharaType>();
				ChPtr::Shared<Mesh>mesh = nullptr;
				ChPtr::Weak<Frame>parent;
				std::vector<ChPtr::Shared<Frame>>childFrames;
#endif
			};

		public:

			Frame();

			virtual ~Frame();

			FrameCRT& ValueIns() { return *value; }

		private:

			FrameCRT* value = nullptr;

		};

	private:

		struct ModelFrameCRT
		{
#ifdef CRT
			ChPtr::Shared<Frame>modelData = nullptr;
			std::basic_string<CharaType> modelName;
#endif
		};

	public:

		ModelFrameCRT& ValueIns() { return *value; }

	private:

		ModelFrameCRT* value = nullptr;

	};

}


#ifdef CRT

ChCpp::ModelAnimator::ModelAnimator()
{
	value = new ModelAnimatorCRT();
}

ChCpp::ModelAnimator::~ModelAnimator()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::ModelFrame()
{
	value = new ModelFrameCRT();
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::~ModelFrame()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::Material::Material()
{
	value = new MaterialCRT();
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::Material::~Material()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::Mesh::Mesh()
{
	value = new MeshCRT();
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::Mesh::~Mesh()
{
	delete value;
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::Frame::Frame()
{
	value = new FrameCRT();
}

template<typename CharaType>
ChCpp::ModelFrame<CharaType>::Frame::~Frame()
{
	delete value;
}

#endif

#endif
