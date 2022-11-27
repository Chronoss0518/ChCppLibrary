
#ifndef Ch_CPP_MLBase_h
#define Ch_CPP_MLBase_h

namespace ChCpp
{
	class ModelObject;
	class FrameObject;
	class ModelObject;
	struct ModelFrame;

	class ModelLoaderBase
	{

	public:


		///////////////////////////////////////////////////////////////////////////////////////

		virtual void CreateModel(ModelObject& _model, const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void OutModelFile(const ModelObject& _model, const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;
		friend FrameObject;

	protected:

		//カレントディレクトリからのルートパス取得//
		std::string GetRoutePath(const std::string& _filePath);

	private:

	};
}


#endif