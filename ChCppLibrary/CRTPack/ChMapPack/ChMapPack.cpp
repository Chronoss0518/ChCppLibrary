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
_Value* MapPack<_Key, _Value>::Find(const _Key& _key)const
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
void MapPack<_Key, _Value>::Clear() { if(!value->pack.empty())value->pack.clear(); }

template<class _Key, class _Value>
VectorPack<_Key> ChCRT::GetKeyListCRT(const MapPack<_Key, _Value>& _map)
{
	VectorPack<_Key> res;

	for (auto&& it : _map)
	{
		res.Push(it.first);
	}

	return res;
}

template<class _Key, class _Value>
VectorPack<_Value> ChCRT::GetValueListCRT(const MapPack<_Key, _Value>& _map)
{
	VectorPack<_Value> res;

	for (auto&& it : _map)
	{
		res.Push(it.second);
	}

	return res;
}

//templateÇÃñæé¶ìIêÈåæ//

#include"../ChStringPack/ChStringPack.h"
#include"../ChSmartPtrPack/ChSmartPtrPack.h"
#include"../../BasePack/Ch3D.h"
#include"../../CPP/ChJsonObject/ChJsonBaseType.h"


template<> VectorPack<StringPack<char>> ChCRT::GetKeyListCRT(const MapPack<StringPack<char>, SharedPtrPack<ChCpp::JsonBaseType<char>>>& _map);
template<> VectorPack<StringPack<wchar_t>> ChCRT::GetKeyListCRT(const MapPack<StringPack<wchar_t>, SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>>& _map);
template<> VectorPack<StringPack<char8_t>> ChCRT::GetKeyListCRT(const MapPack<StringPack<char8_t>, SharedPtrPack<ChCpp::JsonBaseType<char8_t>>>& _map);
template<> VectorPack<StringPack<char16_t>> ChCRT::GetKeyListCRT(const MapPack<StringPack<char16_t>, SharedPtrPack<ChCpp::JsonBaseType<char16_t>>>& _map);
template<> VectorPack<StringPack<char32_t>> ChCRT::GetKeyListCRT(const MapPack<StringPack<char32_t>, SharedPtrPack<ChCpp::JsonBaseType<char32_t>>>& _map);

template<> VectorPack<SharedPtrPack<ChCpp::JsonBaseType<char>>> ChCRT::GetValueListCRT(const MapPack<StringPack<char>, SharedPtrPack<ChCpp::JsonBaseType<char>>>& _map);
template<> VectorPack<SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>> ChCRT::GetValueListCRT(const MapPack<StringPack<wchar_t>, SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>>& _map);
template<> VectorPack<SharedPtrPack<ChCpp::JsonBaseType<char8_t>>> ChCRT::GetValueListCRT(const MapPack<StringPack<char8_t>, SharedPtrPack<ChCpp::JsonBaseType<char8_t>>>& _map);
template<> VectorPack<SharedPtrPack<ChCpp::JsonBaseType<char16_t>>> ChCRT::GetValueListCRT(const MapPack<StringPack<char16_t>, SharedPtrPack<ChCpp::JsonBaseType<char16_t>>>& _map);
template<> VectorPack<SharedPtrPack<ChCpp::JsonBaseType<char32_t>>> ChCRT::GetValueListCRT(const MapPack<StringPack<char32_t>, SharedPtrPack<ChCpp::JsonBaseType<char32_t>>>& _map);

template<> class ChCRT::MapPack<Ch3D::TextureType, StringPack<char>>;
template<> class ChCRT::MapPack<Ch3D::TextureType, StringPack<wchar_t>>;
template<> class ChCRT::MapPack<Ch3D::TextureType, StringPack<char8_t>>;
template<> class ChCRT::MapPack<Ch3D::TextureType, StringPack<char16_t>>;
template<> class ChCRT::MapPack<Ch3D::TextureType, StringPack<char32_t>>;

template<> class ChCRT::MapPack<StringPack<char>, size_t>;
template<> class ChCRT::MapPack<StringPack<wchar_t>, size_t>;
template<> class ChCRT::MapPack<StringPack<char8_t>, size_t>;
template<> class ChCRT::MapPack<StringPack<char16_t>, size_t>;
template<> class ChCRT::MapPack<StringPack<char32_t>, size_t>;

template<> class ChCRT::MapPack<StringPack<char>, long>;
template<> class ChCRT::MapPack<StringPack<wchar_t>, long>;
template<> class ChCRT::MapPack<StringPack<char8_t>, long>;
template<> class ChCRT::MapPack<StringPack<char16_t>, long>;
template<> class ChCRT::MapPack<StringPack<char32_t>, long>;

template<> class ChCRT::MapPack<StringPack<char>, ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char>>>;
template<> class ChCRT::MapPack<StringPack<wchar_t>, ChCRT::SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>>;
template<> class ChCRT::MapPack<StringPack<char8_t>, ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char8_t>>>;
template<> class ChCRT::MapPack<StringPack<char16_t>, ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char16_t>>>;
template<> class ChCRT::MapPack<StringPack<char32_t>, ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char32_t>>>;
