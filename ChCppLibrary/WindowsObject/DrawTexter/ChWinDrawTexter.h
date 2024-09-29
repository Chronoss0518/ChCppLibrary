#ifdef _WINDOWS_

#ifndef Ch_Win_DTexter_h
#define Ch_Win_DTexter_h

#include<string>

namespace ChWin
{
	class DrawTexterBase :public ChCp::Initializer
	{
	public://InitAndRelease//

		virtual void Release();

	public://SetFunction//

		inline void SetWind(const HWND& _wind)
		{
			if (ChPtr::NullCheck(_wind))return;
			hOwn = _wind;

			InvalidateRect(hOwn, nullptr, true);
			UpdateWindow(hOwn);
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃêFê›íË//
		inline void SetFontColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		{
			fontColor.a = _a;
			fontColor.r = _r;
			fontColor.g = _g;
			fontColor.b = _b;
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃêFê›íË//
		inline void SetFontColor(const ChVec4& _color)
		{
			ChVec4 tmpColor = _color * 255;
			ChMath::Vector4Base<unsigned char> col;
			col.val = tmpColor.val;
			SetFontColor(col.r, col.g, col.b, col.a);
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃêFê›íË//
		inline void SetFontColor(const ChMath::Vector4Base<unsigned char>& _color)
		{
			SetFontColor(_color.r, _color.g, _color.b, _color.a);
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃêFê›íË//
		inline void SetBackGroundColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		{
			backColor.a = _a;
			backColor.r = _r;
			backColor.g = _g;
			backColor.b = _b;
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃîwåiêFê›íË//
		inline void SetBackGroundColor(const ChMath::Vector4Base<unsigned char>& _color)
		{
			SetBackGroundColor(_color.r, _color.g, _color.b, _color.a);
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃîwåiêFê›íË//
		inline void SetBackGroundColor(const ChVec4& _color)
		{
			ChVec4 tmpColor = _color * 255;
			ChMath::Vector4Base<unsigned char> col;
			col.val = tmpColor.val;
			SetBackGroundColor(col.r, col.g, col.b, col.a);
		}


	protected://ConstructerDestructer//

		inline DrawTexterBase() {}

		virtual ~DrawTexterBase()
		{
			Release();
		}

		HWND hOwn = nullptr;

		HFONT fontData = nullptr;

		ChMath::Vector4Base<unsigned char> fontColor;
		ChMath::Vector4Base<unsigned char> backColor;
	};

	class DrawTexterA :public DrawTexterBase
	{
	public://InitAndRelease//

		void Init(const HWND& _baseWindHandl);

	public://SetFunction//

		void SetFontData(
			const long& _FWidth,
			const long& _FHeight,
			const long& _FSize,
			const bool& _ULFlg);

	public://Other Functions//

		void Draw(
			const std::string& _drawText,
			const long& _x,
			const long& _y)
		{
			Draw(_drawText.c_str(), static_cast<int>(_drawText.length()), _x, _y);
		}

		void Draw(
			HDC _hdc,
			const std::string& _drawText,
			const long& _x,
			const long& _y)
		{
			Draw(_hdc, _drawText.c_str(), static_cast<int>(_drawText.length()), _x, _y);
		}

	protected:

		void Draw(
			const char* _drawText,
			const int _drawTextLength,
			const long& _x,
			const long& _y);

		void Draw(
			HDC _hdc,
			const char* _drawText,
			const int _drawTextLength,
			const long& _x,
			const long& _y);

	private://ConstructerDestructer//

		inline DrawTexterA() {}

	public:

		inline static DrawTexterA& GetIns()
		{
			static DrawTexterA ins;
			return ins;
		}

	};

	class DrawTexterW :public DrawTexterBase
	{
	public://InitAndRelease//

		void Init(const HWND& _baseWindHandl);

	public://SetFunction//

		void SetFontData(
			const long& _FWidth,
			const long& _FHeight,
			const long& _FSize,
			const bool& _ULFlg);

	public://Other Functions//

		void Draw(
			const std::wstring& _drawText,
			const long& _x,
			const long& _y)
		{
			Draw(_drawText.c_str(), static_cast<int>(_drawText.length()), _x, _y);
		}

		void Draw(
			HDC _hdc,
			const std::wstring& _drawText,
			const long& _x,
			const long& _y)
		{
			Draw(_hdc, _drawText.c_str(), static_cast<int>(_drawText.length()), _x, _y);
		}

	protected:

		void Draw(
			const wchar_t* _drawText,
			const int _drawTextLength,
			const long& _x,
			const long& _y);

		void Draw(
			HDC _hdc,
			const wchar_t* _drawText,
			const int _drawTextLength,
			const long& _x,
			const long& _y);

	private://ConstructerDestructer//

		inline DrawTexterW() {}

	public:

		inline static DrawTexterW& GetIns()
		{
			static DrawTexterW ins;
			return ins;
		}

	};

	inline DrawTexterA& TextDrawerA() { return DrawTexterA::GetIns(); };

	inline DrawTexterW& TextDrawerW() { return DrawTexterW::GetIns(); };

	using DrawTexter =
#ifdef UNICODE
		DrawTexterW;
#else
		DrawTexterA;
#endif

	inline DrawTexter& TextDrawer() { return DrawTexter::GetIns(); };

}

#endif

#endif