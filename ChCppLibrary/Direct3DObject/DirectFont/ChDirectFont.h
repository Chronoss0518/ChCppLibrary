#ifndef Ch_CPP_D3DOBJ_DFont_h
#define Ch_CPP_D3DOBJ_DFont_h

interface IDWriteFactory;
interface IDWriteTextFormat;
interface ID2D1Factory;
interface ID2D1HwndRenderTarget;
interface ID2D1SolidColorBrush;
interface IDWriteFontCollection;

enum DWRITE_FONT_WEIGHT; 
enum DWRITE_FONT_STYLE;
enum DWRITE_FONT_STRETCH;

namespace ChD3D
{
	//Direct3D10à»ç~Ç∂Ç·Ç»Ç¢Ç∆óòópÇ≈Ç´Ç»Ç¢//
	class DirectFont
	{
	public:

		enum class LocaleName
		{
			english,
			japanese,
		};

	public:

		~DirectFont()
		{
			Release();
		}

	public:

		void Init(unsigned long _w,unsigned long _h);

		void Init();

		void Release();

	private:

		bool InitBase(
			const std::wstring& _familyName,
			IDWriteFontCollection* _collection,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _fontSize,
			const std::wstring& _localeName);

	public:

		void SetTextAlignment(DWRITE_TEXT_ALIGNMENT _alignment);

		void SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT _alignment);

	public:

		void Draw();

	private:

		std::wstring GetLocaleName(LocaleName _localeName);

	private:

		IDWriteFactory* dwFactory = nullptr;
		IDWriteTextFormat* textFormat = nullptr;
		ID2D1Factory* d2dFactory = nullptr;
		ID2D1HwndRenderTarget* renderTarget = nullptr;
		ID2D1SolidColorBrush* solidBrush = nullptr;

	};

}

#endif