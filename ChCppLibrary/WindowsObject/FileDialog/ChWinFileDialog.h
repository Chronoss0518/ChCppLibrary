#ifdef _WINDOWS_

#ifndef Ch_Win_FiDl_h
#define Ch_Win_FiDl_h

#include<string>
#include<map>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../ClassParts/ChCPInitializer.h"

namespace ChWin
{

	template<typename CharaType>
	class FileDialogBase : public ChCp::Initializer
	{
	public:

		struct Filter
		{
			std::basic_string<CharaType> name = ChStd::GetZeroChara<CharaType>();
			std::basic_string<CharaType> type = ChStd::GetZeroChara<CharaType>();
		};

	public:

		virtual ~FileDialogBase() { Release(); }

	public://Init And Release//

		virtual void Init(const HWND& _hWnd) = 0;

		virtual void Release();

	protected:

		void Init(const CharaType* _currentDirectory);

	public://Get Functions//

		inline std::basic_string<CharaType> GetFileName()
		{
			if (!openFlg)return ChStd::GetZeroChara<CharaType>();
			openFlg = false;
			return PathToRerative();
		}

		inline std::basic_string<CharaType> GetFileNameFullPath()
		{
			if (!openFlg)return ChStd::GetZeroChara<CharaType>();
			openFlg = false;
			return fileName;
		}

	public://Set Functions//

		void SetTitle(const CharaType* _title);

		void SetStartDir(const CharaType* _dir);

	protected://Set Functions//

		void SetFileName(const CharaType* _fileName);

	protected://Get Functions//

		const CharaType* GetTitleText();

		const CharaType* GetStartDir();

		const CharaType* GetFilterText();

		const CharaType* GetBaseDir();

	public://Is Functions//

		bool IsOpen() { return openFlg; }

	public://Add Functions//

		void AddFilter(const Filter& _fil);

		void AddFilter(
			const CharaType* _name,
			const CharaType* _type);

	public://Other Functions//

		void DelFilter(const CharaType* _name);

		virtual void OpenFileDialog() = 0;

		virtual void SaveFileDialog() = 0;

	protected:

		void CreateFilterStr();

		std::basic_string<CharaType> PathToRerative();

	protected:

		bool openFlg = true;

		static constexpr DWORD openDialogFlg = (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON);
		static constexpr DWORD saveDialogFlg = (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT);

		static constexpr CharaType cutChar = 0;

		HWND hOwn = nullptr;

		std::basic_string<CharaType> title = ChStd::GetZeroChara<CharaType>();

		std::basic_string<CharaType> fileName = ChStd::GetZeroChara<CharaType>();

		std::basic_string<CharaType> startDir = ChStd::GetZeroChara<CharaType>();

		std::basic_string<CharaType> baseDir = ChStd::GetZeroChara<CharaType>();

		std::map<std::basic_string<CharaType>, std::basic_string<CharaType>> filters;

		std::basic_string<CharaType> filterText = ChStd::GetZeroChara<CharaType>();

	};

	class FileDialogA:public FileDialogBase<char>
	{
	public://InitAndRelease//

		void Init(const HWND& _hWnd)override;

	public:

		void OpenFileDialog()override;

		void SaveFileDialog()override;
	};

	class FileDialogW :public FileDialogBase<wchar_t>
	{
	public://InitAndRelease//

		void Init(const HWND& _hWnd)override;

	public:

		void OpenFileDialog()override;

		void SaveFileDialog()override;
	};

	using FileDialog =
#ifdef UNICODE
		FileDialogW;
#else
		FileDialogA;
#endif
}

#endif

#endif