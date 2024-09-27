#ifndef Ch_CPP_File_h
#define Ch_CPP_File_h

#include<string>
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
#include<locale>

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

		static inline void OutToErrorText(
			const std::basic_string<CharaType>& _errorName,
			const std::basic_string<CharaType>& _errorDitails,
			const OTEAddType _addFlg = OTEAddType::None)
		{
			OutToErrorText(_errorName, _errorDitails, ChStd::GetZeroChara<CharaType>(), _addFlg);
		}


		//専用エラーファイルを出力する//
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

	public://Constructor Destructor//

		File(const std::basic_string<CharaType>& _fileName)
		{
			FileOpen(_fileName);
		}

		virtual ~File()
		{
			Release();
		}

		virtual void Release()
		{
			FileClose();
		}

	public://Set Functions//

		void SetLocaleName(const char* _localeName)
		{
			localeName = _localeName;
		}

	public://Get Functions//

		unsigned long GetLength();

	public://Control Functions//

		//Fileを開く//
		inline void FileOpen(
			const std::basic_string<CharaType>& _fileName,
			unsigned int _openMode = std::ios::in | std::ios::out)

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

			if (!IsOpenModeTest(false, false))return res;

			std::locale tmpLocale = std::locale::classic();

			if (localeName != "") { tmpLocale = stream.imbue(std::locale(localeName.GetString())); }

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
			if (!IsOpenModeTest(false, true))return;

			_binary.resize(GetLength());

			std::locale tmpLocale = std::locale::classic();

			if (localeName != "") { tmpLocale = stream.imbue(std::locale(localeName.GetString())); }

			auto istream = dynamic_cast<std::basic_istream<CharaType>*>(&stream);

			istream->read(&_binary[0], GetLength());

			istream->seekg(0, std::ios::beg);

			if (localeName != "") { stream.imbue(tmpLocale); }

			return;
		}

		//Fileに書き込む//
		template<class... _Types>
		inline std::basic_string<CharaType> FileWriteText(
			const std::basic_string<CharaType>& _writeStr,
			_Types&&... _args)
		{
			if (!IsOpenModeTest(true, false))return std::basic_string<CharaType>();

			return Writer(_writeStr);

			//C++20以降の文字列型が対応していないため一旦保留//

			std::basic_string<CharaType> tmpStr = _writeStr;
#ifdef _WINDOWS
			::swscanf_s(&tmpStr[0], &tmpStr[0], _args...);
#else
			std::swscanf(&tmpStr[0], &tmpStr[0], _args...);
#endif
			return Writer(tmpStr);
		}

		//Fileに書き込む//
		inline std::basic_string<CharaType> FileWriteBinary(const std::basic_string<CharaType>& _writeStr)
		{
			if (!IsOpenModeTest(true,true))return std::basic_string<CharaType>();

			std::basic_string<CharaType> tmpStr = _writeStr;

			return Writer(tmpStr);
		}


	private:

		std::basic_string<CharaType> Writer(const std::basic_string<CharaType>& _str)
		{

			std::basic_ofstream<CharaType> tmpStream;

			std::locale tmpLocale = std::locale::classic();

			if (localeName != "") { tmpLocale = stream.imbue(std::locale(localeName.GetString())); }

			tmpStream.set_rdbuf(stream.rdbuf());

			tmpStream << _str.c_str();

			if (localeName != "") { stream.imbue(tmpLocale); }

			return _str;
		}

	private:

		bool IsOpenModeTest(bool _isReadFlg, bool _isBinaryFlg);

		private:

		std::ios_base::openmode flg{ 0 };
		std::basic_fstream<CharaType> stream;
		std::basic_string<CharaType> openFileName = ChStd::GetZeroChara<CharaType>();
		std::string localeName = "";
	};
	
	using CharFile =  File<char>;
	using WCharFile = File<wchar_t>;

}

#endif