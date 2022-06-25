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
		ChVec3 normal;
	};

	struct FaceNormal
	{
		ChVec3 faceNormal;
	};

	template<unsigned long Num>
	struct Bone
	{
		float brendPows[Num];
		unsigned long boneNo[Num];
	};

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

	//‘ÎÛ‚Ì’¸“_‚ğŠÇ—‚·‚é//
	struct Polygon
	{
		 std::vector<unsigned long> vertexNo;
	};

	struct Material
	{
		ChVec4 diffuse = 1.0f;
		ChVec4 specular = 0.0f;
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

	struct MaterialStatus
	{
		Material mate;

		std::map<TextureType, std::string>texture;
	};

	//Material‚É‘Î‰‚·‚é–Ê‚ğŠÇ—‚·‚é//
	template<class vertex = Vertex>
	class Primitive
	{

		std::vector<ChPtr::Shared<Polygon>> polygons = nullptr;
		Vertex* vertexList = nullptr;

		MaterialStatus mate;
	};

	template<class vertex = Vertex,class primitive = Primitive<vertex>>
	class Frame
	{
	public:

		std::vector<ChPtr::Shared<primitive>> primitives = nullptr;
		std::map<std::string, unsigned long>mateNames;

		std::vector<ChPtr::Shared<Frame<Vertex>>> parent;

	};



}

#endif