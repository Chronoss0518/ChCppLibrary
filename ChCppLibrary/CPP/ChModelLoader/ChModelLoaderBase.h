
#ifndef Ch_CPP_MLBase_h
#define Ch_CPP_MLBase_h

namespace ChCpp
{
	class ModelObject;
	class FrameObject;
	struct ModelFrame;

	class ModelLoaderBase
	{

	protected:
		
		void Init();

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void CreateModel(ChPtr::Shared<ModelObject> _model, const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void OutModelFile(const ChPtr::Shared<ModelObject> _model, const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;
		friend FrameObject;

	protected:

		void SetMaxPos(ModelObject& _model, const ChVec3& _pos);

		void SetMinPos(ModelObject& _model, const ChVec3& _pos);

		void SetCenterPos(ModelObject& _model, const ChVec3& _pos);

		void SetBoxSize(ModelObject& _model, const ChVec3& _size);

	protected:

		//カレントディレクトリからのルートパス取得//
		std::string GetRoutePath(const std::string& _filePath);

	protected:

		ChVec3 TestMaxPos(const ChVec3& _pos1, const ChVec3& _pos2);

		ChVec3 TestMinPos(const ChVec3& _pos1, const ChVec3& _pos2);

	protected:

		ChVec3 CreateCenterPos(const ChVec3& _min, const ChVec3& _max);

		//CenterToTopLine And CenterToRightLine//
		ChVec3 CreateBoxSize(const ChVec3& _min, const ChVec3& _max);

	protected:

		ChVec3 maxPos = ChVec3();
		ChVec3 minPos = ChVec3(1e+38f);

	};
}


#endif