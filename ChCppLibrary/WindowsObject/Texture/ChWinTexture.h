#ifdef _WINDOWS_

#ifndef Ch_Win_DWind_h
#define Ch_Win_DWind_h

namespace ChWin
{

	enum class FillType :unsigned long
	{
		PatCopy = PATCOPY,
		PatInvert = PATINVERT,
		DstInvert = DSTINVERT,
		Blackness = BLACKNESS,
		Whiteness = WHITENESS
	};

	class Texture
	{
	public:

		void CreateTexture(ChSystem::Windows& _win, const std::string& _fileName);

		void CreateTexture(HINSTANCE _instance, const std::string& _fileName);

		void CreateTexture(HWND _hWind, const unsigned short _widht, const unsigned short _height);

		void CreateTexture(HWND _hWind, const ChMath::Vector2Base<unsigned short>& _windSize);

		void FillTexture(const FillType _type = FillType::Whiteness);

		void SetRenderTarget();

		void Draw(HWND _hWind, const unsigned short _x, const unsigned short _y, const unsigned short _width, const unsigned short _height );

	private:

		HBITMAP mainTexture = nullptr;

		HDC dc = nullptr;

	};

}

#endif

#endif
