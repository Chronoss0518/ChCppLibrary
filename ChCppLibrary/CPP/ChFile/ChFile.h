#ifndef Ch_CPP_File_h
#define Ch_CPP_File_h



#include<string>

#include"ChFileBase.h"
#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChStr.h"

#ifndef CH_ERROR_TEXT_TYPE_FUNCTION
#define CH_ERROR_TEXT_TYPE_FUNCTION(type) CH_NUMBER_FUNCTION(GetErrorTextType,type)
#endif

namespace ChStd
{
	CH_NUMBER_FUNCTION_BASE(GetErrorTextType);
}

namespace ChCpp
{
	template<typename CharaType>
	class File : public FileBase
	{
	public:

		enum class OTEAddType :unsigned char
		{
			None, 
			//後ろに追加していく//
			AfterFirst, 
			//全ての内容を残しておく//
			All
		};

	public://Static Functions//

		static inline void OutToErrorText(
			const std::basic_string<CharaType>& _errorName,
			const std::basic_string<CharaType>& _errorDitails,
			const OTEAddType _addFlg = OTEAddType::None)
		{
			OutToErrorText(_errorName, _errorDitails, "", _addFlg);
		}


		//専用エラーファイルを出力する//
		static inline void OutToErrorText(
			const std::basic_string<CharaType>& _errorName,
			const std::basic_string<CharaType>& _errorDitails,
			const char* _localeName,
			const OTEAddType _addFlg = OTEAddType::None)
		{
			File<CharaType> outFiles;
			std::basic_string<CharaType> outData = ChStd::GetZeroChara<CharaType>();
			std::basic_string<CharaType> outFileName = ChStd::GetZeroChara<CharaType>();
			outFileName = _errorName + ChStd::GetErrorTextType<CharaType>();
			outFiles.FileOpen(outFileName, _localeName);

			if (_addFlg == OTEAddType::All)
			{
				outData = outFiles.FileRead();
				outData = outData + ChStd::GetCRLFChara<CharaType>();
			}

			if (_addFlg == OTEAddType::AfterFirst)
			{
				static bool flgs = false;
				if (flgs)
				{
					outData = outFiles.FileRead();
					outData = outData + ChStd::GetCRLFChara<CharaType>();
				}
				flgs = true;
			}

			outData = outData + _errorDitails;


			outFiles.FileWrite(outData);

			return;
		}

	public://Constructor Destructor//

		File() {};

	public://Get Functions//

		size_t GetLength();

	public://Control Functions//

		//Fileを開く//
		void FileOpen(
			const std::string& _fileName,
			const std::string& _locale = "",
			const bool _IsUpdate = true);

		//Fileを開く//
		void FileOpen(
			const std::string& _fileName,
			const bool _isUpdate)
		{
			FileOpen(_fileName, "", _isUpdate);
		}

#ifdef _MSC_BUILD 
		//Fileを開く//
		void FileOpen(
			const std::wstring& _fileName,
			const std::string& _locale = "",
			const bool _IsUpdate = true);

		//Fileを開く//
		void FileOpen(
			const std::wstring& _fileName,
			const bool _isUpdate)
		{
			FileOpen(_fileName, "", _isUpdate);
		}
#endif
		//Fileから読み出す//
		std::basic_string<CharaType> FileRead();

		//Fileに書き込む//
		std::basic_string<CharaType> FileWrite(const std::basic_string<CharaType>& _writeStr);

	protected:

		void FileCloseCharName()override;
#ifdef _MSC_BUILD 
		void FileCloseWCharName()override;
#endif

	private:

		std::basic_string<CharaType> fileText = ChStd::GetZeroChara<CharaType>();
	};
	
	using CharFile =  File<char>;
#ifdef _MSC_BUILD 
	using WCharFile = File<wchar_t>;
#endif
}

#endif