#ifndef Ch_CPP_3D_h
#define Ch_CPP_3D_h

#include<string>
#include<vector>
#include"ChMath.h"
#include"ChMath3D.h"

namespace Ch3D
{

	struct Vertex
	{
		ChVec3 pos;
		ChVec2 uv;
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct PolyVertex : public Vertex
	{
		ChVec3 normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct MeshVertex : public PolyVertex
	{
		ChVec3 faceNormal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct SkinMeshData
	{
		ChUIMat boneNo;
		ChLMat bonePow;
		unsigned long blendNum = 0;
	};

	//‘ÎÛ‚Ì’¸“_‚ğŠÇ—‚·‚é//
	struct Polygon
	{
		 std::vector<unsigned long> vertexNo;
	};

	struct Material
	{
		ChVec4 diffuse = ChVec4();
		ChVec4 specular = ChVec4();
		ChVec4 ambient = ChVec4();
	};

	struct MaterialStatus
	{
		Material mate;

		std::string diffuseMap = "";
		std::string ambientMap = "";
		std::string specularMap = "";
		std::string specularHighLightMap = "";
		std::string bumpMap = "";
		std::string alphaMap = "";
		std::string normalMap = "";
		std::string metallicMap = "";
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