#ifndef Ch_CPP_Model_h
#define Ch_CPP_Model_h

namespace ChCpp
{
	class ModelAnimator
	{
	protected:

		float Speed = 0.1f;

		unsigned long AllAnimationCount;

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
			unsigned long AnimationFrameCount;
		};

		std::vector<ChPtr::Shared<AnimationData>>Animation;

	};

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

		struct Material
		{
			std::string materialName = "";
			ChVec4 diffuse = 1.0f;
			ChVec4 specular =1.0f;
			ChVec4 ambient = 0.0f;
			std::vector<std::string>textureNames = std::vector<std::string>(0);

			//std::string diffuseMap;
			//std::string ambientMap;
			//std::string specularMap;
			//std::string specularHighLightMap;
			//std::string bumpMap;
			//std::string alphaMap;
			//std::string normalMap;
			//std::string metallicMap;

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

		struct Mesh
		{
			std::vector<ChPtr::Shared<VertexData>>vertexList;
			std::vector<ChPtr::Shared<Material>>materialList;
			std::map<std::string, unsigned long> materialNo;
			std::vector<ChPtr::Shared<SurFace>>faceList;

			inline ~Mesh()
			{
				faceList.clear();

				vertexList.clear();

				materialList.clear();
			}
		};

		struct Frame
		{
			union
			{
				ChLMatrix baseLMat = ChLMat();
				ChRMatrix baseRMat;
			};

			std::string myName = "";
			ChPtr::Shared<Mesh>mesh = nullptr;
			ChPtr::Weak<Frame>parent;
			std::vector<ChPtr::Shared<Frame>>childFrames;

			Frame()
			{

			}

			~Frame()
			{
				mesh = nullptr;
				childFrames.clear();
			}

		};


		struct BoneTrees
		{
			union
			{
				ChLMat baseLMat = ChLMat();
				ChRMat baseRMat;
			};

			ChPtr::Weak<BoneTrees> parentBone;
			std::vector<ChPtr::Shared<BoneTrees>>childBones;
		};

		std::map<std::string, unsigned long>boneNames;
		std::vector<ChPtr::Shared<BoneTrees>>boneList;

		ChPtr::Shared<Frame>modelData = nullptr;
		std::string modelName;

	};

}
#endif
