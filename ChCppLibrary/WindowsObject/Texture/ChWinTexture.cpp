#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseSystem/ChWindows/ChWindows.h"
#include"../WindDrawer/ChWindDrawer.h"
#include"ChWinTexture.h"

using namespace ChWin;

//Texture Method//

void Texture::Release()
{
	if (ChPtr::NullCheck(mainTexture))return;

	DeleteObject(mainTexture);
	mainTexture = nullptr;
}

ChStd::Bool Texture::CreateTexture(HWND _hWnd, const std::string& _fileName)
{
	HINSTANCE ins = reinterpret_cast<HINSTANCE>(GetWindowLongA(_hWnd, GWL_HINSTANCE));

	return CreateTexture(ins, _fileName);
}

ChStd::Bool Texture::CreateTexture(HINSTANCE _instance, const std::string& _fileName)
{
	Release();
	mainTexture = static_cast<HBITMAP>(LoadImageA(_instance, _fileName.c_str(),IMAGE_BITMAP,0,0, LR_LOADFROMFILE));

	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	return true;
}

ChStd::Bool Texture::CreateTexture(HWND _hWnd, const std::wstring& _fileName)
{

	HINSTANCE ins = reinterpret_cast<HINSTANCE>(GetWindowLongW(_hWnd, GWL_HINSTANCE));

	return CreateTexture(ins, _fileName);
}

ChStd::Bool Texture::CreateTexture(HINSTANCE _instance, const std::wstring& _fileName)
{
	Release();
	mainTexture = static_cast<HBITMAP>(LoadImageW(_instance, _fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	return true;
}

ChStd::Bool Texture::CreateTexture(const int _width, const int _height, const unsigned char* _bit)
{
	return CreateTexture(_width, _height, _bit, 1, 1);
}

ChStd::Bool Texture::CreateTexture(const int _width, const int _height, const unsigned char* _bit, const unsigned int _nPlanes, const unsigned int _bitCount)
{
	Release();

	int w = _width >= 0 ? _width : _width * -1;
	int h = _height >= 0 ? _height : _height * -1;

	mainTexture = CreateBitmap(w, h, _nPlanes, _bitCount, _bit);

	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	return true;

}

HBRUSH Texture::CreateBrush()const
{
	if (!static_cast<bool>(*this))return nullptr;

	return CreatePatternBrush(mainTexture);
}

void Texture::SetTextureToHDC(HDC _target)
{
	if (!IsInit())return;

	SelectObject(_target, mainTexture);
}

void Texture::SetStretchToHDC(HDC _target)
{

	if (!IsInit())return;

	SelectObject(_target, mainTexture);
}

void Texture::Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;


	HDC tmp = CreateCompatibleDC(_drawTarget);
	
	SetTextureToHDC(tmp);

	DrawMain(tmp, _drawTarget, _pos, _size, _basePos);

	DeleteDC(tmp);

}

void Texture::Draw(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY)
{
	Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void Texture::DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	HDC tmp = CreateCompatibleDC(_drawTarget);

	SetTextureToHDC(tmp);

	DrawStretchMain(tmp, _drawTarget, _pos, _size, _basePos, _baseSize);

	DeleteDC(tmp);

}

void Texture::DrawStretch(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH)
{
	DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}

void Texture::DrawTransparent(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	HDC tmp = CreateCompatibleDC(_drawTarget);

	SetTextureToHDC(tmp);

	DrawTransparentMain(tmp, _drawTarget, _pos, _size, _basePos, _baseSize, _transparent);

	DeleteDC(tmp);
}

void Texture::DrawTransparent(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH, const UINT _transparent)
{
	DrawTransparent(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH), _transparent);
}

void Texture::Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{

	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());
	
	SetTextureToHDC(tmp);

	DrawMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos);

	DeleteDC(tmp);

}

void Texture::Draw(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY)
{
	Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void Texture::DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{

	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());
	
	SetTextureToHDC(tmp);

	DrawStretchMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize);

	DeleteDC(tmp);

}

void Texture::DrawStretch(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH)
{
	DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}

void Texture::DrawTransparent(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent)
{

	if (!IsInit())return;
	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	SetTextureToHDC(tmp);
	
	DrawTransparentMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _transparent);

	DeleteDC(tmp);

}

void Texture::DrawTransparent(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH, const UINT _transparent)
{
	DrawTransparent(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH), _transparent);
}

void Texture::DrawMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();

	HDC tmp = CreateCompatibleDC(_drawTarget);

	BitBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, ChStd::EnumCast(opeCode));

}

void Texture::DrawStretchMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	auto bsize = _baseSize;

	int tmpStretch = GetStretchBltMode(_drawTarget);

	SetStretchBltMode(_drawTarget, ChStd::EnumCast(stretchType));

	StretchBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, bsize.w, bsize.h, ChStd::EnumCast(opeCode));

	SetStretchBltMode(_drawTarget, tmpStretch);

}

void Texture::DrawTransparentMain(HDC _textureHDC, HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent)
{

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();
	auto bsize = _baseSize;
	bsize.val.Abs();

	int tmpStretch = GetStretchBltMode(_drawTarget);

	SetStretchBltMode(_drawTarget, ChStd::EnumCast(stretchType));

	TransparentBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, bsize.w, bsize.h, _transparent);

	SetStretchBltMode(_drawTarget, tmpStretch);

}

//RenderTarget Method//

void RenderTarget::Release()
{
	if (ChPtr::NotNullCheck(dc))
	{
		DeleteDC(dc);
		dc = nullptr;
	}

	Texture::Release(); 
}

ChStd::Bool RenderTarget::CreateRenderTarget(HWND _hWnd, const int _width, const int _height)
{
	if (ChPtr::NullCheck(_hWnd))return false;
	Texture::Release();

	int w = _width >= 0 ? _width : _width * -1;
	int h = _height >= 0 ? _height : _height * -1;

	HDC tmp = GetDC(_hWnd);

	dc = CreateCompatibleDC(tmp);

	if (ChPtr::NullCheck(dc))
	{
		ReleaseDC(_hWnd, tmp);
		return false;
	}

	mainTexture = CreateCompatibleBitmap(dc, w, h);

	ReleaseDC(_hWnd, tmp);

	if (ChPtr::NullCheck(mainTexture))
	{
		ReleaseDC(_hWnd, tmp);
		DeleteDC(dc);
		dc = nullptr;
		return false;
	}

	SelectObject(dc, GetStockObject(NULL_PEN));

	SetTextureToHDC(dc);
	SetInitFlg(true);

	return true;
}

ChStd::Bool RenderTarget::CreateRenderTarget(HDC _dc, const int _width, const int _height)
{
	if (ChPtr::NullCheck(_dc))return false;
	Texture::Release();

	int w = _width >= 0 ? _width : _width * -1;
	int h = _height >= 0 ? _height : _height * -1;

	dc = CreateCompatibleDC(_dc);

	if (ChPtr::NullCheck(dc))
	{
		return false;
	}

	mainTexture = CreateCompatibleBitmap(dc, w, h);

	if (ChPtr::NullCheck(mainTexture)) 
	{
		DeleteDC(dc);
		dc = nullptr;
		return false;
	}

	SelectObject(dc, GetStockObject(NULL_PEN));
	SetTextureToHDC(dc);
	SetInitFlg(true);

	return true;

}

void RenderTarget::SetBackGroundColorA(HBRUSH _brush)
{
	if (ChPtr::NullCheck(_brush))return;
	if (!IsInit())return;

	BITMAP tmp;
	GetObjectA(
		mainTexture,
		sizeof(BITMAP),
		&tmp
	);

	SelectObject(dc, _brush);

	PatBlt(dc, 0, 0, tmp.bmWidth, tmp.bmHeight, ChStd::EnumCast(RasterOpeCode::SRCCopy));

	SelectObject(dc, GetStockObject(NULL_BRUSH));
	SetTextureToHDC(dc);
}

void RenderTarget::SetBackGroundColorW(HBRUSH _brush)
{
	if (ChPtr::NullCheck(_brush))return;
	if (!IsInit())return;
	BITMAP tmp;
	GetObjectW(
		mainTexture,
		sizeof(BITMAP),
		&tmp
	);

	SelectObject(dc, _brush);

	PatBlt(dc, 0, 0, tmp.bmWidth, tmp.bmHeight, ChStd::EnumCast(RasterOpeCode::SRCCopy));

	SelectObject(dc, GetStockObject(NULL_BRUSH));
	SetTextureToHDC(dc);
}

void RenderTarget::Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawMain(dc, _drawTarget, _pos, _size, _basePos);

}

void RenderTarget::Draw(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY)
{

	if (!IsInit())return;
	if (_drawTarget == dc)return;
	Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void RenderTarget::DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{

	if (!IsInit())return;
	if (_drawTarget == dc)return;

	DrawStretchMain(dc, _drawTarget, _pos, _size, _basePos, _baseSize);
}

void RenderTarget::DrawStretch(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;

	DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}

void RenderTarget::DrawTransparent(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawTransparentMain(dc, _drawTarget, _pos, _size, _basePos, _baseSize, _transparent);

}

void RenderTarget::DrawTransparent(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawTransparent(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH), _transparent);
}

void RenderTarget::Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos);

}

void RenderTarget::Draw(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void RenderTarget::DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawStretchMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize);
}

void RenderTarget::DrawStretch(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}

void RenderTarget::DrawTransparent(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize, const UINT _transparent)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawTransparentMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _transparent);
}

void RenderTarget::DrawTransparent(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawTransparent(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH), _transparent);
}

void RenderTarget::FillRT(HBRUSH _brush, const RECT& _range)
{
	if (!IsInit())return;
	if (ChPtr::NullCheck(_brush))return;
	FillRect(dc, &_range, _brush);
}

void RenderTarget::FillRT(HBRUSH _brush, const long _x, const long _y, const long _w, const long _h)
{
	if (!IsInit())return;
	if (ChPtr::NullCheck(_brush))return;
	RECT tmp;
	tmp.top = _y;
	tmp.bottom = _y + _h;

	tmp.left = _x;
	tmp.right = _x + _w;

	FillRect(dc, &tmp, _brush);
}