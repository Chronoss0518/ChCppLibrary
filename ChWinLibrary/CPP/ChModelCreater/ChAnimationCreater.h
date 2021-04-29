
#ifndef Ch_CPP_AMesh_h
#define Ch_CPP_AMesh_h

namespace ChCpp
{

	class ModelObject;

	class AnimationCreater
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		std::string& ModelNameIns();

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void CreateMesh(const std::string& _FilePath) {};

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void OutMeshFile(const std::string& _FilePath) {};

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;

	protected:

		void SetModel(ChPtr::Shared<ModelFrame> _Models);

	private:

		void Init(ModelObject* _Model);

		ModelObject* Model;

	};
}



#endif