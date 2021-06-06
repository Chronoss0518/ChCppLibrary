#ifndef Ch_CPP_FBXMesh_h
#define Ch_CPP_FBXMesh_h

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

			unsigned long filePos = 0;

			//Binarys//
			struct SpecialDataRecode
			{
				unsigned long Length;
				union
				{
					std::string string = "";
					std::vector<char> binary;

				};

				SpecialDataRecode(){}
				~SpecialDataRecode();

			};

			struct ArrayListDataRecord
			{
				unsigned long arrayLen = 0;
				unsigned long encoding = 0;
				unsigned long conpressedLength = 0;

				union
				{
					ChPtr::Shared<float> fData = nullptr;
					ChPtr::Shared<long double> dData;
					ChPtr::Shared<long long> lData;
					ChPtr::Shared<long> iData;
					ChPtr::Shared<unsigned char> bData;
				};

				ArrayListDataRecord(){}
				~ArrayListDataRecord();
			};

			struct PropertyRecord
			{
				char type = 0;

				union
				{
					ChPtr::Shared<short> YData = nullptr;
					ChPtr::Shared<unsigned char> bData;
					ChPtr::Shared<long> IData;
					ChPtr::Shared<float> FData;
					ChPtr::Shared<long double> DData;
					ChPtr::Shared<long long> LData;

					ChPtr::Shared<ArrayListDataRecord> arrayData;
					ChPtr::Shared<SpecialDataRecode> specialData;
				};

				PropertyRecord(){}
				~PropertyRecord();
			};

			struct Node
			{
				unsigned long endOffset = 0;
				unsigned long numProperty = 0;
				unsigned long propertyListLen = 0;
				unsigned char nameLen = 0;
				std::string name = "";
				std::vector<ChPtr::Shared<PropertyRecord>> propertys;
				std::vector<ChPtr::Shared<Node>> childNode;
			};

			//Texts//

			struct Objects
			{
				std::string propetyName = "";
				std::string propertyValue = "";
				std::vector<Objects*> childObject;
			};

			void LoadFBXBinary(const std::string& _filePath);

			void BuildBinary(Node& _node, std::vector<char>& _binarys);
			
			void CreatePropetyRecord(ChPtr::Shared<PropertyRecord>& _recode, std::vector<char>& _binarys);

			void CreateArrayRecord(ChPtr::Shared<ArrayListDataRecord>& _recode, std::vector<char>& _binarys);
			void CreateBaseTypeRecord(ChPtr::Shared<PropertyRecord>& _recode, std::vector<char>& _binarys);
			void CreateSpecialTypeRecord(ChPtr::Shared<SpecialDataRecode>& _recode, std::vector<char>& _binarys);

			void LoadFBXText(const std::string& _filePath);

			void BuildObjects(Objects& _obj);

			const char prefix[21] = { (char)0x4b,(char)0x61,(char)0x79,(char)0x64,(char)0x61,(char)0x72,(char)0x61,(char)0x20,(char)0x46,(char)0x42,(char)0x58,(char)0x20,(char)0x42,(char)0x69,(char)0x6e,(char)0x61,(char)0x72,(char)0x79,(char)0x20,(char)0x20,(char)0x00 };

			ChStd::Bool binaryFlg = false;

		};

	}

}

#endif