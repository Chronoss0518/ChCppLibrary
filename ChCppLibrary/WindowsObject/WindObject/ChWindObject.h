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

		//Window�ɘg��t����//
		void SetBorder();

		//Window�Ƀ^�C�g����t����//
		void SetCaption();

		//Window�Ɏq�K�w������t����//
		void SetChild();

		//Window�z����Window�̕`��͈͂�`�悵�Ȃ��悤�ɂ���//
		void SetClipChildren();

		//Window�z����Window���m���d�Ȃ��Ă��镔����`�悵�Ȃ��悤�ɂ���//
		void SetClipSiblings();

		//Window�͏������_�Ŗ�����Ԃɂ���//
		void SetDisabled();

		//Window�Ƀ_�C�A���O�{�b�N�X�Ɠ������E����t����//
		void SetDLGFrame();

		//Window��Control�ł���O���[�v�̍ŏ��ł��邱�Ƃ��`����//
		void SetGroup();

		//Window�ɐ����̃X�N���[���o�[��t����//
		void SetHScroll();

		//Window�͍ŏ�����T�C�Y���ő��Ԃŕ\�������//
		void SetMaxmize();

		//Window�ɍő剻�{�^����t����//
		void SetMaximaizeBox();

		//Window�͍ŏ�����T�C�Y���ŏ���Ԃŕ\�������//
		void SetMinimize();

		//Window�ɍŏ����{�^����t����//
		void SetMinimizeBox();

		//Window�Ƀ^�C�g���o�[�Ƌ��E����������Window���d�˂�//
		void SetOverlapped();

		//Overlapped��Caption,SysMenu,SyzeBox,MinimizeBox,MaximizeBox��ǉ����������X�^�C��//
		void SetOverlappedWindow();

		//Window���|�b�v�A�b�v�E�B���h�E�ɂ���B�������Child�ƕ��p�ł��Ȃ�//
		void SetPopup();

		//Popup��Border,SysMenu��ǉ����������X�^�C��//
		void SetPopupWindow();

		//Window�ɃT�C�Y��ύX�\�ȋ��E����t����//
		void SetSizeBox();

		//Window�̃^�C�g���o�[�ɃE�B���h�E���j���[��t����//
		void SetSysMenu();

		//Window��User��Tab�L�[���������ۂɃt�H�[�J�X���󂯎���悤�ɂ���//
		void SetTabStop();

		//Window���ŏ�����\�������悤�ɂ���//
		void SetVisible();

		//Window�ɐ����X�N���[���o�[��t����//
		void SetVScroll();

		///////////////////////////////////////////////////////////////////////////////////
		//Get Function//

		inline unsigned long GetStyle()const  { return windStyle; }

		///////////////////////////////////////////////////////////////////////////////////

		//�Z�b�g����Ă���Style��0�ɂ���//
		inline void Clear() { windStyle = 0; }

	private:

		unsigned long windStyle = 0;

	};


	//WindowsAPI�̓��AWindow�̍쐬�ƊǗ����i��N���X//
	class WindObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{
			CreateWindowWChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, WS_OVERLAPPEDWINDOW
				| WS_CLIPCHILDREN
				| WS_GROUP
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{
			CreateWindowWChar(
				_appName
				, _windClassName
				, _windSize.w
				, _windSize.h
				, WS_OVERLAPPEDWINDOW
				| WS_CLIPCHILDREN
				| WS_GROUP
				, _hInst
				, _windPos.x
				, _windPos.y);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, _windStyle
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windSize.w
				, _windSize.h
				, _windStyle
				, _hInst
				, _windPos.x
				, _windPos.y);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, _windStyle.GetStyle()
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

			CreateWindowWChar(
				_appName
				, _windClassName
				, _windSize.w
				, _windSize.h
				, _windStyle.GetStyle()
				, _hInst
				, _windPos.x
				, _windPos.y);
		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{
			CreateWindowChar(
				_appName
				, _windClassName
				, _windWidth
				, _windHeight
				, WS_OVERLAPPEDWINDOW
				| WS_CLIPCHILDREN
				| WS_GROUP
				, _hInst
				, _windXPos
				, _windYPos);
		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos = 10,
			const unsigned int _windYPos = 10)
		{

		}

		inline void Create(
			const char* _appName,
			const char* _windClassName,
			const ChMath::Vector2Base<unsigned int>& _windSize,
			const WindStyle& _windStyle,
			const HINSTANCE _hInst,
			const ChMath::Vector2Base<unsigned int>& _windPos = ChMath::Vector2Base<unsigned int>(10, 10))
		{

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�n���h���̎擾//
		inline HWND GethWnd(void) const { return hWnd; }

		//���b�Z�[�W�̒l��Ԃ��֐�//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		//Window�̃T�C�Y���擾����֐�//
		inline const ChMath::Vector2Base<unsigned int> GetWindSize()const { return windSize; }

		//Window�̍���̈ʒu���擾����֐�//
		inline const ChMath::Vector2Base<unsigned int> GetWindPos()const { return windPos; }

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

	private:

		void SetRegister();

		///////////////////////////////////////////////////////////////////////////////////

		void CreateWindowWChar(
			const wchar_t* _appName,
			const wchar_t* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos,
			const unsigned int _windYPos);

		void CreateWindowChar(
			const char* _appName,
			const char* _windClassName,
			const unsigned int _windWidth,
			const unsigned int _windHeight,
			const unsigned long _windStyle,
			const HINSTANCE _hInst,
			const unsigned int _windXPos,
			const unsigned int _windYPos);

		///////////////////////////////////////////////////////////////////////////////////



		HWND hWnd = nullptr;
		MSG msg = {0};
		ChMath::Vector2Base<unsigned int> windSize;
		ChMath::Vector2Base<unsigned int> windPos;
	};

}

#endif

#endif
