#ifndef Ch_CPP_FIO_h
#define Ch_CPP_FIO_h

namespace ChFIO
{
	class File
	{

	public:

		inline File() {}

		inline File(
			const std::string& _fileName)
		{
			FileOpen(_fileName);
		}

		inline ~File()
		{
			FileClose();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを開く//
		inline void FileOpen(
			const std::string& _fileName
			, unsigned int _openMode = std::ios::in | std::ios::out)
		{
			if (_fileName.length() <= 0)return;

			if (_openMode & std::ios::in)
			{

				std::ofstream tmp;
				tmp.open(_fileName, std::ios::app);
				tmp.close();
			}

			flg = _openMode;
			openFileName = _fileName;
			stream.open(_fileName, flg);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを閉じる(Destructerでも起動する)//
		inline void FileClose()
		{
			if (!stream.is_open())return;
			stream.close();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileから読み出す//
		inline std::string FileRead()
		{
			std::string out = "";

			if (!stream.is_open())return;

			std::stringstream tmpSS;

			tmpSS << stream.rdbuf();

			out = tmpSS.str();

			stream.clear();
			stream.seekp(std::ios::beg, static_cast<std::ios_base::seekdir>(0));

			return out;

		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileに書き込む//
		template<class... _Types>
		inline std::string FileWrite(
			const std::string& _writeStr
			, _Types&&... _args)
		{

			if (!stream.is_open())return "";

			if (flg & std::ios::binary)return "";

			if (!(flg & std::ios::app))
			{
				stream.close();
				stream.open(openFileName.c_str(), std::ios::out | std::ios::trunc);
				
				stream.close();
				stream.open(openFileName.c_str(), static_cast<std::ios_base::openmode>(Flg));
			}

			std::string tmpStr = _writeStr;
#ifdef _WIN32
			::sscanf_s(&tmpStr[0], &tmpStr[0], _args...);
#else
			std::sscanf(tmpStr.c_str(), tmpStr.c_str(), _Args...);
#endif
			
			return Writer(tmpStr);

		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		std::string Writer(const std::string& _str)
		{

			std::ofstream tmpStream;

			tmpStream.set_rdbuf(stream.rdbuf());

			tmpStream << _str.c_str();

			return _str;
		}

	protected:

		std::ios_base::openmode flg{ 0 };
		std::string openFileName{ "" };
		std::fstream stream;


	};

	const enum class OTEAddType :unsigned char
	{
		None, AfterFirst, All
	};

	///////////////////////////////////////////////////////////////////////////////////

	//専用エラーファイルを出力する//
	inline static void OutToErrorText(
		const std::string& _ErrorName
		, const std::string& _ErrorDitails
		, const OTEAddType _AddFlg = OTEAddType::None)
	{
		File OutFiles;
		std::string OutData = "";
		std::string OutFileName = "";
		OutFileName = _ErrorName + ".txt";
		OutFiles.FileOpen(OutFileName);

		if (_AddFlg == OTEAddType::All)
		{
			OutFiles.FileRead(OutData);
			OutData = OutData + "\n";
		}

		if (_AddFlg == OTEAddType::AfterFirst)
		{
			static ChStd::Bool Flgs = false;
			if (Flgs)
			{
				OutFiles.FileRead(OutData);
				OutData = OutData + "\n";
			}
			Flgs = true;
		}

		OutData = OutData + _ErrorDitails;

		OutFiles.FileWrite(OutData);

		return;


	}

}


#endif