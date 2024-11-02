#include<Windows.h>
#include"ChWinFileDialog.h"

///////////////////////////////////////////////////////////////////////////////////////
//FileDialogÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::Release()
{
	SetInitFlg(false);
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::Init(const CharaType* _currentDirectory)
{
	startDir += _currentDirectory;
	baseDir = _currentDirectory;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::SetTitle(const CharaType* _title) { title = _title; }

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::SetStartDir(const CharaType* _dir) { startDir = _dir; }

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
	if (filters.find(_name) != filters.end())return;
	filters[_name] = _type;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::DelFilter(const CharaType* _name)
{
	if (filters.empty())return;
	if (filters.find(_name) == filters.end())return;

	filters.erase(_name);
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::CreateFilterStr()
{
	filterText = ChStd::GetZeroChara<CharaType>();

	for (auto&& fil : filters)
	{
		filterText += fil.first + ChStd::GetStartParenthesesChara<CharaType>() + ChStd::GetAsterisk<CharaType>() + fil.second + ChStd::GetEndParenthesesChara<CharaType>() + cutChar + ChStd::GetAsterisk<CharaType>() + fil.second + cutChar;
	}
}

template<typename CharaType>
std::basic_string<CharaType> ChWin::FileDialogBase<CharaType>::PathToRerative()
{
	size_t tmp = fileName.find_last_of(ChStd::GetYenChara<CharaType>(), fileName.size());

	std::basic_string<CharaType> baseStr;

	baseStr = fileName;

	baseStr.replace(0, tmp + 1, ChStd::GetZeroChara<CharaType>());

	return baseStr;
}

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::SetFileName(const CharaType* _fileName)
{
	if (ChPtr::NullCheck(_fileName))return;
	fileName = _fileName;
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetTitleText()
{
	return title.size() <= 0 ? nullptr : title.c_str();
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetStartDir()
{
	return startDir.size() <= 0 ? nullptr : startDir.c_str();
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetFilterText()
{
	return filterText.c_str();
}

template<typename CharaType>
const CharaType* ChWin::FileDialogBase<CharaType>::GetBaseDir()
{
	return baseDir.c_str();
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
