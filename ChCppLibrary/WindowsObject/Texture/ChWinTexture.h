#ifdef _WINDOWS_

#ifndef Ch_Win_WTex_h
#define Ch_Win_WTex_h

#include"../../BasePack/ChMath.h"

namespace ChWin
{
	class Brush;
	class WindDrawer;

	struct RGBData
	{
		inline RGBData()
		{
			num = 0;
		}

		inline RGBData(const COLORREF& _col)
		{
			num = _col;
		}

		inline RGBData(const RGBData& _col)
		{
			num = _col.num;
		}

		union
		{
			COLORREF num = 0;
			ChMath::Vector4Base<unsigned char> byte;
		};
	};

	enum class Stretch :int
	{
		BlackOnWhite = BLACKONWHITE,
		ColorOnColor = COLORONCOLOR,
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

	class Texture :public ChCp::Initializer
	{
	public://ConstructorDestructor//

		inline virtual ~Texture() { Release(); }

	public://InitAndRelease//

		void Release();

	public://Create Functions//

		bool CreateTexture(HWND _hWnd, const char* _fileName);

		bool CreateTexture(HWND _hWnd, const wchar_t* _fileName);

		bool CreateTexture(HINSTANCE _instance, const char* _fileName);

		bool CreateTexture(HINSTANCE _instance, const wchar_t* _fileName);

		bool CreateTexture(const ChINTPOINT& _size, const unsigned char* _bit);

		bool CreateTexture(const int _width, const int _height, const unsigned char* _bit);

		bool CreateTexture(const ChINTPOINT& _size, const unsigned char* _bit, const unsigned int _nPlanes, const unsigned int _bitCount);

		bool CreateTexture(const int _width, const int _height, const unsigned char* _bit, const unsigned int _nPlanes, const unsigned int _bitCount);

		HBRUSH CreateBrush()const;

	public://Set Functions//

		void SetTextureToHDC(HDC _target);

		void SetStretchToHDC(HDC _target);

		inline void SetStretchType(const Stretch _stretch) { stretchType = _stretch; }

		inline void SetRasterizerOperationCodeType(const RasterizerOperationCodeType _opeCode) { opeCode = _opeCode; }

	public://Get Functions//

		inline RasterOpeCode GetRasterizerOperationCodeType() { return opeCode; }

		inline HBITMAP GetTexture() { return mainTexture; }

		inline ChINTPOINT GetTextureSize()
		{
			return
#ifdef UNICODE
				GetTextureSizeW();
#else
				GetTextureSizeA();
#endif
		}

		ChINTPOINT GetTextureSizeW();

		ChINTPOINT GetTextureSizeA();

#ifdef CRT
		inline std::vector<RGBData> GetTextureByte()
		{
			return
#ifdef UNICODE
				GetTextureByteW();
#else
				GetTextureByteA();
#endif
		}

		std::vector<RGBData> GetTextureByteW();

		std::vector<RGBData> GetTextureByteA();
#endif

		inline BITMAP GetTextureData()
		{
			return
#ifdef UNICODE
				GetTextureDataW();
#else
				GetTextureDataA();
#endif
		}

		BITMAP GetTextureDataW();

		BITMAP GetTextureDataA();

	private:

#ifdef CRT
		std::vector<RGBData> GetMonoColor(BITMAP& _ddb);

		std::vector<RGBData> GetByteColor(BITMAP& _ddb);
#endif

	public://Other Functions//

		void Draw(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos = ChINTPOINT(0, 0));

		void Draw(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize);

		void DrawStretch(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent);

		void DrawTransparent(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const HBITMAP _maskTex);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const HBITMAP _maskTex);

		void DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const HBITMAP _maskTex, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const HBITMAP _maskTex, const int _rot);

		void Draw(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos = ChINTPOINT(0, 0));

		void Draw(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize);

		void DrawStretch(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent);

		void DrawTransparent(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const HBITMAP _maskTex);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const HBITMAP _maskTex);

		void DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const HBITMAP _maskTex, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const HBITMAP _maskTex, const int _rot);

		//bool FillTexture(const FillType _type = FillType::Whiteness);

	protected://Other Functions//

		void DrawMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos);

		void DrawStretchMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize);

		void DrawTransparentMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent);

		void DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent);

		void DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const HBITMAP _maskTex);

		void DrawPlgMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const unsigned long _rot);

		void DrawPlgMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const HBITMAP _maskTex, const unsigned long _rot);

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

		bool CreateRenderTarget(HWND _hWnd, const ChINTPOINT& _size);
		bool CreateRenderTarget(HWND _hWnd, const int _width, const int _height);

		bool CreateRenderTarget(HDC _dc, const ChINTPOINT& _size);
		bool CreateRenderTarget(HDC _dc, const int _width, const int _height);

		inline HBRUSH CreateBrush()const { return Texture::CreateBrush(); }

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

		inline ChINTPOINT GetTextureSize() { return Texture::GetTextureSize(); }

		inline ChINTPOINT GetTextureSizeW() { return Texture::GetTextureSizeW(); }

		inline ChINTPOINT GetTextureSizeA() { return Texture::GetTextureSizeA(); }

#ifdef CRT
		inline std::vector<RGBData> GetTextureByte() { return Texture::GetTextureByte(); }

		std::vector<RGBData> GetTextureByteW() { return Texture::GetTextureByteW(); }

		std::vector<RGBData> GetTextureByteA() { return Texture::GetTextureByteA(); }
#endif

		inline BITMAP GetTextureData() { return Texture::GetTextureData(); };

		BITMAP GetTextureDataW() { return Texture::GetTextureDataW(); }

		BITMAP GetTextureDataA() { return Texture::GetTextureDataA(); }

	public://Is Function//

		bool IsInit()const { return static_cast<bool>(*this); }

	public://Other Functions//

		void Draw(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos = ChINTPOINT(0, 0));

		void Draw(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize);

		void DrawStretch(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent);

		void DrawTransparent(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, HBITMAP _maskTex);

		void DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, HBITMAP _maskTex);

		void DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, HBITMAP _maskTex, const int _rot);

		void DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, HBITMAP _maskTex, const int _rot);

		void Draw(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos = ChINTPOINT(0, 0));

		void Draw(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX = 0, const int _baseY = 0);

		void DrawStretch(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize);

		void DrawStretch(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH);

		void DrawTransparent(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent);

		void DrawTransparent(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent);

		void DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, HBITMAP _maskTex);

		void DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, HBITMAP _maskTex);

		void DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, HBITMAP _maskTex, const int _rot);

		void DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, HBITMAP _maskTex, const int _rot);

		void DrawBrush(HBRUSH _brush);

		void DrawBrush(ChWin::Brush& _brush);

		void FillRT(HBRUSH _brush, const RECT& _range);

		void FillRT(HBRUSH _brush, const long _x, const long _y, const long _w, const long _h);

		void FillRT(ChWin::Brush& _brush, const RECT& _range);

		void FillRT(ChWin::Brush& _brush, const long _x, const long _y, const long _w, const long _h);

		//bool UpdateDC(HDC _dc);

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

		bool CreateMaskTexture(HWND _hWnd, const char* _fileName);

		bool CreateMaskTexture(HWND _hWnd, const wchar_t* _fileName);

		bool CreateMaskTexture(HINSTANCE _instance, const char* _fileName);

		bool CreateMaskTexture(HINSTANCE _instance, const wchar_t* _fileName);

		bool CreateMaskTexture(const ChINTPOINT& _size, const unsigned char* _bit);

		bool CreateMaskTexture(const int _width, const int _height, const unsigned char* _bit);

		bool CreateMaskTexture(const ChINTPOINT& _size);

		bool CreateMaskTexture(const int _width, const int _height);

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

		inline ChINTPOINT GetTextureSize() { return Texture::GetTextureSize(); }

		inline ChINTPOINT GetTextureSizeW() { return Texture::GetTextureSizeW(); }

		inline ChINTPOINT GetTextureSizeA() { return Texture::GetTextureSizeA(); }

#ifdef CRT
		inline std::vector<RGBData> GetTextureByte() { return Texture::GetTextureByte(); }

		std::vector<RGBData> GetTextureByteW() { return Texture::GetTextureByteW(); }

		std::vector<RGBData> GetTextureByteA() { return Texture::GetTextureByteA(); }
#endif

		inline BITMAP GetTextureData() { return Texture::GetTextureData(); };

		BITMAP GetTextureDataW() { return Texture::GetTextureDataW(); }

		BITMAP GetTextureDataA() { return Texture::GetTextureDataA(); }

	public://Is Function//

		bool IsInit()const { return RenderTarget::IsInit(); }

	};

}

#ifdef CRT

std::vector<ChWin::RGBData> ChWin::Texture::GetTextureByteW()
{
	BITMAP tmp = GetTextureDataW();

	return tmp.bmBitsPixel >= 8 ? GetByteColor(tmp) : GetMonoColor(tmp);
}

std::vector<ChWin::RGBData> ChWin::Texture::GetTextureByteA()
{
	BITMAP tmp = GetTextureDataA();

	return tmp.bmBitsPixel > 8 ? GetByteColor(tmp) : GetMonoColor(tmp);
}

std::vector<ChWin::RGBData> ChWin::Texture::GetMonoColor(BITMAP& _ddb)
{

	std::vector<RGBData> out;

#if 0

	if (_ddb.bmWidth <= 0 ||
		_ddb.bmHeight <= 0 ||
		_ddb.bmBitsPixel <= 0)return out;

	if (_ddb.bmBitsPixel != 1)return out;

	BITMAPINFO info;

	ChStd::MZero(&info);

	info.bmiHeader.biSize = sizeof(BITMAPINFO);
	info.bmiHeader.biWidth = _ddb.bmWidth;
	info.bmiHeader.biHeight = _ddb.bmHeight;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = _ddb.bmBitsPixel;
	info.bmiHeader.biCompression = BI_RGB;

	const unsigned long createByteNum = (((_ddb.bmWidth * _ddb.bmHeight) / 8) + 1) * 4;

	unsigned char* byte = new unsigned char[createByteNum];

	auto dc = CreateCompatibleDC(nullptr);

	SetTextureToHDC(dc);

	if (GetDIBits(dc, mainTexture, 0, _ddb.bmHeight, byte, &info, DIB_RGB_COLORS) != 0)
	{
		ChCpp::BitBool flgs;
		unsigned char moveCount = 0;
		unsigned long byteCount = 0;

		flgs.SetValue(byte[byteCount]);

		while (out.size() < _ddb.bmWidth * _ddb.bmHeight)
		{

			RGBData col;
			for (unsigned char i = 0; i < 3; i++)
			{
				col.byte[3 - i] = flgs.GetBitFlg(moveCount) ? 1 : 0;
				col.byte[3 - i] *= 255;
			}

			if (col.r == 255)
			{
				int t = 0;
				t = 1;
			}

			out.push_back(col);

			moveCount++;
			if (moveCount < 8)continue;
			if (byteCount > createByteNum)
			{
				int t = 0;
				t = 1;
				break;
			}
			if (byteCount > 10000)
			{
				int t = 0;
				t = 1;
				break;
			}
			moveCount = 0;
			flgs.SetValue(byte[byteCount]);
			byteCount++;
		}

	}

	delete[] byte;

#endif

	return out;
}

std::vector<ChWin::RGBData> ChWin::Texture::GetByteColor(BITMAP& _ddb)
{

	std::vector<RGBData> out;

	if (_ddb.bmWidth <= 0 ||
		_ddb.bmHeight <= 0 ||
		_ddb.bmBitsPixel <= 0)return out;

	BITMAPINFO info;

	ChStd::MZero(&info);

	info.bmiHeader.biSize = sizeof(BITMAPINFO);
	info.bmiHeader.biWidth = _ddb.bmWidth;
	info.bmiHeader.biHeight = _ddb.bmHeight;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = _ddb.bmBitsPixel;
	info.bmiHeader.biCompression = BI_RGB;

	const unsigned char colorTypeCount = (_ddb.bmBitsPixel / 8);

	unsigned long* byte = new unsigned long[_ddb.bmWidth * _ddb.bmHeight];

	auto dc = CreateCompatibleDC(nullptr);

	SetTextureToHDC(dc);

	if (GetDIBits(dc, mainTexture, 0, _ddb.bmHeight, byte, &info, DIB_RGB_COLORS) != 0)
	{
		unsigned long count = 0;

		for (long h = 0; h < _ddb.bmHeight; h++)
		{
			for (long w = 0; w < _ddb.bmWidth; w++)
			{
				RGBData col;

				col.num = byte[w + (h * _ddb.bmWidth)];

				out.push_back(col);
			}
			count += 1;
		}
	}

	delete[] byte;

	return out;
}

void ChWin::Texture::DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent)
{

	static MaskTexture maskRT;

	{
		auto texSize = GetTextureSize();

		maskRT.CreateMaskTexture(texSize.w, texSize.h);
		auto oldBkColor = SetBkColor(_textureHDC, _transparent);

		{

			auto oCode = opeCode;

			opeCode = RasterOpeCode::NotSRCCopy;

			DrawMain(_textureHDC, maskRT.GetRenderTarget(), ChINTPOINT(0, 0), texSize, ChINTPOINT(0, 0));

			opeCode = oCode;

			auto test = maskRT.GetTextureByte();
		}

		SetBkColor(_textureHDC, oldBkColor);

	}

	DrawMaskMain(_textureHDC, _drawTarget, _pos, _size, _basePos, maskRT.GetTexture());
}

#endif


#endif

#endif
