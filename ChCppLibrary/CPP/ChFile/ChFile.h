#ifndef Ch_CPP_File_h
#define Ch_CPP_File_h

#ifdef CRT
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
#include<locale>
#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChStr.h"

#ifndef CH_ERROR_TEXT_TYPE_FUNCTION
#define CH_ERROR_TEXT_TYPE_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(GetErrorTextType,type)
#endif

namespace ChStd
{
#ifdef CRT
	CH_TO_NUMBER_FUNCTION(CH_ERROR_TEXT_TYPE_FUNCTION, ".txt");
#endif
}

namespace ChCpp
{
	template<typename CharaType>
	class File
	{
	public:

		const enum class OTEAddType :unsigned char
		{
			None, 
			//後ろに追加していく//
			AfterFirst, 
			//全ての内容を残しておく//
			All
		};

	public://Static Functions//

#ifdef CRT

		//専用エラーファイルを出力する//
		static inline void OutToErrorText(
			const std::basic_string<CharaType>& _errorName,
			const std::basic_string<CharaType>& _errorDitails,
			const OTEAddType _addFlg = OTEAddType::None)
		{
			OutToErrorText(_errorName, _errorDitails, "", _addFlg);
		}


		static inline void OutToErrorText(
			const std::basic_string<CharaType>& _errorName,
			const std::basic_string<CharaType>& _errorDitails,
			const char* _localeName,
			const OTEAddType _addFlg = OTEAddType::None)
		{
			File outFiles;
			std::basic_string<CharaType> outData = ChStd::GetZeroChara<CharaType>();
			std::basic_string<CharaType> outFileName = ChStd::GetZeroChara<CharaType>();
			outFileName = _errorName + ChStd::GetErrorTextType<CharaType>();
			outFiles.FileOpen(outFileName);
			outFiles.SetLocaleName(_localeName);

			if (_addFlg == OTEAddType::All)
			{
				outData = outFiles.FileReadText();
				outData = outData + ChStd::GetCRLFChara<CharaType>();
			}

			if (_addFlg == OTEAddType::AfterFirst)
			{
				static bool flgs = false;
				if (flgs)
				{
					outData = outFiles.FileReadText();
					outData = outData + ChStd::GetCRLFChara<CharaType>();
				}
				flgs = true;
			}

			outData = outData + _errorDitails;


			outFiles.FileWriteText(outData);

			return;
		}
#endif

	public://Constructor Destructor//

		inline File() {}

#ifdef CRT

		File(
			const std::basic_string<CharaType>& _fileName) {
			FileOpen(_fileName);
		}

#endif

		virtual ~File() { Release(); }

		virtual void Release();


	public://Set Functions//

		void SetLocaleName(const char* _localeName);

	public://Get Functions//

#ifdef CRT
		unsigned long GetLength()
		{
			unsigned long out = 0;

			if (!stream.is_open())return out;

			auto istream = dynamic_cast<std::basic_istream<CharaType>*>(&stream);
			istream->seekg(0,std::ios::end);

			out = static_cast<unsigned long>(istream->tellg());

			istream->seekg(0, std::ios::beg);

			return out;
			

		}

	public://Control Functions//

		//Fileを開く//
		inline void FileOpen(
			const std::basic_string<CharaType>& _fileName
			, unsigned int _openMode = std::ios::in | std::ios::out)

		{
			if (_fileName.length() <= 0)return;

			if (_openMode & std::ios::in)
			{
				stream.open(_fileName, std::ios::app);
				stream.close();
			}

			flg = _openMode;
			openFileName = _fileName;
			stream.open(_fileName, flg);
			
		}

		//Fileを閉じる(Destructerでも起動する)//
		inline void FileClose()
		{
			if (!stream.is_open())return;
			stream.close();
		}

		//Fileから読み出す//
		inline std::basic_string<CharaType> FileReadText()
		{

			std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

			if (!stream.is_open())return res;

			if ((flg & std::ios::binary))return res;

			std::locale tmpLocale = std::locale::classic();

			if (localeName != "") { tmpLocale = stream.imbue(std::locale(localeName.c_str())); }

			std::basic_ostringstream<CharaType> tmpSS;


			tmpSS << stream.rdbuf();

			res = tmpSS.str();

			stream.clear();
			stream.seekp(0, std::ios::beg);

			if (localeName != "") { stream.imbue(tmpLocale); }

			return res;

		}

		//Fileから読み出す//
		inline void FileReadBinary(std::vector<char>& _binary)
		{

			if (!stream.is_open())return;

			if (!(flg & std::ios::binary))return;

			_binary.resize(GetLength());

			std::locale tmpLocale = std::locale::classic();

			if (localeName != "") { tmpLocale = stream.imbue(std::locale(localeName.c_str())); }

			auto istream = dynamic_cast<std::basic_istream<CharaType>*>(&stream);

			istream->read(&_binary[0], GetLength());

			istream->seekg(0, std::ios::beg);

			if (localeName != "") { stream.imbue(tmpLocale); }

			return;

		}

		//Fileに書き込む//
		template<class... _Types>
		inline std::basic_string<CharaType> FileWriteText(
			const std::basic_string<CharaType>& _writeStr
			, _Types&&... _args)
		{

			if (!stream.is_open())return std::basic_string<CharaType>();

			if (flg & std::ios::binary)return std::basic_string<CharaType>();

			if (!(flg & std::ios::app))
			{
				stream.close();
				stream.open(openFileName.c_str(), std::ios::out | std::ios::trunc);
				
				stream.close();
				stream.open(openFileName.c_str(),flg);
			}

			return Writer(_writeStr);

			//C++以降の文字列型が対応していないため一旦保留//

			std::basic_string<CharaType> tmpStr = _writeStr;
#ifdef _WINDOWS
			::swscanf_s(&tmpStr[0], &tmpStr[0], _args...);
#else
			std::swscanf(&tmpStr[0], &tmpStr[0], _args...);
#endif
			
			return Writer(tmpStr);

		}

		//Fileに書き込む//
		inline std::basic_string<CharaType> FileWriteBinary(
			const std::basic_string<CharaType>& _writeStr)
		{

			if (!stream.is_open())return std::basic_string<CharaType>();

			if (flg & std::ios::binary)return std::basic_string<CharaType>();

			if (!(flg & std::ios::app))
			{
				stream.close();
				stream.open(openFileName.c_str(), std::ios::out | std::ios::trunc);

				stream.close();
				stream.open(openFileName.c_str(), flg);
			}

			std::basic_string<CharaType> tmpStr = _writeStr;

			return Writer(tmpStr);

		}

#endif

	private:

#ifdef CRT
		std::basic_string<CharaType> Writer(const std::basic_string<CharaType>& _str)
		{

			std::basic_ofstream<CharaType> tmpStream;

			std::locale tmpLocale = std::locale::classic();

			if (localeName != "") { tmpLocale = stream.imbue(std::locale(localeName.c_str())); }

			tmpStream.set_rdbuf(stream.rdbuf());
			

			tmpStream << _str.c_str();

			if (localeName != "") { stream.imbue(tmpLocale); }

			return _str;
		}
#endif

	protected:

#ifdef CRT
		std::ios_base::openmode flg{ 0 };
		std::basic_string<CharaType> openFileName = ChStd::GetZeroChara<CharaType>();
		std::string localeName = "";
		std::basic_fstream<CharaType> stream;
#endif

	};
	
	using CharFile =  File<char>;
	using WCharFile = File<wchar_t>;

}

#ifdef CRT

template<typename CharaType>
void ChCpp::File<CharaType>::SetLocaleName(const char* _localeName) { localeName = _localeName; }


template<typename CharaType>
void ChCpp::File<CharaType>::Release()
{
	FileClose();
}

#endif

#endif