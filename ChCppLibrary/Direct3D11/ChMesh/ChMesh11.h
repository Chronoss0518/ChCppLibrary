#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

#include"../../CPP/ChBaseObject/ChBaseObject.h"

namespace ChD3D11
{

	class Texture11;
	class Mesh11;

	template<class vertex = Ch3D::Vertex>
	struct PrimitiveData11 :public ChCpp::BaseComponent
	{
		IndexBuffer11 indexBuffer;
		VertexBuffer11<vertex> vertexBuffer;

		typename std::enable_if<std::is_base_of<Ch3D::Vertex, vertex>::value, std::vector<vertex>>::type vertexArray;
		std::vector<unsigned long> indexArray;

		ChPtr::Shared<Material11> mate = nullptr;

	};

	struct BoneData11
	{
		unsigned long skinWeightCount = 0;
		ChMath::Vector3Base<unsigned long> tmpBuffer;
		ChMat_11 animationMat[96];

	};

	struct FrameData11
	{
		friend Mesh11;

		std::map<std::string,ChPtr::Shared<PrimitiveData11<SkinMeshVertex11>>>primitiveDatas;

		std::string frameName;

		ChMat_11 baseMat;
		ChMat_11 animationMat;

		ChPtr::Weak<FrameData11> parentFrame;

		std::vector<ChPtr::Shared<FrameData11>>childFrame;

		inline ChMat_11 GetDrawMatrix() { return drawMat; }

	private:

		ChMat_11 drawMat;

	};

	class Mesh11:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(ID3D11Device* _device);

		void Init();

		void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		inline ChStd::Bool IsMesh() const { return modelData != nullptr; }

		///////////////////////////////////////////////////////////////////////////////////////
		//Creater//

		virtual void Create(const ChCpp::ModelObject& _baseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _dc);

		void SetDrawData(ID3D11DeviceContext* _dc,const std::string& _frameName);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChPtr::Shared<FrameData11> GetRootFrame() { return modelData; }

		inline ChPtr::Shared<FrameData11> GetFrame(const std::string& _frameName)
		{
			return (frameNames.find(_frameName) != frameNames.end()) ? frameNames[_frameName].lock() : nullptr;
		}

		inline std::vector<std::string> GetFrameNames()
		{
			std::vector<std::string> out;

			for (auto&& frame : frameNames)
			{
				out.push_back(frame.first);
			}

			return out;
		}

		inline ID3D11Device* GetDevice() { return device; }

		ChMat_11 GetParentAnimationMatrixs(FrameData11& _frame);

	protected:

		void CreateFrames(
			ChPtr::Shared<FrameData11>& _frames
			, const ChCpp::ModelFrame::Frame& _baseModels);

		void CreatePrimitiveData(
			ChPtr::Shared<FrameData11>& _frames
			, const ChCpp::ModelFrame::Frame& _baseModels);

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
			CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _baseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void UpdateFrameDrawMatrix();

		///////////////////////////////////////////////////////////////////////////////////////

		using FrameName = std::string;
		using MaterialNo = unsigned long;
		using MaterialName = std::string;

		std::map<std::string,ChPtr::Weak<FrameData11>>frameNames;

		std::vector<ChPtr::Weak<FrameData11>>drawFrames;

		ChPtr::Shared<FrameData11> modelData = nullptr;

		ChMat_11* boneList = nullptr;

		ConstantBuffer11<ShaderUseMaterial11> materialBuffer;

	private:

		ChPtr::Shared<Texture11>whiteTex = nullptr;
		ChPtr::Shared<Texture11>normalTex = nullptr;

		ID3D11Device* device = nullptr;
	};

}

#endif