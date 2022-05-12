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

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();

	HDC tmp = CreateCompatibleDC(_drawTarget);
	
	SetTextureToHDC(tmp);

	BitBlt(_drawTarget, pos.x, pos.y, size.w, size.h, tmp, bpos.x, bpos.y, ChStd::EnumCast(opeCode));

	DeleteDC(tmp);

}

void Texture::Draw(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY)
{
	Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void Texture::DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();
	auto bsize = _baseSize;
	bsize.val.Abs();

	HDC tmp = CreateCompatibleDC(_drawTarget);

	int tmpStretch = GetStretchBltMode(_drawTarget);

	SetStretchBltMode(_drawTarget, ChStd::EnumCast(stretchType));

	SetTextureToHDC(tmp);

	StretchBlt(_drawTarget, pos.x, pos.y, size.w, size.h, tmp, bpos.x, bpos.y, bsize.w, bsize.h, ChStd::EnumCast(opeCode));

	DeleteDC(tmp);

	SetStretchBltMode(_drawTarget, tmpStretch);

}

void Texture::DrawStretch(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH)
{
	DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}

void Texture::Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{

	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	SetTextureToHDC(tmp);

	BitBlt(_drawTarget.GetRenderTarget(), pos.x, pos.y, size.w, size.h, tmp, bpos.x, bpos.y, ChStd::EnumCast(opeCode));

	DeleteDC(tmp);

}

void Texture::Draw(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY)
{
	Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void Texture::DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{

	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();
	auto bsize = _baseSize;
	bsize.val.Abs();

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	int tmpStretch = GetStretchBltMode(_drawTarget.GetRenderTarget());

	SetStretchBltMode(_drawTarget.GetRenderTarget(), ChStd::EnumCast(stretchType));

	SetTextureToHDC(tmp);

	StretchBlt(_drawTarget.GetRenderTarget(), pos.x, pos.y, size.w, size.h, tmp, bpos.x, bpos.y, bsize.w, bsize.h, ChStd::EnumCast(opeCode));

	DeleteDC(tmp);

	SetStretchBltMode(_drawTarget.GetRenderTarget(), tmpStretch);

}

void Texture::DrawStretch(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH)
{
	DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
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
	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	return true;
}

ChStd::Bool RenderTarget::CreateRenderTarget(HDC _dc, const int _width, const int _height)
{
	Texture::Release();

	int w = _width >= 0 ? _width : _width * -1;
	int h = _height >= 0 ? _height : _height * -1;


	dc = _dc;
	mainTexture = CreateCompatibleBitmap(dc, w, h);

	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	return true;

}

void RenderTarget::Draw(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	Texture::Draw(_drawTarget, _pos, _size, _basePos);
}

void RenderTarget::Draw(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY)
{

	if (!IsInit())return;
	if (_drawTarget == dc)return;
	Texture::Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void RenderTarget::DrawStretch(HDC _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{

	if (!IsInit())return;
	if (_drawTarget == dc)return;
	Texture::DrawStretch(_drawTarget, _pos, _size, _basePos,_baseSize);
}

void RenderTarget::DrawStretch(HDC _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH)
{

	if (!IsInit())return;
	if (_drawTarget == dc)return;
	Texture::DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}

void RenderTarget::Draw(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	Texture::Draw(_drawTarget, _pos, _size, _basePos);
}

void RenderTarget::Draw(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	Texture::Draw(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY));
}

void RenderTarget::DrawStretch(RenderTarget& _drawTarget, const ChMath::Vector2Base<int>& _pos, const ChMath::Vector2Base<int>& _size, const ChMath::Vector2Base<int>& _basePos, const ChMath::Vector2Base<int>& _baseSize)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	Texture::DrawStretch(_drawTarget, _pos, _size, _basePos, _baseSize);
}

void RenderTarget::DrawStretch(RenderTarget& _drawTarget, unsigned long _x, unsigned long _y, unsigned long _w, unsigned long _h, unsigned long _baseX, unsigned long _baseY, unsigned long _baseW, unsigned long _baseH)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	Texture::DrawStretch(_drawTarget, ChMath::Vector2Base<int>(_x, _y), ChMath::Vector2Base<int>(_w, _h), ChMath::Vector2Base<int>(_baseX, _baseY), ChMath::Vector2Base<int>(_baseW, _baseH));
}
