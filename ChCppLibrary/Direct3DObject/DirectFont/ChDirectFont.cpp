#include<Windows.h>

#include<d2d1.h>
#include<dwrite.h>

#include"../../BaseIncluder/ChBase.h"
#include"ChDirectFont.h"

using namespace ChD3D;

void DirectFont::Init(unsigned long _w, unsigned long _h)
{

}

bool DirectFont::InitBase(
    const std::wstring& _familyName,
    IDWriteFontCollection* _collection, 
    DWRITE_FONT_WEIGHT _weight,
    DWRITE_FONT_STYLE _style,
    DWRITE_FONT_STRETCH _stretch,
    float _fontSize,
    const std::wstring& _localeName)
{
    if (_familyName.length() <= 0)return false;
    if (_localeName.length() <= 0)return false;
    if (_fontSize <= 0.0f)return false;

    if(FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory)))return false;
    
    if (FAILED(DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&dwFactory)
    )))
    {
        Release();
        return false;
    }
#if false
    if (FAILED(dwFactory->CreateTextFormat(
        L"Gabriola",                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        72.0f,
        L"en-us",
        &textFormat
    )))
    {
        Release();
        return false;
    }
#endif

    if (FAILED(dwFactory->CreateTextFormat(
        _familyName.c_str(),
        _collection,
        _weight,
        _style,
        _stretch,
        _fontSize,
        _localeName.c_str(),
        &textFormat
    )))
    {
        Release();
        return false;
    }

    return true;

}

std::wstring DirectFont::GetLocaleName(LocaleName _localeName)
{
    unsigned long localeNameNo = ChStd::EnumCast(_localeName);
    static std::wstring localeName[] = { L"en-us",L"ja-JP" };

    if (localeNameNo >= (sizeof(localeName) / sizeof(std::wstring)))return L"";

    return localeName[localeNameNo];
}
