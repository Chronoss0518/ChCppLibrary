#ifdef _WINDOWS_

#ifndef Ch_Win_FiDl_h
#define Ch_Win_FiDl_h

#ifdef CRT

#include<string>
#include<map>

#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../ClassParts/ChCPInitializer.h"

namespace ChWin
{

	template<typename CharaType>
	class FileDialogBase : public ChCp::Initializer
	{
	public:

		struct FileDialogBaseCRT
		{
#ifdef CRT

			std::basic_string<CharaType> title = ChStd::GetZeroChara<CharaType>();

			std::basic_string<CharaType> fileName = ChStd::GetZeroChara<CharaType>();

			std::basic_string<CharaType> startDir = ChStd::GetZeroChara<CharaType>();

			std::basic_string<CharaType> baseDir = ChStd::GetZeroChara<CharaType>();

			std::map<std::basic_string<CharaType>, std::basic_string<CharaType>> filters;

			std::basic_string<CharaType> filterText = ChStd::GetZeroChara<CharaType>();
#endif
		};

		struct Filter
		{
#ifdef CRT
			std::basic_string<CharaType> name = ChStd::GetZeroChara<CharaType>();
			std::basic_string<CharaType> type = ChStd::GetZeroChara<CharaType>();
#endif
		};



	public:

		FileDialogBase();

		virtual ~FileDialogBase();

	public://Init And Release//

		virtual void Init(const HWND& _hWnd) = 0;

		virtual void Release();

	protected:

		void Init(const CharaType* _currentDirectory);

	public://Get Functions//

#ifdef CRT
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
			return ValueIns().fileName;
		}
#endif

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

#ifdef CRT

		std::basic_string<CharaType> PathToRerative();

#endif

	protected:

		bool openFlg = true;

		static constexpr DWORD openDialogFlg = (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON);
		static constexpr DWORD saveDialogFlg = (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT);

		static constexpr CharaType cutChar = 0;

		HWND hOwn = nullptr;

		FileDialogBaseCRT& ValueIns() { return *value; }

	private:

		FileDialogBaseCRT* value = nullptr;

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


#ifdef CRT

template<typename CharaType>
ChWin::FileDialogBase<CharaType>::FileDialogBase()
{
	value = new FileDialogBaseCRT();
}

template<typename CharaType>
ChWin::FileDialogBase<CharaType>::~FileDialogBase()
{
	Release();
	delete value;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::Init(const CharaType* _currentDirectory)
{
	ValueIns().startDir += _currentDirectory;
	ValueIns().baseDir = _currentDirectory;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::SetTitle(const CharaType* _title) { ValueIns().title = _title; }

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::SetStartDir(const CharaType* _dir) { ValueIns().startDir = _dir; }

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::AddFilter(const Filter& _fil)
{
	AddFilter(_fil.name.c_str(), _fil.type.c_str());
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::AddFilter(
	const CharaType* _name,
	const CharaType* _type)
{
	if (ValueIns().filters.find(_name) != ValueIns().filters.end())return;
	ValueIns().filters[_name] = _type;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::DelFilter(const CharaType* _name)
{
	if (ValueIns().filters.empty())return;
	if (ValueIns().filters.find(_name) == ValueIns().filters.end())return;

	ValueIns().filters.erase(_name);
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::CreateFilterStr()
{
	ValueIns().filterText = ChStd::GetZeroChara<CharaType>();

	for (auto&& fil : ValueIns().filters)
	{
		ValueIns().filterText += fil.first + ChStd::GetStartParenthesesChara<CharaType>() + ChStd::GetAsterisk<CharaType>() + fil.second + ChStd::GetEndParenthesesChara<CharaType>() + cutChar + ChStd::GetAsterisk<CharaType>() + fil.second + cutChar;
	}
}

template<typename CharaType>
std::basic_string<CharaType> ChWin::FileDialogBase<CharaType>::PathToRerative()
{
	size_t tmp = ValueIns().fileName.find_last_of(ChStd::GetYenChara<CharaType>(), ValueIns().fileName.size());

	std::basic_string<CharaType> baseStr;

	baseStr = ValueIns().fileName;

	baseStr.replace(0, tmp + 1, ChStd::GetZeroChara<CharaType>());

	return baseStr;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::SetFileName(const CharaType* _fileName)
{
	if (ChPtr::NullCheck(_fileName))return;
	ValueIns().fileName = _fileName;
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetTitleText()
{
	return ValueIns().title.size() <= 0 ? nullptr : ValueIns().title.c_str();
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetStartDir()
{
	return ValueIns().startDir.size() <= 0 ? nullptr : ValueIns().startDir.c_str();
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetFilterText()
{
	return ValueIns().filterText.c_str();
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetBaseDir()
{
	return ValueIns().baseDir.c_str();
}

void ChWin::FileDialogA::Init(const HWND& _hWnd)
{
	SetInitFlg(true);

	hOwn = _hWnd;
	char tmp[MAX_PATH];

	GetCurrentDirectoryA(MAX_PATH, tmp);

	FileDialogBase<char>::Init(tmp);
}

void ChWin::FileDialogA::OpenFileDialog()
{
	if (!IsInit())return;

	CreateFilterStr();

	OPENFILENAMEA tmp;
	char tmp2[MAX_PATH];
	ChStd::MZero<OPENFILENAMEA>(&tmp);
	tmp.lStructSize = sizeof(tmp);
	tmp.hwndOwner = hOwn;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	tmp.lpstrFile = tmp2;
	tmp.lpstrFile[0] = 0;
	tmp.nMaxFile = MAX_PATH;
	FileDialogBase<char>::CreateFilterStr();
	tmp.lpstrFilter = FileDialogBase<char>::GetFilterText();
	tmp.nFilterIndex = 1;

	tmp.lpstrTitle = FileDialogBase<char>::GetTitleText();
	tmp.lpstrInitialDir = FileDialogBase<char>::GetStartDir();

	tmp.Flags = FileDialogBase<char>::openDialogFlg;

	GetOpenFileNameA(&tmp);

	FileDialogBase<char>::SetFileName(tmp.lpstrFile);

	SetCurrentDirectoryA(FileDialogBase<char>::GetBaseDir());

	openFlg = true;
}

void ChWin::FileDialogA::SaveFileDialog()
{
	if (!IsInit())return;
	CreateFilterStr();

	OPENFILENAMEA tmp;
	char tmp2[MAX_PATH];
	ChStd::MZero(&tmp);
	tmp.lStructSize = sizeof(tmp);
	tmp.hwndOwner = hOwn;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	tmp.lpstrFile = tmp2;
	tmp.lpstrFile[0] = 0;
	tmp.nMaxFile = MAX_PATH;
	FileDialogBase<char>::CreateFilterStr();
	tmp.lpstrFilter = FileDialogBase<char>::GetFilterText();
	tmp.nFilterIndex = 1;

	tmp.lpstrTitle = FileDialogBase<char>::GetTitleText();
	tmp.lpstrInitialDir = FileDialogBase<char>::GetStartDir();

	tmp.Flags = FileDialogBase<char>::saveDialogFlg;

	GetSaveFileNameA(&tmp);
	FileDialogBase<char>::SetFileName(tmp2);

	SetCurrentDirectoryA(FileDialogBase<char>::GetBaseDir());

	openFlg = true;
}

void ChWin::FileDialogW::Init(const HWND& _hWnd)
{
	SetInitFlg(true);

	hOwn = _hWnd;
	wchar_t tmp[MAX_PATH];

	GetCurrentDirectoryW(MAX_PATH, tmp);

	FileDialogBase<wchar_t>::Init(tmp);
}

void ChWin::FileDialogW::OpenFileDialog()
{
	if (!IsInit())return;

	CreateFilterStr();

	OPENFILENAMEW tmp;
	wchar_t tmp2[MAX_PATH];
	ChStd::MZero<OPENFILENAMEW>(&tmp);
	tmp.lStructSize = sizeof(tmp);
	tmp.hwndOwner = hOwn;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	tmp.lpstrFile = tmp2;
	tmp.lpstrFile[0] = 0;
	tmp.nMaxFile = MAX_PATH;
	FileDialogBase<wchar_t>::CreateFilterStr();
	tmp.lpstrFilter = FileDialogBase<wchar_t>::GetFilterText();
	tmp.nFilterIndex = 1;

	tmp.lpstrTitle = FileDialogBase<wchar_t>::GetTitleText();
	tmp.lpstrInitialDir = FileDialogBase<wchar_t>::GetStartDir();

	tmp.Flags = FileDialogBase<wchar_t>::openDialogFlg;

	GetOpenFileNameW(&tmp);

	FileDialogBase<wchar_t>::SetFileName(tmp.lpstrFile);

	SetCurrentDirectoryW(FileDialogBase<wchar_t>::GetBaseDir());

	openFlg = true;
}

void ChWin::FileDialogW::SaveFileDialog()
{
	if (!IsInit())return;
	CreateFilterStr();

	OPENFILENAMEW tmp;
	wchar_t tmp2[MAX_PATH];
	ChStd::MZero(&tmp);
	tmp.lStructSize = sizeof(tmp);
	tmp.hwndOwner = hOwn;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	tmp.lpstrFile = tmp2;
	tmp.lpstrFile[0] = 0;
	tmp.nMaxFile = MAX_PATH;
	FileDialogBase<wchar_t>::CreateFilterStr();
	tmp.lpstrFilter = FileDialogBase<wchar_t>::GetFilterText();
	tmp.nFilterIndex = 1;

	tmp.lpstrTitle = FileDialogBase<wchar_t>::GetTitleText();
	tmp.lpstrInitialDir = FileDialogBase<wchar_t>::GetStartDir();

	tmp.Flags = FileDialogBase<wchar_t>::saveDialogFlg;

	GetSaveFileNameW(&tmp);
	FileDialogBase<wchar_t>::SetFileName(tmp2);

	SetCurrentDirectoryW(FileDialogBase<wchar_t>::GetBaseDir());

	openFlg = true;
}

#endif


#endif