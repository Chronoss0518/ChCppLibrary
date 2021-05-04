
#ifndef Ch_CPP_MLoader_h
#define Ch_CPP_MLoader_h

namespace ChCpp
{

	class ModelObject;
	struct ModelFrame;

	class ModelLoaderBase
	{

	public:


		///////////////////////////////////////////////////////////////////////////////////////

		virtual void CreateModel(const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void OutModelFile(const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;

	protected:

		///////////////////////////////////////////////////////////////////////////////////////

		//カレントディレクトリからのルートパス取得//
		std::string GetRoutePath(const std::string& _filePath);

		///////////////////////////////////////////////////////////////////////////////////////

		void Init(ModelObject * _model);

		void SetModel(ChPtr::Shared<ModelFrame> _models);

	private:

		ModelObject* oModel;

	};
}


#endif