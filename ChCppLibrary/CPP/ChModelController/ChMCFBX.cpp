#include"../../BaseIncluder/ChBase.h"

#include"../ChFile/ChFile.h"

#include"../ChModel/ChModelObject.h"

#include"ChModelControllerBase.h"
#include"ChMCFBX.h"

using namespace ChCpp::ModelController;

///////////////////////////////////////////////////////////////////////////////////////
//ChFBXMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)
{
	LoadFBXBinary(_filePath);

	LoadFBXText(_filePath);
}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::OutModelFile(const ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath)
{

}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::LoadFBXBinary(const std::string& _filePath)
{

	std::vector<char> binarys;

	{

		ChCpp::CharFile file;
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

	filePos = 27;

	while (binarys.size() > filePos)
	{
		if (errorFlg)return;

		auto node = ChPtr::Make_S<Node>();

		BuildBinary(*node, binarys);

		root.childNode.push_back(node);
	}


	if (errorFlg)return;

}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::BuildBinary(Node& _node, const std::vector<char>& _binarys)
{
	if (errorFlg)return;

	_node.endOffset = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;
	_node.numProperty = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;
	_node.propertyListLen = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;
	_node.nameLen = ChStd::BinaryToNumWithLittleEndian<unsigned char>(_binarys, filePos);
	filePos += 1;

	for (unsigned long i = 0; i < _node.nameLen; i++)
	{
		_node.name += _binarys[i + filePos];
	}

	filePos += _node.nameLen;

	for (unsigned long i = 0; i < _node.numProperty; i++)
	{
		if (errorFlg)return;

		auto propertyObj = ChPtr::Make_S< PropertyRecord>();

		CreatePropetyRecord(*propertyObj, _binarys);

		_node.propertys.push_back(propertyObj);
	}

	while (_node.endOffset - 13 > filePos)
	{
		if (errorFlg)return;

		auto node = ChPtr::Make_S<Node>();

		BuildBinary(*node, _binarys);

		_node.childNode.push_back(node);
	}

	filePos = _node.endOffset;

}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::CreatePropetyRecord(PropertyRecord& _recode, const std::vector<char>& _binarys)
{

	if (errorFlg)return;

	_recode.type = _binarys[filePos];
	filePos += 1;

	switch (_recode.type)
	{
	case 'Y':
	{
		MakeBaseType<short, FBXIntegerByte2>(_recode, _binarys, filePos); break;
	}
	case 'C':
	{
		MakeBaseType<unsigned char, FBXIntegerByte1>(_recode, _binarys, filePos); break;
	}
	case 'I':
	{
		MakeBaseType<long, FBXIntegerByte4>(_recode, _binarys, filePos); break;
	}
	case 'F':
	{
		MakeBaseType<float, FBXFloatingByte4>(_recode, _binarys, filePos); break;
	}
	case 'D':
	{
		MakeBaseType<double, FBXFloatingByte8>(_recode, _binarys, filePos); break;
	}
	case 'L':
	{
		MakeBaseType<long long, FBXIntegerByte8>(_recode, _binarys, filePos); break;
	}
	case 'f':
	case 'd':
	case 'l':
	case 'i':
	case 'b':
	{
		auto arrayRecode = ChPtr::Make_S<ArrayListDataRecord>();
		CreateArrayRecord(*arrayRecode, _binarys, _recode.type);
		_recode.arrayData = arrayRecode;
		break;
	}
	case 'S':
	case 'R':
	{
		auto specialRecode = ChPtr::Make_S<SpecialDataRecode>();
		CreateSpecialTypeRecord(*specialRecode, _binarys, _recode.type);
		_recode.specialData = specialRecode;
		break;
	}
	default:
		errorFlg = true;
		break;
	}

}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::CreateArrayRecord(ArrayListDataRecord& _recode, const std::vector<char>& _binarys, const char _type)
{

	if (errorFlg)return;

	_recode.arrayLen = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;

	_recode.encoding = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;

	_recode.conpressedLength = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;

	switch (_type)
	{
	case 'b':
	{
		MakeArrayType<unsigned char, FBXIntegerByte1>(_recode, _binarys, filePos); break;
	}
	case 'i':
	{
		MakeArrayType<long, FBXIntegerByte4>(_recode, _binarys, filePos); break;
	}
	case 'f':
	{
		MakeArrayType<float, FBXFloatingByte4>(_recode, _binarys, filePos); break;
	}
	case 'd':
	{
		MakeArrayType<double, FBXFloatingByte8>(_recode, _binarys, filePos); break;
	}
	case 'l':
	{
		MakeArrayType<long long, FBXIntegerByte8>(_recode, _binarys, filePos); break;
	}
	default:
		break;
	}

}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::CreateSpecialTypeRecord(SpecialDataRecode& _recode, const std::vector<char>& _binarys, const char _type)
{

	if (errorFlg)return;


	_recode.length = ChStd::BinaryToNumWithLittleEndian<unsigned long>(_binarys, filePos);
	filePos += 4;

	switch (_type)
	{
	case 'S':
	{
		_recode.value = MakeSpecialType<FBXString>(_recode.length, _binarys, filePos); break;
	}
	case 'R':
	{
		_recode.value = MakeSpecialType<FBXBinary>(_recode.length, _binarys, filePos); break;
	}
	default:
		break;
	}

}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::LoadFBXText(const std::string& _filePath)
{

	if (binaryFlg)return;

	std::string text = "";

	{

		ChCpp::CharFile file;
		file.FileOpen(_filePath, std::ios::in);

		text = file.FileReadText();

		file.FileClose();
	}

	Objects root;


}

template<typename CharaType>
void ChCpp::ModelController::FBX<CharaType>::BuildObjects(Objects& _obj)
{

}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::ModelController::FBX);
