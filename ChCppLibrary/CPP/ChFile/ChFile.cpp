#include<stdio.h>
#include<locale.h>
#include<wchar.h>
#include"ChFile.h"

#ifdef _MSC_BUILD 

#define METHOD_EXPLICIT_DECLARATION(_CharaType,_AddType,_ReadType,_WriteType)\
template<> void ChCpp::File<_CharaType>::FileOpen(\
	const std::string& _fileName,\
	const std::string& _localeName,\
	const bool _isUpdate){\
	if (_fileName.length() <= 0)return;\
	FileOpenInit(_fileName,_localeName,_isUpdate);\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameChar.c_str(), _ReadType );\
	fileText = ChStd::GetZeroChara<_CharaType>();\
	_CharaType tmp = FGet<_CharaType>(file);\
	while (tmp != static_cast<_CharaType>(EOF)){\
	fileText += tmp;\
	tmp = FGet<_CharaType>(file);}\
	fclose(file);\
\
	if (localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
template<>	void ChCpp::File<_CharaType>::FileOpen(\
	const std::wstring& _fileName,\
	const std::string& _localeName,\
	const bool _isUpdate){\
	if (_fileName.length() <= 0)return;\
	FileOpenInit(_fileName,_localeName,_isUpdate);\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameWChar.c_str(), L##_ReadType );\
	fileText = ChStd::GetZeroChara<_CharaType>();\
	_CharaType tmp = FGet<_CharaType>(file);\
	while (tmp != static_cast<_CharaType>(EOF)){\
	fileText += tmp;\
	tmp = FGet<_CharaType>(file);}\
	fclose(file);\
\
	if (localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
template<> void ChCpp::File<_CharaType>::FileCloseCharName(){\
	if (openFileNameChar == "")return;\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str()); \
\
	FILE* file = Open(openFileNameChar.c_str(), _WriteType );\
	fileText = fileText.c_str();\
	for (size_t i = 0; i < fileText.size(); i++)FPut(file, fileText[i]);\
	fclose(file);\
	openFileNameChar = "";\
	fileText = ChStd::GetZeroChara<_CharaType>();\
\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str()); }\
template<> void ChCpp::File<_CharaType>::FileCloseWCharName(){\
	if (openFileNameWChar == L"")return;\
\
	std::string tmpLocale = ""; \
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str()); \
\
	FILE* file = Open(openFileNameWChar.c_str(), L##_WriteType );\
	fileText = fileText.c_str();\
	for (size_t i = 0; i < fileText.size(); i++)FPut(file, fileText[i]);\
	fclose(file);\
	openFileNameWChar = L"";\
	fileText = ChStd::GetZeroChara<_CharaType>();\
\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str());}
#else

#define METHOD_EXPLICIT_DECLARATION(_CharaType,_AddType,_ReadType,_WriteType)\
template<> void ChCpp::File<_CharaType>::FileOpen(\
	const std::string& _fileName,\
	const std::string& _localeName,\
	const bool _isUpdate){\
	if (_fileName.length() <= 0)return;\
	FileOpenInit(_fileName,_localeName,_isUpdate);\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str());\
\
	FILE* file = Open(openFileNameChar.c_str(), _ReadType );\
	fileText = ChStd::GetZeroChara<_CharaType>();\
	_CharaType tmp = FGet<_CharaType>(file);\
	while (tmp != static_cast<_CharaType>(EOF)){\
	fileText += tmp;\
	tmp = FGet<_CharaType>(file);}\
	fclose(file);\
\
	if (localeName != "") setlocale(LC_ALL, tmpLocale.c_str());}\
template<> void ChCpp::File<_CharaType>::FileCloseCharName(){\
	if (openFileNameChar == "")return;\
\
	std::string tmpLocale = "";\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, localeName.c_str()); \
\
	FILE* file = Open(openFileNameChar.c_str(), _WriteType );\
	fileText = fileText.c_str();\
	for (size_t i = 0; i < fileText.size(); i++)FPut(file, fileText[i]);\
	fclose(file);\
	openFileNameChar = "";\
	fileText = ChStd::GetZeroChara<_CharaType>();\
\
	if (localeName != "")tmpLocale = setlocale(LC_ALL, tmpLocale.c_str()); }
#endif

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

METHOD_EXPLICIT_DECLARATION(char, "a", "r", "w");

#ifdef _MSC_BUILD 
METHOD_EXPLICIT_DECLARATION(wchar_t, "a", "rb", "wb");
#endif


CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::File);
