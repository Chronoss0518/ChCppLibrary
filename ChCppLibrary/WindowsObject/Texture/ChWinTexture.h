#ifdef _WINDOWS_

#ifndef Ch_Win_WTex_h
#define Ch_Win_WTex_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	class Brush;
	class WindDrawer;

	enum class Stretch :int
	{
		BlackOnWhite = BLACKONWHITE,
		ColorOnColor =COLORONCOLOR,
		HalfTone = HALFTONE,
		STR_AndScans = STRETCH_ANDSCANS,
		STR_DeleteScans = STRETCH_DELETESCANS,
		STR_HalfTone = STRETCH_HALFTONE,
		STR_OrScans = STRETCH_ORSCANS,
		WhiteOnBlack = WHITEONBLACK
	};

	typedef enum class RasterizerOperationCodeType : unsigned long
	{
		Blackness = BLACKNESS,
		CaptureBLT = CAPTUREBLT,
		DSTInvert = DSTINVERT,
		MergeCopy = MERGECOPY,
		MergePaint = MERGEPAINT,
		NoMirrorBitmap = NOMIRRORBITMAP,
		NotSRCCopy = NOTSRCCOPY,
		NotSRCErase = NOTSRCERASE,
		PATCopy = PATCOPY,
		PATInvert = PATINVERT,
		PATPaint = PATPAINT,
		SRCAnd = SRCAND,
		SRCCopy = SRCCOPY,
		SRCErase = SRCERASE,
		SRCInvert = SRCINVERT,
		SRCPaint = SRCPAINT,
		Whiteness = WHITENESS
	}RasterOpeCode;

	class RenderTarget;

	class Texture:public ChCp::Initializer
	{
	public://ConstructorDestructor//

		inline virtual ~Texture() { Release(); }

	public://InitAndRelease//

		void Release();

	public://Create Functions//

		ChStd::Bool CreateTexture(HWND _hWnd, const std::string& _fileName);

		ChStd::Bool CreateTexture(HWND _hWnd, const std::wstring& _fileName);

		ChStd::Bool CreateTexture(HINSTANCE _instance, const std::string& _fileName);

		ChStd::Bool CreateTexture(HINSTANCE _instance, const std::wstring& _fileName);

		ChStd::Bool CreateTexture(const int _width, const int _height, const unsigned char* _bit);

		ChStd::Bool CreateTexture(const int _width, const int _height, const unsigned char* _bit,const unsigned int _nPlanes,const unsigned int _bitCount);

		HBRUSH CreateBrush()const;

	public://Set Functions//

		void SetTextureToHDC(HDC _target);

		void SetStretchToHDC(HDC _target);

		inline void SetStretchType(const Stretch _stretch) { stretchType = _stretch; }

		inline void SetRasterizerOperationCodeType(const RasterizerOperationCodeType _opeCode) { opeCode = _opeCode; }

	public://Get Functions//

		inline RasterOpeCode GetRasterizerOperationCodeType() { return opeCode; }

		inline HBITMAP GetTexture() { return mainTexture; }

		inline ChMath::Vector2Base<int> GetTextureSize()
		{
			return 
#ifdef UNICODE
			GetTextureSizeW();
#else
			GetTextureSizeA();
#endif
		}

		ChMath::Vector2Base<int> GetTextureSizeW();

		ChMath::Vector2Base<int> GetTextureSizeA();

	public://Other Functions//

		void Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));
		
		void Draw(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize,const UINT _transparent);

		void DrawTransparent(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY,const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const HBITMAP _maskTex);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const HBITMAP _maskTex);

		void DrawPlg(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const HBITMAP _maskTex, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const HBITMAP _maskTex, const int _rot);

		void Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent);

		void DrawTransparent(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const HBITMAP _maskTex);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const HBITMAP _maskTex);

		void DrawPlg(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const HBITMAP _maskTex, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const HBITMAP _maskTex, const int _rot);

		//ChStd::Bool FillTexture(const FillType _type = FillType::Whiteness);

	protected://Other Functions//

		void DrawMain(HDC _textureHDC,HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos);

		void DrawStretchMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawTransparentMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent);

		void DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const UINT _transparent);
		
		void DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const HBITMAP _maskTex);

		void DrawPlgMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent,const unsigned long _rot);
		
		void DrawPlgMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const HBITMAP _maskTex,const unsigned long _rot);

	protected://Member Value//

		Stretch stretchType = Stretch::ColorOnColor;
		RasterOpeCode opeCode = RasterOpeCode::SRCCopy;
		HBITMAP mainTexture = nullptr;
	};

	class RenderTarget :protected Texture
	{
	public://ConstructorDestructor//

		inline ~RenderTarget()override { Release(); }

	public://Init And Release//

		void Release(); 

	public://Create Functions//

		ChStd::Bool CreateRenderTarget(HWND _hWnd, const ChMath::Vector2Base<int>& _size);
		ChStd::Bool CreateRenderTarget(HWND _hWnd, const int _width, const int _height);

		ChStd::Bool CreateRenderTarget(HDC _dc, const ChMath::Vector2Base<int>& _size);
		ChStd::Bool CreateRenderTarget(HDC _dc, const int _width, const int _height);

		inline HBRUSH CreateBrush()const  { return Texture::CreateBrush(); }

	public://Set Function//

		inline void SetTextureToHDC(HDC _target) { Texture::SetTextureToHDC(_target); }

		inline void SetStretchToHDC(HDC _target) { Texture::SetStretchToHDC(_target); }

		inline void SetStretchType(const Stretch _stretch) { Texture::SetStretchType(_stretch); }

		inline void SetRasterizerOperationCodeType(const RasterizerOperationCodeType _opeCode) { Texture::SetRasterizerOperationCodeType(_opeCode); }

		inline UINT SetBKColor(const UINT _transparent) { return SetBkColor(dc, _transparent); }

	public://Get Functions//

		inline RasterOpeCode GetRasterizerOperationCodeType() { return Texture::GetRasterizerOperationCodeType(); }

		inline HDC GetRenderTarget() { return dc; }

		inline HBITMAP GetTexture() { return Texture::GetTexture(); }

		inline ChMath::Vector2Base<int> GetTextureSize()
		{
			return Texture::GetTextureSize();
		}

	public://Is Function//

		ChStd::Bool IsInit()const { return static_cast<bool>(*this); }

	public://Other Functions//

		void Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent);

		void DrawTransparent(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, HBITMAP _maskTex);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, HBITMAP _maskTex);

		void DrawPlg(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, HBITMAP _maskTex, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, HBITMAP _maskTex, const int _rot);

		void Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent);

		void DrawTransparent(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, HBITMAP _maskTex);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, HBITMAP _maskTex);

		void DrawPlg(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, HBITMAP _maskTex, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, HBITMAP _maskTex, const int _rot);

		void DrawBrush(HBRUSH _brush);

		void DrawBrush(ChWin::Brush& _brush);

		void FillRT(HBRUSH _brush,const RECT& _range);

		void FillRT(HBRUSH _brush,const long _x,const long _y,const long _w,const long _h);

		void FillRT(ChWin::Brush& _brush, const RECT& _range);

		void FillRT(ChWin::Brush& _brush, const long _x, const long _y, const long _w, const long _h);

	protected://Member Value//

		HDC dc = nullptr;

	};

	class MaskTexture :protected RenderTarget
	{
	public://ConstructorDestructor//

		inline ~MaskTexture()override { Release(); }

	public://Init And Release//

		void Release() { RenderTarget::Release(); }

	public://Create Functions//

		ChStd::Bool CreateMaskTexture(const ChMath::Vector2Base<int>& _size);

		ChStd::Bool CreateMaskTexture(const int _width, const int _height);

	public://Set Functions//

		inline void SetTextureToHDC(HDC _target)
		{
			RenderTarget::SetTextureToHDC(_target);
		}

		inline void SetStretchType(const Stretch _stretch) { stretchType = _stretch; }

		inline void SetRasterizerOperationCodeType(const RasterizerOperationCodeType _opeCode) { opeCode = _opeCode; }

		inline UINT SetBKColor(const UINT _transparent) { return RenderTarget::SetBKColor(_transparent); }

	public://Get Functions//

		inline HDC GetRenderTarget() { return RenderTarget::GetRenderTarget(); }

		inline HBITMAP GetTexture() { return RenderTarget::GetTexture(); }

	public://Is Function//

		ChStd::Bool IsInit()const { return RenderTarget::IsInit(); }

	};

}

#endif

#endif
