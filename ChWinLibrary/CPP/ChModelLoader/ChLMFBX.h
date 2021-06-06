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

			//モデルデータの読み込み口//
			void CreateModel(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////

			void OutModelFile(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////

			void LoadFBXBinary(const std::string& _filePath);

			void LoadFBXText(const std::string& _filePath);


			const char prefix[21] = { (char)0x4b,(char)0x61,(char)0x79,(char)0x64,(char)0x61,(char)0x72,(char)0x61,(char)0x20,(char)0x46,(char)0x42,(char)0x58,(char)0x20,(char)0x42,(char)0x69,(char)0x6e,(char)0x61,(char)0x72,(char)0x79,(char)0x20,(char)0x20,(char)0x00 };

			ChStd::Bool binaryFlg = false;

			//Binarys//
			struct SpecialDataRecode
			{
				unsigned long Length;
				union
				{
					char* binary = nullptr;
					char* string;

				};
			};

			struct ArrayListDataRecord
			{
				unsigned long arrayLen = 0;
				unsigned long encoding = 0;
				unsigned long conpressedLength = 0;

				union
				{
					float* fData = nullptr;
					long double* dData;
					long long* lData;
					long* iData;
					unsigned char* bData;
				};
			};

			struct PropertyRecord
			{
				char type = 0;

				union
				{
					short* YData = nullptr;
					unsigned char* bData;
					long* IData;
					float* FData;
					long double* DData;
					long long* LData;
					
					ArrayListDataRecord* arrayData;

					SpecialDataRecode* specialData;
				};
			};

			struct Node
			{
				unsigned long endOffset = 0;
				unsigned long numProperty = 0;
				unsigned long propertyListLen = 0;
				unsigned char nameLen = 0;
				char* name = nullptr;
				PropertyRecord* propertys = nullptr;
				Node* childNode = nullptr;
			};

			//Texts//

			struct Objects
			{
				char* propetyName = nullptr;
				char* propertyValue = nullptr;
				Objects* childObject = nullptr;
			};


		};

	}

}

#endif