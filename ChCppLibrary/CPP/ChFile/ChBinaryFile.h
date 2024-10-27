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

		void FileOpen(const std::wstring& _fileName,const std::string& _localeName = "", bool _isUpdate = true);

		inline void FileOpen(const std::string& _fileName, bool _isUpdate)
		{
			FileOpen(_fileName, "", _isUpdate);
		}

		inline void FileOpen(const std::wstring& _fileName, bool _isUpdate)
		{
			FileOpen(_fileName, "", _isUpdate);
		}

		//FileÇ©ÇÁì«Ç›èoÇ∑//
		std::vector<unsigned char> FileRead();

		//FileÇ…èëÇ´çûÇﬁ//
		std::vector<unsigned char> FileWrite(const std::vector<unsigned char>& _writeData);

	private:

		void FileCloseCharName()override;

		void FileCloseWCharName()override;

	private:

		std::vector<unsigned char>datas;

	};

}

#endif