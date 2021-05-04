#ifndef Ch_CPP_ObjMesh_h
#define Ch_CPP_ObjMesh_h

#ifndef Ch_CPP_MLoader_h
#include"ChModelLoader.h"
#endif


namespace ChCpp
{

	class TextObject;

	namespace ModelLoader
	{

		class FBX :public ModelLoaderBase
		{
		protected:

			///////////////////////////////////////////////////////////////////////////////////////

			//���f���f�[�^�̓ǂݍ��݌�//
			void CreateModel(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////

			void OutModelFile(const std::string& _filePath)override;

		};

	}

}

#endif