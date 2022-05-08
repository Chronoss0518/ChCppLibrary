#ifdef _WINDOWS_

#ifndef Ch_Win_CWind_h
#define Ch_Win_CWind_h

namespace ChWin
{
	class WindClassStyle;

	//WindowsAPI�̓�WindowClass��p�����I�u�W�F�N�g���i��N���X//
	class WindClassObject:public ChCp::Initializer
	{
	public://ConstructorDestructor//

		inline WindClassObject() { Init(); }

		inline WindClassObject(const WNDCLASS& _cls) { Init(_cls); }

		inline ~WindClassObject() { Release(); }
		
	public://InitAndRelease//

		void Init();

		void Init(const WNDCLASS& _cls);

		void Release();

	public://SetFunction//

		void SetStyle(const unsigned int _style);

		void SetStyle(const WindClassStyle* _style);

		void SetIcon(const HICON _icon);

		void SetCursol(const HCURSOR _cursor);

		//�E�B���h�E�N���X�\���̌�̒ǉ��o�C�g��//
		void SetClsExtra(const int _byteNum = 0);

		//�E�B���h�E�C���X�^���X�̌�̒ǉ��o�C�g��//
		void SetWndExtra(const int _byteNum = 0);

		void SetBackgroundColor(const HBRUSH _brush);

		void SetInstance(const HINSTANCE _hInst);

		void SetWindProcedure(WNDPROC _windProc);

	public://GetFunction//

		inline std::string GetWindClassName() { return className; }

	public:

		//Set�֐����Z�b�g���ꂽ�������ɃN���X��o�^����//
		//�N���X�����󕶎��̏ꍇ�͓o�^����Ȃ�//
		void RegistClass(const std::string& _className);

	protected:

		WNDCLASS cls;
		std::string className = "";

	};
}

#endif

#endif
