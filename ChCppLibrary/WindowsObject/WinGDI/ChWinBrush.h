#ifdef _WINDOWS_

#ifndef Ch_Win_Brush_h
#define Ch_Win_Brush_h

namespace ChWin
{
	class Texture;

	enum class HatchType :int
	{
		BDIAGONAL = HS_BDIAGONAL,
		CROSS = HS_CROSS,
		DIAGCROSS = HS_DIAGCROSS,
		FDIAGONAL = HS_FDIAGONAL,
		HORIZONTAL = HS_HORIZONTAL,
		VERTICAL = HS_VERTICAL
	};

	class Brush
	{
	public:

		~Brush() { Release(); }

		void Release();

		void CreateSolidBrush(const unsigned char _r, const unsigned char _g, const unsigned char _b);

		inline void CreateHatchBrush(const unsigned char _r, const unsigned char _g, const unsigned char _b, const HatchType _type = HatchType::CROSS) 
		{
			CreateHatchBrush(_r, _g, _b, static_cast<int>(_type));
		}

		void CreateHatchBrush(const unsigned char _r, const unsigned char _g, const unsigned char _b, const int _type = HS_CROSS);
		
		void CreateNullBrush();

		void CreatePatterBrush(const Texture* _tex);

		void CreatePatterBrush(const Texture& _tex);

		void CreatePatterBrush(const HBITMAP _tex);

		void SetBrush(HBRUSH _brush);

		HBRUSH SelectBrush(HDC _dc);

		void FillRect(HDC _dc, const RECT& _rec);

	private:

		bool createFlg = false;;
		HBRUSH brush = nullptr;
	};
}

#endif

#endif