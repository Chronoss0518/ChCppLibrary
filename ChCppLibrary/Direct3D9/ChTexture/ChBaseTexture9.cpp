#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"
#include"../../CPP/ChFile/ChBinaryFile.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"ChBaseTexture9.h"
#include"TexIncluder9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//BaseTexture9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::Release()
{
	if (ChPtr::NotNullCheck(tex))tex->Release();
	tex = nullptr;

	if (ChPtr::NotNullCheck(sur))sur->Release();
	sur = nullptr;

	if (ChPtr::NotNullCheck(zBu))zBu->Release();
	zBu = nullptr;
}

template<class T>
T BaseTexture9::GetColor(
	const unsigned int _width,
	const unsigned int _height)
{
	T tmpCol;

	ZeroMemory(&tmpCol, sizeof(tmpCol));

	if (_width >= original.w || _height >= original.h)return tmpCol;

	D3DLOCKED_RECT lockRect;

	if (tex->LockRect(0, &lockRect, nullptr, 0) != D3D_OK)
	{
		return tmpCol;
	}
	T* pPitch = (T*)lockRect.pBits;

	DWORD pitch = lockRect.Pitch / sizeof(T);
	pPitch += (pitch * _height);
	tmpCol = *(pPitch + _width);

	tex->UnlockRect(0);

	return tmpCol;
}
template D3DCOLOR BaseTexture9::GetColor(
	const unsigned int _Width,
	const unsigned int _Height);

ChVec4 BaseTexture9::D3DColorToColor255(const D3DCOLOR& _col)
{
	D3DCOLOR tmpCol = _col;
	ChVec4 tmpCol2;
	tmpCol2.a = static_cast<unsigned char>((tmpCol >> 24) & 0xff) / 255.0f;
	tmpCol2.r = static_cast<unsigned char>((tmpCol >> 16) & 0xff) / 255.0f;
	tmpCol2.g = static_cast<unsigned char>((tmpCol >> 8) & 0xff) / 255.0f;
	tmpCol2.b = static_cast<unsigned char>((tmpCol) & 0xff) / 255.0f;
	return tmpCol2;
}

void BaseTexture9::CreateTextureBase(
	const char* _fileName,
	const LPDIRECT3DDEVICE9& _dev,
	const D3DCOLOR& _colKey)
{
	if (ChPtr::NotNullCheck(tex))return;

	OpenFile(_fileName);
	if (original.w <= 0 || original.h <= 0)return;

	D3DXCreateTextureFromFileExA(
		_dev,
		_fileName,
		original.w, original.h,
		1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		_colKey,
		NULL,
		NULL,
		&tex);
}

void BaseTexture9::CreateTextureBase(
	const wchar_t* _fileName,
	const LPDIRECT3DDEVICE9& _dev,
	const D3DCOLOR& _colKey)
{
	if (ChPtr::NotNullCheck(tex))return;

	OpenFile(_fileName);
	if (original.w <= 0 || original.h <= 0)return;

	D3DXCreateTextureFromFileExW(
		_dev,
		_fileName,
		original.w, original.h,
		1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		_colKey,
		NULL,
		NULL,
		&tex);
}

void BaseTexture9::CreateColTexture(
	const LPDIRECT3DDEVICE9& _dev,
	const D3DCOLOR& _col,
	const unsigned long _w,
	const unsigned long _h)
{
	D3DXCreateTexture(
		_dev, _w, _h, 1, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED, &tex);

	if (tex == nullptr)return;

	original.w = _w;
	original.h = _h;

	SetTexColor(_col);
}

template<typename T>
void BaseTexture9::CreateMinuColTexture(
	const LPDIRECT3DDEVICE9& _dev,
	const T& _col,
	const unsigned long _w,
	const unsigned long _h,
	const _D3DFORMAT _format,
	const unsigned long _usage,
	const _D3DPOOL _pool)
{
	D3DXCreateTexture(
		_dev, _w, _h, 1, _usage
		, _format, _pool, &tex);

	if (tex == nullptr)return;

	original.w = _w;
	original.h = _h;

	if(_usage != 0)return;

	SetTexColor(_col);
}
template void BaseTexture9::CreateMinuColTexture(
	const LPDIRECT3DDEVICE9& _dev,
	const D3DCOLOR& _col,
	const unsigned long _w,
	const unsigned long _h,
	const _D3DFORMAT _format,
	const DWORD _usage,
	const _D3DPOOL _pool);

void BaseTexture9::CreateZBuffer(
	const LPDIRECT3DDEVICE9& _dev,
	const _D3DFORMAT _format,
	const _D3DMULTISAMPLE_TYPE _mSample,
	const unsigned long _mQuality)
{

	if (ChPtr::NullCheck(tex))return;

	_dev->CreateDepthStencilSurface(
		original.w,
		original.h,
		_format,
		_mSample,
		_mQuality,
		false,
		&zBu,
		nullptr);
}

template<typename T>
void BaseTexture9::SetTexColor(const T& _color)
{

	D3DLOCKED_RECT lockRect;
	if (tex->LockRect(0, &lockRect, nullptr, 0) != D3D_OK)
	{
		Release();
		return;
	}
	T* pPitch = (T*)lockRect.pBits;

	UINT pitch = lockRect.Pitch / sizeof(T);
	for (unsigned int h = 0; h < original.h; h++)
	{
		for (unsigned int w = 0; w < original.w; w++)
		{
			pPitch[w] = _color;
		}
		pPitch += pitch;
	}

	tex->UnlockRect(0);
}
template void BaseTexture9::SetTexColor(const D3DCOLOR& _color);


ChPtr::Shared<ChTex::BaseTexture9> ChTex::BaseTexture9::TextureType(const std::string& _fileName)
{
	std::string tmpStr;

	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseTexture9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find("png") != tmpStr.npos)
	{
		return ChPtr::Make_S<PngTex9>();
	}

	if (tmpStr.find("jpeg") != tmpStr.npos
		|| tmpStr.find("jpg") != tmpStr.npos)
	{
		return ChPtr::Make_S<JpegTex9>();
	}

	return ChPtr::Make_S<BaseTexture9>();
}

ChPtr::Shared<ChTex::BaseTexture9> ChTex::BaseTexture9::TextureType(const std::wstring& _fileName)
{
	std::wstring tmpStr;

	{
		size_t tmpNum = _fileName.rfind(L".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseTexture9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(L"png") != tmpStr.npos)
	{
		return ChPtr::Make_S<PngTex9>();
	}

	if (tmpStr.find(L"jpeg") != tmpStr.npos
		|| tmpStr.find(L"jpg") != tmpStr.npos)
	{
		return ChPtr::Make_S<JpegTex9>();
	}

	return ChPtr::Make_S<BaseTexture9>();
}

//PngTex9 Method//

void ChTex::PngTex9::OpenFile(const char* _fileName)
{
	ChCpp::BinaryFile file;

	file.FileOpen(_fileName, false);

	auto&& tmp = file.FileRead();

	file.FileClose();

	if (tmp[0] != 0x89)return;
	if (tmp[1] != 0x50)return;
	if (tmp[2] != 0x4E)return;
	if (tmp[3] != 0x47)return;
	if (tmp[4] != 0x0D)return;
	if (tmp[5] != 0x0A)return;
	if (tmp[6] != 0x1A)return;
	if (tmp[7] != 0x0A)return;

	SetChank(tmp);

}

void ChTex::PngTex9::OpenFile(const wchar_t* _fileName)
{
	ChCpp::BinaryFile file;

	file.FileOpen(_fileName, false);

	auto&& tmp = file.FileRead();

	file.FileClose();

	if (tmp[0] != 0x89)return;
	if (tmp[1] != 0x50)return;
	if (tmp[2] != 0x4E)return;
	if (tmp[3] != 0x47)return;
	if (tmp[4] != 0x0D)return;
	if (tmp[5] != 0x0A)return;
	if (tmp[6] != 0x1A)return;
	if (tmp[7] != 0x0A)return;

	SetChank(tmp);

}

void ChTex::PngTex9::SetChank(const std::vector<unsigned char>& _str)
{
	if (_str.size() <= sizeof(CIHDR))return;

	CIHDR tagTest;

	if (_str[0 + sizeof(tagTest.Length) + 8] != 'I')return;
	if (_str[1 + sizeof(tagTest.Length) + 8] != 'H')return;
	if (_str[2 + sizeof(tagTest.Length) + 8] != 'D')return;
	if (_str[3 + sizeof(tagTest.Length) + 8] != 'R')return;

	auto&& chank =  ChStr::StrBinaryToNum<CIHDR, unsigned char>(&_str[0], _str.size(), 8);

	if (chank.Length <= 0)return;

	ChStr::Bytes<unsigned long> wData;
	wData.val = chank.CWData;

	ChStr::Bytes<unsigned long> hData;
	hData.val = chank.CHData;

	for (unsigned char i = 0; i < 2; i++)
	{
		wData.byte[i] += wData.byte[4 - i - 1];
		wData.byte[4 - i - 1] = wData.byte[i] - wData.byte[4 - i - 1];
		wData.byte[i] = wData.byte[i] - wData.byte[4 - i - 1];

		hData.byte[i] += hData.byte[4 - i - 1];
		hData.byte[4 - i - 1] = hData.byte[i] - hData.byte[4 - i - 1];
		hData.byte[i] = hData.byte[i] - hData.byte[4 - i - 1];
	}

	original.w = wData.val;
	original.h = hData.val;
}

//JpegTex9 Method//

void ChTex::JpegTex9::OpenFile(const char* _fileName)
{
	ChCpp::BinaryFile file;
	file.FileOpen(_fileName,false);

	auto&& tmp = file.FileRead();

	file.FileClose();

	SetSegment(tmp);
}

void ChTex::JpegTex9::OpenFile(const wchar_t* _fileName)
{
	ChCpp::BinaryFile file;
	file.FileOpen(_fileName,false);

	auto&& tmp = file.FileRead();

	file.FileClose();

	SetSegment(tmp);
}

void ChTex::JpegTex9::SetSegment(const std::vector<unsigned char>& _str)
{
	if (_str.size() <= sizeof(S_SOF))return;

	if (_str[0] != 0xff)return;
	if (_str[1] != 0xc0)return;
	if (_str[2] != 0)return;

	auto&& data =  ChStr::StrBinaryToNum<S_SOF, unsigned char>(&_str[0], _str.size(), 0);

	if (data.TexWidht <= 0 || data.TexHeight <= 0)return;

	ChStr::Bytes<unsigned long> wData;
	wData.val = data.TexWidht;

	ChStr::Bytes<unsigned long> hData;
	hData.val = data.TexHeight;

	for (unsigned char i = 0; i < 2; i++)
	{
		wData.byte[i] += wData.byte[4 - i - 1];
		wData.byte[4 - i - 1] = wData.byte[i] - wData.byte[4 - i - 1];
		wData.byte[i] = wData.byte[i] - wData.byte[4 - i - 1];

		hData.byte[i] += hData.byte[4 - i - 1];
		hData.byte[4 - i - 1] = hData.byte[i] - hData.byte[4 - i - 1];
		hData.byte[i] = hData.byte[i] - hData.byte[4 - i - 1];
	}

	original.w = wData.val;
	original.h = hData.val;
}