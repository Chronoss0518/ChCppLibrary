#include"ChBinaryFile.h"

void ChCpp::BinaryFile::FileOpen(const std::string& _fileName, const std::string& _localeName, bool _isUpdate)
{
	if (_fileName.length() <= 0)return;
	FileOpenInit(_fileName, _localeName, _isUpdate);

	std::string tmpLocale = "";
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());

	FILE* file = Open(openFileNameChar.c_str(), "rb");
	if (!datas.empty())datas.clear();
	while (feof(file) != 1)
	{
		datas.push_back(fgetc(file));
	}
	fclose(file);
	if (localeName != "")setlocale(LC_ALL, tmpLocale.c_str());
}

#ifdef _MSC_BUILD 
void ChCpp::BinaryFile::FileOpen(const std::wstring& _fileName, const std::string& _localeName, bool _isUpdate)
{
	if (_fileName.length() <= 0)return;
	FileOpenInit(_fileName, _localeName, _isUpdate);

	std::string tmpLocale = "";
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());

	FILE* file = Open(openFileNameWChar.c_str(), L"rb");

	if (!datas.empty())datas.clear();
	while (feof(file) != 1)
	{
		datas.push_back(fgetc(file));
	}
	fclose(file);
	if (localeName != "")setlocale(LC_ALL, tmpLocale.c_str());
}
#endif
std::vector<unsigned char> ChCpp::BinaryFile::FileRead()
{
	return datas;
}

std::vector<unsigned char> ChCpp::BinaryFile::FileWrite(const std::vector<unsigned char>& _writeData)
{
	datas.clear();
	for (auto&& data : _writeData)
		datas.push_back(data);
	return datas;
}

void ChCpp::BinaryFile::FileCloseCharName()
{
	if (openFileNameChar == "")return;

	std::string tmpLocale = "";
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());

	FILE* file = Open(openFileNameChar.c_str(), "wb");

	for (size_t i = 0; i < datas.size(); i++)FPut(file, static_cast<char>(datas[i]));
	fclose(file);

	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str());
	openFileNameChar = "";
}

#ifdef _MSC_BUILD 
void ChCpp::BinaryFile::FileCloseWCharName()
{
	if (openFileNameWChar == L"")return;

	std::string tmpLocale = "";
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());

	FILE* file = Open(openFileNameWChar.c_str(), L"wb");

	for (size_t i = 0; i < datas.size(); i++)FPut(file, static_cast<char>(datas[i]));
	fclose(file);

	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str());
	openFileNameWChar = L"";
}
#endif