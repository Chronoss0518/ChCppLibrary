#include<Windows.h>
#include<wingdi.h>
#include"../../BaseIncluder/ChBase.h"

#include"../PackData/ChPoint.h"
#include"../PackData/ChRect.h"
#include"../WinGDI/ChWinBrush.h"
#include"ChWinTexture.h"

using namespace ChWin;


//Texture Method//

void Texture::Release()
{
	if (ChPtr::NullCheck(mainTexture))return;

	DeleteObject(mainTexture);
	mainTexture = nullptr;

	SetInitFlg(false);
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

ChStd::Bool Texture::CreateTexture(const ChINTPOINT& _size, const unsigned char* _bit)
{
	return CreateTexture(_size, _bit, 1, 1);
}

ChStd::Bool Texture::CreateTexture(const int _width, const int _height, const unsigned char* _bit)
{
	return CreateTexture(ChINTPOINT(_width, _height), _bit, 1, 1);
}

ChStd::Bool Texture::CreateTexture(const ChINTPOINT& _size, const unsigned char* _bit, const unsigned int _nPlanes, const unsigned int _bitCount)
{

	Release();

	auto size = _size;
	size.Abs();

	mainTexture = CreateBitmap(size.w, size.h, _nPlanes, _bitCount, _bit);

	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	return true;
}

ChStd::Bool Texture::CreateTexture(const int _width, const int _height, const unsigned char* _bit, const unsigned int _nPlanes, const unsigned int _bitCount)
{
	return CreateTexture(ChINTPOINT(_width, _height), _bit, _nPlanes, _bitCount);
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

ChINTPOINT Texture::GetTextureSizeW()
{
	if (ChPtr::NullCheck(mainTexture))return ChINTPOINT();

	BITMAP tmp;
	GetObjectW(
		mainTexture,
		sizeof(BITMAP),
		&tmp
	);

	return ChINTPOINT(tmp.bmWidth, tmp.bmHeight);
}

ChINTPOINT Texture::GetTextureSizeA()
{
	if (ChPtr::NullCheck(mainTexture))return ChINTPOINT();

	BITMAP tmp;
	GetObjectA(
		mainTexture,
		sizeof(BITMAP),
		&tmp
	);

	return ChINTPOINT(tmp.bmWidth, tmp.bmHeight);
}

void Texture::Draw(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos)
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
	Draw(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY));
}

void Texture::DrawStretch(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize)
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
	DrawStretch(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH));
}

void Texture::DrawTransparent(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent)
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
	DrawTransparent(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent);
}

void Texture::DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	HDC tmp = CreateCompatibleDC(_drawTarget);

	SetTextureToHDC(tmp);

	DrawMaskMain(tmp, _drawTarget, _pos, _size, _basePos, _transparent);

	DeleteDC(tmp);
}

void Texture::DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent)
{
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _transparent);
}

void Texture::DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, HBITMAP _maskTex)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	HDC tmp = CreateCompatibleDC(_drawTarget);

	SetTextureToHDC(tmp);

	DrawMaskMain(tmp, _drawTarget, _pos, _size, _basePos, _maskTex);

	DeleteDC(tmp);

}

void Texture::DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, HBITMAP _maskTex)
{
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _maskTex);
}

void Texture::DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	HDC tmp = CreateCompatibleDC(_drawTarget);

	SetTextureToHDC(tmp);

	DrawPlgMain(tmp, _drawTarget, _pos, _size, _basePos, _baseSize, _transparent,_rot);

	DeleteDC(tmp);
}

void Texture::DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot)
{
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent,_rot);
}

void Texture::DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, HBITMAP _maskTex, const int _rot)
{
	if (!IsInit())return;

	if (ChPtr::NullCheck(_drawTarget))return;

	HDC tmp = CreateCompatibleDC(_drawTarget);

	SetTextureToHDC(tmp);

	DrawPlgMain(tmp, _drawTarget, _pos, _size, _basePos, _baseSize, _maskTex, _rot);

	DeleteDC(tmp);

}

void Texture::DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, HBITMAP _maskTex, const int _rot)
{
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _maskTex, _rot);

}

void Texture::Draw(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos)
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
	Draw(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY));
}

void Texture::DrawStretch(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize)
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
	DrawStretch(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH));
}

void Texture::DrawTransparent(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent)
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
	DrawTransparent(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent);
}

void Texture::DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent)
{
	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	SetTextureToHDC(tmp);

	DrawMaskMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _transparent);

	DeleteDC(tmp);
}

void Texture::DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent)
{
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _transparent);
}

void Texture::DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, HBITMAP _maskTex)
{
	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	SetTextureToHDC(tmp);

	DrawMaskMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _maskTex);

	DeleteDC(tmp);
}

void Texture::DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, HBITMAP _maskTex)
{
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _maskTex);
}

void Texture::DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot)
{
	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	SetTextureToHDC(tmp);

	DrawPlgMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _transparent, _rot);

	DeleteDC(tmp);
}

void Texture::DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot)
{
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent,_rot);
}

void Texture::DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, HBITMAP _maskTex, const int _rot)
{
	if (!IsInit())return;

	if (!_drawTarget.IsInit())return;

	HDC tmp = CreateCompatibleDC(_drawTarget.GetRenderTarget());

	SetTextureToHDC(tmp);

	DrawPlgMain(tmp, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _maskTex, _rot);

	DeleteDC(tmp);
}

void Texture::DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, HBITMAP _maskTex, const int _rot)
{
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _maskTex, _rot);
}

void Texture::DrawMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos)
{

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();

	BitBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, ChStd::EnumCast(opeCode));

}

void Texture::DrawStretchMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize)
{

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	auto bsize = _baseSize;

	int tmpStretch = SetStretchBltMode(_drawTarget, ChStd::EnumCast(stretchType));

	StretchBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, bsize.w, bsize.h, ChStd::EnumCast(opeCode));

	SetStretchBltMode(_drawTarget, tmpStretch);

}

void Texture::DrawTransparentMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent)
{

	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();
	auto bsize = _baseSize;
	bsize.val.Abs();

	TransparentBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, bsize.w, bsize.h, _transparent);

}

void Texture::DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent)
{

	static MaskTexture maskRT;

	{
		auto texSize = GetTextureSize();

		maskRT.CreateMaskTexture(texSize.w, texSize.h);
		auto oldBkColor = SetBkColor(_textureHDC,_transparent);

		{

			auto oCode = opeCode;

			opeCode = RasterOpeCode::NotSRCCopy;

			DrawMain(_textureHDC, maskRT.GetRenderTarget(), ChINTPOINT(0, 0), texSize, ChINTPOINT(0, 0));

			opeCode = oCode;

		}

		SetBkColor(_textureHDC, oldBkColor);

	}


	DrawMaskMain(_textureHDC, _drawTarget, _pos, _size, _basePos, maskRT.GetTexture());

}

void Texture::DrawMaskMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, HBITMAP _maskTex)
{
	auto pos = _pos;
	pos.val.Abs();
	auto size = _size;
	size.val.Abs();
	auto bpos = _basePos;
	bpos.val.Abs();

	HBRUSH tmp = (HBRUSH)SelectObject(_drawTarget, CreatePatternBrush((HBITMAP)GetCurrentObject(_drawTarget, OBJ_BITMAP)));

	int out = MaskBlt(_drawTarget, pos.x, pos.y, size.w, size.h, _textureHDC, bpos.x, bpos.y, _maskTex, bpos.x, bpos.y, MAKEROP4(ChStd::EnumCast(opeCode), ChStd::EnumCast(RasterOpeCode::PATCopy)));

	DeleteObject(SelectObject(_drawTarget, tmp));

}

void Texture::DrawPlgMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const unsigned long _rot)
{
	auto bpos = _basePos;
	bpos.val.Abs();
	auto bsize = _baseSize;
	bsize.val.Abs();

	static MaskTexture maskRT;

	{
		auto texSize = GetTextureSize();

		maskRT.CreateMaskTexture(texSize.w, texSize.h);
		auto oldBkColor = SetBkColor(_textureHDC,_transparent);

		{

			auto oCode = opeCode;

			opeCode = RasterOpeCode::NotSRCCopy;

			DrawMain(_textureHDC,maskRT.GetRenderTarget(), ChINTPOINT(0, 0), texSize, ChINTPOINT(0, 0));
			
			opeCode = oCode;

		}
		
		SetBkColor(_textureHDC, oldBkColor);

	}

	DrawPlgMain(_textureHDC, _drawTarget, _pos, _size, _basePos, _baseSize, maskRT.GetTexture(), _rot);
}

void Texture::DrawPlgMain(HDC _textureHDC, HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, HBITMAP _maskTex, const unsigned long _rot)
{
	auto pos = _pos;
	auto size = _size;
	auto bpos = _basePos;
	bpos.val.Abs();
	auto bsize = _baseSize;
	bsize.val.Abs();

	POINT edgePoint[3]{ {0,0},{0,0} ,{0,0} };

	{
		ChVec3 rotPointBase[3];

		ChLMat mat;

		mat.SetPosition(static_cast<float>(pos.x + size.x * 0.5f), static_cast<float>(pos.y + size.x * 0.5f), 0.0f);

		mat.SetRotationZAxis(ChMath::ToRadian(static_cast<float>(_rot)));

		for (char i = 0; i < 3; i++)
		{
			rotPointBase[i] = ChVec3(static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
		}

		rotPointBase[1].x += size.x;
		rotPointBase[2].y += size.y;

		for (char i = 0; i < 3; i++)
		{
			rotPointBase[i] -= ChVec3(static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
			rotPointBase[i] -= ChVec3(size.x * 0.5f, size.y * 0.5f, 0.0f);
			rotPointBase[i] = mat.Transform(rotPointBase[i]);
			edgePoint[i].x = static_cast<long>(rotPointBase[i].x);
			edgePoint[i].y = static_cast<long>(rotPointBase[i].y);
		}

	}

	int tmpStretch = SetStretchBltMode(_drawTarget, ChStd::EnumCast(stretchType));

	int out = PlgBlt(_drawTarget, edgePoint, _textureHDC, bpos.x, bpos.y, bsize.w, bsize.h, _maskTex, bpos.x, bpos.y);

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

ChStd::Bool RenderTarget::CreateRenderTarget(HWND _hWnd, const ChINTPOINT& _size)
{
	HDC tmp = GetDC(_hWnd);

	auto success = CreateRenderTarget(tmp, _size);

	ReleaseDC(_hWnd, tmp);

	return success;
}

ChStd::Bool RenderTarget::CreateRenderTarget(HWND _hWnd, const int _width, const int _height)
{
	return CreateRenderTarget(_hWnd,ChINTPOINT(_width,_height));
}

ChStd::Bool RenderTarget::CreateRenderTarget(HDC _dc, const ChINTPOINT& _size)
{
	if (ChPtr::NullCheck(_dc))return false;

	auto texSize = GetTextureSize();

	auto size = _size;
	size.val.Abs();

	if(size.w == texSize.w && size.h == texSize.h) 
	{
		if (ChPtr::NullCheck(dc))
		{
			DeleteDC(dc);
			dc = nullptr;
		}
	}
	else
	{
		Release();
	}

	dc = CreateCompatibleDC(_dc);

	if (ChPtr::NullCheck(dc))
	{
		return false;
	}

	mainTexture = CreateCompatibleBitmap(_dc, size.w, size.h);

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

ChStd::Bool RenderTarget::CreateRenderTarget(HDC _dc, const int _width, const int _height)
{
	return CreateRenderTarget(_dc, ChINTPOINT(_width, _height));
}

void RenderTarget::Draw(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawMain(dc, _drawTarget, _pos, _size, _basePos);

}

void RenderTarget::Draw(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	Draw(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY));
}

void RenderTarget::DrawStretch(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;

	DrawStretchMain(dc, _drawTarget, _pos, _size, _basePos, _baseSize);
}

void RenderTarget::DrawStretch(HDC _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;

	DrawStretch(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH));
}

void RenderTarget::DrawTransparent(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawTransparentMain(dc, _drawTarget, _pos, _size, _basePos, _baseSize, _transparent);

}

void RenderTarget::DrawTransparent(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawTransparent(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent);
}

void RenderTarget::DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawMaskMain(dc,_drawTarget, _pos, _size, _basePos,_transparent);
}

void RenderTarget::DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY),_transparent);
}

void RenderTarget::DrawMask(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const HBITMAP _maskTex)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawMaskMain(dc, _drawTarget, _pos, _size, _basePos, _maskTex);
}

void RenderTarget::DrawMask(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const HBITMAP _maskTex)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _maskTex);
}

void RenderTarget::DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawPlgMain(dc, _drawTarget, _pos, _size, _basePos, _baseSize, _transparent, _rot);
}

void RenderTarget::DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent,_rot);
}

void RenderTarget::DrawPlg(HDC _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const HBITMAP _maskTex, const int _rot)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawPlgMain(dc, _drawTarget, _pos, _size, _basePos, _baseSize, _maskTex, _rot);
}

void RenderTarget::DrawPlg(HDC _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const HBITMAP _maskTex, const int _rot)
{
	if (!IsInit())return;
	if (_drawTarget == dc)return;
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _maskTex, _rot);
}

void RenderTarget::Draw(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos);
}

void RenderTarget::Draw(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	Draw(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY));
}

void RenderTarget::DrawStretch(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawStretchMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize);
}

void RenderTarget::DrawStretch(RenderTarget& _drawTarget, const int  _x, const int  _y, const int  _w, const int  _h, const int  _baseX, const int  _baseY, const int  _baseW, const int  _baseH)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawStretch(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH));
}

void RenderTarget::DrawTransparent(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawTransparentMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _transparent);
}

void RenderTarget::DrawTransparent(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawTransparent(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent);
}

void RenderTarget::DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const UINT _transparent)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawMaskMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _transparent);
}

void RenderTarget::DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const UINT _transparent)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _transparent);
}

void RenderTarget::DrawMask(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const HBITMAP _maskTex)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawMaskMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _maskTex);
}

void RenderTarget::DrawMask(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const HBITMAP _maskTex)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawMask(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), _maskTex);
}

void RenderTarget::DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const UINT _transparent, const int _rot)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawPlgMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _transparent, _rot);
}

void RenderTarget::DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const UINT _transparent, const int _rot)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _transparent,_rot);
}

void RenderTarget::DrawPlg(RenderTarget& _drawTarget, const ChINTPOINT& _pos, const ChINTPOINT& _size, const ChINTPOINT& _basePos, const ChINTPOINT& _baseSize, const HBITMAP _maskTex, const int _rot)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawPlgMain(dc, _drawTarget.GetRenderTarget(), _pos, _size, _basePos, _baseSize, _maskTex, _rot);
}

void RenderTarget::DrawPlg(RenderTarget& _drawTarget, const int _x, const int _y, const int _w, const int _h, const int _baseX, const int _baseY, const int _baseW, const int _baseH, const HBITMAP _maskTex, const int _rot)
{
	if (!IsInit())return;
	if (&_drawTarget == this)return;
	DrawPlg(_drawTarget, ChINTPOINT(_x, _y), ChINTPOINT(_w, _h), ChINTPOINT(_baseX, _baseY), ChINTPOINT(_baseW, _baseH), _maskTex, _rot);
}

void RenderTarget::DrawBrush(HBRUSH _brush)
{
	if (ChPtr::NullCheck(_brush))return;
	if (!IsInit())return;

	auto texSize = GetTextureSize();

	ChRECT rec;

	rec.bottom = texSize.h;
	rec.right = texSize.w;

	FillRT(_brush, rec);

}


void RenderTarget::DrawBrush(ChWin::Brush& _brush)
{
	if (!IsInit())return;

	auto texSize = GetTextureSize();

	ChRECT rec;

	rec.bottom = texSize.h;
	rec.right = texSize.w;

	_brush.FillRect(dc, rec);

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

void RenderTarget::FillRT(ChWin::Brush& _brush, const RECT& _range)
{
	if (!IsInit())return;
	_brush.FillRect(dc, _range);
}

void RenderTarget::FillRT(ChWin::Brush& _brush, const long _x, const long _y, const long _w, const long _h)
{
	if (!IsInit())return;

	RECT tmp;
	tmp.top = _y;
	tmp.bottom = _y + _h;

	tmp.left = _x;
	tmp.right = _x + _w;

	_brush.FillRect(dc, tmp);
}

ChStd::Bool MaskTexture::CreateMaskTexture(HWND _hWnd, const std::string& _fileName)
{

	HINSTANCE ins = reinterpret_cast<HINSTANCE>(GetWindowLongA(_hWnd, GWL_HINSTANCE));

	return CreateTexture(ins, _fileName);

}

ChStd::Bool MaskTexture::CreateMaskTexture(HWND _hWnd, const std::wstring& _fileName)
{

	HINSTANCE ins = reinterpret_cast<HINSTANCE>(GetWindowLongW(_hWnd, GWL_HINSTANCE));

	return CreateTexture(ins, _fileName);
}

ChStd::Bool MaskTexture::CreateMaskTexture(HINSTANCE _instance, const std::string& _fileName)
{
	Release();

	mainTexture = static_cast<HBITMAP>(LoadImageA(_instance, _fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_MONOCHROME));

	if (ChPtr::NullCheck(mainTexture))return false;

	SetInitFlg(true);

	dc = CreateCompatibleDC(NULL);

	if (ChPtr::NullCheck(dc))
	{
		Release();
		return false;
	}

	SetTextureToHDC(dc);

	return true;
}

ChStd::Bool MaskTexture::CreateMaskTexture(HINSTANCE _instance, const std::wstring& _fileName)
{

	Release();

	mainTexture = static_cast<HBITMAP>(LoadImageW(_instance, _fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_MONOCHROME));

	if (ChPtr::NullCheck(mainTexture))return false;

	dc = CreateCompatibleDC(NULL);

	if (ChPtr::NullCheck(dc))
	{
		Release();
		return false;
	}

	SetInitFlg(true);

	SetTextureToHDC(dc);

	return true;
}

ChStd::Bool MaskTexture::CreateMaskTexture(const ChINTPOINT& _size, const unsigned char* _bit)
{
	if (!Texture::CreateTexture(_size, _bit,1,1))return false;

	dc = CreateCompatibleDC(NULL);

	if (ChPtr::NullCheck(dc))
	{
		Release();
		return false;
	}

	SetTextureToHDC(dc);

	return true;
}

ChStd::Bool MaskTexture::CreateMaskTexture(const int _width, const int _height, const unsigned char* _bit)
{
	return CreateMaskTexture(ChINTPOINT(_width, _height), _bit);
}

ChStd::Bool MaskTexture::CreateMaskTexture(const ChINTPOINT& _size)
{
	return CreateMaskTexture(_size, nullptr);
}

ChStd::Bool MaskTexture::CreateMaskTexture(const int _width, const int _height)
{
	return CreateMaskTexture(ChINTPOINT(_width, _height), nullptr);
}
