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

	enum class FillType :unsigned long
	{
		PatCopy = PATCOPY,
		PatInvert = PATINVERT,
		DstInvert = DSTINVERT,
		Blackness = BLACKNESS,
		Whiteness = WHITENESS
	};

	enum class Strech :int
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

		inline void SetStretchType(const Strech _stretch) { stretchType = _stretch; }

		inline void SetRasterizerOperationCodeType(const RasterizerOperationCodeType _opeCode) { opeCode = _opeCode; }

	public://Get Functions//

		inline RasterOpeCode GetRasterizerOperationCodeType() { return opeCode; }

	public://Other Function//

		void Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX = 0, unsigned long _baseY = 0);

		void DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH);

		void Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX = 0, unsigned long _baseY = 0);

		void DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH);

		//ChStd::Bool FillTexture(const FillType _type = FillType::Whiteness);

	protected://Member Value//

		Strech stretchType = Strech::BlackOnWhite;
		RasterOpeCode opeCode = RasterOpeCode::SRCCopy;
		HBITMAP mainTexture = nullptr;

	};

	class RenderTarget :private Texture
	{
	public://ConstructorDestructor//

		inline ~RenderTarget()override { Texture::Release(); }

	public://Init And Release//

		void Release(); 

	public://Create Functions//

		ChStd::Bool CreateRenderTarget(HWND _hWnd, const int _width, const int _height);

		ChStd::Bool CreateRenderTarget(HDC _dc, const int _width, const int _height);

		inline HBRUSH CreateBrush()const  { return Texture::CreateBrush(); }

	public://Set Function//

		inline void SetTextureToHDC(HDC _target) { Texture::SetTextureToHDC(_target); }

		inline void SetStretchToHDC(HDC _target) { Texture::SetStretchToHDC(_target); }

		inline void SetStretchType(const Strech _stretch) { Texture::SetStretchType(_stretch); }

		inline void SetRasterizerOperationCodeType(const RasterizerOperationCodeType _opeCode) { Texture::SetRasterizerOperationCodeType(_opeCode); }

	public://Get Functions//

		inline RasterOpeCode GetRasterizerOperationCodeType() { return Texture::GetRasterizerOperationCodeType(); }

		inline HDC GetRenderTarget() { return dc; }

	public://Is Function//

		ChStd::Bool IsInit()const { return static_cast<bool>(*this); }

	public://Other Functions//

		void Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX = 0, unsigned long _baseY = 0);

		void DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH);

		void Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos = ChMath::Vector2Base<int>(0, 0));

		void Draw(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX = 0, unsigned long _baseY = 0);

		void DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize);

		void DrawStretch(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH);

	protected://Member Value//

		HDC dc = nullptr;

	};

}

#endif

#endif
