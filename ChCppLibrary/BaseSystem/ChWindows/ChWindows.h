#ifdef _WINDOWS_

#ifndef Ch_Game_Windows_h
#define Ch_Game_Windows_h

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/WindObject/ChWindObject.h"
#include"../../WindowsObject/WindClassObject/ChWindClassObject.h"

namespace ChSystem
{
	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);


	//Windows�ō쐬���ꂽWind��Windows�Ɋւ�����o�͂Ȃǂ��Ǘ������A//
	//WIndows�S�̂̊Ǘ��N���X//
	class Windows :public BaseSystem,public ChCp::Releaser
	{
	public:

		Windows() {};

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Wind�̐���(stringVer)//
		void Init(
			const std::string& _appName,
			const std::string& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::string& _appName,
			const std::string& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const int _initWindPosX,
			const int _initWindPosY,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const ChWin::WindCreater& _creater,
			const std::string& _appName,
			const std::string& _windClassName,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::string& _appName,
			const std::string& _className,
			const unsigned long _dwStyle,
			const int _initWindPosX,
			const int _initWindPosY,
			const int _windWidth,
			const int _windHeight,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		//Wind�̐���(wstringVer)//
		void Init(
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const int _windWidth,
			const int _windHeight,
			const int _initWindPosX,
			const int _initWindPosY,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const ChWin::WindCreater& _creater,
			const std::wstring& _appName,
			const std::wstring& _windClassName,
			const HINSTANCE _hInst,
			const int _nCmdShow);

		void Init(
			const std::wstring& _appName,
			const std::wstring& _className,
			const unsigned long _dwStyle,
			const int _initWindPosX,
			const int _initWindPosY,
			const int _windWidth,
			const int _windHeight,
			HINSTANCE _hInst,
			const int _nCmdShow,
			const unsigned long _exStyle = 0,
			HWND _parent = nullptr,
			HMENU _hMenu = nullptr,
			LPVOID _param = nullptr);

		//Wind�̉��//
		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetDefaultWinProcedure(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce)
		{
			wndObject.SetDefaultWindProcedure(_proce);
		}

		inline void SetWinProcedure(const unsigned int _windowMessage ,const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _proce)
		{
			wndObject.SetWindProcedure(_windowMessage, _proce);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�n���h���̎擾//
		inline HWND GethWnd(void) const { return wndObject.GethWnd(); }

		//���b�Z�[�W�̒l��Ԃ��֐�//
		inline const LPMSG GetReturnMassage(void) const { return wndObject.GetReturnMassage(); }

		unsigned long GetNowTime()override { return timeGetTime(); }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�W���̃J�[�\���̕\���t���O//
		inline void IsCursollShou(const ChStd::Bool _f) { ShowCursor(_f); }

		//�L�[���������ۂ̃`�F�b�N���s���֐�//
		ChStd::Bool IsPushKey(const int _key)override;

		//�L�[���������ۂɒ��������܂񂾂̃`�F�b�N���s���֐�//
		ChStd::Bool IsPushKeyNoHold(const int _key)override;

		//�|�[�Y�����ǂ����𔻒f����֐��B//
		//�������̓|�[�Y�ֈڍs����{�^��//
		//�߂�l��True�������ꍇ�̓|�[�Y��//
		ChStd::Bool IsPause(const int _key)override;

		//WindMassage���m�F����֐�//
		ChStd::Bool IsUpdate()override;

		///////////////////////////////////////////////////////////////////////////////////

		void ErrerMessage(
			const std::string& _mainStr
			, const std::string& _subStr)override
		{
			WMessageA(_mainStr, _subStr);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//���b�Z�[�W�{�b�N�X�p�֐�//
		inline void WMessageA(
			const std::string& _mainStr
			, const std::string& _subStr)
		{
			if (ChPtr::NullCheck(wndObject.GethWnd()))return;

			MessageBoxA(
				wndObject.GethWnd()
				, &_mainStr[0]
				, &_subStr[0]
				, MB_OK);

		}

		//���b�Z�[�W�{�b�N�X�p�֐�//
		inline void WMessageW(
			const std::wstring& _mainStr
			, const std::wstring& _subStr)
		{
			if (ChPtr::NullCheck(wndObject.GethWnd()))return;

			MessageBoxW(
				wndObject.GethWnd()
				, &_mainStr[0]
				, &_subStr[0]
				, MB_OK);

		}

		friend LRESULT CALLBACK ChSystem::WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		//Windows�ł̃L�[�S�̂��`�F�b�N���邽�߂̊֐�//
		void SetKeyCode();

		///////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool isKeyUpdate;

		HINSTANCE inst = nullptr;
		ChWin::WindObject wndObject;
		ChWin::WindClassObject cObject;


	};

	static inline void ToRelativePath(std::string&_path)
	{

		if (_path.find(":\\") == _path.npos && _path.find(":/") == _path.npos)return;

		std::string tmp;


		{

			char* tmp2 = nullptr;
			tmp2 = new char[256];

			GetCurrentDirectory(256, tmp2);
			tmp = tmp2;

			delete[] tmp2;

		}

		std::string SetCutChar = "/";
		{

			std::string OutCutChar = "\\";

			while (1)
			{
				size_t tmpLen = tmp.find(OutCutChar, 0);
				if (tmpLen == tmp.npos)break;
				tmp.replace(tmpLen, OutCutChar.size(), SetCutChar);

			}
			while (1)
			{
				size_t tmpLen = _path.find(OutCutChar, 0);
				if (tmpLen == _path.npos)break;
				_path.replace(tmpLen, OutCutChar.size(), SetCutChar);

			}

			std::string tmpBackChar = "";


			while (1)
			{
				size_t tmpLen = _path.find(tmp);

				if (tmpLen != _path.npos)break;

				tmpLen = tmp.rfind(SetCutChar, tmp.length());

				tmp.replace(tmpLen, tmp.length() - tmpLen, "");

				tmpBackChar += "../";

			}



			_path.replace(0, tmp.length() + 1, "");

			_path = tmpBackChar + _path;



		}

	}
}

#endif
//CopyRight Chronoss0518 2018/08

#endif