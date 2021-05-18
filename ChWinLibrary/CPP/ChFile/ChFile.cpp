#include"../../BaseIncluder/ChBase.h"

#include"ChFile.h"


using namespace ChCpp;

void File::OutToErrorText(
	const std::string& _errorName
	, const std::string& _errorDitails
	, const OTEAddType _addFlg)
{
	File outFiles;
	std::string outData = "";
	std::string outFileName = "";
	outFileName = _errorName + ".txt";
	outFiles.FileOpen(outFileName);

	if (_addFlg == OTEAddType::All)
	{
		outData = outFiles.FileRead();
		outData = outData + "\n";
	}

	if (_addFlg == OTEAddType::AfterFirst)
	{
		static ChStd::Bool Flgs = false;
		if (Flgs)
		{
			outData = outFiles.FileRead();
			outData = outData + "\n";
		}
		Flgs = true;
	}

	outData = outData + _errorDitails;

	outFiles.FileWrite(outData);

	return;
}

///////////////////////////////////////////////////////////////////////////////////

void File::FileOpen(
	const std::string& _fileName
	, unsigned int _openMode)
{
	if (_fileName.length() <= 0)return;

	if (_openMode & std::ios::in)
	{

		std::ofstream tmp;
		tmp.open(_fileName, std::ios::app);
		tmp.close();
	}

	flg = _openMode;
	openFileName = _fileName;
	stream.open(_fileName, flg);
}

///////////////////////////////////////////////////////////////////////////////////

std::string File::FileRead()
{
	std::string out = "";

	if (!stream.is_open())return out;

	std::stringstream tmpSS;

	tmpSS << stream.rdbuf();

	out = tmpSS.str();

	stream.clear();
	stream.seekp(std::ios::beg, static_cast<std::ios_base::seekdir>(0));

	return out;

}

