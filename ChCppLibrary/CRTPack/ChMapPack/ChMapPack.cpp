#define CRT
#define CPP20

#include"ChMapPack.h"

#include"../ChStringPack/ChStringPack.h"
#include"../../BasePack/Ch3D.h"

using namespace ChCRT;

//templateÇÃñæé¶ìIêÈåæ//

#define EXPLICIT_DECLARATION(_keyType,_valueType)\
template _valueType##& MapPack<##_keyType##, _valueType##>::operator[](const _keyType##& _key);\
template const _valueType##& MapPack<##_keyType##, _valueType##>::operator [](const _keyType##& _num) const;\
template MapPack<##_keyType##, _valueType##>::MapPack();\
template MapPack<##_keyType##, _valueType##>::~MapPack();\
template size_t MapPack<##_keyType##, _valueType##>::GetSize();\
template _valueType##* MapPack<##_keyType##, _valueType##>::Find(const _keyType##& _key);\
template _valueType##& MapPack<##_keyType##, _valueType##>::Insert(const _keyType##& _key);\
template void MapPack<##_keyType##, _valueType##>::Remove(const _keyType##& _key);\
template void MapPack<##_keyType##, _valueType##>::Clear();


EXPLICIT_DECLARATION(Ch3D::TextureType, StringPack<char>);
EXPLICIT_DECLARATION(Ch3D::TextureType, StringPack<wchar_t>);
EXPLICIT_DECLARATION(Ch3D::TextureType, StringPack<char8_t>);
EXPLICIT_DECLARATION(Ch3D::TextureType, StringPack<char16_t>);
EXPLICIT_DECLARATION(Ch3D::TextureType, StringPack<char32_t>);

EXPLICIT_DECLARATION(StringPack<char>, long);
EXPLICIT_DECLARATION(StringPack<wchar_t>, long);
EXPLICIT_DECLARATION(StringPack<char8_t>, long);
EXPLICIT_DECLARATION(StringPack<char16_t>, long);
EXPLICIT_DECLARATION(StringPack<char32_t>, long)

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
