#include<Windows.h>
#include"ChWinFileDialog.h"

///////////////////////////////////////////////////////////////////////////////////////
//FileDialog���\�b�h//
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChWin::FileDialogBase<CharaType>::Release()
{
	SetInitFlg(false);
}
template void ChWin::FileDialogBase<char>::Release();
template void ChWin::FileDialogBase<wchar_t>::Release();