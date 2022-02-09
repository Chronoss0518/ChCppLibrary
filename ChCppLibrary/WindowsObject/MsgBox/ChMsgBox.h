#ifdef _WINDOWS_

#ifndef Ch_Win_BMsg_h
#define Ch_Win_BMsg_h

namespace ChWin
{
	//WindowsAPIのメッセージボックスを容易に表示させるクラス//
	class MsgBox
	{
	public:
		
		enum class PushButtonType : int
		{
			Ok = IDOK,
			Cancel = IDCANCEL,
			Abort = IDABORT,
			Retry = IDRETRY,
			Ignore = IDIGNORE,
			Yes = IDYES,
			No = IDNO,
			Tryagain = IDTRYAGAIN,
			Continue = IDCONTINUE
		};

		enum DisplayButtonType :unsigned int
		{
			Ok = MB_OK,
			OkCancel = MB_OKCANCEL,
			AbortRetryIgnore = MB_ABORTRETRYIGNORE,
			YesNoCancel = MB_YESNOCANCEL,
			YesNo = MB_YESNO,
			RetryCancel = MB_RETRYCANCEL,
			CancelRetryContinue = MB_CANCELTRYCONTINUE,
			Help = MB_HELP,
		};

		enum class DefaultButtonType : unsigned int
		{
			Button1 = MB_DEFBUTTON1,
			Button2 = MB_DEFBUTTON2,
			Button3 = MB_DEFBUTTON3,
			Button4 = MB_DEFBUTTON4
		};

		enum class ModalType : unsigned int
		{
			None = 0x0L,
			Application = MB_APPLMODAL,
			System = MB_SYSTEMMODAL,
			Task = MB_TASKMODAL
		};

		enum DisplayIconType : unsigned int
		{
			Stop = MB_ICONSTOP,
			Question = MB_ICONQUESTION,
			Warning = MB_ICONWARNING,
			Information = MB_ICONINFORMATION
		};

		enum TextType : unsigned int
		{
			Right = MB_RIGHT,
			RTLReading = MB_RTLREADING
		};

		enum MsgBoxType :unsigned int
		{
			SetForegRound = MB_SETFOREGROUND,
			TopMost = MB_TOPMOST,
		};

#ifdef _UNICODE

		inline static PushButtonType Display(
			HWND _hWnd,
			const wchar_t* _text,
			const wchar_t* _title,
			const unsigned int _uType,
			const DefaultButtonType _dType = DefaultButtonType::Button1,
			const ModalType _mType = ModalType::None)
		{

			unsigned int uType = _uType;
			uType |= ChStd::EnumCast(_dType);
			uType |= ChStd::EnumCast(_mType);

			return (PushButtonType)MessageBoxW(_hWnd, _text, _title, uType);
		}

		inline static PushButtonType DisplayServiceNotification(
			const wchar_t* _text,
			const wchar_t* _title,
			const unsigned int _uType,
			const DefaultButtonType _dType = DefaultButtonType::Button1,
			const ModalType _mType = ModalType::None)
		{

			unsigned int uType = _uType;
			uType |= ChStd::EnumCast(_dType);
			uType |= ChStd::EnumCast(_mType);
			uType |= MB_SERVICE_NOTIFICATION;

			return (PushButtonType)MessageBoxW(nullptr, _text, _title, uType);
		}

#endif

		inline static PushButtonType Display(
			HWND _hWnd,
			const char* _text,
			const char* _title,
			const unsigned int _uType,
			const DefaultButtonType _dType = DefaultButtonType::Button1,
			const ModalType _mType = ModalType::None)
		{

			unsigned int uType = _uType;
			uType |= ChStd::EnumCast(_dType);
			uType |= ChStd::EnumCast(_mType);

			return (PushButtonType)MessageBoxA(_hWnd, _text, _title, uType);
		}

		inline static PushButtonType DisplayServiceNotification(
			const char* _text,
			const char* _title,
			const unsigned int _uType,
			const DefaultButtonType _dType = DefaultButtonType::Button1,
			const ModalType _mType = ModalType::None)
		{
			unsigned int uType = _uType;
			uType |= ChStd::EnumCast(_dType);
			uType |= ChStd::EnumCast(_mType);
			uType |= MB_SERVICE_NOTIFICATION;

			return (PushButtonType)MessageBoxA(nullptr, _text, _title, uType);
		}

	};
}

#endif

#endif
