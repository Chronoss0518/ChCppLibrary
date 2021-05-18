#ifndef Ch_CPP_File_h
#define Ch_CPP_File_h

namespace ChCpp
{
	class File :public ClassPerts::Releaser
	{

	public:

		const enum class OTEAddType :unsigned char
		{
			None, AfterFirst, All
		};

		///////////////////////////////////////////////////////////////////////////////////
		//StaticFunction//

		//専用エラーファイルを出力する//
		static void OutToErrorText(
			const std::string& _errorName
			, const std::string& _errorDitails
			, const OTEAddType _addFlg = OTEAddType::None);

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		inline File() {}

		inline File(
			const std::string& _fileName)
		{
			FileOpen(_fileName);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		inline void Release()override
		{
			FileClose();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを開く//
		void FileOpen(
			const std::string& _fileName
			, unsigned int _openMode = std::ios::in | std::ios::out);

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを閉じる(Destructerでも起動する)//
		inline void FileClose()
		{
			if (!stream.is_open())return;
			stream.close();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileから読み出す//
		std::string FileRead();

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
				stream.open(openFileName.c_str(),flg);
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


}


#endif