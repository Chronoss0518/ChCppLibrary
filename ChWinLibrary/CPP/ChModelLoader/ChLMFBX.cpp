#include"../../BaseIncluder/ChBase.h"

#include"../ChFile/ChFile.h"

#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"
#include"ChLMFBX.h"

using namespace ChCpp::ModelLoader;

void FBX::CreateModel(const std::string& _filePath)
{
	LoadFBXBinary(binarys);
}

///////////////////////////////////////////////////////////////////////////////////////

void FBX::OutModelFile(const std::string& _filePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void FBX::LoadFBXBinary(const std::string& _filePath)
{

	char* binarys = nullptr;

	{

		ChCpp::File<> file;
		file.FileOpen(_filePath, std::ios::in | std::ios::binary);

		binarys = file.FileReadBinary();

		file.FileClose();
	}

	binaryFlg = true;

	for (unsigned char i = 20; i >= 0; i--)
	{
		if (prefix[i] != binarys[i])continue;
		binaryFlg = false;
		break;
	}

	if (!binaryFlg)return;

	Node root;


}

///////////////////////////////////////////////////////////////////////////////////////

void FBX::LoadFBXText(const std::string& _filePath)
{

	if (binaryFlg)return;

	std::string text = "";

	{

		ChCpp::File<> file;
		file.FileOpen(_filePath, std::ios::in);

		text = file.FileReadText();

		file.FileClose();
	}

	Objects root;


}
