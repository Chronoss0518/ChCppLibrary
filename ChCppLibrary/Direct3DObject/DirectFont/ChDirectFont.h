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

		void SetColor(const D2D_COLOR_F& _color);

		void SetColor(const ChVec4& _color);

	private:

		ID2D1SolidColorBrush* brush = nullptr;
	};

	class LayoutObject
	{
	public:

		friend DirectFont;

	public:

		//_range��length��0�̏ꍇ�܂���length + startPosition��textLength���傫���ꍇ�͓o�^����Ă��邷�ׂĂ̕����T�C�Y��ύX����//
		void SetFontSize(float _size, const DWRITE_TEXT_RANGE& _range = { 0, 0 });

		//_range��length��0�̏ꍇ�܂���length + startPosition��textLength���傫���ꍇ�͓o�^����Ă��邷�ׂĂ̕����Ɏ���������ݒ肷��//
		void SetFontStrikethrough(bool _useFlg, const DWRITE_TEXT_RANGE& _range = { 0, 0 });

		//_range��length��0�̏ꍇ�܂���length + startPosition��textLength���傫���ꍇ�͓o�^����Ă��邷�ׂĂ̕����ɉ�����ݒ肷��//
		void SetFontUnderline(bool _useFlg, const DWRITE_TEXT_RANGE& _range = { 0, 0 });

		void SetLayoutBoxWidth(float _width);

		void SetLayoutBoxHeight(float _witdh);

		inline void SetLayoutBoxSize(const ChVec2& _size)
		{
			SetLayoutBoxWidth(_size.w);
			SetLayoutBoxHeight(_size.h);
		}

		//_range��length��0�̏ꍇ�܂���length + startPosition��textLength���傫���ꍇ�͓o�^����Ă��邷�ׂĂ̕����ɉ�����ݒ肷��//
		void SetFamilyName(const std::wstring& _familyName, const DWRITE_TEXT_RANGE& _range);

		void SetFontCollection(IDWriteFontCollection* _collection, const DWRITE_TEXT_RANGE& _range);

		void SetFontWeight(DWRITE_FONT_WEIGHT _weight, const DWRITE_TEXT_RANGE& _range);

		void SetFontStyle(DWRITE_FONT_STYLE _style, const DWRITE_TEXT_RANGE& _range);

		void SetFontStretch(DWRITE_FONT_STRETCH _stretch, const DWRITE_TEXT_RANGE& _range);

		void SetLocaleName(const std::wstring& _localeName, const DWRITE_TEXT_RANGE& _range);

	private:

		DWRITE_TEXT_RANGE GetUseRange(const DWRITE_TEXT_RANGE& _range);

	private:

		IDWriteTextLayout* layout = nullptr;
		unsigned long textLength = 0;

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
			ChMath::Vector2Base<unsigned long>& _size,
			HWND _hwnd,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			D2D1_SIZE_U& _size,
			HWND _hwnd,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			IDXGISurface* _surface,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Release();

		//���ݍ쐬����Ă���TextFormatObject�̒��g�����ׂĔj�����܂�//
		void ReleaseTextFormat();

		//���ݍ쐬����Ă���BrushObject�̒��g�����ׂĔj�����܂�//
		void ReleaseBrush();

		//���ݍ쐬����Ă���BrushObject�̒��g�����ׂĔj�����܂�//
		void ReleaseLayout();

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

		TextFormatObject CreateTextFormat(
			const std::wstring& _familyName,
			IDWriteFontCollection* _collection,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _fontSize,
			const std::wstring& _localeName);

		BrushObject CreateBrush(const D2D_COLOR_F& _color);

		BrushObject CreateBrush(const ChVec4& _color);

		LayoutObject CreateLayout(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat);

		LayoutObject CreateLayout(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			IDWriteTextFormat* _textFormat);

		LayoutObject CreateLayout(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			const TextFormatObject& _textFormat);

		LayoutObject CreateLayout(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			const TextFormatObject& _textFormat);

	public:

		//�Ώۂ�RenderTarget����̐F�œh��Ԃ��������s�����ǂ����̔���//
		void SetClearDisplayFlg(bool _flg = false) { clearDisplayFlg = _flg; }

		//�`�悷��ۂ�Rect��-1�`1�̊Ԃ̎ˉe���W�n�ŕ`�悷�邩�̃t���O//
		void SetProjectionCoodinateSystemFlg(bool _flg = true) { toProjectionCoodinateSystemFlg = _flg; }

		void SetClearDisplayColor(const D2D_COLOR_F& _color) { clearDisplayColor = _color; }

		void SetClearDisplayColor(const ChVec4& _color) { clearDisplayColor = ToD2DCOLORF(_color); }

	private:

		std::wstring GetLocaleName(LocaleNameId _localeName);

		static bool& GetDrawFlg() { static bool flg; return flg; }

	public:

		void DrawStart();

		//���ォ��0,0�̃f�B�X�v���C���W�n�Ōv�Z����//
		inline void Draw(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const D2D1_RECT_F& _drawRect = D2D1::RectF(0.0f, 0.0f, 1280.0f, 720.0f))
		{
			Draw(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//���ォ��0,0�̃f�B�X�v���C���W�n�Ōv�Z����//
		inline void Draw(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const ChVec4& _drawRect = ChVec4(0.0f, 0.0f, 1280.0f, 720.0f))
		{
			Draw(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//���ォ��0,0�̃f�B�X�v���C���W�n�Ōv�Z����//
		void Draw(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const D2D1_RECT_F& _drawRect = D2D1::RectF(0.0f, 0.0f, 1280.0f, 720.0f));

		//���ォ��0,0�̃f�B�X�v���C���W�n�Ōv�Z����//
		void Draw(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const ChVec4& _drawRect = ChVec4(0.0f, 0.0f, 1280.0f, 720.0f));

		void DrawEnd();

	private:

		void DrawTextMethod(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* brushObject,
			const D2D1_RECT_F& _drawRect)
		{

#ifdef _UNICODE
			renderTarget->DrawTextW(
				_text.c_str(),        // The string to render.
				_text.length(),    // The string's length.
				_textFormat,    // The text format.
				&_drawRect,       // The region of the window where the text will be rendered.
				brushObject     // The brush used to draw the text.
			);
#else
			renderTarget->DrawTextA(
				_text.c_str(),       // The string to render.
				_text.length(),    // The string's length.
				_textFormat,    // The text format.
				&_drawRect,       // The region of the window where the text will be rendered.
				brushObject     // The brush used to draw the text.
			);
#endif

		}

	public:

		inline static ChVec4 FromD2DCOLORF(const D2D_COLOR_F& _color)
		{
			ChVec4 res;
			res.a = _color.a;
			res.r = _color.r;
			res.g = _color.g;
			res.b = _color.b;
			return res;
		}

		inline static ChVec4 FromD2DRECTF(const D2D1_RECT_F& _rect)
		{
			ChVec4 res;
			res.left = _rect.left;
			res.top = _rect.top;
			res.right = _rect.right;
			res.bottom = _rect.bottom;
			return res;
		}

		inline static ChVec2 FromD2DPOINT2F(const D2D1_POINT_2F& _point)
		{
			ChVec2 res;
			res.x = _point.x;
			res.y = _point.y;
			return res;
		}

		inline static D2D_COLOR_F ToD2DCOLORF(const ChVec4& _color)
		{

			D2D_COLOR_F res;
			res.a = _color.a;
			res.r = _color.r;
			res.g = _color.g;
			res.b = _color.b;
			return res;
		}

		inline static D2D1_RECT_F ToD2DRECTF(const ChVec4& _rect)
		{
			D2D1_RECT_F res;
			res.left = _rect.left;
			res.top = _rect.top;
			res.right = _rect.right;
			res.bottom = _rect.bottom;
			return res;
		}

		inline static D2D1_POINT_2F FromD2DPOINT2F(const ChVec2& _point)
		{
			D2D1_POINT_2F res;
			res.x = _point.x;
			res.y = _point.y;
			return res;
		}

	private:

		D2D1_RECT_F ToProjectionCoodinateSystem(const D2D1_RECT_F& _targetRect);

		float GetProjectionCoodinateSystemWidth(float _rectX, float _displayW);

		float GetProjectionCoodinateSystemHeight(float _rectX, float _displayW);

	private:

		IDWriteFactory* dwFactory = nullptr;
		ID2D1Factory* d2dFactory = nullptr;
		ID2D1RenderTarget* renderTarget = nullptr;

		std::vector<IDWriteTextFormat*>textFormatList;
		std::vector<ID2D1SolidColorBrush*>brushList;
		std::vector<IDWriteTextLayout*>layoutList;

		LocaleNameId localeNameId = LocaleNameId::English;
		bool thisDrawerFlg = false;

		bool clearDisplayFlg = false;
		D2D_COLOR_F clearDisplayColor = D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f);

		//�ˉe���W�n�ŕ`�悷�邩�̃t���O//
		bool toProjectionCoodinateSystemFlg = true;
		D2D1::Matrix3x2F toProjectionMat;
	};

}

#endif