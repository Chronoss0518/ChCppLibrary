#ifndef Ch_CPP_FileBase_h
#define Ch_CPP_FileBase_h

#include<stdio.h>
#include<locale>
#include<string>

namespace ChCpp
{
	FILE* Open(const std::string& _fileName, const std::string& _type);

	FILE* Open(const std::wstring& _fileName, const std::wstring& _type);

	template<typename OutCharaType>
	OutCharaType FGet(FILE* _fp);

	void FPut(FILE* _fp, const char _char);

	void FPut(FILE* _fp, const wchar_t _char);


	class FileBase
	{
	public:

		virtual ~FileBase() { FileClose(); }

	public:

		inline void SetIsUpdateFlg(bool _flg) { isUpdateFlg = _flg; }

	protected:

		void FileOpenInit(const std::string& _fileName,const std::string& _localeName, bool _isUpdate);
		
		void FileOpenInit(const std::wstring& _fileName,const std::string& _localeName, bool _isUpdate);

	public:

		void FileClose();

	protected:

		virtual void FileCloseCharName() = 0;

		virtual void FileCloseWCharName() = 0;

	protected:

		std::string localeName = "";
		std::string openFileNameChar = "";
		std::wstring openFileNameWChar = L"";

	private:

		bool isUpdateFlg = true;
	};
}

#endif