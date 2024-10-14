
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChTextureList9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChTextureList9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChTex::TextureList9::Release()
{
	if (texList.empty())return;
	texList.clear();

	SetInitFlg(false);
}

ChTex::Texture9* ChTex::TextureList9::GetTexPtr(const unsigned short dataNum)
{
	auto&& tex = texList.find(dataNum);
	if (tex == texList.end())return nullptr;

	return tex->second.get();
}

void ChTex::TextureList9::SetTexture(
	const std::string& _textureName,
	const unsigned short _dataNum,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const D3DCOLOR _colorKey)
{
	if (texList.find(_dataNum) != texList.end())return;

	if (_textureName.length() <= 0)return;

	auto&& tmpTex = ChTex::Texture9::TextureType(_textureName);

	tmpTex->CreateTexture(_textureName, device, _colorKey);

	if (ChPtr::NullCheck(tmpTex->GetTex()))
	{
		//ChSystem::ErrerMessage("âÊëúÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");

		tmpTex = nullptr;
		return;
	}

	SetTextureBase(tmpTex, _dataNum, _gameReSizeWidth, _gameReSizeHeight, _colorKey);
}

//TextureÇÃìoò^//
void ChTex::TextureList9::SetTexture(
	const std::wstring& _textureName,
	const unsigned short _dataNum,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const D3DCOLOR _colorKey)
{
	if (texList.find(_dataNum) != texList.end())return;

	if (_textureName.length() <= 0)return;

	auto&& tmpTex = ChTex::Texture9::TextureType(_textureName);

	tmpTex->CreateTexture(_textureName, device, _colorKey);

	if (ChPtr::NullCheck(tmpTex->GetTex()))
	{
		//ChSystem::ErrerMessage("âÊëúÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");

		tmpTex = nullptr;
		return;
	}

	SetTextureBase(tmpTex, _dataNum, _gameReSizeWidth, _gameReSizeHeight, _colorKey);
}

void ChTex::TextureList9::SetTextureBase(
	ChPtr::Shared<BaseTexture9> _tex,
	const unsigned short _dataNum,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const D3DCOLOR _colorKey)
{
	_tex->SetSclXSize(1.0f);
	_tex->SetSclYSize(1.0f);

	{
		float tmpX, tmpY;
		tmpX = _gameReSizeWidth > 1.0f ? (float)_gameReSizeWidth / (float)_tex->GetOriginalWidth() : 1.0f;
		tmpY = _gameReSizeHeight > 1.0f ? (float)_gameReSizeHeight / (float)_tex->GetOriginalHeight() : 1.0f;

		_tex->SetSclXSize(tmpX);
		_tex->SetSclYSize(tmpY);
	}

	texList[_dataNum] = _tex;
}

void ChTex::TextureList9::SetColorTex(
	const unsigned long& _color,
	const unsigned short _dataNum,
	const unsigned int _gameReSizeWidth,
	const unsigned int _gameReSizeHeight,
	const unsigned long _type)
{

	if (texList.find(_dataNum) != texList.end())return;

	auto tmpTex = ChPtr::Make_S<Texture9>();

	tmpTex->CreateColTexture(device, _color);

	tmpTex->SetSclXSize(1.0f);
	tmpTex->SetSclYSize(1.0f);

	if (_gameReSizeWidth > 0 && _gameReSizeHeight > 0)
	{
		tmpTex->SetSclXSize((float)_gameReSizeWidth);
		tmpTex->SetSclYSize((float)_gameReSizeHeight);
	}

	texList[_dataNum] = tmpTex;

	return;
}

void TextureList9::SetBlendColor(
	const ChVec4& _color,
	const unsigned short _dataNum)
{
	auto&& tex = GetTexPtr(_dataNum);
	if (tex == nullptr)return;

	tex->SetBaseColor(_color);
}

void TextureList9::SetBlendAlpha(const unsigned char _a, const unsigned short _dataNum) {

	auto&& tex = GetTexPtr(_dataNum);
	if (tex == nullptr)return;

	ChVec4 tmpCol = tex->GetBaseColor();
	tmpCol.a = _a;
	tex->SetBaseColor(tmpCol);
}

