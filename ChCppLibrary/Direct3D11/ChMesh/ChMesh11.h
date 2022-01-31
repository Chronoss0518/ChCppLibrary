#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	class Texture11;
	class Mesh11;

	struct FrameData11 :public ChCp::Releaser
	{

		std::map<std::string,ChPtr::Shared<PrimitiveData11<SkinMeshVertex11>>>primitiveDatas;

		std::string frameName;

		ChMat_11 baseMat;
		ChMat_11 animationMat;
		ChMat_11 toWorldMat;

		ChPtr::Weak<FrameData11> parentFrame;

		std::vector<ChPtr::Shared<FrameData11>>childFrame;

		unsigned long primitiveCount = 0;

		std::vector<std::string>boneNameAddOrderList;
		std::map<std::string,ChPtr::Shared<ChMat_11>>skinDataList;

		BoneData11 boneData;

	};

	class Mesh11:public DrawObject
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
		//SetFunction//

		void SetDrawData(ID3D11DeviceContext* _dc);

		void SetDrawData(ID3D11DeviceContext* _dc,const std::string& _frameName);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::map<std::string, ChPtr::Shared<FrameData11>>& GetFrameNames()
		{
			return frameNames;
		}

	protected:

		///////////////////////////////////////////////////////////////////////////////////////

		void CreateFrames(
			ChPtr::Shared<FrameData11>& _frames
			, const ChCpp::ModelFrame::Frame& _baseModels
			, const ChMat_11& _parentMat = ChMat_11());

		void CreatePrimitiveData(
			ChPtr::Shared<FrameData11>& _frames
			, const ChCpp::ModelFrame::Frame& _baseModels);

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
			CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _baseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void UpdateFrame(ID3D11DeviceContext* _dc);

		///////////////////////////////////////////////////////////////////////////////////////

		ChMat_11 UpdateAnimation(const ChPtr::Shared<FrameData11>& _frame);

		///////////////////////////////////////////////////////////////////////////////////////

		using FrameName = std::string;
		using MaterialNo = unsigned long;
		using MaterialName = std::string;

		std::map<std::string,ChPtr::Shared<FrameData11>>frameNames;
		//std::map<std::string, ChPtr::Shared<FrameData11>>boneNames;

		std::vector<ChPtr::Shared<FrameData11>>frameList;

		ChPtr::Shared<FrameData11> modelData = nullptr;

	protected:

		ChPtr::Shared<Texture11>whiteTex = nullptr;
		ChPtr::Shared<Texture11>normalTex = nullptr;

		ConstantBuffer11<ShaderUseMaterial11>mateBuffer;
		ConstantBuffer11<BoneData11> boneData;
	};

}

#endif