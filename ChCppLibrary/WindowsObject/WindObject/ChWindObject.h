#ifdef _WINDOWS_

#ifndef Ch_Win_WCls_h
#define Ch_Win_WCls_h

namespace ChWin
{
	//WindowStyle���Ǘ�����N���X//
	class WindStyle
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//Set Function//

		inline void SetStyle(const unsigned long _windStyles) { windStyle = _windStyles; }

		void SetBorder();

		void SetCaption();

		void SetChild();

		void SetClipChildren();

		void SetClipSiblings();

		void SetDisabled();

		void SetDLGFrame();

		void SetGroup();

		void SetHScroll();

		void SetMaxmize();

		void SetMaximaizeBox();

		void SetMinimize();

		void SetMinimizeBox();

		void SetOverlapped();

		void SetOverlappedWindow();

		void SetPopup();

		void SetSizeBox();

		void SetSysMenu();

		void SetTabStop();

		void SetVisible();

		void SetVScroll();

		///////////////////////////////////////////////////////////////////////////////////
		//Get Function//

		inline unsigned long GetStyle() { return windStyle; }

		///////////////////////////////////////////////////////////////////////////////////

		void Clear();

	private:

		unsigned long windStyle = 0;


	};


	//WindowsAPI�̓��AWindow�̍쐬�ƊǗ����i��N���X//
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
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
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

		void Init(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int> _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�n���h���̎擾//
		inline HWND GethWnd(void) const { return hWnd; }

		//���b�Z�[�W�̒l��Ԃ��֐�//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Window�̃T�C�Y���擾����֐�//
		inline const ChMath::Vector2Base<unsigned int> GetWindSize()const { return windSize; }

		///////////////////////////////////////////////////////////////////////////////////

	private:

		HWND hWnd = nullptr;
		MSG msg = {0};
		ChMath::Vector2Base<unsigned int> windSize;
	};

}

#endif

#endif
