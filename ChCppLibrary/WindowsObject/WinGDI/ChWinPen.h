#ifdef _WINDOWS_

#ifndef Ch_Win_Pen_h
#define Ch_Win_Pen_h

namespace ChWin
{
	enum class PenStyle :int
	{
		Solid = PS_SOLID,
		Dash = PS_DASH,
		Dot = PS_DOT,
		DashDot = PS_DASHDOT,
		DashDotDot = PS_DASHDOTDOT,
		InSideFrame = PS_INSIDEFRAME
	};

	class Pen
	{
	public:

		inline ~Pen() { Release(); }

		void Release();

		void CreatePen(
			const unsigned char _r,
			const unsigned char _g,
			const unsigned char _b,
			unsigned short _width = 1,
			const PenStyle _style = PenStyle::Solid);

		void CreateNullPen();

		HPEN SelectPen(HDC _dc);

		void SetPen(HPEN _pen)
		{
			if (ChPtr::NullCheck(_pen))return;

			Release();

			pen = _pen;
		};

	private:

		HPEN pen = nullptr;
	};
}

#endif

#endif