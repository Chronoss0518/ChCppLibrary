#ifndef Ch_CPP_3D_h
#define Ch_CPP_3D_h

#include<string>
#include<vector>
#include"ChMath.h"
#include"ChMath3D.h"

namespace Ch3D
{
	struct Position
	{
		ChVec3 pos;
	};

	struct UV
	{
		ChVec2 uv;
	};

	struct Color
	{
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct Normal
	{
		ChVec3 normal = ChVec3(0.0f,1.0f,0.0f);
	};

	struct FaceNormal
	{
		ChVec3 faceNormal = ChVec3(0.0f, 1.0f, 0.0f);
	};

	template<unsigned long Num>
	struct Bone
	{
		float brendPows[Num];
		unsigned long boneNo[Num];
	};

	struct HaveVertex:
		public Position,
		public Color
	{};

	struct Vertex:
		public Position,
		public UV,
		public Color
	{};

	struct PolyVertex :
		public Vertex,
		public Normal
	{};

	struct MeshVertex :
		public PolyVertex,
		public FaceNormal
	{};

	//ëŒè€ÇÃí∏ì_Çä«óùÇ∑ÇÈ//
	struct Polygon
	{
		 std::vector<unsigned long> vertexNo;
	};

	struct Material
	{
		ChVec4 diffuse = 1.0f;
		ChVec3 specularColor = 0.0f;
		float specularPower = 1.0f;
		ChVec4 ambient = 0.3f;
	};

	enum class TextureType
	{
		Diffuse,
		Ambient,
		Specular,
		SpecularHighLight,
		Bump,
		Alpha,
		Normal,
		Metallic
	};

	struct Transform
	{
		ChVec3 pos;
		ChVec3 rot;
		ChVec3 scl;

		inline ChLMat GetLeftHandMatrix()
		{
			ChLMat out;
			out.SetPosition(pos);
			out.SetRotation(rot);
			out.SetScalling(scl);
			return out;
		}

		inline ChRMat GetRightHandMatrix()
		{
			ChRMat out;
			out.SetPosition(pos);
			out.SetRotation(rot);
			out.SetScalling(scl);
			return out;
		}
	};

	//MaterialÇ…ëŒâûÇ∑ÇÈñ Çä«óùÇ∑ÇÈ//
	template<class vertex = Vertex>
	class Primitive
	{
		std::vector<ChPtr::Shared<Polygon>> polygons = nullptr;
		Vertex* vertexList = nullptr;

		Material mate;
	};

	template<class vertex = Vertex,class primitive = Primitive<vertex>>
	class Frame
	{
	public:

		std::vector<ChPtr::Shared<primitive>> primitives = nullptr;
		std::map<std::string, unsigned long>mateNames;
		Transform transform;

		std::vector<ChPtr::Shared<Frame<Vertex>>> parent;

	};



}

#endif