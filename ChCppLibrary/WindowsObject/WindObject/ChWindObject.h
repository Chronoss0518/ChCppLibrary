#ifdef _WINDOWS_

#ifndef Ch_Win_WCls_h
#define Ch_Win_WCls_h

namespace ChWin
{


	class WindObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�n���h���̎擾//
		inline HWND GethWnd(void) const { return hWnd; }

		//���b�Z�[�W�̒l��Ԃ��֐�//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		///////////////////////////////////////////////////////////////////////////////////

	private:

		HWND hWnd = nullptr;
		MSG msg;
		
	};

}

#endif

#endif
