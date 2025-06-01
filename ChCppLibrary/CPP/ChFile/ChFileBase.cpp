#include"ChFileBase.h"
#include<filesystem>

void ChCpp::FileBase::FileOpenInit(const std::string& _fileName, const std::string& _localeName, bool _isUpdate)
{
	FileClose();

	localeName = _localeName;
	openFileNameChar = _fileName;

#ifdef _MSC_BUILD 
	openFileNameWChar = L"";
#endif
	isUpdateFlg = _isUpdate;
	if (std::filesystem::exists(_fileName))return;
	FILE* file = fopen(openFileNameChar.c_str(), "a");
	fclose(file);
}

#ifdef _MSC_BUILD 
void ChCpp::FileBase::FileOpenInit(const std::wstring& _fileName, const std::string& _localeName, bool _isUpdate)
{
	FileClose();

	localeName = _localeName;
	openFileNameWChar = _fileName;
	openFileNameChar = "";
	isUpdateFlg = _isUpdate;
	if (std::filesystem::exists(_fileName))return;
	FILE* file = _wfopen(openFileNameWChar.c_str(), L"a");
	fclose(file);
}
#endif

void ChCpp::FileBase::FileClose()
{
	if (!isUpdateFlg)return;

	FileCloseCharName();

#ifdef _MSC_BUILD 
	FileCloseWCharName();
#endif
}

FILE* ChCpp::Open(const std::string& _fileName, const std::string& _type)
{
	return fopen(_fileName.c_str(), _type.c_str());
}

#ifdef _MSC_BUILD 
FILE* ChCpp::Open(const std::wstring& _fileName, const std::wstring& _type)
{
	return _wfopen(_fileName.c_str(), _type.c_str());
}
#endif

template<> char ChCpp::FGet(FILE* _fp)
{
	return fgetc(_fp);
}

template<> wchar_t ChCpp::FGet(FILE* _fp)
{
	return fgetwc(_fp);
}

void ChCpp::FPut(FILE* _fp, const char _char)
{
	fputc(_char, _fp);
}

void ChCpp::FPut(FILE* _fp, const wchar_t _char)
{
	fputwc(_char, _fp);
}
