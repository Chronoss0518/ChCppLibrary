#include"../../BaseIncluder/ChBase.h"

#include"../ChFile/ChFile.h"

#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"
#include"ChLMFBX.h"

using namespace ChCpp::ModelLoader;

void FBX::CreateModel(const std::string& _filePath)
{
	LoadFBXBinary(_filePath);

	LoadFBXText(_filePath);
}

///////////////////////////////////////////////////////////////////////////////////////

void FBX::OutModelFile(const std::string& _filePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void FBX::LoadFBXBinary(const std::string& _filePath)
{

	std::vector<char> binarys;

	{

		ChCpp::File<> file;
		file.FileOpen(_filePath, std::ios::in | std::ios::binary);

		file.FileReadBinary(binarys);

		file.FileClose();
	}

	binaryFlg = true;

	for (char i = 20; i >= 0; i--)
	{
		if (prefix[i] == binarys[i])continue;
		binaryFlg = false;
		break;
	}

	if (!binaryFlg)return;

	Node root;

	BuildBinary(root, binarys);

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

///////////////////////////////////////////////////////////////////////////////////////

void FBX::BuildBinary(Node& _node, std::vector<char>& _binarys)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void FBX::BuildObjects(Objects& _obj)
{

}