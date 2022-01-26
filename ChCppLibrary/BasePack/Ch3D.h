#ifndef Ch_CPP_3D_h
#define Ch_CPP_3D_h

#include<string>
#include<vector>
#include"ChMath.h"
#include"ChMath3D.h"

namespace Ch3D
{

	struct DrawVertex
	{
		ChVec3 pos;
		ChVec2 uv;
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct DrawPolyVertex : public DrawVertex
	{
		ChVec3 normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct DrawMeshVertex : public DrawPolyVertex
	{
		ChVec3 faceNormal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct Vertex
	{
		ChVec3 pos;
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


	struct PolygonVertexData
	{
		unsigned long no = 0;
		ChVec2 uv = ChVec2();
	};

	//ëŒè€ÇÃí∏ì_Çä«óùÇ∑ÇÈ//
	struct Polygon
	{
		 std::vector<ChPtr::Shared<PolygonVertexData>> vertexNo;
	};

	struct TryPolygon
	{
		PolygonVertexData vertexNo[3];
	};

	struct Material
	{
		ChVec4 diffuse = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 specular = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 ambient = ChVec4(0.3f, 0.3f, 0.3f, 1.0f);
	};

	class CreateCallBack
	{
	protected:

		virtual void onCreate() {}
	};

	//MaterialÇ…ëŒâûÇ∑ÇÈñ Çä«óùÇ∑ÇÈ//
	template<class vertex = Vertex>
	class Primitive :public CreateCallBack
	{

		std::vector<ChPtr::Shared<Polygon>> polygons = nullptr;
		Vertex* vertexList = nullptr;

		virtual void onCreated() = 0;

		Material mate;


	};

	template<class vertex = Vertex,class primitive = Primitive<vertex>>
	class Frame :public CreateCallBack
	{
	public:

		std::vector<ChPtr::Shared<primitive>> primitives = nullptr;
		std::map<std::string, unsigned long>mateNames;

		std::vector<ChPtr::Shared<Frame<Vertex>>> parent;

	};



}

#endif