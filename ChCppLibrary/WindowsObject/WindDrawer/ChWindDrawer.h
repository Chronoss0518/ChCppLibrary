#ifdef _WINDOWS_

#ifndef Ch_Win_DWind_h
#define Ch_Win_DWind_h

#include<string>

#include"../Texture/ChWinTexture.h"
#include"../WinGDI/ChWinBrush.h"
#include"../WinGDI/ChWinPen.h"

namespace ChWin
{
	//WindowsAPIÇÃì‡ÅAï`âÊÇéiÇÈÉNÉâÉX//
	class WindDrawer
	{
	public://Init And Release//

		void Release();

	public://Set Functions//

		void SetBrush(Brush& _brush);

		void SetPen(Pen& _pen);

		void SetRenderTarget(HDC _renderTarget);

		void SetRenderTarget(Texture _renderTarget);

	public://Get Functions//

		TEXTMETRIC GetTextMetric();

	public:

		void DrawStart(HWND _hWind);

		inline void DrawString(const std::string& _str, const ChINTPOINT& _pos)
		{
			DrawString(_str.c_str(), _str.length(), _pos);
		}

		inline void DrawString(const std::string& _str, const int _x, const int _y)
		{
			DrawString(_str.c_str(), _str.length(), ChINTPOINT(_x, _y));
		}

		inline void DrawString(const std::wstring& _str, const ChINTPOINT& _pos)
		{
			DrawString(_str.c_str(), _str.length(), _pos);
		}

		inline void DrawString(const std::wstring& _str, const int _x, const int _y)
		{
			DrawString(_str.c_str(), _str.length(), ChINTPOINT(_x, _y));
		}

		void DrawLine(const ChINTPOINT& _startPos, const ChINTPOINT& _endPos);

		void DrawLine(const int _startX, const int _startY, const int _endX, const int _endY);

		void DrawTexture(HBITMAP _texture, const ChINTPOINT& _pos, const ChINTPOINT& _size,const ChINTPOINT& _basePos = ChINTPOINT(0,0),const unsigned long _opeCode = SRCCOPY);

		void DrawTexture(HBITMAP _texture, const int _x, const int _y, const int _w, const int _h,const int _baseX = 0, const int _baseY = 0, const unsigned long _opeCode = SRCCOPY);

		void DrawTexture(Texture& _texture, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos = ChINTPOINT(0,0));

		void DrawTexture(Texture& _texture, const int _x, const int _y, const int _w, const int _h,const int _baseX = 0,const int _baseY = 0);

		void DrawStrachTexture(HBITMAP _texture, const ChMath::Vector4Base<int>& _draw, const ChMath::Vector4Base<int>& _base, const unsigned long _opeCode = SRCCOPY,const int _stretchType = BLACKONWHITE);

		void DrawStrachTexture(HBITMAP _texture, const ChMath::Vector2Base<int>& _drawPos, const ChMath::Vector2Base<int>& _drawSize, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const unsigned long _opeCode = SRCCOPY, const int _stretchType = BLACKONWHITE);

		void DrawStrachTexture(HBITMAP _texture, const int _drawX, const int _drawY, const int _drawW, const int _drawH, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const unsigned long _opeCode = SRCCOPY, const int _stretchType = BLACKONWHITE);

		void DrawStrachTexture(Texture& _texture, const ChMath::Vector4Base<int>& _draw, const ChMath::Vector4Base<int>& _base);

		void DrawStrachTexture(Texture& _texture, const ChMath::Vector2Base<int>& _drawPos, const ChMath::Vector2Base<int>& _drawSize, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStrachTexture(Texture& _texture, const int _drawX, const int _drawY, const int _drawW, const int _drawH, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawEnd();
		
	private:

		void DrawString(const char* _str, const unsigned long _strLen, const ChINTPOINT& _pos);

		void DrawString(const wchar_t* _str, const unsigned long _strLen, const ChINTPOINT& _pos);

	private:

		Brush baseBrush;
		Pen basePen;
		
		RenderTarget bb;

		HWND hWind = nullptr;
		HDC hDC = nullptr;

	private:

		WindDrawer() {}
		~WindDrawer() { Release(); }

	public:

		static WindDrawer& GetIns()
		{
			static WindDrawer ins;
			return ins;
		}

	};

	inline WindDrawer& DrawWindow() { return WindDrawer::GetIns(); }
}

#endif

#endif
