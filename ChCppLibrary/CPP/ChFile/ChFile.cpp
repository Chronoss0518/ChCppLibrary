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
	FileOpenInit(_fileName,_localeName,_isUpdate);\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameChar.c_str(), _ReadType##);\
	fseek(file, 0, SEEK_END);\
	fpos_t filepos = 0;\
	fgetpos(file, &filepos);\
	fseek(file, 0, SEEK_SET);\
	fileText = ChStd::GetZeroChara<##_CharaType##>();\
	for (fpos_t pos = 0; pos < filepos; pos += _AddValue##)fileText += FGet<##_CharaType##>(file);\
	fclose(file);\
\
	if (localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
template<>	void ChCpp::File<##_CharaType##>::FileOpen(\
	const std::wstring& _fileName,\
	const std::string& _localeName,\
	const bool _isUpdate){\
	if (_fileName.length() <= 0)return;\
	FileOpenInit(_fileName,_localeName,_isUpdate);\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameWChar.c_str(), L##_ReadType##);\
	fseek(file, 0, SEEK_END);\
	fpos_t filepos = 0;\
	fgetpos(file, &filepos);\
	fseek(file, 0, SEEK_SET);\
	fileText = ChStd::GetZeroChara<##_CharaType##>();\
	for (fpos_t pos = 0; pos < filepos; pos += _AddValue##)fileText += FGet<##_CharaType##>(file);\
	fclose(file);\
\
	if (localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
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
