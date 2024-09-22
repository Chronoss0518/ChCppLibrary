#define CRT
#define CPP20

#include"ChMapPack.h"

using namespace ChCRT;

template<class _Key, class _Value>
_Value& MapPack<_Key, _Value>::operator[](const _Key& _key) { return value->pack[_key]; }

template<class _Key, class _Value>
const _Value& MapPack<_Key, _Value>::operator [](const _Key& _key) const { return value->pack[_key]; }

template<class _Key, class _Value>
MapPack<_Key, _Value>::MapPack() { value = new MapPackCRT(); }

template<class _Key, class _Value>
MapPack<_Key, _Value>::~MapPack() { delete value; }

template<class _Key, class _Value>
size_t MapPack<_Key, _Value>::GetSize() { return value->pack.size(); }

template<class _Key, class _Value>
_Value* MapPack<_Key, _Value>::Find(const _Key& _key)
{
	auto&& it = value->pack.find(_key);
	if (it == value->pack.end())return nullptr;
	return &it->second;
}

template<class _Key, class _Value>
_Value& MapPack<_Key, _Value>::Insert(const _Key& _key) { return value->pack[_key]; }

template<class _Key, class _Value>
void MapPack<_Key, _Value>::Remove(const _Key& _key)
{

	auto&& it = value->pack.find(_key);
	if (it == value->pack.end())return;
	value->pack.erase(it);
}

template<class _Key, class _Value>
void MapPack<_Key, _Value>::Clear() { value->pack.clear(); }

//templateÇÃñæé¶ìIêÈåæ//

#include"../ChStringPack/ChStringPack.h"
#include"../../BasePack/Ch3D.h"

template ChCRT::MapPack<Ch3D::TextureType, StringPack<char>>;
template ChCRT::MapPack<Ch3D::TextureType, StringPack<wchar_t>>;
template ChCRT::MapPack<Ch3D::TextureType, StringPack<char8_t>>;
template ChCRT::MapPack<Ch3D::TextureType, StringPack<char16_t>>;
template ChCRT::MapPack<Ch3D::TextureType, StringPack<char32_t>>;

template ChCRT::MapPack<StringPack<char>, long>;
template ChCRT::MapPack<StringPack<wchar_t>, long>;
template ChCRT::MapPack<StringPack<char8_t>, long>;
template ChCRT::MapPack<StringPack<char16_t>, long>;
template ChCRT::MapPack<StringPack<char32_t>, long>;
