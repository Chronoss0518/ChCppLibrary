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
	class ModelAnimator:public BaseComponent
	{
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
#ifdef CRT
		std::vector<ChPtr::Shared<AnimationData>>Animation;
#endif
	};

	template<typename CharaType>
	struct ModelFrame
	{
		///////////////////////////////////////////////////////////////////////////////////////
		//MeshDataStruct//

		struct VertexData
		{
			ChVec3 pos;
			ChVec3 normal;
			ChUIMat boneNo;
			ChLMat	blendPow;
		};

		template<typename CharaType>
		struct Material
		{
			ChVec4 diffuse = 1.0f;
			ChVec4 specular =1.0f;
			ChVec4 ambient = 0.0f;

#ifdef CRT
			std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();
			std::vector<std::basic_string<CharaType>>textureNames;
#endif
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
			
			inline ~SurFace()
			{

			}
		};

		template<typename CharaType>
		struct Mesh
		{
#ifdef CRT
			std::vector<ChPtr::Shared<VertexData>>vertexList;
			std::vector<ChPtr::Shared<Material<CharaType>>>materialList;
			std::map<std::basic_string<CharaType>, unsigned long> materialNo;
			std::vector<ChPtr::Shared<SurFace>>faceList;
#endif

			~Mesh()
			{
#ifdef CRT
				faceList.clear();
				vertexList.clear();
				materialList.clear();
#endif
			}
		};

		template<typename CharaType>
		struct Frame
		{
			union
			{
				ChLMatrix baseLMat = ChLMat();
				ChRMatrix baseRMat;
			};

#ifdef CRT
			std::basic_string<CharaType> myName = ChStd::GetZeroChara<CharaType>();
			ChPtr::Shared<Mesh<CharaType>>mesh = nullptr;
			ChPtr::Weak<Frame<CharaType>>parent;
			std::vector<ChPtr::Shared<Frame<CharaType>>>childFrames;
#endif

			~Frame()
			{
#ifdef CRT
				mesh = nullptr;
				childFrames.clear();
#endif
			}

		};

#ifdef CRT
		ChPtr::Shared<Frame<CharaType>>modelData = nullptr;
		std::basic_string<CharaType> modelName;
#endif
	};

}
#endif
