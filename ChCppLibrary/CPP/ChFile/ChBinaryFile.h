#ifndef Ch_CPP_BFile_h
#define Ch_CPP_BFile_h


#include<vector>

#include"ChFileBase.h"

namespace ChCpp
{
	class BinaryFile:public FileBase
	{
	public:

		BinaryFile(){}

	public://Get Functions//

		size_t GetLength() { return datas.size(); }

	public:

		void FileOpen(const std::string& _fileName,const std::string& _localeName = "", bool _isUpdate = true);

#ifdef _MSC_BUILD 
		void FileOpen(const std::wstring& _fileName,const std::string& _localeName = "", bool _isUpdate = true);
#endif

		inline void FileOpen(const std::string& _fileName, bool _isUpdate)
		{
			FileOpen(_fileName, "", _isUpdate);
		}

#ifdef _MSC_BUILD 
		inline void FileOpen(const std::wstring& _fileName, bool _isUpdate)
		{
			FileOpen(_fileName, "", _isUpdate);
		}
#endif

		//FileÇ©ÇÁì«Ç›èoÇ∑//
		std::vector<unsigned char> FileRead();

		//FileÇ…èëÇ´çûÇﬁ//
		std::vector<unsigned char> FileWrite(const std::vector<unsigned char>& _writeData);

	private:

		void FileCloseCharName()override;

#ifdef _MSC_BUILD 
		void FileCloseWCharName()override;
#endif

	private:

		std::vector<unsigned char>datas;

	};

}

#endif