#ifdef _WINDOWS_

#ifndef Ch_Win_DWind_h
#define Ch_Win_DWind_h

#include"../Texture/ChWinTexture.h"
#include"../WinGDI/ChWinBrush.h"
#include"../WinGDI/ChWinPen.h"

namespace ChWin
{
	//WindowsAPIÇÃì‡ÅAï`âÊÇéiÇÈÉNÉâÉX//
	class WindDrawer
	{
	public:

		void Release();

		void SetBrush(Brush& _brush);

		void SetPen(Pen& _pen);

		void SetRenderTarget();

		TEXTMETRIC GetTextMetric();

		void DrawStart(HWND _hWind);

		void DrawString(const std::string& _str,unsigned short x, unsigned short y);

		//void DrawTraiangle()

		void DrawEnd();
		
		static WindDrawer& GetIns()
		{
			static WindDrawer ins;
			return ins;
		}

	private:

		WindDrawer() {}
		~WindDrawer() { Release(); }

		Brush baseBrush;
		Pen basePen;
		Texture bb;

		HWND hWind = nullptr;
		HDC hDC = nullptr;

	};

}

#endif

#endif
