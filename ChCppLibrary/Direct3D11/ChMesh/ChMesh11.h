#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

#include"../../CPP/ChBaseObject/ChBaseObject.h"

namespace ChD3D11
{

	class Texture11;
	class Mesh11;

	struct  DrawPrimitiveData11
	{
		~DrawPrimitiveData11()
		{
			vertexBuffer.Release();
			indexBuffer.Release();
		}

		IndexBuffer11 indexBuffer;
		VertexBuffer11<Ch3D::MeshVertex> vertexBuffer;

		std::vector<Ch3D::MeshVertex> vertexArray;
		std::vector<unsigned long> indexArray;

		ChPtr::Shared<Ch3D::MaterialData> mate;

		ChLMat drawMat;

		std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
	};

	class FrameComponent11 :public ChCpp::BaseComponent
	{
	public:

		//子オブジェクトすべてを作成する。//
		void CreateAll(ID3D11Device* _device);

		void SetPrimitives(ChPtr::Shared<DrawPrimitiveData11> _primitive)
		{
			primitives.push_back(_primitive);
		}

		std::vector<ChPtr::Shared<DrawPrimitiveData11>>& GetPrimitives()
		{
			return primitives;
		}

		ChCpp::FrameComponent* GetFrameCom() { return frameCom; }
		std::vector<ChPtr::Shared<Ch3D::MaterialData>>& GetMaterialList() { return mateList; }
	private:
		std::vector<ChPtr::Shared<Ch3D::MaterialData>> mateList;
		ChCpp::FrameComponent* frameCom = nullptr;
		std::vector<ChPtr::Shared<DrawPrimitiveData11>>primitives;

	};

	class Mesh11:public ChCpp::ModelObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(ID3D11Device* _device);

		void Init()override;

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//Creater//

		void Create()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ID3D11Device* GetDevice() { return device; }

	protected:

		void CreateFrames();

		///////////////////////////////////////////////////////////////////////////////////////

		using FrameName = std::string;
		using MaterialNo = unsigned long;
		using MaterialName = std::string;

	private:

		ID3D11Device* device = nullptr;
	};

}

#endif