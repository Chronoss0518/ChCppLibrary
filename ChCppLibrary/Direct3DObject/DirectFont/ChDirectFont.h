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
	class DirectFont;

	class TextFormatObject
	{
	public:
		
		friend DirectFont;

		void SetTextAlignment(DWRITE_TEXT_ALIGNMENT _alignment);

		void SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT _alignment);

	private:
		IDWriteTextFormat* textFormat = nullptr;
	};

	class BrushObject
	{
	public:

		friend DirectFont;

	private:

		ID2D1SolidColorBrush* brush = nullptr;
	};

	//Direct3D10�ȍ~����Ȃ��Ɨ��p�ł��Ȃ�//
	class DirectFont
	{
	public:

		enum class LocaleNameId
		{
			English,
			Japanese,
		};

	public:

		~DirectFont()
		{
			Release();
		}

	public:

		void Init(
			unsigned long _w,
			unsigned long _h,
			HWND _hwnd,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			unsigned long _w,
			unsigned long _h,
			IDXGISurface* _surface,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Release();

		//���ݍ쐬����Ă���TextFormatObject�̒��g�����ׂĔj�����܂�//
		void ReleaseTextFormat();

		//���ݍ쐬����Ă���BrushObject�̒��g�����ׂĔj�����܂�//
		void ReleaseBrush();

	private:

		bool InitBase();

	public:

		TextFormatObject CreateTextFormat(
			const std::wstring& _familyName,
			IDWriteFontCollection* _collection,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _fontSize);

		BrushObject CreateBrush(const ChVec4& _color);

	public:

		//�f�t�H���g�ł�False//
		void SetClearDisplayFlg(bool _flg) { clearDisplayFlg = _flg; }

		void SetClearDisplayColor(const ChVec4& _color) { clearDisplayColor = _color; }

	public:

		void DrawStart();

		//���ォ��0,0�̃f�B�X�v���C���W�n�Ōv�Z����//
		void Draw(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& brushObject,
			const ChVec4& _drawRect = ChVec4(0.0f, 0.0f, 1280.0f, 720.0f))
		{
			if (!thisDrawerFlg)return;
			if (ChPtr::NullCheck(_textFormat.textFormat))return;
			if (ChPtr::NullCheck(brushObject.brush))return;

			D2D1_RECT_F layoutRect;
			layoutRect = D2D1::RectF(0.0f);
			layoutRect.left = _drawRect.left;
			layoutRect.top = _drawRect.top;
			layoutRect.right = _drawRect.right;
			layoutRect.bottom = _drawRect.bottom;


			renderTarget->DrawText(
				_text.c_str(),        // The string to render.
				_text.length(),    // The string's length.
				_textFormat.textFormat,    // The text format.
				&layoutRect,       // The region of the window where the text will be rendered.
				brushObject.brush     // The brush used to draw the text.
			);

		}

		void DrawEnd();

	private:

		std::wstring GetLocaleName(LocaleNameId _localeName);

		static bool& GetDrawFlg() { static bool flg; return flg; }

	private:

		IDWriteFactory* dwFactory = nullptr;
		ID2D1Factory* d2dFactory = nullptr;
		ID2D1RenderTarget* renderTarget = nullptr;

		std::vector<IDWriteTextFormat*>textFormatList;
		std::vector<ID2D1SolidColorBrush*>brushList;

		LocaleNameId localeNameId = LocaleNameId::English;
		bool thisDrawerFlg = false;

		bool clearDisplayFlg = false;
		ChVec4 clearDisplayColor = ChVec4(0.0f, 0.0f, 0.0f, 0.0f);
	};

}

#endif