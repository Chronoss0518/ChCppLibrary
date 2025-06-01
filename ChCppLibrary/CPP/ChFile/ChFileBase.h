#ifndef Ch_CPP_FileBase_h
#define Ch_CPP_FileBase_h

#include<stdio.h>
#include<locale>
#include<string>

namespace ChCpp
{
	FILE* Open(const std::string& _fileName, const std::string& _type);

#ifdef _MSC_BUILD 
	FILE* Open(const std::wstring& _fileName, const std::wstring& _type);
#endif

	template<typename OutCharaType>
	OutCharaType FGet(FILE* _fp);

	void FPut(FILE* _fp, const char _char);

	void FPut(FILE* _fp, const wchar_t _char);

	class FileBase
	{
	public:

		inline void SetIsUpdateFlg(bool _flg) { isUpdateFlg = _flg; }

	protected:

		void FileOpenInit(const std::string& _fileName,const std::string& _localeName, bool _isUpdate);

#ifdef _MSC_BUILD 
		void FileOpenInit(const std::wstring& _fileName,const std::string& _localeName, bool _isUpdate);
#endif

	public:

		void FileClose();

	protected:

		virtual void FileCloseCharName() = 0;

#ifdef _MSC_BUILD 
		virtual void FileCloseWCharName() = 0;
#endif
	protected:

		std::string localeName = "";
		std::string openFileNameChar = "";

#ifdef _MSC_BUILD 
		std::wstring openFileNameWChar = L"";
#endif

	private:

		bool isUpdateFlg = true;
	};
}

#endif