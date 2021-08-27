#ifdef _WINDOWS_

#ifndef Ch_Win_BWind_h
#define Ch_Win_BWind_h

namespace ChWin
{

	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);

	//WindowsAPI�̓�WindowClass��p�����I�u�W�F�N�g���i��N���X//
	class WindClassObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		inline WindClassObject() { Init(); }

		inline WindClassObject(const WNDCLASS& _cls) { Init(_cls); }

		inline ~WindClassObject() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Init(const WNDCLASS& _cls);

		void Init(const HINSTANCE _hInst);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetStyle(const unsigned int _style);

		void SetWindProcedure(WNDPROC _WindProc);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline WNDCLASS GetWindClass() { return cls; }

		///////////////////////////////////////////////////////////////////////////////////
		
		//Set�֐����Z�b�g���ꂽ�������ɃN���X��o�^����//
		//�N���X�����󕶎��̏ꍇ�͓o�^����Ȃ�//
		void RegistClass();

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		WNDCLASS cls;

		LRESULT(*WndProc)(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam) = nullptr;

		friend LRESULT CALLBACK ChWin::WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

	private:

		static std::map<HWND, WindClassObject*>& WindManager();

	public:

		static WindClassObject* GetWindObject(const HWND* _hWnd);

	};
}

#endif

#endif
