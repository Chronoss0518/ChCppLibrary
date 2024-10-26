#include<stdio.h>
#include<locale.h>
#include<wchar.h>
#include"ChFile.h"

#define METHOD_EXPLICIT_DECLARATION(_CharaType,_AddType,_ReadType,_WriteType,_AddValue)\
template<> void ChCpp::File<##_CharaType##>::FileOpen(\
	const std::string& _fileName,\
	const std::string& _localeName,\
	const bool _isUpdate){\
	if (_fileName.length() <= 0)return;\
\
	localeName = _localeName;\
	openFileNameChar = _fileName;\
\
	std::string tmpLocale = "";\
	if (_localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameChar.c_str(), _AddType##);\
	fclose(file);\
	file = Open(openFileNameChar.c_str(), _ReadType##);\
	fseek(file, 0, SEEK_END);\
	fpos_t filepos = 0;\
	fgetpos(file, &filepos);\
	fseek(file, 0, SEEK_SET);\
	fileText = ChStd::GetZeroChara<##_CharaType##>();\
	for (fpos_t pos = (##_AddValue - 1); pos < filepos; pos += _AddValue##)fileText += FGet<##_CharaType##>(file);\
	fclose(file);\
	isUpdateFlg = _isUpdate;\
\
	if (_localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
template<>	void ChCpp::File<##_CharaType##>::FileOpen(\
	const std::wstring& _fileName,\
	const std::string& _localeName,\
	const bool _isUpdate){\
	if (_fileName.length() <= 0)return;\
\
	localeName = _localeName;\
	openFileNameWChar = _fileName;\
\
	std::string tmpLocale = "";\
	if (_localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameWChar.c_str(), L##_AddType##);\
	fclose(file);\
	file = Open(openFileNameWChar.c_str(), L##_ReadType##);\
	fseek(file, 0, SEEK_END);\
	fpos_t filepos = 0;\
	fgetpos(file, &filepos);\
	fseek(file, 0, SEEK_SET);\
	fileText = ChStd::GetZeroChara<##_CharaType##>();\
	for (fpos_t pos = (##_AddValue - 1); pos < filepos; pos += _AddValue##)fileText += FGet<##_CharaType##>(file);\
	fclose(file);\
	isUpdateFlg = _isUpdate;\
\
	if (_localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
template<> void ChCpp::File<##_CharaType##>::FileCloseCharName(){\
	if (openFileNameChar == "")return;\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str()); \
\
	FILE* file = Open(openFileNameChar.c_str(), _WriteType##);\
	fileText = fileText.c_str();\
	for (size_t i = 0; i < fileText.size(); i++)FPut(file, fileText[i]);\
	fclose(file);\
\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str()); }\
template<> void ChCpp::File<##_CharaType##>::FileCloseWCharName(){\
	if (openFileNameWChar == L"")return;\
\
	std::string tmpLocale = ""; \
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str()); \
\
	FILE* file = Open(openFileNameWChar.c_str(), L##_WriteType##);\
	fileText = fileText.c_str();\
	for (size_t i = 0; i < fileText.size(); i++)FPut(file, fileText[i]);\
	fclose(file);\
\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str());}



FILE* Open(const std::string& _fileName, const std::string& _type);

FILE* Open(const std::wstring& _fileName, const std::wstring& _type);

template<typename OutCharaType>
OutCharaType FGet(FILE* _fp);

void FPut(FILE* _fp, const char _char);

void FPut(FILE* _fp, const wchar_t _char);


FILE* Open(const std::string& _fileName, const std::string& _type)
{
	return fopen(_fileName.c_str(), _type.c_str());
}

FILE* Open(const std::wstring& _fileName, const std::wstring& _type)
{
	return _wfopen(_fileName.c_str(), _type.c_str());
}

template<> char FGet(FILE* _fp)
{
	return fgetc(_fp);
}

template<> wchar_t FGet(FILE* _fp)
{
	return fgetwc(_fp);
}

void FPut(FILE* _fp, const char _char)
{
	fputc(_char, _fp);
}

void FPut(FILE* _fp, const wchar_t _char)
{
	fputwc(_char, _fp);
}



namespace ChStd
{
	CH_TO_NUMBER_FUNCTION(CH_ERROR_TEXT_TYPE_FUNCTION, ".txt");
}

template<typename CharaType>
size_t ChCpp::File<CharaType>::GetLength()
{
	return fileText.size();
}

template<typename CharaType>
void ChCpp::File<CharaType>::FileClose()
{
	if (!isUpdateFlg)return;
	FileCloseCharName();
	FileCloseWCharName();
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::File<CharaType>::FileRead()
{
	return fileText;
}

//FileÇ…èëÇ´çûÇﬁ//
template<typename CharaType>
std::basic_string<CharaType> ChCpp::File<CharaType>::FileWrite(const std::basic_string<CharaType>& _writeStr)
{
	fileText = _writeStr;
	return fileText;
}

METHOD_EXPLICIT_DECLARATION(char, "a", "r", "w", 1);
METHOD_EXPLICIT_DECLARATION(wchar_t, "a", "rb", "wb", 2);



CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::File);
