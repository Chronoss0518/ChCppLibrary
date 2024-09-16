#ifndef Ch_D3DOBJ_DFont_h
#define Ch_D3DOBJ_DFont_h

interface IDWriteFactory;
interface IDWriteTextFormat;
interface ID2D1Factory;
interface ID2D1HwndRenderTarget;
interface ID2D1SolidColorBrush;
interface IDWriteFontCollection;

enum DWRITE_FONT_WEIGHT; 
enum DWRITE_FONT_STYLE;
enum DWRITE_FONT_STRETCH;

#include"../../WindowsObject/PackData/ChRect.h"
#include"../../WindowsObject/PackData/ChPoint.h"

namespace ChD3D
{
	class DirectFontBase;
	class WICBitmapObject;

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

		//_rangeÇÃlengthÇ™0ÇÃèÍçáÇ‹ÇΩÇÕlength + startPositionÇ™textLengthÇÊÇËëÂÇ´Ç¢èÍçáÇÕìoò^Ç≥ÇÍÇƒÇ¢ÇÈÇ∑Ç◊ÇƒÇÃï∂éöÉTÉCÉYÇïœçXÇ∑ÇÈ//
		void SetFontSize(float _size, const DWRITE_TEXT_RANGE& _range = { 0, 0 });

		//_rangeÇÃlengthÇ™0ÇÃèÍçáÇ‹ÇΩÇÕlength + startPositionÇ™textLengthÇÊÇËëÂÇ´Ç¢èÍçáÇÕìoò^Ç≥ÇÍÇƒÇ¢ÇÈÇ∑Ç◊ÇƒÇÃï∂éöÇ…éÊÇËè¡Çµê¸Çê›íËÇ∑ÇÈ//
		void SetFontStrikethrough(bool _useFlg, const DWRITE_TEXT_RANGE& _range = { 0, 0 });

		//_rangeÇÃlengthÇ™0ÇÃèÍçáÇ‹ÇΩÇÕlength + startPositionÇ™textLengthÇÊÇËëÂÇ´Ç¢èÍçáÇÕìoò^Ç≥ÇÍÇƒÇ¢ÇÈÇ∑Ç◊ÇƒÇÃï∂éöÇ…â∫ê¸Çê›íËÇ∑ÇÈ//
		void SetFontUnderline(bool _useFlg, const DWRITE_TEXT_RANGE& _range = { 0, 0 });

		void SetLayoutBoxWidth(float _width);

		void SetLayoutBoxHeight(float _witdh);

		inline void SetLayoutBoxSize(const ChVec2& _size)
		{
			SetLayoutBoxWidth(_size.w);
			SetLayoutBoxHeight(_size.h);
		}

		//_rangeÇÃlengthÇ™0ÇÃèÍçáÇ‹ÇΩÇÕlength + startPositionÇ™textLengthÇÊÇËëÂÇ´Ç¢èÍçáÇÕìoò^Ç≥ÇÍÇƒÇ¢ÇÈÇ∑Ç◊ÇƒÇÃï∂éöÇ…â∫ê¸Çê›íËÇ∑ÇÈ//
		void SetFamilyName(const wchar_t* _familyName, const DWRITE_TEXT_RANGE& _range);

		void SetFontCollection(IDWriteFontCollection* _collection, const DWRITE_TEXT_RANGE& _range);

		void SetFontWeight(DWRITE_FONT_WEIGHT _weight, const DWRITE_TEXT_RANGE& _range);

		void SetFontStyle(DWRITE_FONT_STYLE _style, const DWRITE_TEXT_RANGE& _range);

		void SetFontStretch(DWRITE_FONT_STRETCH _stretch, const DWRITE_TEXT_RANGE& _range);

		void SetLocaleName(const wchar_t* _localeName, const DWRITE_TEXT_RANGE& _range);

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

	//Direct3D10à»ç~Ç∂Ç·Ç»Ç¢Ç∆óòópÇ≈Ç´Ç»Ç¢//
	class DirectFontBase
	{
	public:

		struct DirectFontBaseCRT
		{
#ifdef CRT
			std::vector<IDWriteTextFormat*>textFormatList;
			std::vector<ID2D1SolidColorBrush*>brushList;
			std::vector<LayoutObject::LayoutStruct*>layoutList;
#endif
		};

	public:

		enum class LocaleNameId
		{
			English,
			Japanese,
		};

	public:

		DirectFontBase();
		
		virtual ~DirectFontBase();

	public:

		void Release();

		//åªç›çÏê¨Ç≥ÇÍÇƒÇ¢ÇÈTextFormatObjectÇÃíÜêgÇÇ∑Ç◊Çƒîjä¸ÇµÇ‹Ç∑//
		void ReleaseTextFormat();

		//åªç›çÏê¨Ç≥ÇÍÇƒÇ¢ÇÈBrushObjectÇÃíÜêgÇÇ∑Ç◊Çƒîjä¸ÇµÇ‹Ç∑//
		void ReleaseBrush();

		//åªç›çÏê¨Ç≥ÇÍÇƒÇ¢ÇÈBrushObjectÇÃíÜêgÇÇ∑Ç◊Çƒîjä¸ÇµÇ‹Ç∑//
		void ReleaseLayout();

	protected:

		bool InitBase();

		void EndInit(LocaleNameId _localeNameId);

	public:

#ifdef CRT

		TextFormatObject CreateTextFormat(
			const std::wstring& _familyName,
			IDWriteFontCollection* _collection,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _fontSize)
		{
			TextFormatObject res;

			if (_familyName.length() <= 0)return res;
			if (_fontSize <= 0.0f)return res;

			auto localeName = GetLocaleName(localeNameId);

			if (localeName.length() <= 0)return res;
			if (ChPtr::NullCheck(dwFactory))return res;

			return CreateTextFormatBase(_familyName.c_str(), _familyName.length(), _collection, _weight, _style, _stretch, _fontSize, localeName.c_str());
		}

		TextFormatObject CreateTextFormat(
			const std::wstring& _familyName,
			IDWriteFontCollection* _collection,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _fontSize,
			const std::wstring& _localeName)
		{
			return CreateTextFormatBase(_familyName.c_str(), _familyName.length(), _collection, _weight, _style, _stretch, _fontSize, _localeName.c_str());
		}

#endif

		BrushObject CreateBrush(const D2D_COLOR_F& _color);

		BrushObject CreateBrush(const ChVec4& _color);

#ifdef CRT

		//éÀâeç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat)
		{
			float width = (_layoutBoxWidth * 0.5f + 0.5f) * displaySize.width;
			float height = (_layoutBoxHeight * 0.5f + 0.5f) * displaySize.height;

			auto&& layout = CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), width, height, _textFormat);

			layout.data->toProjectionFlg = true;

			return layout;
		}

		//éÀâeç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			IDWriteTextFormat* _textFormat)
		{
			float width = (_layoutSize.w * 0.5f + 0.5f) * displaySize.width;
			float height = (_layoutSize.h * 0.5f + 0.5f) * displaySize.height;

			auto&& layout = CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), width, height, _textFormat);

			layout.data->toProjectionFlg = true;

			return layout;
		}

		//éÀâeç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			const TextFormatObject& _textFormat)
		{
			float width = (_layoutBoxWidth * 0.5f + 0.5f) * displaySize.width;
			float height = (_layoutBoxHeight * 0.5f + 0.5f) * displaySize.height;

			auto&& layout = CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), width, height, _textFormat.textFormat);

			layout.data->toProjectionFlg = true;

			return layout;
		}

		//éÀâeç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToProjection(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			const TextFormatObject& _textFormat)
		{
			float width = (_layoutSize.w * 0.5f + 0.5f) * displaySize.width;
			float height = (_layoutSize.h * 0.5f + 0.5f) * displaySize.height;

			auto&& layout = CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), width, height, _textFormat.textFormat);

			layout.data->toProjectionFlg = true;

			return layout;
		}

		//ÉXÉNÉäÅ[Éìç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat)
		{
			return CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), _layoutBoxWidth, _layoutBoxHeight, _textFormat);
		}

		//ÉXÉNÉäÅ[Éìç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			IDWriteTextFormat* _textFormat)
		{
			return CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), _layoutSize.w, _layoutSize.h, _textFormat);
		}

		//ÉXÉNÉäÅ[Éìç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			const TextFormatObject& _textFormat)
		{
			return CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), _layoutBoxWidth, _layoutBoxHeight, _textFormat.textFormat);
		}

		//ÉXÉNÉäÅ[Éìç¿ïWånÇ≈óòópÇ∑ÇÈLayoutÇçÏê¨Ç∑ÇÈ//
		LayoutObject CreateLayoutToScreen(
			const std::wstring& _drawText,
			const ChVec2& _layoutSize,
			const TextFormatObject& _textFormat)
		{
			return CreateLayout(_drawText.c_str(), static_cast<unsigned long>(_drawText.length()), _layoutSize.w, _layoutSize.h, _textFormat.textFormat);
		}

#endif

	private:

		TextFormatObject CreateTextFormatBase(
			const wchar_t* _familyName,
			const size_t _familyNameLength,
			IDWriteFontCollection* _collection,
			DWRITE_FONT_WEIGHT _weight,
			DWRITE_FONT_STYLE _style,
			DWRITE_FONT_STRETCH _stretch,
			float _fontSize,
			const wchar_t* _localeName);

		LayoutObject CreateLayout(
			const wchar_t* _drawText,
			const unsigned long _drawTextLength,
			float _layoutBoxWidth,
			float _layoutBoxHeight,
			IDWriteTextFormat* _textFormat);

	public:

		//ëŒè€ÇÃRenderTargetÇàÍÇ¬ÇÃêFÇ≈ìhÇËÇ¬Ç‘Ç∑èàóùÇçsÇ§Ç©Ç«Ç§Ç©ÇÃîªíË//
		void SetClearDisplayFlg(bool _flg = false) { clearDisplayFlg = _flg; }

		void SetClearDisplayColor(const D2D_COLOR_F& _color) { clearDisplayColor = _color; }

		void SetClearDisplayColor(const ChVec4& _color) { clearDisplayColor = ToD2DCOLORF(_color); }

	private:

#ifdef CRT

		std::wstring GetLocaleName(LocaleNameId _localeName)
		{
			unsigned long localeNameNo = ChStd::EnumCast(_localeName);
			static std::wstring localeName[] = { L"en-us",L"ja-JP" };

			if (localeNameNo >= (sizeof(localeName) / sizeof(std::wstring)))return L"";

			return localeName[localeNameNo];
		}

#endif

		static bool& GetDrawFlg() { static bool flg; return flg; }

	protected:

		inline bool IsThisDrawerFlg() { return thisDrawerFlg; }

	public:

		void DrawStart();

#ifdef CRT

		//éÀâeç¿ïWånÇ≈åvéZÇ∑ÇÈÇÊÇ§Ç…èCê≥//
		inline void DrawToProjection(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const D2D1_RECT_F& _drawRect)
		{
			DrawToProjection(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//éÀâeç¿ïWånÇ≈åvéZÇ∑ÇÈÇÊÇ§Ç…èCê≥//
		inline void DrawToProjection(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			D2D1_RECT_F layoutRect = ToD2DRECTF(_drawRect);

			DrawToProjection(_text, _textFormat.textFormat, _brushObject.brush, layoutRect);
		}

		//éÀâeç¿ïWånÇ≈åvéZÇ∑ÇÈÇÊÇ§Ç…èCê≥//
		inline void DrawToProjection(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const D2D1_RECT_F& _drawRect)
		{
			if (!thisDrawerFlg)return;
			if (_text.length() <= 0)return;
			if (ChPtr::NullCheck(_textFormat))return;
			if (ChPtr::NullCheck(_brushObject))return;

			DrawTextMethod(_text.c_str(), static_cast<unsigned long>(_text.length()), _textFormat, _brushObject, ToProjectionCoodinateSystem(_drawRect));
		}

		//éÀâeç¿ïWånÇ≈åvéZÇ∑ÇÈÇÊÇ§Ç…èCê≥//
		inline void DrawToProjection(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			if (!thisDrawerFlg)return;
			if (_text.length() <= 0)return;
			if (ChPtr::NullCheck(_textFormat))return;
			if (ChPtr::NullCheck(_brushObject))return;

			D2D1_RECT_F layoutRect = ToD2DRECTF(_drawRect);

			DrawToProjection(_text, _textFormat, _brushObject, layoutRect);
		}

		//ç∂è„Ç©ÇÁ0,0ÇÃÉXÉNÉäÅ[Éìç¿ïWånÇ≈åvéZÇ∑ÇÈ//
		inline void DrawToScreen(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const D2D1_RECT_F& _drawRect)
		{
			DrawToScreen(_text, _textFormat.textFormat, _brushObject.brush, _drawRect);
		}

		//ç∂è„Ç©ÇÁ0,0ÇÃÉXÉNÉäÅ[Éìç¿ïWånÇ≈åvéZÇ∑ÇÈ//
		inline void DrawToScreen(
			const std::wstring& _text,
			const TextFormatObject& _textFormat,
			const BrushObject& _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			D2D1_RECT_F layoutRect = ToD2DRECTF(_drawRect);

			DrawToScreen(_text, _textFormat.textFormat, _brushObject.brush, layoutRect);
		}

		//ç∂è„Ç©ÇÁ0,0ÇÃÉXÉNÉäÅ[Éìç¿ïWånÇ≈åvéZÇ∑ÇÈ//
		inline void DrawToScreen(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const D2D1_RECT_F& _drawRect)
		{

			if (!thisDrawerFlg)return;
			if (_text.length() <= 0)return;
			if (ChPtr::NullCheck(_textFormat))return;
			if (ChPtr::NullCheck(_brushObject))return;

			DrawTextMethod(_text.c_str(), static_cast<unsigned long>(_text.length()), _textFormat, _brushObject, _drawRect);
		}

		//ç∂è„Ç©ÇÁ0,0ÇÃÉXÉNÉäÅ[Éìç¿ïWånÇ≈åvéZÇ∑ÇÈ//
		void DrawToScreen(
			const std::wstring& _text,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* _brushObject,
			const ChVec4& _drawRect = ChVec4::FromRect(-1.0f, 1.0f, 1.0f, -1.0f))
		{
			if (!thisDrawerFlg)return;
			if (_text.length() <= 0)return;
			if (ChPtr::NullCheck(_textFormat))return;
			if (ChPtr::NullCheck(_brushObject))return;

			D2D1_RECT_F layoutRect = ToD2DRECTF(_drawRect);

			DrawTextMethod(_text.c_str(), static_cast<unsigned long>(_text.length()), _textFormat, _brushObject, layoutRect);
		}

#endif

		//_drawPositionÇÃà íuÇÕç∂è„ÇäÓèÄÇ…Ç∑ÇÈ//
		void DrawLayout(
			const ChVec2& _drawPosition,
			LayoutObject& _layout,
			BrushObject& _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		//_drawPositionÇÃà íuÇÕç∂è„ÇäÓèÄÇ…Ç∑ÇÈ//
		void DrawLayout(
			const D2D1_POINT_2F& _drawPosition,
			LayoutObject& _layout,
			BrushObject& _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		//_drawPositionÇÃà íuÇÕç∂è„ÇäÓèÄÇ…Ç∑ÇÈ//
		void DrawLayout(
			const ChVec2& _drawPosition,
			IDWriteTextLayout* _layout,
			ID2D1SolidColorBrush* _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		//_drawPositionÇÃà íuÇÕç∂è„ÇäÓèÄÇ…Ç∑ÇÈ//
		void DrawLayout(
			const D2D1_POINT_2F& _drawPosition,
			IDWriteTextLayout* _layout, 
			ID2D1SolidColorBrush* _brush,
			D2D1_DRAW_TEXT_OPTIONS _options = D2D1_DRAW_TEXT_OPTIONS_NONE);

		void DrawEnd();

	private:

		void DrawTextMethod(
			const wchar_t* _text,
			const unsigned long _textLength,
			IDWriteTextFormat* _textFormat,
			ID2D1SolidColorBrush* brushObject,
			const D2D1_RECT_F& _drawRect);

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

	private:

		IDWriteTextFormat* GetTextFormat(size_t _num);
		
		size_t GetTextFormatCount();

		void AddTextFormat(IDWriteTextFormat*);
		
		void ClearTextFormatList();

		ID2D1SolidColorBrush* GetBrush(size_t _num);

		size_t GetBrushCount();

		void AddBrush(ID2D1SolidColorBrush*);

		void ClearBrushList();

		LayoutObject::LayoutStruct* GetLayout(size_t _num);

		size_t GetLayoutCount();

		void AddLayout(LayoutObject::LayoutStruct*);

		void ClearLayoutList();

	protected:

		IDWriteFactory* dwFactory = nullptr;
		ID2D1Factory* d2dFactory = nullptr;
		ID2D1RenderTarget* renderTarget = nullptr;

		D2D1_SIZE_F displaySize = D2D1::SizeF(0.0f,0.0f);
		DirectFontBaseCRT& ValueIns() { return *value; }
	private:

		LocaleNameId localeNameId = LocaleNameId::English;
		bool thisDrawerFlg = false;

		bool clearDisplayFlg = false;
		D2D_COLOR_F clearDisplayColor = D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f);
		DirectFontBaseCRT* value = nullptr;
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

	//Direct3D10à»ç~Ç∂Ç·Ç»Ç¢Ç∆óòópÇ≈Ç´Ç»Ç¢//
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

		void SetHDC(HDC _dc, const ChRECT& _subRect);

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

		void Init(
			unsigned long _w,
			unsigned long _h,
			WICBitmapObject& _bitmap,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			ChMath::Vector2Base<unsigned long>& _size,
			WICBitmapObject& _bitmap,
			LocaleNameId _localeNameId = LocaleNameId::English);

		void Init(
			D2D1_SIZE_U& _size,
			WICBitmapObject& _bitmap,
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

#ifdef CRT

ChD3D::DirectFontBase::DirectFontBase()
{
	value = new DirectFontBaseCRT();
}

ChD3D::DirectFontBase::~DirectFontBase()
{
	delete value;
}

IDWriteTextFormat* ChD3D::DirectFontBase::GetTextFormat(size_t _num)
{
	return ValueIns().textFormatList[_num];
}

size_t ChD3D::DirectFontBase::GetTextFormatCount()
{
	return ValueIns().textFormatList.size();
}

void ChD3D::DirectFontBase::AddTextFormat(IDWriteTextFormat* _textFormat)
{
	ValueIns().textFormatList.push_back(_textFormat);
}

void ChD3D::DirectFontBase::ClearTextFormatList()
{
	if (ValueIns().textFormatList.empty())return;
	ValueIns().textFormatList.clear();
}

ID2D1SolidColorBrush* ChD3D::DirectFontBase::GetBrush(size_t _num)
{
	return ValueIns().brushList[_num];
}

size_t ChD3D::DirectFontBase::GetBrushCount()
{
	return ValueIns().brushList.size();
}

void ChD3D::DirectFontBase::AddBrush(ID2D1SolidColorBrush* _brush)
{
	ValueIns().brushList.push_back(_brush);
}

void ChD3D::DirectFontBase::ClearBrushList()
{
	if (ValueIns().brushList.empty())return;
	ValueIns().brushList.clear();
}

ChD3D::LayoutObject::LayoutStruct* ChD3D::DirectFontBase::GetLayout(size_t _num)
{
	return ValueIns().layoutList[_num];
}

size_t ChD3D::DirectFontBase::GetLayoutCount()
{
	return ValueIns().layoutList.size();
}

void ChD3D::DirectFontBase::AddLayout(LayoutObject::LayoutStruct* _layout)
{
	ValueIns().layoutList.push_back(_layout);
}

void ChD3D::DirectFontBase::ClearLayoutList()
{
	if (ValueIns().layoutList.empty())return;
	ValueIns().layoutList.clear();
}

#endif

#endif