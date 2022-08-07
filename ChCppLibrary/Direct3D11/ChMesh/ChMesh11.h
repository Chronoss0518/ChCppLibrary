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

		//unsigned long startNum = 0;
		unsigned char mateNo = 0;
		ChLMat drawMat;

		std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
	};

	class FrameComponent11 :public ChCpp::BaseComponent
	{
	public:

		//�q�I�u�W�F�N�g���ׂĂ��쐬����B//
		void CreateAll(ID3D11Device* _device);

		void UpdateDrawMatrix();

		void SetPrimitives(ChPtr::Shared<DrawPrimitiveData11> _primitive)
		{
			primitives.push_back(_primitive);
		}

		std::vector<ChPtr::Shared<DrawPrimitiveData11>> GetPrimitives()
		{
			return primitives;
		}

		ChCpp::FrameComponent* GetFrameCom() { return frameCom; }

	private:

		ChCpp::FrameComponent* frameCom = nullptr;
		std::vector<ChPtr::Shared<DrawPrimitiveData11>>primitives;

	};

	class Mesh11:public ChCpp::ModelObject,public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(ID3D11Device* _device);

		void Init();

		void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//Creater//

		void Create();

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