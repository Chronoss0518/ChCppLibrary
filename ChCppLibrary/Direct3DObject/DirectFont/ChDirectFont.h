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
	class DirectFontBase;

	enum class CreateFontType
	{
		NONE,
		H_WND,
		H_DC,
		WIC_BITMAP,
		DXGI_SURFACE
	};

	class TextFormatObject
	{
	public:
		
		friend DirectFontBase;

		void SetTextAlignment(DWRITE_TEXT_ALIGNMENT _alignment);

		void SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT _alignment);

	private:
		IDWriteTextFormat* textFormat = nullptr;
	};

	class BrushObject
	{
	public:

		friend DirectFontBase;

		void SetColor(const D2D_COLOR_F& _color);

		void SetColor(const ChVec4& _color);

	private:

		ID2D1SolidColorBrush* brush = nullptr;
	};

	class LayoutObject
	{
	public:

		friend DirectFontBase;

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

	public:

		inline bool IsProjectionFlg() 
		{
			if (ChPtr::NullCheck(data))return false;
			return data->toProjectionFlg;
		};

	private:

		struct LayoutStruct
		{
			IDWriteTextLayout* layout = nullptr;

			bool toProjectionFlg = false;
		};

		unsigned long textLength = 0;

		LayoutStruct* data = nullptr;

	};

	//Direct3D10�ȍ~����Ȃ��Ɨ��p�ł��Ȃ�//
	class DirectFontBase
	{
	public:

		enum class LocaleNameId
		{
			English,
			Japanese,
		};

	public:

		virtual ~DirectFontBase()
		{
			Release();
		}

	public:

		void Release();

		//���ݍ쐬����Ă���TextFormatObject�̒��g�����ׂĔj�����܂�//
		void ReleaseTextFormat();

		//���ݍ쐬����Ă���BrushObject�̒��g�����ׂĔj�����܂�//
		void ReleaseBrush();

		//���ݍ쐬����Ă���BrushObject�̒��g�����ׂĔj�����܂�//
		void ReleaseLayout();

	protected:

		bool InitBase();

		void EndInit(LocaleNameId _localeNameId);

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


		//�ˉe���W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat);

		//�ˉe���W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			IDWriteTextFormat* _textFormat);

		//�ˉe���W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			const TextFormatObject& _textFormat);

		//�ˉe���W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			const TextFormatObject& _textFormat);

		//�X�N���[�����W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat);

		//�X�N���[�����W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			IDWriteTextFormat* _textFormat);

		//�X�N���[�����W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			const TextFormatObject& _textFormat);

		//�X�N���[�����W�n�ŗ��p����Layout���쐬����//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			const TextFormatObject& _textFormat);


	private:

		LayoutObject CreateLayout(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat);

	public:

		//�Ώۂ�RenderTarget����̐F�œh��Ԃ��������s�����ǂ����̔���//
		void SetClearDisplayFlg(bool _flg = false) { clearDisplayFlg = _flg; }

		void SetClearDisplayColor(const D2D_COLOR_F& _color) { clearDisplayColor = _color; }

		void SetClearDisplayColor(const ChVec4& _color) { clearDisplayColor = ToD2DCOLORF(_color); }

	private:

		std::wstring GetLocaleName(LocaleNameId _localeName);

		static bool& GetDrawFlg() { static bool flg; return flg; }

	protected:

		inline bool IsThisDrawerFlg() { return thisDrawerFlg; }

	public:

		void DrawStart();

		//�ˉe���W�n�Ōv�Z����悤�ɏC��//
		inline void DrawToProjection(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const D2D1_RECT_F& _drawRect = D2D1::RectF(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			DrawToProjection(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//�ˉe���W�n�Ōv�Z����悤�ɏC��//
		inline void DrawToProjection(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			DrawToProjection(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//�ˉe���W�n�Ōv�Z����悤�ɏC��//
		void DrawToProjection(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const D2D1_RECT_F& _drawRect = D2D1::RectF(-1.0f, 1.0f, 1.0f, -1.0f));

		//�ˉe���W�n�Ōv�Z����悤�ɏC��//
		void DrawToProjection(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f));

		//���ォ��0,0�̃X�N���[�����W�n�Ōv�Z����//
		inline void DrawToScreen(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const D2D1_RECT_F& _drawRect = D2D1::RectF(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			DrawToScreen(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//���ォ��0,0�̃X�N���[�����W�n�Ōv�Z����//
		inline void DrawToScreen(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			DrawToScreen(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//���ォ��0,0�̃X�N���[�����W�n�Ōv�Z����//
		void DrawToScreen(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const D2D1_RECT_F& _drawRect = D2D1::RectF(-1.0f, 1.0f, 1.0f, -1.0f));

		//���ォ��0,0�̃X�N���[�����W�n�Ōv�Z����//
		void DrawToScreen(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f));

		//_drawPosition�̈ʒu�͍������ɂ���//
		void DrawLayout(
			const ChVec2& _drawPosition,
			LayoutObject& _layout,
			BrushObject& _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		//_drawPosition�̈ʒu�͍������ɂ���//
		void DrawLayout(
			const D2D1_POINT_2F& _drawPosition,
			LayoutObject& _layout,
			BrushObject& _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		//_drawPosition�̈ʒu�͍������ɂ���//
		void DrawLayout(
			const ChVec2& _drawPosition,
			IDWriteTextLayout* _layout,
			ID2D1SolidColorBrush* _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		//_drawPosition�̈ʒu�͍������ɂ���//
		void DrawLayout(
			const D2D1_POINT_2F& _drawPosition,
			IDWriteTextLayout* _layout, 
			ID2D1SolidColorBrush* _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		void DrawEnd();

	private:

		void DrawTextMethod(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* brushObject,
			const D2D1_RECT_F& _drawRect)
		{
			renderTarget->DrawText(
				_text.c_str(),        // The string to render.
				_text.length(),    // The string's length.
				_textFormat,    // The text format.
				&_drawRect,       // The region of the window where the text will be rendered.
				brushObject     // The brush used to draw the text.
			);
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

		inline static D2D1_POINT_2F ToD2DPOINT2F(const ChVec2& _point)
		{
			D2D1_POINT_2F res;
			res.x = _point.x;
			res.y = _point.y;
			return res;
		}

	private:

		D2D1_RECT_F ToProjectionCoodinateSystem(const D2D1_RECT_F& _targetRect);

	protected:

		IDWriteFactory* dwFactory = nullptr;
		ID2D1Factory* d2dFactory = nullptr;
		ID2D1RenderTarget* renderTarget = nullptr;

		D2D1_SIZE_F displaySize = D2D1::SizeF(0.0f,0.0f);

	private:

		std::vector<IDWriteTextFormat*>textFormatList;
		std::vector<ID2D1SolidColorBrush*>brushList;
		std::vector<LayoutObject::LayoutStruct*>layoutList;

		LocaleNameId localeNameId = LocaleNameId::English;
		bool thisDrawerFlg = false;

		bool clearDisplayFlg = false;
		D2D_COLOR_F clearDisplayColor = D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f);

	};

	class DirectFontFromHWND : public DirectFontBase
	{

	public:

		~DirectFontFromHWND()
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
	};

	//Direct3D10�ȍ~����Ȃ��Ɨ��p�ł��Ȃ�//
	class DirectFontFromHDC : public DirectFontBase
	{
	public:

		virtual ~DirectFontFromHDC()
		{
			Release();
		}

	public:

		void Init(
			unsigned long _w,
			unsigned long _h,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			ChMath::Vector2Base<unsigned long>& _size,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			D2D1_SIZE_U& _size,
			LocaleNameId _localeNameId = LocaleNameId::English);

	public:

		void SetHDC(HDC _dc, const ChVec4& _subRect);

		void SetHDC(HDC _dc, RECT _subRect);

	};

	class DirectFontFromWICBitmap : public DirectFontBase
	{

	public:

		~DirectFontFromWICBitmap()
		{
			Release();
		}

	public:

		void Init(
			unsigned long _w,
			unsigned long _h,
			IWICBitmap* _bitmap,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			ChMath::Vector2Base<unsigned long>& _size,
			IWICBitmap* _bitmap,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			D2D1_SIZE_U& _size,
			IWICBitmap* _bitmap,
			LocaleNameId _localeNameId = LocaleNameId::English);

	};

	class DirectFontFromDXGISurface : public DirectFontBase
	{

	public:

		~DirectFontFromDXGISurface()
		{
			Release();
		}

	public:

		void Init(
			IDXGISurface* _surface,
			LocaleNameId _localeNameId = LocaleNameId::English);

	};

}

#endif