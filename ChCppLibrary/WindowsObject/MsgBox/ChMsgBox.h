#ifdef _WINDOWS_

#ifndef Ch_Win_BMsg_h
#define Ch_Win_BMsg_h

namespace ChWin
{

	//WindowsAPIのメッセージボックスを容易に表示させるクラス//
	class MsgBox
	{
	public://Inner Enum Classes//

		typedef enum class PushButtonType : int
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
		}PBType;

		typedef enum class DisplayButtonType :unsigned int
		{
			Ok = MB_OK,
			OkCancel = MB_OKCANCEL,
			AbortRetryIgnore = MB_ABORTRETRYIGNORE,
			YesNoCancel = MB_YESNOCANCEL,
			YesNo = MB_YESNO,
			RetryCancel = MB_RETRYCANCEL,
			CancelRetryContinue = MB_CANCELTRYCONTINUE,
			Help = MB_HELP,

		}DispBType;

		typedef enum class DefaultButtonType : unsigned int
		{
			Button1 = MB_DEFBUTTON1,
			Button2 = MB_DEFBUTTON2,
			Button3 = MB_DEFBUTTON3,
			Button4 = MB_DEFBUTTON4
		}DefBType;

		typedef enum class ModalType : unsigned int
		{
			None = 0x0L,
			Application = MB_APPLMODAL,
			System = MB_SYSTEMMODAL,
			Task = MB_TASKMODAL
		}MType;

		typedef enum class DisplayIconType : unsigned int
		{
			None = 0x0L,
			Stop = MB_ICONSTOP,
			Question = MB_ICONQUESTION,
			Warning = MB_ICONWARNING,
			Information = MB_ICONINFORMATION
		}DIType;

		typedef enum class TextType : unsigned int
		{
			None = 0x0L,
			Right = MB_RIGHT,
			RTLReading = MB_RTLREADING
		}TType;

		typedef enum class MsgBoxType :unsigned int
		{
			None = 0x0L,
			SetForegRound = MB_SETFOREGROUND,
			TopMost = MB_TOPMOST,
		}MBType;

	public://Set Functions//

		inline void SetDefaultButtonType(const DefaultButtonType _type)
		{
			buttonType = static_cast<unsigned int>(_type);
		}

		inline void SetModalType(const ModalType _type)
		{
			mType = _type;
		}

		inline void SetDisplayIconType(const DisplayIconType _type)
		{
			diType = _type;
		}

		inline void SetTextType(const TextType _type)
		{
			tType = _type;
		}

		inline void SetMsgBoxType(const MsgBoxType _type)
		{
			type = _type;
		}

	public://Other Functions//

		inline void AddDisplayButtonType(const DisplayButtonType _type)
		{
			buttonType |= static_cast<unsigned int>(_type);
		}

		inline void ClearDisplayButtonType()
		{
			buttonType = 0;
		}

		PushButtonType DisplayW(
			HWND _hWnd,
			const wchar_t* _title,
			const wchar_t* _text);

		PushButtonType DisplayServiceNotificationW(
			const wchar_t* _title,
			const wchar_t* _text);

		PushButtonType DisplayA(
			HWND _hWnd,
			const char* _title,
			const char* _text);

		PushButtonType DisplayServiceNotificationA(
			const char* _title,
			const char* _text);

		PushButtonType Display(
			HWND _hWnd,
#ifdef _UNICODE
			const wchar_t* _title,
			const wchar_t* _text
#else
			const char* _title,
			const char* _text
#endif
		)
		{
#ifdef _UNICODE
			return DisplayW(_hWnd, _title, _text);
#else
			return DisplayA(_hWnd, _title, _text);
#endif
		}

		PushButtonType DisplayServiceNotification(
#ifdef _UNICODE
			const wchar_t* _title,
			const wchar_t* _text
#else
			const char* _title,
			const char* _text
#endif
		)
		{
#ifdef _UNICODE
			return DisplayServiceNotificationW(_title, _text);
#else
			return DisplayServiceNotificationA(_title, _text);
#endif
		}

		private:

			inline unsigned int CreateUType()
			{
				unsigned int uType = buttonType;
				uType |= ChStd::EnumCast(mType);
				uType |= ChStd::EnumCast(diType);
				uType |= ChStd::EnumCast(tType);
				uType |= ChStd::EnumCast(type);
				return uType;

			}

			unsigned int buttonType = 0;
			ModalType mType = ModalType::None;
			DisplayIconType diType = DisplayIconType::None;
			TextType tType = TextType::None;
			MsgBoxType type = MsgBoxType::None;
	};
}


#endif

#endif
