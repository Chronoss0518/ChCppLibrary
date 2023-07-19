#ifdef _WINDOWS_

#ifndef Ch_Win_BObj_h
#define Ch_Win_BObj_h

#include"../../BaseIncluder/ChBase.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	struct CPOINT :public POINT
	{
		CPOINT&operator =(const POINT& _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;
			return *this;
		}

		CPOINT operator + (const POINT& _Pos)const
		{
			CPOINT Tmp = *this;
			Tmp.x = _Pos.x;
			Tmp.y = _Pos.y;
			return Tmp;
		}
	};


	 void ObjUpdate(const WPARAM& _wParam);

	 void WindMoveUpdate(const HWND _hWnd, LPARAM _lParam);

	 void WindSizeUpdate(const HWND _hWnd, LPARAM _lParam);

	typedef class WindBaseObject :public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline WindBaseObject() {};

		virtual ~WindBaseObject()
		{
			Release();
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _hWnd);

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline const HWND GethWnd()const { return hIns; }

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//移動させないためのフラグ//
		inline void SetNoMoveFlg(const bool _flg) { notCMoveFlg = _flg; }

		//サイズ変更させないためのフラグ//
		inline void SetNoSizeFlg(const bool _flg) { notCSizeFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////////

		void Move(const int _x
			, const int _y
			, const int _w
			, const int _h);

		void Move(const int _x
			, const int _y);

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void Update(const WPARAM& _wParam)
		{
			UpdateWindow(hIns);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		void ReSize(
			const int _w
			, const int _h);

		///////////////////////////////////////////////////////////////////////////////////////

		friend void ObjUpdate(const WPARAM& _wParam);

		friend void WindMoveUpdate(const HWND _hWnd, LPARAM _lParam);

		friend void WindSizeUpdate(const HWND _hWnd, LPARAM _lParam);

	protected:

		static std::string className;

		HWND hIns = nullptr;

		DWORD myID = 0;

		HWND hOwn = nullptr;

		bool notCSizeFlg = false;
		bool notCMoveFlg = false;


		bool startMoveFlg = false;

		void RegisterObj();
		
		long x{ 0 };
		long y{ 0 };
		long w{ 0 };
		long h{ 0 };

	private:

		static std::map<unsigned long, WindBaseObject*>objList;

	}WindObj;
}

#endif

#endif