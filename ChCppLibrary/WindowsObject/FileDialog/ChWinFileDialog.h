#ifdef _WINDOWS_

#ifndef Ch_Win_FiDl_h
#define Ch_Win_FiDl_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	typedef class FileDialog:public ChCp::Initializer
	{
	public:

		struct Filter
		{
			std::string name = "";
			std::string type = "";
		};

	public:

		virtual ~FileDialog()
		{
			Release();
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _hWnd);

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::string GetFileName() 
		{
			if (!openFlg)return "";
			openFlg = false;
			return PathToRerative();
		}

		std::string GetFileNameFullPath()
		{
			if (!openFlg)return "";
			openFlg = false;
			return fileName;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetTitle(const std::string& _title) { title = _title; }

		void SetStartDir(const std::string& _dir) { startDir = _dir; }

		void SetPathLen(const unsigned short _pathLength = 500) 
		{
			if (_pathLength < 2)return;
			pathLength = _pathLength;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		bool IsOpen() { return openFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		void AddFilter(const Filter& _fil);

		void AddFilter(
			const std::string& _name
			, const std::string& _type);

		///////////////////////////////////////////////////////////////////////////////////////

		void DelFilter(const std::string& _name);

		///////////////////////////////////////////////////////////////////////////////////////

		void OpenFileDialog();

		///////////////////////////////////////////////////////////////////////////////////////

		void SaveFileDialog();

		///////////////////////////////////////////////////////////////////////////////////////

	protected:

		void CreateFilterStr();

		///////////////////////////////////////////////////////////////////////////////////////

		std::string PathToRerative();

		///////////////////////////////////////////////////////////////////////////////////////

		std::string title = "";

		std::string fileName = "";

		std::string startDir = "";

		std::string baseDir = "";

		std::map<std::string,std::string> filters;

		bool openFlg = true;

		unsigned short pathLength = 256;

		enum class FlgType { Open, Save };

		static const char cutChar;
		static const DWORD flgs[];

		HWND hOwn = nullptr;
		
		static std::string tmpType;

	}FDialog;

}

#endif

#endif